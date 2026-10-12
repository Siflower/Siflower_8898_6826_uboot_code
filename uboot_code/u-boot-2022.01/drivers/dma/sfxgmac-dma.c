// SPDX-License-Identifier: GPL-2.0+
/*
 * SiFlower Ethernet DMA driver
 * (C) Copyright 2022 qingfang.deng@siflower.com.cn
 */

#include <asm/arch-siflower/eth.h>
#include <asm/io.h>
#include <common.h>
#include <cpu_func.h>
#include <dm.h>
#include <dm/device_compat.h>
#include <dma-uclass.h>
#include <linux/bitfield.h>
#include <linux/delay.h>
#include <log.h>
#include <malloc.h>
#include <net.h>

#define DMA_RX_RING_SZ	PKTBUFSRX
#define DMA_TX_RING_SZ	1

// NPU Searching Engine table regs
#define SE_CLR_RAM_CTRL     0x11180004
#define SE_CLR_RAM_CTRL_IPORT   BIT(1)
#define SE_CLR_RAM_CTRL_IPORT_SPL   BIT(0)
#define SE_CONFIG0      0x11180008
#define SE_CONFIG0_IPSPL_ZERO_LIMIT BIT(19)
#define SE_CONFIG0_IPORT_VALID  BIT(8)
#define SE_TB_OP        0x1118003c
#define SE_TB_OP_BUSY       BIT(31)
#define SE_TB_OP_WR     BIT(24)
#define SE_TB_OP_REQ_ID     GENMASK(21, 16)
#define SE_TB_OP_REQ_ADDR   GENMASK(15, 0)
#define SE_TB_WRDATA0       0x11180040

#define sf_xgmac_dma_chan_is_rx(id)	(!(id))

struct sf_xgmac_dma_rx_desc {
	__le32 rdes0;
	__le32 rdes1;
	__le32 rdes2;
	__le32 rdes3;
	__le32 rdes_ctx0;
	__le32 rdes_ctx1;
	__le32 rdes_ctx2;
	__le32 rdes_ctx3;
};

struct sf_xgmac_dma_tx_desc {
	__le32 tdes_ctx0;
	__le32 tdes_ctx1;
	__le32 tdes_ctx2;
	__le32 tdes_ctx3;
	__le32 tdes0;
	__le32 tdes1;
	__le32 tdes2;
	__le32 tdes3;
};

struct sf_xgmac_dma_ch_priv {
	void *dma_ring;
	u16 refcount;
	u16 dma_ring_size;
	u16 desc_id;
};

struct sf_xgmac_dma_priv {
	void *base;
	struct sf_xgmac_dma_ch_priv rx_ring;
	struct sf_xgmac_dma_ch_priv tx_ring;
};

union npu_iport {
	struct {
		u32 pass_mode : 1;
		u32 vid_zero_handle : 1;
		u32 vlan_security_mode : 1;
		u32 vfp_based_vid_enable : 1;
		u32 vt_en : 1;
		u32 vt_miss_drop : 1;
		u32 use_ivid_as_ovid : 1;
		u32 ifilter_en : 2;
		u32 disable_vlan_check : 1;
		u32 default_port : 5;
		u32 l2_cml : 2;
		u32 action : 2;
		u32 valid : 1;
		u32 rsv0 : 12;
	};
	u32 data;
} __attribute__((__packed__));

enum {
	SE_TB_IPORT_SPL_ID  = 0,
	SE_TB_IPORT_ID      = 1,
};

static int sf_xgmac_dma_request(struct dma *dma)
{
	if (dma->id >= 2)
		return -ENODEV;

	return 0;
}

static void sf_xgmac_dma_init_rx_desc(struct sf_xgmac_dma_rx_desc *rx_desc, void *dst)
{
	rx_desc->rdes0 = cpu_to_le32(virt_to_phys(dst));
	rx_desc->rdes1 = 0;
	rx_desc->rdes2 = 0;
	rx_desc->rdes3 = cpu_to_le32(XGMAC_RDES3_OWN | XGMAC_RDES3_IOC);
	rx_desc->rdes_ctx0 = 0;
	rx_desc->rdes_ctx1 = 0;
	rx_desc->rdes_ctx2 = 0;
	rx_desc->rdes_ctx3 = cpu_to_le32(XGMAC_RDES3_OWN);

	flush_dcache_range((ulong)rx_desc, (ulong)(rx_desc + 1));
}

static void sf_xgmac_dma_init_tx_desc(struct sf_xgmac_dma_tx_desc *tx_desc, void *src,
				      size_t len, ulong ovport)
{
	tx_desc->tdes0 = cpu_to_le32(virt_to_phys(src));
	tx_desc->tdes1 = 0;
	tx_desc->tdes2 = cpu_to_le32(FIELD_PREP(XGMAC_TDES2_B1L, len) | XGMAC_TDES2_IOC);
	tx_desc->tdes3 = cpu_to_le32(XGMAC_TDES3_OWN | XGMAC_TDES3_FD | XGMAC_TDES3_LD);
#ifdef CONFIG_SF21H8898_MPW0
	tx_desc->tdes_ctx0 = cpu_to_le32(XGMAC_TDES0_FAST_MODE | FIELD_PREP(XGMAC_TDES0_OVPORT, ovport));
#else
	tx_desc->tdes_ctx0 = cpu_to_le32(XGMAC_TDES0_FAST_MODE | FIELD_PREP(XGMAC_TDES0_OVPORT, ovport) | HIF_HOST_PORT);
#endif
	tx_desc->tdes_ctx1 = 0;
	tx_desc->tdes_ctx2 = 0;
	tx_desc->tdes_ctx3 = cpu_to_le32(XGMAC_TDES3_OWN | XGMAC_TDES3_CTXT | XGMAC_TDES3_PIDV);

	flush_dcache_range((ulong)tx_desc, (ulong)(tx_desc + 1));
}

static int sf_xgmac_dma_enable(struct dma *dma)
{
	struct sf_xgmac_dma_priv *priv = dev_get_priv(dma->dev);
	struct sf_xgmac_dma_rx_desc *rx_desc;
	struct sf_xgmac_dma_ch_priv *ch_priv;
	int i;

	if (sf_xgmac_dma_chan_is_rx(dma->id)) {
		ch_priv = &priv->rx_ring;
		if (ch_priv->refcount++)
			return 0;

		ch_priv->dma_ring_size = DMA_RX_RING_SZ;
		ch_priv->dma_ring = (void *)0x1c000000 + sizeof(struct sf_xgmac_dma_tx_desc);
	} else {
		ch_priv = &priv->tx_ring;
		if (ch_priv->refcount++)
			return 0;

		ch_priv->dma_ring_size = DMA_TX_RING_SZ;
		ch_priv->dma_ring = (void *)0x1c000000;
	}


	ch_priv->desc_id = 0;

	/* don't handle dma tx buffer here, instead enable it in ops->send */
	if (!sf_xgmac_dma_chan_is_rx(dma->id))
		return 0;

	rx_desc = ch_priv->dma_ring;

	/* init dma rx descs */
	for (i = 0; i < ch_priv->dma_ring_size; i++) {
		sf_xgmac_dma_init_rx_desc(&rx_desc[i], net_rx_packets[i]);
	}

	/* configure dma rx ring registers */
	writel(cpu_to_le32(virt_to_phys(rx_desc)),
	       priv->base + XGMAC_DMA_CH_RxDESC_LADDR(0));
	writel(cpu_to_le32(virt_to_phys(rx_desc + ch_priv->dma_ring_size)),
	       priv->base + XGMAC_DMA_CH_RxDESC_TAIL_LPTR(0));
	writel(ch_priv->dma_ring_size * 2 - 1,
	       priv->base + XGMAC_DMA_CH_RxDESC_RING_LEN(0));

	/* set rx buffer size */
	clrsetbits_32(priv->base + XGMAC_DMA_CH_RX_CONTROL(0),
		      XGMAC_RBSZ, FIELD_PREP(XGMAC_RBSZ, PKTSIZE_ALIGN));

	/* start rx */
	setbits_32(priv->base + XGMAC_DMA_CH_RX_CONTROL(0), XGMAC_RXST);

	return 0;
}

static int sf_xgmac_dma_disable(struct dma *dma)
{
	struct sf_xgmac_dma_priv *priv = dev_get_priv(dma->dev);
	struct sf_xgmac_dma_ch_priv *ch_priv;

	if (sf_xgmac_dma_chan_is_rx(dma->id)) {
		ch_priv = &priv->rx_ring;
	} else {
		ch_priv = &priv->tx_ring;
	}

	if (!ch_priv->refcount)
		return 0;

	if (ch_priv->refcount-- > 1)
		return 0;

	/* stop rx */
	if (sf_xgmac_dma_chan_is_rx(dma->id)) {
		clrbits_32(priv->base + XGMAC_DMA_CH_RX_CONTROL(0), XGMAC_RXST);

		writel(XGMAC_RPS, priv->base + XGMAC_DMA_CH_STATUS(0));
	}

	return 0;
}

static int sf_xgmac_dma_send(struct dma *dma, void *src, size_t len, void *metadata)
{
	struct sf_xgmac_dma_priv *priv = dev_get_priv(dma->dev);
	struct sf_xgmac_dma_ch_priv *ch_priv = &priv->tx_ring;
	struct sf_xgmac_dma_tx_desc *tx_desc = ch_priv->dma_ring;

	if (!ch_priv->refcount)
		return -ENETDOWN;

	tx_desc += ch_priv->desc_id;

	flush_dcache_range((ulong)src, (ulong)(src + len));

	/* prepare tx desc */
	sf_xgmac_dma_init_tx_desc(tx_desc, src, len, (ulong)metadata);

	/* configure dma tx ring registers */
	writel(cpu_to_le32(virt_to_phys(tx_desc)),
	       priv->base + XGMAC_DMA_CH_TxDESC_LADDR(0));
	writel(cpu_to_le32(virt_to_phys(tx_desc + 1)),
	       priv->base + XGMAC_DMA_CH_TxDESC_TAIL_LPTR(0));
	writel(ch_priv->dma_ring_size * 2 - 1,
	       priv->base + XGMAC_DMA_CH_TxDESC_RING_LEN(0));

	/* start tx */
	setbits_32(priv->base + XGMAC_DMA_CH_TX_CONTROL(0), XGMAC_TXST);

	/* wait until own bit is cleared */
	do {
		invalidate_dcache_range((ulong)tx_desc, (ulong)(tx_desc + 1));
	} while (READ_ONCE(tx_desc->tdes3) & XGMAC_TDES3_OWN);

	/* stop tx */
	clrbits_32(priv->base + XGMAC_DMA_CH_TX_CONTROL(0), XGMAC_TXST);

	while (!(readl(priv->base + XGMAC_DMA_CH_STATUS(0)) & XGMAC_TPS));
	writel(XGMAC_TPS, priv->base + XGMAC_DMA_CH_STATUS(0));

	return 0;
}

#ifndef CONFIG_SF21H8898_MPW0
static void npu_tb_op_wait(void)
{
	for (int i = 0; i < 1000 && (readl(SE_TB_OP) & SE_TB_OP_BUSY); i++)
		;
}

static void npu_tb_clr(void)
{
	writel(SE_CLR_RAM_CTRL_IPORT | SE_CLR_RAM_CTRL_IPORT_SPL, SE_CLR_RAM_CTRL);
	for (int i = 0; i < 100 && (readl(SE_CLR_RAM_CTRL) != 0); i++)
		mdelay(1);
}

static void npu_init(void)
{
	const union npu_iport iport = {
		.valid = 1,
		.action = 1,
	};
	u32 reg;

	// clear tables
	npu_tb_clr();
	// enable iport table and disable speed limit
	reg = readl(SE_CONFIG0);
	reg |= SE_CONFIG0_IPORT_VALID;
	reg &= ~SE_CONFIG0_IPSPL_ZERO_LIMIT;
	writel(reg, SE_CONFIG0);

	// configure iport table
	writel(iport.data, SE_TB_WRDATA0);
	for (int i = 0; i < 6; i++) {
		reg = SE_TB_OP_WR | FIELD_PREP(SE_TB_OP_REQ_ADDR, i) |
			FIELD_PREP(SE_TB_OP_REQ_ID, SE_TB_IPORT_ID);

		writel(reg, SE_TB_OP);

		npu_tb_op_wait();
	}
}
#endif
static int sf_xgmac_dma_probe(struct udevice *dev)
{
	struct dma_dev_priv *uc_priv = dev_get_uclass_priv(dev);
	struct sf_xgmac_dma_priv *priv = dev_get_priv(dev);

	priv->base = dev_read_addr_ptr(dev);
	if (!priv->base)
		return -EINVAL;

#ifdef CONFIG_SF21H8898_MPW0
	setbits_32(0x0ce01888, BIT(6));
	setbits_32(0x0ce018e4, BIT(31));
#else
	// Use queue 0 only
	writel(0x403f003f, HIF_MRI_Q_EN);
	npu_init();
#endif

	/* soft reset DMA */
	writel(XGMAC_SWR, priv->base + XGMAC_DMA_MODE);
	while (readl(priv->base + XGMAC_DMA_MODE) & XGMAC_SWR);

	/* set burst length 32 */
	clrsetbits_32(priv->base + XGMAC_DMA_SYSBUS_MODE,
		      XGMAC_BLEN, XGMAC_BLEN32);

	/* disable descriptor prefetch */
	writel(FIELD_PREP(XGMAC_TEDM, 0x3), priv->base + XGMAC_TX_EDMA_CTRL);
	writel(FIELD_PREP(XGMAC_REDM, 0x3), priv->base + XGMAC_RX_EDMA_CTRL);

	/* MTL op mode: weighted round robin, weight strict policy, forward tx status */
	writel(XGMAC_WRR | XGMAC_RAA | XGMAC_FTS, priv->base + XGMAC_MTL_OPMODE);

#ifdef CONFIG_SF21H8898_MPW0
	/* MTL TXQ mode: enable txq, size 2KB */
	writel(FIELD_PREP(XGMAC_TQS, 0x7) | FIELD_PREP(XGMAC_TXQEN, 0x2) |XGMAC_TSF, priv->base + XGMAC_MTL_TXQ_OPMODE(0));
#else
	/* MTL TXQ mode: enable txq, size 4KB */
	writel(FIELD_PREP(XGMAC_TQS, 0xf) | FIELD_PREP(XGMAC_TXQEN, 0x2) |XGMAC_TSF, priv->base + XGMAC_MTL_TXQ_OPMODE(0));
#endif

#ifdef CONFIG_SF21H8898_MPW0
	/* MTL RXQ mode: enable rxq, size 2KB */
	writel(FIELD_PREP(XGMAC_RQS, 0x7) | XGMAC_RSF, priv->base + XGMAC_MTL_RXQ_OPMODE(0));
#else
	/* MTL RXQ mode: enable rxq, size 4KB */
	writel(FIELD_PREP(XGMAC_RQS, 0xf) | XGMAC_RSF, priv->base + XGMAC_MTL_RXQ_OPMODE(0));
#endif

	/* enable interrupt */
	writel(XGMAC_DMA_INT_DEFAULT_EN, priv->base + XGMAC_DMA_CH_INT_EN(0));

	/* enable rx packet flush */
	setbits_32(priv->base + XGMAC_DMA_CH_RX_CONTROL(0), XGMAC_RPF);

	uc_priv->supported = (DMA_SUPPORTS_DEV_TO_MEM |
			      DMA_SUPPORTS_MEM_TO_DEV);

	return 0;
}

static int sf_xgmac_dma_remove(struct udevice *dev)
{
	struct sf_xgmac_dma_priv *priv = dev_get_priv(dev);

	writel(XGMAC_SWR, priv->base + XGMAC_DMA_MODE);

	return 0;
}

static int sf_xgmac_dma_prepare_rcv_buf(struct dma *dma, void *dst, size_t size)
{
	struct sf_xgmac_dma_priv *priv = dev_get_priv(dma->dev);
	struct sf_xgmac_dma_ch_priv *ch_priv = &priv->rx_ring;
	struct sf_xgmac_dma_rx_desc *rx_desc = ch_priv->dma_ring;
	u32 i;

	for (i = 0; i < ch_priv->dma_ring_size; i++) {
		if (net_rx_packets[i] == dst) {
			sf_xgmac_dma_init_rx_desc(&rx_desc[i], dst);
			writel(cpu_to_le32(virt_to_phys(&rx_desc[i + 1])), priv->base + XGMAC_DMA_CH_RxDESC_TAIL_LPTR(0));
			return 0;
		}
	}

	return -ENOENT;
}

static int sf_xgmac_dma_receive(struct dma *dma, void **dst, void *metadata)
{
	struct sf_xgmac_dma_priv *priv = dev_get_priv(dma->dev);
	struct sf_xgmac_dma_ch_priv *ch_priv = &priv->rx_ring;
	struct sf_xgmac_dma_rx_desc *rx_desc = ch_priv->dma_ring;
	u32 len;

	if (!ch_priv->refcount)
		return -ENETDOWN;

	rx_desc += ch_priv->desc_id;

	invalidate_dcache_range((ulong)rx_desc,(ulong)(rx_desc + 1));

	if (rx_desc->rdes3 & XGMAC_RDES3_OWN)
		return -EAGAIN;

	if (FIELD_GET(XGMAC_RDES0_IVPORT, rx_desc->rdes0) != (ulong)metadata)
		return -EAGAIN;

	*dst = net_rx_packets[ch_priv->desc_id];

	len = FIELD_GET(XGMAC_RDES3_PL, rx_desc->rdes3);

	invalidate_dcache_range((ulong)(*dst), (ulong)(*dst) + len);

	ch_priv->desc_id = (ch_priv->desc_id + 1) % ch_priv->dma_ring_size;

	writel(XGMAC_RI | XGMAC_RBU, priv->base + XGMAC_DMA_CH_STATUS(0));

	return len;
}

static const struct dma_ops sf_xgmac_dma_ops = {
	.disable = sf_xgmac_dma_disable,
	.enable = sf_xgmac_dma_enable,
	.prepare_rcv_buf = sf_xgmac_dma_prepare_rcv_buf,
	.request = sf_xgmac_dma_request,
	.receive = sf_xgmac_dma_receive,
	.send = sf_xgmac_dma_send,
};

static const struct udevice_id sf_xgmac_dma_ids[] = {
	{ .compatible = "siflower,sf21h8898-xgmac-dma" },
	{ }
};

U_BOOT_DRIVER(sf_xgmac_dma) = {
	.name		= "sf_xgmac_dma",
	.id		= UCLASS_DMA,
	.of_match	= sf_xgmac_dma_ids,
	.ops		= &sf_xgmac_dma_ops,
	.priv_auto	= sizeof(struct sf_xgmac_dma_priv),
	.probe		= sf_xgmac_dma_probe,
	.remove		= sf_xgmac_dma_remove,
	.flags		= DM_REMOVE_ACTIVE_DMA,
};

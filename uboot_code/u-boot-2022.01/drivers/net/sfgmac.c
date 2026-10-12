// SPDX-License-Identifier: GPL-2.0+
/*
 * SiFlower DWC GMAC driver
 * (C) Copyright 2022 qingfang.deng@siflower.com.cn
 */

#include <asm/arch-siflower/eth.h>
#include <asm/io.h>
#include <dma.h>
#include <eth_phy.h>
#include <linux/bitfield.h>
#include <miiphy.h>

struct sf_gmac_priv {
	struct phy_device *phy;
	struct dma rx;
	struct dma tx;
	u32 gmac_id;
};

static int sf_gmac_start(struct udevice *dev)
{
	struct sf_gmac_priv *priv = dev_get_priv(dev);
	struct eth_pdata *pdata = dev_get_plat(dev);
	u32 val;
	int ret;

	val = GMAC_CONTROL_ACS | GMAC_CONTROL_BE | GMAC_CONTROL_CST;

	ret = phy_startup(priv->phy);
	if (ret)
		return ret;

	if (priv->phy->speed != 1000)
		val |= GMAC_CONTROL_PS;

	if (priv->phy->speed == 100)
		val |= GMAC_CONTROL_FES;

	if (priv->phy->duplex)
		val |= GMAC_CONTROL_DM;

	writel(val, pdata->iobase + GMAC_CONTROL);

	val = FIELD_PREP(GMAC_FLOW_CTRL_PT_MASK, 0x400);
	if (priv->phy->pause)
		val |= GMAC_FLOW_CTRL_RFE | GMAC_FLOW_CTRL_TFE;
	else if (priv->phy->asym_pause)
		val |= GMAC_FLOW_CTRL_TFE;

	writel(val, pdata->iobase + GMAC_FLOW_CTRL);

	ret = dma_enable(&priv->rx);
	if (ret)
		return ret;

	ret = dma_enable(&priv->tx);
	if (ret) {
		dma_disable(&priv->rx);
		return ret;
	}

	setbits_32(pdata->iobase + GMAC_CONTROL, GMAC_CONTROL_TE | GMAC_CONTROL_RE);

	if (priv->gmac_id < 4) {
		clrbits_32(0x0ce018ec, BIT(priv->gmac_id));
		setbits_32(0x0ce018ec, BIT(priv->gmac_id));
	}

	return 0;
}

static int sf_gmac_send(struct udevice *dev, void *packet, int length)
{
	struct sf_gmac_priv *priv = dev_get_priv(dev);

	return dma_send(&priv->tx, packet, length, (void*)(ulong)priv->gmac_id);
}

static int sf_gmac_recv(struct udevice *dev, int flags, uchar **packetp)
{
	struct sf_gmac_priv *priv = dev_get_priv(dev);

	return dma_receive(&priv->rx, (void**)packetp, (void*)(ulong)priv->gmac_id);
}

static int sf_gmac_free_pkt(struct udevice *dev, uchar *packet, int len)
{
	struct sf_gmac_priv *priv = dev_get_priv(dev);

	return dma_prepare_rcv_buf(&priv->rx, packet,len);
}

static void sf_gmac_stop(struct udevice *dev)
{
	struct eth_pdata *pdata = dev_get_plat(dev);
	struct sf_gmac_priv *priv = dev_get_priv(dev);

	phy_shutdown(priv->phy);

	writel(0, pdata->iobase + GMAC_CONTROL);

	dma_disable(&priv->rx);
	dma_disable(&priv->tx);
}

static int sf_gmac_write_hwaddr(struct udevice *dev)
{
	struct eth_pdata *pdata = dev_get_plat(dev);
	u8 *mac_id = pdata->enetaddr;
	u32 macid_lo, macid_hi;

	macid_lo = mac_id[0] | (mac_id[1] << 8) | (mac_id[2] << 16) |
		   (mac_id[3] << 24);
	macid_hi = mac_id[4] | (mac_id[5] << 8);

	writel(macid_hi, pdata->iobase + GMAC_ADDR_HIGH(0));
	writel(macid_lo, pdata->iobase + GMAC_ADDR_LOW(0));

	return 0;
}

static int sf_gmac_set_promisc(struct udevice *dev, bool enable)
{
	struct eth_pdata *pdata = dev_get_plat(dev);

	if (enable)
		setbits_32(pdata->iobase + GMAC_FRAME_FILTER, GMAC_FRAME_FILTER_PR);
	else
		clrbits_32(pdata->iobase + GMAC_FRAME_FILTER, GMAC_FRAME_FILTER_PR);

	return 0;
}

static const struct eth_ops sf_gmac_eth_ops = {
	.start		= sf_gmac_start,
	.send		= sf_gmac_send,
	.recv		= sf_gmac_recv,
	.free_pkt	= sf_gmac_free_pkt,
	.stop		= sf_gmac_stop,
	.write_hwaddr	= sf_gmac_write_hwaddr,
	.set_promisc	= sf_gmac_set_promisc,
};

static int sf_gmac_of_to_plat(struct udevice *dev)
{
	struct sf_gmac_priv *priv = dev_get_priv(dev);
	struct eth_pdata *pdata = dev_get_plat(dev);
	const char *phy_mode;
	char name[6];

	pdata->iobase = dev_read_addr(dev);
	if (pdata->iobase == FDT_ADDR_T_NONE)
		return -EINVAL;

	priv->gmac_id = (pdata->iobase - 0x08000000) / 0x4000;
	if (priv->gmac_id > 4)
		return -EINVAL;

	phy_mode = dev_read_string(dev, "phy-mode");
	if (phy_mode) {
		pdata->phy_interface = phy_get_interface_by_name(phy_mode);

		/* MAC 0~3 supports QSGMII
		 * MAC 4 supports RGMII
		 */
		if (priv->gmac_id == 4) {
			if (pdata->phy_interface != PHY_INTERFACE_MODE_RGMII &&
			    pdata->phy_interface != PHY_INTERFACE_MODE_RGMII_ID &&
			    pdata->phy_interface != PHY_INTERFACE_MODE_RGMII_RXID &&
			    pdata->phy_interface != PHY_INTERFACE_MODE_RGMII_TXID)
				return -EINVAL;
		} else if (pdata->phy_interface != PHY_INTERFACE_MODE_QSGMII)
			return -EINVAL;

	} else if (priv->gmac_id == 4)
		pdata->phy_interface = PHY_INTERFACE_MODE_RGMII;
	else
		pdata->phy_interface = PHY_INTERFACE_MODE_QSGMII;

	pdata->max_speed = 1000;

	snprintf(name, sizeof(name), "gmac%u", priv->gmac_id);
	return device_set_name(dev, name);
}

static int sf_gmac_probe(struct udevice *dev)
{
	struct sf_gmac_priv *priv = dev_get_priv(dev);
	struct eth_pdata *pdata = dev_get_plat(dev);
	struct mii_dev *bus;
	int ret;

	clrbits_32(0x0ce01888, BIT(priv->gmac_id));
	setbits_32(0x0ce01888, BIT(priv->gmac_id));

	/* make pcs work */
	dm_mdio_probe_devices();

	/* configure delay for mac 4 */
	if (priv->gmac_id == 4) {
		u32 mac4_ctrl = 0;
		u32 delay;

		if (pdata->phy_interface == PHY_INTERFACE_MODE_RGMII_TXID ||
		    pdata->phy_interface == PHY_INTERFACE_MODE_RGMII) {
			delay = dev_read_u32_default(dev, "rx-internal-delay-ps", 0);
			delay = DIV_ROUND_CLOSEST(delay, 49);
			if (!FIELD_FIT(MAC4_RX_DELAY, delay))
				return -EINVAL;
			if (delay)
				mac4_ctrl |= MAC4_RX_DELAY_EN | FIELD_PREP(MAC4_RX_DELAY, delay);
		}

		if (pdata->phy_interface == PHY_INTERFACE_MODE_RGMII_RXID ||
		    pdata->phy_interface == PHY_INTERFACE_MODE_RGMII) {
			delay = dev_read_u32_default(dev, "tx-internal-delay-ps", 0);
			delay = DIV_ROUND_CLOSEST(delay, 49);
			if (!FIELD_FIT(MAC4_TX_DELAY, delay))
				return -EINVAL;
			if (delay)
				mac4_ctrl |= MAC4_TX_DELAY_EN | FIELD_PREP(MAC4_TX_DELAY, delay);
		}

		clrsetbits_32(MAC4_CTRL, MAC4_DELAY_MASK, mac4_ctrl);
	}

	bus = eth_phy_get_mdio_bus(dev);
	if (bus)
		eth_phy_set_mdio_bus(dev, bus);

	ret = dma_get_by_index(dev, 0, &priv->rx);
	if (ret)
		return ret;

	ret = dma_get_by_index(dev, 1, &priv->tx);
	if (ret)
		return ret;

	priv->phy = phy_connect(bus, eth_phy_get_addr(dev), dev,
				pdata->phy_interface);
	if (!priv->phy)
		return -ENODEV;

	priv->phy->supported &= PHY_GBIT_FEATURES;
	ret = phy_set_supported(priv->phy, pdata->max_speed);
	if (ret)
		return ret;

	priv->phy->advertising = priv->phy->supported;

	return phy_config(priv->phy);
}

static int sf_gmac_remove(struct udevice *dev)
{
	struct sf_gmac_priv *priv = dev_get_priv(dev);

	clrbits_32(0x0ce01888, BIT(priv->gmac_id));

	return 0;
}

static const struct udevice_id sf_gmac_ids[] = {
	{ .compatible = "siflower,sf21h8898-gmac" },
	{}
};

U_BOOT_DRIVER(sf_gmac) = {
	.name		= "sf_gmac",
	.id		= UCLASS_ETH,
	.of_match	= sf_gmac_ids,
	.of_to_plat	= sf_gmac_of_to_plat,
	.probe		= sf_gmac_probe,
	.remove		= sf_gmac_remove,
	.ops		= &sf_gmac_eth_ops,
	.priv_auto	= sizeof(struct sf_gmac_priv),
	.plat_auto	= sizeof(struct eth_pdata),
};

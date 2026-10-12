// SPDX-License-Identifier: GPL-2.0+
/*
 * SiFlower DWC XGMAC driver
 * (C) Copyright 2022 qingfang.deng@siflower.com.cn
 */

#include <asm/arch-siflower/eth.h>
#include <asm/io.h>
#include <dma.h>
#include <eth_phy.h>
#include <linux/bitfield.h>
#include <malloc.h>
#include <miiphy.h>

#include <linux/delay.h>
#include <asm-generic/gpio.h>

struct sf_xgmac_priv {
	struct phy_device *phy;
	struct mii_dev *mdio;
	struct dma rx;
	struct dma tx;
	u32 gmac_id;
};

static int sf_xgmac_mdio_read(struct mii_dev *bus, int addr, int devad, int reg)
{
	u32 timeout = 100000;
	u32 r;

	r = FIELD_PREP(XGMAC_MDIO_ADDR_PA, addr) | FIELD_PREP(XGMAC_MDIO_ADDR_RA, reg);
	if (devad < 0) {
		setbits_32(bus->priv + XGMAC_MDIO_C22P, BIT(addr));
	} else {
		clrbits_32(bus->priv + XGMAC_MDIO_C22P, BIT(addr));
		r |= FIELD_PREP(XGMAC_MDIO_ADDR_DA, devad);
	}

	writel(r, bus->priv + XGMAC_MDIO_ADDR);

	r = XGMAC_MDIO_DATA_SBUSY | XGMAC_MDIO_DATA_CMD_RD;
	writel(r, bus->priv + XGMAC_MDIO_DATA);

	//TODO: use wait_bit after timer driver is ready
	while ((r = readl(bus->priv + XGMAC_MDIO_DATA)) & XGMAC_MDIO_DATA_SBUSY) {
		if (!--timeout)
			return -ETIMEDOUT;
	}

	return FIELD_GET(XGMAC_MDIO_DATA_SDATA, r);
}

static int sf_xgmac_mdio_write(struct mii_dev *bus, int addr, int devad, int reg, u16 val)
{
	u32 timeout = 100000;
	u32 r;

	r = FIELD_PREP(XGMAC_MDIO_ADDR_PA, addr) | FIELD_PREP(XGMAC_MDIO_ADDR_RA, reg);
	if (devad < 0) {
		setbits_32(bus->priv + XGMAC_MDIO_C22P, BIT(addr));
	} else {
		clrbits_32(bus->priv + XGMAC_MDIO_C22P, BIT(addr));
		r |= FIELD_PREP(XGMAC_MDIO_ADDR_DA, devad);
	}

	writel(r, bus->priv + XGMAC_MDIO_ADDR);

	r = XGMAC_MDIO_DATA_SBUSY | XGMAC_MDIO_DATA_CMD_WR |
	    FIELD_PREP(XGMAC_MDIO_DATA_SDATA, val);
	writel(r, bus->priv + XGMAC_MDIO_DATA);

	//TODO: use wait_bit after timer driver is ready
	while (readl(bus->priv + XGMAC_MDIO_DATA) & XGMAC_MDIO_DATA_SBUSY) {
		if (!--timeout)
			return -ETIMEDOUT;
	}

	return 0;
}

static int sf_xgmac_mdio_probe(struct udevice *dev)
{
	struct sf_xgmac_priv *priv = dev_get_priv(dev);
	struct eth_pdata *pdata = dev_get_plat(dev);
	struct mii_dev *mdio;
	int ret;

#ifdef CONFIG_SF21H8898_MPW0
	/* mpw0 shold return err here with gmac init */
	if (pdata->phy_interface != PHY_INTERFACE_MODE_USXGMII)
		return -EINVAL;
#endif

	ret = eth_phy_binds_nodes(dev);
	if (ret)
		return 0;

	mdio = mdio_alloc();
	if (!mdio)
		return -ENOMEM;

	snprintf(mdio->name, MDIO_NAME_LEN, "xgmac-mdio%u", priv->gmac_id);
	mdio->priv = (void*) pdata->iobase;
	mdio->read = sf_xgmac_mdio_read;
	mdio->write = sf_xgmac_mdio_write;

	ret = mdio_register(mdio);
	if (ret) {
		free(mdio);
		return ret;
	}

	priv->mdio = mdio;

	eth_phy_set_mdio_bus(dev, mdio);

	return 0;
}

static int sf_xgmac_start(struct udevice *dev)
{
	struct sf_xgmac_priv *priv = dev_get_priv(dev);
	struct eth_pdata *pdata = dev_get_plat(dev);
	u32 val;
	int ret;

	ret = phy_startup(priv->phy);
	if (ret)
		return ret;

	val = readl(pdata->iobase + XGMAC_EXT_CFG);
	if (priv->phy->duplex == DUPLEX_FULL)
		val &= ~XGMAC_EXT_CFG_HD;
	else
		val |= XGMAC_EXT_CFG_HD;

	writel(val, pdata->iobase + XGMAC_EXT_CFG);
	val = readl(pdata->iobase + XGMAC_TX_CONFIG);
	val |= XGMAC_CONFIG_TE;
	val &= ~XGMAC_CONFIG_SS_MASK;

	switch (priv->phy->speed) {
	case SPEED_2500:
		val |= XGMAC_CONFIG_SS_2500_GMII;
		break;
	case SPEED_1000:
		val |= XGMAC_CONFIG_SS_1000_GMII;
		break;
	case SPEED_100:
		val |= XGMAC_CONFIG_SS_100_MII;
		break;
	case SPEED_10:
		val |= XGMAC_CONFIG_SS_10_MII;
		break;
	}

	writel(val, pdata->iobase + XGMAC_TX_CONFIG);

	ret = dma_enable(&priv->rx);
	if (ret)
		return ret;

	ret = dma_enable(&priv->tx);
	if (ret) {
		dma_disable(&priv->rx);
		return ret;
	}

	val = XGMAC_CONFIG_CST | XGMAC_CONFIG_ACS | XGMAC_CONFIG_RE;
	writel(val, pdata->iobase + XGMAC_RX_CONFIG);

	return 0;
}

static int sf_xgmac_send(struct udevice *dev, void *packet, int length)
{
	struct sf_xgmac_priv *priv = dev_get_priv(dev);

	return dma_send(&priv->tx, packet, length, (void*)(ulong)priv->gmac_id);
}

static int sf_xgmac_recv(struct udevice *dev, int flags, uchar **packetp)
{
	struct sf_xgmac_priv *priv = dev_get_priv(dev);

	return dma_receive(&priv->rx, (void**)packetp, (void*)(ulong)priv->gmac_id);
}

static int sf_xgmac_free_pkt(struct udevice *dev, uchar *packet, int len)
{
	struct sf_xgmac_priv *priv = dev_get_priv(dev);

	return dma_prepare_rcv_buf(&priv->rx, packet,len);
}

static void sf_xgmac_stop(struct udevice *dev)
{
	struct sf_xgmac_priv *priv = dev_get_priv(dev);
	struct eth_pdata *pdata = dev_get_plat(dev);

	writel(0, pdata->iobase + XGMAC_TX_CONFIG);
	writel(0, pdata->iobase + XGMAC_RX_CONFIG);

	dma_disable(&priv->rx);
	dma_disable(&priv->tx);
}

static int sf_xgmac_write_hwaddr(struct udevice *dev)
{
	struct eth_pdata *pdata = dev_get_plat(dev);
	u8 *mac_id = pdata->enetaddr;
	u32 macid_lo, macid_hi;

	macid_lo = mac_id[0] | (mac_id[1] << 8) | (mac_id[2] << 16) |
		   (mac_id[3] << 24);
	macid_hi = mac_id[4] | (mac_id[5] << 8);

	writel(macid_hi, pdata->iobase + XGMAC_ADDRx_HIGH(0));
	writel(macid_lo, pdata->iobase + XGMAC_ADDRx_LOW(0));

	return 0;
}

static int sf_xgmac_set_promisc(struct udevice *dev, bool enable)
{
	struct eth_pdata *pdata = dev_get_plat(dev);

	if (enable)
		setbits_32(pdata->iobase + XGMAC_PACKET_FILTER, XGMAC_FILTER_PR);
	else
		clrbits_32(pdata->iobase + XGMAC_PACKET_FILTER, XGMAC_FILTER_PR);

	return 0;
}

const struct eth_ops sf_xgmac_ops = {
	.start		= sf_xgmac_start,
	.send		= sf_xgmac_send,
	.recv		= sf_xgmac_recv,
	.free_pkt	= sf_xgmac_free_pkt,
	.stop		= sf_xgmac_stop,
	.write_hwaddr	= sf_xgmac_write_hwaddr,
	.set_promisc	= sf_xgmac_set_promisc,
};

static int sf_xgmac_of_to_plat(struct udevice *dev)
{
	struct sf_xgmac_priv *priv = dev_get_priv(dev);
	struct eth_pdata *pdata = dev_get_plat(dev);
	const char *phy_mode;
	char name[7];
	u32 reg = 0, rxd = MAC5_DELAY_DEFAULT, txd = MAC5_DELAY_DEFAULT;

	pdata->iobase = dev_read_addr(dev);
	if (pdata->iobase == FDT_ADDR_T_NONE)
		return -EINVAL;

	priv->gmac_id = (pdata->iobase - 0x08000000) / 0x4000;

	phy_mode = dev_read_string(dev, "phy-mode");
	if (!phy_mode)
		return -EINVAL;

	pdata->phy_interface = phy_get_interface_by_name(phy_mode);

	dev_read_u32(dev, "rx-internal-delay-ps", &rxd);
	dev_read_u32(dev, "tx-internal-delay-ps", &txd);

	if (pdata->phy_interface == PHY_INTERFACE_MODE_RGMII ||
			pdata->phy_interface == PHY_INTERFACE_MODE_RGMII_TXID ||
			pdata->phy_interface == PHY_INTERFACE_MODE_RGMII_RXID ||
			pdata->phy_interface == PHY_INTERFACE_MODE_RGMII_ID) {

		rxd = DIV_ROUND_CLOSEST(rxd, MAC5_DELAY_STEP);
		txd = DIV_ROUND_CLOSEST(txd, MAC5_DELAY_STEP);

		if (rxd > 256 || txd > 256)
			return -EINVAL;

		if (rxd)
			reg |= FIELD_PREP(MAC5_RX_DELAY, rxd - 1) | MAC5_RX_DELAY_EN;

		if (txd)
			reg |= FIELD_PREP(MAC5_TX_DELAY, txd - 1) | MAC5_TX_DELAY_EN;

		writel(reg, MAC5_CTRL);
	}

#ifdef CONFIG_CMD_MULUP
	/* Allow lif to receive multicast packets */
	setbits_32(pdata->iobase + XGMAC_PACKET_FILTER, XGMAC_FILTER_PM);
#endif

	pdata->max_speed = 1000;
	snprintf(name, sizeof(name), "xgmac%u", priv->gmac_id);
	return device_set_name(dev, name);
}

static int sf_xgmac_probe(struct udevice *dev)
{
	struct sf_xgmac_priv *priv = dev_get_priv(dev);
	struct eth_pdata *pdata = dev_get_plat(dev);
	struct mii_dev *bus;
	int ret;

#ifdef CONFIG_SF21H8898_MPW0
	setbits_32(0x0ce01888, BIT(priv->gmac_id));
#else
	if (priv->gmac_id == 5) {
		/* mac5 is rgmii
		 * mac5 reset bit change to BIT9 in 8898 mpw1
		 * rgmii mode set must under mac reset*/
		clrbits_32(0x0ce01888, BIT(9));
		setbits_32(ETHSYS_MAC5_CTRL, FIELD_PREP(MAC5_PHY_INTF_SEL, 1));
		setbits_32(0x0ce01888, BIT(9));
	}else {
		setbits_32(0x0ce01888, BIT(priv->gmac_id));
	}
#endif

	ret = dma_get_by_index(dev, 0, &priv->rx);
	if (ret)
		return ret;

	ret = dma_get_by_index(dev, 1, &priv->tx);
	if (ret)
		return ret;

	ret = sf_xgmac_mdio_probe(dev);
	if (ret)
		return ret;

	/* make pcs work */
	dm_mdio_probe_devices();

	bus = eth_phy_get_mdio_bus(dev);
	if (!bus)
		bus = priv->mdio;

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

static int sf_xgmac_remove(struct udevice *dev)
{
	struct sf_xgmac_priv *priv = dev_get_priv(dev);

	clrbits_32(0x0ce01888, BIT(priv->gmac_id));
	mdio_unregister(priv->mdio);
	free(priv->mdio);

	return 0;
}

static const struct udevice_id sf_xgmac_ids[] = {
	{ .compatible = "siflower,sf21h8898-xgmac" },
	{ }
};

U_BOOT_DRIVER(eth_sf_xgmac) = {
	.name		= "sf_xgmac",
	.id		= UCLASS_ETH,
	.of_match	= sf_xgmac_ids,
	.of_to_plat	= sf_xgmac_of_to_plat,
	.probe		= sf_xgmac_probe,
	.remove		= sf_xgmac_remove,
	.ops		= &sf_xgmac_ops,
	.priv_auto	= sizeof(struct sf_xgmac_priv),
	.plat_auto	= sizeof(struct eth_pdata),
};

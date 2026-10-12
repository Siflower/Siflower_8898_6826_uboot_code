#include <asm/arch-siflower/eth.h>
#include <asm/io.h>
#include <common.h>
#include <dm.h>
#include <dm/device_compat.h>
#include <errno.h>
#include <linux/bitfield.h>
#include <linux/iopoll.h>
#include <miiphy.h>
#include <phy.h>
#include "sfxpcs.h"

#define ADDR_MASK	BIT(21)
#define DEV_MASK	GENMASK(20, 16)
#define REG_MASK	GENMASK(15, 0)

#define LOAD_SERDES_FW	0
#define SF_PCS_NUM_MAX	2

enum pcs_mode {
	PCS_DISABLED,
	PCS_QSGMII,
	PCS_SGMII,
	PCS_USXGMII
};

struct xpcs_mdio {
	phys_addr_t ioaddr;
	u32 pcs_mode[SF_PCS_NUM_MAX];
};

static int _xpcs_read(phys_addr_t ioaddr, int addr, int devad, int reg)
{
	ulong r;

	r = FIELD_PREP(REG_MASK, reg) | FIELD_PREP(ADDR_MASK, addr) |
	    FIELD_PREP(DEV_MASK, devad);
	r <<= 2;

	return readl(ioaddr + r);
}

static int xpcs_read(struct udevice *dev, int addr, int devad, int reg)
{
	struct xpcs_mdio *priv = dev_get_priv(dev);

	return _xpcs_read(priv->ioaddr, addr, devad, reg);
}

static void _xpcs_write(phys_addr_t ioaddr, int addr, int devad, int reg,
			u16 val)
{
	ulong r;

	r = FIELD_PREP(REG_MASK, reg) | FIELD_PREP(ADDR_MASK, addr) |
	    FIELD_PREP(DEV_MASK, devad);
	r <<= 2;

	writel(val, ioaddr + r);
}

static int xpcs_write(struct udevice *dev, int addr, int devad, int reg,
		      u16 val)
{
	struct xpcs_mdio *priv = dev_get_priv(dev);

	_xpcs_write(priv->ioaddr, addr, devad, reg, val);

	return 0;
}

static const struct mdio_ops xpcs_mdio_ops = {
	.read = xpcs_read,
	.write = xpcs_write,
};

#if LOAD_SERDES_FW
#include "dwc_e16mp.h"

static int xpcs_cr_write(phys_addr_t ioaddr, int addr, int devad, int reg,
			 u16 val)
{
	int timeout = 100000;

	_xpcs_write(ioaddr, addr, devad, VR_XS_PMA_SNPS_CR_ADDR, reg);
	_xpcs_write(ioaddr, addr, devad, VR_XS_PMA_SNPS_CR_DATA, val);
	_xpcs_write(ioaddr, addr, devad, VR_XS_PMA_SNPS_CR_CTRL,
		    VR_XS_PMA_SNPS_CR_CTRL_START_BUSY | VR_XS_PMA_SNPS_CR_CTRL_WR_RDN);

	while (_xpcs_read(ioaddr, addr, devad, VR_XS_PMA_SNPS_CR_CTRL) &
		VR_XS_PMA_SNPS_CR_CTRL_START_BUSY) {
		if (!--timeout)
			return -ETIMEDOUT;
	}

	return 0;
}

static int xpcs_serdes_load_fw(phys_addr_t ioaddr, int addr, int devad)
{
	for (ulong i = 0; i < ARRAY_SIZE(dwc_e16mp_fw); i++) {
		int ret = xpcs_cr_write(ioaddr, addr, devad, dwc_e16mp_fw[i][0],
					dwc_e16mp_fw[i][1]);
		if (ret)
			return ret;
	}

	return 0;
}
#endif

static int xpcs_serdes_poll_sram(phys_addr_t ioaddr, int addr, int devad)
{
	int timeout = 100000;

	while ((_xpcs_read(ioaddr, addr, devad, VR_XS_PMA_MP_12G_16G_25G_SRAM) &
		VR_XS_PMA_MP_12G_16G_25G_SRAM_INIT_DN) == 0) {
		if (!--timeout) {
			log_err("Timed out waiting for SerDes SRAM init\n");
			return -ETIMEDOUT;
		}
	}

	return 0;
}

static int xpcs_poll_reset(phys_addr_t ioaddr, int addr, int devad)
{
	int timeout = 100000;

	while (_xpcs_read(ioaddr, addr, devad, MDIO_CTRL1) & MDIO_CTRL1_RESET) {
		if (!--timeout) {
			log_err("Timed out waiting for reset\n");
			return -ETIMEDOUT;
		}
	}

	return 0;
}

static int xpcs_poll_pg(unsigned long base, int addr, int devad, u32 val)
{
	u32 timeout = 0;

	while (FIELD_GET(PSEQ_STATE,
				_xpcs_read(base, addr, devad, DW_VR_MII_DIG_STS)) != val) {
		if (timeout >= 100) {
			return -1;
		}
		timeout++;
		udelay(100);
	}
	return 0;
}

static int xpcs_qsgmii_init(struct xpcs_mdio *priv, int addr)
{
	u32 reg;
	int ret;

#ifdef CONFIG_SF21H8898_MPW0
	// Init SRAM
	ret = xpcs_serdes_poll_sram(priv->ioaddr, addr, MDIO_MMD_VEND2);
	if (ret)
		return ret;

#if LOAD_SERDES_FW
	ret = xpcs_serdes_load_fw(priv->ioaddr, addr, MDIO_MMD_VEND2);
	if (ret)
		return ret;
#endif

	_xpcs_write(priv->ioaddr, addr, MDIO_MMD_VEND2, VR_XS_PMA_MP_12G_16G_25G_SRAM,
		    VR_XS_PMA_MP_12G_16G_25G_SRAM_EXT_LD_DN);

	ret = xpcs_poll_reset(priv->ioaddr, addr, MDIO_MMD_VEND2);
	if (ret)
		return ret;

	// Enable repeat clock for USXGMII
	reg = _xpcs_read(priv->ioaddr, addr, MDIO_MMD_VEND2, VR_XS_PMA_MP_12G_16G_25G_REF_CLK_CTRL);
	reg |= VR_XS_PMA_MP_12G_16G_25G_REF_CLK_CTRL_REF_RPT_CLK_EN;
	_xpcs_write(priv->ioaddr, addr, MDIO_MMD_VEND2, VR_XS_PMA_MP_12G_16G_25G_REF_CLK_CTRL, reg);

	// Configure SerDes speed to 5.0GS/s
	_xpcs_write(priv->ioaddr, addr, MDIO_MMD_VEND2, VR_XS_PMA_MP_12G_16G_MPLLA_CTRL0, 0x20);
	_xpcs_write(priv->ioaddr, addr, MDIO_MMD_VEND2, VR_XS_PMA_MP_12G_16G_25G_VCO_CAL_LD0, 0x540);
	_xpcs_write(priv->ioaddr, addr, MDIO_MMD_VEND2, VR_XS_PMA_MP_16G_25G_VCO_CAL_REF0, 0x2a);
	_xpcs_write(priv->ioaddr, addr, MDIO_MMD_VEND2, VR_XS_PMA_MP_16G_25G_RX_GENCTRL4, 0x300);
	_xpcs_write(priv->ioaddr, addr, MDIO_MMD_VEND2, VR_XS_PMA_MP_16G_25G_RX_MISC_CTRL0, 0x4);
	_xpcs_write(priv->ioaddr, addr, MDIO_MMD_VEND2, VR_XS_PMA_MP_12G_16G_25G_TX_RATE_CTRL, 0x1);
	_xpcs_write(priv->ioaddr, addr, MDIO_MMD_VEND2, VR_XS_PMA_MP_12G_16G_25G_RX_RATE_CTRL, 0x1);
	_xpcs_write(priv->ioaddr, addr, MDIO_MMD_VEND2, VR_XS_PMA_MP_12G_16G_TX_GENCTRL2, 0x300);
	_xpcs_write(priv->ioaddr, addr, MDIO_MMD_VEND2, VR_XS_PMA_MP_12G_16G_RX_GENCTRL2, 0x300);
	_xpcs_write(priv->ioaddr, addr, MDIO_MMD_VEND2, VR_XS_PMA_MP_12G_16G_MPLLA_CTRL2, 0x200);
	_xpcs_write(priv->ioaddr, addr, MDIO_MMD_VEND2, VR_XS_PMA_MP_12G_16G_25G_TX_EQ_CTRL0, 0x2400);
	_xpcs_write(priv->ioaddr, addr, MDIO_MMD_VEND2, VR_XS_PMA_MP_12G_16G_25G_RX_GENCTRL1, 0xc00);
	// Enable QSGMII mode
	_xpcs_write(priv->ioaddr, addr, MDIO_MMD_VEND2, DW_VR_MII_AN_CTRL,
			FIELD_PREP(DW_VR_MII_PCS_MODE_MASK, DW_VR_MII_PCS_MODE_C37_QSGMII) | 0x1);
	_xpcs_write(priv->ioaddr, addr, MDIO_MMD_VEND2, DW_VR_MII_DBG_CTRL, BIT(6) | BIT(4));

	// Enable MAC speed auto switch & vendor reset
	reg = _xpcs_read(priv->ioaddr, addr, DW_QSGMII_MMD1, DW_VR_MII_DIG_CTRL1);
	reg |= DW_VR_MII_DIG_CTRL1_MAC_AUTO_SW;
	_xpcs_write(priv->ioaddr, addr, DW_QSGMII_MMD1, DW_VR_MII_DIG_CTRL1, reg);
	_xpcs_write(priv->ioaddr, addr, DW_QSGMII_MMD2, DW_VR_MII_DIG_CTRL1, reg);
	_xpcs_write(priv->ioaddr, addr, DW_QSGMII_MMD3, DW_VR_MII_DIG_CTRL1, reg);
	reg |= MDIO_CTRL1_RESET;
	_xpcs_write(priv->ioaddr, addr, MDIO_MMD_VEND2, DW_VR_MII_DIG_CTRL1, reg);

	ret = xpcs_poll_reset(priv->ioaddr, addr, MDIO_MMD_VEND2);
	if (ret)
		return ret;

	// Enable Clause 37 auto-negotiation
	reg = BMCR_ANENABLE | BMCR_SPEED1000 | BMCR_FULLDPLX;
	_xpcs_write(priv->ioaddr, addr, MDIO_MMD_VEND2, MDIO_CTRL1, reg);
	_xpcs_write(priv->ioaddr, addr, DW_QSGMII_MMD1, MDIO_CTRL1, reg);
	_xpcs_write(priv->ioaddr, addr, DW_QSGMII_MMD2, MDIO_CTRL1, reg);
	_xpcs_write(priv->ioaddr, addr, DW_QSGMII_MMD3, MDIO_CTRL1, reg);

	// Enable tranparent EEE, clk_eee_i = 100MHz
	_xpcs_write(priv->ioaddr, addr, MDIO_MMD_VEND2, DW_VR_MII_EEE_MCTRL0, 0x899f);
	_xpcs_write(priv->ioaddr, addr, MDIO_MMD_VEND2, DW_VR_MII_EEE_MCTRL1, DW_VR_MII_EEE_TRN_LPI);
#else
	_xpcs_write(priv->ioaddr, addr, MDIO_MMD_VEND2, MII_BMCR, BMCR_RESET);

    ret = xpcs_poll_reset(priv->ioaddr, 0, MDIO_MMD_VEND2);
    if (ret)
        return ret;

    reg = FIELD_PREP(DW_VR_MII_PCS_MODE_MASK, DW_VR_MII_PCS_MODE_C37_QSGMII);
    _xpcs_write(priv->ioaddr, addr, MDIO_MMD_VEND2, DW_VR_MII_AN_CTRL, reg);
    _xpcs_write(priv->ioaddr, addr, DW_QSGMII_MMD1, DW_VR_MII_AN_CTRL, reg);
    _xpcs_write(priv->ioaddr, addr, DW_QSGMII_MMD2, DW_VR_MII_AN_CTRL, reg);
    _xpcs_write(priv->ioaddr, addr, DW_QSGMII_MMD3, DW_VR_MII_AN_CTRL, reg);

    // 6G serdes init
    _xpcs_write(priv->ioaddr, addr, MDIO_MMD_VEND2, DW_VR_MII_MP_6G_MPLL_CTRL1, 0x28);
    reg = _xpcs_read(priv->ioaddr, addr, MDIO_MMD_VEND2, DW_VR_MII_MP_6G_MPLL_CTRL0);
    reg &= ~LANE_10BIT_SEL;
    _xpcs_write(priv->ioaddr, addr, MDIO_MMD_VEND2, DW_VR_MII_MP_6G_MPLL_CTRL0, reg);
    _xpcs_write(priv->ioaddr, addr, MDIO_MMD_VEND2, DW_VR_MII_MP_6G_MISC_CTRL1, 0x0);
    // Power-cycle the serdes
    _xpcs_write(priv->ioaddr, addr, MDIO_MMD_VEND2, MII_BMCR, BMCR_PDOWN);
    ret = xpcs_poll_pg(priv->ioaddr, addr, MDIO_MMD_VEND2, PSEQ_STATE_DOWN);
    if (ret)
        return ret;

    _xpcs_write(priv->ioaddr, addr, DW_QSGMII_MMD1, MII_BMCR, BMCR_FULLDPLX | BMCR_SPEED1000);
    _xpcs_write(priv->ioaddr, addr, DW_QSGMII_MMD2, MII_BMCR, BMCR_FULLDPLX | BMCR_SPEED1000);
    _xpcs_write(priv->ioaddr, addr, DW_QSGMII_MMD3, MII_BMCR, BMCR_FULLDPLX | BMCR_SPEED1000);
    _xpcs_write(priv->ioaddr, addr, MDIO_MMD_VEND2, MII_BMCR, BMCR_FULLDPLX | BMCR_SPEED1000);
    ret = xpcs_poll_pg(priv->ioaddr, addr, MDIO_MMD_VEND2, PSEQ_STATE_GOOD);
    if (ret)
        return ret;

    // Enable speed auto switch after c37 auto negotiation
    reg = _xpcs_read(priv->ioaddr, addr, MDIO_MMD_VEND2, DW_VR_MII_DIG_CTRL1);
    reg |= DW_VR_MII_DIG_CTRL1_MAC_AUTO_SW;
    _xpcs_write(priv->ioaddr, addr, MDIO_MMD_VEND2, DW_VR_MII_DIG_CTRL1, reg);
    _xpcs_write(priv->ioaddr, addr, DW_QSGMII_MMD1, DW_VR_MII_DIG_CTRL1, reg);
    _xpcs_write(priv->ioaddr, addr, DW_QSGMII_MMD2, DW_VR_MII_DIG_CTRL1, reg);
    _xpcs_write(priv->ioaddr, addr, DW_QSGMII_MMD3, DW_VR_MII_DIG_CTRL1, reg);

    // Enable c37 auto negotiation
    reg = BMCR_ANENABLE | BMCR_ANRESTART | BMCR_FULLDPLX | BMCR_SPEED1000;
    _xpcs_write(priv->ioaddr, addr, MDIO_MMD_VEND2, MII_BMCR, reg);
    _xpcs_write(priv->ioaddr, addr, DW_QSGMII_MMD1, MII_BMCR, reg);
    _xpcs_write(priv->ioaddr, addr, DW_QSGMII_MMD2, MII_BMCR, reg);
    _xpcs_write(priv->ioaddr, addr, DW_QSGMII_MMD3, MII_BMCR, reg);
#endif

	printf("End %s pcs_id:%d\n", __func__, addr);
	return 0;
}

static int xpcs_usxgmii_init(struct xpcs_mdio *priv, int addr)
{
	u32 reg;
	int ret;

	// Init SRAM
	ret = xpcs_serdes_poll_sram(priv->ioaddr, addr, MDIO_MMD_PMAPMD);
	if (ret)
		return ret;

#if LOAD_SERDES_FW
	ret = xpcs_serdes_load_fw(priv->ioaddr, addr, MDIO_MMD_PMAPMD);
	if (ret)
		return ret;
#endif

	_xpcs_write(priv->ioaddr, addr, MDIO_MMD_PMAPMD, VR_XS_PMA_MP_12G_16G_25G_SRAM,
		    VR_XS_PMA_MP_12G_16G_25G_SRAM_EXT_LD_DN);

	ret = xpcs_poll_reset(priv->ioaddr, addr, MDIO_MMD_PMAPMD);
	if (ret)
		return ret;

	// Enable USXGMII mode
	reg = _xpcs_read(priv->ioaddr, addr, MDIO_MMD_PCS, DW_VR_MII_DIG_CTRL1);
	reg |= DW_USXGMII_EN;
	_xpcs_write(priv->ioaddr, addr, MDIO_MMD_PCS, DW_VR_MII_DIG_CTRL1, reg);

	// Configure SerDes speed to 10.3125GS/s
	_xpcs_write(priv->ioaddr, addr, MDIO_MMD_PMAPMD, VR_XS_PMA_MP_12G_16G_MPLLA_CTRL0, 0x21);
	_xpcs_write(priv->ioaddr, addr, MDIO_MMD_PMAPMD, VR_XS_PMA_MP_16G_MPLLA_CTRL3, 0xa03e);
	_xpcs_write(priv->ioaddr, addr, MDIO_MMD_PMAPMD, VR_XS_PMA_MP_12G_16G_25G_VCO_CAL_LD0, 0x549);
	_xpcs_write(priv->ioaddr, addr, MDIO_MMD_PMAPMD, VR_XS_PMA_MP_16G_25G_VCO_CAL_REF0, 0x29);
	_xpcs_write(priv->ioaddr, addr, MDIO_MMD_PMAPMD, VR_XS_PMA_MP_16G_25G_RX_GENCTRL4, 0x0);
	_xpcs_write(priv->ioaddr, addr, MDIO_MMD_PMAPMD, VR_XS_PMA_MP_16G_25G_RX_MISC_CTRL0, 0x2);
	_xpcs_write(priv->ioaddr, addr, MDIO_MMD_PMAPMD, VR_XS_PMA_MP_12G_16G_25G_TX_RATE_CTRL, 0x0);
	_xpcs_write(priv->ioaddr, addr, MDIO_MMD_PMAPMD, VR_XS_PMA_MP_12G_16G_25G_RX_RATE_CTRL, 0x0);
	_xpcs_write(priv->ioaddr, addr, MDIO_MMD_PMAPMD, VR_XS_PMA_MP_12G_16G_TX_GENCTRL2, 0x300);
	_xpcs_write(priv->ioaddr, addr, MDIO_MMD_PMAPMD, VR_XS_PMA_MP_12G_16G_RX_GENCTRL2, 0x300);
	_xpcs_write(priv->ioaddr, addr, MDIO_MMD_PMAPMD, VR_XS_PMA_MP_12G_16G_MPLLA_CTRL2, 0x600);
	_xpcs_write(priv->ioaddr, addr, MDIO_MMD_PMAPMD, VR_XS_PMA_MP_16G_25G_RX_IQ_CTRL0, 0x300);
	_xpcs_write(priv->ioaddr, addr, MDIO_MMD_PMAPMD, VR_XS_PMA_MP_16G_25G_RX_EQ_CTRL0, 0x554a);
	_xpcs_write(priv->ioaddr, addr, MDIO_MMD_PCS, DW_VR_MII_DBG_CTRL, BIT(6) | BIT(4));

	// Enable MAC speed auto switch & vendor reset
	_xpcs_write(priv->ioaddr, addr, MDIO_MMD_VEND2, DW_VR_MII_AN_CTRL, 0x1);
	reg = _xpcs_read(priv->ioaddr, addr, MDIO_MMD_VEND2, DW_VR_MII_DIG_CTRL1);
	reg |= DW_VR_MII_DIG_CTRL1_MAC_AUTO_SW | MDIO_CTRL1_RESET;
	_xpcs_write(priv->ioaddr, addr, MDIO_MMD_VEND2, DW_VR_MII_DIG_CTRL1, reg);

	ret = xpcs_poll_reset(priv->ioaddr, addr, MDIO_MMD_VEND2);
	if (ret)
		return ret;

	// Enable Clause 37 auto-negotiation
	reg = BMCR_ANENABLE | DW_USXGMII_10000 | BMCR_FULLDPLX;
	_xpcs_write(priv->ioaddr, addr, MDIO_MMD_VEND2, MDIO_CTRL1, reg);

	// Enable tranparent EEE, clk_eee_i = 100MHz
	_xpcs_write(priv->ioaddr, addr, MDIO_MMD_PCS, DW_VR_MII_EEE_MCTRL0, 0x899f);
	_xpcs_write(priv->ioaddr, addr, MDIO_MMD_PCS, DW_VR_MII_EEE_MCTRL1, DW_VR_MII_EEE_TRN_LPI);
	printf("End %s pcs_id:%d\n", __func__, addr);
	return 0;
}

static int xpcs_sgmii_init(struct xpcs_mdio *priv, int addr)
{
	u32 reg;
	int ret;

	_xpcs_write(priv->ioaddr, addr, MDIO_MMD_VEND2, MII_BMCR, BMCR_RESET);

	ret = xpcs_poll_reset(priv->ioaddr, addr, MDIO_MMD_VEND2);
	if (ret)
		return ret;

	// 6G serdes init
	_xpcs_write(priv->ioaddr, addr, MDIO_MMD_VEND2, DW_VR_MII_MP_6G_MPLL_CTRL1, 0x32);
	_xpcs_write(priv->ioaddr, addr, MDIO_MMD_VEND2, DW_VR_MII_MP_6G_MISC_CTRL1, 0x5555);
	reg = _xpcs_read(priv->ioaddr, addr, MDIO_MMD_VEND2, DW_VR_MII_DIG_CTRL1);
	reg |= DW_VR_MII_DIG_CTRL1_EN_25G_MODE;
	_xpcs_write(priv->ioaddr, addr, MDIO_MMD_VEND2, DW_VR_MII_DIG_CTRL1, reg);

	// Power-cycle the serdes
	_xpcs_write(priv->ioaddr, addr, MDIO_MMD_VEND2, MII_BMCR, BMCR_PDOWN);
	ret = xpcs_poll_pg(priv->ioaddr, addr, MDIO_MMD_VEND2, PSEQ_STATE_DOWN);
	if (ret)
		return ret;

	_xpcs_write(priv->ioaddr, addr, MDIO_MMD_VEND2, MII_BMCR, BMCR_FULLDPLX | BMCR_SPEED1000);
	ret = xpcs_poll_pg(priv->ioaddr, addr, MDIO_MMD_VEND2, PSEQ_STATE_GOOD);
	if (ret)
		return ret;

	reg = BMCR_FULLDPLX | BMCR_SPEED1000;
	_xpcs_write(priv->ioaddr, addr, MDIO_MMD_VEND2, MII_BMCR, reg);

	printf("End %s pcs_id:%d\n", __func__, addr);
	return 0;
}

static int xpcs_mdio_probe(struct udevice *dev)
{
	struct xpcs_mdio *priv = dev_get_priv(dev);
	ofnode pcs_node;
	const char *node_name;
	bool pcs_enable;
	u32 pcs_id, pcs_mode;
	int ret;

	memset(priv, 0, sizeof(*priv));

	priv->ioaddr = dev_read_addr(dev);
	if (priv->ioaddr == FDT_ADDR_T_NONE)
		return -EINVAL;

	/* search pcs subnode */
	dev_for_each_subnode(pcs_node, dev)
	{
		node_name = ofnode_get_name(pcs_node);
		if (strncmp(node_name, "xpcs", 4))
			continue;

		pcs_enable = ofnode_read_bool(pcs_node, "enable");
		if (!pcs_enable)
			continue;

		ret = ofnode_read_u32(pcs_node, "reg", &pcs_id);
		if (ret || (pcs_id >= SF_PCS_NUM_MAX))
			return ret;

		ret = ofnode_read_u32(pcs_node, "mode", &pcs_mode);
		if (ret)
			return ret;

		priv->pcs_mode[pcs_id] = pcs_mode;
		debug("%s get pcs id:%u mode:%u\n", __func__, pcs_id, pcs_mode);
	}

#ifdef CONFIG_SF21H8898_MPW0
	/* deassert reset, note that bit 6 also controls DMA */
	setbits_32(0x0ce01888, 0xc0);

	/* enable clocks */
	writel(0x198, 0x0ce01864);
	writel(0x198, 0x0ce01868);

#else
	/* deassert reset, note that bit 6 also controls DMA */
	setbits_32(0x0ce01888, 0x60);
#endif

	for (pcs_id = 0; pcs_id < SF_PCS_NUM_MAX; pcs_id++) {
		switch (priv->pcs_mode[pcs_id]) {
		case PCS_QSGMII:
			ret = xpcs_qsgmii_init(priv, pcs_id);
			if (ret)
				dev_err(dev, "QSGMII PCS init failed id:%u ret:%d\n", pcs_id, ret);
			break;
		case PCS_SGMII:
			/* need invert phy rx clk in mpw1 sgmii */
			writel(0x601, (u32 *)0x0ce0186c + pcs_id);

			ret = xpcs_sgmii_init(priv, pcs_id);
			if (ret)
				dev_err(dev, "SGMII PCS init failed id:%u ret:%d\n", pcs_id, ret);
			break;
		case PCS_USXGMII:
			ret = xpcs_usxgmii_init(priv, pcs_id);
			if (ret)
				dev_err(dev, "USXGMII PCS init failed id:%u ret:%d\n", pcs_id, ret);
			break;
		}
	}

	return ret;
}

static const struct udevice_id xpcs_mdio_match[] = {
	{ .compatible = "siflower,sf21h8898-xpcs-mdio" },
	{},
};

U_BOOT_DRIVER(xpcs_mdio) = {
	.name           = "xpcs_mdio",
	.id             = UCLASS_MDIO,
	.of_match       = xpcs_mdio_match,
	.probe          = xpcs_mdio_probe,
	.ops            = &xpcs_mdio_ops,
	.priv_auto	  = sizeof(struct xpcs_mdio),
};

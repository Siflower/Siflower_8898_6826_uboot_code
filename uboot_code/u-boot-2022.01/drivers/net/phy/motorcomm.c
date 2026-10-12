// SPDX-License-Identifier: GPL-2.0+
/*
 * drivers/net/phy/motorcomm.c
 *
 * Driver for Motorcomm PHYs
 *
 * Author: yinghong.zhang<yinghong.zhang@motor-comm.com>
 *
 * Copyright (c) 2024 Motorcomm, Inc.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * Support : Motorcomm Phys:
 * Giga phys: yt8511, yt8521, yt8531, yt8543, yt8614, yt8618
 * 100/10M Phys: yt8510, yt8512, yt8522
 * Automotive 100M Phys: yt8010
 * Automotive 1000M Phys: yt8011
 */
#include <phy.h>
#include <linux/compat.h>
#include <malloc.h>

/* PS: below(#include <linux/delay.h>) will be updated to "#include <common.h>"
 * when uboot ver is 2017.1
 */
#include <linux/delay.h>
#include <net.h>

#include <version.h>

#undef U_BOOT_PHY_DRIVER_MACRO
#if defined(U_BOOT_VERSION_NUM) && defined(U_BOOT_VERSION_NUM_PATCH)
#if ((U_BOOT_VERSION_NUM * 10000 + U_BOOT_VERSION_NUM_PATCH) >= (2023 * 10000 + 7))
#define U_BOOT_PHY_DRIVER_MACRO
#endif
#endif

#define YT_UBOOT_MAJOR			2
#define YT_UBOOT_MINOR			2
#define YT_UBOOT_SUBVERSION		41626
#define YT_UBOOT_VERSIONID		"2.2.41626"

#define PHY_ID_YT8010			0x00000309
#define PHY_ID_YT8010AS			0x4f51eb19
#define PHY_ID_YT8011			0x4f51eb01
#define PHY_ID_YT8510			0x00000109
#define PHY_ID_YT8511			0x0000010a
#define PHY_ID_YT8512			0x00000118
#define PHY_ID_YT8512B			0x00000128
#define PHY_ID_YT8522			0x4f51e928
#define PHY_ID_YT8521S			0x0000011a
#define PHY_ID_YT8531			0x4f51e91b
/* YT8543 phy driver disable(default) */
/* #define YTPHY_YT8543_ENABLE */
#ifdef YTPHY_YT8543_ENABLE
#define PHY_ID_YT8543			0x0008011b
#endif
#define PHY_ID_YT8531S			0x4f51e91a
#define PHY_ID_YT8614			0x4F51E899
#define PHY_ID_YT8618			0x4f51e889
#define PHY_ID_YT8821			0x4f51ea19
#define PHY_ID_MASK			0xffffffff

/* for YT8531 package A xtal init config */
#define YT8531A_XTAL_INIT		0
/* some GMAC need clock input from PHY, for eg., 125M,
 * please enable this macro
 * by degault, it is set to 0
 * NOTE: this macro will need macro SYS_WAKEUP_BASED_ON_ETH_PKT to set to 1
 */
#define GMAC_CLOCK_INPUT_NEEDED		0
#define YT_861X_AB_VER			0
#if (YT_861X_AB_VER)
static int yt8614_get_port_from_phydev(struct phy_device *phydev);
#endif

#define REG_PHY_SPEC_STATUS		0x11

#define REG_DEBUG_ADDR_OFFSET		0x1e
#define REG_DEBUG_DATA			0x1f
#define YT_SPEC_STATUS			0x11
#define YT_UTP_INTR_REG			0x12
#define YT_SOFT_RESET			0x8000
#define YT_SPEED_MODE			0xc000
#define YT_SPEED_MODE_BIT		14
#define YT_DUPLEX			0x2000
#define YT_DUPLEX_BIT			13
#define YT_LINK_STATUS_BIT		10
#define YT_REG_SPACE_UTP		0
#define YT_REG_SPACE_FIBER		2

#define YT8512_CLOCK_INIT_NEED		0
#define YT8512_EXTREG_AFE_PLL		0x50
#define YT8512_EXTREG_EXTEND_COMBO	0x4000
#define YT8512_EXTREG_LED0		0x40c0
#define YT8512_EXTREG_LED1		0x40c3
#define YT8512_EXTREG_SLEEP_CONTROL1	0x2027
#define YT8512_CONFIG_PLL_REFCLK_SEL_EN	0x0040
#define YT8512_CONTROL1_RMII_EN		0x0001
#define YT8512_LED0_ACT_BLK_IND		0x1000
#define YT8512_LED0_DIS_LED_AN_TRY	0x0001
#define YT8512_LED0_BT_BLK_EN		0x0002
#define YT8512_LED0_HT_BLK_EN		0x0004
#define YT8512_LED0_COL_BLK_EN		0x0008
#define YT8512_LED0_BT_ON_EN		0x0010
#define YT8512_LED1_BT_ON_EN		0x0010
#define YT8512_LED1_TXACT_BLK_EN	0x0100
#define YT8512_LED1_RXACT_BLK_EN	0x0200
#define YT8512_10BT_DEBUG_LPBKS		0x200A
#define YT8522_TX_CLK_DELAY		0x4210
#define YT8522_ANAGLOG_IF_CTRL		0x4008
#define YT8522_DAC_CTRL			0x2057
#define YT8522_INTERPOLATOR_FILTER_1	0x14
#define YT8522_INTERPOLATOR_FILTER_2	0x15
#define YT8522_EXTENDED_COMBO_CTRL_1	0x4000
#define YT8522_TX_DELAY_CONTROL		0x19
#define YT8522_EXTENDED_PAD_CONTROL	0x4001
#define YT8512_EN_SLEEP_SW_BIT		15
#define YT8521_EXTREG_SLEEP_CONTROL1	0x27
#define YT8521_EN_SLEEP_SW_BIT		15
#define REG_MII_MMD_CTRL		0x0D
#define REG_MII_MMD_DATA		0x0E

#define YT8614_REG_SPACE_UTP	0
#define YT8614_REG_SPACE_QSGMII	2
#define YT8614_REG_SPACE_SGMII	3

/* to enable system WOL feature of phy, please define this macro to 1
 * otherwise, define it to 0.
 */
#define YT_WOL_FEATURE_ENABLE		0
/* WOL Feature Event Interrupt Enable */
#define YT_WOL_FEATURE_INTR		BIT(6)

/* Magic Packet MAC address registers */
#define YT_WOL_FEATURE_MACADDR2_4_MAGIC_PACKET	0xa007
#define YT_WOL_FEATURE_MACADDR1_4_MAGIC_PACKET	0xa008
#define YT_WOL_FEATURE_MACADDR0_4_MAGIC_PACKET	0xa009

#define YT_WOL_FEATURE_REG_CFG		0xa00a
/* WOL TYPE Config */
#define YT_WOL_FEATURE_TYPE_CFG		BIT(0)
/* WOL Enable Config */
#define YT_WOL_FEATURE_ENABLE_CFG	BIT(3)
/* WOL Event Interrupt Enable Config */
#define YT_WOL_FEATURE_INTR_SEL_CFG	BIT(6)
/* WOL Pulse Width Config */
#define YT_WOL_FEATURE_WIDTH1_CFG	BIT(1)
/* WOL Pulse Width Config */
#define YT_WOL_FEATURE_WIDTH2_CFG	BIT(2)

enum yt_wol_feature_trigger_type_e {
	YT_WOL_FEATURE_PULSE_TRIGGER,
	YT_WOL_FEATURE_LEVEL_TRIGGER,
	YT_WOL_FEATURE_TRIGGER_TYPE_MAX
};

enum yt_wol_feature_pulse_width_e {
	YT_WOL_FEATURE_672MS_PULSE_WIDTH,
	YT_WOL_FEATURE_336MS_PULSE_WIDTH,
	YT_WOL_FEATURE_168MS_PULSE_WIDTH,
	YT_WOL_FEATURE_84MS_PULSE_WIDTH,
	YT_WOL_FEATURE_PULSE_WIDTH_MAX
};

struct yt_wol_feature_cfg {
	bool enable;
	int type;
	int width;
};

/* polling mode */
#define PHY_MODE_FIBER		1	/* fiber mode only */
#define PHY_MODE_UTP		2	/* utp mode only */
#define PHY_MODE_POLL		3	/* fiber and utp, poll mode */

#define msleep(n)		udelay(n * 1000)

struct yt8xxx_priv {
	int strap_polling;
	int chip_mode;
};

static int ytphy_read_ext(struct phy_device *phydev, u32 regnum)
{
	int ret;
	int val;

	ret = phy_write(phydev, MDIO_DEVAD_NONE, REG_DEBUG_ADDR_OFFSET, regnum);
	if (ret < 0)
		return ret;

	val = phy_read(phydev, MDIO_DEVAD_NONE, REG_DEBUG_DATA);

	return val;
}

static int ytphy_write_ext(struct phy_device *phydev, u32 regnum, u16 val)
{
	int ret;

	ret = phy_write(phydev, MDIO_DEVAD_NONE, REG_DEBUG_ADDR_OFFSET, regnum);
	if (ret < 0)
		return ret;

	ret = phy_write(phydev, MDIO_DEVAD_NONE, REG_DEBUG_DATA, val);

	return ret;
}

__attribute__((unused)) static int ytphy_read_mmd(struct phy_device* phydev, u16 device, u16 reg)
{
	int val;
	int ret;

	ret = phy_write(phydev, MDIO_DEVAD_NONE, REG_MII_MMD_CTRL, device);
	if (ret < 0)
		return ret;

	ret = phy_write(phydev, MDIO_DEVAD_NONE, REG_MII_MMD_DATA, reg);
	if (ret < 0)
		return ret;

	ret = phy_write(phydev, MDIO_DEVAD_NONE, REG_MII_MMD_CTRL,
			device | 0x4000);
	if (ret < 0)
		return ret;

	val = phy_read(phydev, MDIO_DEVAD_NONE, REG_MII_MMD_DATA);

	return val;
}

__attribute__((unused)) static int ytphy_write_mmd(struct phy_device* phydev,
						   u16 device, u16 reg,
						   u16 value)
{
	int ret = 0;

	ret = phy_write(phydev, MDIO_DEVAD_NONE, REG_MII_MMD_CTRL, device);
	if (ret < 0)
		return ret;

	ret = phy_write(phydev, MDIO_DEVAD_NONE, REG_MII_MMD_DATA, reg);
	if (ret < 0)
		return ret;

	ret = phy_write(phydev, MDIO_DEVAD_NONE, REG_MII_MMD_CTRL,
			device | 0x4000);
	if (ret < 0)
		return ret;

	ret = phy_write(phydev, MDIO_DEVAD_NONE, REG_MII_MMD_DATA, value);

	return ret;
}

static int ytxxxx_soft_reset(struct phy_device *phydev)
{
	int ret, val;

	val = ytphy_read_ext(phydev, 0xa001);
	ytphy_write_ext(phydev, 0xa001, (val & ~0x8000));

	ret = ytphy_write_ext(phydev, 0xa000, 0);

	return ret;
}

static int ytphy_soft_reset(struct phy_device *phydev)
{
	int ret = 0, val = 0;

	val = phy_read(phydev, MDIO_DEVAD_NONE, MII_BMCR);
	if (val < 0)
		return val;

	ret = phy_write(phydev, MDIO_DEVAD_NONE, MII_BMCR, val | BMCR_RESET);
	if (ret < 0)
		return ret;

	return ret;
}

#if YT8512_CLOCK_INIT_NEED
static int yt8512_clk_init(struct phy_device *phydev)
{
	int ret;
	int val;

	val = ytphy_read_ext(phydev, YT8512_EXTREG_AFE_PLL);
	if (val < 0)
		return val;

	val |= YT8512_CONFIG_PLL_REFCLK_SEL_EN;

	ret = ytphy_write_ext(phydev, YT8512_EXTREG_AFE_PLL, val);
	if (ret < 0)
		return ret;

	val = ytphy_read_ext(phydev, YT8512_EXTREG_EXTEND_COMBO);
	if (val < 0)
		return val;

	val |= YT8512_CONTROL1_RMII_EN;

	ret = ytphy_write_ext(phydev, YT8512_EXTREG_EXTEND_COMBO, val);
	if (ret < 0)
		return ret;

	val = phy_read(phydev, MDIO_DEVAD_NONE, MII_BMCR);
	if (val < 0)
		return val;

	val |= YT_SOFT_RESET;
	ret = phy_write(phydev, MDIO_DEVAD_NONE, MII_BMCR, val);

	return ret;
}
#endif

static int yt8512_led_init(struct phy_device *phydev)
{
	int mask;
	int ret;
	int val;

	val = ytphy_read_ext(phydev, YT8512_EXTREG_LED0);
	if (val < 0)
		return val;

	val |= YT8512_LED0_ACT_BLK_IND;

	mask = YT8512_LED0_DIS_LED_AN_TRY | YT8512_LED0_BT_BLK_EN |
	YT8512_LED0_HT_BLK_EN | YT8512_LED0_COL_BLK_EN |
	YT8512_LED0_BT_ON_EN;
	val &= ~mask;

	ret = ytphy_write_ext(phydev, YT8512_EXTREG_LED0, val);
	if (ret < 0)
		return ret;

	val = ytphy_read_ext(phydev, YT8512_EXTREG_LED1);
	if (val < 0)
		return val;

	val |= YT8512_LED1_BT_ON_EN;

	mask = YT8512_LED1_TXACT_BLK_EN | YT8512_LED1_RXACT_BLK_EN;
	val &= ~mask;

	ret = ytphy_write_ext(phydev, YT8512_LED1_BT_ON_EN, val);

	return ret;
}

#if (YT8531A_XTAL_INIT)
static int yt8531a_xtal_init(struct phy_device *phydev)
{
	int ret = 0;
	int val = 0;

	udelay(50000);	/* delay 50ms */

	do {
		ret = ytphy_write_ext(phydev, 0xa012, 0x88);
		if (ret < 0)
			return ret;

		udelay(100000);	/* delay 100ms */

		val = ytphy_read_ext(phydev, 0xa012);
		if (val < 0)
			return val;
	} while (val != 0x88);

	ret = ytphy_write_ext(phydev, 0xa012, 0xc8);
	if (ret < 0)
		return ret;

	return ret;
}
#endif

#if (YT_WOL_FEATURE_ENABLE)
static int yt_switch_reg_space(struct phy_device *phydev, int space)
{
	int ret;

	if (space == YT_REG_SPACE_UTP)
		ret = ytphy_write_ext(phydev, 0xa000, 0);
	else
		ret = ytphy_write_ext(phydev, 0xa000, 2);

	return ret;
}

static int yt_wol_feature_enable_cfg(struct phy_device *phydev,
				     struct yt_wol_feature_cfg wol_cfg)
{
	int ret = 0;
	int val = 0;

	val = ytphy_read_ext(phydev, YT_WOL_FEATURE_REG_CFG);
	if (val < 0)
		return val;

	if (wol_cfg.enable) {
		val |= YT_WOL_FEATURE_ENABLE_CFG;

		if (wol_cfg.type == YT_WOL_FEATURE_LEVEL_TRIGGER) {
			val &= ~YT_WOL_FEATURE_TYPE_CFG;
			val &= ~YT_WOL_FEATURE_INTR_SEL_CFG;
		} else if (wol_cfg.type == YT_WOL_FEATURE_PULSE_TRIGGER) {
			val |= YT_WOL_FEATURE_TYPE_CFG;
			val |= YT_WOL_FEATURE_INTR_SEL_CFG;

			if (wol_cfg.width == YT_WOL_FEATURE_84MS_PULSE_WIDTH) {
				val &= ~YT_WOL_FEATURE_WIDTH1_CFG;
				val &= ~YT_WOL_FEATURE_WIDTH2_CFG;
			} else if (wol_cfg.width == YT_WOL_FEATURE_168MS_PULSE_WIDTH) {
				val |= YT_WOL_FEATURE_WIDTH1_CFG;
				val &= ~YT_WOL_FEATURE_WIDTH2_CFG;
			} else if (wol_cfg.width == YT_WOL_FEATURE_336MS_PULSE_WIDTH) {
				val &= ~YT_WOL_FEATURE_WIDTH1_CFG;
				val |= YT_WOL_FEATURE_WIDTH2_CFG;
			} else if (wol_cfg.width == YT_WOL_FEATURE_672MS_PULSE_WIDTH) {
				val |= YT_WOL_FEATURE_WIDTH1_CFG;
				val |= YT_WOL_FEATURE_WIDTH2_CFG;
			}
		}
	} else {
		val &= ~YT_WOL_FEATURE_ENABLE_CFG;
		val &= ~YT_WOL_FEATURE_INTR_SEL_CFG;
	}

	ret = ytphy_write_ext(phydev, YT_WOL_FEATURE_REG_CFG, val);
	if (ret < 0)
		return ret;

	return 0;
}

static int yt_wol_feature_set(struct phy_device *phydev,
			      struct ethtool_wolinfo *wol)
{
	/* u-boot ver < v2023.04(not included)
	 * struct phy_device {
	 *	...
	 * 	#ifdef CONFIG_DM_ETH
	 * 		struct udevice *dev;
	 * 		ofnode node;
	 * 	#else
	 * 		struct eth_device *dev;
	 * 	#endif
	 *	...
	 * };
	 * u-boot ver >= v2023.04(included)
	 * struct phy_device {
	 *	...
	 * 		struct udevice *dev;
	 *	...
	 * };
	 * -------------------------------------
	 * u-boot-2021.04
	 * #define U_BOOT_VERSION_NUM 2021
	 * #define U_BOOT_VERSION_NUM_PATCH 4
	 * -------------------------------------
	 * u-boot-2021.07
	 * #define U_BOOT_VERSION_NUM 2021
	 * #define U_BOOT_VERSION_NUM_PATCH 7
	 * -------------------------------------
	 * u-boot-2022.01-rc1
	 * #define U_BOOT_VERSION_NUM 2022
	 * #define U_BOOT_VERSION_NUM_PATCH 1
	 * -------------------------------------
	 * u-boot-2023.04
	 * #define U_BOOT_VERSION_NUM 2023
	 * #define U_BOOT_VERSION_NUM_PATCH 4
	 * -------------------------------------
	 * u-boot-2023.07-rc1
	 * #define U_BOOT_VERSION_NUM 2023
	 * #define U_BOOT_VERSION_NUM_PATCH 7
	 * -------------------------------------
	 * u-boot-2024.10-rc1
	 * #define U_BOOT_VERSION_NUM 2024
	 * #define U_BOOT_VERSION_NUM_PATCH 10
	 * -------------------------------------
	 */
	/* if defined CONFIG_DM_ETH || u-boot ver >= v2023.04 ==> struct udevice */
#if defined(CONFIG_DM_ETH) || (defined(U_BOOT_VERSION_NUM) && defined(U_BOOT_VERSION_NUM_PATCH) && ((U_BOOT_VERSION_NUM * 10000 + U_BOOT_VERSION_NUM_PATCH) >= (2023 * 10000 + 4)))
	struct udevice *dev = phydev->dev;
	struct eth_pdata *pdata = dev_get_plat(dev);
	u8 *hwaddr = pdata->enetaddr;
#else
	struct eth_device *p_attached_dev = phydev->dev;
	u8 *hwaddr = p_attached_dev->enetaddr;
#endif
	struct yt_wol_feature_cfg wol_cfg;
	int ret, curr_reg_space, val;

	memset(&wol_cfg, 0, sizeof(struct yt_wol_feature_cfg));
	curr_reg_space = ytphy_read_ext(phydev, 0xa000);
	if (curr_reg_space < 0)
		return curr_reg_space;

	/* Switch to phy UTP page */
	ret = yt_switch_reg_space(phydev, YT_REG_SPACE_UTP);
	if (ret < 0)
		return ret;

	if (wol->wolopts & WAKE_MAGIC) {
		/* Enable the WOL feature interrupt */
		val = phy_read(phydev, MDIO_DEVAD_NONE, YT_UTP_INTR_REG);
		val |= YT_WOL_FEATURE_INTR;
		ret = phy_write(phydev, MDIO_DEVAD_NONE, YT_UTP_INTR_REG, val);
		if (ret < 0)
			return ret;

		/* Set the WOL feature config */
		wol_cfg.enable = true;
		wol_cfg.type = YT_WOL_FEATURE_PULSE_TRIGGER;
		wol_cfg.width = YT_WOL_FEATURE_672MS_PULSE_WIDTH;
		ret = yt_wol_feature_enable_cfg(phydev, wol_cfg);
		if (ret < 0)
			return ret;

		/* Store the device address for the magic packet */
		ret = ytphy_write_ext(phydev,
				      YT_WOL_FEATURE_MACADDR2_4_MAGIC_PACKET,
				      ((hwaddr[0] << 8) | hwaddr[1]));
		if (ret < 0)
			return ret;
		ret = ytphy_write_ext(phydev,
				      YT_WOL_FEATURE_MACADDR1_4_MAGIC_PACKET,
				      ((hwaddr[2] << 8) | hwaddr[3]));
		if (ret < 0)
			return ret;
		ret = ytphy_write_ext(phydev,
				      YT_WOL_FEATURE_MACADDR0_4_MAGIC_PACKET,
				      ((hwaddr[4] << 8) | hwaddr[5]));
		if (ret < 0)
			return ret;
	} else {
		wol_cfg.enable = false;
		wol_cfg.type = YT_WOL_FEATURE_TRIGGER_TYPE_MAX;
		wol_cfg.width = YT_WOL_FEATURE_PULSE_WIDTH_MAX;
		ret = yt_wol_feature_enable_cfg(phydev, wol_cfg);
		if (ret < 0)
			return ret;
	}

	/* Recover to previous register space page */
	ret = yt_switch_reg_space(phydev, curr_reg_space);
	if (ret < 0)
		return ret;

	return 0;
}
#endif	/*(YT_WOL_FEATURE_ENABLE)*/

static int yt_parse_status(struct phy_device *phydev)
{
	int speed, speed_mode, duplex;
	int val;

	val = phy_read(phydev, MDIO_DEVAD_NONE, YT_SPEC_STATUS);
	if (val < 0)
		return val;

	duplex = (val & YT_DUPLEX) >> YT_DUPLEX_BIT;
	speed_mode = (val & YT_SPEED_MODE) >> YT_SPEED_MODE_BIT;
	switch (speed_mode) {
	case 2:
		speed = SPEED_1000;
		break;
	case 1:
		speed = SPEED_100;
		break;
	default:
		speed = SPEED_10;
		break;
	}

	phydev->speed = speed;
	phydev->duplex = duplex;

	val = phy_read(phydev, MDIO_DEVAD_NONE, MII_LPA);
	if (val < 0)
		return val;

	phydev->pause = val & LPA_PAUSE_CAP;
	phydev->asym_pause = val & LPA_PAUSE_ASYM;

	return 0;
}

static int yt8821_parse_status(struct phy_device *phydev)
{
	int speed_mode_bit15_14, speed_mode_bit9;
	int speed, speed_mode, duplex;
	int val;

	val = phy_read(phydev, MDIO_DEVAD_NONE, YT_SPEC_STATUS);
	if (val < 0)
		return val;

	duplex = (val & YT_DUPLEX) >> YT_DUPLEX_BIT;

	/* Bit9-Bit15-Bit14 speed mode 100---2.5G; 010---1000M;
	 * 001---100M; 000---10M
	 */
	speed_mode_bit15_14 = (val & YT_SPEED_MODE) >> YT_SPEED_MODE_BIT;
	speed_mode_bit9 = (val & BIT(9)) >> 9;
	speed_mode = (speed_mode_bit9 << 2) | speed_mode_bit15_14;

	switch (speed_mode) {
	case 4:
		speed = SPEED_2500;
		break;
	case 2:
		speed = SPEED_1000;
		break;
	case 1:
		speed = SPEED_100;
		break;
	default:
		speed = SPEED_10;
		break;
	}

	phydev->speed = speed;
	phydev->duplex = duplex;

	val = phy_read(phydev, MDIO_DEVAD_NONE, MII_LPA);
	if (val < 0)
		return val;

	phydev->pause = val & LPA_PAUSE_CAP;
	phydev->asym_pause = val & LPA_PAUSE_ASYM;

	return 0;
}

static int yt_startup(struct phy_device *phydev)
{
	msleep(1000);
	genphy_update_link(phydev);
	yt_parse_status(phydev);

	return 0;
}

static int yt8010_config(struct phy_device *phydev)
{
	int val;

	phydev->autoneg = AUTONEG_DISABLE;

	ytphy_write_ext(phydev, 0x1023, 0xfc00);
	ytphy_write_ext(phydev, 0x101d, 0x12c0);
	val = ytphy_read_ext(phydev, 0x1000);
	val &= ~(1 << 7);
	ytphy_write_ext(phydev, 0x1000, val);
	ytphy_write_ext(phydev, 0x101d, 0x12c0);
	ytphy_write_ext(phydev, 0x101e, 0x1900);
	ytphy_write_ext(phydev, 0x101f, 0x1900);
	ytphy_write_ext(phydev, 0x4083, 0x4327);
	ytphy_write_ext(phydev, 0x4082, 0xc20);
	ytphy_soft_reset(phydev);

	return 0;
}

int yt8010AS_soft_reset(struct phy_device *phydev)
{
	int ret;

	/* sgmii */
	ytphy_write_ext(phydev, 0xe, 1);
	ret = ytphy_soft_reset(phydev);
	if (ret < 0) {
		ytphy_write_ext(phydev, 0xe, 0);
		return ret;
	}

	/* utp */
	ytphy_write_ext(phydev, 0xe, 0);
	ret = ytphy_soft_reset(phydev);
	if (ret < 0)
		return ret;

	return 0;
}

static int yt8010AS_config(struct phy_device *phydev)
{
	phydev->autoneg = AUTONEG_DISABLE;

	ytphy_write_ext(phydev, 0x1009, 0x0);

	yt8010AS_soft_reset(phydev);

	return 0;
}

static int yt8010_startup(struct phy_device *phydev)
{
	msleep(1000);

	genphy_update_link(phydev);

	phydev->speed = SPEED_100;
	phydev->duplex = DUPLEX_FULL;

	return 0;
}

static int yt8011_soft_reset(struct phy_device *phydev)
{
	struct yt8xxx_priv *priv = phydev->priv;

	/* utp */
	ytphy_write_ext(phydev, 0x9000, 0x0);
	ytphy_soft_reset(phydev);

	if (priv->chip_mode) {	/* sgmii */
		ytphy_write_ext(phydev, 0x9000, 0x8000);
		ytphy_soft_reset(phydev);

		/* restore utp space */
		ytphy_write_ext(phydev, 0x9000, 0x0);
	}

	return 0;
}

static int yt8011_probe(struct phy_device *phydev)
{
	struct yt8xxx_priv *yt8011;
	int chip_config;

	if (!phydev->priv) {
		yt8011 = kzalloc(sizeof(*yt8011), GFP_KERNEL);
		if (!yt8011)
			return -ENOMEM;	/* ref: net/phy/ti.c */

		phydev->priv = yt8011;

		/* ext reg 0x9030 bit0
		 * 0 = chip works in RGMII mode; 1 = chip works in SGMII mode
		 */
		chip_config = ytphy_read_ext(phydev, 0x9030);
		yt8011->chip_mode = chip_config & 0x1;
	} else {
		yt8011 = (struct yt8xxx_priv *)phydev->priv;
	}

	return 0;
}

/* #define YT8011_RGMII_DVDDIO_3V3 */
/* #define YT8011_RGMII_DVDDIO_2V5 */
/* #define YT8011_RGMII_DVDDIO_1V8 */
static int yt8011_config(struct phy_device *phydev)
{
	struct yt8xxx_priv *priv = phydev->priv;

	phydev->autoneg = AUTONEG_DISABLE;

	/* UTP */
	ytphy_write_ext(phydev, 0x9000, 0x0);

	ytphy_write_ext(phydev, 0x1008, 0x2119);
	ytphy_write_ext(phydev, 0x1092, 0x712);
	ytphy_write_ext(phydev, 0x90bc, 0x6661);
	ytphy_write_ext(phydev, 0x90b9, 0x620b);
	ytphy_write_ext(phydev, 0x2001, 0x6418);
	ytphy_write_ext(phydev, 0x1019, 0x3712);
	ytphy_write_ext(phydev, 0x101a, 0x3713);
	ytphy_write_ext(phydev, 0x2015, 0x1012);
	ytphy_write_ext(phydev, 0x2005, 0x810);
	ytphy_write_ext(phydev, 0x2013, 0xff06);
	ytphy_write_ext(phydev, 0x1053, 0xf);
	ytphy_write_ext(phydev, 0x105e, 0xa46c);
	ytphy_write_ext(phydev, 0x1088, 0x002b);
	ytphy_write_ext(phydev, 0x1088, 0x002b);
	ytphy_write_ext(phydev, 0x1088, 0xb);
	ytphy_write_ext(phydev, 0x3008, 0x143);
	ytphy_write_ext(phydev, 0x3009, 0x1918);
	ytphy_write_ext(phydev, 0x9095, 0x1a1a);
	ytphy_write_ext(phydev, 0x9096, 0x1a10);
	ytphy_write_ext(phydev, 0x9097, 0x101a);
	ytphy_write_ext(phydev, 0x9098, 0x01ff);

	if (!(priv->chip_mode)) {	/* rgmii config */
#if defined (YT8011_RGMII_DVDDIO_3V3)
		ytphy_write_ext(phydev, 0x9000, 0x8000);
		ytphy_write_ext(phydev, 0x0062, 0x0000);
		ytphy_write_ext(phydev, 0x9000, 0x0000);
		ytphy_write_ext(phydev, 0x9031, 0xb200);
		ytphy_write_ext(phydev, 0x903b, 0x0040);
		ytphy_write_ext(phydev, 0x903e, 0x3b3b);
		ytphy_write_ext(phydev, 0x903c, 0xf);
		ytphy_write_ext(phydev, 0x903d, 0x1000);
		ytphy_write_ext(phydev, 0x9038, 0x0000);
#elif defined (YT8011_RGMII_DVDDIO_2V5)
		ytphy_write_ext(phydev, 0x9000, 0x8000);
		ytphy_write_ext(phydev, 0x0062, 0x0000);
		ytphy_write_ext(phydev, 0x9000, 0x0000);
		ytphy_write_ext(phydev, 0x9031, 0xb200);
		ytphy_write_ext(phydev, 0x9111, 0x5);
		ytphy_write_ext(phydev, 0x9114, 0x3939);
		ytphy_write_ext(phydev, 0x9112, 0xf);
		ytphy_write_ext(phydev, 0x9110, 0x0);
		ytphy_write_ext(phydev, 0x9113, 0x10);
		ytphy_write_ext(phydev, 0x903d, 0x2);
#elif defined (YT8011_RGMII_DVDDIO_1V8)
		ytphy_write_ext(phydev, 0x9000, 0x8000);
		ytphy_write_ext(phydev, 0x0062, 0x0000);
		ytphy_write_ext(phydev, 0x9000, 0x0000);
		ytphy_write_ext(phydev, 0x9031, 0xb200);
		ytphy_write_ext(phydev, 0x9116, 0x6);
		ytphy_write_ext(phydev, 0x9119, 0x3939);
		ytphy_write_ext(phydev, 0x9117, 0xf);
		ytphy_write_ext(phydev, 0x9115, 0x0);
		ytphy_write_ext(phydev, 0x9118, 0x20);
		ytphy_write_ext(phydev, 0x903d, 0x3);
#endif
	}

	yt8011_soft_reset(phydev);

	return 0;
}

static int yt8011_startup(struct phy_device *phydev)
{
	msleep(1000);

	genphy_update_link(phydev);

	phydev->speed = SPEED_1000;
	phydev->duplex = DUPLEX_FULL;

	return 0;
}

static int yt8510_config(struct phy_device *phydev)
{
	ytphy_soft_reset(phydev);

	return 0;
}


static int yt8511_config(struct phy_device *phydev)
{
	genphy_config_aneg(phydev);

	ytphy_soft_reset(phydev);

	return 0;
}

static int yt8512_probe(struct phy_device *phydev)
{
	struct yt8xxx_priv *yt8512;
	int chip_config;

	if (!phydev->priv) {
		yt8512 = kzalloc(sizeof(*yt8512), GFP_KERNEL);
		if (!yt8512)
			return -ENOMEM;	/* ref: net/phy/ti.c */

		phydev->priv = yt8512;
		chip_config = ytphy_read_ext(phydev,
					     YT8512_EXTREG_EXTEND_COMBO);
		yt8512->chip_mode = (chip_config & (BIT(1) | BIT(0)));
	} else {
		yt8512 = (struct yt8xxx_priv *)phydev->priv;
	}

	return 0;
}

static int yt8512_config(struct phy_device *phydev)
{
	struct yt8xxx_priv *priv = phydev->priv;
	int ret = 0, val = 0;

	val = ytphy_read_ext(phydev, YT8512_10BT_DEBUG_LPBKS);
	if (val < 0)
		return val;

	val &= ~BIT(10);
	ret = ytphy_write_ext(phydev, YT8512_10BT_DEBUG_LPBKS, val);
	if (ret < 0)
		return ret;

	if (!(priv->chip_mode)) {	/* MII mode */
		val &= ~BIT(15);
		ret = ytphy_write_ext(phydev, YT8512_10BT_DEBUG_LPBKS, val);
		if (ret < 0)
			return ret;
	}

#if YT8512_CLOCK_INIT_NEED
	ret = yt8512_clk_init(phydev);
	if (ret < 0)
		return ret;
#endif

	ret = yt8512_led_init(phydev);

	/* disable auto sleep */
	val = ytphy_read_ext(phydev, YT8512_EXTREG_SLEEP_CONTROL1);
	if (val < 0)
		return val;

	val &= (~BIT(YT8512_EN_SLEEP_SW_BIT));

	ret = ytphy_write_ext(phydev, YT8512_EXTREG_SLEEP_CONTROL1, val);
	if (ret < 0)
		return ret;

	genphy_config_aneg(phydev);

	ytphy_soft_reset(phydev);

	return 0;
}

static int yt8522_probe(struct phy_device *phydev)
{
	struct yt8xxx_priv *yt8522;
	int chip_config;

	if (!phydev->priv) {
		yt8522 = kzalloc(sizeof(*yt8522), GFP_KERNEL);
		if (!yt8522)
			return -ENOMEM;	/* ref: net/phy/ti.c */

		phydev->priv = yt8522;
		chip_config = ytphy_read_ext(phydev,
					     YT8522_EXTENDED_COMBO_CTRL_1);
		yt8522->chip_mode = (chip_config & (BIT(1) | BIT(0)));
	} else {
		yt8522 = (struct yt8xxx_priv *)phydev->priv;
	}

	return 0;
}

static int yt8522_config(struct phy_device *phydev)
{
	struct yt8xxx_priv *priv = phydev->priv;
	int ret;
	int val;

	val = ytphy_read_ext(phydev, YT8522_EXTENDED_COMBO_CTRL_1);
	if (val < 0)
		return val;

	if (0x2 == (priv->chip_mode)) {	/* RMII2 mode */
		val |= BIT(4);
		ret = ytphy_write_ext(phydev, YT8522_EXTENDED_COMBO_CTRL_1,
				      val);
		if (ret < 0)
			return ret;

		ret = ytphy_write_ext(phydev, YT8522_TX_DELAY_CONTROL, 0x9f);
		if (ret < 0)
			return ret;

		ret = ytphy_write_ext(phydev, YT8522_EXTENDED_PAD_CONTROL,
				      0x81d4);
		if (ret < 0)
			return ret;
	}
	else if (0x3 == (priv->chip_mode)) {	/* RMII1 mode */
		val |= BIT(4);
		ret = ytphy_write_ext(phydev, YT8522_EXTENDED_COMBO_CTRL_1,
				      val);
		if (ret < 0)
			return ret;
	}

	ret = ytphy_write_ext(phydev, YT8522_TX_CLK_DELAY, 0);
	if (ret < 0)
		return ret;

	ret = ytphy_write_ext(phydev, YT8522_ANAGLOG_IF_CTRL, 0xbf2a);
	if (ret < 0)
		return ret;

	ret = ytphy_write_ext(phydev, YT8522_DAC_CTRL, 0x297f);
	if (ret < 0)
		return ret;

	ret = ytphy_write_ext(phydev, YT8522_INTERPOLATOR_FILTER_1, 0x1FE);
	if (ret < 0)
		return ret;

	ret = ytphy_write_ext(phydev, YT8522_INTERPOLATOR_FILTER_2, 0x1FE);
	if (ret < 0)
		return ret;

	/* disable auto sleep */
	val = ytphy_read_ext(phydev, YT8512_EXTREG_SLEEP_CONTROL1);
	if (val < 0)
		return val;

	val &= (~BIT(YT8512_EN_SLEEP_SW_BIT));

	ret = ytphy_write_ext(phydev, YT8512_EXTREG_SLEEP_CONTROL1, val);
	if (ret < 0)
		return ret;

	genphy_config_aneg(phydev);

	ytphy_soft_reset(phydev);

	return 0;
}

static int yt8522_startup(struct phy_device *phydev)
{
	int speed, speed_mode, duplex;
	int val;

	msleep(1000);

	val = phy_read(phydev, MDIO_DEVAD_NONE, REG_PHY_SPEC_STATUS);
	if (val < 0)
		return val;

	if ((val & BIT(10)) >> YT_LINK_STATUS_BIT) {	/* link up */
		duplex = (val & BIT(13)) >> YT_DUPLEX_BIT;
		speed_mode = (val & (BIT(15) | BIT(14))) >> YT_SPEED_MODE_BIT;
		switch (speed_mode) {
		case 0:
			speed = SPEED_10;
			break;
		case 1:
			speed = SPEED_100;
			break;
		default:
			speed = SPEED_10;
			break;
		}

		phydev->link = 1;
		phydev->speed = speed;
		phydev->duplex = duplex;

		val = phy_read(phydev, MDIO_DEVAD_NONE, MII_LPA);
		if (val < 0)
			return val;

		phydev->pause = val & LPA_PAUSE_CAP;
		phydev->asym_pause = val & LPA_PAUSE_ASYM;

		return 0;
	}

	phydev->link = 0;

	return 0;
}

static int yt8521_hw_strap_polling(struct phy_device *phydev)
{
	int val = 0;

	val = ytphy_read_ext(phydev, 0xa001) & 0x7;
	switch (val) {
	case 1:
	case 4:
	case 5:
		return PHY_MODE_FIBER;
	case 2:
	case 6:
	case 7:
		return PHY_MODE_POLL;
	case 3:
	case 0:
	default:
		return PHY_MODE_UTP;
	}
}

static int yt8521S_probe(struct phy_device *phydev)
{
	struct yt8xxx_priv *yt8521S;

	if (!phydev->priv) {
		yt8521S = kzalloc(sizeof(*yt8521S), GFP_KERNEL);
		if (!yt8521S)
			return -ENOMEM;	/* ref: net/phy/ti.c */

		phydev->priv = yt8521S;
		yt8521S->strap_polling = yt8521_hw_strap_polling(phydev);
	} else {
		yt8521S = (struct yt8xxx_priv *)phydev->priv;
	}

	return 0;
}

static int yt8521S_config(struct phy_device *phydev)
{
	int val, hw_strap_mode;
	int ret;

#if (YT_WOL_FEATURE_ENABLE)
	struct ethtool_wolinfo wol;

	/* set phy wol enable */
	memset(&wol, 0x0, sizeof(struct ethtool_wolinfo));
	wol.wolopts |= WAKE_MAGIC;
	yt_wol_feature_set(phydev, &wol);
#endif

	hw_strap_mode = ytphy_read_ext(phydev, 0xa001) & 0x7;
	printf("hw_strap_mode: 0x%x\n", hw_strap_mode);

	ytphy_write_ext(phydev, 0xa000, 0);

	/* disable auto sleep */
	val = ytphy_read_ext(phydev, YT8521_EXTREG_SLEEP_CONTROL1);
	if (val < 0)
		return val;

	val &= (~BIT(YT8521_EN_SLEEP_SW_BIT));

	ret = ytphy_write_ext(phydev, YT8521_EXTREG_SLEEP_CONTROL1, val);
	if (ret < 0)
		return ret;

	/* enable RXC clock when no wire plug */
	val = ytphy_read_ext(phydev, 0xc);
	if (val < 0)
		return val;
	val &= ~(1 << 12);
	ret = ytphy_write_ext(phydev, 0xc, val);
	if (ret < 0)
		return ret;

	genphy_config_aneg(phydev);

	ret = ytxxxx_soft_reset(phydev);
	if (ret < 0)
		return ret;

	ret = ytphy_write_ext(phydev, 0xa000, 0x0);

	return ret;
}

/* for fiber mode, there is no 10M speed mode and
 * this function is for this purpose.
 */
static int yt8521_adjust_status(struct phy_device *phydev, int val, int is_utp)
{
	int speed_mode, duplex, speed;

	if (is_utp)
		duplex = (val & YT_DUPLEX) >> YT_DUPLEX_BIT;
	else
		duplex = 1;
	speed_mode = (val & YT_SPEED_MODE) >> YT_SPEED_MODE_BIT;
	switch (speed_mode) {
	case 2:
		speed = SPEED_1000;
		break;
	case 1:
		speed = SPEED_100;
		break;
	default:
		speed = SPEED_10;
		break;
	}

	if (!is_utp) {
		if (speed == SPEED_10)
			speed = SPEED_100;
	}

	phydev->speed = speed;
	phydev->duplex = duplex;

	return 0;
}

static int yt8521S_startup(struct phy_device *phydev)
{
	struct yt8xxx_priv *yt8521S = phydev->priv;
	int link_utp = 0, link_fiber = 0;
	int val_utp = 0, val_fiber = 0;
	int yt8521_fiber_latch_val;
	int yt8521_fiber_curr_val;
	int ret = 0;
	int link;

	msleep(1000);
	if (yt8521S->strap_polling != PHY_MODE_FIBER) {
		/* reading UTP */
		ret = ytphy_write_ext(phydev, 0xa000, 0);
		if (ret < 0)
			return ret;

		val_utp = phy_read(phydev, MDIO_DEVAD_NONE,
				   REG_PHY_SPEC_STATUS);
		if (val_utp < 0)
			return val_utp;

		link = val_utp & (BIT(YT_LINK_STATUS_BIT));
		if (link) {
			link_utp = 1;
			yt8521_adjust_status(phydev, val_utp, 1);
		} else {
			link_utp = 0;
		}
	}

	if (yt8521S->strap_polling != PHY_MODE_UTP) {
		/* reading Fiber */
		ret = ytphy_write_ext(phydev, 0xa000, 2);
		if (ret < 0)
			return ret;

		val_fiber = phy_read(phydev, MDIO_DEVAD_NONE,
				     REG_PHY_SPEC_STATUS);
		if (val_fiber < 0)
			return val_fiber;

		/* for fiber, from 1000m to 100m,
		 * there is not link down from 0x11,
		 * and check reg 1 to identify such case this is important
		 * for Linux kernel for that, missing linkdown event
		 * will cause problem.
		 */
		yt8521_fiber_latch_val = phy_read(phydev, MDIO_DEVAD_NONE,
						  MII_BMSR);
		yt8521_fiber_curr_val = phy_read(phydev, MDIO_DEVAD_NONE,
						 MII_BMSR);
		link = val_fiber & (BIT(YT_LINK_STATUS_BIT));
		if (link && yt8521_fiber_latch_val != yt8521_fiber_curr_val) {
			link = 0;
			printf("%s, phy addr: %d, fiber link down detect, latch = %04x, curr = %04x\n",
			       __func__, phydev->addr,
			       yt8521_fiber_latch_val,
			       yt8521_fiber_curr_val);
		}

		if (link) {
			link_fiber = 1;
			yt8521_adjust_status(phydev, val_fiber, 0);
		} else {
			link_fiber = 0;
		}
	}

	if (link_utp || link_fiber) {
		if (phydev->link == 0)
			printf("%s, phy addr: %d, link up, media: %s, mii reg 0x11 = 0x%x\n",
			       __func__, phydev->addr,
			       (link_utp && link_fiber) ? "UNKONWN MEDIA" :
			       (link_utp ? "UTP" : "Fiber"),
			       (link_utp ? (unsigned int)val_utp :
			       (unsigned int)val_fiber));
		phydev->link = 1;
	} else {
		if (phydev->link == 1)
			printf("%s, phy addr: %d, link down\n", __func__,
			       phydev->addr);
		phydev->link = 0;
	}

	if (yt8521S->strap_polling != PHY_MODE_FIBER) {
		if (link_fiber)
			ytphy_write_ext(phydev, 0xa000, 2);
		if (link_utp)
			ytphy_write_ext(phydev, 0xa000, 0);
	}

	return 0;
}

static int yt8531_config(struct phy_device *phydev)
{
	int ret = 0, val = 0;

#if (YT8531A_XTAL_INIT)
	ret = yt8531a_xtal_init(phydev);
	if (ret < 0)
		return ret;
#endif

#if (YT_WOL_FEATURE_ENABLE)
	struct ethtool_wolinfo wol;

	/* set phy wol enable */
	memset(&wol, 0x0, sizeof(struct ethtool_wolinfo));
	wol.wolopts |= WAKE_MAGIC;
	yt_wol_feature_set(phydev, &wol);
#endif

	val = ytphy_read_ext(phydev, 0xf);
	if(0x31 != val && 0x32 != val) {
		ret = ytphy_write_ext(phydev, 0x52, 0x231d);
		if (ret < 0)
			return ret;

		ret = ytphy_write_ext(phydev, 0x51, 0x04a9);
		if (ret < 0)
			return ret;

		ret = ytphy_write_ext(phydev, 0x57, 0x274c);
		if (ret < 0)
			return ret;

		if(0x500 == val) {
			val = ytphy_read_ext(phydev, 0xa001);
			if((0x30 == (val & 0x30)) || (0x20 == (val & 0x30))) {
				ret = ytphy_write_ext(phydev, 0xa010, 0xabff);
				if (ret < 0)
					return ret;
			}
		}
	}

	genphy_config_aneg(phydev);

	ytphy_soft_reset(phydev);

	return 0;
}

#ifdef YTPHY_YT8543_ENABLE
static int yt8543_config(struct phy_device *phydev)
{
	int ret = 0, val = 0;

#if (YT_WOL_FEATURE_ENABLE)
	struct ethtool_wolinfo wol;

	/* set phy wol enable */
	memset(&wol, 0x0, sizeof(struct ethtool_wolinfo));
	wol.wolopts |= WAKE_MAGIC;
	yt_wol_feature_set(phydev, &wol);
#endif

	ret = ytphy_write_ext(phydev, 0x403c, 0x286);
	if (ret < 0)
		return ret;

	ret = ytphy_write_ext(phydev, 0xdc, 0x855c);
	if (ret < 0)
		return ret;

	ret = ytphy_write_ext(phydev, 0xdd, 0x6040);
	if (ret < 0)
		return ret;

	ret = ytphy_write_ext(phydev, 0x40e, 0xf00);
	if (ret < 0)
		return ret;

	ret = ytphy_write_ext(phydev, 0x40f, 0xf00);
	if (ret < 0)
		return ret;

	ret = ytphy_write_ext(phydev, 0x411, 0x5030);
	if (ret < 0)
		return ret;

	ret = ytphy_write_ext(phydev, 0x1f, 0x110a);
	if (ret < 0)
		return ret;

	ret = ytphy_write_ext(phydev, 0x20, 0xc06);
	if (ret < 0)
		return ret;

	ret = ytphy_write_ext(phydev, 0x40d, 0x1f);
	if (ret < 0)
		return ret;

	val = ytphy_read_ext(phydev, 0xa088);
	if (val < 0)
		return ret;

	ret = ytphy_write_ext(phydev, 0xa088,
			      ((val & 0xfff0) | BIT(4)) |
			      (((ytphy_read_ext(phydev, 0xa015) & 0x3c)) >> 2));
	if (ret < 0)
		return ret;

	ret = ytphy_write_ext(phydev, 0xa183, 0x1918);
	if (ret < 0)
		return ret;

	ret = ytphy_write_ext(phydev, 0xa184, 0x1818);
	if (ret < 0)
		return ret;

	ret = ytphy_write_ext(phydev, 0xa186, 0x2018);
	if (ret < 0)
		return ret;

	ret = ytphy_write_ext(phydev, 0xa189, 0x3894);
	if (ret < 0)
		return ret;

	ret = ytphy_write_ext(phydev, 0xa187, 0x3838);
	if (ret < 0)
		return ret;

	ret = ytphy_write_ext(phydev, 0xa18b, 0x1918);
	if (ret < 0)
		return ret;

	ret = ytphy_write_ext(phydev, 0xa18c, 0x1818);
	if (ret < 0)
		return ret;

	genphy_config_aneg(phydev);

	ytphy_soft_reset(phydev);

	return 0;
}
#endif

static int yt8531S_config(struct phy_device *phydev)
{
	int ret = 0, val = 0;

#if (YT8531A_XTAL_INIT)
	ret = yt8531a_xtal_init(phydev);
	if (ret < 0)
		return ret;
#endif

	ret = ytphy_write_ext(phydev, 0xa023, 0x4031);
	if (ret < 0)
		return ret;

	ytphy_write_ext(phydev, 0xa000, 0x0);
	val = ytphy_read_ext(phydev, 0xf);

	if (0x31 != val && 0x32 != val) {
		ret = ytphy_write_ext(phydev, 0xa071, 0x9007);
		if (ret < 0)
			return ret;

		ret = ytphy_write_ext(phydev, 0x52, 0x231d);
		if (ret < 0)
			return ret;

		ret = ytphy_write_ext(phydev, 0x51, 0x04a9);
		if (ret < 0)
			return ret;

		ret = ytphy_write_ext(phydev, 0x57, 0x274c);
		if (ret < 0)
			return ret;

		ret = ytphy_write_ext(phydev, 0xa006, 0x10d);
		if (ret < 0)
			return ret;

		if (0x500 == val) {
			val = ytphy_read_ext(phydev, 0xa001);
			if((0x30 == (val & 0x30)) || (0x20 == (val & 0x30))) {
				ret = ytphy_write_ext(phydev, 0xa010, 0xabff);
				if (ret < 0)
					return ret;
			}
		}
	}

	ret = yt8521S_config(phydev);

	if (ret < 0)
		return ret;

	ytphy_write_ext(phydev, 0xa000, 0x0);

	return 0;
}

#if (YT_861X_AB_VER)
static int yt8614_get_port_from_phydev(struct phy_device *phydev)
{
	int tmp = ytphy_read_ext(phydev, 0xa0ff);
	int phy_addr = (unsigned int)phydev->addr;

	if ((phy_addr - tmp) < 0) {
		ytphy_write_ext(phydev, 0xa0ff, phy_addr);
		tmp = phy_addr;
	}

	return (phy_addr - tmp);
}
#endif

static int yt8614_config_init(struct phy_device *phydev)
{
	int port, ret = 0;

	port = phydev->addr & 3;

	ret = ytphy_write_ext(phydev, 0xa000, YT8614_REG_SPACE_UTP);
	if (ret < 0)
		return ret;

	/* for utp to optimize signal */
	ret = ytphy_write_ext(phydev, 0x41, 0x33);
	if (ret < 0)
		return ret;
	ret = ytphy_write_ext(phydev, 0x42, 0x66);
	if (ret < 0)
		return ret;
	ret = ytphy_write_ext(phydev, 0x43, 0xaa);
	if (ret < 0)
		return ret;
	ret = ytphy_write_ext(phydev, 0x44, 0xd0d);
	if (ret < 0)
		return ret;
	if (port == 2) {
		ret = ytphy_write_ext(phydev, 0x57, 0x2929);
		if (ret < 0)
			return ret;
	}

	/* for QSGMII optimization */
	ret = ytphy_write_ext(phydev, 0xa000, YT8614_REG_SPACE_QSGMII);
	if (ret < 0)
	        return ret;
	ret = ytphy_write_ext(phydev, 0x3, 0x4F80);
	if (ret < 0)
	        return ret;
	ret = ytphy_write_ext(phydev, 0xe, 0x4F80);
	if (ret < 0)
		return ret;

	/* for SGMII optimization */
	ret = ytphy_write_ext(phydev, 0xa000, YT8614_REG_SPACE_SGMII);
	if (ret < 0)
		return ret;
	ret = ytphy_write_ext(phydev, 0x3, 0x2420);
	if (ret < 0)
		return ret;
	ret = ytphy_write_ext(phydev, 0xe, 0x24a0);
	if (ret < 0)
		return ret;

	return ytphy_write_ext(phydev, 0xa000, YT8614_REG_SPACE_UTP);
}

int yt8618_soft_reset(struct phy_device *phydev)
{
	int ret;

	/* qsgmii */
	ytphy_write_ext(phydev, 0xa000, 2);
	ret = ytphy_soft_reset(phydev);
	if (ret < 0) {
		ytphy_write_ext(phydev, 0xa000, 0);
		return ret;
	}

	ytphy_write_ext(phydev, 0xa000, 0);
	ret = ytphy_soft_reset(phydev);
	if (ret < 0)
		return ret;

	return 0;
}

static int yt8618_config(struct phy_device *phydev)
{
	unsigned int retries = 12;
#if (YT_861X_AB_VER)
	int port = 0;
#endif
	int ret;
	int val;

#if (YT_861X_AB_VER)
	port = yt8614_get_port_from_phydev(phydev);
#endif

	ytphy_write_ext(phydev, 0xa000, 0);

	/* for utp to optimize signal */
	ret = ytphy_write_ext(phydev, 0x41, 0x33);
	if (ret < 0)
		return ret;
	ret = ytphy_write_ext(phydev, 0x42, 0x66);
	if (ret < 0)
		return ret;
	ret = ytphy_write_ext(phydev, 0x43, 0xaa);
	if (ret < 0)
		return ret;
	ret = ytphy_write_ext(phydev, 0x44, 0xd0d);
	if (ret < 0)
		return ret;

#if (YT_861X_AB_VER)
	if ((port == 2) || (port == 5)) {
		ret = ytphy_write_ext(phydev, 0x57, 0x2929);
		if (ret < 0)
			return ret;
	}
#endif

	val = phy_read(phydev, MDIO_DEVAD_NONE, MII_BMCR);
	phy_write(phydev, MDIO_DEVAD_NONE, MII_BMCR, val | BMCR_RESET);
	do {
		msleep(50);
		ret = phy_read(phydev, MDIO_DEVAD_NONE, MII_BMCR);
		if (ret < 0)
			return ret;
	} while ((ret & BMCR_RESET) && --retries);
	if (ret & BMCR_RESET)
		return -ETIMEDOUT;

	/* for QSGMII optimization */
	ytphy_write_ext(phydev, 0xa000, 0x02);

	ret = ytphy_write_ext(phydev, 0x3, 0x4F80);
	if (ret < 0) {
		ytphy_write_ext(phydev, 0xa000, 0);
		return ret;
	}
	ret = ytphy_write_ext(phydev, 0xe, 0x4F80);
	if (ret < 0) {
		ytphy_write_ext(phydev, 0xa000, 0);
		return ret;
	}

	ytphy_write_ext(phydev, 0xa000, 0);

	printf("%s done, phy addr: %d\n", __func__, phydev->addr);

	genphy_config_aneg(phydev);

	yt8618_soft_reset(phydev);

	return ret;
}

static int yt8618_startup(struct phy_device *phydev)
{
	int link_utp = 0;
	int link;
	int ret;
	int val;

	msleep(1000);

	/* switch to utp and reading regs  */
	ret = ytphy_write_ext(phydev, 0xa000, 0);
	if (ret < 0)
		return ret;

	val = phy_read(phydev, MDIO_DEVAD_NONE, REG_PHY_SPEC_STATUS);
	if (val < 0)
		return val;

	link = val & (BIT(YT_LINK_STATUS_BIT));
	if (link) {
		link_utp = 1;
		yt8521_adjust_status(phydev, val, 1);
	} else {
		link_utp = 0;
	}

	if (link_utp)
		phydev->link = 1;
	else
		phydev->link = 0;

	val = phy_read(phydev, MDIO_DEVAD_NONE, MII_LPA);
	if (val < 0)
		return val;

	phydev->pause = val & LPA_PAUSE_CAP;
	phydev->asym_pause = val & LPA_PAUSE_ASYM;

	return 0;
}

static int yt8821_init(struct phy_device *phydev)
{
	int ret = 0;

	ret = ytphy_write_ext(phydev, 0xa000, 0x2);
	if (ret < 0)
		return ret;

	ret = ytphy_write_ext(phydev, 0x23, 0x8605);
	if (ret < 0)
		return ret;

	ret = ytphy_write_ext(phydev, 0xa000, 0x0);
	if (ret < 0)
		return ret;

	ret = ytphy_write_ext(phydev, 0x34e, 0x8080);
	if (ret < 0)
		return ret;

	ret = ytphy_write_ext(phydev, 0x4d2, 0x5200);
	if (ret < 0)
		return ret;

	ret = ytphy_write_ext(phydev, 0x4d3, 0x5200);
	if (ret < 0)
		return ret;

	ret = ytphy_write_ext(phydev, 0x372, 0x5a3c);
	if (ret < 0)
		return ret;

	ret = ytphy_write_ext(phydev, 0x374, 0x7c6c);
	if (ret < 0)
		return ret;

	ret = ytphy_write_ext(phydev, 0x336, 0xaa0a);
	if (ret < 0)
		return ret;

	ret = ytphy_write_ext(phydev, 0x340, 0x3022);
	if (ret < 0)
		return ret;

	ret = ytphy_write_ext(phydev, 0x36a, 0x8000);
	if (ret < 0)
		return ret;

	ret = ytphy_write_ext(phydev, 0x4b3, 0x7711);
	if (ret < 0)
		return ret;

	ret = ytphy_write_ext(phydev, 0x4b5, 0x2211);
	if (ret < 0)
		return ret;

	ret = ytphy_write_ext(phydev, 0x56, 0x20);
	if (ret < 0)
		return ret;

	ret = ytphy_write_ext(phydev, 0x56, 0x3f);
	if (ret < 0)
		return ret;

	ret = ytphy_write_ext(phydev, 0x97, 0x380c);
	if (ret < 0)
		return ret;

	ret = ytphy_write_ext(phydev, 0x660, 0x112a);
	if (ret < 0)
		return ret;

	ret = ytphy_write_ext(phydev, 0x450, 0xe9);
	if (ret < 0)
		return ret;

	ret = ytphy_write_ext(phydev, 0x466, 0x6464);
	if (ret < 0)
		return ret;

	ret = ytphy_write_ext(phydev, 0x467, 0x6464);
	if (ret < 0)
		return ret;

	ret = ytphy_write_ext(phydev, 0x468, 0x6464);
	if (ret < 0)
		return ret;

	ret = ytphy_write_ext(phydev, 0x469, 0x6464);
	if (ret < 0)
		return ret;

	return ret;
}

#define YT8821_CHIP_MODE_AUTO_BX2500_SGMII	(1)
#define YT8821_CHIP_MODE_FORCE_BX2500		(0)
#define YT8821_CHIP_MODE_UTP_TO_FIBER_FORCE	(0)
static int yt8821_config(struct phy_device *phydev)
{
	int ret;
	int val;

	val = ytphy_read_ext(phydev, 0xa001);
/* ext reg 0xa001 bit2:0 3'b000 */
#if (YT8821_CHIP_MODE_AUTO_BX2500_SGMII)
	val &= ~(BIT(0));
	val &= ~(BIT(1));
	val &= ~(BIT(2));
	ret = ytphy_write_ext(phydev, 0xa001, val);
	if (ret < 0)
		return ret;

	ret = ytphy_write_ext(phydev, 0xa000, 2);
	if (ret < 0)
		return ret;

	val = phy_read(phydev, MDIO_DEVAD_NONE, MII_BMCR);
	val |= BIT(12);
	phy_write(phydev, MDIO_DEVAD_NONE, MII_BMCR, val);

	ret = ytphy_write_ext(phydev, 0xa000, 0x0);
	if (ret < 0)
		return ret;
/* ext reg 0xa001 bit2:0 3'b001 */
#elif (YT8821_CHIP_MODE_FORCE_BX2500)
	val |= BIT(0);
	val &= ~(BIT(1));
	val &= ~(BIT(2));
	ret = ytphy_write_ext(phydev, 0xa001, val);
	if (ret < 0)
		return ret;

	ret = ytphy_write_ext(phydev, 0xa000, 0x0);
	if (ret < 0)
		return ret;

	val = phy_read(phydev, MDIO_DEVAD_NONE, MII_ADVERTISE);
	val |= 1 << 10;
	val |= 1 << 11;
	phy_write(phydev, MDIO_DEVAD_NONE, MII_ADVERTISE, val);

	ret = ytphy_write_ext(phydev, 0xa000, 2);
	if (ret < 0)
		return ret;

	val = phy_read(phydev, MDIO_DEVAD_NONE, MII_ADVERTISE);
	val |= 1 << 7;
	val |= 1 << 8;
	phy_write(phydev, MDIO_DEVAD_NONE, MII_ADVERTISE, val);

	val = phy_read(phydev, MDIO_DEVAD_NONE, MII_BMCR);
	val &= ~(BIT(12));
	phy_write(phydev, MDIO_DEVAD_NONE, MII_BMCR, val);

	ret = ytphy_write_ext(phydev, 0xa000, 0x0);
	if (ret < 0)
		return ret;
/* ext reg 0xa001 bit2:0 3'b101 */
#elif (YT8821_CHIP_MODE_UTP_TO_FIBER_FORCE)
	val |= BIT(0);
	val &= ~(BIT(1));
	val |= BIT(2);
	ret = ytphy_write_ext(phydev, 0xa001, val);
	if (ret < 0)
		return ret;
#endif

#if (YT_WOL_FEATURE_ENABLE)
	struct ethtool_wolinfo wol;

	/* set phy wol enable */
	memset(&wol, 0x0, sizeof(struct ethtool_wolinfo));
	wol.wolopts |= WAKE_MAGIC;
	yt_wol_feature_set(phydev, &wol);
#endif

	ret = yt8821_init(phydev);
	if (ret < 0)
		return ret;

	/* disable auto sleep */
	val = ytphy_read_ext(phydev, YT8521_EXTREG_SLEEP_CONTROL1);
	if (val < 0)
		return val;

	val &= (~BIT(YT8521_EN_SLEEP_SW_BIT));

	ret = ytphy_write_ext(phydev, YT8521_EXTREG_SLEEP_CONTROL1, val);
	if (ret < 0)
		return ret;

	genphy_config_aneg(phydev);

	/* soft reset whole chip */
	ret = ytxxxx_soft_reset(phydev);

	printf("%s done, phy addr: %d\n", __func__, phydev->addr);

	return ret;
}

static int yt8821_startup(struct phy_device *phydev)
{
	msleep(1000);
	genphy_update_link(phydev);
	yt8821_parse_status(phydev);

	return 0;
}

#if defined(U_BOOT_PHY_DRIVER_MACRO)
U_BOOT_PHY_DRIVER(YT8010_driver) = {
#else
static struct phy_driver YT8010_driver = {
#endif
	.name		= "YT8010 100Mb Automotive Ethernet",
	.uid		= PHY_ID_YT8010,
	.mask		= PHY_ID_MASK,
	.features	= PHY_BASIC_FEATURES,
	.config		= &yt8010_config,
	.startup	= &yt8010_startup,
	.shutdown	= &genphy_shutdown,
};

#if defined(U_BOOT_PHY_DRIVER_MACRO)
U_BOOT_PHY_DRIVER(YT8010AS_driver) = {
#else
static struct phy_driver YT8010AS_driver = {
#endif
	.name		= "YT8010AS 100Mb Automotive Ethernet",
	.uid		= PHY_ID_YT8010AS,
	.mask		= PHY_ID_MASK,
	.features	= PHY_BASIC_FEATURES,
	.config		= &yt8010AS_config,
	.startup	= &yt8010_startup,
	.shutdown	= &genphy_shutdown,
};

#if defined(U_BOOT_PHY_DRIVER_MACRO)
U_BOOT_PHY_DRIVER(YT8011_driver) = {
#else
static struct phy_driver YT8011_driver = {
#endif
	.name		= "YT8011 1000Mb Automotive Ethernet",
	.uid		= PHY_ID_YT8011,
	.mask		= PHY_ID_MASK,
	.features	= PHY_GBIT_FEATURES,
	.probe		= &yt8011_probe,
	.config		= &yt8011_config,
	.startup	= &yt8011_startup,
	.shutdown	= &genphy_shutdown,
};

#if defined(U_BOOT_PHY_DRIVER_MACRO)
U_BOOT_PHY_DRIVER(YT8510_driver) = {
#else
static struct phy_driver YT8510_driver = {
#endif
	.name		= "8510 100/10Mb Ethernet",
	.uid		= PHY_ID_YT8510,
	.mask		= PHY_ID_MASK,
	.features	= PHY_BASIC_FEATURES,
	.config		= &yt8510_config,
	.startup	= &yt_startup,
	.shutdown	= &genphy_shutdown,
};

#if defined(U_BOOT_PHY_DRIVER_MACRO)
U_BOOT_PHY_DRIVER(YT8511_driver) = {
#else
static struct phy_driver YT8511_driver = {
#endif
	.name		= "YT8511 Gigabit Ethernet",
	.uid		= PHY_ID_YT8511,
	.mask		= PHY_ID_MASK,
	.features	= PHY_GBIT_FEATURES,
	.config		= &yt8511_config,
	.startup	= &yt_startup,
	.shutdown	= &genphy_shutdown,
};

#if defined(U_BOOT_PHY_DRIVER_MACRO)
U_BOOT_PHY_DRIVER(YT8512_driver) = {
#else
static struct phy_driver YT8512_driver = {
#endif
	.name		= "YT8512 100/10Mb Ethernet",
	.uid		= PHY_ID_YT8512,
	.mask		= PHY_ID_MASK,
	.features	= PHY_BASIC_FEATURES,
	.probe		= &yt8512_probe,
	.config		= &yt8512_config,
	.startup	= &yt_startup,
	.shutdown	= &genphy_shutdown,
};

#if defined(U_BOOT_PHY_DRIVER_MACRO)
U_BOOT_PHY_DRIVER(YT8522_driver) = {
#else
static struct phy_driver YT8522_driver = {
#endif
	.name		= "YT8522 100/10Mb Ethernet",
	.uid		= PHY_ID_YT8522,
	.mask		= PHY_ID_MASK,
	.features	= PHY_BASIC_FEATURES,
	.probe		= &yt8522_probe,
	.config		= &yt8522_config,
	.startup	= &yt8522_startup,
	.shutdown	= &genphy_shutdown,
};

#if defined(U_BOOT_PHY_DRIVER_MACRO)
U_BOOT_PHY_DRIVER(YT8512B_driver) = {
#else
static struct phy_driver YT8512B_driver = {
#endif
	.name		= "YT8512B 100/10Mb Ethernet",
	.uid		= PHY_ID_YT8512B,
	.mask		= PHY_ID_MASK,
	.features	= PHY_BASIC_FEATURES,
	.probe		= &yt8512_probe,
	.config		= &yt8512_config,
	.startup	= &yt_startup,
	.shutdown	= &genphy_shutdown,
};

#if defined(U_BOOT_PHY_DRIVER_MACRO)
U_BOOT_PHY_DRIVER(YT8521S_driver) = {
#else
static struct phy_driver YT8521S_driver = {
#endif
	.name		= "YT8521S Gigabit Ethernet",
	.uid		= PHY_ID_YT8521S,
	.mask		= PHY_ID_MASK,
	.features	= PHY_GBIT_FEATURES,
	.probe		= &yt8521S_probe,
	.config		= &yt8521S_config,
	.startup	= &yt8521S_startup,
	.shutdown	= &genphy_shutdown,
};

#if defined(U_BOOT_PHY_DRIVER_MACRO)
U_BOOT_PHY_DRIVER(YT8531_driver) = {
#else
static struct phy_driver YT8531_driver = {
#endif
	.name		= "YT8531 Gigabit Ethernet",
	.uid		= PHY_ID_YT8531,
	.mask		= PHY_ID_MASK,
	.features	= PHY_GBIT_FEATURES,
	.config		= &yt8531_config,
	.startup	= &yt_startup,
	.shutdown	= &genphy_shutdown,
};

#ifdef YTPHY_YT8543_ENABLE
#if defined(U_BOOT_PHY_DRIVER_MACRO)
U_BOOT_PHY_DRIVER(YT8543_driver) = {
#else
static struct phy_driver YT8543_driver = {
#endif
	.name		= "YT8543 dual port Gigabit Ethernet",
	.uid		= PHY_ID_YT8543,
	.mask		= PHY_ID_MASK,
	.features	= PHY_GBIT_FEATURES,
	.config		= &yt8543_config,
	.startup	= &yt_startup,
	.shutdown	= &genphy_shutdown,
};
#endif

#if defined(U_BOOT_PHY_DRIVER_MACRO)
U_BOOT_PHY_DRIVER(YT8531S_driver) = {
#else
static struct phy_driver YT8531S_driver = {
#endif
	.name		= "YT8531S Gigabit Ethernet",
	.uid		= PHY_ID_YT8531S,
	.mask		= PHY_ID_MASK,
	.features	= PHY_GBIT_FEATURES,
	.probe		= &yt8521S_probe,
	.config		= &yt8531S_config,
	.startup	= &yt8521S_startup,
	.shutdown	= &genphy_shutdown,
};

#if defined(U_BOOT_PHY_DRIVER_MACRO)
U_BOOT_PHY_DRIVER(YT8614_driver) = {
#else
static struct phy_driver YT8614_driver = {
#endif
	.name		= "Motorcomm YT8614",
	.uid		= PHY_ID_YT8614,
	.mask		= PHY_ID_MASK,
	.features	= PHY_GBIT_FEATURES,
	.probe		= yt8614_config_init,
	.config		= genphy_config,
	.startup	= genphy_startup,
	.shutdown	= genphy_shutdown,
};

#if defined(U_BOOT_PHY_DRIVER_MACRO)
U_BOOT_PHY_DRIVER(YT8618_driver) = {
#else
static struct phy_driver YT8618_driver = {
#endif
	.name		= "YT8618 Gigabit Ethernet",
	.uid		= PHY_ID_YT8618,
	.mask		= PHY_ID_MASK,
	.features	= PHY_GBIT_FEATURES,
	.config		= &yt8618_config,
	.startup	= &yt8618_startup,
	.shutdown	= &genphy_shutdown,
};

#if defined(U_BOOT_PHY_DRIVER_MACRO)
U_BOOT_PHY_DRIVER(YT8821_driver) = {
#else
static struct phy_driver YT8821_driver = {
#endif
	.name		= "YT8821 2.5Gb Ethernet",
	.uid		= PHY_ID_YT8821,
	.mask		= PHY_ID_MASK,
	.features	= PHY_GBIT_FEATURES,
	.config		= &yt8821_config,
	.startup	= &yt8821_startup,
	.shutdown	= &genphy_shutdown,
};

#if !defined(U_BOOT_PHY_DRIVER_MACRO)
int phy_motorcomm_init(void)
{
	phy_register(&YT8010_driver);
	phy_register(&YT8010AS_driver);
	phy_register(&YT8011_driver);
	phy_register(&YT8510_driver);
	phy_register(&YT8511_driver);
	phy_register(&YT8512_driver);
	phy_register(&YT8512B_driver);
	phy_register(&YT8522_driver);
	phy_register(&YT8521S_driver);
	phy_register(&YT8531_driver);
#ifdef YTPHY_YT8543_ENABLE
	phy_register(&YT8543_driver);
#endif
	phy_register(&YT8531S_driver);
	phy_register(&YT8614_driver);
	phy_register(&YT8618_driver);
	phy_register(&YT8821_driver);

	return 0;
}
#endif


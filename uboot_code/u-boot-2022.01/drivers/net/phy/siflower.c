// SPDX-License-Identifier: GPL-2.0+
/*
* Siflower PHY drivers
*
* Copyright 2023-2034 Siflower, Inc.
* Description : Driver for SF1211F Giga PHYs.
*/
#include <common.h>
#include <linux/bitops.h>
#include <phy.h>
#include <linux/delay.h>
#include "siflower_fw.h"

/* Mask used for ID comparisons */
#define SIFLOWER_PHY_ID_MASK                                    0xffffffff
/* SF1211F PHY IDs */
#define SF1211F_PHY_ID                                          0xADB40412
/* SF1240 PHY IDs */
#define SF1240_PHY_ID                                          0xADB40411
/* PHY EXTRW OPSREG */
#define SF1211F_EXTREG_ADDR                                     0x0E
#define SF1211F_EXTREG_DATA                                     0x0D

#define SIFLOWER_SPEC_REG                                       0x11
#define SIFLOWER_PHY_RXC_DELAY_VAL                              0x40
#define SIFLOWER_PHY_TXC_DELAY_VAL                              0x40
/* PHY MODE OPSREG*/
#define SF1211F_EXTREG_GET_PORT_PHY_MODE                        0x062B
#define SF1211F_EXTREG_PHY_MODE_MASK                            0x0070
/* 8 PHY MODE */
#define SF1211F_EXTREG_PHY_MODE_UTP_TO_RGMII                    0x00
#define SF1211F_EXTREG_PHY_MODE_FIBER_TO_RGMII                  0x10
#define SF1211F_EXTREG_PHY_MODE_UTP_OR_FIBER_TO_RGMII           0x20
#define SF1211F_EXTREG_PHY_MODE_UTP_TO_SGMII                    0x30
#define SF1211F_EXTREG_PHY_MODE_SGMII_PHY_TO_RGMII_MAC          0x40
#define SF1211F_EXTREG_PHY_MODE_SGMII_MAC_TO_RGMII_PHY          0x50
#define SF1211F_EXTREG_PHY_MODE_UTP_TO_FIBER_AUTO               0x60
#define SF1211F_EXTREG_PHY_MODE_UTP_TO_FIBER_FORCE              0x70


/* PHY LED */
#define SF1211F_EXTREG_LED0                                     0x1E33   // 0
#define SF1211F_EXTREG_LED1                                     0x1E34   // 00101111
#define SF1211F_EXTREG_LED2                                     0x1E35   // 0x40
/* SF1240 PHY BX LED */
#define SF1240_EXTREG_LEDCTRL                                  0x0621
#define SF1240_EXTREG_LED0_1                                   0x0700
#define SF1240_EXTREG_LED0_2                                   0x0701
#define SF1240_EXTREG_LED1_1                                   0x0702
#define SF1240_EXTREG_LED1_2                                   0x0703
#define SF1240_EXTREG_LED2_1                                   0x0706
#define SF1240_EXTREG_LED2_2                                   0x0707
#define SF1240_EXTREG_LED3_1                                   0x0708
#define SF1240_EXTREG_LED3_2                                   0x0709
#define SF1240_EXTREG_LED4_1                                   0x070C
#define SF1240_EXTREG_LED4_2                                   0x070D
#define SF1240_EXTREG_LED5_1                                   0x070E
#define SF1240_EXTREG_LED5_2                                   0x070F
#define SF1240_EXTREG_LED6_1                                   0x0712
#define SF1240_EXTREG_LED6_2                                   0x0713
#define SF1240_EXTREG_LED7_1                                   0x0714
#define SF1240_EXTREG_LED7_2                                   0x0715

/* SF1240 PATCH INIT */
#define LINK_AN_STATUS						0x11
#define glblEphyInit						0xC413
#define glblPatchEnable						0xC45D
#define glblPatchEnableAck					0xC45E
#define glblPatchInit						0xC460

#define SIFLOWER_PHY_CLK_OUT_125M_ENABLE                        1

#define msleep(n)                udelay(n * 1000)

static int sfphy_read_ext(struct phy_device *phydev, u32 regnum)
{
	int ret, val, oldval;

	ret = phy_read(phydev, MDIO_DEVAD_NONE, SF1211F_EXTREG_ADDR);
	if (ret < 0) {
		return ret;
	}
	oldval = ret;

	ret = phy_write(phydev, MDIO_DEVAD_NONE, SF1211F_EXTREG_ADDR, regnum);
	if(ret < 0) {
		return ret;
	}
	ret = phy_read(phydev, MDIO_DEVAD_NONE, SF1211F_EXTREG_DATA);
	if(ret < 0) {
		return ret;
	}
	val = ret;

	ret = phy_write(phydev, MDIO_DEVAD_NONE, SF1211F_EXTREG_ADDR, oldval);
	if (ret < 0) {
		return ret;
	}
	ret = val;

	return ret;
}

static int sfphy_write_ext(struct phy_device *phydev, u32 regnum, u16 val)
{
	int ret, oldval;

	ret = phy_read(phydev, MDIO_DEVAD_NONE, SF1211F_EXTREG_ADDR);
	if (ret < 0) {
		return ret;
	}
	oldval = ret;

	ret = phy_write(phydev, MDIO_DEVAD_NONE, SF1211F_EXTREG_ADDR, regnum);
	if(ret < 0) {
		return ret;
	}
	ret = phy_write(phydev, MDIO_DEVAD_NONE, SF1211F_EXTREG_DATA, val);
	if(ret < 0) {
		return ret;
	}

	ret = phy_write(phydev, MDIO_DEVAD_NONE, SF1211F_EXTREG_ADDR, oldval);
	if (ret < 0) {
		return ret;
	}
	ret = val;

	return ret;
}

static int sf1240_load_patch(struct phy_device *phydev)
{
	unsigned int offset = 0;
	int ret;
	u16 val;

	for (; offset < sf1240_fw_size; offset++) {
		val = sf1240_fw[offset];
		ret = sfphy_write_ext(phydev, 0xC800 + offset, val);
		if (ret < 0) {
			return ret;
		}
	}

	return 0;
}

static int sf1240_all_port_power_down(struct phy_device *phydev)
{
	struct phy_device *sf1240_phydev = NULL;
	unsigned int val, ret;
	int addr;

	for (addr = 0; addr < PHY_MAX_ADDR; addr++) {
		sf1240_phydev = phydev->bus->phymap[addr];
		if (!sf1240_phydev || sf1240_phydev->phy_id != SF1240_PHY_ID)
			continue;

		val = phy_read(sf1240_phydev, MDIO_DEVAD_NONE, MII_BMCR);
		val |= BMCR_PDOWN;
		phy_write(sf1240_phydev, MDIO_DEVAD_NONE, MII_BMCR, val);

		val = phy_read(sf1240_phydev, MDIO_DEVAD_NONE, LINK_AN_STATUS);
		if (!(val & BIT(11))) {
			return -1;
		} else {
			sf1240_phydev = NULL;
		}

		if (ret)
			return ret;
	}
	return ret;
}

static int sf1240_load_patch_enable(struct phy_device *phydev)
{
	int ret, num = 0;
	unsigned int patchenable_val, patchenableack_val;

	// set the port POWER_DOWN bit 1 and check POWER_DOWN_STATUS bit
	ret = sf1240_all_port_power_down(phydev);
	if (ret)
		return -1;

	//set the glblPatchEnable 0 and check the glblPatchEnableAck 0
	ret = sfphy_write_ext(phydev, glblPatchEnable, 0x0);
	if (ret < 0)
		return ret;

	while (sfphy_read_ext(phydev, glblPatchEnableAck) != 0) {
		msleep(10);
		if(++num == 10) {
			printf("Ext_read glblPatchEnableAck Time Out!\r\n");
			return -1;
		}
	}

	// load the bin and write it at the 0xC800
	sf1240_load_patch(phydev);

	// init the patch
	ret = sfphy_write_ext(phydev, glblPatchInit, 0x85);
	if (ret < 0)
		return ret;

	// enable the patch and reset the phy_init
	ret = sfphy_write_ext(phydev, glblEphyInit, 0x85);

	num = 0;
	while (sfphy_read_ext(phydev, glblEphyInit) != 0) {
		msleep(10);
		if(++num == 10) {
			printf("Ext_read Time Out!\r\n");
			break;
		}
	}

	// check the patch enable
	patchenable_val = sfphy_read_ext(phydev, glblPatchEnable);
	patchenableack_val = sfphy_read_ext(phydev, glblPatchEnableAck);
	if (patchenable_val != 0x85 || patchenableack_val != 0x85)
		printf("now the patch load fail!!!\n");

	return 0;

}

static int sf1240_led_init(struct phy_device *phydev)
{
	int ret;
	// set led put low level
	ret = sfphy_write_ext(phydev, SF1240_EXTREG_LEDCTRL, 0x00);
	if (ret < 0)
		return ret;
	ret = sfphy_read_ext(phydev, SF1240_EXTREG_LED0_1);
	if (ret < 0)
		return ret;
	ret = sfphy_read_ext(phydev, SF1240_EXTREG_LED0_2);
	if (ret < 0)
		return ret;


	// set led 0 1
	ret = sfphy_write_ext(phydev, SF1240_EXTREG_LED0_1, 0x00);
	if (ret < 0)
		return ret;
	ret = sfphy_write_ext(phydev, SF1240_EXTREG_LED0_2, 0x0E);
	if (ret < 0)
		return ret;
	ret = sfphy_write_ext(phydev, SF1240_EXTREG_LED1_1, 0xF0);
	if (ret < 0)
		return ret;
	ret = sfphy_write_ext(phydev, SF1240_EXTREG_LED1_2, 0x0E);
	if (ret < 0)
		return ret;

	// set led 2 3
	ret = sfphy_write_ext(phydev, SF1240_EXTREG_LED2_1, 0x00);
	if (ret < 0)
		return ret;
	ret = sfphy_write_ext(phydev, SF1240_EXTREG_LED2_2, 0x1E);
	if (ret < 0)
		return ret;
	ret = sfphy_write_ext(phydev, SF1240_EXTREG_LED3_1, 0xF0);
	if (ret < 0)
		return ret;
	ret = sfphy_write_ext(phydev, SF1240_EXTREG_LED3_2, 0x1E);
	if (ret < 0)
		return ret;

	// set led 4
	ret = sfphy_write_ext(phydev, SF1240_EXTREG_LED4_1, 0x00);
	if (ret < 0)
		return ret;
	ret = sfphy_write_ext(phydev, SF1240_EXTREG_LED4_2, 0x2E);
	if (ret < 0)
		return ret;
	ret = sfphy_write_ext(phydev, SF1240_EXTREG_LED5_1, 0xF0);
	if (ret < 0)
		return ret;
	ret = sfphy_write_ext(phydev, SF1240_EXTREG_LED5_2, 0x2E);
	if (ret < 0)
		return ret;

	// set led 6
	ret = sfphy_write_ext(phydev, SF1240_EXTREG_LED6_2, 0x00);
	if (ret < 0)
		return ret;
	ret = sfphy_write_ext(phydev, SF1240_EXTREG_LED6_2, 0x3E);
	if (ret < 0)
		return ret;
	ret = sfphy_write_ext(phydev, SF1240_EXTREG_LED7_1, 0xF0);
	if (ret < 0)
		return ret;
	ret = sfphy_write_ext(phydev, SF1240_EXTREG_LED7_2, 0x3E);
	if (ret < 0)
		return ret;

	return ret;
}

static int sf1211f_led_init(struct phy_device *phydev)
{
	int ret;

	ret = sfphy_write_ext(phydev, SF1211F_EXTREG_LED0, 0x00);
	if(ret < 0) {
		return ret;
	}
	ret = sfphy_write_ext(phydev, SF1211F_EXTREG_LED1, 0x2F);
	if(ret < 0) {
		return ret;
	}

	return sfphy_write_ext(phydev, SF1211F_EXTREG_LED2, 0x40);
}

static int sf1211f_soft_reset(struct phy_device *phydev)
{
	int ret = 0, val = 0;

	val = phy_read(phydev, MDIO_DEVAD_NONE, MII_BMCR);
	if (val < 0) {
		return val;
	}
	ret = phy_write(phydev, MDIO_DEVAD_NONE, MII_BMCR, val | BMCR_RESET);
	if(ret < 0) {
		return ret;
	}

	return ret;
}

static int sf1240_soft_reset(struct phy_device *phydev)
{
	int ret = 0, val = 0;

	val = phy_read(phydev, MDIO_DEVAD_NONE, MII_BMCR);
	if (val < 0) {
		return val;
	}
	ret = phy_write(phydev, MDIO_DEVAD_NONE, MII_BMCR, val | BMCR_RESET);
	if(ret < 0) {
		return ret;
	}

	return ret;
}

#if SIFLOWER_PHY_CLK_OUT_125M_ENABLE
static int sf1211f_clkout_init(struct phy_device *phydev)
{
	int ret;

	ret = sfphy_write_ext(phydev, 0x0272 , 0x09);
	if(ret < 0) {
		return ret;
	}

	return ret;
}
#endif

static int sf1211f_rxc_txc_init(struct phy_device *phydev)
{
	int ret;

	ret = (sfphy_read_ext(phydev, SF1211F_EXTREG_GET_PORT_PHY_MODE) &
		SF1211F_EXTREG_PHY_MODE_MASK);
	if (ret < 0)
		return ret;

	if ((ret == SF1211F_EXTREG_PHY_MODE_UTP_TO_SGMII) ||
		(ret == SF1211F_EXTREG_PHY_MODE_UTP_TO_FIBER_AUTO) ||
		(ret == SF1211F_EXTREG_PHY_MODE_UTP_TO_FIBER_FORCE))
		return 0;

	// Init rxc and enable rxc
	if (ret == SF1211F_EXTREG_PHY_MODE_UTP_TO_RGMII) {
		ret = phy_read(phydev, MDIO_DEVAD_NONE, 0x11);
		if ((ret & 0x4) == 0x0) {
			ret = sfphy_write_ext(phydev,0x1E0C, 0x17);
			if (ret < 0)
				return ret;
			ret = sfphy_write_ext(phydev,0x1E58, 0x00);
			if (ret < 0)
				return ret;
		}
	}

	if (phydev->interface == PHY_INTERFACE_MODE_RGMII_RXID){
		// Init rxc delay
		ret = sfphy_write_ext(phydev,0x0282, SIFLOWER_PHY_RXC_DELAY_VAL);
		if (ret < 0)
			return ret;
	}
	else if (phydev->interface == PHY_INTERFACE_MODE_RGMII_TXID){
		// Init txc delay
		ret = sfphy_write_ext(phydev,0x0281, SIFLOWER_PHY_TXC_DELAY_VAL);
		if (ret < 0)
			return ret;
	}
	else if(phydev->interface == PHY_INTERFACE_MODE_RGMII_ID){
		ret = sfphy_write_ext(phydev,0x0282, SIFLOWER_PHY_RXC_DELAY_VAL);
		if (ret < 0)
			return ret;
		ret = sfphy_write_ext(phydev,0x0281, SIFLOWER_PHY_TXC_DELAY_VAL);
		if (ret < 0)
			return ret;
	}

	return ret;
}

static int sf1211f_config_opt(struct phy_device *phydev)
{
	int ret;

	ret = sfphy_write_ext(phydev, 0x0149 , 0x84);
	if(ret < 0) {
		return ret;
	}

	ret = sfphy_write_ext(phydev, 0x014A , 0x86);
	if(ret < 0) {
		return ret;
	}

	ret = sfphy_write_ext(phydev, 0x023C , 0x81);
	if(ret < 0) {
		return ret;
	}

	return ret;
}

static int sf1211f_config(struct phy_device *phydev)
{
	int ret;
	ret = sf1211f_soft_reset(phydev);
	if(ret < 0) {
		return ret;
	}
	msleep(10);

	ret = sf1211f_rxc_txc_init(phydev);
	if(ret < 0) {
		return ret;
	}

	ret = sf1211f_config_opt(phydev);
	if(ret < 0) {
		return ret;
	}

	ret = sf1211f_led_init(phydev);
	if(ret < 0) {
		return ret;
	}

#if SIFLOWER_PHY_CLK_OUT_125M_ENABLE
	ret = sf1211f_clkout_init(phydev);
	if(ret < 0) {
		return ret;
	}
#endif

	ret = genphy_config_aneg(phydev);
	if(ret < 0) {
		return ret;
	}

	return 0;
}

static int sf1240_config(struct phy_device *phydev)
{
	int ret;
	ret = sf1240_soft_reset(phydev);
	if(ret < 0) {
		return ret;
	}
	msleep(10);

	ret = sf1240_led_init(phydev);
	if(ret < 0) {
		return ret;
	}

    /*
	ret = sf1240_load_patch_enable(phydev);
	if(ret < 0) {
		return ret;
	}
    */

	ret = genphy_config_aneg(phydev);
	if(ret < 0) {
		return ret;
	}

	return 0;
}

static int sf1211f_update_status(struct phy_device *phydev)
{
	int ret;

	phydev->speed = SPEED_10;
	phydev->duplex = DUPLEX_HALF;

	ret = phy_read(phydev, MDIO_DEVAD_NONE, SIFLOWER_SPEC_REG);
	if(ret < 0) {
		return ret;
	}

	if (ret & 0x02)
		phydev->duplex = DUPLEX_FULL;
	if ((ret & 0x18) == 0x10)
		phydev->speed = SPEED_1000;
	if ((ret & 0x18) == 0x08)
		phydev->speed = SPEED_100;
	return 0;
}

static int sf1240_update_status(struct phy_device *phydev)
{
	int ret;

	phydev->speed = SPEED_10;
	phydev->duplex = DUPLEX_HALF;

	ret = phy_read(phydev, MDIO_DEVAD_NONE, SIFLOWER_SPEC_REG);
	if(ret < 0) {
		return ret;
	}

	if (ret & 0x02)
		phydev->duplex = DUPLEX_FULL;
	if ((ret & 0x18) == 0x10)
		phydev->speed = SPEED_1000;
	if ((ret & 0x18) == 0x08)
		phydev->speed = SPEED_100;
	return 0;
}

static int sf1211f_startup(struct phy_device *phydev)
{
	int ret;

	ret = genphy_update_link(phydev);
	if(ret < 0) {
		return ret;
	}
	ret = sf1211f_update_status(phydev);
	if(ret < 0) {
		return ret;
	}
	ret = sf1211f_soft_reset(phydev);
	if(ret < 0) {
		return ret;
	}
	msleep(10);

	return 0;
}

static int sf1240_startup(struct phy_device *phydev)
{
	int ret;

	ret = genphy_update_link(phydev);
	if(ret < 0) {
		return ret;
	}

	ret = sf1240_update_status(phydev);
	if(ret < 0) {
		return ret;
	}

	ret = sf1240_soft_reset(phydev);
	if(ret < 0) {
		return ret;
	}
	msleep(10);

	return 0;
}

static struct phy_driver SF1211F_driver = {
	.name		= "Siflower SF23P1211F",
	.uid		= SF1211F_PHY_ID,
	.mask		= SIFLOWER_PHY_ID_MASK,
	.features	= PHY_GBIT_FEATURES,
	.config		= &sf1211f_config,
	.startup	= &sf1211f_startup,
	.shutdown	= &genphy_shutdown,
};

static struct phy_driver SF1240_driver = {
	.name		= "SF1240 Gigabit Ethernet",
	.uid		= SF1240_PHY_ID,
	.mask		= SIFLOWER_PHY_ID_MASK,
	.features	= PHY_GBIT_FEATURES,
	.config        	= &sf1240_config,
	.startup	= &sf1240_startup,
	.shutdown	= &genphy_shutdown,
};

int phy_siflower_init(void)
{
	phy_register(&SF1211F_driver);
	phy_register(&SF1240_driver);

	return 0;
}

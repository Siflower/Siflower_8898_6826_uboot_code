#include <miiphy.h>
#include <linux/delay.h>
#include <asm/gpio.h>
#include <malloc.h>

/* ID register values for different switch models */
#define PORT_SWITCH_ID_9215S		0x90020001

/* Device addresses */
#define MAX_BUSYING_WAIT_TIME	10

/* SMI format */
#define REG_ADDR_BIT1_ADDR 0
#define REG_ADDR_BIT1_DATA 1
#define REG_ADDR_BIT0_WRITE 0
#define REG_ADDR_BIT0_READ 1

/* Reg addr */
#define REG_ADDR_CHIP_ID			0x80008
#define INT_IF_ACCESS_FRAME_CTRL    0xf0000
#define INT_IF_ACCESS_ADDR_CTRL     0xf0004
#define INT_IF_ACCESS_DATA_0_ADDR   0xf0008
#define INT_IF_ACCESS_DATA_1_ADDR   0xf000c


struct yt9215xx_phy_priv {
	struct mii_dev	*mdio_bus;
	int smi_addr;
	int id;
	int port_count;		/* Number of switch ports */
	int cpu_port;
};


static int yt9215s_smi_read(struct phy_device *phydev, int devad, u32 reg)
{
	struct yt9215xx_phy_priv *priv = phydev->priv;
	struct mii_dev *mdio_bus = priv->mdio_bus;
	int smi_addr = priv->smi_addr;
	u32 rData;
	u16 regVal;
	u8 switchId;
	u8 regAddr;

	switchId = (devad == MDIO_DEVAD_NONE) ? 0 : devad;
	regAddr = (switchId << 2) | (REG_ADDR_BIT1_ADDR << 1) | REG_ADDR_BIT0_READ;
	/* Set reg_addr[31:16] */
	regVal = (reg >> 16) & 0xffff;
	mdio_bus->write(mdio_bus, smi_addr, MDIO_DEVAD_NONE, regAddr, regVal);

	/* Set reg_addr[15:0] */
	regVal = reg & 0xffff;
	mdio_bus->write(mdio_bus, smi_addr, MDIO_DEVAD_NONE, regAddr, regVal);

	regAddr = (switchId << 2) | (REG_ADDR_BIT1_DATA << 1)| REG_ADDR_BIT0_READ;
	/* Read Data [31:16] */
	regVal = mdio_bus->read(mdio_bus, smi_addr, MDIO_DEVAD_NONE, regAddr);
	rData = (uint32_t)(regVal << 16);

	/* Read Data [15:0] */
	regVal = mdio_bus->read(mdio_bus, smi_addr, MDIO_DEVAD_NONE, regAddr);
	rData |= regVal;

	return rData;
}

static int yt9215s_smi_write(struct phy_device *phydev, int devad,
		u32 reg, u32 val)
{
	struct yt9215xx_phy_priv *priv = phydev->priv;
	struct mii_dev *mdio_bus = priv->mdio_bus;
	int smi_addr = priv->smi_addr;
	u16 regVal;
	u8 regAddr;
	u8 switchId;

	switchId = (devad == MDIO_DEVAD_NONE) ? 0 : devad;
	regAddr = (switchId << 2) | (REG_ADDR_BIT1_ADDR << 1) | REG_ADDR_BIT0_WRITE;
	/* Set reg_addr[31:16] */
	regVal = (reg >> 16) & 0xffff;
	mdio_bus->write(mdio_bus, smi_addr, MDIO_DEVAD_NONE, regAddr, regVal);

	/* Set reg_addr[15:0] */
	regVal = reg & 0xffff;
	mdio_bus->write(mdio_bus, smi_addr, MDIO_DEVAD_NONE, regAddr, regVal);

	/* Write Data [31:16] out */
	regAddr = (switchId << 2)| (REG_ADDR_BIT1_DATA << 1)| REG_ADDR_BIT0_WRITE;
	regVal = (val >> 16) & 0xffff;
	mdio_bus->write(mdio_bus, smi_addr, MDIO_DEVAD_NONE, regAddr, regVal);

	/* Write Data [15:0] out */
	regVal = val & 0xffff;
	mdio_bus->write(mdio_bus, smi_addr, MDIO_DEVAD_NONE, regAddr, regVal);

	return 0;
}

static int yt9215s_phy_wait_busy(struct phy_device *phydev, int devad)
{
	u32 regVal, wait_count;

	yt9215s_smi_write(phydev, devad, INT_IF_ACCESS_FRAME_CTRL, 1);
	while (wait_count < MAX_BUSYING_WAIT_TIME) {
		regVal = yt9215s_smi_read(phydev, devad, INT_IF_ACCESS_FRAME_CTRL);
		if (regVal == 0)
			return 0;

		wait_count++;
	}

	debug("%s wait phy busy timeout\n", __func__);
	return -1;
}

/* Wrapper function to make calls to phy_read_indirect simpler */
static int yt9215s_phy_read_indirect(struct mii_dev *smi_wrapper, int addr,
		int devad, int reg)
{
	struct phy_device *phydev = (struct phy_device *)smi_wrapper->priv;
	u32 regVal;
	int ret;

	regVal = yt9215s_smi_read(phydev, devad, INT_IF_ACCESS_ADDR_CTRL);
	regVal &= 0xFC00FFF1;
	regVal |= ((addr & 0x1f) << 21) | ((reg & 0x1f) << 16) | (2 << 2);
	yt9215s_smi_write(phydev, devad, INT_IF_ACCESS_ADDR_CTRL, regVal);

	ret = yt9215s_phy_wait_busy(phydev, devad);
	if (ret)
		return ret;

	regVal = yt9215s_smi_read(phydev, devad, INT_IF_ACCESS_DATA_1_ADDR);
	debug("%s read phy:%u reg:%d val:0x%x\n", __func__, addr, reg, regVal);
	return regVal;
}

/* Wrapper function to make calls to phy_read_indirect simpler */
static int yt9215s_phy_write_indirect(struct mii_dev *smi_wrapper, int addr,
		int devad, int reg, u16 val)
{
	struct phy_device *phydev = (struct phy_device *)smi_wrapper->priv;
	u32 regVal;

	regVal = yt9215s_smi_read(phydev, devad, INT_IF_ACCESS_ADDR_CTRL);
	regVal &= 0xFC00FFF1;
	regVal |= ((addr & 0x1f) << 21) | ((reg & 0x1f) << 16) | (1 << 2);
	yt9215s_smi_write(phydev, devad, INT_IF_ACCESS_ADDR_CTRL, regVal);
	yt9215s_smi_write(phydev, devad, INT_IF_ACCESS_DATA_0_ADDR, val);

	debug("%s write phy:%u reg:%d val:0x%x\n", __func__, addr, reg, val);
	return yt9215s_phy_wait_busy(phydev, devad);
}

static int yt9215xx_get_switch_id(struct phy_device *phydev)
{
	struct yt9215xx_phy_priv *priv = phydev->priv;
	int ret;

	ret = yt9215s_smi_read(phydev, 0, REG_ADDR_CHIP_ID);
	if (ret == 0 || ret == 0xffffffff)
		return -1;

	priv->id = ret;
	return 0;
}

static int yt9215xx_probe(struct phy_device *phydev)
{
	struct yt9215xx_phy_priv *priv;
	struct mii_dev *smi_wrapper;
	int ret;

	priv = malloc(sizeof(*priv));
	if (!priv)
		return -ENOMEM;

	memset(priv, 0, sizeof(*priv));

	/*
	 * This device requires indirect reads/writes to the PHY registers
	 * which the generic PHY code can't handle.  Make a wrapper MII device
	 * to handle reads/writes
	 */
	smi_wrapper = mdio_alloc();
	if (!smi_wrapper) {
		free(priv);
		return -ENOMEM;
	}

	/*
	 * Store the mdio bus in the private data, as we are going to replace
	 * the bus with the wrapper bus
	 */
	priv->mdio_bus = phydev->bus;

	/*
	 * Store the smi bus address in private data.  This lets us use the
	 * phydev addr field for device address instead, as the genphy code
	 * expects.
	 */
	priv->smi_addr = phydev->addr;

	/*
	 * Store the phy_device in the wrapper mii device. This lets us get it
	 * back when genphy functions call phy_read/phy_write.
	 */
	smi_wrapper->priv = phydev;
	snprintf(smi_wrapper->name, MDIO_NAME_LEN, "mdio-phy@%llu",
			(phys_addr_t)phydev->bus->priv);
	smi_wrapper->read = yt9215s_phy_read_indirect;
	smi_wrapper->write = yt9215s_phy_write_indirect;

	/* Replace the bus with the wrapper device */
	phydev->bus = smi_wrapper;
	/* Default set phy_read/phy_write port id to 0 */
	phydev->addr = 0;

	phydev->priv = priv;

	ret = yt9215xx_get_switch_id(phydev);
	if (ret < 0)
		return ret;

	printf("%s ID 0x%x\n", __func__, priv->id);

	switch (priv->id) {
	case PORT_SWITCH_ID_9215S:
		priv->port_count = 5;
		priv->cpu_port = 5;
		break;
	default:
		free(priv);
		printf("%s Unknown Switch ID 0x%x\n", __func__, priv->id);
		return -ENODEV;
	}

	ret = mdio_register(smi_wrapper);
	if (ret)
		printf("Failed to register SMI bus\n");

	return 0;
}

static int yt9215xx_phy_config(struct phy_device *phydev)
{
	yt9215s_smi_write(phydev, MDIO_DEVAD_NONE, 0x80394, 0x0);
	yt9215s_smi_write(phydev, MDIO_DEVAD_NONE, 0x80408, 0x4184108);
	yt9215s_smi_write(phydev, MDIO_DEVAD_NONE, 0x80028, 0x1);
	yt9215s_smi_write(phydev, MDIO_DEVAD_NONE, 0x8008c, 0x27c);
	//set port isolation to avoid unexpected IP address assignment
	yt9215s_smi_write(phydev, MDIO_DEVAD_NONE, 0x180294, 0xf);
	yt9215s_smi_write(phydev, MDIO_DEVAD_NONE, 0x180298, 0xf);
	yt9215s_smi_write(phydev, MDIO_DEVAD_NONE, 0x18029c, 0xf);
	yt9215s_smi_write(phydev, MDIO_DEVAD_NONE, 0x1802a0, 0xf);
	/* yt9215s phy reset must set reg reset bit with autoneg bit,
	 * or it will not recovery to autoneg mode after reset
	 */
	yt9215s_phy_write_indirect(phydev->bus, 0, MDIO_DEVAD_NONE, 0, 0x1140);
	return 0;
}

static int yt9215xx_phy_startup(struct phy_device *phydev)
{
	struct yt9215xx_phy_priv *priv = phydev->priv;
	int port;
	int res;

	for (port = 0; port < priv->port_count; port++) {
		phydev->addr = port;

		res = genphy_startup(phydev);
		if (res == 0)
			break;
	}

	/* Since we are connected directly to the switch,
	 * we cannot be dependent on the user-facing port
	 * settings (e.g: 100Mbits/sec would not work here)
	 */
	phydev->speed = SPEED_2500;
	phydev->duplex = DUPLEX_FULL;
	phydev->link = 1;

	return 0;
}

static struct phy_driver yt9215s_driver = {
	.name		= "Motorcomm YT9215S",
	.uid 		= 0x01e04281,
	.mask		= 0x0fffffff,
	.features	= PHY_GBIT_FEATURES,
	.probe		= yt9215xx_probe,
	.config		= yt9215xx_phy_config,
	.startup 	= yt9215xx_phy_startup,
	.shutdown	= &genphy_shutdown,
};

int phy_yt9215xx_init(void)
{
	return phy_register(&yt9215s_driver);
}

/*
 * Cause the weak get_phy_id definition is overloading,
 * we need to use standard functions to read the phy register
 */
int generic_get_phy_id(struct mii_dev *bus, int addr, int devad, u32 *phy_id)
{
	int phy_reg;

	/*
	 * Grab the bits from PHYIR1, and put them
	 * in the upper half
	 */
	phy_reg = bus->read(bus, addr, devad, MII_PHYSID1);

	if (phy_reg < 0)
		return -EIO;

	*phy_id = (phy_reg & 0xffff) << 16;

	/* Grab the bits from PHYIR2, and put them in the lower half */
	phy_reg = bus->read(bus, addr, devad, MII_PHYSID2);

	if (phy_reg < 0)
		return -EIO;

	*phy_id |= (phy_reg & 0xffff);

	return 0;
}

/*
 * Overload weak get_phy_id definition since we need non-standard functions
 * to read PHY registers
 */
int get_phy_id(struct mii_dev *bus, int smi_addr, int devad, u32 *phy_id)
{
	struct phy_device temp_phy;
	struct yt9215xx_phy_priv temp_priv;
	struct mii_dev temp_mii;
	int ret;

	/*
	 * Buid temporary data structures that the chip reading code needs to
	 * read the ID
	 */
	temp_priv.mdio_bus = bus;
	temp_priv.smi_addr = smi_addr;
	temp_phy.priv = &temp_priv;
	temp_mii.priv = &temp_phy;

	ret = yt9215s_phy_read_indirect(&temp_mii, 0, devad, MII_PHYSID1);
	if (ret < 0)
		goto generic;

	*phy_id = ret << 16;

	ret = yt9215s_phy_read_indirect(&temp_mii, 0, devad, MII_PHYSID2);
	if (ret < 0)
		goto generic;

	*phy_id |= (ret & 0xffff);

	return 0;

generic:
	return generic_get_phy_id(bus, smi_addr, devad, phy_id);
}

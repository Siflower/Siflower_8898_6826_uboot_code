#include "gmac_mdio.h"
#include "lif_reg.h"

extern struct XGmacContext g_gmac_context;
static int32_t g_phy_addr = 0xff;
static int32_t g_phydev_addr[5] = {0xff, 0xff, 0xff, 0xff, 0xff};

#define MDIO_SEL(macid) (0x08000000 + 0x4000 * macid)


void gpio_manager_reset(void)
{
    // gpio manager soft reset
    writel(0xff, 0x0ce0a000);
    writel(0x00, 0x0ce0a000);

    // gpio clk gating enable (default 0x00 set 0xff means enable gating )
    writel(0x00, 0x0ce0a004);
    writel(0xff, 0x0ce0a004);

    // gpio soft boe, config channel enbale(bit0:reg  bit1:bus) (default 0x00)
    writel(0x00, 0x0ce0a00c);
    writel(0xff, 0x0ce0a00c);
}

int32_t gwait_phy_rw_not_busy(uintptr_t macid)
{
    int32_t reg = CSR_REG_READ(MDIO_SEL(macid) + REG_GMAC_GmiiAddr);
    // wait for GMII Register GB is not busy
    while (reg & GMII_ADDR_MASK_GB) {
        reg = CSR_REG_READ(MDIO_SEL(macid) + REG_GMAC_GmiiAddr);
    }
    return reg;
}

int read_phy_reg_direct(uintptr_t macid, int phy_addr, int phy_reg)
{
    int value = gwait_phy_rw_not_busy(macid);
    // clear the data first
    writel(0xffffffff, MDIO_SEL(macid) + REG_GMAC_GmiiData);
    // set address flag
    value = (value & (~GMII_ADDR_MASK_GR)) |
            ((phy_reg << 6) & GMII_ADDR_MASK_GR);
    // set phy addr
    value = (value & (~GMII_ADDR_MASK_PA)) |
            ((phy_addr << 11) & GMII_ADDR_MASK_PA);
    // set read flag
    value = value & (~GMII_ADDR_VALUE_GW_WRITE);
    // set GB flag to indica is busy now
    value = value | GMII_ADDR_MASK_GB;
    writel(value, MDIO_SEL(macid) + REG_GMAC_GmiiAddr);
    // wait for complete
    gwait_phy_rw_not_busy(macid);
    return readl(MDIO_SEL(macid) + REG_GMAC_GmiiData) & GMII_DATA_MASK;
}

int read_phy_reg(uintptr_t macid, int phy_reg)
{
    int read_value = read_phy_reg_direct(macid, g_phydev_addr[macid], phy_reg);
    return read_value;
}

void write_phy_reg_direct(uintptr_t macid, int phy_addr, int phy_reg, int value)
{
    int addr_value = gwait_phy_rw_not_busy(macid);
    // prepare data for register 5
    writel(value & GMII_DATA_MASK, MDIO_SEL(macid) + REG_GMAC_GmiiData);
    // set address flag
    addr_value = (addr_value & (~GMII_ADDR_MASK_GR)) |
        ((phy_reg << 6) & GMII_ADDR_MASK_GR);
    // set phy addr
    addr_value = (addr_value & (~GMII_ADDR_MASK_PA)) |
        ((phy_addr << 11) & GMII_ADDR_MASK_PA);
    // set write flag
    addr_value = addr_value  | GMII_ADDR_VALUE_GW_WRITE;
    // set GB flag to indica is busy now
    addr_value = addr_value | GMII_ADDR_MASK_GB;
    writel(addr_value, MDIO_SEL(macid) + REG_GMAC_GmiiAddr);
    // wait for finish
    gwait_phy_rw_not_busy(macid);
}

int32_t xgmac_wait_phy_rw_not_busy(int phy_addr)
{
    int32_t reg = CSR_REG_READ(XGMAC_ADDR_BASE + XGMAC_MDIO_DATA);
    // wait for GMII Register GB is not busy
    while (reg & XGMAC_MDIO_DATA_SBUSY) {
        reg = CSR_REG_READ(XGMAC_ADDR_BASE + XGMAC_MDIO_DATA);
    }
    return reg;
}


int xgmac_read_phy_reg_direct(int phy_addr, int phy_reg)
{
    xgmac_wait_phy_rw_not_busy(phy_addr);

	int addr_value = FIELD_PREP(XGMAC_MDIO_ADDR_PA, phy_addr) | FIELD_PREP(XGMAC_MDIO_ADDR_RA, phy_reg);
	writel(addr_value, XGMAC_ADDR_BASE + XGMAC_MDIO_ADDR);
	writel(XGMAC_MDIO_DATA_SBUSY | XGMAC_MDIO_DATA_CMD_RD, XGMAC_ADDR_BASE + XGMAC_MDIO_DATA);
    xgmac_wait_phy_rw_not_busy(phy_addr);
    return readl((uintptr_t)(XGMAC_ADDR_BASE + XGMAC_MDIO_DATA)) & XGMAC_MDIO_DATA_SDATA;
}

void xgmac_write_phy_reg_direct(int phy_addr, int phy_reg, int value)
{
    int addr_value = xgmac_wait_phy_rw_not_busy(phy_addr);
	addr_value = FIELD_PREP(XGMAC_MDIO_ADDR_PA, phy_addr) | FIELD_PREP(XGMAC_MDIO_ADDR_RA, phy_reg);
	writel(addr_value, XGMAC_ADDR_BASE + XGMAC_MDIO_ADDR);
	writel(value | XGMAC_MDIO_DATA_SBUSY | XGMAC_MDIO_DATA_CMD_WR, XGMAC_ADDR_BASE + XGMAC_MDIO_DATA);

    // wait for finish
    xgmac_wait_phy_rw_not_busy(phy_addr);
}

void phy_scan(bool is_xgmac_mdio)
{
    unsigned int phy_no = 0, addr_index = 0;
    unsigned int phy_id = 0, phy_id1 = 0, phy_id2 = 0;

    for (phy_no = 0; phy_no < 5; phy_no++) {
        for (addr_index = 0; addr_index < 32; addr_index++) {
            if (is_xgmac_mdio) {
                phy_id1 = xgmac_read_phy_reg_direct(addr_index, MII_PHYSID1) & 0xffff;
                phy_id2 = xgmac_read_phy_reg_direct(addr_index, MII_PHYSID2) & 0xffff;
            } else {
                phy_id1 = read_phy_reg_direct(phy_no, addr_index, MII_PHYSID1) & 0xffff;
                phy_id2 = read_phy_reg_direct(phy_no, addr_index, MII_PHYSID2) & 0xffff;
            }
            phy_id = phy_id1 | (phy_id2 << 16);
            if ((phy_id & 0x1fffffff) != 0x1fffffff) {
                // TODO: fpga has no phy0 and phy4, but scan get phy_id 0xffff0000
                if (phy_id1 == 0xffff || phy_id2 == 0xffff)
                    continue;
                if (phy_id1 == 0x0 || phy_id2 == 0x0)
                    continue;
                if (is_xgmac_mdio) {
                    g_phy_addr = addr_index;
                    printf("use xgmac mdio scan phyaddr:%u success, phy_id:0x%x\n", addr_index, phy_id);
                    return;
                } else {
                    g_phydev_addr[phy_no] = addr_index;
                    printf("use rgmii mdio scan phy[%u] phyaddr:%u success, phy_id:0x%x\n", phy_no, addr_index, phy_id);
                }
                break;
            }
        }
    }
}

static int gmac_sf_pad_set_func(uintptr_t index, pad_func func)
{
	u32 tmp;

	if(index > PAD_INDEX_MAX)
		return -1;
	switch (func) {
	// write 0,0,0 to fmux_sel_reg mode_bit1_reg mode_bit0_reg
	case FUNC0:
		// set oen 0
		tmp = readl(PAD_INDEX_REG(index));
		tmp &= ~(0x1 << SW_OEN_REG);
		writel(tmp, PAD_INDEX_REG(index));

		tmp = readl(PAD_INDEX_REG(index));
		tmp |=(0x1 << FUNC_SW_SEL_REG);
		writel(tmp, PAD_INDEX_REG(index));

		tmp = readl(PAD_INDEX_REG(index));
		tmp |=(0x1 << SW_IE_REG);
		writel(tmp, PAD_INDEX_REG(index));

		tmp = readl(PAD_INDEX_REG(index));
		tmp &= ~(0x7 << 0);
		writel(tmp, PAD_INDEX_REG(index));
		break;
	case FUNC1:
		tmp = readl(PAD_INDEX_REG(index));
		tmp &= ~(0x1 << SW_OEN_REG);
		writel(tmp, PAD_INDEX_REG(index));

		tmp = readl(PAD_INDEX_REG(index));
		tmp |=(0x1 << FUNC_SW_SEL_REG);
		writel(tmp, PAD_INDEX_REG(index));

		tmp = readl(PAD_INDEX_REG(index));
		tmp |=(0x1 << SW_IE_REG);
		writel(tmp, PAD_INDEX_REG(index));

		tmp = readl(PAD_INDEX_REG(index));
		tmp &= ~(0x3 << 1);
		tmp |=(0x1 << 0);
		writel(tmp, PAD_INDEX_REG(index));
		break;
	case FUNC2:
		tmp = readl(PAD_INDEX_REG(index));
		tmp &= ~(0x1 << SW_OEN_REG);
		writel(tmp, PAD_INDEX_REG(index));

		tmp = readl(PAD_INDEX_REG(index));
		tmp |=(0x1 << FUNC_SW_SEL_REG);
		writel(tmp, PAD_INDEX_REG(index));

		tmp = readl(PAD_INDEX_REG(index));
		tmp |=(0x1 << SW_IE_REG);
		writel(tmp, PAD_INDEX_REG(index));

		tmp = readl(PAD_INDEX_REG(index));
		tmp &= ~(0x3 << 1);
		tmp |=(0x2 << 0);
		writel(tmp, PAD_INDEX_REG(index));
		break;
	case FUNC3:
		tmp = readl(PAD_INDEX_REG(index));
		tmp &= ~(0x1 << SW_OEN_REG);
		writel(tmp, PAD_INDEX_REG(index));

		tmp = readl(PAD_INDEX_REG(index));
		tmp |=(0x1 << FUNC_SW_SEL_REG);
		writel(tmp, PAD_INDEX_REG(index));

		tmp = readl(PAD_INDEX_REG(index));
		tmp |=(0x1 << SW_IE_REG);
		writel(tmp, PAD_INDEX_REG(index));

		tmp = readl(PAD_INDEX_REG(index));
		tmp &= ~(0x3 << 1);
		tmp |=(0x3 << 0);
		writel(tmp, PAD_INDEX_REG(index));
		break;

	case GPIO_INPUT:
		// set oen 1
		tmp = readl(PAD_INDEX_REG(index));
		tmp |=(0x1 << SW_OEN_REG);
		writel(tmp, PAD_INDEX_REG(index));

		//set ie 1
		tmp = readl(PAD_INDEX_REG(index));
		tmp |=(0x1 << SW_IE_REG);
		writel(tmp, PAD_INDEX_REG(index));

		// write 1 to fmux_sel_reg
		tmp = readl(PAD_INDEX_REG(index));
		tmp |=(0x1 << FMUX_SEL_REG);
		writel(tmp, PAD_INDEX_REG(index));

		tmp = readl(PAD_INDEX_REG(index));
		writeb(1, GPIO_DIR(index));
		break;
	case GPIO_OUTPUT:
		// set oen 0
		tmp = readl(PAD_INDEX_REG(index));
		tmp &= ~(0x1 << SW_OEN_REG);
		writel(tmp, PAD_INDEX_REG(index));

		//set ie 0
		tmp = readl(PAD_INDEX_REG(index));
		tmp &=~ (0x1 << SW_IE_REG);
		writel(tmp, PAD_INDEX_REG(index));

		// write 1 to fmux_sel_reg
		tmp = readl(PAD_INDEX_REG(index));
		tmp |=(0x1 << FMUX_SEL_REG);
		writel(tmp, PAD_INDEX_REG(index));

		tmp = readl(PAD_INDEX_REG(index));
		writeb(0, GPIO_DIR(index));
		break;
	default:
		return -1;
	}

	return 0;
}

static int gmac_sf_pad_set_value(uintptr_t index, pad_output_level level)
{
	if (index > PAD_INDEX_MAX)
		return -1;
	writeb(level, GPIO_WDAT(index));

	return 0;
}



int sf_fpga_phy_init(void)
{
    unsigned int phy_no = 0, i = 0, value = 0;
    unsigned int mscr = 0, phy_ctrl_write = 0;

    // trigger marvell phy hw reset
    for (i = 38; i <= 40; i++) {
        gmac_sf_pad_set_func(i, GPIO_OUTPUT);
        gmac_sf_pad_set_value(i, LOW_LEVEL);
        mydl(10000);
        gmac_sf_pad_set_value(i, HIGH_LEVEL);
    }

    phy_scan(0); // use rgmii mdio scan
    phy_scan(1); // use xgmac mdio scan


    // init fpga rgmii phys
    for (phy_no = 0; phy_no < 5; phy_no++){
        if (g_phydev_addr[phy_no] == 0xff)
            continue;
        // switch to MSCR page
        write_phy_reg_direct(phy_no, g_phydev_addr[phy_no], MII_MARVELL_PHY_PAGE, MII_MARVELL_MSCR_PAGE);
        // rx/tx delay
        mscr = read_phy_reg_direct(phy_no, g_phydev_addr[phy_no], MII_88E1121_PHY_MSCR_REG);
        mscr &= ~MII_88E1121_PHY_MSCR_DELAY_MASK;
        // 2'b00: no delay
        // 2'b01: tx delay
        // 2'b10: rx delay
        // 2'b11: rx and tx delay
        //mscr |= ((phy_no == 4 ? 0x0 : 0x1) << 4);
        //mscr |= (3 << 4);
        mscr &= ~(BMCR_SPEED100 | BMCR_SPEED1000);
        //mscr |= BMCR_SPEED100 | (1 << 14);
        mscr |= BMCR_SPEED100;
        write_phy_reg_direct(phy_no, g_phydev_addr[phy_no], MII_88E1121_PHY_MSCR_REG, mscr);
        value = read_phy_reg_direct(phy_no, g_phydev_addr[phy_no], MII_88E1121_PHY_MSCR_REG) & 0xffff;
        printf("read page2 reg21: 0x%04x\r\n", value);

        // switch to COPPER page
        write_phy_reg_direct(phy_no, g_phydev_addr[phy_no], MII_MARVELL_PHY_PAGE, MII_MARVELL_COPPER_PAGE);
        // set speed and duplex, soft reset phy
        phy_ctrl_write = BMCR_SPEED100 | BMCR_FULLDPLX;
        write_phy_reg_direct(phy_no, g_phydev_addr[phy_no], MII_BMCR, BMCR_RESET);
        u64 count = 0;
        while ((read_phy_reg_direct(phy_no, g_phydev_addr[phy_no], MII_BMCR)) & BMCR_RESET) {
            if (count++ > 10000) {
                printf("phy reset timeout\r\n");
                return -1;
            }
        }
        //phy_ctrl_write |= BMCR_LOOPBACK;
        // set phy speed
        write_phy_reg_direct(phy_no, g_phydev_addr[phy_no], MII_BMCR, phy_ctrl_write);
        //c_delay_us(0,1);

        // to test phy reg read
        value = read_phy_reg_direct(phy_no, g_phydev_addr[phy_no], MII_PHYSID1) & 0xffff;
        printf("value : 0x%04x\r\n", value);
        value = read_phy_reg_direct(phy_no, g_phydev_addr[phy_no], MII_PHYSID2) & 0xffff;
        printf("value : 0x%04x\r\n", value);
        value = read_phy_reg_direct(phy_no, g_phydev_addr[phy_no], MII_BMCR) & 0xffff;
        printf("value : 0x%04x\r\n", value);
        value = read_phy_reg_direct(phy_no, g_phydev_addr[phy_no], MII_BMSR) & 0xffff;
        printf("value : 0x%04x\r\n", value);
    }

    // init fpga xgmac phys
    if (g_phy_addr != 0xff) {
        // switch to MSCR page
        xgmac_write_phy_reg_direct(g_phy_addr,MII_MARVELL_PHY_PAGE, MII_MARVELL_MSCR_PAGE);
        // rx/tx delay
        mscr = xgmac_read_phy_reg_direct(g_phy_addr,MII_88E1121_PHY_MSCR_REG);
        mscr &= ~MII_88E1121_PHY_MSCR_DELAY_MASK;
        // 2'b00: no delay
        // 2'b01: tx delay
        // 2'b10: rx delay
        // 2'b11: rx and tx delay
        //mscr |= ((i == 4 ? 0x0 : 0x1) << 4);
        //mscr |= (3 << 4);
        mscr &= ~(BMCR_SPEED100 | BMCR_SPEED1000);
        //mscr |= BMCR_SPEED100 | (1 << 14);
        mscr |= BMCR_SPEED100;
        xgmac_write_phy_reg_direct(g_phy_addr,MII_88E1121_PHY_MSCR_REG, mscr);
        value = xgmac_read_phy_reg_direct(g_phy_addr,MII_88E1121_PHY_MSCR_REG) & 0xffff;
        printf("read page2 reg21: 0x%04x\r\n", value);

        // switch to COPPER page
        xgmac_write_phy_reg_direct(g_phy_addr,MII_MARVELL_PHY_PAGE, MII_MARVELL_COPPER_PAGE);
        // set speed and duplex, soft reset phy
        phy_ctrl_write = BMCR_SPEED100 | BMCR_FULLDPLX;
        xgmac_write_phy_reg_direct(g_phy_addr,MII_BMCR, BMCR_RESET);
        u64 count = 0;
        while ((xgmac_read_phy_reg_direct(g_phy_addr,MII_BMCR)) & BMCR_RESET) {
            if (count++ > 10000) {
                printf("phy reset timeout\r\n");
                return -1;
            }
        }
        //phy_ctrl_write |= BMCR_LOOPBACK;
        // set phy speed
        xgmac_write_phy_reg_direct(g_phy_addr,MII_BMCR, phy_ctrl_write);
        //c_delay_us(0,1);

        // to test phy reg read
        value = xgmac_read_phy_reg_direct(g_phy_addr,MII_PHYSID1) & 0xffff;
        printf("value : 0x%04x\r\n", value);
        value = xgmac_read_phy_reg_direct(g_phy_addr,MII_PHYSID2) & 0xffff;
        printf("value : 0x%04x\r\n", value);
        value = xgmac_read_phy_reg_direct(g_phy_addr,MII_BMCR) & 0xffff;
        printf("value : 0x%04x\r\n", value);
        value = xgmac_read_phy_reg_direct(g_phy_addr,MII_BMSR) & 0xffff;
        printf("value : 0x%04x\r\n", value);
    }

    return 0;
}

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <linux/io.h>
#include <linux/types.h>
#include "lif_common.h"
#include "../../../../fbl/common/pad.h"
#include "../../../../fbl/common/sys_manager.h"

#define MII_BMCR        0x00
#define BMCR_SPEED1000          0x0040  /* MSB of Speed (1000)         */
#define BMCR_CTST               0x0080  /* Collision test              */
#define BMCR_FULLDPLX           0x0100  /* Full duplex                 */
#define BMCR_ANRESTART          0x0200  /* Auto negotiation restart    */
#define BMCR_ISOLATE            0x0400  /* Isolate data paths from MII */
#define BMCR_PDOWN              0x0800  /* Enable low power state      */
#define BMCR_ANENABLE           0x1000  /* Enable auto negotiation     */
#define BMCR_SPEED100           0x2000  /* Select 100Mbps              */
#define BMCR_LOOPBACK           0x4000  /* TXD loopback bits           */
#define BMCR_RESET              0x8000  /* Reset to default state      */
#define BMCR_SPEED10            0x0000  /* Select 10Mbps               */

#define MII_BMSR                0x01    /* Basic mode status register  */
#define BMSR_ERCAP              0x0001  /* Ext-reg capability          */
#define BMSR_JCD                0x0002  /* Jabber detected             */
#define BMSR_LSTATUS            0x0004  /* Link status                 */
#define BMSR_ANEGCAPABLE        0x0008  /* Able to do auto-negotiation */
#define BMSR_RFAULT             0x0010  /* Remote fault detected       */
#define BMSR_ANEGCOMPLETE       0x0020  /* Auto-negotiation complete   */
#define BMSR_RESV               0x00c0  /* Unused...                   */
#define BMSR_ESTATEN            0x0100  /* Extended Status in R15      */
#define BMSR_100HALF2           0x0200  /* Can do 100BASE-T2 HDX       */
#define BMSR_100FULL2           0x0400  /* Can do 100BASE-T2 FDX       */
#define BMSR_10HALF             0x0800  /* Can do 10mbps, half-duplex  */
#define BMSR_10FULL             0x1000  /* Can do 10mbps, full-duplex  */
#define BMSR_100HALF            0x2000  /* Can do 100mbps, half-duplex */
#define BMSR_100FULL            0x4000  /* Can do 100mbps, full-duplex */
#define BMSR_100BASE4           0x8000  /* Can do 100mbps, 4k packets  */

#define MII_PHYSID1     0x02
#define MII_PHYSID2     0x03

#define MII_MARVELL_PHY_PAGE            22
#define MII_MARVELL_COPPER_PAGE         0x00
#define MII_MARVELL_MSCR_PAGE           0x02

#define MII_88E1121_PHY_MSCR_REG        21
#define MII_88E1121_PHY_MSCR_RX_DELAY   (1 << 5)
#define MII_88E1121_PHY_MSCR_TX_DELAY   (1 << 4)
#define MII_88E1121_PHY_MSCR_DELAY_MASK (0x3 << 4)

#define GMII_ADDR_MASK_GB (1 << 0)
#define GMII_ADDR_VALUE_GW_WRITE  (1 << 1)
//#define GMII_ADDR_MASK_CR (0xf << 2)
#define GMII_ADDR_MASK_GR (0x1f << 6)
#define GMII_ADDR_MASK_PA (0x1f << 11)
#define GMII_DATA_MASK  0xffff

void gpio_manager_reset(void);
int32_t gwait_phy_rw_not_busy(uintptr_t macid);
int read_phy_reg_direct(uintptr_t macid, int phy_addr, int phy_reg);
int read_phy_reg(uintptr_t macid, int phy_reg);
void write_phy_reg(uintptr_t macid, int phy_reg, int value);
int sf_fpga_phy_init(void);

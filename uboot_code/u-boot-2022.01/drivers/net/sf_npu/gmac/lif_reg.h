#ifndef _LIF_REG_H_
#define _LIF_REG_H_

#include "lif_common.h"

#define DUT_ADDRESS             0x0CE0002C
//#define DDR_BASE_ADDR           0xa0000000
//#define DDR_BASE_PHY_ADDR       0x20000000
#define LIF_BASE_ADDR           0x08000000
#define LIF_SYSTEM              0x0CE01800
#define GMA0_BASE_ADDR          (LIF_BASE_ADDR + 0x0000)
#define GMA1_BASE_ADDR          (LIF_BASE_ADDR + 0x4000)
#define GMA2_BASE_ADDR          (LIF_BASE_ADDR + 0x8000)
#define GMA3_BASE_ADDR          (LIF_BASE_ADDR + 0xc000)
#define GMA4_BASE_ADDR          (LIF_BASE_ADDR + 0x10000)
#define DWCXG_XGMAC_BASE	    (LIF_BASE_ADDR + 0x14000)
#define HIF_DMA_ADDR_BASE       (LIF_BASE_ADDR + 0x18000 + 0x1000)  //gamc dma
#define XGMAC_DMA_ADDR_BASE     (LIF_BASE_ADDR + 0x18000)   //xgmac dma
#define HIF_MTL_ADDR_BASE       (LIF_BASE_ADDR + 0x18000)

#define GLOBA_DEBUG_ADDRESS     0  //????


//xgmac register
#define DWCXG_CORE_Registers						          (DWCXG_XGMAC_BASE + 0x0000)
#define DWCXG_MTL_Registers						              (HIF_MTL_ADDR_BASE + 0x1000)
#define DWCXG_MTL_TCQ0_Registers				              (HIF_MTL_ADDR_BASE + 0x1100)
#define DWCXG_MTL_Q0_Registers				                  (HIF_MTL_ADDR_BASE + 0x1180)

#define REG_DWCXG_MAC_TX_Configuration    	                  (DWCXG_CORE_Registers + 0x000)
#define REG_DWCXG_MAC_RX_Configuration    	                  (DWCXG_CORE_Registers + 0x004)
#define REG_DWCXG_MAC_Packet_Filter      	                  (DWCXG_CORE_Registers + 0x008)
#define REG_DWCXG_MAC_WD_JB_Timeout                           (DWCXG_CORE_Registers + 0x00c)
#define REG_DWCXG_MAC_Interrupt_Enable                        (DWCXG_CORE_Registers + 0x0d4)
#define DWCXG_GMAC_PmtCtrlStatus                              (DWCXG_CORE_Registers + 0x0c0)
#define REG_DWCXG_Addr0High    	                              (DWCXG_CORE_Registers + 0x300)
#define REG_DWCXG_Addr0Low    	                              (DWCXG_CORE_Registers + 0x304)
#define REG_DWCXG_MAC_Indir_Access_Ctrl    	                  (DWCXG_CORE_Registers + 0x700)    //MAC_Indir_Access_Ctrl
#define REG_DWCXG_MAC_Q0_TX_Flow_Control      	              (DWCXG_CORE_Registers + 0x070)    //MAC_Q0_Tx_Flow_Ctrl
#define REG_DWCXG_MAC_RX_Flow_Control      	                  (DWCXG_CORE_Registers + 0x090)
#define REG_DWCXG_MAC_Version    	                          (DWCXG_CORE_Registers + 0x110)    //MAC_Version
#define REG_DWCXG_MAC_Debug    	                              (DWCXG_CORE_Registers + 0x114)    //MAC_Debug
#define REG_DWCXG_MAC_Extended_Configuration                  (DWCXG_CORE_Registers + 0x140)
#define REG_DWCXG_MDIO_Single_Command_Address                 (DWCXG_CORE_Registers + 0x200)
#define REG_DWCXG_MDIO_Single_Command_Control_Data            (DWCXG_CORE_Registers + 0x204)
#define REG_DWCXG_MDIO_Continuous_Write_Address               (DWCXG_CORE_Registers + 0x208)
#define REG_DWCXG_MDIO_Continuous_Write_Data                  (DWCXG_CORE_Registers + 0x20c)
#define REG_DWCXG_MDIO_Continuous_Scan_Port_Enable            (DWCXG_CORE_Registers + 0x210)
#define REG_DWCXG_MDIO_Interrupt_Status                       (DWCXG_CORE_Registers + 0x214)
#define REG_DWCXG_MDIO_Interrupt_Enable                       (DWCXG_CORE_Registers + 0x218)
#define REG_DWCXG_MDIO_Port_Connect_Disconnect_Status         (DWCXG_CORE_Registers + 0x21c)
#define REG_DWCXG_MDIO_Clause_22_Port                         (DWCXG_CORE_Registers + 0x220)
#define REG_DWCXG_MDIO_Port_Nx4_Indirect_Control              (DWCXG_CORE_Registers + 0x224)
#define REG_DWCXG_MDIO_PortNx4P0_Device_In_Use                (DWCXG_CORE_Registers + 0x230)
#define REG_DWCXG_MDIO_PortNx4P0_Link_Status                  (DWCXG_CORE_Registers + 0x234)
#define REG_DWCXG_MAC_Auxiliary_Control                       (DWCXG_CORE_Registers + 0xd40)
#define REG_DWCXG_MAC_Timestamp_Control                       (DWCXG_CORE_Registers + 0xd00)
#define REG_DWCXG_MAC_Sub_Second_Increment                    (DWCXG_CORE_Registers + 0xd04)
#define REG_DWCXG_MAC_System_Time_Second                      (DWCXG_CORE_Registers + 0xd08)
#define REG_DWCXG_MAC_System_Time_NanoSecond                  (DWCXG_CORE_Registers + 0xd0c)
#define REG_DWCXG_MAC_RxQ_Ctrl0                               (DWCXG_CORE_Registers + 0x0a0)
#define REG_DWCXG_MAC_RxQ_Ctrl1                               (DWCXG_CORE_Registers + 0x0a4)
#define REG_DWCXG_MAC_RxQ_Ctrl2                               (DWCXG_CORE_Registers + 0x0a8)
#define REG_DWCXG_MAC_RxQ_Ctrl3                               (DWCXG_CORE_Registers + 0x0ac)
#define REG_DWCXG_MAC_HW_Feature0                             (DWCXG_CORE_Registers + 0x11c)
#define REG_DWCXG_MAC_HW_Feature1                             (DWCXG_CORE_Registers + 0x120)


#define DWCXG_MTL_Operation_Mode                               (DWCXG_MTL_Registers + 0x000)
#define DWCXG_MTL_Interrupt_Status                             (DWCXG_MTL_Registers + 0x020)
#define DWCXG_MTL_TxQ0_Operation_Mode                          (DWCXG_MTL_TCQ0_Registers + 0x00)
#define DWCXG_MTL_RxQ0_Operation_Mode                          (DWCXG_MTL_TCQ0_Registers + 0x40)      //MTL_RXQ(#0)_Operation_Mode
#define DWCXG_MTL_RXQ0_Flow_Control                            (DWCXG_MTL_TCQ0_Registers + 0x50)      //MTL_RXQ(#0)_Flow_Control
#define DWCXG_MTL_Q0_Interrupt_Enable                          (DWCXG_MTL_TCQ0_Registers + 0x70)
#define DWCXG_MTL_TXQ0_DEBUG                                   (DWCXG_MTL_TCQ0_Registers + 0x08)




//XGMAC DMA
#define REG_XGMAC_DMA_Mode                                       (XGMAC_DMA_ADDR_BASE + 0x3000)
#define REG_XGMAC_DMA_BusMode                                    (XGMAC_DMA_ADDR_BASE + 0x3004)
#define REG_XGMAC_DMA_RxBaseAddr                                 (XGMAC_DMA_ADDR_BASE + 0x311c)
#define REG_XGMAC_DMA_RxTailAddr                                 (XGMAC_DMA_ADDR_BASE + 0x312c)
#define REG_XGMAC_DMA_TxBaseAddr                                 (XGMAC_DMA_ADDR_BASE + 0X3114)
#define REG_XGMAC_DMA_TxTailAddr                                 (XGMAC_DMA_ADDR_BASE + 0X3124)
#define REG_XGMAC_DMA_CH0_TX_Control                             (XGMAC_DMA_ADDR_BASE + 0x3104)
#define REG_XGMAC_DMA_CH0_RX_Control                             (XGMAC_DMA_ADDR_BASE + 0x3108)
#define REG_XGMAC_DMA_CH0_Control                                (XGMAC_DMA_ADDR_BASE + 0x3100)
#define REG_XGMAC_DMA_CH0_TX_Control2                            (XGMAC_DMA_ADDR_BASE + 0x3130)
#define REG_XGMAC_DMA_CH0_RX_Control2                            (XGMAC_DMA_ADDR_BASE + 0x3134)
#define REG_XGMAC_DMA_CH0_Interrupt_Enable                       (XGMAC_DMA_ADDR_BASE + 0x3138)
#define REG_XGMAC_DMA_CH0_Status                                 (XGMAC_DMA_ADDR_BASE + 0x3160)




//GMAC DMA register
#define REG_DWCXG_DMA_BusMode                                    (HIF_DMA_ADDR_BASE + 0x0000)    //CSR0
#define REG_DWCXG_DMA_TxPollDemand                               (HIF_DMA_ADDR_BASE + 0x0004)    //CSR1  Transmit Poll Demand Register
#define REG_DWCXG_DMA_RxPollDemand                               (HIF_DMA_ADDR_BASE + 0x0008)    //CSR2
#define REG_DWCXG_DMA_RxBaseAddr                                 (HIF_DMA_ADDR_BASE + 0x000c)    //CSR3
#define REG_DWCXG_DMA_TxBaseAddr                                 (HIF_DMA_ADDR_BASE + 0X0010)    //CSR4
#define REG_DWCXG_DMA_Status                                     (HIF_DMA_ADDR_BASE + 0x0014)    //CSR5
#define REG_DWCXG_DMA_Control									 (HIF_DMA_ADDR_BASE + 0x0018)		//CSR6
#define REG_DWCXG_DMA_Interrupt									 (HIF_DMA_ADDR_BASE + 0x001c)		//CSR7
#define REG_DWCXG_DMA_MissedFr									 (HIF_DMA_ADDR_BASE + 0x0020)     //CSR8
#define REG_DWCXG_DMA_TxCurrDesc								 (HIF_DMA_ADDR_BASE + 0x0048)	    //CSR18
#define REG_DWCXG_DMA_RxCurrDesc								 (HIF_DMA_ADDR_BASE + 0x004c)
#define REG_DWCXG_DMA_TxCurrAddr								 (HIF_DMA_ADDR_BASE + 0x0050)
#define REG_DWCXG_DMA_RxCurrAddr								 (HIF_DMA_ADDR_BASE + 0x0054)






//gmac register
#define REG_GMAC_Config           0x0000
#define REG_GMAC_FrameFilter      0x0004
#define REG_GMAC_HashHigh         0x0008
#define REG_GMAC_HashLow          0x000C
#define REG_GMAC_GmiiAddr         0x0010
#define REG_GMAC_GmiiData         0x0014
#define REG_GMAC_FlowControl      0x0018    /*  Flow control Register                      */
#define REG_GMAC_Vlan             0x001C    /* VLAN tag Register (IEEE 802.1Q)             */
#define REG_GMAC_Version     	  0x0020    /* GMAC Core Version Register                */
#define REG_GMAC_WakeupAddr  	  0x0028    /* GMAC wake-up frame filter adrress reg     */
#define REG_GMAC_PmtCtrlStatus    0x002C    /* PMT control and status register           */
#define REG_GMAC_InterruptStatus  0x0038    /* Mac Interrupt ststus register	       */
#define REG_GMAC_InterruptMask    0x003C    /* Mac Interrupt Mask register	       */
#define REG_GMAC_Addr0High    	  0x0040    /* Mac address0 high Register                */
#define REG_GMAC_Addr0Low    	  0x0044    /* Mac address0 low Register                 */
#define REG_GMAC_Addr1High    	  0x0048    /* Mac address1 high Register                */
#define REG_GMAC_Addr1Low     	  0x004C    /* Mac address1 low Register                 */
#define REG_GMAC_Addr2High   	  0x0050    /* Mac address2 high Register                */
#define REG_GMAC_Addr2Low     	  0x0054    /* Mac address2 low Register                 */
#define REG_GMAC_Addr3High    	  0x0058    /* Mac address3 high Register                */
#define REG_GMAC_Addr3Low     	  0x005C    /* Mac address3 low Register                 */
#define REG_GMAC_Addr4High    	  0x0060    /* Mac address4 high Register                */
#define REG_GMAC_Addr4Low     	  0x0064    /* Mac address4 low Register                 */
#define REG_GMAC_Addr5High    	  0x0068    /* Mac address5 high Register                */
#define REG_GMAC_Addr5Low     	  0x006C    /* Mac address5 low Register                 */
#define REG_GMAC_Addr6High    	  0x0070    /* Mac address6 high Register                */
#define REG_GMAC_Addr6Low     	  0x0074    /* Mac address6 low Register                 */
#define REG_GMAC_Addr7High    	  0x0078    /* Mac address7 high Register                */
#define REG_GMAC_Addr7Low     	  0x007C    /* Mac address7 low Register                 */
#define REG_GMAC_Addr8High    	  0x0080    /* Mac address8 high Register                */
#define REG_GMAC_Addr8Low     	  0x0084    /* Mac address8 low Register                 */
#define REG_GMAC_Addr9High    	  0x0088    /* Mac address9 high Register                */
#define REG_GMAC_Addr9Low      	  0x008C    /* Mac address9 low Register                 */
#define REG_GMAC_Addr10High       0x0090    /* Mac address10 high Register               */
#define REG_GMAC_Addr10Low    	  0x0094    /* Mac address10 low Register                */
#define REG_GMAC_Addr11High   	  0x0098    /* Mac address11 high Register               */
#define REG_GMAC_Addr11Low    	  0x009C    /* Mac address11 low Register                */
#define REG_GMAC_Addr12High   	  0x00A0    /* Mac address12 high Register               */
#define REG_GMAC_Addr12Low     	  0x00A4    /* Mac address12 low Register                */
#define REG_GMAC_Addr13High   	  0x00A8    /* Mac address13 high Register               */
#define REG_GMAC_Addr13Low   	  0x00AC    /* Mac address13 low Register                */
#define REG_GMAC_Addr14High   	  0x00B0    /* Mac address14 high Register               */
#define REG_GMAC_Addr14Low        0x00B4    /* Mac address14 low Register                */
#define REG_GMAC_Addr15High       0x00B8    /* Mac address15 high Register               */
#define REG_GMAC_Addr15Low  	  0x00BC    /* Mac address15 low Register                */
#define REG_GMAC_LinkStatus       0x00D8    /* SGMII/RGMII/SMII Control and Status Register */
#define REG_GMAC_Vlan_Control     0x0584    /* VLAN Tag Inclusion or Replacement         */
#define REG_GMAC_Vlan_HashTable   0x0588    /* VLAN Hash Table Register                  */
#define REG_GMAC_TSControl		  0x0700
#define REG_GMAC_TSSubSecIncr	  0x0704
#define REG_GMAC_TSHigh			  0x0708
#define REG_GMAC_TSLow			  0x070C
#define REG_GMAC_TSHighUpdate	  0x0710
#define REG_GMAC_TSLowUpdate	  0x0714
#define REG_GMAC_TSAddend		  0x0718
#define REG_GMAC_TSTargetTimeHigh 0x071C
#define REG_GMAC_TSTargetTimeLow  0x0720
#define REG_GMAC_TSHighWord		  0x0724
#define REG_GMAC_TSStatus		  0x0728
#define REG_GMAC_AuxiliaryTSLow	  0x0730
#define REG_GMAC_AuxiliaryTSHigh  0x0734

/* XGMAC Registers */
#define XGMAC_ADDR_BASE         (LIF_BASE_ADDR + 0x14000)
#define XGMAC_MDIO_ADDR			0x00000200
#define XGMAC_MDIO_C22P         0x00000220
#define  XGMAC_MDIO_ADDR_DA		GENMASK(25, 21)		/* Clause 45 device address */
#define  XGMAC_MDIO_ADDR_PA		GENMASK(20, 16)		/* PHY address */
#define  XGMAC_MDIO_ADDR_RA		GENMASK(15, 0)		/* Register address */

#define XGMAC_MDIO_DATA			0x00000204
#define  XGMAC_MDIO_DATA_SBUSY		BIT(22)			/* Busy */
#define  XGMAC_MDIO_DATA_CR		GENMASK(21, 19)		/* Clock range */
#define  XGMAC_MDIO_DATA_CMD		GENMASK(17, 16)		/* Control command */
#define  XGMAC_MDIO_DATA_CMD_RD		XGMAC_MDIO_DATA_CMD	/* Control command read */
#define  XGMAC_MDIO_DATA_CMD_WR		BIT(16)			/* Control command write */
#define  XGMAC_MDIO_DATA_SDATA		GENMASK(15, 0)		/* Control data */

#define XGMAC_MDIO_C22P			0x00000220


#endif

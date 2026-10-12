#ifndef _LIF_COMMON_H_
#define _LIF_COMMON_H_


#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/io.h>
#include <linux/types.h>
#include <linux/bitfield.h>

#define CSR_REG_WRITE(addr,value) writel(value,(uintptr_t)(addr))
#define CSR_REG_READ(addr) readl((uintptr_t)(addr))

typedef unsigned int BOOLEAN;
typedef unsigned int uint32_t;
typedef int int32_t;
#define NULL ((void *)0)

//debug ret for simulation
#define DEBUG_SIM_RET_FAIL       0x77
#define DEBUG_SIM_RET_PASS       0x88
#define DEBUG_SIM_RET_TIMEOUT    0x99
#define ENH_RCV_BUFSIZE          2048
#define TRUE   1
#define FALSE  0

#define GMII_ADDR_MASK_CR      0x80380000     //CSR Clock Range,clear CRS and set CR
#define XGMII_TX_RX_PBL_MASK   0x3f0000	      //PBL(DMA_CH(#i)_TX_Control) mask
#define XGMII_TX_RX_DSL_MASK   0x1c0000       //DSL (DMA_CH(#i)_Control) mask


#define DWCXG_NUM_TXQ              1    //the num transmit queues rang(1~16),default is 1

//0101: The CSR clock frequency is 250-300 MHz and the MDC clock is CSR clock/122(CR=010).
#define CSR_CLK_DIV_5 0x00100000
#define PTP_CLOCK 	  50				//50MHz

 // if it is set to 1, interrupt is available for all the descriptors or else interrupt is available only for descriptor whose index%MODULO_INTERRUPT is zero
#define MODULO_INTERRUPT   1

/*  Error Codes  */
#define ESYNOPGMACNOERR   0
#define ESYNOPGMACNOMEM   1
#define ESYNOPGMACPHYERR  2
#define ESYNOPGMACBUSY    3




#define SIFLOWER_EMAC_SBD_IRQ  32
#define SIFLOWER_EMAC_PMT_IRQ  34


#define XG_DMA 1

#define XGMAC_DMA_CH_NUM  4

#define XGMAC_DMA_CONTEXT_DESC      1
#define DEFAULT_DMA_TX_DESC_NUM        128
#define DEFAULT_DMA_RX_DESC_NUM        256

enum Mii_Link_Status {
	LINKDOWN = 0,
	LINKUP = 1,
};

enum Mii_Duplex_Mode {
	HALFDUPLEX = 1,
	FULLDUPLEX = 2,
};
enum Mii_Link_Speed {
	SPEED10 = 1,
	SPEED100 = 2,
	SPEED1000 = 3,
	XGMIISPEED2500=4,
	GMIISPEED2500=5,
	SPEED5000=6,
	SPEED10000=7
};

enum Mii_Loop_Back {
	NOLOOPBACK = 0,
	LOOPBACK = 1,
};


enum DescMode {
	RINGMODE = 0x00000001,
	CHAINMODE = 0x00000002,//XGMAC not support
};

enum BufferMode {
	SINGLEBUF = 0x00000001,
	DUALBUF = 0x00000002,
};

enum{
    GIC_HIGH_LV,
    GIC_LOW_LV,
    GIC_RISING_EDGE,
    GIC_FALLING_EDGE,
};

typedef struct XG_DmaTXDescStruct
{
#ifdef XGMAC_DMA_CONTEXT_DESC
    uint32_t timestamp_low;
	uint32_t timestamp_high;
	uint32_t tag;
	uint32_t control;
#endif
	uint32_t rdes0;
	uint32_t rdes1;
	uint32_t rdes2;
	uint32_t rdes3;
}XGMAC_DmaTXDesc;

typedef struct XG_DmaRXDescStruct
{
	uint32_t rdes0;
	uint32_t rdes1;
	uint32_t rdes2;
	uint32_t rdes3;
//#ifdef XGMAC_DMA_CONTEXT_DESC
//    uint32_t timestamp_low;
//	uint32_t timestamp_high;
//	uint32_t tag;
//	uint32_t control;
//#endif
}XGMAC_DmaRXDesc;

typedef struct DmaDescStruct
{
    uint32_t status;         /* Status										*/
	uint32_t length;         /* Buffer 1  and Buffer 2 length							*/
	uint32_t buffer1;        /* Network Buffer 1 pointer (Dma-able) 						*/
	uint32_t buffer2;        /* Network Buffer 2 pointer or next descriptor pointer (Dma-able)in chain structure */
  	/* These data below is used only by driver */
	uint32_t data1;          /* This holds virtual address of buffer1, not used by DMA				*/
	uint32_t data2;          /* This holds virtual address of buffer2, not used by DMA				*/

} GMAC_DmaTxDesc;

typedef struct DmaRxDescStruct
{
    uint32_t status;         /* Status										*/
	uint32_t length;         /* Buffer 1  and Buffer 2 length							*/
	uint32_t buffer1;        /* Network Buffer 1 pointer (Dma-able) 						*/
	uint32_t buffer2;        /* Network Buffer 2 pointer or next descriptor pointer (Dma-able)in chain structure */
	uint32_t extstatus;
	uint32_t reserved1;
	uint32_t timestamplow;
	uint32_t timerstamphigh;
  	/* These data below is used only by driver */
	uint32_t data1;          /* This holds virtual address of buffer1, not used by DMA				*/
	uint32_t data2;          /* This holds virtual address of buffer2, not used by DMA				*/

} GMAC_DmaRxDesc;


struct XG_macContext {
	int32_t version;

	/* Dma-able address of first tx descriptor either in ring or chain mode,
	 * this is used by the GMAC device */
	int32_t TxDescDma;
    int32_t Last_TxDescDma;

	/* Dma-albe address of first rx descriptor either in ring or chain mode,
	 * this is used by the GMAC device */
	int32_t RxDescDma;
    int32_t Last_RxDescDma;

#ifdef XG_DMA
    XGMAC_DmaTXDesc *TxDesc, *Last_TxDesc;
	XGMAC_DmaRXDesc *RxDesc, *Last_RxDesc;
#else
    GMAC_DmaTxDesc *TxDesc, *Last_TxDesc;
    GMAC_DmaRxDesc *RxDesc, *Last_RxDesc;
#endif

	/*  Number of Tx Descriptors owned by DMA at any given time */
	int32_t BusyTxDesc;
	/*  Number of Rx Descriptors owned by DMA at any given time */
	uint32_t BusyRxDesc;

	/*  number of rx descriptors in the rx descriptor queue/pool */
	uint32_t RxDescCount;
	/*  number of tx descriptors in the tx descriptor queue/pool */
	uint32_t TxDescCount;

	/* index of the tx descriptor owned by DMA, is obtained by
	 * synopGMAC_get_tx_qptr()*/
	uint32_t TxBusy;
	/* index of the tx descriptor next available with driver, given to DMA
	 * by synopGMAC_set_tx_qptr()*/
	uint32_t TxNext;
	/* index of the rx descriptor owned by DMA, obtained by
	 * synopGMAC_get_rx_qptr()*/
	uint32_t RxBusy;
	/* index of the rx descriptor next available with driver, given to DMA
	 * by synopGMAC_set_rx_qptr()*/
	uint32_t RxNext;


#ifdef XG_DMA
    XGMAC_DmaTXDesc *TxBusyDesc,*TxNextDesc;
	XGMAC_DmaRXDesc *RxBusyDesc,*RxNextDesc;
#else
    GMAC_DmaTxDesc   *TxBusyDesc, *TxNextDesc;
	GMAC_DmaRxDesc   *RxBusyDesc, *RxNextDesc;
#endif




	/* Clock divider value programmed in the hardware */
	uint32_t ClockDivMdc;

	/********cfg parameters********/
	// 1--mac Loopback mode
	uint32_t LOOPBACK;
	// mac Duplex mode of the Phy
	enum Mii_Duplex_Mode DUPLEX_MODE;
	// mac speed
	enum Mii_Link_Speed MAC_SPEED;
	// buffer desc mode
	enum DescMode BUFFER_DESC_MODE;
	// Tx Descriptors needed in the Descriptor pool/queue
	// 1--phy test mode to speed up simulation
	uint32_t PHY_TESTMODE;
	uint32_t TRANSMIT_DESC_SIZE;
	// Rx Descriptors needed in the Descriptor pool/queue
	uint32_t RECEIVE_DESC_SIZE;
	// The CSR clock frequency div,with value CSR_CLK_DIV_0 ~ CSR_CLK_DIV_5
	uint32_t CSR_CLK_DIV;
	// the basic control value of MAC register 0
	int32_t BASE_CTRL;
	// address of mac address1
	char DEFAULT_MAC_ADDRESS[6];
};


/*DmaStatus         = 0x0014,    CSR5 - Dma status Register                        */
enum DmaStatusReg
{
  /*Bit 28 27 and 26 indicate whether the interrupt due to PMT GMACMMC or GMAC LINE Remaining bits are DMA interrupts*/

  #ifdef AVB_SUPPORT
  DmaSlotCounterIntr      = 0x40000000,   /* For Ch1 and Ch2 AVB slot interrupt status          31     RW       0       */
  #endif
  #ifdef LPI_SUPPORT
  GmacLPIIntr             = 0x40000000,   /* GMC LPI interrupt                                  31     RO       0       */
  #endif
  GmacTSIntr			  = 0x20000000,	  /* (TTI)Timestamp Trigger Interrupt					29	   RO		0		*/
  GmacPmtIntr             = 0x10000000,   /* (GPI)Gmac subsystem interrupt                      28     RO       0       */
  GmacMmcIntr             = 0x08000000,   /* (GMI)Gmac MMC subsystem interrupt                  27     RO       0       */
  GmacLineIntfIntr        = 0x04000000,   /* Line interface interrupt                           26     RO       0       */

  DmaErrorBit2            = 0x02000000,   /* (EB)Error bits 0-data buffer, 1-desc. access       25     RO       0       */
  DmaErrorBit1            = 0x01000000,   /* (EB)Error bits 0-write trnsf, 1-read transfr       24     RO       0       */
  DmaErrorBit0            = 0x00800000,   /* (EB)Error bits 0-Rx DMA, 1-Tx DMA                  23     RO       0       */

  DmaTxState              = 0x00700000,   /* (TS)Transmit process state                         22:20  RO               */
  DmaTxStopped            = 0x00000000,   /* Stopped - Reset or Stop Tx Command issued                         000      */
  DmaTxFetching           = 0x00100000,   /* Running - fetching the Tx descriptor                                       */
  DmaTxWaiting            = 0x00200000,   /* Running - waiting for status                                               */
  DmaTxReading            = 0x00300000,   /* Running - reading the data from host memory                                */
  DmaTxSuspended          = 0x00600000,   /* Suspended - Tx Descriptor unavailabe                                       */
  DmaTxClosing            = 0x00700000,   /* Running - closing Rx descriptor                                            */

  DmaRxState              = 0x000E0000,   /* (RS)Receive process state                         19:17  RO                */
  DmaRxStopped            = 0x00000000,   /* Stopped - Reset or Stop Rx Command issued                         000      */
  DmaRxFetching           = 0x00020000,   /* Running - fetching the Rx descriptor                                       */
  DmaRxWaiting            = 0x00060000,   /* Running - waiting for packet                                               */
  DmaRxSuspended          = 0x00080000,   /* Suspended - Rx Descriptor unavailable                                      */
  DmaRxClosing            = 0x000A0000,   /* Running - closing descriptor                                               */
  DmaRxQueuing            = 0x000E0000,   /* Running - queuing the recieve frame into host memory                       */

  DmaIntNormal            = 0x00010000,   /* (NIS)Normal interrupt summary                     16     RW        0       */
  DmaIntAbnormal          = 0x00008000,   /* (AIS)Abnormal interrupt summary                   15     RW        0       */

  DmaIntEarlyRx           = 0x00004000,   /* Early receive interrupt (Normal)       RW        0       */
  DmaIntBusError          = 0x00002000,   /* Fatal bus error (Abnormal)             RW        0       */
  DmaIntEarlyTx           = 0x00000400,   /* Early transmit interrupt (Abnormal)    RW        0       */
  DmaIntRxWdogTO          = 0x00000200,   /* Receive Watchdog Timeout (Abnormal)    RW        0       */
  DmaIntRxStopped         = 0x00000100,   /* Receive process stopped (Abnormal)     RW        0       */
  DmaIntRxNoBuffer        = 0x00000080,   /* Receive buffer unavailable (Abnormal)  RW        0       */
  DmaIntRxCompleted       = 0x00000040,   /* Completion of frame reception (Normal) RW        0       */
  DmaIntTxUnderflow       = 0x00000020,   /* Transmit underflow (Abnormal)          RW        0       */
  DmaIntRcvOverflow       = 0x00000010,   /* Receive Buffer overflow interrupt      RW        0       */
  DmaIntTxJabberTO        = 0x00000008,   /* Transmit Jabber Timeout (Abnormal)     RW        0       */
  DmaIntTxNoBuffer        = 0x00000004,   /* Transmit buffer unavailable (Normal)   RW        0       */
  DmaIntTxStopped         = 0x00000002,   /* Transmit process stopped (Abnormal)    RW        0       */
  DmaIntTxCompleted       = 0x00000001,   /* Transmit completed (Normal)            RW        0       */

};



/*DmaInterrupt      = 0x001C,    CSR7 - Interrupt enable Register Layout     */
enum  DmaInterruptReg
{
  DmaIeNormal            = DmaIntNormal     ,
  DmaIeAbnormal          = DmaIntAbnormal   ,
  DmaIeEarlyRx           = DmaIntEarlyRx    ,
  DmaIeBusError          = DmaIntBusError   ,
  DmaIeEarlyTx           = DmaIntEarlyTx    ,
  DmaIeRxWdogTO          = DmaIntRxWdogTO   ,
  DmaIeRxStopped         = DmaIntRxStopped  ,
  DmaIeRxNoBuffer        = DmaIntRxNoBuffer ,   /* Receive buffer unavailable enable       RW        0       */
  DmaIeRxCompleted       = DmaIntRxCompleted,   /* Completion of frame reception enable    RW        0       */
  DmaIeTxUnderflow       = DmaIntTxUnderflow,   /* Transmit underflow enable               RW        0       */
  DmaIeRxOverflow        = DmaIntRcvOverflow,   /* Receive Buffer overflow interrupt       RW        0       */
  DmaIeTxJabberTO        = DmaIntTxJabberTO ,   /* Transmit Jabber Timeout enable          RW        0       */
  DmaIeTxNoBuffer        = DmaIntTxNoBuffer ,   /* Transmit buffer unavailable enable      RW        0       */
  DmaIeTxStopped         = DmaIntTxStopped  ,   /* Transmit process stopped enable         RW        0       */
  DmaIeTxCompleted       = DmaIntTxCompleted,   /* Transmit completed enable               RW        0       */
};

enum InitialRegisters
{
    DmaIntTxNormMask = DmaIntTxCompleted,
    DmaIntRxNormMask = DmaIntRxCompleted,
	DmaIntEnable = DmaIeNormal | DmaIeAbnormal | DmaIntBusError |DmaIntRxNoBuffer | DmaIeRxCompleted | DmaIntRxStopped |  DmaIntTxUnderflow | DmaIeTxCompleted | DmaIntTxStopped,
	DmaIntDisable = 0,
};

enum DmaDescriptorStatus    /* status word of DMA descriptor */
{

  DescOwnByDma          = 0x80000000,   /* (OWN)Descriptor is owned by DMA engine              31      RW                  */
  DescDAFilterFail      = 0x40000000,   /* (AFM)Rx - DA Filter Fail for the rx frame           30                          */

  DescFrameLengthMask   = 0x3FFF0000,   /* (FL)Receive descriptor frame length                 29:16                       */
  DescFrameLengthShift  = 16,

  DescError             = 0x00008000,   /* (ES)Error summary bit  - OR of the follo. bits:     15                          */
					/*  DE || OE || IPC || LC || RWT || RE || CE */
  DescRxTruncated       = 0x00004000,   /* (DE)Rx - no more descriptors for receive frame      14                          */
  DescSAFilterFail      = 0x00002000,   /* (SAF)Rx - SA Filter Fail for the received frame     13                          */
  DescRxLengthError	    = 0x00001000,   /* (LE)Rx - frm size not matching with len field       12                          */
  DescRxDamaged         = 0x00000800,   /* (OE)Rx - frm was damaged due to buffer overflow     11                          */
  DescRxVLANTag         = 0x00000400,   /* (VLAN)Rx - received frame is a VLAN frame           10                          */
  DescRxFirst           = 0x00000200,   /* (FS)Rx - first descriptor of the frame              9                          */
  DescRxLast            = 0x00000100,   /* (LS)Rx - last descriptor of the frame               8                          */
  DescRxLongFrame       = 0x00000080,   /* (Giant Frame)Rx - frame is longer than 1518/1522    7                          */
  DescRxCollision       = 0x00000040,   /* (LC)Rx - late collision occurred during reception   6                          */
  DescRxFrameEther      = 0x00000020,   /* (FT)Rx - Frame type - Ethernet, otherwise 802.3     5                          */
  DescRxWatchdog        = 0x00000010,   /* (RWT)Rx - watchdog timer expired during reception   4                          */
  DescRxMiiError        = 0x00000008,   /* (RE)Rx - error reported by MII interface            3                          */
  DescRxDribbling       = 0x00000004,   /* (DE)Rx - frame contains non int multiple of 8 bits  2                          */
  DescRxCrc             = 0x00000002,   /* (CE)Rx - CRC error                                  1                          */
//  DescRxMacMatch        = 0x00000001,   /* (RX MAC Address) Rx mac address reg(1 to 15)match   0                          */

  DescRxEXTsts          = 0x00000001,   /* Extended Status Available (RDES0)   bit0                */

  DescTxIntEnable       = 0x40000000,   /* (IC)Tx - interrupt on completion                    30                       */
  DescTxLast            = 0x20000000,   /* (LS)Tx - Last segment of the frame                  29                       */
  DescTxFirst           = 0x10000000,   /* (FS)Tx - First segment of the frame                 28                       */
  DescTxDisableCrcAdd   = 0x08000000,   /* (DC)Tx - Add CRC disabled (first segment only)      27                       */
  DescTxDisablePadd   	= 0x04000000,   /* (DP)disable padding, added by - reyaz               26                       */
  DescTxTSEnable		= 0x02000000,	/* (TTSE)Tx - Transmit Timestamp Enable				   25						*/
  DescTxEnableCRCRepl   = 0x01000000,   /* (CRCR)CRC Replacement Control                       24                       */

  DescTxCisMask     	= 0x00c00000,   /* (CIC)Tx checksum offloading control mask		       23:22			*/
  DescTxCisBypass   	= 0x00000000,   /* Checksum bypass								*/
  DescTxCisIpv4HdrCs	= 0x00400000,	/* IPv4 header checksum								*/
  DescTxCisTcpOnlyCs    = 0x00800000,	/* TCP/UDP/ICMP checksum. Pseudo header checksum is assumed to be present	*/
  DescTxCisTcpPseudoCs  = 0x00c00000,	/* TCP/UDP/ICMP checksum fully in hardware including pseudo header		*/

  TxDescEndOfRing       = 0x00200000,   /* (TER)End of descriptors ring                        21                       */
  TxDescChain           = 0x00100000,   /* (TCH)Second buffer address is chain address         20                       */

  DescRxChkBit0		    = 0x00000001,   /*()  Rx - Rx Payload Checksum Error                   0                          */
  DescRxChkBit7	    	= 0x00000080,   /* (IPC CS ERROR)Rx - Ipv4 header checksum error       7                          */
  DescRxChkBit5 		= 0x00000020,   /* (FT)Rx - Frame type - Ethernet, otherwise 802.3     5                          */

  DescRxTSavail         = 0x00000080,   /* Time stamp available                                7                          */
  DescRxFrameType   	= 0x00000020,   /* (FT)Rx - Frame type - Ethernet, otherwise 802.3     5                          */

  DescTxTSStatus		= 0x00020000,	/* (TTSS)Tx Timestamp Status						   17						  */
  DescTxIpv4ChkError    = 0x00010000,   /* (IHE) Tx Ip header error                            16                         */
  DescTxTimeout         = 0x00004000,   /* (JT)Tx - Transmit jabber timeout                    14                         */
  DescTxFrameFlushed    = 0x00002000,   /* (FF)Tx - DMA/MTL flushed the frame due to SW flush  13                         */
  DescTxPayChkError     = 0x00001000,   /* (PCE) Tx Payload checksum Error                     12                         */
  DescTxLostCarrier     = 0x00000800,   /* (LC)Tx - carrier lost during tramsmission           11                         */
  DescTxNoCarrier       = 0x00000400,   /* (NC)Tx - no carrier signal from the tranceiver      10                         */
  DescTxLateCollision   = 0x00000200,   /* (LC)Tx - transmission aborted due to collision      9                         */
  DescTxExcCollisions   = 0x00000100,   /* (EC)Tx - transmission aborted after 16 collisions   8                         */
  DescTxVLANFrame       = 0x00000080,   /* (VF)Tx - VLAN-type frame                            7                         */

  DescTxCollMask        = 0x00000078,   /* (CC)Tx - Collision count                            6:3                        */
  DescTxCollShift       = 3,

  DescTxExcDeferral     = 0x00000004,   /* (ED)Tx - excessive deferral                         2                        */
  DescTxUnderflow       = 0x00000002,   /* (UF)Tx - late data arrival from the memory          1                        */
  DescTxDeferred        = 0x00000001,   /* (DB)Tx - frame transmision deferred                 0                        */

	/*
	This explains the RDES1/TDES1 bits layout
			  --------------------------------------------------------------------
	    RDES1/TDES1  | Control Bits | Byte Count Buffer 2 | Byte Count Buffer 1          |
			  --------------------------------------------------------------------

	*/
// DmaDescriptorLength     length word of DMA descriptor


  RxDisIntCompl		= 0x80000000,	/* (Disable Rx int on completion) 			31			*/
  RxDescEndOfRing       = 0x00008000,   /* (TER)End of descriptors ring                         15                       */
  RxDescChain           = 0x00004000,   /* (TCH)Second buffer address is chain address          14                       */


  DescSize2Mask         = 0x1FFF0000,   /* (TBS2) Buffer 2 size                                28:16                    */
  DescSize2Shift        = 16,
  DescSize1Mask         = 0x00001FFF,   /* (TBS1) Buffer 1 size                                12:0                     */
  DescSize1Shift        = 0,


	/*
	This explains the RDES4 Extended Status bits layout
			   --------------------------------------------------------------------
	  RDES4   |                             Extended Status                        |
			   --------------------------------------------------------------------
	*/

  DescRxPtpAvail        = 0x00004000,    /* PTP snapshot available                              14                        */
  DescRxPtpVer          = 0x00002000,    /* When set indicates IEEE1584 Version 2 (else Ver1)   13                        */
  DescRxPtpFrameType    = 0x00001000,    /* PTP frame type Indicates PTP sent over ethernet     12                        */
  DescRxPtpMessageType  = 0x00000F00,    /* Message Type                                        11:8                      */
  DescRxPtpNo           = 0x00000000,    /* 0000 => No PTP message received                                               */
  DescRxPtpSync         = 0x00000100,    /* 0001 => Sync (all clock types) received                                       */
  DescRxPtpFollowUp     = 0x00000200,    /* 0010 => Follow_Up (all clock types) received                                  */
  DescRxPtpDelayReq     = 0x00000300,    /* 0011 => Delay_Req (all clock types) received                                  */
  DescRxPtpDelayResp    = 0x00000400,    /* 0100 => Delay_Resp (all clock types) received                                 */
  DescRxPtpPdelayReq    = 0x00000500,    /* 0101 => Pdelay_Req (in P to P tras clk)  or Announce in Ord and Bound clk     */
  DescRxPtpPdelayResp   = 0x00000600,    /* 0110 => Pdealy_Resp(in P to P trans clk) or Management in Ord and Bound clk   */
  DescRxPtpPdelayRespFP = 0x00000700,    /* 0111 => Pdealy_Resp_Follow_Up (in P to P trans clk) or Signaling in Ord and Bound clk   */
  DescRxPtpIPV6         = 0x00000080,    /* Received Packet is  in IPV6 Packet                  7                         */
  DescRxPtpIPV4         = 0x00000040,    /* Received Packet is  in IPV4 Packet                  6                         */

  DescRxChkSumBypass    = 0x00000020,    /* When set indicates checksum offload engine          5
                                            is bypassed                                                                   */
  DescRxIpPayloadError  = 0x00000010,    /* When set indicates 16bit IP payload CS is in error  4                         */
  DescRxIpHeaderError   = 0x00000008,    /* When set indicates 16bit IPV4 header CS is in       3
                                            error or IP datagram version is not consistent
                                            with Ethernet type value                                                      */
  DescRxIpPayloadType   = 0x00000007,     /* Indicate the type of payload encapsulated          2:0
                                             in IPdatagram processed by COE (Rx)                                          */
  DescRxIpPayloadUnknown= 0x00000000,     /* Unknown or didnot process IP payload                                         */
  DescRxIpPayloadUDP    = 0x00000001,     /* UDP                                                                          */
  DescRxIpPayloadTCP    = 0x00000002,     /* TCP                                                                          */
  DescRxIpPayloadICMP   = 0x00000003,     /* ICMP                                                                         */

};

enum RxDescCOEEbcode
{
	RxLenLT600 = 0,
	RxIpHdrPayLoadChkBypass = 1,
	RxIpHdrPayLoadRes = 2,
	RxChkBypass = 3,
	RxNoChkError = 4,
	RxPayLoadChkError = 5,
	RxIpHdrChkError = 6,
	RxIpHdrPayLoadChkError = 7,
};

enum DmaBusModeReg
{
  DmaFixedBurstEnable     = 0x00010000,   /* (FB)Fixed Burst SINGLE, INCR4, INCR8 or INCR16   16     RW                */
  DmaFixedBurstDisable    = 0x00000000,   /*             SINGLE, INCR                                          0       */

  DmaTxPriorityRatio11    = 0x00000000,   /* (PR)TX:RX DMA priority ratio 1:1                15:14   RW        00      */
  DmaTxPriorityRatio21    = 0x00004000,   /* (PR)TX:RX DMA priority ratio 2:1                                          */
  DmaTxPriorityRatio31    = 0x00008000,   /* (PR)TX:RX DMA priority ratio 3:1                                          */
  DmaTxPriorityRatio41    = 0x0000C000,   /* (PR)TX:RX DMA priority ratio 4:1                                          */

  DmaBurstLengthx8        = 0x01000000,   /* When set mutiplies the PBL by 8                  24      RW        0      */

  DmaBurstLength256       = 0x01002000,   /*(DmaBurstLengthx8 | DmaBurstLength32) = 256      [24]:13:8                 */
  DmaBurstLength128       = 0x01001000,   /*(DmaBurstLengthx8 | DmaBurstLength16) = 128      [24]:13:8                 */
  DmaBurstLength64        = 0x01000800,   /*(DmaBurstLengthx8 | DmaBurstLength8) = 64        [24]:13:8                 */
  DmaBurstLength32        = 0x00002000,   /* (PBL) programmable Dma burst length = 32        13:8    RW                */
  DmaBurstLength16        = 0x00001000,   /* Dma burst length = 16                                                     */
  DmaBurstLength8         = 0x00000800,   /* Dma burst length = 8                                                      */
  DmaBurstLength4         = 0x00000400,   /* Dma burst length = 4                                                      */
  DmaBurstLength2         = 0x00000200,   /* Dma burst length = 2                                                      */
  DmaBurstLength1         = 0x00000100,   /* Dma burst length = 1                                                      */
  DmaBurstLength0         = 0x00000000,   /* Dma burst length = 0                                               0x00   */

  DmaDescriptor8Words     = 0x00000080,   /* Enh Descriptor works  1=> 8 word descriptor      7                  0    */
  DmaDescriptor4Words     = 0x00000000,   /* Enh Descriptor works  0=> 4 word descriptor      7                  0    */

  DmaDescriptorSkip16     = 0x00000040,   /* (DSL)Descriptor skip length (no.of dwords)       6:2     RW               */
  DmaDescriptorSkip8      = 0x00000020,   /* between two unchained descriptors                                         */
  DmaDescriptorSkip4      = 0x00000010,   /*                                                                           */
  DmaDescriptorSkip2      = 0x00000008,   /*                                                                           */
  DmaDescriptorSkip1      = 0x00000004,   /*                                                                           */
  DmaDescriptorSkip0      = 0x00000000,   /*                                                                    0x00   */

  DmaArbitRr              = 0x00000000,   /* (DA) DMA RR arbitration                            1     RW         0     */
  DmaArbitPr              = 0x00000002,   /* Rx has priority over Tx                                                   */

  DmaResetOn              = 0x00000001,   /* (SWR)Software Reset DMA engine                     0     RW               */
  DmaResetOff             = 0x00000000,   /*                                                                         0    */
};

/**********************************************************
 * DMA engine interrupt handling functions
 **********************************************************/

enum DmaIntEnum  /* Intrerrupt types */
{
  gmacDmaRxNormal   = 0x01,   /* normal receiver interrupt */
  gmacDmaRxAbnormal = 0x02,   /* abnormal receiver interrupt */
  gmacDmaRxStopped  = 0x04,   /* receiver stopped */
  gmacDmaTxNormal   = 0x08,   /* normal transmitter interrupt */
  gmacDmaTxAbnormal = 0x10,   /* abnormal transmitter interrupt */
  gmacDmaTxStopped  = 0x20,   /* transmitter stopped */
  gmacDmaError      = 0x80,   /* Dma engine error */
};

enum DmaControlReg
{
  DmaDisableDropTcpCs	  = 0x04000000,   /* (DT) Dis. drop. of tcp/ip CS error frames        26      RW        0       */

  DmaRxStoreAndForward      = 0x02000000,   /* (RSF)Receive Store and forward                   25      RW        0       */
  DmaTxStoreAndForward      = 0x00200000,   /* (TSF)Transmit Store and forward                  21      RW        0       */
  DmaFlushTxFifo          = 0x00100000,   /* (FTF)Tx FIFO controller is reset to default      20      RW        0       */

  DmaTxThreshCtrl         = 0x0001C000,   /* (TTC)Controls thre Threh of MTL tx Fifo          16:14   RW                */
  DmaTxThreshCtrl16       = 0x0001C000,   /* (TTC)Controls thre Threh of MTL tx Fifo 16       16:14   RW                */
  DmaTxThreshCtrl24       = 0x00018000,   /* (TTC)Controls thre Threh of MTL tx Fifo 24       16:14   RW                */
  DmaTxThreshCtrl32       = 0x00014000,   /* (TTC)Controls thre Threh of MTL tx Fifo 32       16:14   RW                */
  DmaTxThreshCtrl40       = 0x00010000,   /* (TTC)Controls thre Threh of MTL tx Fifo 40       16:14   RW                */
  DmaTxThreshCtrl256      = 0x0000c000,   /* (TTC)Controls thre Threh of MTL tx Fifo 256      16:14   RW                */
  DmaTxThreshCtrl192      = 0x00008000,   /* (TTC)Controls thre Threh of MTL tx Fifo 192      16:14   RW                */
  DmaTxThreshCtrl128      = 0x00004000,   /* (TTC)Controls thre Threh of MTL tx Fifo 128      16:14   RW                */
  DmaTxThreshCtrl64       = 0x00000000,   /* (TTC)Controls thre Threh of MTL tx Fifo 64       16:14   RW        000     */

  DmaTxStart              = 0x00002000,   /* (ST)Start/Stop transmission                      13      RW        0       */

  DmaRxFlowCtrlDeact      = 0x00401800,   /* (RFD)Rx flow control deact. threhold             [22]:12:11   RW                 */
  DmaRxFlowCtrlDeact1K    = 0x00000000,   /* (RFD)Rx flow control deact. threhold (1kbytes)   [22]:12:11   RW        00       */
  DmaRxFlowCtrlDeact2K    = 0x00000800,   /* (RFD)Rx flow control deact. threhold (2kbytes)   [22]:12:11   RW                 */
  DmaRxFlowCtrlDeact3K    = 0x00001000,   /* (RFD)Rx flow control deact. threhold (3kbytes)   [22]:12:11   RW                 */
  DmaRxFlowCtrlDeact4K    = 0x00001800,   /* (RFD)Rx flow control deact. threhold (4kbytes)   [22]:12:11   RW                 */
  DmaRxFlowCtrlDeact5K    = 0x00400000,   /* (RFD)Rx flow control deact. threhold (5kbytes)   [22]:12:11   RW                 */
  DmaRxFlowCtrlDeact6K    = 0x00400800,   /* (RFD)Rx flow control deact. threhold (6kbytes)   [22]:12:11   RW                 */
  DmaRxFlowCtrlDeact7K    = 0x00401000,   /* (RFD)Rx flow control deact. threhold (7kbytes)   [22]:12:11   RW                 */

  DmaRxFlowCtrlAct        = 0x00800600,   /* (RFA)Rx flow control Act. threhold              [23]:10:09   RW                 */
  DmaRxFlowCtrlAct1K      = 0x00000000,   /* (RFA)Rx flow control Act. threhold (1kbytes)    [23]:10:09   RW        00       */
  DmaRxFlowCtrlAct2K      = 0x00000200,   /* (RFA)Rx flow control Act. threhold (2kbytes)    [23]:10:09   RW                 */
  DmaRxFlowCtrlAct3K      = 0x00000400,   /* (RFA)Rx flow control Act. threhold (3kbytes)    [23]:10:09   RW                 */
  DmaRxFlowCtrlAct4K      = 0x00000300,   /* (RFA)Rx flow control Act. threhold (4kbytes)    [23]:10:09   RW                 */
  DmaRxFlowCtrlAct5K      = 0x00800000,   /* (RFA)Rx flow control Act. threhold (5kbytes)    [23]:10:09   RW                 */
  DmaRxFlowCtrlAct6K      = 0x00800200,   /* (RFA)Rx flow control Act. threhold (6kbytes)    [23]:10:09   RW                 */
  DmaRxFlowCtrlAct7K      = 0x00800400,   /* (RFA)Rx flow control Act. threhold (7kbytes)    [23]:10:09   RW                 */

  DmaRxThreshCtrl         = 0x00000018,   /* (RTC)Controls thre Threh of MTL rx Fifo          4:3   RW                */
  DmaRxThreshCtrl64       = 0x00000000,   /* (RTC)Controls thre Threh of MTL rx Fifo 64       4:3   RW                */
  DmaRxThreshCtrl32       = 0x00000008,   /* (RTC)Controls thre Threh of MTL rx Fifo 32       4:3   RW                */
  DmaRxThreshCtrl96       = 0x00000010,   /* (RTC)Controls thre Threh of MTL rx Fifo 96       4:3   RW                */
  DmaRxThreshCtrl128      = 0x00000018,   /* (RTC)Controls thre Threh of MTL rx Fifo 128      4:3   RW                */

  DmaEnHwFlowCtrl         = 0x00000100,   /* (EFC)Enable HW flow control                      8       RW                 */
  DmaDisHwFlowCtrl        = 0x00000000,   /* Disable HW flow control                                            0        */

  DmaFwdErrorFrames       = 0x00000080,   /* (FEF)Forward error frames                        7       RW        0       */
  DmaFwdUnderSzFrames     = 0x00000040,   /* (FUF)Forward undersize frames                    6       RW        0       */
  DmaDropGiantFrames      = 0x00000020,   /* (DGF)Drop Giant Frames                           5       RW        0       */
  DmaTxSecondFrame        = 0x00000004,   /* (OSF)Operate on second frame                     4       RW        0       */
  DmaRxStart              = 0x00000002,   /* (SR)Start/Stop reception                         1       RW        0       */
};
enum DmaDescDirect
{
	TX_Desc = 0,
	RX_Desc = 1,
};


enum XG_DmaReg
{
	XG_DmaDescriptorSkip2 = 2  << 18,
    XG_DmaBurstLength32   = 32 << 16,
	XG_DmaAAL             = 1  << 12,
	XG_DmaUNDEF           = 1 << 0,
	XG_DmaEAME            = 1 << 11,

	XG_DmaTIE             = 1 << 0,
	XG_DmaTXSE            = 1 << 1,
    XG_DmaRIE             = 1 << 6,
	XG_DmaTBUE            = 1 << 2,
	XG_DmaRBUE            = 1 << 7,
	XG_DmaRSE             = 1 << 8,
	XG_DmaDDDE            = 1 << 9,
	XG_DmaFBEE            = 1 << 12,
	XG_DmaCDEE            = 1 << 13,
	XG_DmaAIE             = 1 << 14,
	XG_DmaNIE             = 1 << 15,
	XG_DmaTPS             = 1 << 1,
	XG_DmaRPS             = 1 << 8,
};
enum XGmacMtlConfig
{
	Mtl_ETSALG = 0x0 << 5,//WRR algorithm
    Mtl_RAA    = 0x0 << 2, //strict priority(SP)
	Mtl_FTS    = 0x1 << 1, //forward transmit status
	Mtl_TSF    = 0x1 << 1, //Transmit store and forward
	Mtl_TTC    = 0x3 << 4, //Transmit Threshold vlaue 128
	Mtl_TSQEN  = 0x2 << 2, //Transmit Queue Enable
	Mtl_TSQ    = 0xf << 16,//Transmit Queue size is 4096
	Mtl_Q2TCMAP = 0x0 << 8,//Queue0 map to TC0
	Mtl_RSF     = 0x1 << 5,//Receive store and forward
	Mtl_RSQ     = 0xF << 16,//Receive Queue size is 4096
    Mtl_RTC     = 0x11 << 0,//Receive Queue Threshold is 128
};

#define DEFAULT_MAC_DUPLEX_MODE FULLDUPLEX
#define DEFAULT_MAC_SPEED       SPEED1000
#define DEFAULT_MAC_DESC_MODE   RINGMODE
#define DEFAULT_MAC_MDC_DIV     CSR_CLK_DIV_5

#define DEFAULT_XGMAC_DUPLEX_MODE FULLDUPLEX
#define DEFAULT_XGMAC_SPEED       SPEED10000
#define DEFAULT_XGMAC_DESC_MODE   RINGMODE
#define DEFAULT_XGMAC_MDC_DIV     CSR_CLK_DIV_5

#define TX_BD_FLAG_SINGLE (DescTxFirst | DescTxLast | DescTxIntEnable)

uint32_t    lif_get_dut(uint32_t register_addr);
int32_t     dma_read_interrupt_src(void);
int32_t     dma_wait_tx_irq_timeout(struct XG_macContext *gmacdev,int32_t timeout_us);
int32_t     dma_wait_rx_irq_timeout(uint32_t timeout_us);
void      	mydl(unsigned int tm);

int32_t gmac_dma_is_desc_owned_by_dma(GMAC_DmaTxDesc *desc);
	int32_t gmac_dma_is_desc_empty(GMAC_DmaTxDesc *desc);
    int32_t gmac_dma_is_last_tx_desc(struct XG_macContext *gmacdev,GMAC_DmaTxDesc *desc );
	int32_t gmac_dma_is_last_rx_desc(struct XG_macContext *gmacdev,GMAC_DmaRxDesc *desc );
    void   	gmac_dma_rx_desc_init_ring(GMAC_DmaRxDesc *desc, uint32_t last_ring_desc);
    void    gmac_dma_tx_desc_init_ring(GMAC_DmaTxDesc *desc, uint32_t last_ring_desc);
	int32_t gmac_get_tx_qptr(struct XG_macContext *gmacdev,
	                         uint32_t *Status,
							 uint32_t *Buffer1,
							 uint32_t *Length1,
							 uint32_t *Data1,
							 uint32_t *Buffer2,
							 uint32_t *Length2,
							 uint32_t *Data2);
	uint32_t gmac_get_rx_qptr(struct XG_macContext *gmacdev,
	                          uint32_t *Status,
							  uint32_t *Buffer1,
							  uint32_t *Length1,
							  uint32_t *Data1,
							  uint32_t *Buffer2,
							  uint32_t *Length2,
							  uint32_t *Data2,
							  uint32_t *Ext_Status,
							  uint32_t *Time_Stamp_High,
							  uint32_t *Time_Stamp_Low);
    int32_t gmac_set_tx_qptr(struct XG_macContext *gmacdev,
	                         uint32_t Buffer1,
							 uint32_t Length1,
							 uint32_t Data1,
							 uint32_t Buffer2,
							 uint32_t Length2,
							 uint32_t Data2,
							 uint32_t offload_needed,
							 int32_t tx_flag);

   int32_t gmac_set_rx_qptr(struct XG_macContext *gmacdev,
                                uint32_t Buffer1,
								uint32_t Length1);

void        xgmac_init_mtl(void);
void        lif_dma_mtl_init(struct XG_macContext *gmacdev);
void        dma_init_tx_desc_base(int32_t tx_dma_base);
void        dma_init_rx_desc_base(int32_t rx_dma_base);
void 		dma_disable_interrupt_all(void);
void 		dma_enable_interrupt(uint32_t interrupts);
int32_t     xgmac_is_rx_desc_valid(uint32_t status);
int32_t     xgmac_get_rx_desc_frame_length(uint32_t status);
int32_t 	dma_reset(void);
int32_t 	dma_control_init(uint32_t init_value);
void    	dma_enable_rx(void);
void    	dma_enable_tx(void);
int32_t		dma_bus_mode_init(uint32_t init_value);
void        dma_resume_dma_tx(void);
void        dma_init(struct XG_macContext *gmacdev);
int32_t   	reset_rx_buffer(struct XG_macContext *gmacdev);
void *      plat_alloc_consistent_dmaable_memory(uint32_t size, uint32_t *addr);
int32_t     dma_setup_rx_desc_queue(struct XG_macContext *gmacdev,uint32_t no_of_desc,uint32_t desc_mode);
int32_t     dma_setup_tx_desc_queue(struct XG_macContext *gmacdev,uint32_t no_of_desc,uint32_t desc_mode);
void 		reg_set_bits(uint32_t reg, uint32_t bits);
void 		reg_clear_bits(uint32_t reg,uint32_t bits_mask);
void 		xgmac_tx_checksum_offload_tcponly(GMAC_DmaTxDesc * desc);
void 		dma_disable_tx(void);
void 		dma_disable_rx(void);
void        drop_giant_frames(void);
void        xgmac_dma_set_rx_buffer_size(uint32_t size);











#ifdef XG_DMA
    void    xgmac_dma_rx_desc_init_ring(XGMAC_DmaRXDesc *desc);
    void    xgmac_dma_tx_desc_init_ring(XGMAC_DmaTXDesc *desc);
	int32_t xgmac_dma_is_desc_owned_by_dma(uintptr_t desc,char direct);
	int32_t xgmac_dma_is_desc_empty(uintptr_t desc,char direct);
	int32_t xgmac_dma_is_last_tx_desc(struct XG_macContext *gmacdev,XGMAC_DmaTXDesc *desc );
	int32_t xgmac_dma_is_last_rx_desc(struct XG_macContext *gmacdev,XGMAC_DmaRXDesc *desc );
    int32_t xgmac_set_tx_qptr(struct XG_macContext *gmacdev,uint32_t Buffer1,uint32_t Length1,uint32_t timestamp_low,uint32_t timestamp_high,uint32_t tag,uint32_t control);
	int32_t xgmac_get_tx_qptr(struct XG_macContext *gmacdev,
	                          uint32_t *Status,
							  uint32_t *Buffer1,
							  uint32_t *Length1,
							  uint32_t *Data1,
							  uint32_t *Buffer2,
							  uint32_t *Length2,
							  uint32_t *Data2);
    int32_t xgmac_get_rx_qptr(struct XG_macContext *gmacdev,uint32_t *Length1, char *is_context);
    int32_t xgmac_set_rx_qptr(struct XG_macContext *gmacdev,uint32_t Buffer1,uint32_t Length1);
void        xgmac_dma_reset(void);
void 		xgmac_dma_set_tx_desc_ring_length(uint32_t length);
void 		xgmac_dma_set_rx_desc_ring_length(uint32_t length);
void        xgmac_dma_init_tx_desc_base(uint32_t tx_dma_base);
void        xgmac_dma_init_rx_desc_base(uint32_t rx_dma_base);
void        xgmac_dma_init_rx_tail_desc_base(uint32_t rx_tail_dma_base);
void        xgmac_dma_init_tx_tail_desc_base(uint32_t tx_tail_dma_base);
void 		xgmac_dma_set_brust_length(uint32_t brustlength);
void 		xgmac_dma_set_desc_skip(uint32_t skip);
void 		xgmac_dma_enable_interrupt(uint32_t interrupts);
void 		xgmac_dma_enable_tx(BOOLEAN enable);
void 		xgmac_dma_enable_rx(BOOLEAN enable);
void xgmac_dma_disable_tx(void);
void xgmac_dma_disable_rx(void);
void 		xgmac_dma_init(struct XG_macContext *gmacdev);
int32_t     dma_wait_tps_irq_timeout(struct XG_macContext *gmacdev,int32_t timeout_us);
#endif

int32_t dma_wait_tps_irq_timeout(struct XG_macContext *gmacdev,int32_t timeout_us);
//int pkt_check(u8 *buf1,u8 *buf2, int len);









#endif

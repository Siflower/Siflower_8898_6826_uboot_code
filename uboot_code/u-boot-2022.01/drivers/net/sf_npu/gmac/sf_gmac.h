#ifndef _SF_GMAC_H_
#define _SF_GMAC_H_

#include "lif_reg.h"
#include "lif_common.h"

enum GmacConfigReg
{
                                              /* Bit description                      Bits         R/W   Reset value  */

  GmacSrcReplControl          = 0x70000000,    /*(SARC)Source Address Insertion or Replacement Control       [30:28]           */
  GmacSrcReplControlInsert0   = 0x20000000,    /*the MAC inserts the content of the MAC Address 0 in the SA field*/
  GmacSrcReplControlReplace0  = 0x30000000,    /*the MAC replaces the content of the MAC Address 0 in the SA field*/
  GmacSrcReplControlInsert1   = 0x60000000,    /*the MAC inserts the content of the MAC Address 1 in the SA field*/
  GmacSrcReplControlReplace1  = 0x70000000,    /*the MAC replaces the content of the MAC Address 1 in the SA field*/
  GmacSrcReplControlDisable  = 0x00000000,     /*disable the SARC SA control*/

  Gmac2KFrame                = 0x08000000,
  Gmac2KFrameEnable          = 0x08000000,     /* (TWOKPE)Support for 2K Packets        27           RW                */
  Gmac2KFrameDisable    = 0x00000000,     /* Disable jumbo frame                                          0       */

  GmacWatchdog		   = 0x00800000,
  GmacWatchdogDisable      = 0x00800000,     /* (WD)Disable watchdog timer on Rx      23           RW                */
  GmacWatchdogEnable       = 0x00000000,     /* Enable watchdog timer                                        0       */

  GmacJabber		   = 0x00400000,
  GmacJabberDisable        = 0x00400000,     /* (JD)Disable jabber timer on Tx        22           RW                */
  GmacJabberEnable         = 0x00000000,     /* Enable jabber timer                                          0       */

  GmacFrameBurst           = 0x00200000,
  GmacFrameBurstEnable     = 0x00200000,     /* (BE)Enable frame bursting during Tx   21           RW                */
  GmacFrameBurstDisable    = 0x00000000,     /* Disable frame bursting                                       0       */

  GmacJumboFrame           = 0x00100000,
  GmacJumboFrameEnable     = 0x00100000,     /* (JE)Enable jumbo frame for Tx         20           RW                */
  GmacJumboFrameDisable    = 0x00000000,     /* Disable jumbo frame                                          0       */

  GmacInterFrameGap7       = 0x000E0000,     /* (IFG) Config7 - 40 bit times          19:17        RW                */
  GmacInterFrameGap6       = 0x000C0000,     /* (IFG) Config6 - 48 bit times                                         */
  GmacInterFrameGap5       = 0x000A0000,     /* (IFG) Config5 - 56 bit times                                         */
  GmacInterFrameGap4       = 0x00080000,     /* (IFG) Config4 - 64 bit times                                         */
  GmacInterFrameGap3       = 0x00060000,     /* (IFG) Config3 - 72 bit times                                         */
  GmacInterFrameGap2       = 0x00040000,     /* (IFG) Config2 - 80 bit times                                         */
  GmacInterFrameGap1       = 0x00020000,     /* (IFG) Config1 - 88 bit times                                         */
  GmacInterFrameGap0       = 0x00000000,     /* (IFG) Config0 - 96 bit times                                 000     */

  GmacDisableCrs	   = 0x00010000,
  GmacMiiGmii		   = 0x00008000,
  GmacSelectMii            = 0x00008000,     /* (PS)Port Select-MII mode              15           RW                */
  GmacSelectGmii           = 0x00000000,     /* GMII mode                                                    0       */
   GmacFESpeed100           = 0x00004000,     /*(FES)Fast Ethernet speed 100Mbps       14           RW                */
  GmacFESpeed10            = 0x00000000,     /* 10Mbps                                                       0       */

  GmacRxOwn		   = 0x00002000,
  GmacDisableRxOwn         = 0x00002000,     /* (DO)Disable receive own packets       13           RW                */
  GmacEnableRxOwn          = 0x00000000,     /* Enable receive own packets                                   0       */

  GmacLoopback		   = 0x00001000,
  GmacLoopbackOn           = 0x00001000,     /* (LM)Loopback mode for GMII/MII        12           RW                */
  GmacLoopbackOff          = 0x00000000,     /* Normal mode                                                  0       */

  GmacDuplex		   = 0x00000800,
  GmacFullDuplex           = 0x00000800,     /* (DM)Full duplex mode                  11           RW                */
  GmacHalfDuplex           = 0x00000000,     /* Half duplex mode                                             0       */

  GmacRxIpcOffload	   = 0x00000400,     /*IPC checksum offload		      10           RW        0       */

  GmacRetry		   = 0x00000200,
  GmacRetryDisable         = 0x00000200,     /* (DR)Disable Retry                      9           RW                */
  GmacRetryEnable          = 0x00000000,     /* Enable retransmission as per BL                              0       */

  GmacLinkUp               = 0x00000100,     /* (LUD)Link UP                           8           RW                */
  GmacLinkDown             = 0x00000100,     /* Link Down                                                    0       */

  GmacCRCEthStrip          =  0x02000000,    /*(CST) CRC Stripping for Type Frames*/
  GmacCRCEthStripEnable    =  0x02000000,
  GmacCRCEthStripDisable   =  0x00000000,

  GmacPadCrcStrip	   = 0x00000080,
  GmacPadCrcStripEnable    = 0x00000080,     /* (ACS) Automatic Pad/Crc strip enable   7           RW                */
  GmacPadCrcStripDisable   = 0x00000000,     /* Automatic Pad/Crc stripping disable                          0       */

  GmacBackoffLimit	   = 0x00000060,
  GmacBackoffLimit3        = 0x00000060,     /* (BL)Back-off limit in HD mode          6:5         RW                */
  GmacBackoffLimit2        = 0x00000040,     /*                                                                      */
  GmacBackoffLimit1        = 0x00000020,     /*                                                                      */
  GmacBackoffLimit0        = 0x00000000,     /*                                                              00      */

  GmacDeferralCheck	   = 0x00000010,
  GmacDeferralCheckEnable  = 0x00000010,     /* (DC)Deferral check enable in HD mode   4           RW                */
  GmacDeferralCheckDisable = 0x00000000,     /* Deferral check disable                                       0       */

  GmacTx		   = 0x00000008,
  GmacTxEnable             = 0x00000008,     /* (TE)Transmitter enable                 3           RW                */
  GmacTxDisable            = 0x00000000,     /* Transmitter disable                                          0       */

  GmacRx		   = 0x00000004,
  GmacRxEnable             = 0x00000004,     /* (RE)Receiver enable                    2           RW                */
  GmacRxDisable            = 0x00000000,     /* Receiver disable                                             0       */
};

/* GmacFrameFilter    = 0x0004,     Mac frame filtering controls Register Layout*/
enum GmacFrameFilterReg
{
  GmacFilter		   = 0x80000000,
  GmacFilterOff            = 0x80000000,     /* (RA)Receive all incoming packets       31         RW                 */
  GmacFilterOn             = 0x00000000,     /* Receive filtered packets only                                0       */

  GmacHashPerfectFilter	   = 0x00000400,     /*Hash or Perfect Filter enable           10         RW         0       */

  GmacSrcAddrFilter	   = 0x00000200,
  GmacSrcAddrFilterEnable  = 0x00000200,     /* (SAF)Source Address Filter enable       9         RW                 */
  GmacSrcAddrFilterDisable = 0x00000000,     /*                                                              0       */

  GmacSrcInvaAddrFilter    = 0x00000100,
  GmacSrcInvAddrFilterEn   = 0x00000100,     /* (SAIF)Inv Src Addr Filter enable        8         RW                 */
  GmacSrcInvAddrFilterDis  = 0x00000000,     /*                                                              0       */

  GmacPassControl	   = 0x000000C0,
  GmacPassControl3         = 0x000000C0,     /* (PCF)MAC forwards control frames that pass the Address Filter    7:6       RW                 */
  GmacPassControl2         = 0x00000080,     /* MAC forwards all control frames to application even if they fail the Address Filter*/
  GmacPassControl1         = 0x00000040,     /* MAC forwards all control frames except Pause frames to application even if they fail the Address filter. */
  GmacPassControl0         = 0x00000000,     /* MAC filters all control frames from reaching the application.    00      */

  GmacBroadcast		   = 0x00000020,
  GmacBroadcastDisable     = 0x00000020,     /* (DBF)Disable Rx of broadcast frames     5         RW                 */
  GmacBroadcastEnable      = 0x00000000,     /* Enable broadcast frames                                      0       */

  GmacMulticastFilter      = 0x00000010,
  GmacMulticastFilterOff   = 0x00000010,     /* (PM) Pass all multicast packets         4         RW                 */
  GmacMulticastFilterOn    = 0x00000000,     /* Pass filtered multicast packets                              0       */

  GmacDestAddrFilter       = 0x00000008,
  GmacDestAddrFilterInv    = 0x00000008,     /* (DAIF)Inverse filtering for DA          3         RW                 */
  GmacDestAddrFilterNor    = 0x00000000,     /* Normal filtering for DA                                      0       */

  GmacMcastHashFilter      = 0x00000004,
  GmacMcastHashFilterOn    = 0x00000004,     /* (HMC)perfom multicast hash filtering    2         RW                 */
  GmacMcastHashFilterOff   = 0x00000000,     /* perfect filtering only                                       0       */

  GmacUcastHashFilter      = 0x00000002,
  GmacUcastHashFilterOn    = 0x00000002,     /* (HUC)Unicast Hash filtering only        1         RW                 */
  GmacUcastHashFilterOff   = 0x00000000,     /* perfect filtering only                                       0       */

  GmacPromiscuousMode      = 0x00000001,
  GmacPromiscuousModeOn    = 0x00000001,     /* Receive all frames                      0         RW                 */
  GmacPromiscuousModeOff   = 0x00000000,     /* Receive filtered packets only                                0       */
};

/*GmacGmiiAddr             = 0x0010,    GMII address Register(ext. Phy) Layout          */
enum GmacGmiiAddrReg
{
  GmiiDevMask              = 0x0000F800,     /* (PA)GMII device address                 15:11     RW         0x00    */
  GmiiDevShift             = 11,

  GmiiRegMask              = 0x000007C0,     /* (GR)GMII register in selected Phy       10:6      RW         0x00    */
  GmiiRegShift             = 6,

  GmiiCsrClkMask	   = 0x0000001C,     /*CSR Clock bit Mask			 4:2			     */
  GmiiCsrClk5              = 0x00000014,     /* (CR)CSR Clock Range     250-300 MHz      4:2      RW         000     */
  GmiiCsrClk4              = 0x00000010,     /*                         150-250 MHz                                  */
  GmiiCsrClk3              = 0x0000000C,     /*                         35-60 MHz                                    */
  GmiiCsrClk2              = 0x00000008,     /*                         20-35 MHz                                    */
  GmiiCsrClk1              = 0x00000004,     /*                         100-150 MHz                                  */
  GmiiCsrClk0              = 0x00000000,     /*                         60-100 MHz                                   */

  GmiiWrite                = 0x00000002,     /* (GW)Write to register                      1      RW                 */
  GmiiRead                 = 0x00000000,     /* Read from register                                            0      */

  GmiiBusy                 = 0x00000001,     /* (GB)GMII interface is busy                 0      RW          0      */
};


/*GmacFlowControl    = 0x0018,    Flow control Register   Layout                  */
enum GmacFlowControlReg
{
  GmacPauseTimeMask        = 0xFFFF0000,     /* (PT) PAUSE TIME field in the control frame  31:16   RW       0x0000  */
  GmacPauseTimeShift       = 16,

  GmacPauseLowThresh	   = 0x00000030,
  GmacPauseLowThresh3      = 0x00000030,     /* (PLT)thresh for pause tmr 256 slot time      5:4    RW               */
  GmacPauseLowThresh2      = 0x00000020,     /*                           144 slot time                              */
  GmacPauseLowThresh1      = 0x00000010,     /*                            28 slot time                              */
  GmacPauseLowThresh0      = 0x00000000,     /*                             4 slot time                       000    */

  GmacUnicastPauseFrame    = 0x00000008,
  GmacUnicastPauseFrameOn  = 0x00000008,     /* (UP)Detect pause frame with unicast addr.     3    RW                */
  GmacUnicastPauseFrameOff = 0x00000000,     /* Detect only pause frame with multicast addr.                   0     */

  GmacRxFlowControl	   = 0x00000004,
  GmacRxFlowControlEnable  = 0x00000004,     /* (RFE)Enable Rx flow control                   2    RW                */
  GmacRxFlowControlDisable = 0x00000000,     /* Disable Rx flow control                                        0     */

  GmacTxFlowControl   	   = 0x00000002,
  GmacTxFlowControlEnable  = 0x00000002,     /* (TFE)Enable Tx flow control                   1    RW                */
  GmacTxFlowControlDisable = 0x00000000,     /* Disable flow control                                           0     */

  GmacFlowControlBackPressure= 0x00000001,
  GmacSendPauseFrame       = 0x00000001,     /* (FCB/PBA)send pause frm/Apply back pressure   0    RW          0     */
};

/* GmacGmiiData            = 0x0014,    GMII data Register(ext. Phy) Layout             */
enum GmacGmiiDataReg
{
  GmiiDataMask             = 0x0000FFFF,     /* (GD)GMII Data                             15:0    RW         0x0000  */
};

enum GmacPmtCtrlStatusBitDefinition
{
	GmacPmtFrmFilterPtrReset	= 0x80000000,		/* when set remote wake-up frame filter register pointer to 3'b000 */
	GmacPmtGlobalUnicast		= 0x00000200,		/* When set enables any unicast packet to be a wake-up frame       */
	GmacPmtWakeupFrameReceived	= 0x00000040,		/* Wake up frame received					   */
	GmacPmtMagicPktReceived		= 0x00000020,		/* Magic Packet received					   */
	GmacPmtWakeupFrameEnable	= 0x00000004,		/* Wake-up frame enable						   */
	GmacPmtMagicPktEnable		= 0x00000002,		/* Magic packet enable						   */
	GmacPmtPowerDown		= 0x00000001,		/* Power Down							   */
};


/*  GmacInterruptStatus	  = 0x0038,     Mac Interrupt ststus register	       */
enum GmacInterruptStatusBitDefinition
{
  GmacTSIntSts		   = 0x00000200,    /* set if int generated due to TS (Read Time Stamp Status Register to know details)*/
  GmacMmcRxChksumOffload   = 0x00000080,    /* set if int generated in MMC RX CHECKSUM OFFLOAD int register	                  */
  GmacMmcTxIntSts	   = 0x00000040,    /* set if int generated in MMC TX Int register			   */
  GmacMmcRxIntSts	   = 0x00000020,    /* set if int generated in MMC RX Int register 			   */
  GmacMmcIntSts		   = 0x00000010,    /* set if any of the above bit [7:5] is set			   */
  GmacPmtIntSts		   = 0x00000008,    /* set whenver magic pkt/wake-on-lan frame is received		   */
  GmacPcsAnComplete	   = 0x00000004,    /* set when AN is complete in TBI/RTBI/SGMIII phy interface        */
  GmacPcsLnkStsChange	   = 0x00000002,    /* set if any lnk status change in TBI/RTBI/SGMII interface        */
  GmacRgmiiIntSts	   = 0x00000001,    /* set if any change in lnk status of RGMII interface		   */

};

/*  GmacInterruptMask       = 0x003C,     Mac Interrupt Mask register	       */
enum GmacInterruptMaskBitDefinition
{
  GmacTSIntMask		   = 0x00000200,    /* when set disables the time stamp interrupt generation            */
  GmacPmtIntMask	   = 0x00000008,    /* when set Disables the assertion of PMT interrupt     	    	*/
  GmacPcsAnIntMask	   = 0x00000004,    /* When set disables the assertion of PCS AN complete interrupt	      	*/
  GmacPcsLnkStsIntMask	   = 0x00000002,    /* when set disables the assertion of PCS lnk status change interrupt	*/
  GmacRgmiiIntMask	   = 0x00000001,    /* when set disables the assertion of RGMII int 			*/
};

enum GmacTimestampControlReg
{
	GmacAuxiliarySnapshot3			= (1 << 28),	//When set, the Auxiliary snapshot of event on ptp_aux_trig_i[3] input is enabled.
	GmacAuxiliarySnapshot2			= (1 << 27),	//When set, the Auxiliary snapshot of event on ptp_aux_trig_i[2] input is enabled.
	GmacAuxiliarySnapshot1			= (1 << 26),	//When set, the Auxiliary snapshot of event on ptp_aux_trig_i[1] input is enabled.
	GmacAuxiliarySnapshot0			= (1 << 25),	//When set, the Auxiliary snapshot of event on ptp_aux_trig_i[0] input is enabled.
	GmacAuxiliarySnapshotFIFOClear	= (1 << 24),	//When set, it resets the pointers of the Auxiliary Snapshot FIFO.
	GmacEnableMACAddressFilter		= (1 << 18),	//When set, the DA MAC address is used to filter the PTP frames when PTP is directly sent over Ethernet.
	GmacSnapshotTpyeSelectBit17		= (1 << 17),	//bits [17:16] along with Bits 15 and 14 decide the set of PTP packet types for which snapshot needs to be taken.
	GmacSnapshotTpyeSelectBit16		= (1 << 16),	//bits [17:16] along with Bits 15 and 14 decide the set of PTP packet types for which snapshot needs to be taken.
	GmacSnapshotMaster				= (1 << 15),	//When set, the snapshot is taken only for the messages relevant to the master node.
	GmacSnapshotEvent				= (1 << 14),	//When set, the timestamp snapshot is taken only for event messages.
	GmacTimestampIPv4				= (1 << 13),	//When set, the MAC receiver processes PTP packets encapsulated in UDP over IPv4 packets.
	GmacTimestampIPv6				= (1 << 12),	//When set, the MAC receiver processes PTP packets encapsulated in UDP over IPv6 packets.
	GmacTimestampEthernet			= (1 << 11),	//When set, the MAC receiver processes the PTP packets encapsulated directly in the Ethernet frames.
	GmacPTPVersion2					= (1 << 10),	//When set, the PTP packets are processed using the 1588 version 2 format.
	GmacTimestampDigitalOrBinary	= (1 << 9),		//When set, System Time-Nanoseconds register has an accuracy of 1 ns.
	GmacTimestampEnableAll			= (1 << 8),		//When set, the timestamp snapshot is enabled for all frames received by the MAC.
	GmacAddendRegUpdate				= (1 << 5),		//When set, the content of the Timestamp Addend register is updated in the PTP block for fine correction.
	GmacTimestampIntEnable			= (1 << 4),		//When set, the timestamp interrupt is generated when the System Time
													//becomes greater than the value written in the Target Time register.
	GmacTimestampUpdate				= (1 << 3),		//When set, the system time is updated (added or subtracted) with the value specified in the Register 452 and Register 453.
	GmacTimestampInit				= (1 << 2),		//When set, the system time is initialized (overwritten) with the value specified in the Register 452 and Register 453.
	GmacptpUpdateMethod				= (1 << 1),		//When set, this bit indicates that the system times update should be done using the fine update method.
	GmacTimstampEnable				= (1 << 0),		//When set, the timestamp is added for the transmit and receive frames.
};

//Register 453 (System Time – Nanoseconds Update Register) = 0x0710
enum GmacSystemTimeLowUpdateReg
{
	GmacSUBTIME				= (1 << 31),		//When set,the time value is subtracted with the contents of the update register.
	GmacTSSS				= 0x7fffffff,		//Timestamp low value.
};

/*
 * Register 448 (Timestamp Control Register)bit 1:Timestamp Fine or Coarse Update
 * When set, this bit indicates that the system times update should be
 * done using the fine update method. When reset, it indicates the
 * system timestamp update should be done using the Coarse method.
 */
enum GmacPtpUpdateMethod
{
	GmacPtpFineCorrectionMethod,				//set bit 1
	GmacPtpCoarseCorrectionMethod,				//reset bit 1
};

/*
 * Register 453 (System Time – Nanoseconds Update Register) bit 31:Add or Subtract Time
 * When this bit is set, the time value is subtracted with the contents of the
 * update register. When this bit is reset, the time value is added with the
 * contents of the update register.
 */
enum GmacPtpSystemTimeUpdateStyle
{
	GmacPtpSystemTimeUpdateSubtract,			//set bit 31
	GmacPtpSystemTimeUpdateAdd,					//reset bit 31
};


/*
 * Register 448 (Timestamp Control Register)bit 10:Enable PTP packet Processing for Version 2 Format
 * When set, the PTP packets are processed using the 1588 version 2 format.
 * Otherwise, the PTP packets are processed using the version 1 format.
 */
enum GmacPtpVersionFormat
{
	GmacPtpVersion1,							//set bit 10
	GmacPtpVersion2,							//reset bit 10
};
#define DEFAULT_GMAC_BASE_CTRL (GmacWatchdogEnable | GmacJumboFrameEnable | GmacCRCEthStripEnable | GmacPadCrcStripEnable)
//gmac function

void        gmac_init(void);

#endif

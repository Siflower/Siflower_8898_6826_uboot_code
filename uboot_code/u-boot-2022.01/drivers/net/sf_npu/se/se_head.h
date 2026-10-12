//
// Version: 3439., 2021-12-27 11:13:30
//

#ifndef __SE_REG_H__
#define __SE_REG_H__

//-------------------------------------------------------------------------
// SE BASE ADDR:
//-------------------------------------------------------------------------
#ifndef SE_BASE_ADDR
#define SE_BASE_ADDR (0x11000000)
#endif

//-------------------------------------------------------------------------
// INT_STATUS_RGT INFO:
//-------------------------------------------------------------------------
#define SE_INT_STATUS_RGT_REG_ADDR (SE_BASE_ADDR+0x180000)
#define INT_STATUS_RGT_MDF_OVF_INT_FIELD_OFFSET (11)
#define INT_STATUS_RGT_MDF_OVF_INT_FIELD_SIZE   (1)
#define INT_STATUS_RGT_EVXLT_LKP_OVF_INT_FIELD_OFFSET (10)
#define INT_STATUS_RGT_EVXLT_LKP_OVF_INT_FIELD_SIZE   (1)
#define INT_STATUS_RGT_EVLKP_LKP_OVF_INT_FIELD_OFFSET (9)
#define INT_STATUS_RGT_EVLKP_LKP_OVF_INT_FIELD_SIZE   (1)
#define INT_STATUS_RGT_EVSCH_OVF_INT_FIELD_OFFSET (8)
#define INT_STATUS_RGT_EVSCH_OVF_INT_FIELD_SIZE   (1)
#define INT_STATUS_RGT_MACSCH_OVF_INT_FIELD_OFFSET (7)
#define INT_STATUS_RGT_MACSCH_OVF_INT_FIELD_SIZE   (1)
#define INT_STATUS_RGT_MSPLS_OVF_INT_FIELD_OFFSET (6)
#define INT_STATUS_RGT_MSPLS_OVF_INT_FIELD_SIZE   (1)
#define INT_STATUS_RGT_MACSPL_LKP_OVF_INT_FIELD_OFFSET (5)
#define INT_STATUS_RGT_MACSPL_LKP_OVF_INT_FIELD_SIZE   (1)
#define INT_STATUS_RGT_L2_LKP_BUF_OVF_INT_FIELD_OFFSET (4)
#define INT_STATUS_RGT_L2_LKP_BUF_OVF_INT_FIELD_SIZE   (1)
#define INT_STATUS_RGT_L2_LKP_SCH_OVF_INT_FIELD_OFFSET (3)
#define INT_STATUS_RGT_L2_LKP_SCH_OVF_INT_FIELD_SIZE   (1)
#define INT_STATUS_RGT_IVXLT_OVF_INT_FIELD_OFFSET (2)
#define INT_STATUS_RGT_IVXLT_OVF_INT_FIELD_SIZE   (1)
#define INT_STATUS_RGT_IVLKP_OVF_INT_FIELD_OFFSET (1)
#define INT_STATUS_RGT_IVLKP_OVF_INT_FIELD_SIZE   (1)
#define INT_STATUS_RGT_IVPSPL_LKP_OVF_INT_FIELD_OFFSET (0)
#define INT_STATUS_RGT_IVPSPL_LKP_OVF_INT_FIELD_SIZE   (1)
	
//-------------------------------------------------------------------------
// CLR_RAM_CTRL_RGT INFO:
//-------------------------------------------------------------------------
#define SE_CLR_RAM_CTRL_RGT_REG_ADDR (SE_BASE_ADDR+0x180004)
#define CLR_RAM_CTRL_RGT_MODIFY_COPY_TB_CLR_FIELD_OFFSET (15)
#define CLR_RAM_CTRL_RGT_MODIFY_COPY_TB_CLR_FIELD_SIZE   (1)
#define CLR_RAM_CTRL_RGT_EVLAN_ACTION_TB_CLR_FIELD_OFFSET (14)
#define CLR_RAM_CTRL_RGT_EVLAN_ACTION_TB_CLR_FIELD_SIZE   (1)
#define CLR_RAM_CTRL_RGT_EVLAN_LOOKUP_TB_CLR_FIELD_OFFSET (13)
#define CLR_RAM_CTRL_RGT_EVLAN_LOOKUP_TB_CLR_FIELD_SIZE   (1)
#define CLR_RAM_CTRL_RGT_EVLAN_TRANSLATE_TB_CLR_FIELD_OFFSET (12)
#define CLR_RAM_CTRL_RGT_EVLAN_TRANSLATE_TB_CLR_FIELD_SIZE   (1)
#define CLR_RAM_CTRL_RGT_EVLAN_PORT_TPID_TB_CLR_FIELD_OFFSET (11)
#define CLR_RAM_CTRL_RGT_EVLAN_PORT_TPID_TB_CLR_FIELD_SIZE   (1)
#define CLR_RAM_CTRL_RGT_EVLAN_OUT_TPID_TB_CLR_FIELD_OFFSET (10)
#define CLR_RAM_CTRL_RGT_EVLAN_OUT_TPID_TB_CLR_FIELD_SIZE   (1)
#define CLR_RAM_CTRL_RGT_INTF_TB_CLR_FIELD_OFFSET (9)
#define CLR_RAM_CTRL_RGT_INTF_TB_CLR_FIELD_SIZE   (1)
#define CLR_RAM_CTRL_RGT_MAC_SPEED_LIMIT_TB_CLR_FIELD_OFFSET (8)
#define CLR_RAM_CTRL_RGT_MAC_SPEED_LIMIT_TB_CLR_FIELD_SIZE   (1)
#define CLR_RAM_CTRL_RGT_MAC_TB_CLR_FIELD_OFFSET (7)
#define CLR_RAM_CTRL_RGT_MAC_TB_CLR_FIELD_SIZE   (1)
#define CLR_RAM_CTRL_RGT_L2_HASH_TB1_CLR_FIELD_OFFSET (6)
#define CLR_RAM_CTRL_RGT_L2_HASH_TB1_CLR_FIELD_SIZE   (1)
#define CLR_RAM_CTRL_RGT_L2_HASH_TB0_CLR_FIELD_OFFSET (5)
#define CLR_RAM_CTRL_RGT_L2_HASH_TB0_CLR_FIELD_SIZE   (1)
#define CLR_RAM_CTRL_RGT_IVLAN_LOOKUP_TB_CLR_FIELD_OFFSET (4)
#define CLR_RAM_CTRL_RGT_IVLAN_LOOKUP_TB_CLR_FIELD_SIZE   (1)
#define CLR_RAM_CTRL_RGT_IPORT_BASED_VLAN_TB_CLR_FIELD_OFFSET (3)
#define CLR_RAM_CTRL_RGT_IPORT_BASED_VLAN_TB_CLR_FIELD_SIZE   (1)
#define CLR_RAM_CTRL_RGT_IVLAN_XLT_TB_CLR_FIELD_OFFSET (2)
#define CLR_RAM_CTRL_RGT_IVLAN_XLT_TB_CLR_FIELD_SIZE   (1)
#define CLR_RAM_CTRL_RGT_IPORT_TB_CLR_FIELD_OFFSET (1)
#define CLR_RAM_CTRL_RGT_IPORT_TB_CLR_FIELD_SIZE   (1)
#define CLR_RAM_CTRL_RGT_IPORT_SPEED_LIMIT_TB_CLR_FIELD_OFFSET (0)
#define CLR_RAM_CTRL_RGT_IPORT_SPEED_LIMIT_TB_CLR_FIELD_SIZE   (1)
	
//-------------------------------------------------------------------------
// CONFIG0_RGT INFO:
//-------------------------------------------------------------------------
#define SE_CONFIG0_RGT_REG_ADDR (SE_BASE_ADDR+0x180008)
#define CONFIG0_RGT_RESERVED1_FIELD_OFFSET (17)
#define CONFIG0_RGT_RESERVED1_FIELD_SIZE   (15)
#define CONFIG0_RGT_IVLKP_CFG_DIS_TB_FIELD_OFFSET (16)
#define CONFIG0_RGT_IVLKP_CFG_DIS_TB_FIELD_SIZE   (1)
#define CONFIG0_RGT_IVLKP_CFG_ENTR_MINUS_ONE_FIELD_OFFSET (10)
#define CONFIG0_RGT_IVLKP_CFG_ENTR_MINUS_ONE_FIELD_SIZE   (6)
#define CONFIG0_RGT_PORTBV_TABLE_VLD_FIELD_OFFSET (9)
#define CONFIG0_RGT_PORTBV_TABLE_VLD_FIELD_SIZE   (1)
#define CONFIG0_RGT_IPORT_TABLE_VLD_FIELD_OFFSET (8)
#define CONFIG0_RGT_IPORT_TABLE_VLD_FIELD_SIZE   (1)
#define CONFIG0_RGT_IVXLT_CFG_DIS_TB_FIELD_OFFSET (7)
#define CONFIG0_RGT_IVXLT_CFG_DIS_TB_FIELD_SIZE   (1)
#define CONFIG0_RGT_IVXLT_CFG_ENTR_MINUS_ONE_FIELD_OFFSET (1)
#define CONFIG0_RGT_IVXLT_CFG_ENTR_MINUS_ONE_FIELD_SIZE   (6)
#define CONFIG0_RGT_IVPSPL_MODE_FIELD_OFFSET (0)
#define CONFIG0_RGT_IVPSPL_MODE_FIELD_SIZE   (1)
	
//-------------------------------------------------------------------------
// CONFIG1_RGT INFO:
//-------------------------------------------------------------------------
#define SE_CONFIG1_RGT_REG_ADDR (SE_BASE_ADDR+0x18000C)
#define CONFIG1_RGT_RESERVED2_FIELD_OFFSET (30)
#define CONFIG1_RGT_RESERVED2_FIELD_SIZE   (2)
#define CONFIG1_RGT_L2_HASH_POLY_SEL9_FIELD_OFFSET (27)
#define CONFIG1_RGT_L2_HASH_POLY_SEL9_FIELD_SIZE   (3)
#define CONFIG1_RGT_L2_HASH_POLY_SEL8_FIELD_OFFSET (24)
#define CONFIG1_RGT_L2_HASH_POLY_SEL8_FIELD_SIZE   (3)
#define CONFIG1_RGT_L2_HASH_POLY_SEL7_FIELD_OFFSET (21)
#define CONFIG1_RGT_L2_HASH_POLY_SEL7_FIELD_SIZE   (3)
#define CONFIG1_RGT_L2_HASH_POLY_SEL6_FIELD_OFFSET (18)
#define CONFIG1_RGT_L2_HASH_POLY_SEL6_FIELD_SIZE   (3)
#define CONFIG1_RGT_L2_HASH_POLY_SEL5_FIELD_OFFSET (15)
#define CONFIG1_RGT_L2_HASH_POLY_SEL5_FIELD_SIZE   (3)
#define CONFIG1_RGT_L2_HASH_POLY_SEL4_FIELD_OFFSET (12)
#define CONFIG1_RGT_L2_HASH_POLY_SEL4_FIELD_SIZE   (3)
#define CONFIG1_RGT_L2_HASH_POLY_SEL3_FIELD_OFFSET (9)
#define CONFIG1_RGT_L2_HASH_POLY_SEL3_FIELD_SIZE   (3)
#define CONFIG1_RGT_L2_HASH_POLY_SEL2_FIELD_OFFSET (6)
#define CONFIG1_RGT_L2_HASH_POLY_SEL2_FIELD_SIZE   (3)
#define CONFIG1_RGT_L2_HASH_POLY_SEL1_FIELD_OFFSET (3)
#define CONFIG1_RGT_L2_HASH_POLY_SEL1_FIELD_SIZE   (3)
#define CONFIG1_RGT_L2_HASH_POLY_SEL0_FIELD_OFFSET (0)
#define CONFIG1_RGT_L2_HASH_POLY_SEL0_FIELD_SIZE   (3)
	
//-------------------------------------------------------------------------
// CONFIG2_RGT INFO:
//-------------------------------------------------------------------------
#define SE_CONFIG2_RGT_REG_ADDR (SE_BASE_ADDR+0x180010)
#define CONFIG2_RGT_EVACT_TABLE_VLD_FIELD_OFFSET (31)
#define CONFIG2_RGT_EVACT_TABLE_VLD_FIELD_SIZE   (1)
#define CONFIG2_RGT_EVXLT_CFG_DIS_TB_FIELD_OFFSET (30)
#define CONFIG2_RGT_EVXLT_CFG_DIS_TB_FIELD_SIZE   (1)
#define CONFIG2_RGT_EVXLT_CFG_ENTR_MINUS_ONE_FIELD_OFFSET (24)
#define CONFIG2_RGT_EVXLT_CFG_ENTR_MINUS_ONE_FIELD_SIZE   (6)
#define CONFIG2_RGT_RESERVED2_FIELD_OFFSET (17)
#define CONFIG2_RGT_RESERVED2_FIELD_SIZE   (7)
#define CONFIG2_RGT_PTPID_TABLE_VLD_FIELD_OFFSET (16)
#define CONFIG2_RGT_PTPID_TABLE_VLD_FIELD_SIZE   (1)
#define CONFIG2_RGT_OTPID_TABLE_VLD_FIELD_OFFSET (15)
#define CONFIG2_RGT_OTPID_TABLE_VLD_FIELD_SIZE   (1)
#define CONFIG2_RGT_EVLKP_CFG_DIS_TB_FIELD_OFFSET (14)
#define CONFIG2_RGT_EVLKP_CFG_DIS_TB_FIELD_SIZE   (1)
#define CONFIG2_RGT_EVLKP_CFG_ENTR_MINUS_ONE_FIELD_OFFSET (8)
#define CONFIG2_RGT_EVLKP_CFG_ENTR_MINUS_ONE_FIELD_SIZE   (6)
#define CONFIG2_RGT_INTF_TABLE_VLD_FIELD_OFFSET (7)
#define CONFIG2_RGT_INTF_TABLE_VLD_FIELD_SIZE   (1)
#define CONFIG2_RGT_MAC_TABLE_VLD_FIELD_OFFSET (6)
#define CONFIG2_RGT_MAC_TABLE_VLD_FIELD_SIZE   (1)
#define CONFIG2_RGT_MACSPL_MODE_FIELD_OFFSET (5)
#define CONFIG2_RGT_MACSPL_MODE_FIELD_SIZE   (1)
#define CONFIG2_RGT_L2_AGE_CLR_AFTER_RD_FIELD_OFFSET (4)
#define CONFIG2_RGT_L2_AGE_CLR_AFTER_RD_FIELD_SIZE   (1)
#define CONFIG2_RGT_L2_SEG_NUM_MINUS_ONE_FIELD_OFFSET (0)
#define CONFIG2_RGT_L2_SEG_NUM_MINUS_ONE_FIELD_SIZE   (4)
	
//-------------------------------------------------------------------------
// CONFIG3_RGT INFO:
//-------------------------------------------------------------------------
#define SE_CONFIG3_RGT_REG_ADDR (SE_BASE_ADDR+0x180014)
	
//-------------------------------------------------------------------------
// CONFIG4_RGT INFO:
//-------------------------------------------------------------------------
#define SE_CONFIG4_RGT_REG_ADDR (SE_BASE_ADDR+0x180018)
	
//-------------------------------------------------------------------------
// CONFIG5_RGT INFO:
//-------------------------------------------------------------------------
#define SE_CONFIG5_RGT_REG_ADDR (SE_BASE_ADDR+0x18001C)
	
//-------------------------------------------------------------------------
// CONFIG6_RGT INFO:
//-------------------------------------------------------------------------
#define SE_CONFIG6_RGT_REG_ADDR (SE_BASE_ADDR+0x180020)
	
//-------------------------------------------------------------------------
// CONFIG7_RGT INFO:
//-------------------------------------------------------------------------
#define SE_CONFIG7_RGT_REG_ADDR (SE_BASE_ADDR+0x180024)
	
//-------------------------------------------------------------------------
// SPL_CONFIG0_RGT INFO:
//-------------------------------------------------------------------------
#define SE_SPL_CONFIG0_RGT_REG_ADDR (SE_BASE_ADDR+0x180028)
#define SPL_CONFIG0_RGT_MAC_SPL_TIMER_MINUS1_FIELD_OFFSET (0)
#define SPL_CONFIG0_RGT_MAC_SPL_TIMER_MINUS1_FIELD_SIZE   (32)
	
//-------------------------------------------------------------------------
// SPL_CONFIG1_RGT INFO:
//-------------------------------------------------------------------------
#define SE_SPL_CONFIG1_RGT_REG_ADDR (SE_BASE_ADDR+0x18002c)
#define SPL_CONFIG1_RGT_IVP_SPL_TIMER_MINUS1_FIELD_OFFSET (0)
#define SPL_CONFIG1_RGT_IVP_SPL_TIMER_MINUS1_FIELD_SIZE   (32)
	
//-------------------------------------------------------------------------
// TB_OP_ADDR_RGT INFO:
//-------------------------------------------------------------------------
#define SE_TB_OP_ADDR_RGT_REG_ADDR (SE_BASE_ADDR+0x18003C)
#define TB_OP_ADDR_RGT_HOST_MGT_REQ_FIELD_OFFSET (31)
#define TB_OP_ADDR_RGT_HOST_MGT_REQ_FIELD_SIZE   (1)
#define TB_OP_ADDR_RGT_HOST_MGT_REQ_OPCODE_FIELD_OFFSET (24)
#define TB_OP_ADDR_RGT_HOST_MGT_REQ_OPCODE_FIELD_SIZE   (1)
#define TB_OP_ADDR_RGT_HOST_MGT_REQ_ID_FIELD_OFFSET (16)
#define TB_OP_ADDR_RGT_HOST_MGT_REQ_ID_FIELD_SIZE   (5)
#define TB_OP_ADDR_RGT_HOST_MGT_REQ_ADDR_FIELD_OFFSET (0)
#define TB_OP_ADDR_RGT_HOST_MGT_REQ_ADDR_FIELD_SIZE   (16)
	
//-------------------------------------------------------------------------
// TB_WRDATA00_RGT INFO:
//-------------------------------------------------------------------------
#define SE_TB_WRDATA00_RGT_REG_ADDR (SE_BASE_ADDR+0x180040)
#define TB_WRDATA00_RGT_TB_WRDATA00_FIELD_OFFSET (0)
#define TB_WRDATA00_RGT_TB_WRDATA00_FIELD_SIZE   (32)
	
//-------------------------------------------------------------------------
// TB_WRDATA01_RGT INFO:
//-------------------------------------------------------------------------
#define SE_TB_WRDATA01_RGT_REG_ADDR (SE_BASE_ADDR+0x180044)
#define TB_WRDATA01_RGT_TB_WRDATA01_FIELD_OFFSET (0)
#define TB_WRDATA01_RGT_TB_WRDATA01_FIELD_SIZE   (32)
	
//-------------------------------------------------------------------------
// TB_WRDATA02_RGT INFO:
//-------------------------------------------------------------------------
#define SE_TB_WRDATA02_RGT_REG_ADDR (SE_BASE_ADDR+0x180048)
#define TB_WRDATA02_RGT_TB_WRDATA02_FIELD_OFFSET (0)
#define TB_WRDATA02_RGT_TB_WRDATA02_FIELD_SIZE   (32)
	
//-------------------------------------------------------------------------
// TB_WRDATA03_RGT INFO:
//-------------------------------------------------------------------------
#define SE_TB_WRDATA03_RGT_REG_ADDR (SE_BASE_ADDR+0x18004c)
#define TB_WRDATA03_RGT_TB_WRDATA03_FIELD_OFFSET (0)
#define TB_WRDATA03_RGT_TB_WRDATA03_FIELD_SIZE   (32)
	
//-------------------------------------------------------------------------
// TB_WRDATA04_RGT INFO:
//-------------------------------------------------------------------------
#define SE_TB_WRDATA04_RGT_REG_ADDR (SE_BASE_ADDR+0x180050)
#define TB_WRDATA04_RGT_TB_WRDATA04_FIELD_OFFSET (0)
#define TB_WRDATA04_RGT_TB_WRDATA04_FIELD_SIZE   (32)
	
//-------------------------------------------------------------------------
// TB_WRDATA05_RGT INFO:
//-------------------------------------------------------------------------
#define SE_TB_WRDATA05_RGT_REG_ADDR (SE_BASE_ADDR+0x180054)
#define TB_WRDATA05_RGT_TB_WRDATA05_FIELD_OFFSET (0)
#define TB_WRDATA05_RGT_TB_WRDATA05_FIELD_SIZE   (32)
	
//-------------------------------------------------------------------------
// TB_WRDATA06_RGT INFO:
//-------------------------------------------------------------------------
#define SE_TB_WRDATA06_RGT_REG_ADDR (SE_BASE_ADDR+0x180058)
#define TB_WRDATA06_RGT_TB_WRDATA06_FIELD_OFFSET (0)
#define TB_WRDATA06_RGT_TB_WRDATA06_FIELD_SIZE   (32)
	
//-------------------------------------------------------------------------
// TB_WRDATA07_RGT INFO:
//-------------------------------------------------------------------------
#define SE_TB_WRDATA07_RGT_REG_ADDR (SE_BASE_ADDR+0x18005c)
#define TB_WRDATA07_RGT_TB_WRDATA07_FIELD_OFFSET (0)
#define TB_WRDATA07_RGT_TB_WRDATA07_FIELD_SIZE   (32)
	
//-------------------------------------------------------------------------
// TB_WRDATA08_RGT INFO:
//-------------------------------------------------------------------------
#define SE_TB_WRDATA08_RGT_REG_ADDR (SE_BASE_ADDR+0x180060)
#define TB_WRDATA08_RGT_TB_WRDATA08_FIELD_OFFSET (0)
#define TB_WRDATA08_RGT_TB_WRDATA08_FIELD_SIZE   (32)
	
//-------------------------------------------------------------------------
// TB_WRDATA09_RGT INFO:
//-------------------------------------------------------------------------
#define SE_TB_WRDATA09_RGT_REG_ADDR (SE_BASE_ADDR+0x180064)
#define TB_WRDATA09_RGT_TB_WRDATA09_FIELD_OFFSET (0)
#define TB_WRDATA09_RGT_TB_WRDATA09_FIELD_SIZE   (32)
	
//-------------------------------------------------------------------------
// TB_WRDATA10_RGT INFO:
//-------------------------------------------------------------------------
#define SE_TB_WRDATA10_RGT_REG_ADDR (SE_BASE_ADDR+0x180068)
#define TB_WRDATA10_RGT_TB_WRDATA10_FIELD_OFFSET (0)
#define TB_WRDATA10_RGT_TB_WRDATA10_FIELD_SIZE   (32)
	
//-------------------------------------------------------------------------
// TB_WRDATA11_RGT INFO:
//-------------------------------------------------------------------------
#define SE_TB_WRDATA11_RGT_REG_ADDR (SE_BASE_ADDR+0x18006c)
#define TB_WRDATA11_RGT_TB_WRDATA11_FIELD_OFFSET (0)
#define TB_WRDATA11_RGT_TB_WRDATA11_FIELD_SIZE   (32)
	
//-------------------------------------------------------------------------
// TB_WRDATA12_RGT INFO:
//-------------------------------------------------------------------------
#define SE_TB_WRDATA12_RGT_REG_ADDR (SE_BASE_ADDR+0x180070)
#define TB_WRDATA12_RGT_TB_WRDATA12_FIELD_OFFSET (0)
#define TB_WRDATA12_RGT_TB_WRDATA12_FIELD_SIZE   (32)
	
//-------------------------------------------------------------------------
// TB_WRDATA13_RGT INFO:
//-------------------------------------------------------------------------
#define SE_TB_WRDATA13_RGT_REG_ADDR (SE_BASE_ADDR+0x180074)
#define TB_WRDATA13_RGT_TB_WRDATA13_FIELD_OFFSET (0)
#define TB_WRDATA13_RGT_TB_WRDATA13_FIELD_SIZE   (32)
	
//-------------------------------------------------------------------------
// TB_WRDATA14_RGT INFO:
//-------------------------------------------------------------------------
#define SE_TB_WRDATA14_RGT_REG_ADDR (SE_BASE_ADDR+0x180078)
#define TB_WRDATA14_RGT_TB_WRDATA14_FIELD_OFFSET (0)
#define TB_WRDATA14_RGT_TB_WRDATA14_FIELD_SIZE   (32)
	
//-------------------------------------------------------------------------
// TB_WRDATA15_RGT INFO:
//-------------------------------------------------------------------------
#define SE_TB_WRDATA15_RGT_REG_ADDR (SE_BASE_ADDR+0x18007c)
#define TB_WRDATA15_RGT_TB_WRDATA15_FIELD_OFFSET (0)
#define TB_WRDATA15_RGT_TB_WRDATA15_FIELD_SIZE   (32)
	
//-------------------------------------------------------------------------
// TB_RDDATA00_RGT INFO:
//-------------------------------------------------------------------------
#define SE_TB_RDDATA00_RGT_REG_ADDR (SE_BASE_ADDR+0x180080)
#define TB_RDDATA00_RGT_TB_RDDATA00_FIELD_OFFSET (0)
#define TB_RDDATA00_RGT_TB_RDDATA00_FIELD_SIZE   (32)
	
//-------------------------------------------------------------------------
// TB_RDDATA01_RGT INFO:
//-------------------------------------------------------------------------
#define SE_TB_RDDATA01_RGT_REG_ADDR (SE_BASE_ADDR+0x180084)
#define TB_RDDATA01_RGT_TB_RDDATA01_FIELD_OFFSET (0)
#define TB_RDDATA01_RGT_TB_RDDATA01_FIELD_SIZE   (32)
	
//-------------------------------------------------------------------------
// TB_RDDATA02_RGT INFO:
//-------------------------------------------------------------------------
#define SE_TB_RDDATA02_RGT_REG_ADDR (SE_BASE_ADDR+0x180088)
#define TB_RDDATA02_RGT_TB_RDDATA02_FIELD_OFFSET (0)
#define TB_RDDATA02_RGT_TB_RDDATA02_FIELD_SIZE   (32)
	
//-------------------------------------------------------------------------
// TB_RDDATA03_RGT INFO:
//-------------------------------------------------------------------------
#define SE_TB_RDDATA03_RGT_REG_ADDR (SE_BASE_ADDR+0x18008c)
#define TB_RDDATA03_RGT_TB_RDDATA03_FIELD_OFFSET (0)
#define TB_RDDATA03_RGT_TB_RDDATA03_FIELD_SIZE   (32)
	
//-------------------------------------------------------------------------
// TB_RDDATA04_RGT INFO:
//-------------------------------------------------------------------------
#define SE_TB_RDDATA04_RGT_REG_ADDR (SE_BASE_ADDR+0x180090)
#define TB_RDDATA04_RGT_TB_RDDATA04_FIELD_OFFSET (0)
#define TB_RDDATA04_RGT_TB_RDDATA04_FIELD_SIZE   (32)
	
//-------------------------------------------------------------------------
// TB_RDDATA05_RGT INFO:
//-------------------------------------------------------------------------
#define SE_TB_RDDATA05_RGT_REG_ADDR (SE_BASE_ADDR+0x180094)
#define TB_RDDATA05_RGT_TB_RDDATA05_FIELD_OFFSET (0)
#define TB_RDDATA05_RGT_TB_RDDATA05_FIELD_SIZE   (32)
	
//-------------------------------------------------------------------------
// TB_RDDATA06_RGT INFO:
//-------------------------------------------------------------------------
#define SE_TB_RDDATA06_RGT_REG_ADDR (SE_BASE_ADDR+0x180098)
#define TB_RDDATA06_RGT_TB_RDDATA06_FIELD_OFFSET (0)
#define TB_RDDATA06_RGT_TB_RDDATA06_FIELD_SIZE   (32)
	
//-------------------------------------------------------------------------
// TB_RDDATA07_RGT INFO:
//-------------------------------------------------------------------------
#define SE_TB_RDDATA07_RGT_REG_ADDR (SE_BASE_ADDR+0x18009c)
#define TB_RDDATA07_RGT_TB_RDDATA07_FIELD_OFFSET (0)
#define TB_RDDATA07_RGT_TB_RDDATA07_FIELD_SIZE   (32)
	
//-------------------------------------------------------------------------
// TB_RDDATA08_RGT INFO:
//-------------------------------------------------------------------------
#define SE_TB_RDDATA08_RGT_REG_ADDR (SE_BASE_ADDR+0x1800a0)
#define TB_RDDATA08_RGT_TB_RDDATA08_FIELD_OFFSET (0)
#define TB_RDDATA08_RGT_TB_RDDATA08_FIELD_SIZE   (32)
	
//-------------------------------------------------------------------------
// TB_RDDATA09_RGT INFO:
//-------------------------------------------------------------------------
#define SE_TB_RDDATA09_RGT_REG_ADDR (SE_BASE_ADDR+0x18000a4)
#define TB_RDDATA09_RGT_TB_RDDATA09_FIELD_OFFSET (0)
#define TB_RDDATA09_RGT_TB_RDDATA09_FIELD_SIZE   (32)
	
//-------------------------------------------------------------------------
// TB_RDDATA10_RGT INFO:
//-------------------------------------------------------------------------
#define SE_TB_RDDATA10_RGT_REG_ADDR (SE_BASE_ADDR+0x1800a8)
#define TB_RDDATA10_RGT_TB_RDDATA10_FIELD_OFFSET (0)
#define TB_RDDATA10_RGT_TB_RDDATA10_FIELD_SIZE   (32)
	
//-------------------------------------------------------------------------
// TB_RDDATA11_RGT INFO:
//-------------------------------------------------------------------------
#define SE_TB_RDDATA11_RGT_REG_ADDR (SE_BASE_ADDR+0x1800ac)
#define TB_RDDATA11_RGT_TB_RDDATA11_FIELD_OFFSET (0)
#define TB_RDDATA11_RGT_TB_RDDATA11_FIELD_SIZE   (32)
	
//-------------------------------------------------------------------------
// TB_RDDATA12_RGT INFO:
//-------------------------------------------------------------------------
#define SE_TB_RDDATA12_RGT_REG_ADDR (SE_BASE_ADDR+0x1800b0)
#define TB_RDDATA12_RGT_TB_RDDATA12_FIELD_OFFSET (0)
#define TB_RDDATA12_RGT_TB_RDDATA12_FIELD_SIZE   (32)
	
//-------------------------------------------------------------------------
// TB_RDDATA13_RGT INFO:
//-------------------------------------------------------------------------
#define SE_TB_RDDATA13_RGT_REG_ADDR (SE_BASE_ADDR+0x1800b4)
#define TB_RDDATA13_RGT_TB_RDDATA13_FIELD_OFFSET (0)
#define TB_RDDATA13_RGT_TB_RDDATA13_FIELD_SIZE   (32)
	
//-------------------------------------------------------------------------
// TB_RDDATA14_RGT INFO:
//-------------------------------------------------------------------------
#define SE_TB_RDDATA14_RGT_REG_ADDR (SE_BASE_ADDR+0x1800b8)
#define TB_RDDATA14_RGT_TB_RDDATA14_FIELD_OFFSET (0)
#define TB_RDDATA14_RGT_TB_RDDATA14_FIELD_SIZE   (32)
	
//-------------------------------------------------------------------------
// TB_RDDATA15_RGT INFO:
//-------------------------------------------------------------------------
#define SE_TB_RDDATA15_RGT_REG_ADDR (SE_BASE_ADDR+0x1800bc)
#define TB_RDDATA15_RGT_TB_RDDATA15_FIELD_OFFSET (0)
#define TB_RDDATA15_RGT_TB_RDDATA15_FIELD_SIZE   (32)
	
//-------------------------------------------------------------------------
// NAT_STATUS_RGT INFO:
//-------------------------------------------------------------------------
#define SE_NAT_STATUS_RGT_REG_ADDR (SE_BASE_ADDR+0x188000)
#define NAT_STATUS_RGT_NAT_SPEED_LIMIT_BP_OVF_FIELD_OFFSET (30)
#define NAT_STATUS_RGT_NAT_SPEED_LIMIT_BP_OVF_FIELD_SIZE   (1)
#define NAT_STATUS_RGT_DDR_ADDR_REQ_FIFO_OVF_FIELD_OFFSET (29)
#define NAT_STATUS_RGT_DDR_ADDR_REQ_FIFO_OVF_FIELD_SIZE   (1)
#define NAT_STATUS_RGT_DDR_DATA_RESP_FIFO_OVF_FIELD_OFFSET (28)
#define NAT_STATUS_RGT_DDR_DATA_RESP_FIFO_OVF_FIELD_SIZE   (1)
#define NAT_STATUS_RGT_ILKP_RESULT_FIFO_OVF_FIELD_OFFSET (27)
#define NAT_STATUS_RGT_ILKP_RESULT_FIFO_OVF_FIELD_SIZE   (1)
#define NAT_STATUS_RGT_KEY_FIFO_OVF_FIELD_OFFSET (26)
#define NAT_STATUS_RGT_KEY_FIFO_OVF_FIELD_SIZE   (1)
#define NAT_STATUS_RGT_ILKP_BUSY_BP_OVF_FIELD_OFFSET (25)
#define NAT_STATUS_RGT_ILKP_BUSY_BP_OVF_FIELD_SIZE   (1)
#define NAT_STATUS_RGT_FRAG_FIFO_OVF_FIELD_OFFSET (24)
#define NAT_STATUS_RGT_FRAG_FIFO_OVF_FIELD_SIZE   (1)
#define NAT_STATUS_RGT_ELKP_FIFO_STATUS_FIELD_OFFSET (10)
#define NAT_STATUS_RGT_ELKP_FIFO_STATUS_FIELD_SIZE   (8)
#define NAT_STATUS_RGT_FRG_FIFO_STATUS_FIELD_OFFSET (8)
#define NAT_STATUS_RGT_FRG_FIFO_STATUS_FIELD_SIZE   (2)
#define NAT_STATUS_RGT_HOST_MGT_REQ_BUSY_FIELD_OFFSET (0)
#define NAT_STATUS_RGT_HOST_MGT_REQ_BUSY_FIELD_SIZE   (1)
	
//-------------------------------------------------------------------------
// NAT_CONFIG0_RGT INFO:
//-------------------------------------------------------------------------
#define SE_NAT_CONFIG0_RGT_REG_ADDR (SE_BASE_ADDR+0x188004)
#define NAT_CONFIG0_RGT_DNAT_SUB_TB7_VLD_FIELD_OFFSET (31)
#define NAT_CONFIG0_RGT_DNAT_SUB_TB7_VLD_FIELD_SIZE   (1)
#define NAT_CONFIG0_RGT_DNAT_SUB_TB6_VLD_FIELD_OFFSET (30)
#define NAT_CONFIG0_RGT_DNAT_SUB_TB6_VLD_FIELD_SIZE   (1)
#define NAT_CONFIG0_RGT_DNAT_SUB_TB5_VLD_FIELD_OFFSET (29)
#define NAT_CONFIG0_RGT_DNAT_SUB_TB5_VLD_FIELD_SIZE   (1)
#define NAT_CONFIG0_RGT_DNAT_SUB_TB4_VLD_FIELD_OFFSET (28)
#define NAT_CONFIG0_RGT_DNAT_SUB_TB4_VLD_FIELD_SIZE   (1)
#define NAT_CONFIG0_RGT_DNAT_SUB_TB3_VLD_FIELD_OFFSET (27)
#define NAT_CONFIG0_RGT_DNAT_SUB_TB3_VLD_FIELD_SIZE   (1)
#define NAT_CONFIG0_RGT_DNAT_SUB_TB2_VLD_FIELD_OFFSET (26)
#define NAT_CONFIG0_RGT_DNAT_SUB_TB2_VLD_FIELD_SIZE   (1)
#define NAT_CONFIG0_RGT_DNAT_SUB_TB1_VLD_FIELD_OFFSET (25)
#define NAT_CONFIG0_RGT_DNAT_SUB_TB1_VLD_FIELD_SIZE   (1)
#define NAT_CONFIG0_RGT_DNAT_SUB_TB0_VLD_FIELD_OFFSET (24)
#define NAT_CONFIG0_RGT_DNAT_SUB_TB0_VLD_FIELD_SIZE   (1)
#define NAT_CONFIG0_RGT_SNAT_SUB_TB7_VLD_FIELD_OFFSET (23)
#define NAT_CONFIG0_RGT_SNAT_SUB_TB7_VLD_FIELD_SIZE   (1)
#define NAT_CONFIG0_RGT_SNAT_SUB_TB6_VLD_FIELD_OFFSET (22)
#define NAT_CONFIG0_RGT_SNAT_SUB_TB6_VLD_FIELD_SIZE   (1)
#define NAT_CONFIG0_RGT_SNAT_SUB_TB5_VLD_FIELD_OFFSET (21)
#define NAT_CONFIG0_RGT_SNAT_SUB_TB5_VLD_FIELD_SIZE   (1)
#define NAT_CONFIG0_RGT_SNAT_SUB_TB4_VLD_FIELD_OFFSET (20)
#define NAT_CONFIG0_RGT_SNAT_SUB_TB4_VLD_FIELD_SIZE   (1)
#define NAT_CONFIG0_RGT_SNAT_SUB_TB3_VLD_FIELD_OFFSET (19)
#define NAT_CONFIG0_RGT_SNAT_SUB_TB3_VLD_FIELD_SIZE   (1)
#define NAT_CONFIG0_RGT_SNAT_SUB_TB2_VLD_FIELD_OFFSET (18)
#define NAT_CONFIG0_RGT_SNAT_SUB_TB2_VLD_FIELD_SIZE   (1)
#define NAT_CONFIG0_RGT_SNAT_SUB_TB1_VLD_FIELD_OFFSET (17)
#define NAT_CONFIG0_RGT_SNAT_SUB_TB1_VLD_FIELD_SIZE   (1)
#define NAT_CONFIG0_RGT_SNAT_SUB_TB0_VLD_FIELD_OFFSET (16)
#define NAT_CONFIG0_RGT_SNAT_SUB_TB0_VLD_FIELD_SIZE   (1)
#define NAT_CONFIG0_RGT_ELKP_V6_ACS_TIMES_FIELD_OFFSET (13)
#define NAT_CONFIG0_RGT_ELKP_V6_ACS_TIMES_FIELD_SIZE   (2)
#define NAT_CONFIG0_RGT_ELKP_V4_ACS_TIMES_FIELD_OFFSET (11)
#define NAT_CONFIG0_RGT_ELKP_V4_ACS_TIMES_FIELD_SIZE   (2)
#define NAT_CONFIG0_RGT_ELKP_TABLE_SIZE_FIELD_OFFSET (9)
#define NAT_CONFIG0_RGT_ELKP_TABLE_SIZE_FIELD_SIZE   (2)
#define NAT_CONFIG0_RGT_ELKP_VST_CLR_AFTER_RD_FIELD_OFFSET (8)
#define NAT_CONFIG0_RGT_ELKP_VST_CLR_AFTER_RD_FIELD_SIZE   (1)
#define NAT_CONFIG0_RGT_ELKP_HOST_UPDATE_VST_FIELD_OFFSET (7)
#define NAT_CONFIG0_RGT_ELKP_HOST_UPDATE_VST_FIELD_SIZE   (1)
#define NAT_CONFIG0_RGT_DIS_DDR_LKP_FIELD_OFFSET (6)
#define NAT_CONFIG0_RGT_DIS_DDR_LKP_FIELD_SIZE   (1)
#define NAT_CONFIG0_RGT_FRG_HLKP_TRANSPARENT_FIELD_OFFSET (5)
#define NAT_CONFIG0_RGT_FRG_HLKP_TRANSPARENT_FIELD_SIZE   (1)
#define NAT_CONFIG0_RGT_FRG_V4_BYPASS_FIELD_OFFSET (4)
#define NAT_CONFIG0_RGT_FRG_V4_BYPASS_FIELD_SIZE   (1)
#define NAT_CONFIG0_RGT_FRG_V6_BYPASS_FIELD_OFFSET (3)
#define NAT_CONFIG0_RGT_FRG_V6_BYPASS_FIELD_SIZE   (1)
#define NAT_CONFIG0_RGT_CFG_HNAT_MODE_FIELD_OFFSET (0)
#define NAT_CONFIG0_RGT_CFG_HNAT_MODE_FIELD_SIZE   (3)
	
//-------------------------------------------------------------------------
// NAT_CONFIG1_RGT INFO:
//-------------------------------------------------------------------------
#define SE_NAT_CONFIG1_RGT_REG_ADDR (SE_BASE_ADDR+0x188008)
#define NAT_CONFIG1_RGT_ILKP_HASH_POLY_SEL7_FIELD_OFFSET (21)
#define NAT_CONFIG1_RGT_ILKP_HASH_POLY_SEL7_FIELD_SIZE   (3)
#define NAT_CONFIG1_RGT_ILKP_HASH_POLY_SEL6_FIELD_OFFSET (18)
#define NAT_CONFIG1_RGT_ILKP_HASH_POLY_SEL6_FIELD_SIZE   (3)
#define NAT_CONFIG1_RGT_ILKP_HASH_POLY_SEL5_FIELD_OFFSET (15)
#define NAT_CONFIG1_RGT_ILKP_HASH_POLY_SEL5_FIELD_SIZE   (3)
#define NAT_CONFIG1_RGT_ILKP_HASH_POLY_SEL4_FIELD_OFFSET (12)
#define NAT_CONFIG1_RGT_ILKP_HASH_POLY_SEL4_FIELD_SIZE   (3)
#define NAT_CONFIG1_RGT_ILKP_HASH_POLY_SEL3_FIELD_OFFSET (9)
#define NAT_CONFIG1_RGT_ILKP_HASH_POLY_SEL3_FIELD_SIZE   (3)
#define NAT_CONFIG1_RGT_ILKP_HASH_POLY_SEL2_FIELD_OFFSET (6)
#define NAT_CONFIG1_RGT_ILKP_HASH_POLY_SEL2_FIELD_SIZE   (3)
#define NAT_CONFIG1_RGT_ILKP_HASH_POLY_SEL1_FIELD_OFFSET (3)
#define NAT_CONFIG1_RGT_ILKP_HASH_POLY_SEL1_FIELD_SIZE   (3)
#define NAT_CONFIG1_RGT_ILKP_HASH_POLY_SEL0_FIELD_OFFSET (0)
#define NAT_CONFIG1_RGT_ILKP_HASH_POLY_SEL0_FIELD_SIZE   (3)
	
//-------------------------------------------------------------------------
// NAT_CONFIG2_RGT INFO:
//-------------------------------------------------------------------------
#define SE_NAT_CONFIG2_RGT_REG_ADDR (SE_BASE_ADDR+0x18800C)
#define NAT_CONFIG2_RGT_ELKP_HASH_POLY_SEL7_FIELD_OFFSET (21)
#define NAT_CONFIG2_RGT_ELKP_HASH_POLY_SEL7_FIELD_SIZE   (3)
#define NAT_CONFIG2_RGT_ELKP_HASH_POLY_SEL6_FIELD_OFFSET (18)
#define NAT_CONFIG2_RGT_ELKP_HASH_POLY_SEL6_FIELD_SIZE   (3)
#define NAT_CONFIG2_RGT_ELKP_HASH_POLY_SEL5_FIELD_OFFSET (15)
#define NAT_CONFIG2_RGT_ELKP_HASH_POLY_SEL5_FIELD_SIZE   (3)
#define NAT_CONFIG2_RGT_ELKP_HASH_POLY_SEL4_FIELD_OFFSET (12)
#define NAT_CONFIG2_RGT_ELKP_HASH_POLY_SEL4_FIELD_SIZE   (3)
#define NAT_CONFIG2_RGT_ELKP_HASH_POLY_SEL3_FIELD_OFFSET (9)
#define NAT_CONFIG2_RGT_ELKP_HASH_POLY_SEL3_FIELD_SIZE   (3)
#define NAT_CONFIG2_RGT_ELKP_HASH_POLY_SEL2_FIELD_OFFSET (6)
#define NAT_CONFIG2_RGT_ELKP_HASH_POLY_SEL2_FIELD_SIZE   (3)
#define NAT_CONFIG2_RGT_ELKP_HASH_POLY_SEL1_FIELD_OFFSET (3)
#define NAT_CONFIG2_RGT_ELKP_HASH_POLY_SEL1_FIELD_SIZE   (3)
#define NAT_CONFIG2_RGT_ELKP_HASH_POLY_SEL0_FIELD_OFFSET (0)
#define NAT_CONFIG2_RGT_ELKP_HASH_POLY_SEL0_FIELD_SIZE   (3)
	
//-------------------------------------------------------------------------
// NAT_CONFIG3_RGT INFO:
//-------------------------------------------------------------------------
#define SE_NAT_CONFIG3_RGT_REG_ADDR (SE_BASE_ADDR+0x188010)
#define NAT_CONFIG3_RGT_DDR_DNAT_BASE_ADDR_FIELD_OFFSET (0)
#define NAT_CONFIG3_RGT_DDR_DNAT_BASE_ADDR_FIELD_SIZE   (32)
	
//-------------------------------------------------------------------------
// NAT_CONFIG4_RGT INFO:
//-------------------------------------------------------------------------
#define SE_NAT_CONFIG4_RGT_REG_ADDR (SE_BASE_ADDR+0x188014)
#define NAT_CONFIG4_RGT_DDR_SNAT_BASE_ADDR_FIELD_OFFSET (0)
#define NAT_CONFIG4_RGT_DDR_SNAT_BASE_ADDR_FIELD_SIZE   (32)
	
//-------------------------------------------------------------------------
// NAT_CONFIG5_RGT INFO:
//-------------------------------------------------------------------------
#define SE_NAT_CONFIG5_RGT_REG_ADDR (SE_BASE_ADDR+0x188018)
#define NAT_CONFIG5_RGT_NAT_MIB_MODE_FIELD_OFFSET (4)
#define NAT_CONFIG5_RGT_NAT_MIB_MODE_FIELD_SIZE   (4)
#define NAT_CONFIG5_RGT_NAT_SPL_MODE_FIELD_OFFSET (0)
#define NAT_CONFIG5_RGT_NAT_SPL_MODE_FIELD_SIZE   (3)
	
//-------------------------------------------------------------------------
// NAT_CONFIG6_RGT INFO:
//-------------------------------------------------------------------------
#define SE_NAT_CONFIG6_RGT_REG_ADDR (SE_BASE_ADDR+0x18801C)
#define NAT_CONFIG6_RGT_NAT_SPL_TIMER_MINUS1_FIELD_OFFSET (0)
#define NAT_CONFIG6_RGT_NAT_SPL_TIMER_MINUS1_FIELD_SIZE   (32)
	
//-------------------------------------------------------------------------
// NAT_BUF_THRESH_RGT INFO:
//-------------------------------------------------------------------------
#define SE_NAT_BUF_THRESH_RGT_REG_ADDR (SE_BASE_ADDR+0x188020)
#define NAT_BUF_THRESH_RGT_ADDR_FIFO_BP_THRESH_FIELD_OFFSET (20)
#define NAT_BUF_THRESH_RGT_ADDR_FIFO_BP_THRESH_FIELD_SIZE   (6)
#define NAT_BUF_THRESH_RGT_DDR_FIFO_BP_THRESH_FIELD_OFFSET (16)
#define NAT_BUF_THRESH_RGT_DDR_FIFO_BP_THRESH_FIELD_SIZE   (4)
#define NAT_BUF_THRESH_RGT_ILKP_FIFO_BP_THRESH_FIELD_OFFSET (12)
#define NAT_BUF_THRESH_RGT_ILKP_FIFO_BP_THRESH_FIELD_SIZE   (4)
#define NAT_BUF_THRESH_RGT_KEY_FIFO_BP_THRESH_FIELD_OFFSET (8)
#define NAT_BUF_THRESH_RGT_KEY_FIFO_BP_THRESH_FIELD_SIZE   (4)
#define NAT_BUF_THRESH_RGT_FRG_THRESH_RGT_FIELD_OFFSET (0)
#define NAT_BUF_THRESH_RGT_FRG_THRESH_RGT_FIELD_SIZE   (5)
	
//-------------------------------------------------------------------------
// NAT_COMMAND_RGT INFO:
//-------------------------------------------------------------------------
#define SE_NAT_COMMAND_RGT_REG_ADDR (SE_BASE_ADDR+0x188024)
#define NAT_COMMAND_RGT_NAT_SPEED_LIMIT_TB_CLR_FIELD_OFFSET (8)
#define NAT_COMMAND_RGT_NAT_SPEED_LIMIT_TB_CLR_FIELD_SIZE   (1)
#define NAT_COMMAND_RGT_NAPT_ALL_TB_CLR_FIELD_OFFSET (7)
#define NAT_COMMAND_RGT_NAPT_ALL_TB_CLR_FIELD_SIZE   (1)
#define NAT_COMMAND_RGT_NAPT_TB1_CLR_FIELD_OFFSET (6)
#define NAT_COMMAND_RGT_NAPT_TB1_CLR_FIELD_SIZE   (1)
#define NAT_COMMAND_RGT_NAPT_TB0_CLR_FIELD_OFFSET (5)
#define NAT_COMMAND_RGT_NAPT_TB0_CLR_FIELD_SIZE   (1)
#define NAT_COMMAND_RGT_SNAT_HASH_TB1_CLR_FIELD_OFFSET (4)
#define NAT_COMMAND_RGT_SNAT_HASH_TB1_CLR_FIELD_SIZE   (1)
#define NAT_COMMAND_RGT_SNAT_HASH_TB0_CLR_FIELD_OFFSET (3)
#define NAT_COMMAND_RGT_SNAT_HASH_TB0_CLR_FIELD_SIZE   (1)
#define NAT_COMMAND_RGT_DNAT_HASH_TB1_CLR_FIELD_OFFSET (2)
#define NAT_COMMAND_RGT_DNAT_HASH_TB1_CLR_FIELD_SIZE   (1)
#define NAT_COMMAND_RGT_DNAT_HASH_TB0_CLR_FIELD_OFFSET (1)
#define NAT_COMMAND_RGT_DNAT_HASH_TB0_CLR_FIELD_SIZE   (1)
#define NAT_COMMAND_RGT_FRAG_INIT_FIELD_OFFSET (0)
#define NAT_COMMAND_RGT_FRAG_INIT_FIELD_SIZE   (1)
	
//-------------------------------------------------------------------------
// NAT_FRG_TIMER_RGT INFO:
//-------------------------------------------------------------------------
#define SE_NAT_FRG_TIMER_RGT_REG_ADDR (SE_BASE_ADDR+0x188028)
#define NAT_FRG_TIMER_RGT_FRG_AGE_TIMER_FIELD_OFFSET (0)
#define NAT_FRG_TIMER_RGT_FRG_AGE_TIMER_FIELD_SIZE   (32)
	
//-------------------------------------------------------------------------
// NAT_FRG_AGE_CNT_RGT INFO:
//-------------------------------------------------------------------------
#define SE_NAT_FRG_AGE_CNT_RGT_REG_ADDR (SE_BASE_ADDR+0x18802C)
#define NAT_FRG_AGE_CNT_RGT_FRG_MIN_AGE_FIELD_OFFSET (16)
#define NAT_FRG_AGE_CNT_RGT_FRG_MIN_AGE_FIELD_SIZE   (8)
#define NAT_FRG_AGE_CNT_RGT_FRG_FAST_AGE_FIELD_OFFSET (8)
#define NAT_FRG_AGE_CNT_RGT_FRG_FAST_AGE_FIELD_SIZE   (8)
#define NAT_FRG_AGE_CNT_RGT_FRG_AGE_TIMEOUT_FIELD_OFFSET (0)
#define NAT_FRG_AGE_CNT_RGT_FRG_AGE_TIMEOUT_FIELD_SIZE   (8)
	
//-------------------------------------------------------------------------
// NAT_LKP_REQ_RGT INFO:
//-------------------------------------------------------------------------
#define SE_NAT_LKP_REQ_RGT_REG_ADDR (SE_BASE_ADDR+0x188038)
#define NAT_LKP_REQ_RGT_HLKP_SCH_REQ_FIELD_OFFSET (16)
#define NAT_LKP_REQ_RGT_HLKP_SCH_REQ_FIELD_SIZE   (16)
#define NAT_LKP_REQ_RGT_HLKP_REQ_FIELD_OFFSET (0)
#define NAT_LKP_REQ_RGT_HLKP_REQ_FIELD_SIZE   (16)
	
//-------------------------------------------------------------------------
// NAT_OP_ADDR_RGT INFO:
//-------------------------------------------------------------------------
#define SE_NAT_OP_ADDR_RGT_REG_ADDR (SE_BASE_ADDR+0x18803C)
#define NAT_OP_ADDR_RGT_HOST_MGT_REQ_BUSY_FIELD_OFFSET (31)
#define NAT_OP_ADDR_RGT_HOST_MGT_REQ_BUSY_FIELD_SIZE   (1)
#define NAT_OP_ADDR_RGT_HOST_MGT_REQ_OPCODE_FIELD_OFFSET (24)
#define NAT_OP_ADDR_RGT_HOST_MGT_REQ_OPCODE_FIELD_SIZE   (1)
#define NAT_OP_ADDR_RGT_HOST_MGT_REQ_ID_FIELD_OFFSET (16)
#define NAT_OP_ADDR_RGT_HOST_MGT_REQ_ID_FIELD_SIZE   (3)
#define NAT_OP_ADDR_RGT_HOST_MGT_REQ_ADDR_FIELD_OFFSET (0)
#define NAT_OP_ADDR_RGT_HOST_MGT_REQ_ADDR_FIELD_SIZE   (13)
	
//-------------------------------------------------------------------------
// NAT_TB_WRDATA00_RGT INFO:
//-------------------------------------------------------------------------
#define SE_NAT_TB_WRDATA00_RGT_REG_ADDR (SE_BASE_ADDR+0x188040)
#define NAT_TB_WRDATA00_RGT_NAT_TB_WRDATA00_FIELD_OFFSET (0)
#define NAT_TB_WRDATA00_RGT_NAT_TB_WRDATA00_FIELD_SIZE   (32)
	
//-------------------------------------------------------------------------
// NAT_TB_WRDATA01_RGT INFO:
//-------------------------------------------------------------------------
#define SE_NAT_TB_WRDATA01_RGT_REG_ADDR (SE_BASE_ADDR+0x188044)
#define NAT_TB_WRDATA01_RGT_NAT_TB_WRDATA01_FIELD_OFFSET (0)
#define NAT_TB_WRDATA01_RGT_NAT_TB_WRDATA01_FIELD_SIZE   (32)
	
//-------------------------------------------------------------------------
// NAT_TB_WRDATA02_RGT INFO:
//-------------------------------------------------------------------------
#define SE_NAT_TB_WRDATA02_RGT_REG_ADDR (SE_BASE_ADDR+0x188048)
#define NAT_TB_WRDATA02_RGT_NAT_TB_WRDATA02_FIELD_OFFSET (0)
#define NAT_TB_WRDATA02_RGT_NAT_TB_WRDATA02_FIELD_SIZE   (32)
	
//-------------------------------------------------------------------------
// NAT_TB_WRDATA03_RGT INFO:
//-------------------------------------------------------------------------
#define SE_NAT_TB_WRDATA03_RGT_REG_ADDR (SE_BASE_ADDR+0x18804c)
#define NAT_TB_WRDATA03_RGT_NAT_TB_WRDATA03_FIELD_OFFSET (0)
#define NAT_TB_WRDATA03_RGT_NAT_TB_WRDATA03_FIELD_SIZE   (32)
	
//-------------------------------------------------------------------------
// NAT_TB_WRDATA04_RGT INFO:
//-------------------------------------------------------------------------
#define SE_NAT_TB_WRDATA04_RGT_REG_ADDR (SE_BASE_ADDR+0x188050)
#define NAT_TB_WRDATA04_RGT_NAT_TB_WRDATA04_FIELD_OFFSET (0)
#define NAT_TB_WRDATA04_RGT_NAT_TB_WRDATA04_FIELD_SIZE   (32)
	
//-------------------------------------------------------------------------
// NAT_TB_WRDATA05_RGT INFO:
//-------------------------------------------------------------------------
#define SE_NAT_TB_WRDATA05_RGT_REG_ADDR (SE_BASE_ADDR+0x188054)
#define NAT_TB_WRDATA05_RGT_NAT_TB_WRDATA05_FIELD_OFFSET (0)
#define NAT_TB_WRDATA05_RGT_NAT_TB_WRDATA05_FIELD_SIZE   (32)
	
//-------------------------------------------------------------------------
// NAT_TB_WRDATA06_RGT INFO:
//-------------------------------------------------------------------------
#define SE_NAT_TB_WRDATA06_RGT_REG_ADDR (SE_BASE_ADDR+0x188058)
#define NAT_TB_WRDATA06_RGT_NAT_TB_WRDATA06_FIELD_OFFSET (0)
#define NAT_TB_WRDATA06_RGT_NAT_TB_WRDATA06_FIELD_SIZE   (32)
	
//-------------------------------------------------------------------------
// NAT_TB_WRDATA07_RGT INFO:
//-------------------------------------------------------------------------
#define SE_NAT_TB_WRDATA07_RGT_REG_ADDR (SE_BASE_ADDR+0x18805c)
#define NAT_TB_WRDATA07_RGT_NAT_TB_WRDATA07_FIELD_OFFSET (0)
#define NAT_TB_WRDATA07_RGT_NAT_TB_WRDATA07_FIELD_SIZE   (32)
	
//-------------------------------------------------------------------------
// NAT_TB_WRDATA08_RGT INFO:
//-------------------------------------------------------------------------
#define SE_NAT_TB_WRDATA08_RGT_REG_ADDR (SE_BASE_ADDR+0x188060)
#define NAT_TB_WRDATA08_RGT_NAT_TB_WRDATA08_FIELD_OFFSET (0)
#define NAT_TB_WRDATA08_RGT_NAT_TB_WRDATA08_FIELD_SIZE   (32)
	
//-------------------------------------------------------------------------
// NAT_TB_WRDATA09_RGT INFO:
//-------------------------------------------------------------------------
#define SE_NAT_TB_WRDATA09_RGT_REG_ADDR (SE_BASE_ADDR+0x188064)
#define NAT_TB_WRDATA09_RGT_NAT_TB_WRDATA09_FIELD_OFFSET (0)
#define NAT_TB_WRDATA09_RGT_NAT_TB_WRDATA09_FIELD_SIZE   (32)
	
//-------------------------------------------------------------------------
// NAT_TB_WRDATA10_RGT INFO:
//-------------------------------------------------------------------------
#define SE_NAT_TB_WRDATA10_RGT_REG_ADDR (SE_BASE_ADDR+0x188068)
#define NAT_TB_WRDATA10_RGT_NAT_TB_WRDATA10_FIELD_OFFSET (0)
#define NAT_TB_WRDATA10_RGT_NAT_TB_WRDATA10_FIELD_SIZE   (32)
	
//-------------------------------------------------------------------------
// NAT_TB_WRDATA11_RGT INFO:
//-------------------------------------------------------------------------
#define SE_NAT_TB_WRDATA11_RGT_REG_ADDR (SE_BASE_ADDR+0x18806c)
#define NAT_TB_WRDATA11_RGT_NAT_TB_WRDATA11_FIELD_OFFSET (0)
#define NAT_TB_WRDATA11_RGT_NAT_TB_WRDATA11_FIELD_SIZE   (32)
	
//-------------------------------------------------------------------------
// NAT_TB_WRDATA12_RGT INFO:
//-------------------------------------------------------------------------
#define SE_NAT_TB_WRDATA12_RGT_REG_ADDR (SE_BASE_ADDR+0x188070)
#define NAT_TB_WRDATA12_RGT_NAT_TB_WRDATA12_FIELD_OFFSET (0)
#define NAT_TB_WRDATA12_RGT_NAT_TB_WRDATA12_FIELD_SIZE   (32)
	
//-------------------------------------------------------------------------
// NAT_TB_WRDATA13_RGT INFO:
//-------------------------------------------------------------------------
#define SE_NAT_TB_WRDATA13_RGT_REG_ADDR (SE_BASE_ADDR+0x188074)
#define NAT_TB_WRDATA13_RGT_NAT_TB_WRDATA13_FIELD_OFFSET (0)
#define NAT_TB_WRDATA13_RGT_NAT_TB_WRDATA13_FIELD_SIZE   (32)
	
//-------------------------------------------------------------------------
// NAT_TB_WRDATA14_RGT INFO:
//-------------------------------------------------------------------------
#define SE_NAT_TB_WRDATA14_RGT_REG_ADDR (SE_BASE_ADDR+0x188078)
#define NAT_TB_WRDATA14_RGT_NAT_TB_WRDATA14_FIELD_OFFSET (0)
#define NAT_TB_WRDATA14_RGT_NAT_TB_WRDATA14_FIELD_SIZE   (32)
	
//-------------------------------------------------------------------------
// NAT_TB_WRDATA15_RGT INFO:
//-------------------------------------------------------------------------
#define SE_NAT_TB_WRDATA15_RGT_REG_ADDR (SE_BASE_ADDR+0x18807c)
#define NAT_TB_WRDATA15_RGT_NAT_TB_WRDATA15_FIELD_OFFSET (0)
#define NAT_TB_WRDATA15_RGT_NAT_TB_WRDATA15_FIELD_SIZE   (32)
	
//-------------------------------------------------------------------------
// NAT_TB_RDDATA00_RGT INFO:
//-------------------------------------------------------------------------
#define SE_NAT_TB_RDDATA00_RGT_REG_ADDR (SE_BASE_ADDR+0x188080)
#define NAT_TB_RDDATA00_RGT_NAT_TB_RDDATA00_FIELD_OFFSET (0)
#define NAT_TB_RDDATA00_RGT_NAT_TB_RDDATA00_FIELD_SIZE   (32)
	
//-------------------------------------------------------------------------
// NAT_TB_RDDATA01_RGT INFO:
//-------------------------------------------------------------------------
#define SE_NAT_TB_RDDATA01_RGT_REG_ADDR (SE_BASE_ADDR+0x188084)
#define NAT_TB_RDDATA01_RGT_NAT_TB_RDDATA01_FIELD_OFFSET (0)
#define NAT_TB_RDDATA01_RGT_NAT_TB_RDDATA01_FIELD_SIZE   (32)
	
//-------------------------------------------------------------------------
// NAT_TB_RDDATA02_RGT INFO:
//-------------------------------------------------------------------------
#define SE_NAT_TB_RDDATA02_RGT_REG_ADDR (SE_BASE_ADDR+0x188088)
#define NAT_TB_RDDATA02_RGT_NAT_TB_RDDATA02_FIELD_OFFSET (0)
#define NAT_TB_RDDATA02_RGT_NAT_TB_RDDATA02_FIELD_SIZE   (32)
	
//-------------------------------------------------------------------------
// NAT_TB_RDDATA03_RGT INFO:
//-------------------------------------------------------------------------
#define SE_NAT_TB_RDDATA03_RGT_REG_ADDR (SE_BASE_ADDR+0x18808c)
#define NAT_TB_RDDATA03_RGT_NAT_TB_RDDATA03_FIELD_OFFSET (0)
#define NAT_TB_RDDATA03_RGT_NAT_TB_RDDATA03_FIELD_SIZE   (32)
	
//-------------------------------------------------------------------------
// NAT_TB_RDDATA04_RGT INFO:
//-------------------------------------------------------------------------
#define SE_NAT_TB_RDDATA04_RGT_REG_ADDR (SE_BASE_ADDR+0x188090)
#define NAT_TB_RDDATA04_RGT_NAT_TB_RDDATA04_FIELD_OFFSET (0)
#define NAT_TB_RDDATA04_RGT_NAT_TB_RDDATA04_FIELD_SIZE   (32)
	
//-------------------------------------------------------------------------
// NAT_TB_RDDATA05_RGT INFO:
//-------------------------------------------------------------------------
#define SE_NAT_TB_RDDATA05_RGT_REG_ADDR (SE_BASE_ADDR+0x188094)
#define NAT_TB_RDDATA05_RGT_NAT_TB_RDDATA05_FIELD_OFFSET (0)
#define NAT_TB_RDDATA05_RGT_NAT_TB_RDDATA05_FIELD_SIZE   (32)
	
//-------------------------------------------------------------------------
// NAT_TB_RDDATA06_RGT INFO:
//-------------------------------------------------------------------------
#define SE_NAT_TB_RDDATA06_RGT_REG_ADDR (SE_BASE_ADDR+0x188098)
#define NAT_TB_RDDATA06_RGT_NAT_TB_RDDATA06_FIELD_OFFSET (0)
#define NAT_TB_RDDATA06_RGT_NAT_TB_RDDATA06_FIELD_SIZE   (32)
	
//-------------------------------------------------------------------------
// NAT_TB_RDDATA07_RGT INFO:
//-------------------------------------------------------------------------
#define SE_NAT_TB_RDDATA07_RGT_REG_ADDR (SE_BASE_ADDR+0x18809c)
#define NAT_TB_RDDATA07_RGT_NAT_TB_RDDATA07_FIELD_OFFSET (0)
#define NAT_TB_RDDATA07_RGT_NAT_TB_RDDATA07_FIELD_SIZE   (32)
	
//-------------------------------------------------------------------------
// NAT_TB_RDDATA08_RGT INFO:
//-------------------------------------------------------------------------
#define SE_NAT_TB_RDDATA08_RGT_REG_ADDR (SE_BASE_ADDR+0x1880a0)
#define NAT_TB_RDDATA08_RGT_NAT_TB_RDDATA08_FIELD_OFFSET (0)
#define NAT_TB_RDDATA08_RGT_NAT_TB_RDDATA08_FIELD_SIZE   (32)
	
//-------------------------------------------------------------------------
// NAT_TB_RDDATA09_RGT INFO:
//-------------------------------------------------------------------------
#define SE_NAT_TB_RDDATA09_RGT_REG_ADDR (SE_BASE_ADDR+0x1880a4)
#define NAT_TB_RDDATA09_RGT_NAT_TB_RDDATA09_FIELD_OFFSET (0)
#define NAT_TB_RDDATA09_RGT_NAT_TB_RDDATA09_FIELD_SIZE   (32)
	
//-------------------------------------------------------------------------
// NAT_TB_RDDATA10_RGT INFO:
//-------------------------------------------------------------------------
#define SE_NAT_TB_RDDATA10_RGT_REG_ADDR (SE_BASE_ADDR+0x1880a8)
#define NAT_TB_RDDATA10_RGT_NAT_TB_RDDATA10_FIELD_OFFSET (0)
#define NAT_TB_RDDATA10_RGT_NAT_TB_RDDATA10_FIELD_SIZE   (32)
	
//-------------------------------------------------------------------------
// NAT_TB_RDDATA11_RGT INFO:
//-------------------------------------------------------------------------
#define SE_NAT_TB_RDDATA11_RGT_REG_ADDR (SE_BASE_ADDR+0x1880ac)
#define NAT_TB_RDDATA11_RGT_NAT_TB_RDDATA11_FIELD_OFFSET (0)
#define NAT_TB_RDDATA11_RGT_NAT_TB_RDDATA11_FIELD_SIZE   (32)
	
//-------------------------------------------------------------------------
// NAT_TB_RDDATA12_RGT INFO:
//-------------------------------------------------------------------------
#define SE_NAT_TB_RDDATA12_RGT_REG_ADDR (SE_BASE_ADDR+0x1880b0)
#define NAT_TB_RDDATA12_RGT_NAT_TB_RDDATA12_FIELD_OFFSET (0)
#define NAT_TB_RDDATA12_RGT_NAT_TB_RDDATA12_FIELD_SIZE   (32)
	
//-------------------------------------------------------------------------
// NAT_TB_RDDATA13_RGT INFO:
//-------------------------------------------------------------------------
#define SE_NAT_TB_RDDATA13_RGT_REG_ADDR (SE_BASE_ADDR+0x1880b4)
#define NAT_TB_RDDATA13_RGT_NAT_TB_RDDATA13_FIELD_OFFSET (0)
#define NAT_TB_RDDATA13_RGT_NAT_TB_RDDATA13_FIELD_SIZE   (32)
	
//-------------------------------------------------------------------------
// NAT_TB_RDDATA14_RGT INFO:
//-------------------------------------------------------------------------
#define SE_NAT_TB_RDDATA14_RGT_REG_ADDR (SE_BASE_ADDR+0x1880b8)
#define NAT_TB_RDDATA14_RGT_NAT_TB_RDDATA14_FIELD_OFFSET (0)
#define NAT_TB_RDDATA14_RGT_NAT_TB_RDDATA14_FIELD_SIZE   (32)
	
//-------------------------------------------------------------------------
// NAT_TB_RDDATA15_RGT INFO:
//-------------------------------------------------------------------------
#define SE_NAT_TB_RDDATA15_RGT_REG_ADDR (SE_BASE_ADDR+0x1880bc)
#define NAT_TB_RDDATA15_RGT_NAT_TB_RDDATA15_FIELD_OFFSET (0)
#define NAT_TB_RDDATA15_RGT_NAT_TB_RDDATA15_FIELD_SIZE   (32)
	
//-------------------------------------------------------------------------
// SE_NAT_KEY_RAM_KEY0_DATA0 INFO:
//-------------------------------------------------------------------------
#define SE_SE_NAT_KEY_RAM_KEY0_DATA0_REG_ADDR (SE_BASE_ADDR+0x188400)
#define SE_NAT_KEY_RAM_KEY0_DATA0_KEY0_DIP_31_0_FIELD_OFFSET (0)
#define SE_NAT_KEY_RAM_KEY0_DATA0_KEY0_DIP_31_0_FIELD_SIZE   (32)
	
//-------------------------------------------------------------------------
// SE_NAT_KEY_RAM_KEY0_DATA1 INFO:
//-------------------------------------------------------------------------
#define SE_SE_NAT_KEY_RAM_KEY0_DATA1_REG_ADDR (SE_BASE_ADDR+0x188404)
#define SE_NAT_KEY_RAM_KEY0_DATA1_KEY0_DIP_63_32_FIELD_OFFSET (0)
#define SE_NAT_KEY_RAM_KEY0_DATA1_KEY0_DIP_63_32_FIELD_SIZE   (32)
	
//-------------------------------------------------------------------------
// SE_NAT_KEY_RAM_KEY0_DATA2 INFO:
//-------------------------------------------------------------------------
#define SE_SE_NAT_KEY_RAM_KEY0_DATA2_REG_ADDR (SE_BASE_ADDR+0x188408)
#define SE_NAT_KEY_RAM_KEY0_DATA2_KEY0_DIP_95_64_FIELD_OFFSET (0)
#define SE_NAT_KEY_RAM_KEY0_DATA2_KEY0_DIP_95_64_FIELD_SIZE   (32)
	
//-------------------------------------------------------------------------
// SE_NAT_KEY_RAM_KEY0_DATA3 INFO:
//-------------------------------------------------------------------------
#define SE_SE_NAT_KEY_RAM_KEY0_DATA3_REG_ADDR (SE_BASE_ADDR+0x18840c)
#define SE_NAT_KEY_RAM_KEY0_DATA3_KEY0_DIP_127_96_FIELD_OFFSET (0)
#define SE_NAT_KEY_RAM_KEY0_DATA3_KEY0_DIP_127_96_FIELD_SIZE   (32)
	
//-------------------------------------------------------------------------
// SE_NAT_KEY_RAM_KEY0_DATA4 INFO:
//-------------------------------------------------------------------------
#define SE_SE_NAT_KEY_RAM_KEY0_DATA4_REG_ADDR (SE_BASE_ADDR+0x188410)
#define SE_NAT_KEY_RAM_KEY0_DATA4_KEY0_SIP_31_0_FIELD_OFFSET (0)
#define SE_NAT_KEY_RAM_KEY0_DATA4_KEY0_SIP_31_0_FIELD_SIZE   (32)
	
//-------------------------------------------------------------------------
// SE_NAT_KEY_RAM_KEY0_DATA5 INFO:
//-------------------------------------------------------------------------
#define SE_SE_NAT_KEY_RAM_KEY0_DATA5_REG_ADDR (SE_BASE_ADDR+0x188414)
#define SE_NAT_KEY_RAM_KEY0_DATA5_KEY0_SIP_63_32_FIELD_OFFSET (0)
#define SE_NAT_KEY_RAM_KEY0_DATA5_KEY0_SIP_63_32_FIELD_SIZE   (32)
	
//-------------------------------------------------------------------------
// SE_NAT_KEY_RAM_KEY0_DATA6 INFO:
//-------------------------------------------------------------------------
#define SE_SE_NAT_KEY_RAM_KEY0_DATA6_REG_ADDR (SE_BASE_ADDR+0x188418)
#define SE_NAT_KEY_RAM_KEY0_DATA6_KEY0_SIP_95_64_FIELD_OFFSET (0)
#define SE_NAT_KEY_RAM_KEY0_DATA6_KEY0_SIP_95_64_FIELD_SIZE   (32)
	
//-------------------------------------------------------------------------
// SE_NAT_KEY_RAM_KEY0_DATA7 INFO:
//-------------------------------------------------------------------------
#define SE_SE_NAT_KEY_RAM_KEY0_DATA7_REG_ADDR (SE_BASE_ADDR+0x18841c)
#define SE_NAT_KEY_RAM_KEY0_DATA7_KEY0_SIP_127_96_FIELD_OFFSET (0)
#define SE_NAT_KEY_RAM_KEY0_DATA7_KEY0_SIP_127_96_FIELD_SIZE   (32)
	
//-------------------------------------------------------------------------
// SE_NAT_KEY_RAM_KEY0_DATA8 INFO:
//-------------------------------------------------------------------------
#define SE_SE_NAT_KEY_RAM_KEY0_DATA8_REG_ADDR (SE_BASE_ADDR+0x188420)
#define SE_NAT_KEY_RAM_KEY0_DATA8_KEY0_SPORT_FIELD_OFFSET (16)
#define SE_NAT_KEY_RAM_KEY0_DATA8_KEY0_SPORT_FIELD_SIZE   (16)
#define SE_NAT_KEY_RAM_KEY0_DATA8_KEY0_DPORT_FIELD_OFFSET (0)
#define SE_NAT_KEY_RAM_KEY0_DATA8_KEY0_DPORT_FIELD_SIZE   (16)
	
//-------------------------------------------------------------------------
// SE_NAT_KEY_RAM_KEY0_DATA9 INFO:
//-------------------------------------------------------------------------
#define SE_SE_NAT_KEY_RAM_KEY0_DATA9_REG_ADDR (SE_BASE_ADDR+0x188424)
#define SE_NAT_KEY_RAM_KEY0_DATA9_KEY0_PKT_ID_31_0_FIELD_OFFSET (0)
#define SE_NAT_KEY_RAM_KEY0_DATA9_KEY0_PKT_ID_31_0_FIELD_SIZE   (32)
	
//-------------------------------------------------------------------------
// SE_NAT_KEY_RAM_KEY0_DATA10 INFO:
//-------------------------------------------------------------------------
#define SE_SE_NAT_KEY_RAM_KEY0_DATA10_REG_ADDR (SE_BASE_ADDR+0x188428)
#define SE_NAT_KEY_RAM_KEY0_DATA10_KEY0_V6_FLAG_FIELD_OFFSET (4)
#define SE_NAT_KEY_RAM_KEY0_DATA10_KEY0_V6_FLAG_FIELD_SIZE   (1)
#define SE_NAT_KEY_RAM_KEY0_DATA10_KEY0_DNAT_FLAG_FIELD_OFFSET (3)
#define SE_NAT_KEY_RAM_KEY0_DATA10_KEY0_DNAT_FLAG_FIELD_SIZE   (1)
#define SE_NAT_KEY_RAM_KEY0_DATA10_KEY0_FRAG_FLAG_FIELD_OFFSET (1)
#define SE_NAT_KEY_RAM_KEY0_DATA10_KEY0_FRAG_FLAG_FIELD_SIZE   (2)
#define SE_NAT_KEY_RAM_KEY0_DATA10_KEY0_UDP_FLAG_FIELD_OFFSET (0)
#define SE_NAT_KEY_RAM_KEY0_DATA10_KEY0_UDP_FLAG_FIELD_SIZE   (1)
	
//-------------------------------------------------------------------------
// SE_NAT_RESULT_RAM_RESULT0_DATA0 INFO:
//-------------------------------------------------------------------------
#define SE_SE_NAT_RESULT_RAM_RESULT0_DATA0_REG_ADDR (SE_BASE_ADDR+0x188800)
#define SE_NAT_RESULT_RAM_RESULT0_DATA0_RESULT0_REPLACE_IP_31_0_FIELD_OFFSET (0)
#define SE_NAT_RESULT_RAM_RESULT0_DATA0_RESULT0_REPLACE_IP_31_0_FIELD_SIZE   (32)
	
//-------------------------------------------------------------------------
// SE_NAT_RESULT_RAM_RESULT0_DATA1 INFO:
//-------------------------------------------------------------------------
#define SE_SE_NAT_RESULT_RAM_RESULT0_DATA1_REG_ADDR (SE_BASE_ADDR+0x188804)
#define SE_NAT_RESULT_RAM_RESULT0_DATA1_RESULT0_REPLACE_IP_63_32_FIELD_OFFSET (0)
#define SE_NAT_RESULT_RAM_RESULT0_DATA1_RESULT0_REPLACE_IP_63_32_FIELD_SIZE   (32)
	
//-------------------------------------------------------------------------
// SE_NAT_RESULT_RAM_RESULT0_DATA2 INFO:
//-------------------------------------------------------------------------
#define SE_SE_NAT_RESULT_RAM_RESULT0_DATA2_REG_ADDR (SE_BASE_ADDR+0x188808)
#define SE_NAT_RESULT_RAM_RESULT0_DATA2_RESULT0_REPLACE_IP_95_64_FIELD_OFFSET (0)
#define SE_NAT_RESULT_RAM_RESULT0_DATA2_RESULT0_REPLACE_IP_95_64_FIELD_SIZE   (32)
	
//-------------------------------------------------------------------------
// SE_NAT_RESULT_RAM_RESULT0_DATA3 INFO:
//-------------------------------------------------------------------------
#define SE_SE_NAT_RESULT_RAM_RESULT0_DATA3_REG_ADDR (SE_BASE_ADDR+0x18880c)
#define SE_NAT_RESULT_RAM_RESULT0_DATA3_RESULT0_REPLACE_IP_100_96_FIELD_OFFSET (0)
#define SE_NAT_RESULT_RAM_RESULT0_DATA3_RESULT0_REPLACE_IP_100_96_FIELD_SIZE   (5)
	
//-------------------------------------------------------------------------
// SE_NAT_RESULT_RAM_RESULT0_DATA4 INFO:
//-------------------------------------------------------------------------
#define SE_SE_NAT_RESULT_RAM_RESULT0_DATA4_REG_ADDR (SE_BASE_ADDR+0x188810)
#define SE_NAT_RESULT_RAM_RESULT0_DATA4_RESULT0_REPLACE_PORT_4_0_FIELD_OFFSET (27)
#define SE_NAT_RESULT_RAM_RESULT0_DATA4_RESULT0_REPLACE_PORT_4_0_FIELD_SIZE   (5)
#define SE_NAT_RESULT_RAM_RESULT0_DATA4_RESULT0_REPLACE_IP_127_101_FIELD_OFFSET (0)
#define SE_NAT_RESULT_RAM_RESULT0_DATA4_RESULT0_REPLACE_IP_127_101_FIELD_SIZE   (27)
	
//-------------------------------------------------------------------------
// SE_NAT_RESULT_RAM_RESULT0_DATA5 INFO:
//-------------------------------------------------------------------------
#define SE_SE_NAT_RESULT_RAM_RESULT0_DATA5_REG_ADDR (SE_BASE_ADDR+0x188814)
#define SE_NAT_RESULT_RAM_RESULT0_DATA5_RESULT0_REPLACE_PRIORITY_EN_FIELD_OFFSET (31)
#define SE_NAT_RESULT_RAM_RESULT0_DATA5_RESULT0_REPLACE_PRIORITY_EN_FIELD_SIZE   (1)
#define SE_NAT_RESULT_RAM_RESULT0_DATA5_RESULT0_REPLACE_PRIORITY_2_0_FIELD_OFFSET (28)
#define SE_NAT_RESULT_RAM_RESULT0_DATA5_RESULT0_REPLACE_PRIORITY_2_0_FIELD_SIZE   (3)
#define SE_NAT_RESULT_RAM_RESULT0_DATA5_RESULT0_SMAC_INDEX_5_0_FIELD_OFFSET (22)
#define SE_NAT_RESULT_RAM_RESULT0_DATA5_RESULT0_SMAC_INDEX_5_0_FIELD_SIZE   (6)
#define SE_NAT_RESULT_RAM_RESULT0_DATA5_RESULT0_DMAC_INDEX_10_0_FIELD_OFFSET (11)
#define SE_NAT_RESULT_RAM_RESULT0_DATA5_RESULT0_DMAC_INDEX_10_0_FIELD_SIZE   (11)
#define SE_NAT_RESULT_RAM_RESULT0_DATA5_RESULT0_REPLACE_PORT_15_5_FIELD_OFFSET (0)
#define SE_NAT_RESULT_RAM_RESULT0_DATA5_RESULT0_REPLACE_PORT_15_5_FIELD_SIZE   (11)
	
//-------------------------------------------------------------------------
// SE_NAT_RESULT_RAM_RESULT0_DATA6 INFO:
//-------------------------------------------------------------------------
#define SE_SE_NAT_RESULT_RAM_RESULT0_DATA6_REG_ADDR (SE_BASE_ADDR+0x188818)
#define SE_NAT_RESULT_RAM_RESULT0_DATA6_RESULT0_NAT_ID_12_0_FIELD_OFFSET (19)
#define SE_NAT_RESULT_RAM_RESULT0_DATA6_RESULT0_NAT_ID_12_0_FIELD_SIZE   (13)
#define SE_NAT_RESULT_RAM_RESULT0_DATA6_RESULT0_SPL_EN_FIELD_OFFSET (18)
#define SE_NAT_RESULT_RAM_RESULT0_DATA6_RESULT0_SPL_EN_FIELD_SIZE   (1)
#define SE_NAT_RESULT_RAM_RESULT0_DATA6_RESULT0_SPL_INDEX_7_0_FIELD_OFFSET (10)
#define SE_NAT_RESULT_RAM_RESULT0_DATA6_RESULT0_SPL_INDEX_7_0_FIELD_SIZE   (8)
#define SE_NAT_RESULT_RAM_RESULT0_DATA6_RESULT0_MIB_EN_FIELD_OFFSET (9)
#define SE_NAT_RESULT_RAM_RESULT0_DATA6_RESULT0_MIB_EN_FIELD_SIZE   (1)
#define SE_NAT_RESULT_RAM_RESULT0_DATA6_RESULT0_MIB_INDEX_8_0_FIELD_OFFSET (0)
#define SE_NAT_RESULT_RAM_RESULT0_DATA6_RESULT0_MIB_INDEX_8_0_FIELD_SIZE   (9)
	
//-------------------------------------------------------------------------
// SE_NAT_RESULT_RAM_RESULT0_DATA7 INFO:
//-------------------------------------------------------------------------
#define SE_SE_NAT_RESULT_RAM_RESULT0_DATA7_REG_ADDR (SE_BASE_ADDR+0x18881c)
#define SE_NAT_RESULT_RAM_RESULT0_DATA7_RESULT0_HIT_LOCATION_FIELD_OFFSET (4)
#define SE_NAT_RESULT_RAM_RESULT0_DATA7_RESULT0_HIT_LOCATION_FIELD_SIZE   (1)
#define SE_NAT_RESULT_RAM_RESULT0_DATA7_RESULT0_HIT_FIELD_OFFSET (3)
#define SE_NAT_RESULT_RAM_RESULT0_DATA7_RESULT0_HIT_FIELD_SIZE   (1)
#define SE_NAT_RESULT_RAM_RESULT0_DATA7_RESULT0_NAT_ID_15_13_FIELD_OFFSET (0)
#define SE_NAT_RESULT_RAM_RESULT0_DATA7_RESULT0_NAT_ID_15_13_FIELD_SIZE   (3)
	
//-------------------------------------------------------------------------
// TCAM_STATUS_RGT INFO:
//-------------------------------------------------------------------------
#define SE_TCAM_STATUS_RGT_REG_ADDR (SE_BASE_ADDR+0x190000)
#define TCAM_STATUS_RGT_TCAM_P4_BP_OVF_FIELD_OFFSET (4)
#define TCAM_STATUS_RGT_TCAM_P4_BP_OVF_FIELD_SIZE   (1)
#define TCAM_STATUS_RGT_TCAM_P3_BP_OVF_FIELD_OFFSET (3)
#define TCAM_STATUS_RGT_TCAM_P3_BP_OVF_FIELD_SIZE   (1)
#define TCAM_STATUS_RGT_TCAM_P2_BP_OVF_FIELD_OFFSET (2)
#define TCAM_STATUS_RGT_TCAM_P2_BP_OVF_FIELD_SIZE   (1)
#define TCAM_STATUS_RGT_TCAM_P1_BP_OVF_FIELD_OFFSET (1)
#define TCAM_STATUS_RGT_TCAM_P1_BP_OVF_FIELD_SIZE   (1)
#define TCAM_STATUS_RGT_TCAM_P0_BP_OVF_FIELD_OFFSET (0)
#define TCAM_STATUS_RGT_TCAM_P0_BP_OVF_FIELD_SIZE   (1)
	
//-------------------------------------------------------------------------
// TCAM_CLR_RGT INFO:
//-------------------------------------------------------------------------
#define SE_TCAM_CLR_RGT_REG_ADDR (SE_BASE_ADDR+0x190004)
#define TCAM_CLR_RGT_TCAM_BLK4_TB_CLR_FIELD_OFFSET (4)
#define TCAM_CLR_RGT_TCAM_BLK4_TB_CLR_FIELD_SIZE   (1)
#define TCAM_CLR_RGT_TCAM_BLK3_TB_CLR_FIELD_OFFSET (3)
#define TCAM_CLR_RGT_TCAM_BLK3_TB_CLR_FIELD_SIZE   (1)
#define TCAM_CLR_RGT_TCAM_BLK2_TB_CLR_FIELD_OFFSET (2)
#define TCAM_CLR_RGT_TCAM_BLK2_TB_CLR_FIELD_SIZE   (1)
#define TCAM_CLR_RGT_TCAM_BLK1_TB_CLR_FIELD_OFFSET (1)
#define TCAM_CLR_RGT_TCAM_BLK1_TB_CLR_FIELD_SIZE   (1)
#define TCAM_CLR_RGT_TCAM_BLK0_TB_CLR_FIELD_OFFSET (0)
#define TCAM_CLR_RGT_TCAM_BLK0_TB_CLR_FIELD_SIZE   (1)
	
//-------------------------------------------------------------------------
// TCAM_BLK_CONFIG0_RGT INFO:
//-------------------------------------------------------------------------
#define SE_TCAM_BLK_CONFIG0_RGT_REG_ADDR (SE_BASE_ADDR+0x190008)
#define TCAM_BLK_CONFIG0_RGT_TCAM_BLK4_PORT_CFG_FIELD_OFFSET (12)
#define TCAM_BLK_CONFIG0_RGT_TCAM_BLK4_PORT_CFG_FIELD_SIZE   (3)
#define TCAM_BLK_CONFIG0_RGT_TCAM_BLK3_PORT_CFG_FIELD_OFFSET (9)
#define TCAM_BLK_CONFIG0_RGT_TCAM_BLK3_PORT_CFG_FIELD_SIZE   (3)
#define TCAM_BLK_CONFIG0_RGT_TCAM_BLK2_PORT_CFG_FIELD_OFFSET (6)
#define TCAM_BLK_CONFIG0_RGT_TCAM_BLK2_PORT_CFG_FIELD_SIZE   (3)
#define TCAM_BLK_CONFIG0_RGT_TCAM_BLK1_PORT_CFG_FIELD_OFFSET (3)
#define TCAM_BLK_CONFIG0_RGT_TCAM_BLK1_PORT_CFG_FIELD_SIZE   (3)
#define TCAM_BLK_CONFIG0_RGT_TCAM_BLK0_PORT_CFG_FIELD_OFFSET (0)
#define TCAM_BLK_CONFIG0_RGT_TCAM_BLK0_PORT_CFG_FIELD_SIZE   (3)
	
//-------------------------------------------------------------------------
// TCAM_CONFIG1_RGT INFO:
//-------------------------------------------------------------------------
#define SE_TCAM_CONFIG1_RGT_REG_ADDR (SE_BASE_ADDR+0x19000C)
#define TCAM_CONFIG1_RGT_P4_FIFO_BP_THRESH_FIELD_OFFSET (16)
#define TCAM_CONFIG1_RGT_P4_FIFO_BP_THRESH_FIELD_SIZE   (3)
#define TCAM_CONFIG1_RGT_P3_FIFO_BP_THRESH_FIELD_OFFSET (12)
#define TCAM_CONFIG1_RGT_P3_FIFO_BP_THRESH_FIELD_SIZE   (3)
#define TCAM_CONFIG1_RGT_P2_FIFO_BP_THRESH_FIELD_OFFSET (8)
#define TCAM_CONFIG1_RGT_P2_FIFO_BP_THRESH_FIELD_SIZE   (3)
#define TCAM_CONFIG1_RGT_P1_FIFO_BP_THRESH_FIELD_OFFSET (4)
#define TCAM_CONFIG1_RGT_P1_FIFO_BP_THRESH_FIELD_SIZE   (3)
#define TCAM_CONFIG1_RGT_P0_FIFO_BP_THRESH_FIELD_OFFSET (0)
#define TCAM_CONFIG1_RGT_P0_FIFO_BP_THRESH_FIELD_SIZE   (3)
	
//-------------------------------------------------------------------------
// TCAM_TB_OP_ADDR_RGT INFO:
//-------------------------------------------------------------------------
#define SE_TCAM_TB_OP_ADDR_RGT_REG_ADDR (SE_BASE_ADDR+0x19003C)
#define TCAM_TB_OP_ADDR_RGT_HOST_MGT_REQ_BUSY_FIELD_OFFSET (31)
#define TCAM_TB_OP_ADDR_RGT_HOST_MGT_REQ_BUSY_FIELD_SIZE   (1)
#define TCAM_TB_OP_ADDR_RGT_HOST_MGT_REQ_OPCODE_FIELD_OFFSET (24)
#define TCAM_TB_OP_ADDR_RGT_HOST_MGT_REQ_OPCODE_FIELD_SIZE   (1)
#define TCAM_TB_OP_ADDR_RGT_HOST_MGT_REQ_ID_FIELD_OFFSET (16)
#define TCAM_TB_OP_ADDR_RGT_HOST_MGT_REQ_ID_FIELD_SIZE   (7)
#define TCAM_TB_OP_ADDR_RGT_HOST_MGT_REQ_ADDR_FIELD_OFFSET (0)
#define TCAM_TB_OP_ADDR_RGT_HOST_MGT_REQ_ADDR_FIELD_SIZE   (5)
	
//-------------------------------------------------------------------------
// TCAM_TB_WRDATA00_RGT INFO:
//-------------------------------------------------------------------------
#define SE_TCAM_TB_WRDATA00_RGT_REG_ADDR (SE_BASE_ADDR+0x190040)
#define TCAM_TB_WRDATA00_RGT_TCAM_TB_WRDATA00_FIELD_OFFSET (0)
#define TCAM_TB_WRDATA00_RGT_TCAM_TB_WRDATA00_FIELD_SIZE   (32)
	
//-------------------------------------------------------------------------
// TCAM_TB_WRDATA01_RGT INFO:
//-------------------------------------------------------------------------
#define SE_TCAM_TB_WRDATA01_RGT_REG_ADDR (SE_BASE_ADDR+0x190044)
#define TCAM_TB_WRDATA01_RGT_TCAM_TB_WRDATA01_FIELD_OFFSET (0)
#define TCAM_TB_WRDATA01_RGT_TCAM_TB_WRDATA01_FIELD_SIZE   (32)
	
//-------------------------------------------------------------------------
// TCAM_TB_WRDATA02_RGT INFO:
//-------------------------------------------------------------------------
#define SE_TCAM_TB_WRDATA02_RGT_REG_ADDR (SE_BASE_ADDR+0x190048)
#define TCAM_TB_WRDATA02_RGT_TCAM_TB_WRDATA02_FIELD_OFFSET (0)
#define TCAM_TB_WRDATA02_RGT_TCAM_TB_WRDATA02_FIELD_SIZE   (8)
	
//-------------------------------------------------------------------------
// TCAM_RESERVED0 INFO:
//-------------------------------------------------------------------------
#define SE_TCAM_RESERVED0_REG_ADDR (SE_BASE_ADDR+0x19004c)
	
//-------------------------------------------------------------------------
// TCAM_TB_RDDATA00_RGT INFO:
//-------------------------------------------------------------------------
#define SE_TCAM_TB_RDDATA00_RGT_REG_ADDR (SE_BASE_ADDR+0x190080)
#define TCAM_TB_RDDATA00_RGT_TCAM_TB_RDDATA00_FIELD_OFFSET (0)
#define TCAM_TB_RDDATA00_RGT_TCAM_TB_RDDATA00_FIELD_SIZE   (32)
	
//-------------------------------------------------------------------------
// TCAM_TB_RDDATA01_RGT INFO:
//-------------------------------------------------------------------------
#define SE_TCAM_TB_RDDATA01_RGT_REG_ADDR (SE_BASE_ADDR+0x190084)
#define TCAM_TB_RDDATA01_RGT_TCAM_TB_RDDATA01_FIELD_OFFSET (0)
#define TCAM_TB_RDDATA01_RGT_TCAM_TB_RDDATA01_FIELD_SIZE   (32)
	
//-------------------------------------------------------------------------
// TCAM_TB_RDDATA02_RGT INFO:
//-------------------------------------------------------------------------
#define SE_TCAM_TB_RDDATA02_RGT_REG_ADDR (SE_BASE_ADDR+0x190088)
#define TCAM_TB_RDDATA02_RGT_TCAM_TB_RDDATA02_FIELD_OFFSET (0)
#define TCAM_TB_RDDATA02_RGT_TCAM_TB_RDDATA02_FIELD_SIZE   (8)
	

#endif

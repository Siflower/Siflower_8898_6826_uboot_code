#ifndef SPL_SE_C
#define SPL_SE_C

#include "spl_se.h"
#include "se_common.h"
#include <string.h>

//Table: Intf SPL
void cfg_intf_spl_table_item(SplKey_S* spl_key) {
     int i = 0;

     SplTableInfo_U m_spl_table_info_u;

     for(i=0; i<2; i++) {
         m_spl_table_info_u.data[i] = 0x0;
     }
     m_spl_table_info_u.m_spl_table_info_s.credit_7_0        = get_data64(spl_key->credit,   0, 8);
     m_spl_table_info_u.m_spl_table_info_s.credit_15_8       = get_data64(spl_key->credit,   8, 8);
     m_spl_table_info_u.m_spl_table_info_s.credit_23_16      = get_data64(spl_key->credit,  16, 8);
     m_spl_table_info_u.m_spl_table_info_s.cnt_7_0           = get_data64(spl_key->cnt,  0, 8);
     m_spl_table_info_u.m_spl_table_info_s.cnt_15_8          = get_data64(spl_key->cnt,  8, 8);
     m_spl_table_info_u.m_spl_table_info_s.cnt_23_16         = get_data64(spl_key->cnt, 16, 8);
     m_spl_table_info_u.m_spl_table_info_s.cnt_29_24         = get_data64(spl_key->cnt, 24, 8);

     SE_WR_REG(SE_TB_WRDATA00_RGT_REG_ADDR, m_spl_table_info_u.data[0]);
     SE_WR_REG(SE_TB_WRDATA01_RGT_REG_ADDR, m_spl_table_info_u.data[1]);
     SE_WR_REG(SE_TB_OP_ADDR_RGT_REG_ADDR, (WRITE_TABLE<<TB_OP_ADDR_RGT_HOST_MGT_REQ_OPCODE_FIELD_OFFSET)+
                                           (ARP_SE_MACSPL_TABLE<<TB_OP_ADDR_RGT_HOST_MGT_REQ_ID_FIELD_OFFSET)+
                                           (spl_key->item_index<<TB_OP_ADDR_RGT_HOST_MGT_REQ_ADDR_FIELD_OFFSET)
                  );

     //enable spl_table
     update_reg(SE_CONFIG2_RGT_REG_ADDR, CONFIG2_RGT_INTF_TABLE_VLD_FIELD_OFFSET, CONFIG2_RGT_INTF_TABLE_VLD_FIELD_SIZE, 1);
}

//Table: Ivlan SPL
void cfg_ivlan_spl_table_item(SplKey_S* spl_key) {
     int i = 0;

     SplTableInfo_U m_spl_table_info_u;

     for(i=0; i<2; i++) {
         m_spl_table_info_u.data[i] = 0x0;
     }
     m_spl_table_info_u.m_spl_table_info_s.credit_7_0        = get_data64(spl_key->credit,   0, 8);
     m_spl_table_info_u.m_spl_table_info_s.credit_15_8       = get_data64(spl_key->credit,   8, 8);
     m_spl_table_info_u.m_spl_table_info_s.credit_23_16      = get_data64(spl_key->credit,  16, 8);
     m_spl_table_info_u.m_spl_table_info_s.cnt_7_0           = get_data64(spl_key->cnt,  0, 8);
     m_spl_table_info_u.m_spl_table_info_s.cnt_15_8          = get_data64(spl_key->cnt,  8, 8);
     m_spl_table_info_u.m_spl_table_info_s.cnt_23_16         = get_data64(spl_key->cnt, 16, 8);
     m_spl_table_info_u.m_spl_table_info_s.cnt_29_24         = get_data64(spl_key->cnt, 24, 8);

     SE_WR_REG(SE_TB_WRDATA00_RGT_REG_ADDR, m_spl_table_info_u.data[0]);
     SE_WR_REG(SE_TB_WRDATA01_RGT_REG_ADDR, m_spl_table_info_u.data[1]);
     SE_WR_REG(SE_TB_OP_ADDR_RGT_REG_ADDR, (WRITE_TABLE<<TB_OP_ADDR_RGT_HOST_MGT_REQ_OPCODE_FIELD_OFFSET)+
                                           (IVLAN_PORT_SE_IVLAN_SPL_TABLE<<TB_OP_ADDR_RGT_HOST_MGT_REQ_ID_FIELD_OFFSET)+
                                           (spl_key->item_index<<TB_OP_ADDR_RGT_HOST_MGT_REQ_ADDR_FIELD_OFFSET)
                  );

     //enable spl_table
     update_reg(SE_CONFIG0_RGT_REG_ADDR, CONFIG0_RGT_IVPSPL_MODE_FIELD_OFFSET, CONFIG0_RGT_IVPSPL_MODE_FIELD_SIZE, 1);
}

#endif

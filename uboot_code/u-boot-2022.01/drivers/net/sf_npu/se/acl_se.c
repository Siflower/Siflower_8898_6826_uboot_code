#ifndef ACL_SE_C
#define ACL_SE_C

#include "acl_se.h"
#include "tcam_se.h"

extern BlkTable_S blk_tables[8];

//MPP: ACL, Table: ACL, Mode: 7
void cfg_acl_mode7_table_item(AclMode7Key_S* acl_mode7_key, AclModeRsp_S* acl_mode_rsp, AclModeCfg_S* acl_mode_cfg, int is_iacl) {

     int i = 0;
     KeyLocInfo_S m_key_loc_info;

     AclMode7TableInfo_U m_acl_mode7_table_info_u;
     AclMode7TableInfo_U m_acl_mode7_table_mask_info_u;

     init_blk_tables(&blk_tables[0]);

     #if SE_DEBUG_INFO
     {
         int i = 0;
         int j = 0;
         for(i=1; i<2; i++) {
             for(j=0; j<2; j++) {
                 printf("33 blk_tables[%0d].items[%0d].blk_id       = %0d\n", i, j, blk_tables[i].items[j].blk_id      );
                 printf("33 blk_tables[%0d].items[%0d].table_id     = %0d\n", i, j, blk_tables[i].items[j].table_id    );
                 printf("33 blk_tables[%0d].items[%0d].key_mode     = %0d\n", i, j, blk_tables[i].items[j].key_mode    );
                 printf("33 blk_tables[%0d].items[%0d].slice_bitmap = %0d\n", i, j, blk_tables[i].items[j].slice_bitmap);
                 printf("33 blk_tables[%0d].items[%0d].empty_slice  = %0d\n", i, j, blk_tables[i].items[j].empty_slice );
             }
         }
     }
     #endif

     for(i=0; i<3; i++) {
         m_acl_mode7_table_info_u.data[i] = 0x0;
         m_acl_mode7_table_mask_info_u.data[i] = 0xFFFFFFFF;
     }
     m_acl_mode7_table_info_u.m_acl_mode7_table_info_s.new_id             = acl_mode_rsp->new_id                 ;
     m_acl_mode7_table_info_u.m_acl_mode7_table_info_s.dscp_replace_en    = acl_mode_rsp->dscp_replace_en        ;
     m_acl_mode7_table_info_u.m_acl_mode7_table_info_s.action_0           = get_data8(acl_mode_rsp->action, 0, 1);
     m_acl_mode7_table_info_u.m_acl_mode7_table_info_s.action_2_1         = get_data8(acl_mode_rsp->action, 1, 2);
     m_acl_mode7_table_info_u.m_acl_mode7_table_info_s.priority           = acl_mode_rsp->priority               ;
     m_acl_mode7_table_info_u.m_acl_mode7_table_info_s.priority_en        = acl_mode_rsp->priority_en            ;
     m_acl_mode7_table_info_u.m_acl_mode7_table_info_s.mf_type_7_0        = get_data16(acl_mode7_key->mf_type, 0, 8)      ;
     m_acl_mode7_table_info_u.m_acl_mode7_table_info_s.mf_type_11_8       = get_data16(acl_mode7_key->mf_type, 8, 4)      ;
     m_acl_mode7_table_info_u.m_acl_mode7_table_info_s.mf_iport_id_3_0    = get_data16(acl_mode7_key->mf_iport_id, 0, 4)  ;
     m_acl_mode7_table_info_u.m_acl_mode7_table_info_s.mf_iport_id_5_4    = get_data16(acl_mode7_key->mf_iport_id, 4, 2)  ;
     m_acl_mode7_table_info_u.m_acl_mode7_table_info_s.mf_oport_id        = acl_mode7_key->mf_oport_id                    ;
     m_acl_mode7_table_info_u.m_acl_mode7_table_info_s.mf_user_frag_7_0   = get_data32(acl_mode7_key->mf_user_frag, 0 , 8);
     m_acl_mode7_table_info_u.m_acl_mode7_table_info_s.mf_user_frag_15_8  = get_data32(acl_mode7_key->mf_user_frag, 8 , 8);
     m_acl_mode7_table_info_u.m_acl_mode7_table_info_s.mf_user_frag_23_16 = get_data32(acl_mode7_key->mf_user_frag, 16, 8);
     m_acl_mode7_table_info_u.m_acl_mode7_table_info_s.mf_user_frag_31_24 = get_data32(acl_mode7_key->mf_user_frag, 24, 8);

     m_acl_mode7_table_mask_info_u.m_acl_mode7_table_info_s.mf_type_7_0         = 0x0  ;
     m_acl_mode7_table_mask_info_u.m_acl_mode7_table_info_s.mf_type_11_8        = 0x0  ;
     m_acl_mode7_table_mask_info_u.m_acl_mode7_table_info_s.mf_iport_id_3_0     = 0x0  ;
     m_acl_mode7_table_mask_info_u.m_acl_mode7_table_info_s.mf_iport_id_5_4     = 0x0  ;
     m_acl_mode7_table_mask_info_u.m_acl_mode7_table_info_s.mf_oport_id         = 0x0  ;
     m_acl_mode7_table_mask_info_u.m_acl_mode7_table_info_s.mf_user_frag_7_0    = 0x0  ;
     m_acl_mode7_table_mask_info_u.m_acl_mode7_table_info_s.mf_user_frag_15_8   = 0x0  ;
     m_acl_mode7_table_mask_info_u.m_acl_mode7_table_info_s.mf_user_frag_23_16  = 0x0  ;
     m_acl_mode7_table_mask_info_u.m_acl_mode7_table_info_s.mf_user_frag_31_24  = 0x0  ;

     if(is_iacl == 1) {
         get_blk_index(acl_mode7_key->table_id, acl_mode7_key->key_mode, IACL_TCAM_BLK, &blk_tables[0], &m_key_loc_info);
     }
     else {
         get_blk_index(acl_mode7_key->table_id, acl_mode7_key->key_mode, EACL_TCAM_BLK, &blk_tables[0], &m_key_loc_info);
     }
     #if SE_DEBUG_INFO
     printf("m_key_loc_info.blk_id      = %0d\n", m_key_loc_info.blk_id     );
     printf("m_key_loc_info.item_index  = %0d\n", m_key_loc_info.item_index );
     printf("m_key_loc_info.slice_index = %0d\n", m_key_loc_info.slice_index);
     #endif

     if(acl_mode7_key->key_mode == 0) {
         unsigned int req_id    = 0x0;
         unsigned int req_index = 0x0;

         req_id    = TCAM_BLK_RAM_ID(m_key_loc_info.blk_id, m_key_loc_info.slice_index);
         req_index = 2*m_key_loc_info.item_index;
         #if SE_DEBUG_INFO
         printf("req_id      = %0d\n",  req_id   );
         printf("req_index   = %0d\n",  req_index);
         #endif

         SE_WR_REG(SE_TCAM_TB_WRDATA00_RGT_REG_ADDR, m_acl_mode7_table_info_u.data[0]);
         SE_WR_REG(SE_TCAM_TB_WRDATA01_RGT_REG_ADDR, m_acl_mode7_table_info_u.data[1]);
         SE_WR_REG(SE_TCAM_TB_WRDATA02_RGT_REG_ADDR, m_acl_mode7_table_info_u.data[2]);
         SE_WR_REG(SE_TCAM_TB_OP_ADDR_RGT_REG_ADDR, (WRITE_TABLE<<TCAM_TB_OP_ADDR_RGT_HOST_MGT_REQ_OPCODE_FIELD_OFFSET)+
                                                    (req_id<<TCAM_TB_OP_ADDR_RGT_HOST_MGT_REQ_ID_FIELD_OFFSET)+
                                                    (req_index<<TCAM_TB_OP_ADDR_RGT_HOST_MGT_REQ_ADDR_FIELD_OFFSET)
                      );

         req_id    = TCAM_BLK_RAM_ID(m_key_loc_info.blk_id, m_key_loc_info.slice_index);
         req_index = 2*m_key_loc_info.item_index+1;
         SE_WR_REG(SE_TCAM_TB_WRDATA00_RGT_REG_ADDR, m_acl_mode7_table_mask_info_u.data[0]);
         SE_WR_REG(SE_TCAM_TB_WRDATA01_RGT_REG_ADDR, m_acl_mode7_table_mask_info_u.data[1]);
         SE_WR_REG(SE_TCAM_TB_WRDATA02_RGT_REG_ADDR, m_acl_mode7_table_mask_info_u.data[2]);
         SE_WR_REG(SE_TCAM_TB_OP_ADDR_RGT_REG_ADDR, (WRITE_TABLE<<TCAM_TB_OP_ADDR_RGT_HOST_MGT_REQ_OPCODE_FIELD_OFFSET)+
                                                    (req_id<<TCAM_TB_OP_ADDR_RGT_HOST_MGT_REQ_ID_FIELD_OFFSET)+
                                                    (req_index<<TCAM_TB_OP_ADDR_RGT_HOST_MGT_REQ_ADDR_FIELD_OFFSET)
                      );

         req_id    = TCAM_BLK_MODE_ID(m_key_loc_info.blk_id);
         req_index = m_key_loc_info.item_index;
         SE_WR_REG(SE_TCAM_TB_WRDATA00_RGT_REG_ADDR, (acl_mode7_key->key_mode<<2)+acl_mode7_key->table_id);
         SE_WR_REG(SE_TCAM_TB_OP_ADDR_RGT_REG_ADDR, (WRITE_TABLE<<TCAM_TB_OP_ADDR_RGT_HOST_MGT_REQ_OPCODE_FIELD_OFFSET)+
                                                    (req_id<<TCAM_TB_OP_ADDR_RGT_HOST_MGT_REQ_ID_FIELD_OFFSET)+
                                                    (req_index<<TCAM_TB_OP_ADDR_RGT_HOST_MGT_REQ_ADDR_FIELD_OFFSET)
                      );
     }

     //CFG WR
     SE_WR_REG(SE_TCAM_BLK_CONFIG0_RGT_REG_ADDR, (0<<TCAM_BLK_CONFIG0_RGT_TCAM_BLK0_PORT_CFG_FIELD_OFFSET) |
                                                 (1<<TCAM_BLK_CONFIG0_RGT_TCAM_BLK1_PORT_CFG_FIELD_OFFSET) |
                                                 (2<<TCAM_BLK_CONFIG0_RGT_TCAM_BLK2_PORT_CFG_FIELD_OFFSET) |
                                                 (3<<TCAM_BLK_CONFIG0_RGT_TCAM_BLK3_PORT_CFG_FIELD_OFFSET) |
                                                 (4<<TCAM_BLK_CONFIG0_RGT_TCAM_BLK4_PORT_CFG_FIELD_OFFSET)
              );

}

#endif

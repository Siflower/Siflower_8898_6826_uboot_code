#ifndef L3_SE_C
#define L3_SE_C

#include "l3_se.h"
#include "tcam_se.h"

extern BlkTable_S blk_tables[8];

//MPP: L3P0, Table: l3uc/mc*g, ipv4
void cfg_l3_uc_ipv4_table_item(L3UcIpv4Key_S* l3_uc_ipv4_key, L3UcRsp_S* l3_uc_rsp, L3Cfg_S* L3_cfg) {

     int i = 0;
     KeyLocInfo_S m_key_loc_info;

     L3UcIpv4TableInfo_U m_l3_uc_ipv4_table_info_u;
     L3UcIpv4TableInfo_U m_l3_uc_ipv4_table_mask_info_u;

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
         m_l3_uc_ipv4_table_info_u.data[i] = 0x0;
         m_l3_uc_ipv4_table_mask_info_u.data[i] = 0xFFFFFFFF;
     }
     m_l3_uc_ipv4_table_info_u.m_l3_uc_ipv4_table_info_s.next_hop_ptr_7_0  = get_data16(l3_uc_rsp->next_hop_ptr, 0, 8);
     m_l3_uc_ipv4_table_info_u.m_l3_uc_ipv4_table_info_s.next_hop_ptr_10_8 = get_data16(l3_uc_rsp->next_hop_ptr, 8, 3);
     m_l3_uc_ipv4_table_info_u.m_l3_uc_ipv4_table_info_s.oport_id_4_0      = get_data8(l3_uc_rsp->oport_id, 0, 5);
     m_l3_uc_ipv4_table_info_u.m_l3_uc_ipv4_table_info_s.oport_id_5        = get_data8(l3_uc_rsp->oport_id, 5, 1);
     m_l3_uc_ipv4_table_info_u.m_l3_uc_ipv4_table_info_s.intf_id           = l3_uc_rsp->intf_id                  ;
     m_l3_uc_ipv4_table_info_u.m_l3_uc_ipv4_table_info_s.dip0_3_0          = get_data8(l3_uc_ipv4_key->dip[0], 0, 4)  ;
     m_l3_uc_ipv4_table_info_u.m_l3_uc_ipv4_table_info_s.dip0_7_4          = get_data8(l3_uc_ipv4_key->dip[0], 4, 4)  ;
     m_l3_uc_ipv4_table_info_u.m_l3_uc_ipv4_table_info_s.dip1_3_0          = get_data8(l3_uc_ipv4_key->dip[1], 0, 4)  ;
     m_l3_uc_ipv4_table_info_u.m_l3_uc_ipv4_table_info_s.dip1_7_4          = get_data8(l3_uc_ipv4_key->dip[1], 4, 4)  ;
     m_l3_uc_ipv4_table_info_u.m_l3_uc_ipv4_table_info_s.dip2_3_0          = get_data8(l3_uc_ipv4_key->dip[2], 0, 4)  ;
     m_l3_uc_ipv4_table_info_u.m_l3_uc_ipv4_table_info_s.dip2_7_4          = get_data8(l3_uc_ipv4_key->dip[2], 4, 4)  ;
     m_l3_uc_ipv4_table_info_u.m_l3_uc_ipv4_table_info_s.dip3_3_0          = get_data8(l3_uc_ipv4_key->dip[3], 0, 4)  ;
     m_l3_uc_ipv4_table_info_u.m_l3_uc_ipv4_table_info_s.dip3_7_4          = get_data8(l3_uc_ipv4_key->dip[3], 4, 4)  ;
     m_l3_uc_ipv4_table_info_u.m_l3_uc_ipv4_table_info_s.ovid_3_0          = get_data16(l3_uc_ipv4_key->ovid , 0, 4)  ;
     m_l3_uc_ipv4_table_info_u.m_l3_uc_ipv4_table_info_s.ovid_11_4         = get_data16(l3_uc_ipv4_key->ovid , 4, 8)  ;

     m_l3_uc_ipv4_table_mask_info_u.m_l3_uc_ipv4_table_info_s.dip0_3_0          = 0x0  ;
     m_l3_uc_ipv4_table_mask_info_u.m_l3_uc_ipv4_table_info_s.dip0_7_4          = 0x0  ;
     m_l3_uc_ipv4_table_mask_info_u.m_l3_uc_ipv4_table_info_s.dip1_3_0          = 0x0  ;
     m_l3_uc_ipv4_table_mask_info_u.m_l3_uc_ipv4_table_info_s.dip1_7_4          = 0x0  ;
     m_l3_uc_ipv4_table_mask_info_u.m_l3_uc_ipv4_table_info_s.dip2_3_0          = 0x0  ;
     m_l3_uc_ipv4_table_mask_info_u.m_l3_uc_ipv4_table_info_s.dip2_7_4          = 0x0  ;
     m_l3_uc_ipv4_table_mask_info_u.m_l3_uc_ipv4_table_info_s.dip3_3_0          = 0x0  ;
     m_l3_uc_ipv4_table_mask_info_u.m_l3_uc_ipv4_table_info_s.dip3_7_4          = 0x0  ;
     m_l3_uc_ipv4_table_mask_info_u.m_l3_uc_ipv4_table_info_s.ovid_3_0          = 0x0  ;
     m_l3_uc_ipv4_table_mask_info_u.m_l3_uc_ipv4_table_info_s.ovid_11_4         = 0x0  ;

     get_blk_index(l3_uc_ipv4_key->table_id, l3_uc_ipv4_key->key_mode, L3P0_TCAM_BLK, &blk_tables[0], &m_key_loc_info);
     #if SE_DEBUG_INFO
     printf("m_key_loc_info.blk_id      = %0d\n", m_key_loc_info.blk_id     );
     printf("m_key_loc_info.item_index  = %0d\n", m_key_loc_info.item_index );
     printf("m_key_loc_info.slice_index = %0d\n", m_key_loc_info.slice_index);
     #endif

     if(l3_uc_ipv4_key->key_mode == 0) {
         unsigned int req_id    = 0x0;
         unsigned int req_index = 0x0;

         req_id    = TCAM_BLK_RAM_ID(m_key_loc_info.blk_id, m_key_loc_info.slice_index);
         req_index = 2*m_key_loc_info.item_index;
         #if SE_DEBUG_INFO
         printf("req_id      = %0d\n",  req_id   );
         printf("req_index   = %0d\n",  req_index);
         #endif

         SE_WR_REG(SE_TCAM_TB_WRDATA00_RGT_REG_ADDR, m_l3_uc_ipv4_table_info_u.data[0]);
         SE_WR_REG(SE_TCAM_TB_WRDATA01_RGT_REG_ADDR, m_l3_uc_ipv4_table_info_u.data[1]);
         SE_WR_REG(SE_TCAM_TB_WRDATA02_RGT_REG_ADDR, m_l3_uc_ipv4_table_info_u.data[2]);
         SE_WR_REG(SE_TCAM_TB_OP_ADDR_RGT_REG_ADDR, (WRITE_TABLE<<TCAM_TB_OP_ADDR_RGT_HOST_MGT_REQ_OPCODE_FIELD_OFFSET)+
                                                    (req_id<<TCAM_TB_OP_ADDR_RGT_HOST_MGT_REQ_ID_FIELD_OFFSET)+
                                                    (req_index<<TCAM_TB_OP_ADDR_RGT_HOST_MGT_REQ_ADDR_FIELD_OFFSET)
                      );

         req_id    = TCAM_BLK_RAM_ID(m_key_loc_info.blk_id, m_key_loc_info.slice_index);
         req_index = 2*m_key_loc_info.item_index+1;
         SE_WR_REG(SE_TCAM_TB_WRDATA00_RGT_REG_ADDR, m_l3_uc_ipv4_table_mask_info_u.data[0]);
         SE_WR_REG(SE_TCAM_TB_WRDATA01_RGT_REG_ADDR, m_l3_uc_ipv4_table_mask_info_u.data[1]);
         SE_WR_REG(SE_TCAM_TB_WRDATA02_RGT_REG_ADDR, m_l3_uc_ipv4_table_mask_info_u.data[2]);
         SE_WR_REG(SE_TCAM_TB_OP_ADDR_RGT_REG_ADDR, (WRITE_TABLE<<TCAM_TB_OP_ADDR_RGT_HOST_MGT_REQ_OPCODE_FIELD_OFFSET)+
                                                    (req_id<<TCAM_TB_OP_ADDR_RGT_HOST_MGT_REQ_ID_FIELD_OFFSET)+
                                                    (req_index<<TCAM_TB_OP_ADDR_RGT_HOST_MGT_REQ_ADDR_FIELD_OFFSET)
                      );

         req_id    = TCAM_BLK_MODE_ID(m_key_loc_info.blk_id);
         req_index = m_key_loc_info.item_index;
         SE_WR_REG(SE_TCAM_TB_WRDATA00_RGT_REG_ADDR, (l3_uc_ipv4_key->key_mode<<2)+l3_uc_ipv4_key->table_id);
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

//MPP: L3P0, Table: l3uc/mc*g, ipv6
void cfg_l3_uc_ipv6_table_item(L3UcIpv6Key_S* l3_uc_ipv6_key, L3UcRsp_S* l3_uc_rsp, L3Cfg_S* L3_cfg) {

     int i = 0;
     KeyLocInfo_S m_key_loc_info;

     L3UcIpv6TableInfo_U m_l3_uc_ipv6_table_info_u;
     L3UcIpv6TableInfo_U m_l3_uc_ipv6_table_mask_info_u;

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

     for(i=0; i<9; i++) {
         m_l3_uc_ipv6_table_info_u.data[i] = 0x0;
         m_l3_uc_ipv6_table_mask_info_u.data[i] = 0xFFFFFFFF;
     }
     m_l3_uc_ipv6_table_info_u.m_l3_uc_ipv6_table_info_s.next_hop_ptr_7_0  = get_data16(l3_uc_rsp->next_hop_ptr, 0, 8);
     m_l3_uc_ipv6_table_info_u.m_l3_uc_ipv6_table_info_s.next_hop_ptr_10_8 = get_data16(l3_uc_rsp->next_hop_ptr, 8, 3);
     m_l3_uc_ipv6_table_info_u.m_l3_uc_ipv6_table_info_s.oport_id_4_0      = get_data8(l3_uc_rsp->oport_id, 0, 5);
     m_l3_uc_ipv6_table_info_u.m_l3_uc_ipv6_table_info_s.oport_id_5        = get_data8(l3_uc_rsp->oport_id, 5, 1);
     m_l3_uc_ipv6_table_info_u.m_l3_uc_ipv6_table_info_s.intf_id           = l3_uc_rsp->intf_id                  ;
     m_l3_uc_ipv6_table_info_u.m_l3_uc_ipv6_table_info_s.dip0_3_0          = get_data8(l3_uc_ipv6_key->dip[0], 0, 4)  ;
     m_l3_uc_ipv6_table_info_u.m_l3_uc_ipv6_table_info_s.dip0_7_4          = get_data8(l3_uc_ipv6_key->dip[0], 4, 4)  ;
     m_l3_uc_ipv6_table_info_u.m_l3_uc_ipv6_table_info_s.dip1_3_0          = get_data8(l3_uc_ipv6_key->dip[1], 0, 4)  ;
     m_l3_uc_ipv6_table_info_u.m_l3_uc_ipv6_table_info_s.dip1_7_4          = get_data8(l3_uc_ipv6_key->dip[1], 4, 4)  ;
     m_l3_uc_ipv6_table_info_u.m_l3_uc_ipv6_table_info_s.dip2_3_0          = get_data8(l3_uc_ipv6_key->dip[2], 0, 4)  ;
     m_l3_uc_ipv6_table_info_u.m_l3_uc_ipv6_table_info_s.dip2_7_4          = get_data8(l3_uc_ipv6_key->dip[2], 4, 4)  ;
     m_l3_uc_ipv6_table_info_u.m_l3_uc_ipv6_table_info_s.dip3_3_0          = get_data8(l3_uc_ipv6_key->dip[3], 0, 4)  ;
     m_l3_uc_ipv6_table_info_u.m_l3_uc_ipv6_table_info_s.dip3_7_4          = get_data8(l3_uc_ipv6_key->dip[3], 4, 4)  ;
     m_l3_uc_ipv6_table_info_u.m_l3_uc_ipv6_table_info_s.dip4_3_0          = get_data8(l3_uc_ipv6_key->dip[4], 0, 4)  ;
     m_l3_uc_ipv6_table_info_u.m_l3_uc_ipv6_table_info_s.dip4_7_4          = get_data8(l3_uc_ipv6_key->dip[4], 4, 4)  ;
     m_l3_uc_ipv6_table_info_u.m_l3_uc_ipv6_table_info_s.dip5_3_0          = get_data8(l3_uc_ipv6_key->dip[5], 0, 4)  ;
     m_l3_uc_ipv6_table_info_u.m_l3_uc_ipv6_table_info_s.dip5_7_4          = get_data8(l3_uc_ipv6_key->dip[5], 4, 4)  ;
     m_l3_uc_ipv6_table_info_u.m_l3_uc_ipv6_table_info_s.dip6_3_0          = get_data8(l3_uc_ipv6_key->dip[6], 0, 4)  ;
     m_l3_uc_ipv6_table_info_u.m_l3_uc_ipv6_table_info_s.dip6_7_4          = get_data8(l3_uc_ipv6_key->dip[6], 4, 4)  ;
     m_l3_uc_ipv6_table_info_u.m_l3_uc_ipv6_table_info_s.dip7_3_0          = get_data8(l3_uc_ipv6_key->dip[7], 0, 4)  ;
     m_l3_uc_ipv6_table_info_u.m_l3_uc_ipv6_table_info_s.dip7_7_4          = get_data8(l3_uc_ipv6_key->dip[7], 4, 4)  ;
     m_l3_uc_ipv6_table_info_u.m_l3_uc_ipv6_table_info_s.dip8_3_0          = get_data8(l3_uc_ipv6_key->dip[8],  0, 4) ;
     m_l3_uc_ipv6_table_info_u.m_l3_uc_ipv6_table_info_s.dip8_7_4          = get_data8(l3_uc_ipv6_key->dip[8],  4, 4) ;
     m_l3_uc_ipv6_table_info_u.m_l3_uc_ipv6_table_info_s.dip9_3_0          = get_data8(l3_uc_ipv6_key->dip[9],  0, 4) ;
     m_l3_uc_ipv6_table_info_u.m_l3_uc_ipv6_table_info_s.dip9_7_4          = get_data8(l3_uc_ipv6_key->dip[9],  4, 4) ;
     m_l3_uc_ipv6_table_info_u.m_l3_uc_ipv6_table_info_s.dip10_3_0         = get_data8(l3_uc_ipv6_key->dip[10], 0, 4) ;
     m_l3_uc_ipv6_table_info_u.m_l3_uc_ipv6_table_info_s.dip10_7_4         = get_data8(l3_uc_ipv6_key->dip[10], 4, 4) ;
     m_l3_uc_ipv6_table_info_u.m_l3_uc_ipv6_table_info_s.dip11_3_0         = get_data8(l3_uc_ipv6_key->dip[11], 0, 4) ;
     m_l3_uc_ipv6_table_info_u.m_l3_uc_ipv6_table_info_s.dip11_7_4         = get_data8(l3_uc_ipv6_key->dip[11], 4, 4) ;
     m_l3_uc_ipv6_table_info_u.m_l3_uc_ipv6_table_info_s.dip12_3_0         = get_data8(l3_uc_ipv6_key->dip[12], 0, 4) ;
     m_l3_uc_ipv6_table_info_u.m_l3_uc_ipv6_table_info_s.dip12_7_4         = get_data8(l3_uc_ipv6_key->dip[12], 4, 4) ;
     m_l3_uc_ipv6_table_info_u.m_l3_uc_ipv6_table_info_s.dip13_3_0         = get_data8(l3_uc_ipv6_key->dip[13], 0, 4) ;
     m_l3_uc_ipv6_table_info_u.m_l3_uc_ipv6_table_info_s.dip13_7_4         = get_data8(l3_uc_ipv6_key->dip[13], 4, 4) ;
     m_l3_uc_ipv6_table_info_u.m_l3_uc_ipv6_table_info_s.dip14_3_0         = get_data8(l3_uc_ipv6_key->dip[14], 0, 4) ;
     m_l3_uc_ipv6_table_info_u.m_l3_uc_ipv6_table_info_s.dip14_7_4         = get_data8(l3_uc_ipv6_key->dip[14], 4, 4) ;
     m_l3_uc_ipv6_table_info_u.m_l3_uc_ipv6_table_info_s.dip15_3_0         = get_data8(l3_uc_ipv6_key->dip[15], 0, 4) ;
     m_l3_uc_ipv6_table_info_u.m_l3_uc_ipv6_table_info_s.dip15_7_4         = get_data8(l3_uc_ipv6_key->dip[15], 4, 4) ;
     m_l3_uc_ipv6_table_info_u.m_l3_uc_ipv6_table_info_s.ovid_3_0          = get_data16(l3_uc_ipv6_key->ovid , 0, 4)  ;
     m_l3_uc_ipv6_table_info_u.m_l3_uc_ipv6_table_info_s.ovid_11_4         = get_data16(l3_uc_ipv6_key->ovid , 4, 8)  ;

     m_l3_uc_ipv6_table_mask_info_u.m_l3_uc_ipv6_table_info_s.dip0_3_0          = 0x0  ;
     m_l3_uc_ipv6_table_mask_info_u.m_l3_uc_ipv6_table_info_s.dip0_7_4          = 0x0  ;
     m_l3_uc_ipv6_table_mask_info_u.m_l3_uc_ipv6_table_info_s.dip1_3_0          = 0x0  ;
     m_l3_uc_ipv6_table_mask_info_u.m_l3_uc_ipv6_table_info_s.dip1_7_4          = 0x0  ;
     m_l3_uc_ipv6_table_mask_info_u.m_l3_uc_ipv6_table_info_s.dip2_3_0          = 0x0  ;
     m_l3_uc_ipv6_table_mask_info_u.m_l3_uc_ipv6_table_info_s.dip2_7_4          = 0x0  ;
     m_l3_uc_ipv6_table_mask_info_u.m_l3_uc_ipv6_table_info_s.dip3_3_0          = 0x0  ;
     m_l3_uc_ipv6_table_mask_info_u.m_l3_uc_ipv6_table_info_s.dip3_7_4          = 0x0  ;
     m_l3_uc_ipv6_table_mask_info_u.m_l3_uc_ipv6_table_info_s.dip4_3_0          = 0x0  ;
     m_l3_uc_ipv6_table_mask_info_u.m_l3_uc_ipv6_table_info_s.dip4_7_4          = 0x0  ;
     m_l3_uc_ipv6_table_mask_info_u.m_l3_uc_ipv6_table_info_s.dip5_3_0          = 0x0  ;
     m_l3_uc_ipv6_table_mask_info_u.m_l3_uc_ipv6_table_info_s.dip5_7_4          = 0x0  ;
     m_l3_uc_ipv6_table_mask_info_u.m_l3_uc_ipv6_table_info_s.dip6_3_0          = 0x0  ;
     m_l3_uc_ipv6_table_mask_info_u.m_l3_uc_ipv6_table_info_s.dip6_7_4          = 0x0  ;
     m_l3_uc_ipv6_table_mask_info_u.m_l3_uc_ipv6_table_info_s.dip7_3_0          = 0x0  ;
     m_l3_uc_ipv6_table_mask_info_u.m_l3_uc_ipv6_table_info_s.dip7_7_4          = 0x0  ;
     m_l3_uc_ipv6_table_mask_info_u.m_l3_uc_ipv6_table_info_s.dip8_3_0          = 0x0  ;
     m_l3_uc_ipv6_table_mask_info_u.m_l3_uc_ipv6_table_info_s.dip8_7_4          = 0x0  ;
     m_l3_uc_ipv6_table_mask_info_u.m_l3_uc_ipv6_table_info_s.dip9_3_0          = 0x0  ;
     m_l3_uc_ipv6_table_mask_info_u.m_l3_uc_ipv6_table_info_s.dip9_7_4          = 0x0  ;
     m_l3_uc_ipv6_table_mask_info_u.m_l3_uc_ipv6_table_info_s.dip10_3_0         = 0x0  ;
     m_l3_uc_ipv6_table_mask_info_u.m_l3_uc_ipv6_table_info_s.dip10_7_4         = 0x0  ;
     m_l3_uc_ipv6_table_mask_info_u.m_l3_uc_ipv6_table_info_s.dip11_3_0         = 0x0  ;
     m_l3_uc_ipv6_table_mask_info_u.m_l3_uc_ipv6_table_info_s.dip11_7_4         = 0x0  ;
     m_l3_uc_ipv6_table_mask_info_u.m_l3_uc_ipv6_table_info_s.dip12_3_0         = 0x0  ;
     m_l3_uc_ipv6_table_mask_info_u.m_l3_uc_ipv6_table_info_s.dip12_7_4         = 0x0  ;
     m_l3_uc_ipv6_table_mask_info_u.m_l3_uc_ipv6_table_info_s.dip13_3_0         = 0x0  ;
     m_l3_uc_ipv6_table_mask_info_u.m_l3_uc_ipv6_table_info_s.dip13_7_4         = 0x0  ;
     m_l3_uc_ipv6_table_mask_info_u.m_l3_uc_ipv6_table_info_s.dip14_3_0         = 0x0  ;
     m_l3_uc_ipv6_table_mask_info_u.m_l3_uc_ipv6_table_info_s.dip14_7_4         = 0x0  ;
     m_l3_uc_ipv6_table_mask_info_u.m_l3_uc_ipv6_table_info_s.dip15_3_0         = 0x0  ;
     m_l3_uc_ipv6_table_mask_info_u.m_l3_uc_ipv6_table_info_s.dip15_7_4         = 0x0  ;
     m_l3_uc_ipv6_table_mask_info_u.m_l3_uc_ipv6_table_info_s.ovid_3_0          = 0x0  ;
     m_l3_uc_ipv6_table_mask_info_u.m_l3_uc_ipv6_table_info_s.ovid_11_4         = 0x0  ;

     get_blk_index(l3_uc_ipv6_key->table_id, l3_uc_ipv6_key->key_mode, L3P0_TCAM_BLK, &blk_tables[0], &m_key_loc_info);
     #if SE_DEBUG_INFO
     printf("m_key_loc_info.blk_id      = %0d\n", m_key_loc_info.blk_id     );
     printf("m_key_loc_info.item_index  = %0d\n", m_key_loc_info.item_index );
     printf("m_key_loc_info.slice_index = %0d\n", m_key_loc_info.slice_index);
     #endif

     if(l3_uc_ipv6_key->key_mode == 2) {
         unsigned int req_id    = 0x0;
         unsigned int req_index = 0x0;

         req_id    = TCAM_BLK_RAM_ID(m_key_loc_info.blk_id, m_key_loc_info.slice_index);
         req_index = 2*m_key_loc_info.item_index;
         #if SE_DEBUG_INFO
         printf("req_id      = %0d\n",  req_id   );
         printf("req_index   = %0d\n",  req_index);
         #endif

         SE_WR_REG(SE_TCAM_TB_WRDATA00_RGT_REG_ADDR, m_l3_uc_ipv6_table_info_u.data[0]);
         SE_WR_REG(SE_TCAM_TB_WRDATA01_RGT_REG_ADDR, m_l3_uc_ipv6_table_info_u.data[1]);
         SE_WR_REG(SE_TCAM_TB_WRDATA02_RGT_REG_ADDR, m_l3_uc_ipv6_table_info_u.data[2]);
         SE_WR_REG(SE_TCAM_TB_OP_ADDR_RGT_REG_ADDR, (WRITE_TABLE<<TCAM_TB_OP_ADDR_RGT_HOST_MGT_REQ_OPCODE_FIELD_OFFSET)+
                                                    (req_id<<TCAM_TB_OP_ADDR_RGT_HOST_MGT_REQ_ID_FIELD_OFFSET)+
                                                    (req_index<<TCAM_TB_OP_ADDR_RGT_HOST_MGT_REQ_ADDR_FIELD_OFFSET)
                      );

         req_id    = TCAM_BLK_RAM_ID(m_key_loc_info.blk_id, m_key_loc_info.slice_index+1);
         req_index = 2*m_key_loc_info.item_index;
         SE_WR_REG(SE_TCAM_TB_WRDATA00_RGT_REG_ADDR, (GET_DATA_FIELD(m_l3_uc_ipv6_table_info_u.data[3], 0, 8)<<24)+GET_DATA_FIELD(m_l3_uc_ipv6_table_info_u.data[2], 8, 24));
         SE_WR_REG(SE_TCAM_TB_WRDATA01_RGT_REG_ADDR, (GET_DATA_FIELD(m_l3_uc_ipv6_table_info_u.data[4], 0, 8)<<24)+GET_DATA_FIELD(m_l3_uc_ipv6_table_info_u.data[3], 8, 24));
         SE_WR_REG(SE_TCAM_TB_WRDATA02_RGT_REG_ADDR, GET_DATA_FIELD(m_l3_uc_ipv6_table_info_u.data[4], 8, 8));
         SE_WR_REG(SE_TCAM_TB_OP_ADDR_RGT_REG_ADDR, (WRITE_TABLE<<TCAM_TB_OP_ADDR_RGT_HOST_MGT_REQ_OPCODE_FIELD_OFFSET)+
                                                    (req_id<<TCAM_TB_OP_ADDR_RGT_HOST_MGT_REQ_ID_FIELD_OFFSET)+
                                                    (req_index<<TCAM_TB_OP_ADDR_RGT_HOST_MGT_REQ_ADDR_FIELD_OFFSET)
                      );

         req_id    = TCAM_BLK_RAM_ID(m_key_loc_info.blk_id, m_key_loc_info.slice_index+2);
         req_index = 2*m_key_loc_info.item_index;
         SE_WR_REG(SE_TCAM_TB_WRDATA00_RGT_REG_ADDR, (GET_DATA_FIELD(m_l3_uc_ipv6_table_info_u.data[5], 0, 16)<<16)+GET_DATA_FIELD(m_l3_uc_ipv6_table_info_u.data[4], 16, 16));
         SE_WR_REG(SE_TCAM_TB_WRDATA01_RGT_REG_ADDR, (GET_DATA_FIELD(m_l3_uc_ipv6_table_info_u.data[6], 0, 16)<<16)+GET_DATA_FIELD(m_l3_uc_ipv6_table_info_u.data[5], 16, 16));
         SE_WR_REG(SE_TCAM_TB_WRDATA02_RGT_REG_ADDR, GET_DATA_FIELD(m_l3_uc_ipv6_table_info_u.data[6], 16, 8));
         SE_WR_REG(SE_TCAM_TB_OP_ADDR_RGT_REG_ADDR, (WRITE_TABLE<<TCAM_TB_OP_ADDR_RGT_HOST_MGT_REQ_OPCODE_FIELD_OFFSET)+
                                                    (req_id<<TCAM_TB_OP_ADDR_RGT_HOST_MGT_REQ_ID_FIELD_OFFSET)+
                                                    (req_index<<TCAM_TB_OP_ADDR_RGT_HOST_MGT_REQ_ADDR_FIELD_OFFSET)
                      );

         req_id    = TCAM_BLK_RAM_ID(m_key_loc_info.blk_id, m_key_loc_info.slice_index+3);
         req_index = 2*m_key_loc_info.item_index;
         SE_WR_REG(SE_TCAM_TB_WRDATA00_RGT_REG_ADDR, (GET_DATA_FIELD(m_l3_uc_ipv6_table_info_u.data[7], 0, 24)<<8)+GET_DATA_FIELD(m_l3_uc_ipv6_table_info_u.data[6], 24, 8));
         SE_WR_REG(SE_TCAM_TB_WRDATA01_RGT_REG_ADDR, (GET_DATA_FIELD(m_l3_uc_ipv6_table_info_u.data[8], 0, 24)<<8)+GET_DATA_FIELD(m_l3_uc_ipv6_table_info_u.data[7], 24, 8));
         SE_WR_REG(SE_TCAM_TB_WRDATA02_RGT_REG_ADDR, GET_DATA_FIELD(m_l3_uc_ipv6_table_info_u.data[8], 24, 8));
         SE_WR_REG(SE_TCAM_TB_OP_ADDR_RGT_REG_ADDR, (WRITE_TABLE<<TCAM_TB_OP_ADDR_RGT_HOST_MGT_REQ_OPCODE_FIELD_OFFSET)+
                                                    (req_id<<TCAM_TB_OP_ADDR_RGT_HOST_MGT_REQ_ID_FIELD_OFFSET)+
                                                    (req_index<<TCAM_TB_OP_ADDR_RGT_HOST_MGT_REQ_ADDR_FIELD_OFFSET)
                      );

         req_id    = TCAM_BLK_RAM_ID(m_key_loc_info.blk_id, m_key_loc_info.slice_index);
         req_index = 2*m_key_loc_info.item_index+1;
         SE_WR_REG(SE_TCAM_TB_WRDATA00_RGT_REG_ADDR, m_l3_uc_ipv6_table_mask_info_u.data[0]);
         SE_WR_REG(SE_TCAM_TB_WRDATA01_RGT_REG_ADDR, m_l3_uc_ipv6_table_mask_info_u.data[1]);
         SE_WR_REG(SE_TCAM_TB_WRDATA02_RGT_REG_ADDR, m_l3_uc_ipv6_table_mask_info_u.data[2]);
         SE_WR_REG(SE_TCAM_TB_OP_ADDR_RGT_REG_ADDR, (WRITE_TABLE<<TCAM_TB_OP_ADDR_RGT_HOST_MGT_REQ_OPCODE_FIELD_OFFSET)+
                                                    (req_id<<TCAM_TB_OP_ADDR_RGT_HOST_MGT_REQ_ID_FIELD_OFFSET)+
                                                    (req_index<<TCAM_TB_OP_ADDR_RGT_HOST_MGT_REQ_ADDR_FIELD_OFFSET)
                      );

         req_id    = TCAM_BLK_RAM_ID(m_key_loc_info.blk_id, m_key_loc_info.slice_index+1);
         req_index = 2*m_key_loc_info.item_index+1;
         SE_WR_REG(SE_TCAM_TB_WRDATA00_RGT_REG_ADDR, (GET_DATA_FIELD(m_l3_uc_ipv6_table_mask_info_u.data[3], 0, 8)<<24)+GET_DATA_FIELD(m_l3_uc_ipv6_table_mask_info_u.data[2], 8, 24));
         SE_WR_REG(SE_TCAM_TB_WRDATA01_RGT_REG_ADDR, (GET_DATA_FIELD(m_l3_uc_ipv6_table_mask_info_u.data[4], 0, 8)<<24)+GET_DATA_FIELD(m_l3_uc_ipv6_table_mask_info_u.data[3], 8, 24));
         SE_WR_REG(SE_TCAM_TB_WRDATA02_RGT_REG_ADDR, GET_DATA_FIELD(m_l3_uc_ipv6_table_mask_info_u.data[4], 8, 8));
         SE_WR_REG(SE_TCAM_TB_OP_ADDR_RGT_REG_ADDR, (WRITE_TABLE<<TCAM_TB_OP_ADDR_RGT_HOST_MGT_REQ_OPCODE_FIELD_OFFSET)+
                                                    (req_id<<TCAM_TB_OP_ADDR_RGT_HOST_MGT_REQ_ID_FIELD_OFFSET)+
                                                    (req_index<<TCAM_TB_OP_ADDR_RGT_HOST_MGT_REQ_ADDR_FIELD_OFFSET)
                      );

         req_id    = TCAM_BLK_RAM_ID(m_key_loc_info.blk_id, m_key_loc_info.slice_index+2);
         req_index = 2*m_key_loc_info.item_index+1;
         SE_WR_REG(SE_TCAM_TB_WRDATA00_RGT_REG_ADDR, (GET_DATA_FIELD(m_l3_uc_ipv6_table_mask_info_u.data[5], 0, 16)<<16)+GET_DATA_FIELD(m_l3_uc_ipv6_table_mask_info_u.data[4], 16, 16));
         SE_WR_REG(SE_TCAM_TB_WRDATA01_RGT_REG_ADDR, (GET_DATA_FIELD(m_l3_uc_ipv6_table_mask_info_u.data[6], 0, 16)<<16)+GET_DATA_FIELD(m_l3_uc_ipv6_table_mask_info_u.data[5], 16, 16));
         SE_WR_REG(SE_TCAM_TB_WRDATA02_RGT_REG_ADDR, GET_DATA_FIELD(m_l3_uc_ipv6_table_mask_info_u.data[6], 16, 8));
         SE_WR_REG(SE_TCAM_TB_OP_ADDR_RGT_REG_ADDR, (WRITE_TABLE<<TCAM_TB_OP_ADDR_RGT_HOST_MGT_REQ_OPCODE_FIELD_OFFSET)+
                                                    (req_id<<TCAM_TB_OP_ADDR_RGT_HOST_MGT_REQ_ID_FIELD_OFFSET)+
                                                    (req_index<<TCAM_TB_OP_ADDR_RGT_HOST_MGT_REQ_ADDR_FIELD_OFFSET)
                      );

         req_id    = TCAM_BLK_RAM_ID(m_key_loc_info.blk_id, m_key_loc_info.slice_index+3);
         req_index = 2*m_key_loc_info.item_index+1;
         SE_WR_REG(SE_TCAM_TB_WRDATA00_RGT_REG_ADDR, (GET_DATA_FIELD(m_l3_uc_ipv6_table_mask_info_u.data[7], 0, 24)<<8)+GET_DATA_FIELD(m_l3_uc_ipv6_table_mask_info_u.data[6], 24, 8));
         SE_WR_REG(SE_TCAM_TB_WRDATA01_RGT_REG_ADDR, (GET_DATA_FIELD(m_l3_uc_ipv6_table_mask_info_u.data[8], 0, 24)<<8)+GET_DATA_FIELD(m_l3_uc_ipv6_table_mask_info_u.data[7], 24, 8));
         SE_WR_REG(SE_TCAM_TB_WRDATA02_RGT_REG_ADDR, GET_DATA_FIELD(m_l3_uc_ipv6_table_mask_info_u.data[8], 24, 8));
         SE_WR_REG(SE_TCAM_TB_OP_ADDR_RGT_REG_ADDR, (WRITE_TABLE<<TCAM_TB_OP_ADDR_RGT_HOST_MGT_REQ_OPCODE_FIELD_OFFSET)+
                                                    (req_id<<TCAM_TB_OP_ADDR_RGT_HOST_MGT_REQ_ID_FIELD_OFFSET)+
                                                    (req_index<<TCAM_TB_OP_ADDR_RGT_HOST_MGT_REQ_ADDR_FIELD_OFFSET)
                      );


         req_id    = TCAM_BLK_MODE_ID(m_key_loc_info.blk_id);
         req_index = m_key_loc_info.item_index;
         SE_WR_REG(SE_TCAM_TB_WRDATA00_RGT_REG_ADDR, (l3_uc_ipv6_key->key_mode<<2)+l3_uc_ipv6_key->table_id);
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

//MPP: L3P0, Table: l3mcsg
void cfg_l3_mcsg_ipv4_table_item(L3McsgIpv4Key_S* l3_mcsg_ipv4_key, L3McsgRsp_S* l3_mcsg_rsp, L3Cfg_S* L3_cfg) {

     int i = 0;
     KeyLocInfo_S m_key_loc_info;

     L3McsgIpv4TableInfo_U m_l3_mcsg_ipv4_table_info_u;
     L3McsgIpv4TableInfo_U m_l3_mcsg_ipv4_table_mask_info_u;

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
         m_l3_mcsg_ipv4_table_info_u.data[i] = 0x0;
         m_l3_mcsg_ipv4_table_mask_info_u.data[i] = 0xFFFFFFFF;
     }
     m_l3_mcsg_ipv4_table_info_u.m_l3_mcsg_ipv4_table_info_s.intf_id             = l3_mcsg_rsp->intf_id            ;
     m_l3_mcsg_ipv4_table_info_u.m_l3_mcsg_ipv4_table_info_s.oport_bitmap_1_0    = get_data64(l3_mcsg_rsp->oport_bitmap, 0, 2) ;
     m_l3_mcsg_ipv4_table_info_u.m_l3_mcsg_ipv4_table_info_s.oport_bitmap_9_2    = get_data64(l3_mcsg_rsp->oport_bitmap, 2, 8) ;
     m_l3_mcsg_ipv4_table_info_u.m_l3_mcsg_ipv4_table_info_s.oport_bitmap_17_10  = get_data64(l3_mcsg_rsp->oport_bitmap,10, 8) ;
     m_l3_mcsg_ipv4_table_info_u.m_l3_mcsg_ipv4_table_info_s.oport_bitmap_25_18  = get_data64(l3_mcsg_rsp->oport_bitmap,18, 8) ;
     m_l3_mcsg_ipv4_table_info_u.m_l3_mcsg_ipv4_table_info_s.oport_bitmap_33_26  = get_data64(l3_mcsg_rsp->oport_bitmap,26, 8) ;
     m_l3_mcsg_ipv4_table_info_u.m_l3_mcsg_ipv4_table_info_s.oport_bitmap_35_34  = get_data64(l3_mcsg_rsp->oport_bitmap,34, 2) ;
     m_l3_mcsg_ipv4_table_info_u.m_l3_mcsg_ipv4_table_info_s.iport_id            = l3_mcsg_rsp->iport_id           ;
     m_l3_mcsg_ipv4_table_info_u.m_l3_mcsg_ipv4_table_info_s.dip0_3_0            = get_data8(l3_mcsg_ipv4_key->dip[0], 0, 4)          ;
     m_l3_mcsg_ipv4_table_info_u.m_l3_mcsg_ipv4_table_info_s.dip0_7_4            = get_data8(l3_mcsg_ipv4_key->dip[0], 4, 4)          ;
     m_l3_mcsg_ipv4_table_info_u.m_l3_mcsg_ipv4_table_info_s.dip1_3_0            = get_data8(l3_mcsg_ipv4_key->dip[1], 0, 4)          ;
     m_l3_mcsg_ipv4_table_info_u.m_l3_mcsg_ipv4_table_info_s.dip1_7_4            = get_data8(l3_mcsg_ipv4_key->dip[1], 4, 4)          ;
     m_l3_mcsg_ipv4_table_info_u.m_l3_mcsg_ipv4_table_info_s.dip2_3_0            = get_data8(l3_mcsg_ipv4_key->dip[2], 0, 4)          ;
     m_l3_mcsg_ipv4_table_info_u.m_l3_mcsg_ipv4_table_info_s.dip2_7_4            = get_data8(l3_mcsg_ipv4_key->dip[2], 4, 4)          ;
     m_l3_mcsg_ipv4_table_info_u.m_l3_mcsg_ipv4_table_info_s.dip3_3_0            = get_data8(l3_mcsg_ipv4_key->dip[3], 0, 4)          ;
     m_l3_mcsg_ipv4_table_info_u.m_l3_mcsg_ipv4_table_info_s.dip3_7_4            = get_data8(l3_mcsg_ipv4_key->dip[3], 4, 4)          ;
     m_l3_mcsg_ipv4_table_info_u.m_l3_mcsg_ipv4_table_info_s.sip0_3_0            = get_data8(l3_mcsg_ipv4_key->sip[0], 0, 4)          ;
     m_l3_mcsg_ipv4_table_info_u.m_l3_mcsg_ipv4_table_info_s.sip0_7_4            = get_data8(l3_mcsg_ipv4_key->sip[0], 4, 4)          ;
     m_l3_mcsg_ipv4_table_info_u.m_l3_mcsg_ipv4_table_info_s.sip1_3_0            = get_data8(l3_mcsg_ipv4_key->sip[1], 0, 4)          ;
     m_l3_mcsg_ipv4_table_info_u.m_l3_mcsg_ipv4_table_info_s.sip1_7_4            = get_data8(l3_mcsg_ipv4_key->sip[1], 4, 4)          ;
     m_l3_mcsg_ipv4_table_info_u.m_l3_mcsg_ipv4_table_info_s.sip2_3_0            = get_data8(l3_mcsg_ipv4_key->sip[2], 0, 4)          ;
     m_l3_mcsg_ipv4_table_info_u.m_l3_mcsg_ipv4_table_info_s.sip2_7_4            = get_data8(l3_mcsg_ipv4_key->sip[2], 4, 4)          ;
     m_l3_mcsg_ipv4_table_info_u.m_l3_mcsg_ipv4_table_info_s.sip3_3_0            = get_data8(l3_mcsg_ipv4_key->sip[3], 0, 4)          ;
     m_l3_mcsg_ipv4_table_info_u.m_l3_mcsg_ipv4_table_info_s.sip3_7_4            = get_data8(l3_mcsg_ipv4_key->sip[3], 4, 4)          ;
     m_l3_mcsg_ipv4_table_info_u.m_l3_mcsg_ipv4_table_info_s.ovid_3_0            = get_data16(l3_mcsg_ipv4_key->ovid , 0, 4)          ;
     m_l3_mcsg_ipv4_table_info_u.m_l3_mcsg_ipv4_table_info_s.ovid_11_4           = get_data16(l3_mcsg_ipv4_key->ovid , 4, 8)          ;

     m_l3_mcsg_ipv4_table_mask_info_u.m_l3_mcsg_ipv4_table_info_s.sip0_3_0          = 0x0  ;
     m_l3_mcsg_ipv4_table_mask_info_u.m_l3_mcsg_ipv4_table_info_s.sip0_7_4          = 0x0  ;
     m_l3_mcsg_ipv4_table_mask_info_u.m_l3_mcsg_ipv4_table_info_s.sip1_3_0          = 0x0  ;
     m_l3_mcsg_ipv4_table_mask_info_u.m_l3_mcsg_ipv4_table_info_s.sip1_7_4          = 0x0  ;
     m_l3_mcsg_ipv4_table_mask_info_u.m_l3_mcsg_ipv4_table_info_s.sip2_3_0          = 0x0  ;
     m_l3_mcsg_ipv4_table_mask_info_u.m_l3_mcsg_ipv4_table_info_s.sip2_7_4          = 0x0  ;
     m_l3_mcsg_ipv4_table_mask_info_u.m_l3_mcsg_ipv4_table_info_s.sip3_3_0          = 0x0  ;
     m_l3_mcsg_ipv4_table_mask_info_u.m_l3_mcsg_ipv4_table_info_s.sip3_7_4          = 0x0  ;
     m_l3_mcsg_ipv4_table_mask_info_u.m_l3_mcsg_ipv4_table_info_s.dip0_3_0          = 0x0  ;
     m_l3_mcsg_ipv4_table_mask_info_u.m_l3_mcsg_ipv4_table_info_s.dip0_7_4          = 0x0  ;
     m_l3_mcsg_ipv4_table_mask_info_u.m_l3_mcsg_ipv4_table_info_s.dip1_3_0          = 0x0  ;
     m_l3_mcsg_ipv4_table_mask_info_u.m_l3_mcsg_ipv4_table_info_s.dip1_7_4          = 0x0  ;
     m_l3_mcsg_ipv4_table_mask_info_u.m_l3_mcsg_ipv4_table_info_s.dip2_3_0          = 0x0  ;
     m_l3_mcsg_ipv4_table_mask_info_u.m_l3_mcsg_ipv4_table_info_s.dip2_7_4          = 0x0  ;
     m_l3_mcsg_ipv4_table_mask_info_u.m_l3_mcsg_ipv4_table_info_s.dip3_3_0          = 0x0  ;
     m_l3_mcsg_ipv4_table_mask_info_u.m_l3_mcsg_ipv4_table_info_s.dip3_7_4          = 0x0  ;
     m_l3_mcsg_ipv4_table_mask_info_u.m_l3_mcsg_ipv4_table_info_s.ovid_3_0          = 0x0  ;
     m_l3_mcsg_ipv4_table_mask_info_u.m_l3_mcsg_ipv4_table_info_s.ovid_11_4         = 0x0  ;

     get_blk_index(l3_mcsg_ipv4_key->table_id, l3_mcsg_ipv4_key->key_mode, L3P0_TCAM_BLK, &blk_tables[0], &m_key_loc_info);
     #if SE_DEBUG_INFO
     printf("m_key_loc_info.blk_id      = %0d\n", m_key_loc_info.blk_id     );
     printf("m_key_loc_info.item_index  = %0d\n", m_key_loc_info.item_index );
     printf("m_key_loc_info.slice_index = %0d\n", m_key_loc_info.slice_index);
     #endif

     if(l3_mcsg_ipv4_key->key_mode == 1) {
         unsigned int req_id    = 0x0;
         unsigned int req_index = 0x0;

         req_id    = TCAM_BLK_RAM_ID(m_key_loc_info.blk_id, m_key_loc_info.slice_index);
         req_index = 2*m_key_loc_info.item_index;
         #if SE_DEBUG_INFO
         printf("req_id      = %0d\n",  req_id   );
         printf("req_index   = %0d\n",  req_index);
         #endif
         SE_WR_REG(SE_TCAM_TB_WRDATA00_RGT_REG_ADDR, m_l3_mcsg_ipv4_table_info_u.data[0]);
         SE_WR_REG(SE_TCAM_TB_WRDATA01_RGT_REG_ADDR, m_l3_mcsg_ipv4_table_info_u.data[1]);
         SE_WR_REG(SE_TCAM_TB_WRDATA02_RGT_REG_ADDR, m_l3_mcsg_ipv4_table_info_u.data[2]);
         SE_WR_REG(SE_TCAM_TB_OP_ADDR_RGT_REG_ADDR, (WRITE_TABLE<<TCAM_TB_OP_ADDR_RGT_HOST_MGT_REQ_OPCODE_FIELD_OFFSET)+
                                                    (req_id<<TCAM_TB_OP_ADDR_RGT_HOST_MGT_REQ_ID_FIELD_OFFSET)+
                                                    (req_index<<TCAM_TB_OP_ADDR_RGT_HOST_MGT_REQ_ADDR_FIELD_OFFSET)
                      );

         req_id    = TCAM_BLK_RAM_ID(m_key_loc_info.blk_id, m_key_loc_info.slice_index+1);
         req_index = 2*m_key_loc_info.item_index;
         #if SE_DEBUG_INFO
         printf("req_id      = %0d\n",  req_id   );
         printf("req_index   = %0d\n",  req_index);
         #endif
         SE_WR_REG(SE_TCAM_TB_WRDATA00_RGT_REG_ADDR, (GET_DATA_FIELD(m_l3_mcsg_ipv4_table_info_u.data[3], 0, 8)<<24)+GET_DATA_FIELD(m_l3_mcsg_ipv4_table_info_u.data[2], 8, 24));
         SE_WR_REG(SE_TCAM_TB_WRDATA01_RGT_REG_ADDR, (GET_DATA_FIELD(m_l3_mcsg_ipv4_table_info_u.data[4], 0, 8)<<24)+GET_DATA_FIELD(m_l3_mcsg_ipv4_table_info_u.data[3], 8, 24));
         SE_WR_REG(SE_TCAM_TB_WRDATA02_RGT_REG_ADDR, GET_DATA_FIELD(m_l3_mcsg_ipv4_table_info_u.data[4], 8, 8));
         SE_WR_REG(SE_TCAM_TB_OP_ADDR_RGT_REG_ADDR, (WRITE_TABLE<<TCAM_TB_OP_ADDR_RGT_HOST_MGT_REQ_OPCODE_FIELD_OFFSET)+
                                                    (req_id<<TCAM_TB_OP_ADDR_RGT_HOST_MGT_REQ_ID_FIELD_OFFSET)+
                                                    (req_index<<TCAM_TB_OP_ADDR_RGT_HOST_MGT_REQ_ADDR_FIELD_OFFSET)
                      );

         req_id    = TCAM_BLK_RAM_ID(m_key_loc_info.blk_id, m_key_loc_info.slice_index);
         req_index = 2*m_key_loc_info.item_index+1;
         SE_WR_REG(SE_TCAM_TB_WRDATA00_RGT_REG_ADDR, m_l3_mcsg_ipv4_table_mask_info_u.data[0]);
         SE_WR_REG(SE_TCAM_TB_WRDATA01_RGT_REG_ADDR, m_l3_mcsg_ipv4_table_mask_info_u.data[1]);
         SE_WR_REG(SE_TCAM_TB_WRDATA02_RGT_REG_ADDR, m_l3_mcsg_ipv4_table_mask_info_u.data[2]);
         SE_WR_REG(SE_TCAM_TB_OP_ADDR_RGT_REG_ADDR, (WRITE_TABLE<<TCAM_TB_OP_ADDR_RGT_HOST_MGT_REQ_OPCODE_FIELD_OFFSET)+
                                                    (req_id<<TCAM_TB_OP_ADDR_RGT_HOST_MGT_REQ_ID_FIELD_OFFSET)+
                                                    (req_index<<TCAM_TB_OP_ADDR_RGT_HOST_MGT_REQ_ADDR_FIELD_OFFSET)
                      );

         req_id    = TCAM_BLK_RAM_ID(m_key_loc_info.blk_id, m_key_loc_info.slice_index+1);
         req_index = 2*m_key_loc_info.item_index+1;
         SE_WR_REG(SE_TCAM_TB_WRDATA00_RGT_REG_ADDR, (GET_DATA_FIELD(m_l3_mcsg_ipv4_table_mask_info_u.data[3], 0, 8)<<24)+GET_DATA_FIELD(m_l3_mcsg_ipv4_table_mask_info_u.data[2], 8, 24));
         SE_WR_REG(SE_TCAM_TB_WRDATA01_RGT_REG_ADDR, (GET_DATA_FIELD(m_l3_mcsg_ipv4_table_mask_info_u.data[4], 0, 8)<<24)+GET_DATA_FIELD(m_l3_mcsg_ipv4_table_mask_info_u.data[3], 8, 24));
         SE_WR_REG(SE_TCAM_TB_WRDATA02_RGT_REG_ADDR, GET_DATA_FIELD(m_l3_mcsg_ipv4_table_mask_info_u.data[4], 8, 8));
         SE_WR_REG(SE_TCAM_TB_OP_ADDR_RGT_REG_ADDR, (WRITE_TABLE<<TCAM_TB_OP_ADDR_RGT_HOST_MGT_REQ_OPCODE_FIELD_OFFSET)+
                                                    (req_id<<TCAM_TB_OP_ADDR_RGT_HOST_MGT_REQ_ID_FIELD_OFFSET)+
                                                    (req_index<<TCAM_TB_OP_ADDR_RGT_HOST_MGT_REQ_ADDR_FIELD_OFFSET)
                      );

         req_id    = TCAM_BLK_MODE_ID(m_key_loc_info.blk_id);
         req_index = m_key_loc_info.item_index;
         SE_WR_REG(SE_TCAM_TB_WRDATA00_RGT_REG_ADDR, (l3_mcsg_ipv4_key->key_mode<<2)+l3_mcsg_ipv4_key->table_id);
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

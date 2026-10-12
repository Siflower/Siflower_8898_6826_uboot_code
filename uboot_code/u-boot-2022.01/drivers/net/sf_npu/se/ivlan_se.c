#ifndef IVLAN_SE_C
#define IVLAN_SE_C

#include "ivlan_se.h"
#include "tcam_se.h"
#include "se_common.h"
#include <string.h>

//MPP: ivlan_port, Table: iport
void cfg_ivlan_iport_table_item(IvlanIportKey_S* ivlan_iport_key, IvlanIportRsp_S* ivlan_iport_rsp, IvlanCfg_S* ivlan_cfg) {

     IvlanIportTableInfo_U m_ivlan_iport_table_info_u;

     m_ivlan_iport_table_info_u.data = 0x0;

     m_ivlan_iport_table_info_u.m_ivlan_iport_table_info_s.pass_mode            = ivlan_iport_rsp->pass_mode           ;
     m_ivlan_iport_table_info_u.m_ivlan_iport_table_info_s.vid_zero_handle      = ivlan_iport_rsp->vid_zero_handle     ;
     m_ivlan_iport_table_info_u.m_ivlan_iport_table_info_s.vlan_security_mode   = ivlan_iport_rsp->vlan_security_mode  ;
     m_ivlan_iport_table_info_u.m_ivlan_iport_table_info_s.vfp_based_vid_enable = ivlan_iport_rsp->vfp_based_vid_enable;
     m_ivlan_iport_table_info_u.m_ivlan_iport_table_info_s.vt_en                = ivlan_iport_rsp->vt_en               ;
     m_ivlan_iport_table_info_u.m_ivlan_iport_table_info_s.vt_miss_drop         = ivlan_iport_rsp->vt_miss_drop        ;
     m_ivlan_iport_table_info_u.m_ivlan_iport_table_info_s.use_ivid_as_ovid     = ivlan_iport_rsp->use_ivid_as_ovid    ;
     m_ivlan_iport_table_info_u.m_ivlan_iport_table_info_s.ifiliter_en_0        = get_data16(ivlan_iport_rsp->ifiliter_en, 0, 1);
     m_ivlan_iport_table_info_u.m_ivlan_iport_table_info_s.ifiliter_en_1        = get_data16(ivlan_iport_rsp->ifiliter_en, 1, 1);
     m_ivlan_iport_table_info_u.m_ivlan_iport_table_info_s.disable_vlan_check   = ivlan_iport_rsp->disable_vlan_check  ;
     m_ivlan_iport_table_info_u.m_ivlan_iport_table_info_s.default_port         = ivlan_iport_rsp->default_port        ;
     m_ivlan_iport_table_info_u.m_ivlan_iport_table_info_s.iso_id               = ivlan_iport_rsp->iso_id              ;
     m_ivlan_iport_table_info_u.m_ivlan_iport_table_info_s.valid                = ivlan_iport_rsp->valid               ;

     SE_WR_REG(SE_TB_WRDATA00_RGT_REG_ADDR, m_ivlan_iport_table_info_u.data);
     SE_WR_REG(SE_TB_OP_ADDR_RGT_REG_ADDR, (WRITE_TABLE<<TB_OP_ADDR_RGT_HOST_MGT_REQ_OPCODE_FIELD_OFFSET)+
                                           (IVLAN_PORT_SE_IVLAN_IPORT_TABLE<<TB_OP_ADDR_RGT_HOST_MGT_REQ_ID_FIELD_OFFSET)+
                                           (ivlan_iport_key->iport_num<<TB_OP_ADDR_RGT_HOST_MGT_REQ_ADDR_FIELD_OFFSET)
                  );

     //enable ivlan_iport_table
     update_reg(SE_CONFIG0_RGT_REG_ADDR, CONFIG0_RGT_IPORT_TABLE_VLD_FIELD_OFFSET, CONFIG0_RGT_IPORT_TABLE_VLD_FIELD_SIZE, 1);
}

//MPP: ivlan_vid, Table: pbv
void cfg_ivlan_pbv_table_item(IvlanPbvKey_S* ivlan_pbv_key, IvlanPbvRsp_S* ivlan_pbv_rsp, IvlanCfg_S* ivlan_pbv_cfg) {

     int i = 0;

     IvlanPbvTableInfo_U m_ivlan_pbv_table_info_u;

     for(i=0; i<2; i++) {
         m_ivlan_pbv_table_info_u.data[i] = 0x0;
     }
     m_ivlan_pbv_table_info_u.m_ivlan_pbv_table_info_s.un_pitag_action  = ivlan_pbv_rsp->un_pitag_action ;
     m_ivlan_pbv_table_info_u.m_ivlan_pbv_table_info_s.un_itag_action   = ivlan_pbv_rsp->un_itag_action  ;
     m_ivlan_pbv_table_info_u.m_ivlan_pbv_table_info_s.un_potag_action  = ivlan_pbv_rsp->un_potag_action ;
     m_ivlan_pbv_table_info_u.m_ivlan_pbv_table_info_s.un_otag_action   = ivlan_pbv_rsp->un_otag_action  ;
     m_ivlan_pbv_table_info_u.m_ivlan_pbv_table_info_s.sit_pitag_action = ivlan_pbv_rsp->sit_pitag_action;
     m_ivlan_pbv_table_info_u.m_ivlan_pbv_table_info_s.sit_itag_action  = ivlan_pbv_rsp->sit_itag_action ;
     m_ivlan_pbv_table_info_u.m_ivlan_pbv_table_info_s.sit_potag_action = ivlan_pbv_rsp->sit_potag_action;
     m_ivlan_pbv_table_info_u.m_ivlan_pbv_table_info_s.sit_otag_action  = ivlan_pbv_rsp->sit_otag_action ;
     m_ivlan_pbv_table_info_u.m_ivlan_pbv_table_info_s.sot_pitag_action = ivlan_pbv_rsp->sot_pitag_action;
     m_ivlan_pbv_table_info_u.m_ivlan_pbv_table_info_s.sot_itag_action  = ivlan_pbv_rsp->sot_itag_action ;
     m_ivlan_pbv_table_info_u.m_ivlan_pbv_table_info_s.sot_potag_action = ivlan_pbv_rsp->sot_potag_action;
     m_ivlan_pbv_table_info_u.m_ivlan_pbv_table_info_s.sot_otag_action  = ivlan_pbv_rsp->sot_otag_action ;
     m_ivlan_pbv_table_info_u.m_ivlan_pbv_table_info_s.dt_pitag_action  = ivlan_pbv_rsp->dt_pitag_action ;
     m_ivlan_pbv_table_info_u.m_ivlan_pbv_table_info_s.dt_itag_action   = ivlan_pbv_rsp->dt_itag_action  ;
     m_ivlan_pbv_table_info_u.m_ivlan_pbv_table_info_s.dt_potag_action  = ivlan_pbv_rsp->dt_potag_action ;
     m_ivlan_pbv_table_info_u.m_ivlan_pbv_table_info_s.dt_otag_action   = ivlan_pbv_rsp->dt_otag_action  ;
     m_ivlan_pbv_table_info_u.m_ivlan_pbv_table_info_s.ipri             = ivlan_pbv_rsp->ipri            ;
     m_ivlan_pbv_table_info_u.m_ivlan_pbv_table_info_s.opri             = ivlan_pbv_rsp->opri            ;
     m_ivlan_pbv_table_info_u.m_ivlan_pbv_table_info_s.ivid_1_0         = get_data16(ivlan_pbv_rsp->ivid,  0, 2);
     m_ivlan_pbv_table_info_u.m_ivlan_pbv_table_info_s.ivid_9_2         = get_data16(ivlan_pbv_rsp->ivid,  2, 8);
     m_ivlan_pbv_table_info_u.m_ivlan_pbv_table_info_s.ivid_11_10       = get_data16(ivlan_pbv_rsp->ivid, 10, 2);
     m_ivlan_pbv_table_info_u.m_ivlan_pbv_table_info_s.ovid_5_0         = get_data16(ivlan_pbv_rsp->ovid,  0, 6);
     m_ivlan_pbv_table_info_u.m_ivlan_pbv_table_info_s.ovid_11_6        = get_data16(ivlan_pbv_rsp->ovid,  6, 6);
     m_ivlan_pbv_table_info_u.m_ivlan_pbv_table_info_s.transparent_en   = ivlan_pbv_rsp->transparent_en  ;
     m_ivlan_pbv_table_info_u.m_ivlan_pbv_table_info_s.vld              = ivlan_pbv_rsp->vld                   ;

     SE_WR_REG(SE_TB_WRDATA00_RGT_REG_ADDR, m_ivlan_pbv_table_info_u.data[0]);
     SE_WR_REG(SE_TB_WRDATA01_RGT_REG_ADDR, m_ivlan_pbv_table_info_u.data[1]);
     SE_WR_REG(SE_TB_OP_ADDR_RGT_REG_ADDR, (WRITE_TABLE<<TB_OP_ADDR_RGT_HOST_MGT_REQ_OPCODE_FIELD_OFFSET)+
                                           (IVLAN_PBV_SE_DIRECT_TABLE<<TB_OP_ADDR_RGT_HOST_MGT_REQ_ID_FIELD_OFFSET)+
                                           (ivlan_pbv_key->iport_num<<TB_OP_ADDR_RGT_HOST_MGT_REQ_ADDR_FIELD_OFFSET)
                  );

     //enable ivlan_pbv_table
     update_reg(SE_CONFIG0_RGT_REG_ADDR, CONFIG0_RGT_PORTBV_TABLE_VLD_FIELD_OFFSET, CONFIG0_RGT_PORTBV_TABLE_VLD_FIELD_SIZE, 1);
}

//MPP: ivlan_lkp, Table: ivlan_lkp
static int ilvan_lkp_table_index = 0;
void cfg_ivlan_lkp_table_item(IvlanLkpKey_S* ivlan_lkp_key, IvlanLkpRsp_S* ivlan_lkp_rsp, IvlanCfg_S* ivlan_lkp_cfg) {

     int i = 0;

     IvlanLkpTableInfo_U m_ivlan_lkp_table_info_u;

     for(i=0; i<3; i++) {
         m_ivlan_lkp_table_info_u.data[i] = 0x0;
     }
     m_ivlan_lkp_table_info_u.m_ivlan_lkp_table_info_s.result_vld         = 1                                ;
     m_ivlan_lkp_table_info_u.m_ivlan_lkp_table_info_s.learn_disable      = ivlan_lkp_rsp->learn_disable     ;
     m_ivlan_lkp_table_info_u.m_ivlan_lkp_table_info_s.l2_pfm             = ivlan_lkp_rsp->l2_pfm            ;
     m_ivlan_lkp_table_info_u.m_ivlan_lkp_table_info_s.ipmcv6_en          = ivlan_lkp_rsp->ipmcv6_en         ;
     m_ivlan_lkp_table_info_u.m_ivlan_lkp_table_info_s.ipmcv4_en          = ivlan_lkp_rsp->ipmcv4_en         ;
     m_ivlan_lkp_table_info_u.m_ivlan_lkp_table_info_s.l2_miss_tocpu      = ivlan_lkp_rsp->l2_miss_tocpu     ;
     m_ivlan_lkp_table_info_u.m_ivlan_lkp_table_info_s.l2_miss_drop       = ivlan_lkp_rsp->l2_miss_drop      ;
     m_ivlan_lkp_table_info_u.m_ivlan_lkp_table_info_s.l2_non_ucast_tocpu = ivlan_lkp_rsp->l2_non_ucast_tocpu;
     m_ivlan_lkp_table_info_u.m_ivlan_lkp_table_info_s.l2_non_ucast_drop  = ivlan_lkp_rsp->l2_non_ucast_drop ;
     m_ivlan_lkp_table_info_u.m_ivlan_lkp_table_info_s.sp_tree_port9      = ivlan_lkp_rsp->sp_tree_port9     ;
     m_ivlan_lkp_table_info_u.m_ivlan_lkp_table_info_s.sp_tree_port8      = ivlan_lkp_rsp->sp_tree_port8     ;
     m_ivlan_lkp_table_info_u.m_ivlan_lkp_table_info_s.sp_tree_port7      = ivlan_lkp_rsp->sp_tree_port7     ;
     m_ivlan_lkp_table_info_u.m_ivlan_lkp_table_info_s.sp_tree_port6      = ivlan_lkp_rsp->sp_tree_port6     ;
     m_ivlan_lkp_table_info_u.m_ivlan_lkp_table_info_s.sp_tree_port5      = ivlan_lkp_rsp->sp_tree_port5     ;
     m_ivlan_lkp_table_info_u.m_ivlan_lkp_table_info_s.sp_tree_port4      = ivlan_lkp_rsp->sp_tree_port4     ;
     m_ivlan_lkp_table_info_u.m_ivlan_lkp_table_info_s.sp_tree_port3      = ivlan_lkp_rsp->sp_tree_port3     ;
     m_ivlan_lkp_table_info_u.m_ivlan_lkp_table_info_s.sp_tree_port2      = ivlan_lkp_rsp->sp_tree_port2     ;
     m_ivlan_lkp_table_info_u.m_ivlan_lkp_table_info_s.sp_tree_port1      = ivlan_lkp_rsp->sp_tree_port1     ;
     m_ivlan_lkp_table_info_u.m_ivlan_lkp_table_info_s.sp_tree_port0      = ivlan_lkp_rsp->sp_tree_port0     ;
     m_ivlan_lkp_table_info_u.m_ivlan_lkp_table_info_s.port_bitmap_1_0    = get_data64(ivlan_lkp_rsp->port_bitmap,  0,  1);
     m_ivlan_lkp_table_info_u.m_ivlan_lkp_table_info_s.port_bitmap_33_2   = get_data64(ivlan_lkp_rsp->port_bitmap,  2, 32);
     m_ivlan_lkp_table_info_u.m_ivlan_lkp_table_info_s.port_bitmap_35_34  = get_data64(ivlan_lkp_rsp->port_bitmap, 34,  2);
     m_ivlan_lkp_table_info_u.m_ivlan_lkp_table_info_s.ovid_5_0           = get_data16(ivlan_lkp_key->ovid, 0, 6);
     m_ivlan_lkp_table_info_u.m_ivlan_lkp_table_info_s.ovid_11_6          = get_data16(ivlan_lkp_key->ovid, 6, 6);

     SE_WR_REG(SE_TB_WRDATA00_RGT_REG_ADDR, m_ivlan_lkp_table_info_u.data[0]);
     SE_WR_REG(SE_TB_WRDATA01_RGT_REG_ADDR, m_ivlan_lkp_table_info_u.data[1]);
     SE_WR_REG(SE_TB_WRDATA02_RGT_REG_ADDR, m_ivlan_lkp_table_info_u.data[2]);
     SE_WR_REG(SE_TB_OP_ADDR_RGT_REG_ADDR, (WRITE_TABLE<<TB_OP_ADDR_RGT_HOST_MGT_REQ_OPCODE_FIELD_OFFSET)+
                                           (IVLAN_LKP_SE_LITE_HASH_TABLE<<TB_OP_ADDR_RGT_HOST_MGT_REQ_ID_FIELD_OFFSET)+
                                           (ilvan_lkp_table_index<<TB_OP_ADDR_RGT_HOST_MGT_REQ_ADDR_FIELD_OFFSET)
                  );
     ilvan_lkp_table_index++;

     //enable ivlan_lkp_table
     update_reg(SE_CONFIG0_RGT_REG_ADDR, CONFIG0_RGT_IVLKP_CFG_ENTR_MINUS_ONE_FIELD_OFFSET, CONFIG0_RGT_IVLKP_CFG_ENTR_MINUS_ONE_FIELD_SIZE, (ilvan_lkp_table_index%2)?(ilvan_lkp_table_index/2)+1:(ilvan_lkp_table_index/2));
     update_reg(SE_CONFIG0_RGT_REG_ADDR, CONFIG0_RGT_IVLKP_CFG_DIS_TB_FIELD_OFFSET, CONFIG0_RGT_IVLKP_CFG_DIS_TB_FIELD_SIZE, 0);
}

//MPP: ivlan_vid, Table: VFP
extern BlkTable_S blk_tables[8];
void cfg_vfp_ipv4_table_item(VfpIpv4Key_S* vfp_ipv4_key, VfpRsp_S* vfp_rsp, IvlanCfg_S* ivlan_cfg) {

     int i = 0;
     KeyLocInfo_S m_key_loc_info;

     VfpIpv4TableInfo_U m_vfp_ipv4_table_info_u;
     VfpIpv4TableInfo_U m_vfp_ipv4_table_mask_info_u;

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
         m_vfp_ipv4_table_info_u.data[i] = 0x0;
         m_vfp_ipv4_table_mask_info_u.data[i] = 0xFFFFFFFF;
     }
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.un_pitag_action   = vfp_rsp->un_pitag_action ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.un_itag_action    = vfp_rsp->un_itag_action  ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.un_potag_action   = vfp_rsp->un_potag_action ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.un_otag_action    = vfp_rsp->un_otag_action  ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.sit_pitag_action  = vfp_rsp->sit_pitag_action;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.sit_itag_action   = vfp_rsp->sit_itag_action ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.sit_potag_action  = vfp_rsp->sit_potag_action;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.sit_otag_action   = vfp_rsp->sit_otag_action ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.sot_pitag_action  = vfp_rsp->sot_pitag_action;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.sot_itag_action   = vfp_rsp->sot_itag_action ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.sot_potag_action  = vfp_rsp->sot_potag_action;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.sot_otag_action   = vfp_rsp->sot_otag_action ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.dt_pitag_action   = vfp_rsp->dt_pitag_action ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.dt_itag_action    = vfp_rsp->dt_itag_action  ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.dt_potag_action   = vfp_rsp->dt_potag_action ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.dt_otag_action    = vfp_rsp->dt_otag_action  ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.new_ipri          = vfp_rsp->new_ipri        ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.new_opri          = vfp_rsp->new_opri        ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.new_ivid_1_0      = get_data16(vfp_rsp->new_ivid, 0, 2)    ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.new_ivid_9_2      = get_data16(vfp_rsp->new_ivid, 2, 8)    ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.new_ivid_11_10    = get_data16(vfp_rsp->new_ivid, 10, 2)   ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.new_ovid_5_0      = get_data16(vfp_rsp->new_ovid, 0, 6)    ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.new_ovid_11_6     = get_data16(vfp_rsp->new_ovid, 7, 6)    ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.transparent_en    = vfp_rsp->transparent_en  ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.dport_5_0         = get_data16(vfp_ipv4_key->dport, 0, 6)      ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.dport_13_6        = get_data16(vfp_ipv4_key->dport, 6, 8)      ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.dport_15_14       = get_data16(vfp_ipv4_key->dport, 14, 2)     ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.sport_5_0         = get_data16(vfp_ipv4_key->sport, 0, 6)      ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.sport_13_6        = get_data16(vfp_ipv4_key->sport, 6, 8)      ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.sport_15_14       = get_data16(vfp_ipv4_key->sport, 14, 2)     ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.protocal_5_0      = get_data16(vfp_ipv4_key->protocal, 0, 6)   ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.protocal_7_6      = get_data16(vfp_ipv4_key->protocal, 6, 2)   ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.dip0_5_0          = get_data64(vfp_ipv4_key->dip[0], 0, 6)     ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.dip0_7_6          = get_data64(vfp_ipv4_key->dip[0], 6, 2)     ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.dip1_5_0          = get_data64(vfp_ipv4_key->dip[1], 0, 6)     ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.dip1_7_6          = get_data64(vfp_ipv4_key->dip[1], 6, 2)     ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.dip2_5_0          = get_data64(vfp_ipv4_key->dip[2], 0, 6)     ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.dip2_7_6          = get_data64(vfp_ipv4_key->dip[2], 6, 2)     ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.dip3_5_0          = get_data64(vfp_ipv4_key->dip[3], 0, 6)     ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.dip3_7_6          = get_data64(vfp_ipv4_key->dip[3], 6, 2)     ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.sip0_5_0          = get_data64(vfp_ipv4_key->sip[0], 0, 6)     ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.sip0_7_6          = get_data64(vfp_ipv4_key->sip[0], 6, 2)     ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.sip1_5_0          = get_data64(vfp_ipv4_key->sip[1], 0, 6)     ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.sip1_7_6          = get_data64(vfp_ipv4_key->sip[1], 6, 2)     ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.sip2_5_0          = get_data64(vfp_ipv4_key->sip[2], 0, 6)     ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.sip2_7_6          = get_data64(vfp_ipv4_key->sip[2], 6, 2)     ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.sip3_5_0          = get_data64(vfp_ipv4_key->sip[3], 0, 6)     ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.sip3_7_6          = get_data64(vfp_ipv4_key->sip[3], 6, 2)     ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.dmac_5_0          = get_data64(vfp_ipv4_key->dmac, 0, 6)       ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.dmac_13_6         = get_data64(vfp_ipv4_key->dmac, 6, 8)       ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.dmac_21_14        = get_data64(vfp_ipv4_key->dmac, 14, 8)      ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.dmac_29_22        = get_data64(vfp_ipv4_key->dmac, 22, 8)      ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.dmac_37_30        = get_data64(vfp_ipv4_key->dmac, 30, 8)      ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.dmac_45_38        = get_data64(vfp_ipv4_key->dmac, 38, 8)      ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.dmac_47_46        = get_data64(vfp_ipv4_key->dmac, 46, 2)      ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.smac_5_0          = get_data64(vfp_ipv4_key->smac, 0, 6)       ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.smac_13_6         = get_data64(vfp_ipv4_key->smac, 6, 8)       ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.smac_21_14        = get_data64(vfp_ipv4_key->smac, 14, 8)      ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.smac_29_22        = get_data64(vfp_ipv4_key->smac, 22, 8)      ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.smac_37_30        = get_data64(vfp_ipv4_key->smac, 30, 8)      ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.smac_45_38        = get_data64(vfp_ipv4_key->smac, 38, 8)      ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.smac_47_46        = get_data64(vfp_ipv4_key->smac, 46, 2)      ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.i_vport           = vfp_ipv4_key->i_vport                      ;

     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.dport_5_0         = 0x0  ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.dport_13_6        = 0x0  ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.dport_15_14       = 0x0  ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.sport_5_0         = 0x0  ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.sport_13_6        = 0x0  ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.sport_15_14       = 0x0  ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.protocal_5_0      = 0x0  ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.protocal_7_6      = 0x0  ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.dip0_5_0          = 0x0  ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.dip0_7_6          = 0x0  ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.dip1_5_0          = 0x0  ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.dip1_7_6          = 0x0  ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.dip2_5_0          = 0x0  ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.dip2_7_6          = 0x0  ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.dip3_5_0          = 0x0  ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.dip3_7_6          = 0x0  ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.sip0_5_0          = 0x0  ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.sip0_7_6          = 0x0  ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.sip1_5_0          = 0x0  ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.sip1_7_6          = 0x0  ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.sip2_5_0          = 0x0  ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.sip2_7_6          = 0x0  ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.sip3_5_0          = 0x0  ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.sip3_7_6          = 0x0  ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.dmac_5_0          = 0x0  ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.dmac_13_6         = 0x0  ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.dmac_21_14        = 0x0  ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.dmac_29_22        = 0x0  ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.dmac_37_30        = 0x0  ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.dmac_45_38        = 0x0  ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.dmac_47_46        = 0x0  ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.smac_5_0          = 0x0  ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.smac_13_6         = 0x0  ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.smac_21_14        = 0x0  ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.smac_29_22        = 0x0  ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.smac_37_30        = 0x0  ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.smac_45_38        = 0x0  ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.smac_47_46        = 0x0  ;
     m_vfp_ipv4_table_info_u.m_vfp_ipv4_table_info_s.i_vport           = 0x0  ;

     get_blk_index(vfp_ipv4_key->table_id, vfp_ipv4_key->key_mode, VFP_TCAM_BLK, &blk_tables[0], &m_key_loc_info);
     #if SE_DEBUG_INFO
     printf("m_key_loc_info.blk_id      = %0d\n", m_key_loc_info.blk_id     );
     printf("m_key_loc_info.item_index  = %0d\n", m_key_loc_info.item_index );
     printf("m_key_loc_info.slice_index = %0d\n", m_key_loc_info.slice_index);
     #endif

     if(vfp_ipv4_key->key_mode == 2) {
         unsigned int req_id    = 0x0;
         unsigned int req_index = 0x0;

         req_id    = TCAM_BLK_RAM_ID(m_key_loc_info.blk_id, m_key_loc_info.slice_index);
         req_index = 2*m_key_loc_info.item_index;
         #if SE_DEBUG_INFO
         printf("req_id      = %0d\n",  req_id   );
         printf("req_index   = %0d\n",  req_index);
         #endif
         SE_WR_REG(SE_TCAM_TB_WRDATA00_RGT_REG_ADDR, m_vfp_ipv4_table_info_u.data[0]); //32
         SE_WR_REG(SE_TCAM_TB_WRDATA01_RGT_REG_ADDR, m_vfp_ipv4_table_info_u.data[1]); //32
         SE_WR_REG(SE_TCAM_TB_WRDATA02_RGT_REG_ADDR, m_vfp_ipv4_table_info_u.data[2]); //8
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
         SE_WR_REG(SE_TCAM_TB_WRDATA00_RGT_REG_ADDR, (GET_DATA_FIELD(m_vfp_ipv4_table_info_u.data[3], 0, 8)<<24)+GET_DATA_FIELD(m_vfp_ipv4_table_info_u.data[2], 8, 24));
         SE_WR_REG(SE_TCAM_TB_WRDATA01_RGT_REG_ADDR, (GET_DATA_FIELD(m_vfp_ipv4_table_info_u.data[4], 0, 8)<<24)+GET_DATA_FIELD(m_vfp_ipv4_table_info_u.data[3], 8, 24));
         SE_WR_REG(SE_TCAM_TB_WRDATA02_RGT_REG_ADDR, GET_DATA_FIELD(m_vfp_ipv4_table_info_u.data[4], 8, 8));
         SE_WR_REG(SE_TCAM_TB_OP_ADDR_RGT_REG_ADDR, (WRITE_TABLE<<TCAM_TB_OP_ADDR_RGT_HOST_MGT_REQ_OPCODE_FIELD_OFFSET)+
                                                    (req_id<<TCAM_TB_OP_ADDR_RGT_HOST_MGT_REQ_ID_FIELD_OFFSET)+
                                                    (req_index<<TCAM_TB_OP_ADDR_RGT_HOST_MGT_REQ_ADDR_FIELD_OFFSET)
                      );

         req_id    = TCAM_BLK_RAM_ID(m_key_loc_info.blk_id, m_key_loc_info.slice_index+2);
         req_index = 2*m_key_loc_info.item_index;
         #if SE_DEBUG_INFO
         printf("req_id      = %0d\n",  req_id   );
         printf("req_index   = %0d\n",  req_index);
         #endif
         SE_WR_REG(SE_TCAM_TB_WRDATA00_RGT_REG_ADDR, (GET_DATA_FIELD(m_vfp_ipv4_table_info_u.data[5], 0, 16)<<16)+GET_DATA_FIELD(m_vfp_ipv4_table_info_u.data[4], 16, 16));
         SE_WR_REG(SE_TCAM_TB_WRDATA01_RGT_REG_ADDR, (GET_DATA_FIELD(m_vfp_ipv4_table_info_u.data[6], 0, 16)<<16)+GET_DATA_FIELD(m_vfp_ipv4_table_info_u.data[5], 16, 16));
         SE_WR_REG(SE_TCAM_TB_WRDATA02_RGT_REG_ADDR, GET_DATA_FIELD(m_vfp_ipv4_table_info_u.data[6], 16, 8));
         SE_WR_REG(SE_TCAM_TB_OP_ADDR_RGT_REG_ADDR, (WRITE_TABLE<<TCAM_TB_OP_ADDR_RGT_HOST_MGT_REQ_OPCODE_FIELD_OFFSET)+
                                                    (req_id<<TCAM_TB_OP_ADDR_RGT_HOST_MGT_REQ_ID_FIELD_OFFSET)+
                                                    (req_index<<TCAM_TB_OP_ADDR_RGT_HOST_MGT_REQ_ADDR_FIELD_OFFSET)
                      );

         req_id    = TCAM_BLK_RAM_ID(m_key_loc_info.blk_id, m_key_loc_info.slice_index+3);
         req_index = 2*m_key_loc_info.item_index;
         #if SE_DEBUG_INFO
         printf("req_id      = %0d\n",  req_id   );
         printf("req_index   = %0d\n",  req_index);
         #endif
         SE_WR_REG(SE_TCAM_TB_WRDATA00_RGT_REG_ADDR, (GET_DATA_FIELD(m_vfp_ipv4_table_info_u.data[7], 0, 24)<<8)+GET_DATA_FIELD(m_vfp_ipv4_table_info_u.data[6], 24, 8));
         SE_WR_REG(SE_TCAM_TB_WRDATA01_RGT_REG_ADDR, (GET_DATA_FIELD(m_vfp_ipv4_table_info_u.data[8], 0, 24)<<8)+GET_DATA_FIELD(m_vfp_ipv4_table_info_u.data[7], 24, 8));
         SE_WR_REG(SE_TCAM_TB_WRDATA02_RGT_REG_ADDR, GET_DATA_FIELD(m_vfp_ipv4_table_info_u.data[8], 24, 8));
         SE_WR_REG(SE_TCAM_TB_OP_ADDR_RGT_REG_ADDR, (WRITE_TABLE<<TCAM_TB_OP_ADDR_RGT_HOST_MGT_REQ_OPCODE_FIELD_OFFSET)+
                                                    (req_id<<TCAM_TB_OP_ADDR_RGT_HOST_MGT_REQ_ID_FIELD_OFFSET)+
                                                    (req_index<<TCAM_TB_OP_ADDR_RGT_HOST_MGT_REQ_ADDR_FIELD_OFFSET)
                      );


         req_id    = TCAM_BLK_RAM_ID(m_key_loc_info.blk_id, m_key_loc_info.slice_index);
         req_index = 2*m_key_loc_info.item_index+1;
         SE_WR_REG(SE_TCAM_TB_WRDATA00_RGT_REG_ADDR, m_vfp_ipv4_table_mask_info_u.data[0]);
         SE_WR_REG(SE_TCAM_TB_WRDATA01_RGT_REG_ADDR, m_vfp_ipv4_table_mask_info_u.data[1]);
         SE_WR_REG(SE_TCAM_TB_WRDATA02_RGT_REG_ADDR, m_vfp_ipv4_table_mask_info_u.data[2]);
         SE_WR_REG(SE_TCAM_TB_OP_ADDR_RGT_REG_ADDR, (WRITE_TABLE<<TCAM_TB_OP_ADDR_RGT_HOST_MGT_REQ_OPCODE_FIELD_OFFSET)+
                                                    (req_id<<TCAM_TB_OP_ADDR_RGT_HOST_MGT_REQ_ID_FIELD_OFFSET)+
                                                    (req_index<<TCAM_TB_OP_ADDR_RGT_HOST_MGT_REQ_ADDR_FIELD_OFFSET)
                      );

         req_id    = TCAM_BLK_RAM_ID(m_key_loc_info.blk_id, m_key_loc_info.slice_index+1);
         req_index = 2*m_key_loc_info.item_index+1;
         #if SE_DEBUG_INFO
         printf("req_id      = %0d\n",  req_id   );
         printf("req_index   = %0d\n",  req_index);
         #endif
         SE_WR_REG(SE_TCAM_TB_WRDATA00_RGT_REG_ADDR, (GET_DATA_FIELD(m_vfp_ipv4_table_mask_info_u.data[3], 0, 8)<<24)+GET_DATA_FIELD(m_vfp_ipv4_table_mask_info_u.data[2], 8, 24));
         SE_WR_REG(SE_TCAM_TB_WRDATA01_RGT_REG_ADDR, (GET_DATA_FIELD(m_vfp_ipv4_table_mask_info_u.data[4], 0, 8)<<24)+GET_DATA_FIELD(m_vfp_ipv4_table_mask_info_u.data[3], 8, 24));
         SE_WR_REG(SE_TCAM_TB_WRDATA02_RGT_REG_ADDR, GET_DATA_FIELD(m_vfp_ipv4_table_mask_info_u.data[4], 8, 8));
         SE_WR_REG(SE_TCAM_TB_OP_ADDR_RGT_REG_ADDR, (WRITE_TABLE<<TCAM_TB_OP_ADDR_RGT_HOST_MGT_REQ_OPCODE_FIELD_OFFSET)+
                                                    (req_id<<TCAM_TB_OP_ADDR_RGT_HOST_MGT_REQ_ID_FIELD_OFFSET)+
                                                    (req_index<<TCAM_TB_OP_ADDR_RGT_HOST_MGT_REQ_ADDR_FIELD_OFFSET)
                      );

         req_id    = TCAM_BLK_RAM_ID(m_key_loc_info.blk_id, m_key_loc_info.slice_index+2);
         req_index = 2*m_key_loc_info.item_index+1;
         #if SE_DEBUG_INFO
         printf("req_id      = %0d\n",  req_id   );
         printf("req_index   = %0d\n",  req_index);
         #endif
         SE_WR_REG(SE_TCAM_TB_WRDATA00_RGT_REG_ADDR, (GET_DATA_FIELD(m_vfp_ipv4_table_mask_info_u.data[5], 0, 16)<<16)+GET_DATA_FIELD(m_vfp_ipv4_table_mask_info_u.data[4], 16, 16));
         SE_WR_REG(SE_TCAM_TB_WRDATA01_RGT_REG_ADDR, (GET_DATA_FIELD(m_vfp_ipv4_table_mask_info_u.data[6], 0, 16)<<16)+GET_DATA_FIELD(m_vfp_ipv4_table_mask_info_u.data[5], 16, 16));
         SE_WR_REG(SE_TCAM_TB_WRDATA02_RGT_REG_ADDR, GET_DATA_FIELD(m_vfp_ipv4_table_mask_info_u.data[6], 16, 8));
         SE_WR_REG(SE_TCAM_TB_OP_ADDR_RGT_REG_ADDR, (WRITE_TABLE<<TCAM_TB_OP_ADDR_RGT_HOST_MGT_REQ_OPCODE_FIELD_OFFSET)+
                                                    (req_id<<TCAM_TB_OP_ADDR_RGT_HOST_MGT_REQ_ID_FIELD_OFFSET)+
                                                    (req_index<<TCAM_TB_OP_ADDR_RGT_HOST_MGT_REQ_ADDR_FIELD_OFFSET)
                      );

         req_id    = TCAM_BLK_RAM_ID(m_key_loc_info.blk_id, m_key_loc_info.slice_index+3);
         req_index = 2*m_key_loc_info.item_index+1;
         #if SE_DEBUG_INFO
         printf("req_id      = %0d\n",  req_id   );
         printf("req_index   = %0d\n",  req_index);
         #endif
         SE_WR_REG(SE_TCAM_TB_WRDATA00_RGT_REG_ADDR, (GET_DATA_FIELD(m_vfp_ipv4_table_mask_info_u.data[7], 0, 24)<<8)+GET_DATA_FIELD(m_vfp_ipv4_table_mask_info_u.data[6], 24, 8));
         SE_WR_REG(SE_TCAM_TB_WRDATA01_RGT_REG_ADDR, (GET_DATA_FIELD(m_vfp_ipv4_table_mask_info_u.data[8], 0, 24)<<8)+GET_DATA_FIELD(m_vfp_ipv4_table_mask_info_u.data[7], 24, 8));
         SE_WR_REG(SE_TCAM_TB_WRDATA02_RGT_REG_ADDR, GET_DATA_FIELD(m_vfp_ipv4_table_mask_info_u.data[8], 24, 8));
         SE_WR_REG(SE_TCAM_TB_OP_ADDR_RGT_REG_ADDR, (WRITE_TABLE<<TCAM_TB_OP_ADDR_RGT_HOST_MGT_REQ_OPCODE_FIELD_OFFSET)+
                                                    (req_id<<TCAM_TB_OP_ADDR_RGT_HOST_MGT_REQ_ID_FIELD_OFFSET)+
                                                    (req_index<<TCAM_TB_OP_ADDR_RGT_HOST_MGT_REQ_ADDR_FIELD_OFFSET)
                      );


         req_id    = TCAM_BLK_MODE_ID(m_key_loc_info.blk_id);
         req_index = m_key_loc_info.item_index;
         SE_WR_REG(SE_TCAM_TB_WRDATA00_RGT_REG_ADDR, (vfp_ipv4_key->key_mode<<2)+vfp_ipv4_key->table_id);
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

//MPP: ivlan_vid, Table: ivlan_xlt
static int ivlan_xlt_table_index = 0;
void cfg_ivlan_xlt_table_item(IvlanXltKey_S* ivlan_xlt_key, IvlanXltRsp_S* ivlan_xlt_rsp, IvlanCfg_S* ivlan_cfg) {

     int i = 0;

     IvlanXltTableInfo_U m_ivlan_xlt_table_info_u;

     for(i=0; i<3; i++) {
         m_ivlan_xlt_table_info_u.data[i] = 0x0;
     }
     m_ivlan_xlt_table_info_u.m_ivlan_xlt_table_info_s.result_vld           = 1                                                  ;
     m_ivlan_xlt_table_info_u.m_ivlan_xlt_table_info_s.un_pitag_action      = ivlan_xlt_rsp->un_pitag_action                     ;
     m_ivlan_xlt_table_info_u.m_ivlan_xlt_table_info_s.un_itag_action       = ivlan_xlt_rsp->un_itag_action                      ;
     m_ivlan_xlt_table_info_u.m_ivlan_xlt_table_info_s.un_potag_action      = ivlan_xlt_rsp->un_potag_action                     ;
     m_ivlan_xlt_table_info_u.m_ivlan_xlt_table_info_s.un_otag_action_0     = get_data16(ivlan_xlt_rsp->un_otag_action, 0, 1)    ;
     m_ivlan_xlt_table_info_u.m_ivlan_xlt_table_info_s.un_otag_action_1     = get_data16(ivlan_xlt_rsp->un_otag_action, 1, 1)    ;
     m_ivlan_xlt_table_info_u.m_ivlan_xlt_table_info_s.sit_pitag_action     = ivlan_xlt_rsp->sit_pitag_action                    ;
     m_ivlan_xlt_table_info_u.m_ivlan_xlt_table_info_s.sit_itag_action      = ivlan_xlt_rsp->sit_itag_action                     ;
     m_ivlan_xlt_table_info_u.m_ivlan_xlt_table_info_s.sit_potag_action     = ivlan_xlt_rsp->sit_potag_action                    ;
     m_ivlan_xlt_table_info_u.m_ivlan_xlt_table_info_s.sit_otag_action_0    = get_data16(ivlan_xlt_rsp->sit_otag_action, 0, 1)   ;
     m_ivlan_xlt_table_info_u.m_ivlan_xlt_table_info_s.sit_otag_action_1    = get_data16(ivlan_xlt_rsp->sit_otag_action, 1, 1)   ;
     m_ivlan_xlt_table_info_u.m_ivlan_xlt_table_info_s.sot_pitag_action     = ivlan_xlt_rsp->sot_pitag_action                    ;
     m_ivlan_xlt_table_info_u.m_ivlan_xlt_table_info_s.sot_itag_action      = ivlan_xlt_rsp->sot_itag_action                     ;
     m_ivlan_xlt_table_info_u.m_ivlan_xlt_table_info_s.sot_potag_action     = ivlan_xlt_rsp->sot_potag_action                    ;
     m_ivlan_xlt_table_info_u.m_ivlan_xlt_table_info_s.sot_otag_action_0    = get_data16(ivlan_xlt_rsp->sot_otag_action, 0, 1)   ;
     m_ivlan_xlt_table_info_u.m_ivlan_xlt_table_info_s.sot_otag_action_1    = get_data16(ivlan_xlt_rsp->sot_otag_action, 1, 1)   ;
     m_ivlan_xlt_table_info_u.m_ivlan_xlt_table_info_s.dt_pitag_action      = ivlan_xlt_rsp->dt_pitag_action                     ;
     m_ivlan_xlt_table_info_u.m_ivlan_xlt_table_info_s.dt_itag_action       = ivlan_xlt_rsp->dt_itag_action                      ;
     m_ivlan_xlt_table_info_u.m_ivlan_xlt_table_info_s.dt_potag_action      = ivlan_xlt_rsp->dt_potag_action                     ;
     m_ivlan_xlt_table_info_u.m_ivlan_xlt_table_info_s.dt_otag_action_0     = get_data16(ivlan_xlt_rsp->dt_otag_action, 0, 1)    ;
     m_ivlan_xlt_table_info_u.m_ivlan_xlt_table_info_s.dt_otag_action_1     = get_data16(ivlan_xlt_rsp->dt_otag_action, 1, 1)    ;
     m_ivlan_xlt_table_info_u.m_ivlan_xlt_table_info_s.new_ipri             = ivlan_xlt_rsp->new_ipri                            ;
     m_ivlan_xlt_table_info_u.m_ivlan_xlt_table_info_s.new_opri             = ivlan_xlt_rsp->new_opri                            ;
     m_ivlan_xlt_table_info_u.m_ivlan_xlt_table_info_s.new_ivid_0           = get_data16(ivlan_xlt_rsp->new_ivid, 0, 1)          ;
     m_ivlan_xlt_table_info_u.m_ivlan_xlt_table_info_s.new_ivid_8_1         = get_data16(ivlan_xlt_rsp->new_ivid, 1, 8)          ;
     m_ivlan_xlt_table_info_u.m_ivlan_xlt_table_info_s.new_ivid_11_9        = get_data16(ivlan_xlt_rsp->new_ivid, 9, 3)          ;
     m_ivlan_xlt_table_info_u.m_ivlan_xlt_table_info_s.new_ovid_4_0         = get_data16(ivlan_xlt_rsp->new_ovid, 0, 5)          ;
     m_ivlan_xlt_table_info_u.m_ivlan_xlt_table_info_s.new_ovid_11_5        = get_data16(ivlan_xlt_rsp->new_ovid, 5, 7)          ;
     m_ivlan_xlt_table_info_u.m_ivlan_xlt_table_info_s.transparent_en       = ivlan_xlt_rsp->transparent_en                      ;
     m_ivlan_xlt_table_info_u.m_ivlan_xlt_table_info_s.inner_vid_7_0        = get_data16(ivlan_xlt_key->inner_vid, 0, 8)         ;
     m_ivlan_xlt_table_info_u.m_ivlan_xlt_table_info_s.inner_vid_11_8       = get_data16(ivlan_xlt_key->inner_vid, 8, 4)         ;
     m_ivlan_xlt_table_info_u.m_ivlan_xlt_table_info_s.outer_vid_3_0        = get_data16(ivlan_xlt_key->outer_vid, 0, 4)         ;
     m_ivlan_xlt_table_info_u.m_ivlan_xlt_table_info_s.outer_vid_11_4       = get_data16(ivlan_xlt_key->outer_vid, 4, 8)         ;
     m_ivlan_xlt_table_info_u.m_ivlan_xlt_table_info_s.iport_num            = ivlan_xlt_key->iport_num                           ;

     SE_WR_REG(SE_TB_WRDATA00_RGT_REG_ADDR, m_ivlan_xlt_table_info_u.data[0]);
     SE_WR_REG(SE_TB_WRDATA01_RGT_REG_ADDR, m_ivlan_xlt_table_info_u.data[1]);
     SE_WR_REG(SE_TB_WRDATA02_RGT_REG_ADDR, m_ivlan_xlt_table_info_u.data[2]);
     SE_WR_REG(SE_TB_OP_ADDR_RGT_REG_ADDR, (WRITE_TABLE<<TB_OP_ADDR_RGT_HOST_MGT_REQ_OPCODE_FIELD_OFFSET)+
                                           (IVLAN_XLT_SE_LITE_HASH_TABLE<<TB_OP_ADDR_RGT_HOST_MGT_REQ_ID_FIELD_OFFSET)+
                                           (ivlan_xlt_table_index<<TB_OP_ADDR_RGT_HOST_MGT_REQ_ADDR_FIELD_OFFSET)
                  );

     ivlan_xlt_table_index++;

     //enable ivlan_iport_table
     update_reg(SE_CONFIG0_RGT_REG_ADDR, CONFIG0_RGT_IVXLT_CFG_ENTR_MINUS_ONE_FIELD_OFFSET, CONFIG0_RGT_IVXLT_CFG_ENTR_MINUS_ONE_FIELD_SIZE, (ivlan_xlt_table_index%2)?(ivlan_xlt_table_index/2)+1:(ivlan_xlt_table_index/2));
     update_reg(SE_CONFIG0_RGT_REG_ADDR, CONFIG0_RGT_IVXLT_CFG_DIS_TB_FIELD_OFFSET, CONFIG0_RGT_IVXLT_CFG_DIS_TB_FIELD_SIZE, 0);
}


#endif

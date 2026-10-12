#ifndef EVLAN_SE_C
#define EVLAN_SE_C

#include "evlan_se.h"
#include "se_common.h"
#include <string.h>

//MPP: evlan_act, Table: evlan_act
void cfg_evlan_act_table_item(EvlanActKey_S* evlan_act_key, EvlanActRsp_S* evlan_act_rsp, EvlanCfg_S* evlan_act_cfg) {

     EvlanActTableInfo_U m_evlan_act_table_info_u;

     m_evlan_act_table_info_u.data = 0x0;

     m_evlan_act_table_info_u.m_evlan_act_table_info_s.tt_atag_action   = evlan_act_rsp->tt_atag_action  ;
     m_evlan_act_table_info_u.m_evlan_act_table_info_s.tt_patag_action  = evlan_act_rsp->tt_patag_action ;
     m_evlan_act_table_info_u.m_evlan_act_table_info_s.tt_otag_action   = evlan_act_rsp->tt_otag_action  ;
     m_evlan_act_table_info_u.m_evlan_act_table_info_s.tt_potag_action  = evlan_act_rsp->tt_potag_action ;
     m_evlan_act_table_info_u.m_evlan_act_table_info_s.tt_itag_action   = evlan_act_rsp->tt_itag_action  ;
     m_evlan_act_table_info_u.m_evlan_act_table_info_s.tt_pitag_action  = evlan_act_rsp->tt_pitag_action ;
     m_evlan_act_table_info_u.m_evlan_act_table_info_s.dt_otag_action   = evlan_act_rsp->dt_otag_action  ;
     m_evlan_act_table_info_u.m_evlan_act_table_info_s.dt_potag_action  = evlan_act_rsp->dt_potag_action ;
     m_evlan_act_table_info_u.m_evlan_act_table_info_s.dt_itag_action   = evlan_act_rsp->dt_itag_action  ;
     m_evlan_act_table_info_u.m_evlan_act_table_info_s.dt_pitag_action  = evlan_act_rsp->dt_pitag_action ;
     m_evlan_act_table_info_u.m_evlan_act_table_info_s.sot_otag_action  = evlan_act_rsp->sot_otag_action ;
     m_evlan_act_table_info_u.m_evlan_act_table_info_s.sot_potag_action = evlan_act_rsp->sot_potag_action;
     m_evlan_act_table_info_u.m_evlan_act_table_info_s.sot_itag_action  = evlan_act_rsp->sot_itag_action ;
     m_evlan_act_table_info_u.m_evlan_act_table_info_s.sot_pitag_action = evlan_act_rsp->sot_pitag_action;

     SE_WR_REG(SE_TB_WRDATA00_RGT_REG_ADDR, m_evlan_act_table_info_u.data);
     SE_WR_REG(SE_TB_OP_ADDR_RGT_REG_ADDR, (WRITE_TABLE<<TB_OP_ADDR_RGT_HOST_MGT_REQ_OPCODE_FIELD_OFFSET)+
                                           (EVLAN_ACT_SE_DIRECT_TABLE<<TB_OP_ADDR_RGT_HOST_MGT_REQ_ID_FIELD_OFFSET)+
                                           (evlan_act_key->tag_action_id<<TB_OP_ADDR_RGT_HOST_MGT_REQ_ADDR_FIELD_OFFSET)
                  );

     //enable evlan_act_table
     update_reg(SE_CONFIG2_RGT_REG_ADDR, CONFIG2_RGT_EVACT_TABLE_VLD_FIELD_OFFSET, CONFIG2_RGT_EVACT_TABLE_VLD_FIELD_SIZE, 1);
}

//MPP: evlan_lkp, Table: evlan_lkp
static int evlan_lkp_hash_table_index = 0;
static EvlanLkpTpidTableInfo_U evlan_lkp_tpid_table[8];
static int evlan_lkp_tpid_table_index = 0;
static int evlan_lkp_tpid_table_init_flag = 0;
void cfg_evlan_lkp_table_item(EvlanLkpKey_S* evlan_lkp_key, EvlanLkpRsp_S* evlan_lkp_rsp, EvlanCfg_S* evlan_lkp_cfg) {

     int i = 0;

     int hash_table_id = 0;
     int hash_table_index = 0;

     int is_tpid_table_exist = 0;

     EvlanLkpTableInfo_U m_evlan_lkp_table_info_u;
     EvlanLkpTpidTableInfo_U m_evlan_lkp_tpid_table_info_u;

     m_evlan_lkp_tpid_table_info_u.data = 0x0;

     if(evlan_lkp_tpid_table_init_flag == 0) {
         for(i=0; i<8; i++) {
             evlan_lkp_tpid_table[i].data = 0x0;
         }
         evlan_lkp_tpid_table_init_flag = 1;
     }

     m_evlan_lkp_table_info_u.m_evlan_lkp_table_info_s.outer_tpid_index = evlan_lkp_tpid_table_index;
     for(i=0; i<8; i++) {
         if( (evlan_lkp_tpid_table[i].m_evlan_lkp_tpid_table_info_s.outer_tpid == evlan_lkp_rsp->outer_tpid) &&
             (evlan_lkp_tpid_table[i].m_evlan_lkp_tpid_table_info_s.vld == 1)
           ) {
             m_evlan_lkp_table_info_u.m_evlan_lkp_table_info_s.outer_tpid_index = i;
             is_tpid_table_exist = 1;
             break;
         }
     }
     if(is_tpid_table_exist == 0) {
         evlan_lkp_tpid_table[evlan_lkp_tpid_table_index].m_evlan_lkp_tpid_table_info_s.vld = 1;
         m_evlan_lkp_tpid_table_info_u.m_evlan_lkp_tpid_table_info_s.outer_tpid = evlan_lkp_rsp->outer_tpid;
         SE_WR_REG(SE_TB_WRDATA00_RGT_REG_ADDR, m_evlan_lkp_tpid_table_info_u.data);
         SE_WR_REG(SE_TB_OP_ADDR_RGT_REG_ADDR, (WRITE_TABLE<<TB_OP_ADDR_RGT_HOST_MGT_REQ_OPCODE_FIELD_OFFSET)+
                                               (EVLAN_OTPID_SE_DIRECT_TABLE<<TB_OP_ADDR_RGT_HOST_MGT_REQ_ID_FIELD_OFFSET)+
                                               (m_evlan_lkp_table_info_u.m_evlan_lkp_table_info_s.outer_tpid_index<<TB_OP_ADDR_RGT_HOST_MGT_REQ_ADDR_FIELD_OFFSET)
                  );
         update_reg(SE_CONFIG2_RGT_REG_ADDR, CONFIG2_RGT_OTPID_TABLE_VLD_FIELD_OFFSET, CONFIG2_RGT_OTPID_TABLE_VLD_FIELD_SIZE, 1);

         evlan_lkp_tpid_table_index++;
     }

     for(i=0; i<4; i++) {
         m_evlan_lkp_table_info_u.data[i] = 0x0;
     }
     m_evlan_lkp_table_info_u.m_evlan_lkp_table_info_s.result_vld                =  1                                ;
     m_evlan_lkp_table_info_u.m_evlan_lkp_table_info_s.sp_tree_port9             =  evlan_lkp_rsp->sp_tree_port9     ;
     m_evlan_lkp_table_info_u.m_evlan_lkp_table_info_s.sp_tree_port8             =  evlan_lkp_rsp->sp_tree_port8     ;
     m_evlan_lkp_table_info_u.m_evlan_lkp_table_info_s.sp_tree_port7             =  evlan_lkp_rsp->sp_tree_port7     ;
     m_evlan_lkp_table_info_u.m_evlan_lkp_table_info_s.sp_tree_port6             =  evlan_lkp_rsp->sp_tree_port6     ;
     m_evlan_lkp_table_info_u.m_evlan_lkp_table_info_s.sp_tree_port5             =  evlan_lkp_rsp->sp_tree_port5     ;
     m_evlan_lkp_table_info_u.m_evlan_lkp_table_info_s.sp_tree_port4             =  evlan_lkp_rsp->sp_tree_port4     ;
     m_evlan_lkp_table_info_u.m_evlan_lkp_table_info_s.sp_tree_port3             =  evlan_lkp_rsp->sp_tree_port3     ;
     m_evlan_lkp_table_info_u.m_evlan_lkp_table_info_s.sp_tree_port2             =  evlan_lkp_rsp->sp_tree_port2     ;
     m_evlan_lkp_table_info_u.m_evlan_lkp_table_info_s.sp_tree_port1             =  evlan_lkp_rsp->sp_tree_port1     ;
     m_evlan_lkp_table_info_u.m_evlan_lkp_table_info_s.sp_tree_port0             =  evlan_lkp_rsp->sp_tree_port0     ;
     m_evlan_lkp_table_info_u.m_evlan_lkp_table_info_s.un_bitmap_7_0             =  get_data64(evlan_lkp_rsp->un_bitmap, 0, 8)  ;
     m_evlan_lkp_table_info_u.m_evlan_lkp_table_info_s.un_bitmap_15_8            =  get_data64(evlan_lkp_rsp->un_bitmap, 8, 8)  ;
     m_evlan_lkp_table_info_u.m_evlan_lkp_table_info_s.un_bitmap_23_16           =  get_data64(evlan_lkp_rsp->un_bitmap, 16,8)  ;
     m_evlan_lkp_table_info_u.m_evlan_lkp_table_info_s.un_bitmap_31_24           =  get_data64(evlan_lkp_rsp->un_bitmap, 24,8)  ;
     m_evlan_lkp_table_info_u.m_evlan_lkp_table_info_s.un_bitmap_35_32           =  get_data64(evlan_lkp_rsp->un_bitmap, 32,4)  ;
     m_evlan_lkp_table_info_u.m_evlan_lkp_table_info_s.port_bitmap_3_0           =  get_data64(evlan_lkp_rsp->port_bitmap, 0, 4);
     m_evlan_lkp_table_info_u.m_evlan_lkp_table_info_s.port_bitmap_11_4          =  get_data64(evlan_lkp_rsp->port_bitmap, 4, 8);
     m_evlan_lkp_table_info_u.m_evlan_lkp_table_info_s.port_bitmap_19_12         =  get_data64(evlan_lkp_rsp->port_bitmap, 12,8);
     m_evlan_lkp_table_info_u.m_evlan_lkp_table_info_s.port_bitmap_27_20         =  get_data64(evlan_lkp_rsp->port_bitmap, 20,8);
     m_evlan_lkp_table_info_u.m_evlan_lkp_table_info_s.port_bitmap_35_28         =  get_data64(evlan_lkp_rsp->port_bitmap, 28,8);
     m_evlan_lkp_table_info_u.m_evlan_lkp_table_info_s.ovid_7_0                  =  get_data16(evlan_lkp_key->ovid, 0, 8)       ;
     m_evlan_lkp_table_info_u.m_evlan_lkp_table_info_s.ovid_11_8                 =  get_data16(evlan_lkp_key->ovid, 8, 4)       ;

     hash_table_id    = ((evlan_lkp_hash_table_index&0x30)>>4);
     hash_table_index = (evlan_lkp_hash_table_index&0x0f);

     SE_WR_REG(SE_TB_WRDATA00_RGT_REG_ADDR, m_evlan_lkp_table_info_u.data[0]);
     SE_WR_REG(SE_TB_WRDATA01_RGT_REG_ADDR, m_evlan_lkp_table_info_u.data[1]);
     SE_WR_REG(SE_TB_WRDATA02_RGT_REG_ADDR, m_evlan_lkp_table_info_u.data[2]);
     SE_WR_REG(SE_TB_WRDATA03_RGT_REG_ADDR, m_evlan_lkp_table_info_u.data[3]);
     SE_WR_REG(SE_TB_OP_ADDR_RGT_REG_ADDR, (WRITE_TABLE<<TB_OP_ADDR_RGT_HOST_MGT_REQ_OPCODE_FIELD_OFFSET)+
                                           (EVLAN_VID_SE_LITE_HASH_TABLE<<TB_OP_ADDR_RGT_HOST_MGT_REQ_ID_FIELD_OFFSET)+
                                           (((hash_table_index<<2)+hash_table_id)<<TB_OP_ADDR_RGT_HOST_MGT_REQ_ADDR_FIELD_OFFSET)
                  );
     evlan_lkp_hash_table_index++;

     #if SE_DEBUG_INFO
     {
         int i=0;
         for(i=0; i<4; i++) {
             printf("11111111111 m_evlan_lkp_table_info_u.data[%0d] = 0x%0x\n", i, m_evlan_lkp_table_info_u.data[i]);
         }
     }
     #endif

     //enable evlan_lkp_table
     update_reg(SE_CONFIG2_RGT_REG_ADDR, CONFIG2_RGT_EVLKP_CFG_ENTR_MINUS_ONE_FIELD_OFFSET, CONFIG2_RGT_EVLKP_CFG_ENTR_MINUS_ONE_FIELD_SIZE, hash_table_index);
     update_reg(SE_CONFIG2_RGT_REG_ADDR, CONFIG2_RGT_EVLKP_CFG_DIS_TB_FIELD_OFFSET, CONFIG2_RGT_EVLKP_CFG_DIS_TB_FIELD_SIZE, 0);
}

//MPP: evlan_xlt, Table: evlan_xlt
static int evlan_xlt_table_index = 0;
void cfg_evlan_xlt_table_item(EvlanXltKey_S* evlan_xlt_key, EvlanXltRsp_S* evlan_xlt_rsp, EvlanCfg_S* evlan_cfg) {

     int i = 0;

     EvlanXltTableInfo_U m_evlan_xlt_table_info_u;

     for(i=0; i<3; i++) {
         m_evlan_xlt_table_info_u.data[i] = 0x0;
     }
     m_evlan_xlt_table_info_u.m_evlan_xlt_table_info_s.result_vld                  = 1                                          ;
     m_evlan_xlt_table_info_u.m_evlan_xlt_table_info_s.tag_action_profile_ptr      = evlan_xlt_rsp->tag_action_profile_ptr      ;
     m_evlan_xlt_table_info_u.m_evlan_xlt_table_info_s.new_ipri_0                  = get_data16(evlan_xlt_rsp->new_ipri, 0, 1)  ;
     m_evlan_xlt_table_info_u.m_evlan_xlt_table_info_s.new_ipri_2_1                = get_data16(evlan_xlt_rsp->new_ipri, 1, 2)  ;
     m_evlan_xlt_table_info_u.m_evlan_xlt_table_info_s.new_opri                    = evlan_xlt_rsp->new_opri                    ;
     m_evlan_xlt_table_info_u.m_evlan_xlt_table_info_s.new_ivid_2_0                = get_data16(evlan_xlt_rsp->new_ivid, 0, 3)  ;
     m_evlan_xlt_table_info_u.m_evlan_xlt_table_info_s.new_ivid_10_3               = get_data16(evlan_xlt_rsp->new_ivid, 3, 8)  ;
     m_evlan_xlt_table_info_u.m_evlan_xlt_table_info_s.new_ivid_11                 = get_data16(evlan_xlt_rsp->new_ivid, 11, 1) ;
     m_evlan_xlt_table_info_u.m_evlan_xlt_table_info_s.new_ovid_6_0                = get_data16(evlan_xlt_rsp->new_ovid, 0, 7)  ;
     m_evlan_xlt_table_info_u.m_evlan_xlt_table_info_s.new_ovid_11_7               = get_data16(evlan_xlt_rsp->new_ovid, 7, 5)  ;
     m_evlan_xlt_table_info_u.m_evlan_xlt_table_info_s.old_ivid_2_0                = get_data16(evlan_xlt_key->old_ivid, 0, 3)  ;
     m_evlan_xlt_table_info_u.m_evlan_xlt_table_info_s.old_ivid_10_3               = get_data16(evlan_xlt_key->old_ivid, 3, 8)  ;
     m_evlan_xlt_table_info_u.m_evlan_xlt_table_info_s.old_ivid_11                 = get_data16(evlan_xlt_key->old_ivid, 11, 1) ;
     m_evlan_xlt_table_info_u.m_evlan_xlt_table_info_s.old_ovid_6_0                = get_data16(evlan_xlt_key->old_ovid, 0, 7)  ;
     m_evlan_xlt_table_info_u.m_evlan_xlt_table_info_s.old_ovid_11_7               = get_data16(evlan_xlt_key->old_ovid, 7, 5)  ;
     m_evlan_xlt_table_info_u.m_evlan_xlt_table_info_s.oport_num_2_0               = get_data16(evlan_xlt_key->oport_num, 0, 3) ;
     m_evlan_xlt_table_info_u.m_evlan_xlt_table_info_s.oport_num_5_3               = get_data16(evlan_xlt_key->oport_num, 3, 3) ;

     SE_WR_REG(SE_TB_WRDATA00_RGT_REG_ADDR, m_evlan_xlt_table_info_u.data[0]);
     SE_WR_REG(SE_TB_WRDATA01_RGT_REG_ADDR, m_evlan_xlt_table_info_u.data[1]);
     SE_WR_REG(SE_TB_WRDATA02_RGT_REG_ADDR, m_evlan_xlt_table_info_u.data[2]);
     SE_WR_REG(SE_TB_OP_ADDR_RGT_REG_ADDR, (WRITE_TABLE<<TB_OP_ADDR_RGT_HOST_MGT_REQ_OPCODE_FIELD_OFFSET)+
                                           (EVLAN_XLT_SE_LITE_HASH_TABLE<<TB_OP_ADDR_RGT_HOST_MGT_REQ_ID_FIELD_OFFSET)+
                                           (evlan_xlt_table_index<<TB_OP_ADDR_RGT_HOST_MGT_REQ_ADDR_FIELD_OFFSET)
                  );

     evlan_xlt_table_index++;

     //enable evlan_iport_table
     update_reg(SE_CONFIG2_RGT_REG_ADDR, CONFIG2_RGT_EVXLT_CFG_ENTR_MINUS_ONE_FIELD_OFFSET, CONFIG2_RGT_EVXLT_CFG_ENTR_MINUS_ONE_FIELD_SIZE, (evlan_xlt_table_index%2)?(evlan_xlt_table_index/2)+1:(evlan_xlt_table_index/2));
     update_reg(SE_CONFIG2_RGT_REG_ADDR, CONFIG2_RGT_EVXLT_CFG_DIS_TB_FIELD_OFFSET, CONFIG2_RGT_EVXLT_CFG_DIS_TB_FIELD_SIZE, 0);
}

//MPP: evlan_lkp, Table: port_tpid
void cfg_evlan_ptpid_table_item(EvlanPtpidKey_S* evlan_ptpid_key, EvlanPtpidRsp_S* evlan_ptpid_rsp, EvlanCfg_S* evlan_ptpid_cfg) {

     EvlanPtpidTableInfo_U m_evlan_ptpid_table_info_u;

     m_evlan_ptpid_table_info_u.data = 0x0;

     m_evlan_ptpid_table_info_u.m_evlan_ptpid_table_info_s.inner_tpid   = evlan_ptpid_rsp->inner_tpid  ;
     m_evlan_ptpid_table_info_u.m_evlan_ptpid_table_info_s.outer_tpid   = evlan_ptpid_rsp->outer_tpid ;

     SE_WR_REG(SE_TB_WRDATA00_RGT_REG_ADDR, m_evlan_ptpid_table_info_u.data);
     SE_WR_REG(SE_TB_OP_ADDR_RGT_REG_ADDR, (WRITE_TABLE<<TB_OP_ADDR_RGT_HOST_MGT_REQ_OPCODE_FIELD_OFFSET)+
                                           (EVLAN_TPID_SE_HASH_TABLE<<TB_OP_ADDR_RGT_HOST_MGT_REQ_ID_FIELD_OFFSET)+
                                           (evlan_ptpid_key->tag_action_id<<TB_OP_ADDR_RGT_HOST_MGT_REQ_ADDR_FIELD_OFFSET)
                  );

     //enable evlan_ptpid_table
     update_reg(SE_CONFIG2_RGT_REG_ADDR, CONFIG2_RGT_PTPID_TABLE_VLD_FIELD_OFFSET, CONFIG2_RGT_PTPID_TABLE_VLD_FIELD_SIZE, 1);
}

#endif

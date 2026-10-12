#ifndef EVLAN_SE_H
#define EVLAN_SE_H

#include "se_common.h"

//Evlan CFG:
typedef struct evlan_cfg_s {
    unsigned char hnat_mode;
}EvlanCfg_S;


//MPP: evlan_act, Table: evlan_act
typedef struct evlan_act_key_s {
    unsigned char  tag_action_id;
}EvlanActKey_S;

typedef struct evlan_act_rsp_s { //not include hit and limit drop

    unsigned char tt_atag_action  ;
    unsigned char tt_patag_action ;
    unsigned char tt_otag_action  ;
    unsigned char tt_potag_action ;
    unsigned char tt_itag_action  ;
    unsigned char tt_pitag_action ;
    unsigned char dt_otag_action  ;
    unsigned char dt_potag_action ;
    unsigned char dt_itag_action  ;
    unsigned char dt_pitag_action ;
    unsigned char sot_otag_action ;
    unsigned char sot_potag_action;
    unsigned char sot_itag_action ;
    unsigned char sot_pitag_action;

}EvlanActRsp_S;

typedef struct evlan_act_table_info_s {
       unsigned char sot_pitag_action: 2;
       unsigned char sot_itag_action : 2;
       unsigned char sot_potag_action: 2;
       unsigned char sot_otag_action : 2; //sot_pitag_action,sot_itag_action,sot_potag_action,sot_otag_action format a char field
       unsigned char dt_pitag_action : 2;
       unsigned char dt_itag_action  : 2;
       unsigned char dt_potag_action : 2;
       unsigned char dt_otag_action  : 2; //dt_pitag_action,dt_itag_action,dt_potag_action,dt_otag_action format a char field
       unsigned char tt_pitag_action : 2;
       unsigned char tt_itag_action  : 2;
       unsigned char tt_potag_action : 2;
       unsigned char tt_otag_action  : 2; //tt_pitag_action,tt_itag_action,tt_potag_action,tt_otag_action format a char field
       unsigned char tt_patag_action : 2;
       unsigned char tt_atag_action  : 2;
       unsigned char rsv0            : 4; //tt_patag_action,tt_atag_action,rsv0 format a char field
}EvlanActTableInfo_S;

typedef union evlan_act_table_info_u {
       EvlanActTableInfo_S m_evlan_act_table_info_s;
       unsigned int data;
}EvlanActTableInfo_U;

void cfg_evlan_act_table_item(EvlanActKey_S* evlan_act_key, EvlanActRsp_S* evlan_act_rsp, EvlanCfg_S* evlan_cfg);

//MPP: evlan_lkp, Table: evlan_lkp
typedef struct evlan_lkp_key_s {
    unsigned char  ovid;
}EvlanLkpKey_S;

typedef struct evlan_lkp_rsp_s { //not include hit and limit drop

    uint64_t       port_bitmap       ;
    uint64_t       un_bitmap         ;
    unsigned char  sp_tree_port0     ;
    unsigned char  sp_tree_port1     ;
    unsigned char  sp_tree_port2     ;
    unsigned char  sp_tree_port3     ;
    unsigned char  sp_tree_port4     ;
    unsigned char  sp_tree_port5     ;
    unsigned char  sp_tree_port6     ;
    unsigned char  sp_tree_port7     ;
    unsigned char  sp_tree_port8     ;
    unsigned char  sp_tree_port9     ;
    unsigned short outer_tpid        ;
}EvlanLkpRsp_S;

typedef struct evlan_lkp_table_info_s {

       unsigned char result_vld         : 1;
       unsigned char outer_tpid_index   : 3;
       unsigned char sp_tree_port9      : 2;
       unsigned char sp_tree_port8      : 2; // result_vld,outer_tpid_6_0,sp_tree_port9,sp_tree_port8 format a char field
       unsigned char sp_tree_port7      : 2;
       unsigned char sp_tree_port6      : 2;
       unsigned char sp_tree_port5      : 2;
       unsigned char sp_tree_port4      : 2; // sp_tree_port7,sp_tree_port6,sp_tree_port5,sp_tree_port4 format a char field
       unsigned char sp_tree_port3      : 2;
       unsigned char sp_tree_port2      : 2; 
       unsigned char sp_tree_port1      : 2;
       unsigned char sp_tree_port0      : 2; // sp_tree_port3,sp_tree_port2,sp_tree_port1,sp_tree_port0 format a char field
       unsigned char un_bitmap_7_0         ;
       unsigned char un_bitmap_15_8        ;
       unsigned char un_bitmap_23_16       ;
       unsigned char un_bitmap_31_24       ;
       unsigned char un_bitmap_35_32    : 4;
       unsigned char port_bitmap_3_0    : 4; // un_bitmap_35_32,port_bitmap_3_0 format a char field
       unsigned char port_bitmap_11_4      ;
       unsigned char port_bitmap_19_12     ;
       unsigned char port_bitmap_27_20     ;
       unsigned char port_bitmap_35_28     ;
       unsigned char ovid_7_0              ;
       unsigned char ovid_11_8          : 4;
       unsigned char rsv0               : 4; // ovid_11_8,rsv0 format a char field
       unsigned char rsv1[2]               ;
}EvlanLkpTableInfo_S;

typedef union evlan_lkp_table_info_u {
       EvlanLkpTableInfo_S m_evlan_lkp_table_info_s;
       unsigned int data[4];
}EvlanLkpTableInfo_U;

//tpid little table
typedef struct evlan_lkp_tpid_table_info_s {
       unsigned short outer_tpid;
       unsigned short vld       ;
}EvlanLkpTpidTableInfo_S;

typedef union evlan_lkp_tpid_table_info_u {
       EvlanLkpTpidTableInfo_S m_evlan_lkp_tpid_table_info_s;
       unsigned int data;
}EvlanLkpTpidTableInfo_U;

void cfg_evlan_lkp_table_item(EvlanLkpKey_S* evlan_lkp_key, EvlanLkpRsp_S* evlan_lkp_rsp, EvlanCfg_S* evlan_cfg);

//MPP: evlan_xlt, Table: evlan_xlt
typedef struct evlan_xlt_key_s {
    unsigned char  oport_num;
    unsigned char  old_ovid;
    unsigned char  old_ivid;
}EvlanXltKey_S;

typedef struct evlan_xlt_rsp_s { //not include hit
    unsigned short new_ovid               ;
    unsigned short new_ivid               ;
    unsigned char  new_opri               ;
    unsigned char  new_ipri               ;
    unsigned char  tag_action_profile_ptr ;
}EvlanXltRsp_S;

typedef struct evlan_xlt_table_info_s { //288bit
       unsigned char result_vld               : 1;
       unsigned char tag_action_profile_ptr   : 6;
       unsigned char new_ipri_0               : 1; // result_vld,tag_action_profile_ptr,new_ipri_0 format a char field
       unsigned char new_ipri_2_1             : 2;
       unsigned char new_opri                 : 3;
       unsigned char new_ivid_2_0             : 3; // new_ipri_2_1,new_opri,new_ivid_2_0 format a char field
       unsigned char new_ivid_10_3               ;
       unsigned char new_ivid_11              : 1;
       unsigned char new_ovid_6_0             : 7; // new_ivid_11,new_ovid_6_0 format a char field
       unsigned char new_ovid_11_7            : 5;
       unsigned char old_ivid_2_0             : 3; // new_ovid_11_7,old_ivid_2_0 format a char field
       unsigned char old_ivid_10_3               ;
       unsigned char old_ivid_11              : 1;
       unsigned char old_ovid_6_0             : 7; // old_ivid_11,old_ovid_6_0  format a char field
       unsigned char old_ovid_11_7            : 5;
       unsigned char oport_num_2_0            : 3; // old_ovid_11_7,oport_num_2_0 format a char field
       unsigned char oport_num_5_3            : 3;
       unsigned char rsv0                     : 5; // oport_num_5_3,rsv0 format a char field
       unsigned char rsv1[3]                     ;
}EvlanXltTableInfo_S;

typedef union evlan_xlt_table_info_u {
       EvlanXltTableInfo_S m_evlan_xlt_table_info_s;
       unsigned int data[3];
}EvlanXltTableInfo_U;

void cfg_evlan_xlt_table_item(EvlanXltKey_S* evlan_xlt_key, EvlanXltRsp_S* evlan_xlt_rsp, EvlanCfg_S* evlan_cfg);


//MPP: evlan_lkp, Table: port_tpid
typedef struct evlan_ptpid_key_s {
    unsigned char  tag_action_id;
}EvlanPtpidKey_S;

typedef struct evlan_ptpid_rsp_s { //not include hit and limit drop

    unsigned short inner_tpid ;
    unsigned short outer_tpid ;

}EvlanPtpidRsp_S;

typedef struct evlan_ptpid_table_info_s {
    unsigned short inner_tpid ;
    unsigned short outer_tpid ;
}EvlanPtpidTableInfo_S;

typedef union evlan_ptpid_table_info_u {
       EvlanPtpidTableInfo_S m_evlan_ptpid_table_info_s;
       unsigned int data;
}EvlanPtpidTableInfo_U;

void cfg_evlan_ptpid_table_item(EvlanPtpidKey_S* evlan_ptpid_key, EvlanPtpidRsp_S* evlan_ptpid_rsp, EvlanCfg_S* evlan_cfg);

#endif

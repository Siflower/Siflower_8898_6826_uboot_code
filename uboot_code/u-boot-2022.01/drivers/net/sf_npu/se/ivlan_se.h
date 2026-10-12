#ifndef IVLAN_SE_H
#define IVLAN_SE_H

#include "se_common.h"
#include "tcam_se.h"

//Ivlan CFG:
typedef struct ivlan_cfg_s {
    unsigned char hnat_mode;
}IvlanCfg_S;


//MPP: ivlan_port, Table: iport
typedef struct ivlan_iport_key_s {
    unsigned char  iport_num;
}IvlanIportKey_S;

typedef struct ivlan_iport_rsp_s { //not include hit and limit drop
 
    unsigned char valid               ;
    unsigned char iso_id              ;
    unsigned char default_port        ;
    unsigned char disable_vlan_check  ;
    unsigned char ifiliter_en         ;
    unsigned char use_ivid_as_ovid    ;
    unsigned char vt_miss_drop        ;
    unsigned char vt_en               ;
    unsigned char vfp_based_vid_enable;
    unsigned char vlan_security_mode  ;
    unsigned char vid_zero_handle     ;
    unsigned char pass_mode           ;

}IvlanIportRsp_S;

typedef struct ivlan_iport_table_info_s {

     unsigned char pass_mode           : 1;
     unsigned char vid_zero_handle     : 1;
     unsigned char vlan_security_mode  : 1;
     unsigned char vfp_based_vid_enable: 1;
     unsigned char vt_en               : 1;
     unsigned char vt_miss_drop        : 1;
     unsigned char use_ivid_as_ovid    : 1;
     unsigned char ifiliter_en_0       : 1; //pass_mode,vid_zero_handle,vlan_security_mode,vfp_based_vid_enable,vt_en,vt_miss_drop,use_ivid_as_ovid,ifiliter_en_0 format a char field
     unsigned char ifiliter_en_1       : 1;
     unsigned char disable_vlan_check  : 1;
     unsigned char default_port        : 6; //ifiliter_en_1,disable_vlan_check,default_port format a char field
     unsigned char iso_id              : 6;
     unsigned char valid               : 1;
     unsigned char rsv0                : 1; // iso_id, valid, rsv format a char field
     unsigned char rsv1                   ;
}IvlanIportTableInfo_S;

typedef union ivlan_iport_table_info_u {
       IvlanIportTableInfo_S m_ivlan_iport_table_info_s;
       unsigned int data;
}IvlanIportTableInfo_U;

void cfg_ivlan_iport_table_item(IvlanIportKey_S* ivlan_iport_key, IvlanIportRsp_S* ivlan_iport_rsp, IvlanCfg_S* ivlan_cfg);

//MPP: ivlan_vid, Table: pbv
typedef struct ivlan_pbv_key_s {
    unsigned char  iport_num;
}IvlanPbvKey_S;

typedef struct ivlan_pbv_rsp_s { //not include hit and limit drop
    unsigned char  vld               ;
    unsigned char  transparent_en    ;
    unsigned char  ovid              ;
    unsigned char  ivid              ;
    unsigned char  opri              ;
    unsigned char  ipri              ;
    unsigned char  dt_otag_action    ;
    unsigned char  dt_potag_action   ;
    unsigned char  dt_itag_action    ;
    unsigned char  dt_pitag_action   ;
    unsigned char  sot_otag_action   ;
    unsigned char  sot_potag_action  ;
    unsigned char  sot_itag_action   ;
    unsigned char  sot_pitag_action  ;
    unsigned char  sit_otag_action   ;
    unsigned char  sit_potag_action  ;
    unsigned char  sit_itag_action   ;
    unsigned char  sit_pitag_action  ;
    unsigned char  un_otag_action    ;
    unsigned char  un_potag_action   ;
    unsigned char  un_itag_action    ;
    unsigned char  un_pitag_action   ;
}IvlanPbvRsp_S;

typedef struct ivlan_pbv_table_info_s {

       unsigned char un_pitag_action : 2;
       unsigned char un_itag_action  : 2;
       unsigned char un_potag_action : 2;
       unsigned char un_otag_action  : 2;
       unsigned char sit_pitag_action: 2;
       unsigned char sit_itag_action : 2;
       unsigned char sit_potag_action: 2;
       unsigned char sit_otag_action : 2;
       unsigned char sot_pitag_action: 2;
       unsigned char sot_itag_action : 2;
       unsigned char sot_potag_action: 2;
       unsigned char sot_otag_action : 2;
       unsigned char dt_pitag_action : 2;
       unsigned char dt_itag_action  : 2;
       unsigned char dt_potag_action : 2;
       unsigned char dt_otag_action  : 2;
       unsigned char ipri            : 3;
       unsigned char opri            : 3;
       unsigned char ivid_1_0        : 2; // ipri,opri,ivid_1_0 format a char field
       unsigned char ivid_9_2           ;
       unsigned char ivid_11_10      : 2;
       unsigned char ovid_5_0        : 6; // ivid_11_10, ovid_5_0 format a char field
       unsigned char ovid_11_6       : 6;
       unsigned char transparent_en  : 1;
       unsigned char vld             : 1; // ovid_11_6, transparent_en, vld format a char field
}IvlanPbvTableInfo_S;

typedef union ivlan_pbv_table_info_u {
       IvlanPbvTableInfo_S m_ivlan_pbv_table_info_s;
       unsigned int data[2];
}IvlanPbvTableInfo_U;

void cfg_ivlan_pbv_table_item(IvlanPbvKey_S* ivlan_pbv_key, IvlanPbvRsp_S* ivlan_pbv_rsp, IvlanCfg_S* ivlan_pbv_cfg);

//MPP: ivlan_lkp, Table: lkp
typedef struct ivlan_lkp_key_s {
    unsigned char  ovid;
}IvlanLkpKey_S;

typedef struct ivlan_lkp_rsp_s { //not include hit and limit drop

    uint64_t      port_bitmap       ;
    unsigned char sp_tree_port0     ;
    unsigned char sp_tree_port1     ;
    unsigned char sp_tree_port2     ;
    unsigned char sp_tree_port3     ;
    unsigned char sp_tree_port4     ;
    unsigned char sp_tree_port5     ;
    unsigned char sp_tree_port6     ;
    unsigned char sp_tree_port7     ;
    unsigned char sp_tree_port8     ;
    unsigned char sp_tree_port9     ;
    unsigned char l2_non_ucast_drop ;
    unsigned char l2_non_ucast_tocpu;
    unsigned char l2_miss_drop      ;
    unsigned char l2_miss_tocpu     ;
    unsigned char ipmcv4_en         ;
    unsigned char ipmcv6_en         ;
    unsigned char l2_pfm            ;
    unsigned char learn_disable     ;
}IvlanLkpRsp_S;

typedef struct ivlan_lkp_table_info_s {

       unsigned char result_vld         : 1;
       unsigned char learn_disable      : 1;
       unsigned char l2_pfm             : 2;
       unsigned char ipmcv6_en          : 1;
       unsigned char ipmcv4_en          : 1;
       unsigned char l2_miss_tocpu      : 1;
       unsigned char l2_miss_drop       : 1; //result_vld,learn_disable,l2_pfm,ipmcv6_en,ipmcv4_en,l2_miss_tocpu,l2_miss_drop format a char field
       unsigned char l2_non_ucast_tocpu : 1;
       unsigned char l2_non_ucast_drop  : 1;
       unsigned char sp_tree_port9      : 2;
       unsigned char sp_tree_port8      : 2;
       unsigned char sp_tree_port7      : 2; //l2_non_ucast_tocpu,l2_non_ucast_drop,sp_tree_port9,sp_tree_port8,sp_tree_port7 format a char field
       unsigned char sp_tree_port6      : 2;
       unsigned char sp_tree_port5      : 2;
       unsigned char sp_tree_port4      : 2;
       unsigned char sp_tree_port3      : 2; //sp_tree_port6,sp_tree_port5,sp_tree_port4,sp_tree_port3 format a char field
       unsigned char sp_tree_port2      : 2;
       unsigned char sp_tree_port1      : 2;
       unsigned char sp_tree_port0      : 2;
       unsigned char port_bitmap_1_0    : 2; //sp_tree_port2,sp_tree_port1,sp_tree_port0,port_bitmap_1_0 format a char field
       unsigned int  port_bitmap_33_2      ;
       unsigned char port_bitmap_35_34  : 2;
       unsigned char ovid_5_0           : 6; //port_bitmap_35_34,ovid_5_0 format a char field
       unsigned char ovid_11_6          : 6;
       unsigned char rsv0               : 2; //ovid_11_6,rsv0 format a char field
       unsigned char rsv1[2]               ;
}IvlanLkpTableInfo_S;

typedef union ivlan_lkp_table_info_u {
       IvlanLkpTableInfo_S m_ivlan_lkp_table_info_s;
       unsigned int data[3];
}IvlanLkpTableInfo_U;

void cfg_ivlan_lkp_table_item(IvlanLkpKey_S* ivlan_lkp_key, IvlanLkpRsp_S* ivlan_lkp_rsp, IvlanCfg_S* ivlan_cfg);

//MPP: ivlan_vid, Table: vfp
typedef struct vfp_ipv4_key_s {
    unsigned char  key_mode;
    unsigned char  table_id;
    unsigned char  i_vport ;
    uint64_t       smac    ;
    uint64_t       dmac    ;
    unsigned char  sip[4]  ;
    unsigned char  dip[4]  ;
    unsigned char  protocal;
    unsigned short sport   ;
    unsigned short dport   ;
}VfpIpv4Key_S;


typedef struct vfp_rsp_s { //not include hit
    unsigned char  transparent_en    ;
    unsigned char  new_ovid          ;
    unsigned char  new_ivid          ;
    unsigned char  new_opri          ;
    unsigned char  new_ipri          ;
    unsigned char  dt_otag_action    ;
    unsigned char  dt_potag_action   ;
    unsigned char  dt_itag_action    ;
    unsigned char  dt_pitag_action   ;
    unsigned char  sot_otag_action   ;
    unsigned char  sot_potag_action  ;
    unsigned char  sot_itag_action   ;
    unsigned char  sot_pitag_action  ;
    unsigned char  sit_otag_action   ;
    unsigned char  sit_potag_action  ;
    unsigned char  sit_itag_action   ;
    unsigned char  sit_pitag_action  ;
    unsigned char  un_otag_action    ;
    unsigned char  un_potag_action   ;
    unsigned char  un_itag_action    ;
    unsigned char  un_pitag_action   ;
}VfpRsp_S;

typedef struct vfp_ipv4_table_info_s { //288bit
       unsigned char un_pitag_action : 2;
       unsigned char un_itag_action  : 2;
       unsigned char un_potag_action : 2;
       unsigned char un_otag_action  : 2;
       unsigned char sit_pitag_action: 2;
       unsigned char sit_itag_action : 2;
       unsigned char sit_potag_action: 2;
       unsigned char sit_otag_action : 2;
       unsigned char sot_pitag_action: 2;
       unsigned char sot_itag_action : 2;
       unsigned char sot_potag_action: 2;
       unsigned char sot_otag_action : 2;
       unsigned char dt_pitag_action : 2;
       unsigned char dt_itag_action  : 2;
       unsigned char dt_potag_action : 2;
       unsigned char dt_otag_action  : 2;
       unsigned char new_ipri        : 3;
       unsigned char new_opri        : 3;
       unsigned char new_ivid_1_0    : 2; // new_ipri,new_opri,new_ivid_1_0 format a char field
       unsigned char new_ivid_9_2       ;
       unsigned char new_ivid_11_10  : 2;
       unsigned char new_ovid_5_0    : 6; // new_ivid_11_10, new_ovid_5_0 format a char field
       unsigned char new_ovid_11_6   : 6;
       unsigned char transparent_en  : 1;
       unsigned char rsv0            : 1; // new_ovid_11_6, transparent_en, rsv0 format a char field
       unsigned char rsv1               ;
       unsigned char rsv2               ;
       unsigned char rsv3            : 2;
       unsigned char dport_5_0       : 6; // rsv3, dport_r_0 format a char field
       unsigned char dport_13_6         ;
       unsigned char dport_15_14     : 2;
       unsigned char sport_5_0       : 6; // dport_15_14, sport_5_0 format a char field
       unsigned char sport_13_6         ;
       unsigned char sport_15_14     : 2;
       unsigned char protocal_5_0    : 6; //sport_15_10, protocal_1_0 format a char field
       unsigned char protocal_7_6    : 2;
       unsigned char dip0_5_0        : 6; //protocal_7_6, dip0_5_0 format a char field
       unsigned char dip0_7_6        : 2;
       unsigned char dip1_5_0        : 6; // dip0_7_6, dip1_5_0 format a char field
       unsigned char dip1_7_6        : 2;
       unsigned char dip2_5_0        : 6; // dip1_7_6, dip2_5_0 format a char field
       unsigned char dip2_7_6        : 2;
       unsigned char dip3_5_0        : 6; // dip2_7_6, dip3_5_0 format a char field
       unsigned char dip3_7_6        : 2;
       unsigned char sip0_5_0        : 6; // dip3_7_6, sip0_5_0 format a char field
       unsigned char sip0_7_6        : 2;
       unsigned char sip1_5_0        : 6; // sip0_7_6, sip1_5_0 format a char field
       unsigned char sip1_7_6        : 2;
       unsigned char sip2_5_0        : 6; // sip1_7_6, sip2_5_0 format a char field
       unsigned char sip2_7_6        : 2;
       unsigned char sip3_5_0        : 6; // sip2_7_6, sip3_5_0 format a char field
       unsigned char sip3_7_6        : 2;
       unsigned char dmac_5_0        : 6; // sip3_7_6, dmac_5_0 format a char field
       unsigned char dmac_13_6          ;
       unsigned char dmac_21_14         ;
       unsigned char dmac_29_22         ;
       unsigned char dmac_37_30         ;
       unsigned char dmac_45_38         ;
       unsigned char dmac_47_46      : 2;
       unsigned char smac_5_0        : 6; // dmac_47_46, smac_5_0 format a char field
       unsigned char smac_13_6          ;
       unsigned char smac_21_14         ;
       unsigned char smac_29_22         ;
       unsigned char smac_37_30         ;
       unsigned char smac_45_38         ;
       unsigned char smac_47_46      : 2;
       unsigned char i_vport         : 6; // smac_47_46, i_vport foramt a char field
}VfpIpv4TableInfo_S;

typedef union vfp_ipv4_table_info_u {
       VfpIpv4TableInfo_S m_vfp_ipv4_table_info_s;
       unsigned int data[9];
}VfpIpv4TableInfo_U;

void cfg_vfp_ipv4_table_item(VfpIpv4Key_S* vfp_ipv4_key, VfpRsp_S* vfp_rsp, IvlanCfg_S* ivlan_cfg);


//MPP: ivlan_vid, Table: ivlan_xlt
typedef struct ivlan_xlt_key_s {
    unsigned char  iport_num;
    unsigned char  outer_vid;
    unsigned char  inner_vid;
}IvlanXltKey_S;


typedef struct ivlan_xlt_rsp_s { //not include hit
    unsigned char  transparent_en    ;
    unsigned short new_ovid          ;
    unsigned short new_ivid          ;
    unsigned char  new_opri          ;
    unsigned char  new_ipri          ;
    unsigned char  dt_otag_action    ;
    unsigned char  dt_potag_action   ;
    unsigned char  dt_itag_action    ;
    unsigned char  dt_pitag_action   ;
    unsigned char  sot_otag_action   ;
    unsigned char  sot_potag_action  ;
    unsigned char  sot_itag_action   ;
    unsigned char  sot_pitag_action  ;
    unsigned char  sit_otag_action   ;
    unsigned char  sit_potag_action  ;
    unsigned char  sit_itag_action   ;
    unsigned char  sit_pitag_action  ;
    unsigned char  un_otag_action    ;
    unsigned char  un_potag_action   ;
    unsigned char  un_itag_action    ;
    unsigned char  un_pitag_action   ;
}IvlanXltRsp_S;

typedef struct ivlan_xlt_table_info_s { //288bit
       unsigned char result_vld        : 1;
       unsigned char un_pitag_action   : 2;
       unsigned char un_itag_action    : 2;
       unsigned char un_potag_action   : 2;
       unsigned char un_otag_action_0  : 1; // result_vld,un_pitag_action,un_itag_action,un_potag_action,un_otag_action_0 format a char field
       unsigned char un_otag_action_1  : 1;
       unsigned char sit_pitag_action  : 2;
       unsigned char sit_itag_action   : 2;
       unsigned char sit_potag_action  : 2;
       unsigned char sit_otag_action_0 : 1; // un_otag_action_1,sit_pitag_action,sit_itag_action,sit_potag_action,sit_otag_action_0 format a char field
       unsigned char sit_otag_action_1 : 1;
       unsigned char sot_pitag_action  : 2;
       unsigned char sot_itag_action   : 2;
       unsigned char sot_potag_action  : 2;
       unsigned char sot_otag_action_0 : 1; // sit_otag_action_1,sot_pitag_action,sot_itag_action,sot_potag_action,sot_otag_action_0 format a char field
       unsigned char sot_otag_action_1 : 1;
       unsigned char dt_pitag_action   : 2;
       unsigned char dt_itag_action    : 2;
       unsigned char dt_potag_action   : 2;
       unsigned char dt_otag_action_0  : 1; // sot_otag_action_1,dt_pitag_action,dt_itag_action,dt_potag_action,dt_otag_action_0 format a char field
       unsigned char dt_otag_action_1  : 1;
       unsigned char new_ipri          : 3;
       unsigned char new_opri          : 3;
       unsigned char new_ivid_0        : 1; // dt_otag_action_1,new_ipri,new_opri,new_ivid_0 format a char field
       unsigned char new_ivid_8_1         ;
       unsigned char new_ivid_11_9     : 3;
       unsigned char new_ovid_4_0      : 5; // new_ivid_11_9,new_ovid_4_0 format a char field
       unsigned char new_ovid_11_5     : 7;
       unsigned char transparent_en    : 1; // new_ovid_11_5,transparen format a char field
       unsigned char inner_vid_7_0        ;
       unsigned char inner_vid_11_8    : 4;
       unsigned char outer_vid_3_0     : 4; // inner_vid_11_8,outer_vid_3_0  format a char field
       unsigned char outer_vid_11_4       ;
       unsigned char iport_num         : 6;
       unsigned char rsv0              : 2; // iport_num,rsv0 format a char field
}IvlanXltTableInfo_S;

typedef union ivlan_xlt_table_info_u {
       IvlanXltTableInfo_S m_ivlan_xlt_table_info_s;
       unsigned int data[3];
}IvlanXltTableInfo_U;

void cfg_ivlan_xlt_table_item(IvlanXltKey_S* ivlan_xlt_key, IvlanXltRsp_S* ivlan_xlt_rsp, IvlanCfg_S* ivlan_cfg);

#endif

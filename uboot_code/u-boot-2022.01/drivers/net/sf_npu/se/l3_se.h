#ifndef L3_SE_H
#define L3_SE_H

#include "se_common.h"
#include "tcam_se.h"

//MPP: L3P0, Table: l3uc/mc*g, ipv6
typedef struct l3_uc_ipv6_key_s {
    unsigned char  key_mode;
    unsigned char  table_id;
    unsigned short ovid    ;
    unsigned char  dip[16]  ;
}L3UcIpv6Key_S;

typedef struct l3_uc_ipv6_table_info_s { //72bit
        unsigned char  next_hop_ptr_7_0     ;
        unsigned char  next_hop_ptr_10_8 : 3;
        unsigned char  oport_id_4_0      : 5; //next_hop_ptr_10_8, oport_id_4_0 format a char field
        unsigned char  oport_id_5        : 1;
        unsigned char  intf_id           : 6;
        unsigned char  rsv2              : 1;  //oport_id_5,intf_id,rsv2 format a char field
        unsigned char  rsv1[15]             ;
        unsigned char  rsv0              : 4;
        unsigned char  dip0_3_0          : 4; //rsv0, dip0_3_0 format a char field
        unsigned char  dip0_7_4          : 4;
        unsigned char  dip1_3_0          : 4; //dip0_7_4, dip1_3_0 format a char field
        unsigned char  dip1_7_4          : 4;
        unsigned char  dip2_3_0          : 4; //dip1_7_4, dip2_3_0 format a char field
        unsigned char  dip2_7_4          : 4;
        unsigned char  dip3_3_0          : 4; //dip2_7_4, dip3_3_0 format a char field
        unsigned char  dip3_7_4          : 4;

        unsigned char  dip4_3_0          : 4; //dip3_7_4, dip4_3_0 format a char field
        unsigned char  dip4_7_4          : 4;
        unsigned char  dip5_3_0          : 4; //dip4_7_4, dip5_3_0 format a char field
        unsigned char  dip5_7_4          : 4;
        unsigned char  dip6_3_0          : 4; //dip5_7_4, dip6_3_0 format a char field
        unsigned char  dip6_7_4          : 4;
        unsigned char  dip7_3_0          : 4; //dip6_7_4, dip7_3_0 format a char field
        unsigned char  dip7_7_4          : 4;

        unsigned char  dip8_3_0          : 4; //dip7_7_4, dip8_3_0 format a char field
        unsigned char  dip8_7_4          : 4;
        unsigned char  dip9_3_0          : 4; //dip8_7_4, dip9_3_0 format a char field
        unsigned char  dip9_7_4          : 4;
        unsigned char  dip10_3_0         : 4; //dip9_7_4, dip10_3_0 format a char field
        unsigned char  dip10_7_4         : 4;
        unsigned char  dip11_3_0         : 4; //dip10_7_4, dip11_3_0 format a char field
        unsigned char  dip11_7_4         : 4; 

        unsigned char  dip12_3_0         : 4; //dip11_7_4, dip12_3_0 format a char field
        unsigned char  dip12_7_4         : 4;
        unsigned char  dip13_3_0         : 4; //dip12_7_4, dip13_3_0 format a char field
        unsigned char  dip13_7_4         : 4;
        unsigned char  dip14_3_0         : 4; //dip13_7_4, dip14_3_0 format a char field
        unsigned char  dip14_7_4         : 4;
        unsigned char  dip15_3_0         : 4; //dip14_7_4, dip15_3_0 format a char field
        unsigned char  dip15_7_4         : 4; 

        unsigned char  ovid_3_0          : 4; //dip15_7_4, ovid_3_0 format a char field
        unsigned char  ovid_11_4            ;
}L3UcIpv6TableInfo_S;

//MPP: L3P0, Table: l3uc/mc*g, ipv4
typedef struct l3_uc_ipv4_key_s {
    unsigned char  key_mode;
    unsigned char  table_id;
    unsigned short ovid    ;
    unsigned char  dip[4]  ;
}L3UcIpv4Key_S;


typedef struct l3_uc_rsp_s { //not include hit
    unsigned char  intf_id      ;
    unsigned char  oport_id     ;
    unsigned short next_hop_ptr ;
}L3UcRsp_S;

typedef struct l3_cfg_s {
    unsigned char hnat_mode; //tmp, need to change
}L3Cfg_S;

typedef struct l3_uc_ipv4_table_info_s { //72bit
        unsigned char  next_hop_ptr_7_0     ;
        unsigned char  next_hop_ptr_10_8 : 3;
        unsigned char  oport_id_4_0      : 5; //next_hop_ptr_10_8, oport_id_4_0 format a char field
        unsigned char  oport_id_5        : 1;
        unsigned char  intf_id           : 6;
        unsigned char  rsv2              : 1;  //oport_id_5,intf_id,rsv2 format a char field
        unsigned char  rsv0              : 4;
        unsigned char  dip0_3_0          : 4; //rsv0, dip0_3_0 format a char field
        unsigned char  dip0_7_4          : 4;
        unsigned char  dip1_3_0          : 4; //dip0_7_4, dip1_3_0 format a char field
        unsigned char  dip1_7_4          : 4;
        unsigned char  dip2_3_0          : 4; //dip1_7_4, dip2_3_0 format a char field
        unsigned char  dip2_7_4          : 4;
        unsigned char  dip3_3_0          : 4; //dip2_7_4, dip3_3_0 format a char field
        unsigned char  dip3_7_4          : 4;
        unsigned char  ovid_3_0          : 4; //dip3_7_4, ovid_3_0 format a char field
        unsigned char  ovid_11_4            ;
        unsigned char  rsv1[3]              ;
}L3UcIpv4TableInfo_S;

typedef union l3_uc_ipv4_table_info_u {
       L3UcIpv4TableInfo_S m_l3_uc_ipv4_table_info_s;
       unsigned int data[3];
}L3UcIpv4TableInfo_U;

typedef union l3_uc_ipv6_table_info_u {
       L3UcIpv6TableInfo_S m_l3_uc_ipv6_table_info_s;
       unsigned int data[9];
}L3UcIpv6TableInfo_U;

void cfg_l3_uc_ipv4_table_item(L3UcIpv4Key_S* l3_uc_ipv4_key, L3UcRsp_S* l3_uc_rsp, L3Cfg_S* L3_cfg);

void cfg_l3_uc_ipv6_table_item(L3UcIpv6Key_S* l3_uc_ipv6_key, L3UcRsp_S* l3_uc_rsp, L3Cfg_S* L3_cfg);

//MPP: L3P0, Table: l3mcsg
typedef struct l3_mcsg_ipv4_key_s {
    unsigned char  key_mode;
    unsigned char  table_id;
    unsigned short ovid    ;
    unsigned char  sip[4]  ;
    unsigned char  dip[4]  ;
}L3McsgIpv4Key_S;


typedef struct l3_mcsg_rsp_s { //not include hit
    unsigned char  intf_id      ;
    unsigned char  iport_id     ;
    uint64_t       oport_bitmap ;
}L3McsgRsp_S;

typedef struct l3_mcsg_ipv4_table_info_s { //144bit
        unsigned char  intf_id           : 6;
        unsigned char  oport_bitmap_1_0  : 2; //intf_id,oport_bitmap_1_0 format a char field
        unsigned char  oport_bitmap_9_2     ;
        unsigned char  oport_bitmap_17_10   ;
        unsigned char  oport_bitmap_25_18   ;
        unsigned char  oport_bitmap_33_26   ;
        unsigned char  oport_bitmap_35_34: 2;
        unsigned char  iport_id          : 6; //oport_bitmap_35_34,iport_id format a char field
        unsigned char  rsv0                 ;
        unsigned char  rsv1                 ;
        unsigned char  rsv2              : 4;
        unsigned char  dip0_3_0          : 4; //rsv2, dip0_3_0 format a char field
        unsigned char  dip0_7_4          : 4;
        unsigned char  dip1_3_0          : 4; //dip0_7_4, dip1_3_0 format a char field
        unsigned char  dip1_7_4          : 4;
        unsigned char  dip2_3_0          : 4; //dip1_7_4, dip2_3_0 format a char field
        unsigned char  dip2_7_4          : 4;
        unsigned char  dip3_3_0          : 4; //dip2_7_4, dip3_3_0 format a char field
        unsigned char  dip3_7_4          : 4;
        unsigned char  sip0_3_0          : 4; //dip3_7_4, sip0_3_0 format a char field
        unsigned char  sip0_7_4          : 4;
        unsigned char  sip1_3_0          : 4; //sip0_7_4, sip1_3_0 format a char field
        unsigned char  sip1_7_4          : 4;
        unsigned char  sip2_3_0          : 4; //sip1_7_4, sip2_3_0 format a char field
        unsigned char  sip2_7_4          : 4;
        unsigned char  sip3_3_0          : 4; //sip2_7_4, sip3_3_0 format a char field
        unsigned char  sip3_7_4          : 4;
        unsigned char  ovid_3_0          : 4; //sip3_7_4, ovid_3_0 format a char field
        unsigned char  ovid_11_4            ;
        unsigned char  rsv3[2]              ;
}L3McsgIpv4TableInfo_S;

typedef union l3_mcsg_ipv4_table_info_u {
       L3McsgIpv4TableInfo_S m_l3_mcsg_ipv4_table_info_s;
       unsigned int data[5];
}L3McsgIpv4TableInfo_U;

void cfg_l3_mcsg_ipv4_table_item(L3McsgIpv4Key_S* l3_mcsg_ipv4_key, L3McsgRsp_S* l3_mcsg_rsp, L3Cfg_S* L3_cfg);

#endif

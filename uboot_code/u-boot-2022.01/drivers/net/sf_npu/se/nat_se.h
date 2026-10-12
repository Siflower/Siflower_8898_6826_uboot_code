#ifndef NAT_SE_H
#define NAT_SE_H

#include "se_common.h"

typedef struct nat_key_s {
    unsigned short pkt_len; //14bit
    unsigned char  l3_flag; //1bit   0:PV4  1:PV6
    unsigned char  dnat_flag;  //1bit 1: dnat
    unsigned char  frag_flag;  //2bit 0:NO FRG 1:F FRG 2: INT FRG 3:L FRG
    unsigned int   pkt_id   ;     //32bit V4:16bit  V6:32bit
    unsigned char  l4_flag  ; 
    unsigned short sport;
    unsigned char  sip[16];
    unsigned short dport  ;
    unsigned char  dip[16];
}NatKey_S;

typedef struct nat_hash_key_s {
    unsigned char  hashkey[37];
}NatHashKey_S;

typedef struct nat_rsp_s {
    unsigned char  repl_pri_en   ; //1bit
    unsigned char  repl_pri      ; //3bit
    unsigned char  smac_index    ; //6bit
    unsigned short dmac_index    ; //11bit
    unsigned short repl_port     ; //16bit
    unsigned char  repl_ip[16]   ; //128bit
}NatRsp_S;

typedef struct nat_cfg_s {
    unsigned char hnat_mode;
    unsigned char elkp_table_size;
    unsigned char elkp_v4_acs_times;
    unsigned int  elkp_snat_base_addr;
    unsigned int  elkp_dnat_base_addr;
}NatCfg_S;

//typedef struct nat_tb_op_reg_s {
//    unsigned int host_mgt_req_busy:1 ; //31
//    unsigned int rsv0:6 ; //30:25
//    unsigned int host_mgt_req_opcode:1 ; //24
//    unsigned int rsv1:5 ; //23:19
//    unsigned int host_mgt_req_id:3 ; //18:16
//    unsigned int rsv2:3 ; //15:13
//    unsigned int host_mgt_req_addr:13 ; //12:0
//}NatTbOpReg_s;

//ipv4
typedef struct napt_table_info_ipv4_s {
        unsigned char  public_ip[4]         ;
        unsigned char  public_port[2]       ;
        unsigned char  private_ip[4]        ;
        unsigned char  private_port[2]      ;
        unsigned char  router_ip[4]         ;
        unsigned char  router_port[2]       ;
        unsigned char  l4_type           :1 ;
        unsigned char  valid             :1 ;
        unsigned char  rtmac_index       :6 ; //l4_type, valid, rtmac_index format a char field
        unsigned char  primac_index_7_0     ;
        unsigned char  primac_index_10_8 : 3;
        unsigned char  pubmac_index_4_0  : 5; //primac_index_10_8, pubmac_index_4_0 format a char field
        unsigned char  pubmac_index_10_5 : 6;
        unsigned char  repl_pri_en       : 1;
        unsigned char  repl_pri_0        : 1; //pubmac_index_10_5, repl_pri_en, repl_pri_0 format a char field
        unsigned char  repl_pri_2_1      : 2;
        unsigned char  stat_en           : 1;
        unsigned char  stat_index_4_0    : 5; //repl_pri_2_1,stat_en,stat_index_4_0 format a char field
        unsigned char  stat_index_8_5    : 4; 
        unsigned char  spl_en            : 1;
        unsigned char  spl_index_2_0     : 3; //stat_index_8_5,spl_en,spl_index_2_0 format a char field
        unsigned char  spl_index_7_3     : 5;
        unsigned char  rsv0              : 3; //spl_index_7_3,rsv format a char field
        unsigned char  rsv1[7]              ;
}NaptTableInfoIpv4_s;

typedef union napt_table_info_ipv4_u {
       NaptTableInfoIpv4_s m_napt_table_info_ipv4_s;
       unsigned int data[8];
}NaptTableInfoIpv4_u;

//ipv6
typedef struct napt_table_info_ipv6_s {
        unsigned char  public_ip[16]        ;
        unsigned char  public_port[2]       ;
        unsigned char  private_ip[16]       ;
        unsigned char  private_port[2]      ;
        unsigned char  router_ip[16]        ;
        unsigned char  router_port[2]       ;
        unsigned char  l4_type           :1 ;
        unsigned char  valid             :1 ;
        unsigned char  rtmac_index       :6 ; //l4_type, valid, rtmac_index format a char field
        unsigned char  primac_index_7_0     ;
        unsigned char  primac_index_10_8 : 3;
        unsigned char  pubmac_index_4_0  : 5; //primac_index_10_8, pubmac_index_4_0 format a char field
        unsigned char  pubmac_index_10_5 : 6;
        unsigned char  repl_pri_en       : 1;
        unsigned char  repl_pri_0        : 1; //pubmac_index_10_5, repl_pri_en, repl_pri_0 format a char field
        unsigned char  repl_pri_2_1      : 2;
        unsigned char  stat_en           : 1;
        unsigned char  stat_index_4_0    : 5; //repl_pri_2_1,stat_en,stat_index_4_0 format a char field
        unsigned char  stat_index_8_5    : 4; 
        unsigned char  spl_en            : 1;
        unsigned char  spl_index_2_0     : 3; //stat_index_8_5,spl_en,spl_index_2_0 format a char field
        unsigned char  spl_index_7_3     : 5;
        unsigned char  ipv6_valid        : 1;
        unsigned char  rsv0              : 2; //spl_index_7_3,ipv6_valid,rsv format a char field
        unsigned char  rsv1[3]              ;
}NaptTableInfoIpv6_s;

typedef union napt_table_info_ipv6_u {
       NaptTableInfoIpv6_s m_napt_table_info_ipv6_s;
       unsigned int data[16];
}NaptTableInfoIpv6_u;


void cfg_nat_table_item(NatKey_S* nat_key, NatRsp_S* nat_rsp, NatCfg_S* nat_cfg);

#endif

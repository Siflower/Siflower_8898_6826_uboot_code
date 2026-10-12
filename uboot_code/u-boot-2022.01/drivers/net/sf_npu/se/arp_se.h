#ifndef ARP_SE_H
#define ARP_SE_H

#include "se_common.h"

//MPP:Arp, Cfg
typedef struct arp_cfg_s {
    unsigned char hnat_mode;
}ArpCfg_S;

//MPP:Arp, Table: intf
typedef struct intf_key_s {
    unsigned char  intf_id;
}IntfKey_S;

typedef struct intf_rsp_s { //not include hit and limit drop
    unsigned char  pppoe_en  ;
    uint64_t       pppoe_hdr ;
    uint64_t       smac      ;
    unsigned short ovid      ;
}IntfRsp_S;

typedef struct intf_table_info_s {
     unsigned char ovid_7_0          ;
     unsigned char ovid_11_8      : 4;
     unsigned char smac_3_0       : 4; // ovid_11_8, smac_3_0 format a char field
     unsigned char smac_11_4         ;
     unsigned char smac_19_12        ;
     unsigned char smac_27_20        ;
     unsigned char smac_35_28        ;
     unsigned char smac_43_36        ;
     unsigned char smac_47_44     : 4;
     unsigned char pppoe_hdr_3_0  : 4; // smac_47_44, pppoe_hdr_3_0 format a char field
     unsigned char pppoe_hdr_11_4    ;
     unsigned char pppoe_hdr_19_12   ;
     unsigned char pppoe_hdr_27_20   ;
     unsigned char pppoe_hdr_35_28   ;
     unsigned char pppoe_hdr_43_36   ;
     unsigned char pppoe_hdr_51_44   ;
     unsigned char pppoe_hdr_59_52   ;
     unsigned char pppoe_hdr_63_60: 4;
     unsigned char pppoe_en       : 1;
     unsigned char hit            : 1;
     unsigned char rsv            : 2; //pppoe_hdr_63_60, pppoe_en, rsv format a char field
}IntfTableInfo_S;

typedef union intf_table_info_u {
       IntfTableInfo_S m_intf_table_info_s;
       unsigned int data[4];
}IntfTableInfo_U;

void cfg_intf_table_item(IntfKey_S* intf_key, IntfRsp_S* intf_rsp, ArpCfg_S* arp_cfg);


//MPP:Arp, Table: arp
typedef struct arp_key_s {
    unsigned short  next_hop_ptr;
    unsigned short  pkt_len;
}ArpKey_S;

typedef struct arp_rsp_s { //not include hit and limit drop
    unsigned short sta_index     ;
    unsigned char  repeater_index;
    uint64_t       dmac          ;
    unsigned short ovid          ;
}ArpRsp_S;

void cfg_arp_table_item(ArpKey_S* arp_key, ArpRsp_S* arp_rsp, ArpCfg_S* arp_cfg);

#endif

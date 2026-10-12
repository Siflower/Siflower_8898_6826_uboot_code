#ifndef L2_SE_H
#define L2_SE_H

#include "se_common.h"


typedef struct l2_key_s {
    //unsigned short pkt_len; //14bit
    unsigned char  ovid; //12
    unsigned char  mac[6];
}L2Key_S;

typedef struct l2_hash_key_s {
    unsigned char  hashkey[8];
}L2HashKey_S;

typedef struct l2_rsp_s { //not include hit and limit drop
    uint64_t       port_bitmap   ; //36bit
    unsigned short sta_index     ; //10bit
    unsigned char  repeater_index; //4bit
    unsigned char  l3_en         ; //1bit
    unsigned char  da_cml        ; //2bit
    unsigned char  sa_cml        ; //2bit
}L2Rsp_S;

typedef struct l2_cfg_s {
    unsigned char hnat_mode;
}L2Cfg_S;

typedef struct mac_table_info_s {
        unsigned char  result_mib_id_7_0    ; //separate a char field
        unsigned char  result_mib_id_8   :1 ;
        unsigned char  result_mib_en     :3 ;
        unsigned char  result_spl_id_3_0 :4 ; //result_mib_id_8,result_mib_en,result_spl_id_3_0 format a char field
        unsigned char  result_spl_id_7_4 :4 ;
        unsigned char  result_spl_en     :1 ;
        unsigned char  result_age_en     :1 ;
        unsigned char  result_dcml       :2 ; //result_spl_id_7_4,result_spl_en,result_age_en,result_dcml format a char field
        unsigned char  result_scml       :2 ;
        unsigned char  result_l3_en      :1 ;
        unsigned char  result_repeater_id:4 ;
        unsigned char  result_sta_id_0   :1 ; //result_scml, result_l3_en, result_repeater_id, result_sta_id_0 format a char field
        unsigned char  result_sta_id_8_1    ; //separate a char field
        unsigned char  result_sta_id_9   :1 ;
        unsigned char  result_bitmap_6_0 :7 ; //result_sta_id_9, result_bitmap_6_0 format a char field
        unsigned char  result_bitmap_14_7   ; //separate a char field
        unsigned char  result_bitmap_22_15  ; //separate a char field
        unsigned char  result_bitmap_30_23  ; //separate a char field
        unsigned char  result_bitmap_35_31 :5 ;
        unsigned char  result_mac_2_0      :3 ; //result_bitmap_35_31, result_mac_2_0 format a char field
        unsigned char  result_mac_10_3        ; //separate a char field
        unsigned char  result_mac_18_11       ; //separate a char field
        unsigned char  result_mac_26_19       ; //separate a char field
        unsigned char  result_mac_34_27       ; //separate a char field
        unsigned char  result_mac_42_35       ; //separate a char field
        unsigned char  result_mac_47_43    :5 ;
        unsigned char  result_vid_2_0      :3 ; //result_mac_47_43, result_vid_2_0 format a char field
        unsigned char  result_vid_10_3        ; //separate a char field
        unsigned char  result_vid_11       :1 ;
        unsigned char  result_vld          :1 ;
        unsigned char  rsv0                :6 ; //result_vid_11, result_vld, rsv0 format a char field
        unsigned char  rsv1[2]                ;
}MacTableInfo_S;

typedef union mac_table_info_u {
       MacTableInfo_S m_mac_table_info_s;
       unsigned int data[5];
}MacTableInfo_U;

void cfg_l2_table_item(L2Key_S* l2_key, L2Rsp_S* l2_rsp, L2Cfg_S* L2_cfg);

#endif

#ifndef ACL_SE_H
#define ACL_SE_H

#include "se_common.h"
#include "tcam_se.h"

//MPP: ACL, Table: ACL, Mode: 7
typedef struct acl_mode7_key_s {
    unsigned char  key_mode       ;
    unsigned char  table_id       ;
    unsigned short mf_type        ;
    unsigned char  mf_iport_id    ;
    unsigned char  mf_oport_id    ;
    unsigned int   mf_user_frag   ;
}AclMode7Key_S;

typedef struct acl_mode7_rsp_s { //not include hit
    unsigned char  priority_en     ;
    unsigned char  priority        ;
    unsigned char  action          ;
    unsigned char  dscp_replace_en ;
    unsigned char  new_id          ;
}AclModeRsp_S;

typedef struct acl_mode_cfg_s {
    unsigned char hnat_mode; //tmp, need to change
}AclModeCfg_S;

typedef struct acl_mode7_table_info_s { //72bit
        unsigned char  new_id            : 6;
        unsigned char  dscp_replace_en   : 1;
        unsigned char  action_0          : 1; // new_id,dscp_replace_en,action_0 format a char field
        unsigned char  action_2_1        : 2;
        unsigned char  priority          : 3;
        unsigned char  priority_en       : 1;
        unsigned char  rsv0              : 2; // action_2_1,priority,priority_en,rsv0  format a char field
        unsigned char  mf_type_7_0          ;
        unsigned char  mf_type_11_8      : 4;
        unsigned char  mf_iport_id_3_0   : 4; // mf_type_11_8,mf_iport_id_3_0 format a char field
        unsigned char  mf_iport_id_5_4   : 2;
        unsigned char  mf_oport_id       : 6; // mf_iport_id_5_4,mf_oport_id format a char field
        unsigned char  mf_user_frag_7_0     ;
        unsigned char  mf_user_frag_15_8    ;
        unsigned char  mf_user_frag_23_16   ;
        unsigned char  mf_user_frag_31_24   ;
        unsigned char  rsv1[3]              ;
}AclMode7TableInfo_S;

typedef union acl_mode7_table_info_u {
       AclMode7TableInfo_S m_acl_mode7_table_info_s;
       unsigned int data[3];
}AclMode7TableInfo_U;

void cfg_acl_mode7_table_item(AclMode7Key_S* acl_mode7_key, AclModeRsp_S* acl_mode_rsp, AclModeCfg_S* acl_mode_cfg, int is_iacl);

#endif

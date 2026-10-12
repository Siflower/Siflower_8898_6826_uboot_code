#ifndef SPL_SE_H
#define SPL_SE_H

#include "se_common.h"

//Table: SPL
typedef struct spl_key_s {
    unsigned int item_index ;
    unsigned int cnt        ; //30bit
    unsigned int credit     ; //24bit
}SplKey_S;

typedef struct spl_table_info_s {
     unsigned char credit_7_0        ;
     unsigned char credit_15_8       ;
     unsigned char credit_23_16      ;
     unsigned char cnt_7_0           ;
     unsigned char cnt_15_8          ;
     unsigned char cnt_23_16         ;
     unsigned char cnt_29_24      : 5;
     unsigned char rsv0           : 3;
     unsigned char rsv1              ;
}SplTableInfo_S;

typedef union spl_table_info_u {
       SplTableInfo_S m_spl_table_info_s;
       unsigned int data[2];
}SplTableInfo_U;

void cfg_intf_spl_table_item(SplKey_S* spl_key);

void cfg_ivlan_spl_table_item(SplKey_S* spl_key);

#endif

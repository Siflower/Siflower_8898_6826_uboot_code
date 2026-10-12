#ifndef TCAM_SE_H
#define TCAM_SE_H

#include "se_common.h"

#define VFP_TCAM_BLK  (0x0)
#define L3P0_TCAM_BLK (0x1)
#define L3P1_TCAM_BLK (0x2)
#define EACL_TCAM_BLK (0x4)
#define IACL_TCAM_BLK (0x3)

#define TCAM_BLK_RAM_ID(BLK_ID, RAM_INDEX) ((BLK_ID)*9+(RAM_INDEX))
#define TCAM_BLK_MODE_ID(BLK_ID) ((BLK_ID)*9+8)

typedef struct blk_table_item_s {
    unsigned char blk_id       ;
             int  table_id     ;
             int  key_mode     ;  //key_mode_decode
    unsigned char slice_bitmap ;
    unsigned char empty_slice  ;
}BlkTableItem_S;

typedef struct blk_table_s{
    BlkTableItem_S items[32]; //real 64, but even item store key, odd item store mask
}BlkTable_S;

typedef struct key_loc_info_s {
    int blk_id      ;
    int item_index  ;
    int slice_index ;
}KeyLocInfo_S;

void init_blk_tables(BlkTable_S* m_blk_tables);

void get_blk_index(unsigned char table_id, unsigned char key_mode, unsigned char blk_id, BlkTable_S* m_blk_tables, KeyLocInfo_S* m_key_loc_info);

#endif

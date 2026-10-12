#ifndef TCAM_SE_C
#define TCAM_SE_C

#include "tcam_se.h"

BlkTable_S blk_tables[8];

static int init_flag = 0;

void init_blk_tables(BlkTable_S* m_blk_tables){
    int i = 0;
    int j = 0;

    if(init_flag == 0) {
        for(i=0; i<8; i++) {
            for(j=0; j<32; j++) {
                m_blk_tables[i].items[j].blk_id = i;
                m_blk_tables[i].items[j].table_id = -1;
                m_blk_tables[i].items[j].key_mode = -1;
                m_blk_tables[i].items[j].slice_bitmap = 0x0;
                m_blk_tables[i].items[j].empty_slice  = 0x0;
            }
        }
        init_flag = 1;
    }

    #if SE_DEBUG_INFO
     {
         int i = 0;
         int j = 0;
         for(i=1; i<2; i++) {
             for(j=0; j<2; j++) {
                 printf("m_blk_tables[%0d].items[%0d].blk_id       = %0d\n", i, j, m_blk_tables[i].items[j].blk_id      );
                 printf("m_blk_tables[%0d].items[%0d].table_id     = %0d\n", i, j, m_blk_tables[i].items[j].table_id    );
                 printf("m_blk_tables[%0d].items[%0d].key_mode     = %0d\n", i, j, m_blk_tables[i].items[j].key_mode    );
                 printf("m_blk_tables[%0d].items[%0d].slice_bitmap = %0d\n", i, j, m_blk_tables[i].items[j].slice_bitmap);
                 printf("m_blk_tables[%0d].items[%0d].empty_slice  = %0d\n", i, j, m_blk_tables[i].items[j].empty_slice );
             }
         }
     }
     #endif
}

void get_blk_index(unsigned char table_id, unsigned char key_mode, unsigned char blk_id, BlkTable_S* m_blk_tables, KeyLocInfo_S* m_key_loc_info) {
    int j = 0;
    int key_mode_decode = 0;

    if(key_mode == 0) {
        key_mode_decode = 1;
    }
    else if(key_mode == 1) {
        key_mode_decode = 2;
    }
    else if(key_mode == 2) {
        key_mode_decode = 4;
    }
    else if(key_mode == 3) {
        key_mode_decode = 8;
    }

    #if SE_DEBUG_INFO
     {
         int i = 0;
         int j = 0;
         for(i=1; i<2; i++) {
             for(j=0; j<2; j++) {
                 printf("22 m_blk_tables[%0d].items[%0d].blk_id       = %0d\n", i, j, m_blk_tables[i].items[j].blk_id      );
                 printf("22 m_blk_tables[%0d].items[%0d].table_id     = %0d\n", i, j, m_blk_tables[i].items[j].table_id    );
                 printf("22 m_blk_tables[%0d].items[%0d].key_mode     = %0d\n", i, j, m_blk_tables[i].items[j].key_mode    );
                 printf("22 m_blk_tables[%0d].items[%0d].slice_bitmap = %0d\n", i, j, m_blk_tables[i].items[j].slice_bitmap);
                 printf("22 m_blk_tables[%0d].items[%0d].empty_slice  = %0d\n", i, j, m_blk_tables[i].items[j].empty_slice );
             }
         }
         printf("blk_id  = %0d\n", blk_id );
     }
     #endif

    m_key_loc_info->blk_id = -1;
    m_key_loc_info->item_index = -1;
    m_key_loc_info->slice_index = -1;

    for(j=0; j<32; j++) {
        if( (m_blk_tables[blk_id].items[j].table_id == -1) && (m_blk_tables[blk_id].items[j].key_mode == -1) ) {

            //update blk_tables
            m_blk_tables[blk_id].items[j].table_id = table_id;
            m_blk_tables[blk_id].items[j].key_mode = key_mode_decode;

            //update key_loc_info
            m_key_loc_info->blk_id = blk_id;
            m_key_loc_info->item_index = j;
            m_key_loc_info->slice_index = m_blk_tables[blk_id].items[j].empty_slice;

            //update empty_slice in blk_tables
            m_blk_tables[blk_id].items[j].empty_slice += key_mode_decode;

            break;
        }
        else { //table_item have been occupy
            if( (m_blk_tables[blk_id].items[j].table_id != table_id) || (m_blk_tables[blk_id].items[j].key_mode != key_mode_decode) ) {
                continue;
            }
            else {
                if(m_blk_tables[blk_id].items[j].empty_slice + key_mode_decode > 8) { //no enough loc to store key and mask
                    continue;
                }
                else {
                    //no need update blk_tables
                    //m_blk_tables[blk_id].items[j].table_id = table_id;
                    //m_blk_tables[blk_id].items[j].key_mode = key_mode_decode;

                    //update key_loc_info
                    m_key_loc_info->blk_id      = blk_id;
                    m_key_loc_info->item_index  = j;
                    m_key_loc_info->slice_index = m_blk_tables[blk_id].items[j].empty_slice;

                    //update empty_slice in blk_tables
                    m_blk_tables[blk_id].items[j].empty_slice += key_mode_decode;

                    break;
                }
            }
        }
    }
     #if SE_DEBUG_INFO
     printf("11m_key_loc_info.blk_id      = %0d\n", m_key_loc_info->blk_id     );
     printf("11m_key_loc_info.item_index  = %0d\n", m_key_loc_info->item_index );
     printf("11m_key_loc_info.slice_index = %0d\n", m_key_loc_info->slice_index);
     #endif

    //if(m_key_loc_info->blk_id == -1) {
    //    c_uvm_fatal(0, "Tcam Key can not find loc in blk_id:%0d", blk_id);
    //}
}

#endif

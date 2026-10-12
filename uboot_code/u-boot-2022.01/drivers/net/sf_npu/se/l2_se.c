#ifndef L2_SE_C
#define L2_SE_C

#include "l2_se.h"
#include "se_common.h"
#include <string.h>

int mac_table_index = 0;

void gen_l2_hash_key(L2Key_S* l2_key, L2HashKey_S* l2_hash_key) {

    memset(l2_hash_key, 0x0, sizeof(L2HashKey_S));

    l2_hash_key->hashkey[8-0-1] = l2_key->mac[0];
    l2_hash_key->hashkey[8-1-1] = l2_key->mac[1];
    l2_hash_key->hashkey[8-2-1] = l2_key->mac[2];
    l2_hash_key->hashkey[8-3-1] = l2_key->mac[3];
    l2_hash_key->hashkey[8-4-1] = l2_key->mac[4];
    l2_hash_key->hashkey[8-5-1] = l2_key->mac[5];
    l2_hash_key->hashkey[8-6-1] = (l2_key->ovid&0xff);
    l2_hash_key->hashkey[8-7-1] = ((l2_key->ovid&0xff)>>8);

    //l2_hash_key->hashkey[0] = l2_key->dmac[0];
    //l2_hash_key->hashkey[1] = l2_key->dmac[1];
    //l2_hash_key->hashkey[2] = l2_key->dmac[2];
    //l2_hash_key->hashkey[3] = l2_key->dmac[3];
    //l2_hash_key->hashkey[4] = l2_key->dmac[4];
    //l2_hash_key->hashkey[5] = l2_key->dmac[5];
    //l2_hash_key->hashkey[6] = (l2_key->ovid&0xff);
    //l2_hash_key->hashkey[7] = ((l2_key->ovid&0xff)>>8);

#if SE_DEBUG_INFO
    {
        int i=0;
        for(i=0; i<8; i++) {
            printf("l2_hash_key->hashkey[%0d] = 0x%0x", i, l2_hash_key->hashkey[i]);
        }
    }
#endif
}

void cfg_l2_table_item(L2Key_S* l2_key, L2Rsp_S* l2_rsp, L2Cfg_S* L2_cfg) {

     int i = 0;

     L2HashKey_S m_l2_hash_key;
     unsigned short hash_value[10];
     unsigned short hash_index[10];
     uint64_t mac = 0x0;

     MacTableInfo_U m_mac_table_info_u;

     gen_l2_hash_key(l2_key, &m_l2_hash_key);

#if SE_DEBUG_INFO
    {
        int i=0;
        printf("sizeof(L2HashKey_S) = %ld", sizeof(L2HashKey_S));
        for(i=0; i<8; i++) {
            printf("m_l2_hash_key->hashkey[%0d] = 0x%0x", i, m_l2_hash_key.hashkey[i]);
        }
    }
#endif

     hash_value[0] = crc16(&m_l2_hash_key.hashkey[0], sizeof(L2HashKey_S), 0);
     hash_value[1] = crc16(&m_l2_hash_key.hashkey[0], sizeof(L2HashKey_S), 1);
     hash_value[2] = crc16(&m_l2_hash_key.hashkey[0], sizeof(L2HashKey_S), 2);
     hash_value[3] = crc16(&m_l2_hash_key.hashkey[0], sizeof(L2HashKey_S), 3);
     hash_value[4] = crc16(&m_l2_hash_key.hashkey[0], sizeof(L2HashKey_S), 4);
     hash_value[5] = crc16(&m_l2_hash_key.hashkey[0], sizeof(L2HashKey_S), 5);
     hash_value[6] = crc16(&m_l2_hash_key.hashkey[0], sizeof(L2HashKey_S), 6);
     hash_value[7] = crc16(&m_l2_hash_key.hashkey[0], sizeof(L2HashKey_S), 7);
     hash_value[8] = crc16(&m_l2_hash_key.hashkey[0], sizeof(L2HashKey_S), 8);
     hash_value[9] = crc16(&m_l2_hash_key.hashkey[0], sizeof(L2HashKey_S), 9);

     hash_index[0] = get_data16(hash_value[0], 0, 9);
     hash_index[1] = get_data16(hash_value[0], 0, 8);
     hash_index[2] = get_data16(hash_value[0], 0, 8);
     hash_index[3] = get_data16(hash_value[0], 0, 7);
     hash_index[4] = get_data16(hash_value[0], 0, 7);
     hash_index[5] = get_data16(hash_value[0], 0, 6);
     hash_index[6] = get_data16(hash_value[0], 0, 6);
     hash_index[7] = get_data16(hash_value[0], 0, 6);
     hash_index[7] = get_data16(hash_value[0], 0, 5);
     hash_index[7] = get_data16(hash_value[0], 0, 5);

     NAT_SE_WR_REG(SE_TB_WRDATA00_RGT_REG_ADDR, mac_table_index);
     NAT_SE_WR_REG(SE_TB_OP_ADDR_RGT_REG_ADDR, (WRITE_TABLE<<TB_OP_ADDR_RGT_HOST_MGT_REQ_OPCODE_FIELD_OFFSET)+
                                               (L2_SE_HASH0_TABLE<<TB_OP_ADDR_RGT_HOST_MGT_REQ_ID_FIELD_OFFSET)+
                                               (hash_index[0]<<TB_OP_ADDR_RGT_HOST_MGT_REQ_ADDR_FIELD_OFFSET)
                  );

     for(i=0; i<5; i++) {
         m_mac_table_info_u.data[i] = 0x0;
     }
     m_mac_table_info_u.m_mac_table_info_s.result_vld = 1;

     m_mac_table_info_u.m_mac_table_info_s.result_vid_2_0  = get_data16(l2_key->ovid, 0, 3);
     m_mac_table_info_u.m_mac_table_info_s.result_vid_10_3 = get_data16(l2_key->ovid, 3, 8);
     m_mac_table_info_u.m_mac_table_info_s.result_vid_11   = get_data16(l2_key->ovid, 11, 1);

     mac = (((uint64_t)l2_key->mac[0])<< 0) +
           (((uint64_t)l2_key->mac[1])<< 8) +
           (((uint64_t)l2_key->mac[2])<<16) +
           (((uint64_t)l2_key->mac[3])<<24) +
           (((uint64_t)l2_key->mac[4])<<32) +
           (((uint64_t)l2_key->mac[5])<<40) ;
     m_mac_table_info_u.m_mac_table_info_s.result_mac_2_0   = get_data64(mac, 0,  3);
     m_mac_table_info_u.m_mac_table_info_s.result_mac_10_3  = get_data64(mac, 3, 8);
     m_mac_table_info_u.m_mac_table_info_s.result_mac_18_11 = get_data64(mac, 11, 8);
     m_mac_table_info_u.m_mac_table_info_s.result_mac_26_19 = get_data64(mac, 19, 8);
     m_mac_table_info_u.m_mac_table_info_s.result_mac_34_27 = get_data64(mac, 27, 8);
     m_mac_table_info_u.m_mac_table_info_s.result_mac_42_35 = get_data64(mac, 35, 8);
     m_mac_table_info_u.m_mac_table_info_s.result_mac_47_43 = get_data64(mac, 43, 5);

     m_mac_table_info_u.m_mac_table_info_s.result_bitmap_6_0   = get_data64(l2_rsp->port_bitmap, 0 , 7);
     m_mac_table_info_u.m_mac_table_info_s.result_bitmap_14_7  = get_data64(l2_rsp->port_bitmap, 7 , 8);
     m_mac_table_info_u.m_mac_table_info_s.result_bitmap_22_15 = get_data64(l2_rsp->port_bitmap, 15, 8);
     m_mac_table_info_u.m_mac_table_info_s.result_bitmap_30_23 = get_data64(l2_rsp->port_bitmap, 23, 8);
     m_mac_table_info_u.m_mac_table_info_s.result_bitmap_35_31 = get_data64(l2_rsp->port_bitmap, 31, 5);

     m_mac_table_info_u.m_mac_table_info_s.result_sta_id_0   = get_data16(l2_rsp->sta_index, 0, 1);
     m_mac_table_info_u.m_mac_table_info_s.result_sta_id_8_1 = get_data16(l2_rsp->sta_index, 1, 8);
     m_mac_table_info_u.m_mac_table_info_s.result_sta_id_9   = get_data16(l2_rsp->sta_index, 9, 1);

     m_mac_table_info_u.m_mac_table_info_s.result_repeater_id   = l2_rsp->repeater_index;

     m_mac_table_info_u.m_mac_table_info_s.result_l3_en   = l2_rsp->l3_en;
     m_mac_table_info_u.m_mac_table_info_s.result_dcml    = l2_rsp->da_cml;
     m_mac_table_info_u.m_mac_table_info_s.result_scml    = l2_rsp->sa_cml;

#if SE_DEBUG_INFO
    {
        int i= 0;
        for(i=0; i<6; i++) {
            printf("l2_key->mac[%0d] = 0x%0x", i, l2_key->mac[i]);
        }
        printf("mac = 0x%llx", mac);
        printf("m_mac_table_info_u.m_mac_table_info_s.result_mac_2_0 = 0x%x", m_mac_table_info_u.m_mac_table_info_s.result_mac_2_0);
        printf("m_mac_table_info_u.m_mac_table_info_s.result_mac_10_3  = 0x%x", m_mac_table_info_u.m_mac_table_info_s.result_mac_10_3 );
        printf("m_mac_table_info_u.m_mac_table_info_s.result_mac_18_11 = 0x%x", m_mac_table_info_u.m_mac_table_info_s.result_mac_18_11);
        printf("m_mac_table_info_u.m_mac_table_info_s.result_mac_26_19 = 0x%x", m_mac_table_info_u.m_mac_table_info_s.result_mac_26_19);
        printf("m_mac_table_info_u.m_mac_table_info_s.result_mac_34_27 = 0x%x", m_mac_table_info_u.m_mac_table_info_s.result_mac_34_27);
        printf("m_mac_table_info_u.m_mac_table_info_s.result_mac_42_35 = 0x%x", m_mac_table_info_u.m_mac_table_info_s.result_mac_42_35);
        printf("m_mac_table_info_u.m_mac_table_info_s.result_mac_47_43 = 0x%x", m_mac_table_info_u.m_mac_table_info_s.result_mac_47_43);
        printf("l2_key->ovid = 0x%0x", l2_key->ovid);
        printf("m_mac_table_info_u.m_mac_table_info_s.result_vid_2_0 = 0x%0x", m_mac_table_info_u.m_mac_table_info_s.result_vid_2_0);
        printf("m_mac_table_info_u.m_mac_table_info_s.result_vid_10_3 = 0x%0x", m_mac_table_info_u.m_mac_table_info_s.result_vid_10_3);
        printf("m_mac_table_info_u.m_mac_table_info_s.result_vid_11 = 0x%0x", m_mac_table_info_u.m_mac_table_info_s.result_vid_11);
        for(i=0; i<5; i++) {
            printf("m_mac_table_info_u.data[%0d] = 0x%0x", i, m_mac_table_info_u.data[i]);
        }
    }
#endif



     SE_WR_REG(SE_TB_WRDATA00_RGT_REG_ADDR, m_mac_table_info_u.data[0]);
     SE_WR_REG(SE_TB_WRDATA01_RGT_REG_ADDR, m_mac_table_info_u.data[1]);
     SE_WR_REG(SE_TB_WRDATA02_RGT_REG_ADDR, m_mac_table_info_u.data[2]);
     SE_WR_REG(SE_TB_WRDATA03_RGT_REG_ADDR, m_mac_table_info_u.data[3]);
     SE_WR_REG(SE_TB_WRDATA04_RGT_REG_ADDR, m_mac_table_info_u.data[4]);
     SE_WR_REG(SE_TB_OP_ADDR_RGT_REG_ADDR, (WRITE_TABLE<<TB_OP_ADDR_RGT_HOST_MGT_REQ_OPCODE_FIELD_OFFSET)+
                                               (ARP_SE_MAC_TABLE<<TB_OP_ADDR_RGT_HOST_MGT_REQ_ID_FIELD_OFFSET)+
                                               (mac_table_index<<TB_OP_ADDR_RGT_HOST_MGT_REQ_ADDR_FIELD_OFFSET)
                  );

     mac_table_index++;

     //enable mac_table
     update_reg(SE_CONFIG2_RGT_REG_ADDR, CONFIG2_RGT_MAC_TABLE_VLD_FIELD_OFFSET, CONFIG2_RGT_MAC_TABLE_VLD_FIELD_SIZE, 1);
}

#endif

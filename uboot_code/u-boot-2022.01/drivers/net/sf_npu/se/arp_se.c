#ifndef ARP_SE_C
#define ARP_SE_C

#include "arp_se.h"
#include "l2_se.h"
#include "se_common.h"
#include <string.h>

//MPP:Arp, Table: intf
void cfg_intf_table_item(IntfKey_S* intf_key, IntfRsp_S* intf_rsp, ArpCfg_S* arp_cfg) {

     int i = 0;

     IntfTableInfo_U m_intf_table_info_u;

     for(i=0; i<4; i++) {
         m_intf_table_info_u.data[i] = 0x0;
     }
     m_intf_table_info_u.m_intf_table_info_s.ovid_7_0        = get_data16(intf_rsp->ovid,  0, 8);
     m_intf_table_info_u.m_intf_table_info_s.ovid_11_8       = get_data16(intf_rsp->ovid,  8, 4);
     m_intf_table_info_u.m_intf_table_info_s.smac_3_0        = get_data64(intf_rsp->smac,  0, 4);
     m_intf_table_info_u.m_intf_table_info_s.smac_11_4       = get_data64(intf_rsp->smac,  4, 8);
     m_intf_table_info_u.m_intf_table_info_s.smac_19_12      = get_data64(intf_rsp->smac, 12, 8);
     m_intf_table_info_u.m_intf_table_info_s.smac_27_20      = get_data64(intf_rsp->smac, 20, 8);
     m_intf_table_info_u.m_intf_table_info_s.smac_35_28      = get_data64(intf_rsp->smac, 28, 8);
     m_intf_table_info_u.m_intf_table_info_s.smac_43_36      = get_data64(intf_rsp->smac, 36, 8);
     m_intf_table_info_u.m_intf_table_info_s.smac_47_44      = get_data64(intf_rsp->smac, 44, 4);
     m_intf_table_info_u.m_intf_table_info_s.pppoe_hdr_3_0   = get_data64(intf_rsp->pppoe_hdr,  0, 4);
     m_intf_table_info_u.m_intf_table_info_s.pppoe_hdr_11_4  = get_data64(intf_rsp->pppoe_hdr,  4, 8);
     m_intf_table_info_u.m_intf_table_info_s.pppoe_hdr_19_12 = get_data64(intf_rsp->pppoe_hdr, 12, 8);
     m_intf_table_info_u.m_intf_table_info_s.pppoe_hdr_27_20 = get_data64(intf_rsp->pppoe_hdr, 20, 8);
     m_intf_table_info_u.m_intf_table_info_s.pppoe_hdr_35_28 = get_data64(intf_rsp->pppoe_hdr, 28, 8);
     m_intf_table_info_u.m_intf_table_info_s.pppoe_hdr_43_36 = get_data64(intf_rsp->pppoe_hdr, 36, 8);
     m_intf_table_info_u.m_intf_table_info_s.pppoe_hdr_51_44 = get_data64(intf_rsp->pppoe_hdr, 44, 8);
     m_intf_table_info_u.m_intf_table_info_s.pppoe_hdr_59_52 = get_data64(intf_rsp->pppoe_hdr, 52, 8);
     m_intf_table_info_u.m_intf_table_info_s.pppoe_hdr_63_60 = get_data64(intf_rsp->pppoe_hdr, 60, 4);
     m_intf_table_info_u.m_intf_table_info_s.pppoe_en        = intf_rsp->pppoe_en;
     m_intf_table_info_u.m_intf_table_info_s.hit             = 1;

     SE_WR_REG(SE_TB_WRDATA00_RGT_REG_ADDR, m_intf_table_info_u.data[0]);
     SE_WR_REG(SE_TB_WRDATA01_RGT_REG_ADDR, m_intf_table_info_u.data[1]);
     SE_WR_REG(SE_TB_WRDATA02_RGT_REG_ADDR, m_intf_table_info_u.data[2]);
     SE_WR_REG(SE_TB_WRDATA03_RGT_REG_ADDR, m_intf_table_info_u.data[3]);
     SE_WR_REG(SE_TB_OP_ADDR_RGT_REG_ADDR, (WRITE_TABLE<<TB_OP_ADDR_RGT_HOST_MGT_REQ_OPCODE_FIELD_OFFSET)+
                                           (ARP_SE_INTF_DIRECT_TABLE<<TB_OP_ADDR_RGT_HOST_MGT_REQ_ID_FIELD_OFFSET)+
                                           (intf_key->intf_id<<TB_OP_ADDR_RGT_HOST_MGT_REQ_ADDR_FIELD_OFFSET)
                  );

     //enable intf_table
     update_reg(SE_CONFIG2_RGT_REG_ADDR, CONFIG2_RGT_INTF_TABLE_VLD_FIELD_OFFSET, CONFIG2_RGT_INTF_TABLE_VLD_FIELD_SIZE, 1);
}

void cfg_arp_table_item(ArpKey_S* arp_key, ArpRsp_S* arp_rsp, ArpCfg_S* arp_cfg) {

     int i = 0;
     MacTableInfo_U m_mac_table_info_u;

     for(i=0; i<5; i++) {
         m_mac_table_info_u.data[i] = 0x0;
     }
     m_mac_table_info_u.m_mac_table_info_s.result_vld = 1;

     m_mac_table_info_u.m_mac_table_info_s.result_vid_2_0  = get_data16(arp_rsp->ovid, 0, 3);
     m_mac_table_info_u.m_mac_table_info_s.result_vid_10_3 = get_data16(arp_rsp->ovid, 3, 8);
     m_mac_table_info_u.m_mac_table_info_s.result_vid_11   = get_data16(arp_rsp->ovid, 11, 1);

     m_mac_table_info_u.m_mac_table_info_s.result_mac_2_0   = get_data64(arp_rsp->dmac, 0,  3);
     m_mac_table_info_u.m_mac_table_info_s.result_mac_10_3  = get_data64(arp_rsp->dmac, 3, 8);
     m_mac_table_info_u.m_mac_table_info_s.result_mac_18_11 = get_data64(arp_rsp->dmac, 11, 8);
     m_mac_table_info_u.m_mac_table_info_s.result_mac_26_19 = get_data64(arp_rsp->dmac, 19, 8);
     m_mac_table_info_u.m_mac_table_info_s.result_mac_34_27 = get_data64(arp_rsp->dmac, 27, 8);
     m_mac_table_info_u.m_mac_table_info_s.result_mac_42_35 = get_data64(arp_rsp->dmac, 35, 8);
     m_mac_table_info_u.m_mac_table_info_s.result_mac_47_43 = get_data64(arp_rsp->dmac, 43, 5);

     m_mac_table_info_u.m_mac_table_info_s.result_sta_id_0   = get_data16(arp_rsp->sta_index, 0, 1);
     m_mac_table_info_u.m_mac_table_info_s.result_sta_id_8_1 = get_data16(arp_rsp->sta_index, 1, 8);
     m_mac_table_info_u.m_mac_table_info_s.result_sta_id_9   = get_data16(arp_rsp->sta_index, 9, 1);
     m_mac_table_info_u.m_mac_table_info_s.result_repeater_id   = arp_rsp->repeater_index;

#if SE_DEBUG_INFO
    {
        int i= 0;
        printf("mac = 0x%llx", arp_rsp->dmac);
        printf("rst_mac_2_0 = 0x%x", m_mac_table_info_u.m_mac_table_info_s.result_mac_2_0);
        printf("rst_mac_10_3  = 0x%x", m_mac_table_info_u.m_mac_table_info_s.result_mac_10_3 );
        printf("rst_mac_18_11 = 0x%x", m_mac_table_info_u.m_mac_table_info_s.result_mac_18_11);
        printf("rst_mac_26_19 = 0x%x", m_mac_table_info_u.m_mac_table_info_s.result_mac_26_19);
        printf("rst_mac_34_27 = 0x%x", m_mac_table_info_u.m_mac_table_info_s.result_mac_34_27);
        printf("rst_mac_42_35 = 0x%x", m_mac_table_info_u.m_mac_table_info_s.result_mac_42_35);
        printf("rst_mac_47_43 = 0x%x", m_mac_table_info_u.m_mac_table_info_s.result_mac_47_43);
        printf("rst_vid_2_0 = 0x%0x", m_mac_table_info_u.m_mac_table_info_s.result_vid_2_0);
        printf("rEst_vid_10_3 = 0x%0x", m_mac_table_info_u.m_mac_table_info_s.result_vid_10_3);
        printf("rst_vid_11 = 0x%0x", m_mac_table_info_u.m_mac_table_info_s.result_vid_11);
        for(i=0; i<5; i++) {
            printf("mac_tb.data[%0d] = 0x%0x", i, m_mac_table_info_u.data[i]);
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
                                               (arp_key->next_hop_ptr<<TB_OP_ADDR_RGT_HOST_MGT_REQ_ADDR_FIELD_OFFSET)
                  );

}

#endif

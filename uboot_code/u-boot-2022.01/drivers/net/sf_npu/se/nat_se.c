#ifndef NAT_SE_C
#define NAT_SE_C

#include <string.h>
#include "se_common.h"
#include "nat_se.h"

int napt_index = 0;

void gen_nat_hash_key(NatKey_S* nat_key, NatHashKey_S* nat_hash_key, NatCfg_S* nat_cfg) {
    memset(nat_hash_key, 0x0, sizeof(NatHashKey_S));

    if(nat_cfg->hnat_mode == 0x0)
    {
        if(nat_key->dnat_flag)
        {
            nat_hash_key->hashkey[37-15-1] = nat_key->dip[15];
            nat_hash_key->hashkey[37-14-1] = nat_key->dip[14];
            nat_hash_key->hashkey[37-13-1] = nat_key->dip[13];
            nat_hash_key->hashkey[37-12-1] = nat_key->dip[12];
            nat_hash_key->hashkey[37-11-1] = nat_key->dip[11];
            nat_hash_key->hashkey[37-10-1] = nat_key->dip[10];
            nat_hash_key->hashkey[37-9 -1] = nat_key->dip[9 ];
            nat_hash_key->hashkey[37-8 -1] = nat_key->dip[8 ];
            nat_hash_key->hashkey[37-7 -1] = nat_key->dip[7 ];
            nat_hash_key->hashkey[37-6 -1] = nat_key->dip[6 ];
            nat_hash_key->hashkey[37-5 -1] = nat_key->dip[5 ];
            nat_hash_key->hashkey[37-4 -1] = nat_key->dip[4 ];
            nat_hash_key->hashkey[37-3 -1] = nat_key->dip[3 ];
            nat_hash_key->hashkey[37-2 -1] = nat_key->dip[2 ];
            nat_hash_key->hashkey[37-1 -1] = nat_key->dip[1 ];
            nat_hash_key->hashkey[37-0 -1] = nat_key->dip[0 ];
        }
        else
        {
            nat_hash_key->hashkey[37-33-1] = nat_key->sip[15];
            nat_hash_key->hashkey[37-32-1] = nat_key->sip[14];
            nat_hash_key->hashkey[37-31-1] = nat_key->sip[13];
            nat_hash_key->hashkey[37-30-1] = nat_key->sip[12];
            nat_hash_key->hashkey[37-29-1] = nat_key->sip[11];
            nat_hash_key->hashkey[37-28-1] = nat_key->sip[10];
            nat_hash_key->hashkey[37-27-1] = nat_key->sip[9 ];
            nat_hash_key->hashkey[37-26-1] = nat_key->sip[8 ];
            nat_hash_key->hashkey[37-25-1] = nat_key->sip[7 ];
            nat_hash_key->hashkey[37-24-1] = nat_key->sip[6 ];
            nat_hash_key->hashkey[37-23-1] = nat_key->sip[5 ];
            nat_hash_key->hashkey[37-22-1] = nat_key->sip[4 ];
            nat_hash_key->hashkey[37-21-1] = nat_key->sip[3 ];
            nat_hash_key->hashkey[37-20-1] = nat_key->sip[2 ];
            nat_hash_key->hashkey[37-19-1] = nat_key->sip[1 ];
            nat_hash_key->hashkey[37-18-1] = nat_key->sip[0 ];
        }
    #if SE_DEBUG_INFO
		int i = 0;
        for(i=0; i<4; i++)
        {
            printf("nat_key.dip[%0d] = 0x%0x", i, nat_key->dip[i]);
        }
        for(i=0; i<4; i++)
        {
            printf("nat_key.sip[%0d] = 0x%0x", i, nat_key->sip[i]);
        }
    #endif
    }
    else if(nat_cfg->hnat_mode == 0x1)
    {
        nat_hash_key->hashkey[37-36-1] = nat_key->l4_flag;

        nat_hash_key->hashkey[37-35-1] = ((nat_key->sport&0xFF00)>>8);
        nat_hash_key->hashkey[37-34-1] = nat_key->sport&0xFF;

        nat_hash_key->hashkey[37-33-1] = nat_key->sip[15];
        nat_hash_key->hashkey[37-32-1] = nat_key->sip[14];
        nat_hash_key->hashkey[37-31-1] = nat_key->sip[13];
        nat_hash_key->hashkey[37-30-1] = nat_key->sip[12];
        nat_hash_key->hashkey[37-29-1] = nat_key->sip[11];
        nat_hash_key->hashkey[37-28-1] = nat_key->sip[10];
        nat_hash_key->hashkey[37-27-1] = nat_key->sip[9 ];
        nat_hash_key->hashkey[37-26-1] = nat_key->sip[8 ];
        nat_hash_key->hashkey[37-25-1] = nat_key->sip[7 ];
        nat_hash_key->hashkey[37-24-1] = nat_key->sip[6 ];
        nat_hash_key->hashkey[37-23-1] = nat_key->sip[5 ];
        nat_hash_key->hashkey[37-22-1] = nat_key->sip[4 ];
        nat_hash_key->hashkey[37-21-1] = nat_key->sip[3 ];
        nat_hash_key->hashkey[37-20-1] = nat_key->sip[2 ];
        nat_hash_key->hashkey[37-19-1] = nat_key->sip[1 ];
        nat_hash_key->hashkey[37-18-1] = nat_key->sip[0 ];

        nat_hash_key->hashkey[37-17-1] = ((nat_key->dport&0xFF00)>>8);
        nat_hash_key->hashkey[37-16-1] = nat_key->dport&0xFF;

        nat_hash_key->hashkey[37-15-1] = nat_key->dip[15];
        nat_hash_key->hashkey[37-14-1] = nat_key->dip[14];
        nat_hash_key->hashkey[37-13-1] = nat_key->dip[13];
        nat_hash_key->hashkey[37-12-1] = nat_key->dip[12];
        nat_hash_key->hashkey[37-11-1] = nat_key->dip[11];
        nat_hash_key->hashkey[37-10-1] = nat_key->dip[10];
        nat_hash_key->hashkey[37-9 -1] = nat_key->dip[9 ];
        nat_hash_key->hashkey[37-8 -1] = nat_key->dip[8 ];
        nat_hash_key->hashkey[37-7 -1] = nat_key->dip[7 ];
        nat_hash_key->hashkey[37-6 -1] = nat_key->dip[6 ];
        nat_hash_key->hashkey[37-5 -1] = nat_key->dip[5 ];
        nat_hash_key->hashkey[37-4 -1] = nat_key->dip[4 ];
        nat_hash_key->hashkey[37-3 -1] = nat_key->dip[3 ];
        nat_hash_key->hashkey[37-2 -1] = nat_key->dip[2 ];
        nat_hash_key->hashkey[37-1 -1] = nat_key->dip[1 ];
        nat_hash_key->hashkey[37-0 -1] = nat_key->dip[0 ];
    }
}

//void gen_nat_napt_rsp(NatKey_S* nat_key, NatHashKey_S* nat_hash_key) {
//
//    memset(nat_hash_key, 0x0, sizeof(NatHashKey_S));
//
//
//    //dnat_flag=0, hnat_mode=3'b000
//    nat_hash_key->hashkey[18] = nat_key->sip[0];
//    nat_hash_key->hashkey[19] = nat_key->sip[1];
//    nat_hash_key->hashkey[20] = nat_key->sip[2];
//    nat_hash_key->hashkey[21] = nat_key->sip[3];
//
//}



void cfg_nat_table_ipv4_item(NatKey_S* nat_key, NatRsp_S* nat_rsp, NatCfg_S* nat_cfg) {

     int i = 0;

     NatHashKey_S m_nat_hash_key;
     unsigned short hash_value[8];
     unsigned short hash_index[8];

     NaptTableInfoIpv4_u m_napt_table_info_ipv4_u;

     gen_nat_hash_key(nat_key, &m_nat_hash_key, nat_cfg);

    #if SE_DEBUG_INFO
     for(i=0; i<37; i=i+1) {
         printf("m_nat_hash_key.hashkey[%0d] = 0x%0x", i, m_nat_hash_key.hashkey[i]);
     }
    #endif

     hash_value[0] = crc16(&m_nat_hash_key.hashkey[0], sizeof(NatHashKey_S), 0);
     hash_value[1] = crc16(&m_nat_hash_key.hashkey[0], sizeof(NatHashKey_S), 1);
     hash_value[2] = crc16(&m_nat_hash_key.hashkey[0], sizeof(NatHashKey_S), 2);
     hash_value[3] = crc16(&m_nat_hash_key.hashkey[0], sizeof(NatHashKey_S), 3);
     hash_value[4] = crc16(&m_nat_hash_key.hashkey[0], sizeof(NatHashKey_S), 4);
     hash_value[5] = crc16(&m_nat_hash_key.hashkey[0], sizeof(NatHashKey_S), 5);
     hash_value[6] = crc16(&m_nat_hash_key.hashkey[0], sizeof(NatHashKey_S), 6);
     hash_value[7] = crc16(&m_nat_hash_key.hashkey[0], sizeof(NatHashKey_S), 7);

     #if SE_DEBUG_INFO
     for(i=0; i<8; i=i+1) {
         printf("hash_value[%0d] = 0x%0x", i, hash_value[i]);
     }
     #endif

     hash_index[0] = get_data16(hash_value[1], 0, 12);
     hash_index[1] = get_data16(hash_value[0], 0, 11);
     hash_index[2] = get_data16(hash_value[1], 0, 11);
     hash_index[3] = get_data16(hash_value[0], 0, 10);
     hash_index[4] = get_data16(hash_value[1], 0, 10);
     hash_index[5] = get_data16(hash_value[0], 0, 10);
     hash_index[6] = get_data16(hash_value[1], 0, 9 );
     hash_index[7] = get_data16(hash_value[0], 0, 9 );

     #if SE_DEBUG_INFO
     for(i=0; i<8; i=i+1) {
         printf("hash_index[%0d] = 0x%0x", i, hash_index[i]);
     }
     #endif

     NAT_SE_WR_REG(SE_NAT_TB_WRDATA00_RGT_REG_ADDR, napt_index);
     if(nat_key->dnat_flag)
     {
         NAT_SE_WR_REG(SE_NAT_OP_ADDR_RGT_REG_ADDR, (WRITE_TABLE<<NAT_OP_ADDR_RGT_HOST_MGT_REQ_OPCODE_FIELD_OFFSET)+
                                                   (DNAT_HASH0_TABLE<<NAT_OP_ADDR_RGT_HOST_MGT_REQ_ID_FIELD_OFFSET)+
                                                   (hash_index[0]<<NAT_OP_ADDR_RGT_HOST_MGT_REQ_ADDR_FIELD_OFFSET));
     }
     else
     {
         NAT_SE_WR_REG(SE_NAT_OP_ADDR_RGT_REG_ADDR, (WRITE_TABLE<<NAT_OP_ADDR_RGT_HOST_MGT_REQ_OPCODE_FIELD_OFFSET)+
                                                   (SNAT_HASH0_TABLE<<NAT_OP_ADDR_RGT_HOST_MGT_REQ_ID_FIELD_OFFSET)+
                                                   (hash_index[0]<<NAT_OP_ADDR_RGT_HOST_MGT_REQ_ADDR_FIELD_OFFSET));
     }

     for(i=0; i<8; i++) {
         m_napt_table_info_ipv4_u.data[i] = 0x0;
     }
     //dnat_flag=0, hant_mode=3'h000
     if(nat_cfg->hnat_mode == 0x0)
     {
         if(nat_key->dnat_flag)
         {
             m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.private_ip[0] = nat_rsp->repl_ip[0];
             m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.private_ip[1] = nat_rsp->repl_ip[1];
             m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.private_ip[2] = nat_rsp->repl_ip[2];
             m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.private_ip[3] = nat_rsp->repl_ip[3];
         }
         else
         {
             m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.private_ip[0] = nat_key->sip[0];
             m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.private_ip[1] = nat_key->sip[1];
             m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.private_ip[2] = nat_key->sip[2];
             m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.private_ip[3] = nat_key->sip[3];
         }
     }
     else if(nat_cfg->hnat_mode == 0x1)
     {
         if(nat_key->dnat_flag)
         {
             m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.private_ip[0] = nat_rsp->repl_ip[0];
             m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.private_ip[1] = nat_rsp->repl_ip[1];
             m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.private_ip[2] = nat_rsp->repl_ip[2];
             m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.private_ip[3] = nat_rsp->repl_ip[3];
             m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.private_port[0] = nat_rsp->repl_port&0xFF;
             m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.private_port[1] = ((nat_rsp->repl_port&0xFF00)>>8);
         }
         else
         {
             m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.private_ip[0] = nat_key->sip[0];
             m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.private_ip[1] = nat_key->sip[1];
             m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.private_ip[2] = nat_key->sip[2];
             m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.private_ip[3] = nat_key->sip[3];
             m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.private_port[0] = nat_key->sport&0xFF;
             m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.private_port[1] = ((nat_key->sport&0xFF00)>>8);
         }
     }
     m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.l4_type  = nat_key->l4_flag;

    if(nat_cfg->hnat_mode == 0x0)
    {
        if(nat_key->dnat_flag)
        {
            m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.router_ip[0] = nat_key->dip[0];
            m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.router_ip[1] = nat_key->dip[1];
            m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.router_ip[2] = nat_key->dip[2];
            m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.router_ip[3] = nat_key->dip[3];
        }
        else
        {
            m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.router_ip[0] = nat_rsp->repl_ip[0];
            m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.router_ip[1] = nat_rsp->repl_ip[1];
            m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.router_ip[2] = nat_rsp->repl_ip[2];
            m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.router_ip[3] = nat_rsp->repl_ip[3];
        }
    }
    else if(nat_cfg->hnat_mode == 0x1)
    {
        if(nat_key->dnat_flag)
        {
            //key_srch_flag & (key_v4_dip == v4_router_ip0) & (key_dport == v4_router_port0) & (key_v4_sip == v4_public_ip0) & (key_sport == v4_public_port0) & (key_l4_type == v4_l4_type0);
            m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.router_ip[0] = nat_key->dip[0];
            m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.router_ip[1] = nat_key->dip[1];
            m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.router_ip[2] = nat_key->dip[2];
            m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.router_ip[3] = nat_key->dip[3];
            m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.router_port[0] = nat_key->dport&0xFF;
            m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.router_port[1] = ((nat_key->dport&0xFF00)>>8);
            m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.public_ip[0] = nat_key->sip[0];
            m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.public_ip[1] = nat_key->sip[1];
            m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.public_ip[2] = nat_key->sip[2];
            m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.public_ip[3] = nat_key->sip[3];
            m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.public_port[0] = nat_key->sport&0xFF;
            m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.public_port[1] = ((nat_key->sport&0xFF00)>>8);
        }
        else
        {
            // key_srch_flag & (key_v4_dip == v4_public_ip0) & (key_dport == v4_public_port0) & (key_v4_sip == v4_private_ip0) & (key_sport == v4_private_port0) & (key_l4_type == v4_l4_type0);
            m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.public_ip[0] = nat_key->dip[0];
            m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.public_ip[1] = nat_key->dip[1];
            m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.public_ip[2] = nat_key->dip[2];
            m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.public_ip[3] = nat_key->dip[3];
            m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.public_port[0] = nat_key->dport&0xFF;
            m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.public_port[1] = ((nat_key->dport&0xFF00)>>8);
            m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.router_ip[0] = nat_rsp->repl_ip[0];
            m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.router_ip[1] = nat_rsp->repl_ip[1];
            m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.router_ip[2] = nat_rsp->repl_ip[2];
            m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.router_ip[3] = nat_rsp->repl_ip[3];
            m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.router_port[0] = nat_rsp->repl_port&0xFF;
            m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.router_port[1] = ((nat_rsp->repl_port&0xFF00)>>8);
        }
    }

     m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.repl_pri_en   = nat_rsp->repl_pri_en;
     m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.repl_pri_0    = nat_rsp->repl_pri & 0x1;
     m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.repl_pri_2_1  = ((nat_rsp->repl_pri & 0x6)>>1);

     if(nat_key->dnat_flag == 1) { //dnat
         m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.rtmac_index       = nat_rsp->smac_index;
         m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.primac_index_7_0  = (nat_rsp->dmac_index&0xff);
         m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.primac_index_10_8 = ((nat_rsp->dmac_index&0x700)>>8);
     }
     else { //snat
         m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.rtmac_index       = nat_rsp->smac_index;
         m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.pubmac_index_4_0  = (nat_rsp->dmac_index&0x1f);
         m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.pubmac_index_10_5 = ((nat_rsp->dmac_index&0x7e0)>>5);
     }

     m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.valid  = 1;

     #if SE_DEBUG_INFO
     for(i=0; i<8; i=i+1) {
         printf("m_napt_table_info_ipv4_u.data[%0d] = 0x%0x", i, m_napt_table_info_ipv4_u.data[i]);
     }
     #endif

     NAT_SE_WR_REG(SE_NAT_TB_WRDATA00_RGT_REG_ADDR, m_napt_table_info_ipv4_u.data[0]);
     NAT_SE_WR_REG(SE_NAT_TB_WRDATA01_RGT_REG_ADDR, m_napt_table_info_ipv4_u.data[1]);
     NAT_SE_WR_REG(SE_NAT_TB_WRDATA02_RGT_REG_ADDR, m_napt_table_info_ipv4_u.data[2]);
     NAT_SE_WR_REG(SE_NAT_TB_WRDATA03_RGT_REG_ADDR, m_napt_table_info_ipv4_u.data[3]);
     NAT_SE_WR_REG(SE_NAT_TB_WRDATA04_RGT_REG_ADDR, m_napt_table_info_ipv4_u.data[4]);
     NAT_SE_WR_REG(SE_NAT_TB_WRDATA05_RGT_REG_ADDR, m_napt_table_info_ipv4_u.data[5]);
     NAT_SE_WR_REG(SE_NAT_TB_WRDATA06_RGT_REG_ADDR, m_napt_table_info_ipv4_u.data[6]);
     NAT_SE_WR_REG(SE_NAT_TB_WRDATA07_RGT_REG_ADDR, m_napt_table_info_ipv4_u.data[7]);
     NAT_SE_WR_REG(SE_NAT_OP_ADDR_RGT_REG_ADDR, (WRITE_TABLE<<NAT_OP_ADDR_RGT_HOST_MGT_REQ_OPCODE_FIELD_OFFSET)+
                                                (NAPT0_TABLE<<NAT_OP_ADDR_RGT_HOST_MGT_REQ_ID_FIELD_OFFSET)+
                                                (napt_index<<NAT_OP_ADDR_RGT_HOST_MGT_REQ_ADDR_FIELD_OFFSET)
                  );

     update_reg(SE_NAT_CONFIG0_RGT_REG_ADDR, NAT_CONFIG0_RGT_CFG_HNAT_MODE_FIELD_OFFSET, NAT_CONFIG0_RGT_CFG_HNAT_MODE_FIELD_SIZE, nat_cfg->hnat_mode);

     napt_index++;
}


void cfg_nat_table_ipv6_item(NatKey_S* nat_key, NatRsp_S* nat_rsp, NatCfg_S* nat_cfg) {

     int i = 0;

     NatHashKey_S m_nat_hash_key;
     unsigned short hash_value[8];
     unsigned short hash_index[8];

     NaptTableInfoIpv6_u m_napt_table_info_ipv6_u;

     gen_nat_hash_key(nat_key, &m_nat_hash_key, nat_cfg);

    #if SE_DEBUG_INFO
     for(i=0; i<37; i=i+1) {
         printf("m_nat_hash_key.hashkey[%0d] = 0x%0x", i, m_nat_hash_key.hashkey[i]);
     }
    #endif

     hash_value[0] = crc16(&m_nat_hash_key.hashkey[0], sizeof(NatHashKey_S), 0);
     hash_value[1] = crc16(&m_nat_hash_key.hashkey[0], sizeof(NatHashKey_S), 1);
     hash_value[2] = crc16(&m_nat_hash_key.hashkey[0], sizeof(NatHashKey_S), 2);
     hash_value[3] = crc16(&m_nat_hash_key.hashkey[0], sizeof(NatHashKey_S), 3);
     hash_value[4] = crc16(&m_nat_hash_key.hashkey[0], sizeof(NatHashKey_S), 4);
     hash_value[5] = crc16(&m_nat_hash_key.hashkey[0], sizeof(NatHashKey_S), 5);
     hash_value[6] = crc16(&m_nat_hash_key.hashkey[0], sizeof(NatHashKey_S), 6);
     hash_value[7] = crc16(&m_nat_hash_key.hashkey[0], sizeof(NatHashKey_S), 7);

     #if SE_DEBUG_INFO
     for(i=0; i<8; i=i+1) {
         printf("hash_value[%0d] = 0x%0x", i, hash_value[i]);
     }
     #endif

     hash_index[0] = get_data16(hash_value[1], 0, 12);
     hash_index[1] = get_data16(hash_value[0], 0, 11);
     hash_index[2] = get_data16(hash_value[1], 0, 11);
     hash_index[3] = get_data16(hash_value[0], 0, 10);
     hash_index[4] = get_data16(hash_value[1], 0, 10);
     hash_index[5] = get_data16(hash_value[0], 0, 10);
     hash_index[6] = get_data16(hash_value[1], 0, 9 );
     hash_index[7] = get_data16(hash_value[0], 0, 9 );

     #if SE_DEBUG_INFO
     for(i=0; i<8; i=i+1) {
         printf("hash_index[%0d] = 0x%0x", i, hash_index[i]);
     }
     #endif

     NAT_SE_WR_REG(SE_NAT_TB_WRDATA00_RGT_REG_ADDR, napt_index);
     if(nat_key->dnat_flag)
     {
         NAT_SE_WR_REG(SE_NAT_OP_ADDR_RGT_REG_ADDR, (WRITE_TABLE<<NAT_OP_ADDR_RGT_HOST_MGT_REQ_OPCODE_FIELD_OFFSET)+
                                                   (DNAT_HASH0_TABLE<<NAT_OP_ADDR_RGT_HOST_MGT_REQ_ID_FIELD_OFFSET)+
                                                   (hash_index[0]<<NAT_OP_ADDR_RGT_HOST_MGT_REQ_ADDR_FIELD_OFFSET));
     }
     else
     {
         NAT_SE_WR_REG(SE_NAT_OP_ADDR_RGT_REG_ADDR, (WRITE_TABLE<<NAT_OP_ADDR_RGT_HOST_MGT_REQ_OPCODE_FIELD_OFFSET)+
                                                   (SNAT_HASH0_TABLE<<NAT_OP_ADDR_RGT_HOST_MGT_REQ_ID_FIELD_OFFSET)+
                                                   (hash_index[0]<<NAT_OP_ADDR_RGT_HOST_MGT_REQ_ADDR_FIELD_OFFSET));
     }

     for(i=0; i<16; i++) {
         m_napt_table_info_ipv6_u.data[i] = 0x0;
     }
     //dnat_flag=0, hant_mode=3'h000
     if(nat_cfg->hnat_mode == 0x0)
     {
         if(nat_key->dnat_flag)
         {
             m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.private_ip[0] = nat_rsp->repl_ip[0];
             m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.private_ip[1] = nat_rsp->repl_ip[1];
             m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.private_ip[2] = nat_rsp->repl_ip[2];
             m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.private_ip[3] = nat_rsp->repl_ip[3];
             m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.private_ip[4] = nat_rsp->repl_ip[4];
             m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.private_ip[5] = nat_rsp->repl_ip[5];
             m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.private_ip[6] = nat_rsp->repl_ip[6];
             m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.private_ip[7] = nat_rsp->repl_ip[7];
             m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.private_ip[8] = nat_rsp->repl_ip[8];
             m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.private_ip[9] = nat_rsp->repl_ip[9];
             m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.private_ip[10] = nat_rsp->repl_ip[10];
             m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.private_ip[11] = nat_rsp->repl_ip[11];
             m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.private_ip[12] = nat_rsp->repl_ip[12];
             m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.private_ip[13] = nat_rsp->repl_ip[13];
             m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.private_ip[14] = nat_rsp->repl_ip[14];
             m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.private_ip[15] = nat_rsp->repl_ip[15];
         }
         else
         {
             m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.private_ip[0] = nat_key->sip[0];
             m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.private_ip[1] = nat_key->sip[1];
             m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.private_ip[2] = nat_key->sip[2];
             m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.private_ip[3] = nat_key->sip[3];
             m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.private_ip[4] = nat_key->sip[4];
             m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.private_ip[5] = nat_key->sip[5];
             m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.private_ip[6] = nat_key->sip[6];
             m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.private_ip[7] = nat_key->sip[7];
             m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.private_ip[8] = nat_key->sip[8];
             m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.private_ip[9] = nat_key->sip[9];
             m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.private_ip[10] = nat_key->sip[10];
             m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.private_ip[11] = nat_key->sip[11];
             m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.private_ip[12] = nat_key->sip[12];
             m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.private_ip[13] = nat_key->sip[13];
             m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.private_ip[14] = nat_key->sip[14];
             m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.private_ip[15] = nat_key->sip[15];
         }
     }
     else if(nat_cfg->hnat_mode == 0x1)
     {
         if(nat_key->dnat_flag)
         {
             m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.private_ip[0] = nat_rsp->repl_ip[0];
             m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.private_ip[1] = nat_rsp->repl_ip[1];
             m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.private_ip[2] = nat_rsp->repl_ip[2];
             m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.private_ip[3] = nat_rsp->repl_ip[3];
             m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.private_ip[4] = nat_rsp->repl_ip[4];
             m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.private_ip[5] = nat_rsp->repl_ip[5];
             m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.private_ip[6] = nat_rsp->repl_ip[6];
             m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.private_ip[7] = nat_rsp->repl_ip[7];
             m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.private_ip[8] = nat_rsp->repl_ip[8];
             m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.private_ip[9] = nat_rsp->repl_ip[9];
             m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.private_ip[10] = nat_rsp->repl_ip[10];
             m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.private_ip[11] = nat_rsp->repl_ip[11];
             m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.private_ip[12] = nat_rsp->repl_ip[12];
             m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.private_ip[13] = nat_rsp->repl_ip[13];
             m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.private_ip[14] = nat_rsp->repl_ip[14];
             m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.private_ip[15] = nat_rsp->repl_ip[15];
             m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.private_port[0] = nat_rsp->repl_port&0xFF;
             m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.private_port[1] = ((nat_rsp->repl_port&0xFF00)>>8);
         }
         else
         {
             m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.private_ip[0] = nat_key->sip[0];
             m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.private_ip[1] = nat_key->sip[1];
             m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.private_ip[2] = nat_key->sip[2];
             m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.private_ip[3] = nat_key->sip[3];
             m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.private_ip[4] = nat_key->sip[4];
             m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.private_ip[5] = nat_key->sip[5];
             m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.private_ip[6] = nat_key->sip[6];
             m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.private_ip[7] = nat_key->sip[7];
             m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.private_ip[8] = nat_key->sip[8];
             m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.private_ip[9] = nat_key->sip[9];
             m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.private_ip[10] = nat_key->sip[10];
             m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.private_ip[11] = nat_key->sip[11];
             m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.private_ip[12] = nat_key->sip[12];
             m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.private_ip[13] = nat_key->sip[13];
             m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.private_ip[14] = nat_key->sip[14];
             m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.private_ip[15] = nat_key->sip[15];
             m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.private_port[0] = nat_key->sport&0xFF;
             m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.private_port[1] = ((nat_key->sport&0xFF00)>>8);
         }
     }
     m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.l4_type  = nat_key->l4_flag;
     m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.ipv6_valid  = 1;

    if(nat_cfg->hnat_mode == 0x0)
    {
        if(nat_key->dnat_flag)
        {
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.router_ip[0] = nat_key->dip[0];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.router_ip[1] = nat_key->dip[1];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.router_ip[2] = nat_key->dip[2];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.router_ip[3] = nat_key->dip[3];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.router_ip[4] = nat_key->dip[4];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.router_ip[5] = nat_key->dip[5];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.router_ip[6] = nat_key->dip[6];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.router_ip[7] = nat_key->dip[7];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.router_ip[8] = nat_key->dip[8];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.router_ip[9] = nat_key->dip[9];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.router_ip[10] = nat_key->dip[10];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.router_ip[11] = nat_key->dip[11];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.router_ip[12] = nat_key->dip[12];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.router_ip[13] = nat_key->dip[13];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.router_ip[14] = nat_key->dip[14];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.router_ip[15] = nat_key->dip[15];
        }
        else
        {
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.router_ip[0] = nat_rsp->repl_ip[0];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.router_ip[1] = nat_rsp->repl_ip[1];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.router_ip[2] = nat_rsp->repl_ip[2];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.router_ip[3] = nat_rsp->repl_ip[3];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.router_ip[4] = nat_rsp->repl_ip[4];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.router_ip[5] = nat_rsp->repl_ip[5];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.router_ip[6] = nat_rsp->repl_ip[6];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.router_ip[7] = nat_rsp->repl_ip[7];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.router_ip[8] = nat_rsp->repl_ip[8];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.router_ip[9] = nat_rsp->repl_ip[9];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.router_ip[10] = nat_rsp->repl_ip[10];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.router_ip[11] = nat_rsp->repl_ip[11];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.router_ip[12] = nat_rsp->repl_ip[12];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.router_ip[13] = nat_rsp->repl_ip[13];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.router_ip[14] = nat_rsp->repl_ip[14];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.router_ip[15] = nat_rsp->repl_ip[15];
        }
    }
    else if(nat_cfg->hnat_mode == 0x1)
    {
        if(nat_key->dnat_flag)
        {
            //key_srch_flag & (key_v4_dip == v4_router_ip0) & (key_dport == v4_router_port0) & (key_v4_sip == v4_public_ip0) & (key_sport == v4_public_port0) & (key_l4_type == v4_l4_type0);
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.router_ip[0] = nat_key->dip[0];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.router_ip[1] = nat_key->dip[1];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.router_ip[2] = nat_key->dip[2];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.router_ip[3] = nat_key->dip[3];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.router_ip[4] = nat_key->dip[4];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.router_ip[5] = nat_key->dip[5];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.router_ip[6] = nat_key->dip[6];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.router_ip[7] = nat_key->dip[7];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.router_ip[8] = nat_key->dip[8];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.router_ip[9] = nat_key->dip[9];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.router_ip[10] = nat_key->dip[10];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.router_ip[11] = nat_key->dip[11];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.router_ip[12] = nat_key->dip[12];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.router_ip[13] = nat_key->dip[13];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.router_ip[14] = nat_key->dip[14];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.router_ip[15] = nat_key->dip[15];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.router_port[0] = nat_key->dport&0xFF;
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.router_port[1] = ((nat_key->dport&0xFF00)>>8);
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.public_ip[0] = nat_key->sip[0];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.public_ip[1] = nat_key->sip[1];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.public_ip[2] = nat_key->sip[2];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.public_ip[3] = nat_key->sip[3];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.public_ip[4] = nat_key->sip[4];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.public_ip[5] = nat_key->sip[5];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.public_ip[6] = nat_key->sip[6];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.public_ip[7] = nat_key->sip[7];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.public_ip[8] = nat_key->sip[8];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.public_ip[9] = nat_key->sip[9];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.public_ip[10] = nat_key->sip[10];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.public_ip[11] = nat_key->sip[11];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.public_ip[12] = nat_key->sip[12];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.public_ip[13] = nat_key->sip[13];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.public_ip[14] = nat_key->sip[14];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.public_ip[15] = nat_key->sip[15];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.public_port[0] = nat_key->sport&0xFF;
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.public_port[1] = ((nat_key->sport&0xFF00)>>8);
        }
        else
        {
            // key_srch_flag & (key_v4_dip == v4_public_ip0) & (key_dport == v4_public_port0) & (key_v4_sip == v4_private_ip0) & (key_sport == v4_private_port0) & (key_l4_type == v4_l4_type0);
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.public_ip[0] = nat_key->dip[0];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.public_ip[1] = nat_key->dip[1];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.public_ip[2] = nat_key->dip[2];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.public_ip[3] = nat_key->dip[3];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.public_ip[4] = nat_key->dip[4];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.public_ip[5] = nat_key->dip[5];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.public_ip[6] = nat_key->dip[6];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.public_ip[7] = nat_key->dip[7];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.public_ip[8] = nat_key->dip[8];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.public_ip[9] = nat_key->dip[9];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.public_ip[10] = nat_key->dip[10];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.public_ip[11] = nat_key->dip[11];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.public_ip[12] = nat_key->dip[12];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.public_ip[13] = nat_key->dip[13];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.public_ip[14] = nat_key->dip[14];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.public_ip[15] = nat_key->dip[15];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.public_port[0] = nat_key->dport&0xFF;
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.public_port[1] = ((nat_key->dport&0xFF00)>>8);
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.router_ip[0] = nat_rsp->repl_ip[0];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.router_ip[1] = nat_rsp->repl_ip[1];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.router_ip[2] = nat_rsp->repl_ip[2];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.router_ip[3] = nat_rsp->repl_ip[3];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.router_ip[4] = nat_rsp->repl_ip[4];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.router_ip[5] = nat_rsp->repl_ip[5];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.router_ip[6] = nat_rsp->repl_ip[6];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.router_ip[7] = nat_rsp->repl_ip[7];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.router_ip[8] = nat_rsp->repl_ip[8];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.router_ip[9] = nat_rsp->repl_ip[9];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.router_ip[10] = nat_rsp->repl_ip[10];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.router_ip[11] = nat_rsp->repl_ip[11];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.router_ip[12] = nat_rsp->repl_ip[12];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.router_ip[13] = nat_rsp->repl_ip[13];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.router_ip[14] = nat_rsp->repl_ip[14];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.router_ip[15] = nat_rsp->repl_ip[15];
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.router_port[0] = nat_rsp->repl_port&0xFF;
            m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.router_port[1] = ((nat_rsp->repl_port&0xFF00)>>8);
        }
    }

     m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.repl_pri_en   = nat_rsp->repl_pri_en;
     m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.repl_pri_0    = nat_rsp->repl_pri & 0x1;
     m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.repl_pri_2_1  = ((nat_rsp->repl_pri & 0x6)>>1);

     if(nat_key->dnat_flag == 1) { //dnat
         m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.rtmac_index       = nat_rsp->smac_index;
         m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.primac_index_7_0  = (nat_rsp->dmac_index&0xff);
         m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.primac_index_10_8 = ((nat_rsp->dmac_index&0x700)>>8);
     }
     else { //snat
         m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.rtmac_index       = nat_rsp->smac_index;
         m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.pubmac_index_4_0  = (nat_rsp->dmac_index&0x1f);
         m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.pubmac_index_10_5 = ((nat_rsp->dmac_index&0x7e0)>>5);
     }

     m_napt_table_info_ipv6_u.m_napt_table_info_ipv6_s.valid  = 1;

     #if SE_DEBUG_INFO
     for(i=0; i<16; i=i+1) {
         printf("m_napt_table_info_ipv6_u.data[%0d] = 0x%0x", i, m_napt_table_info_ipv6_u.data[i]);
     }
     #endif

     NAT_SE_WR_REG(SE_NAT_TB_WRDATA00_RGT_REG_ADDR, m_napt_table_info_ipv6_u.data[ 0]);
     NAT_SE_WR_REG(SE_NAT_TB_WRDATA01_RGT_REG_ADDR, m_napt_table_info_ipv6_u.data[ 1]);
     NAT_SE_WR_REG(SE_NAT_TB_WRDATA02_RGT_REG_ADDR, m_napt_table_info_ipv6_u.data[ 2]);
     NAT_SE_WR_REG(SE_NAT_TB_WRDATA03_RGT_REG_ADDR, m_napt_table_info_ipv6_u.data[ 3]);
     NAT_SE_WR_REG(SE_NAT_TB_WRDATA04_RGT_REG_ADDR, m_napt_table_info_ipv6_u.data[ 4]);
     NAT_SE_WR_REG(SE_NAT_TB_WRDATA05_RGT_REG_ADDR, m_napt_table_info_ipv6_u.data[ 5]);
     NAT_SE_WR_REG(SE_NAT_TB_WRDATA06_RGT_REG_ADDR, m_napt_table_info_ipv6_u.data[ 6]);
     NAT_SE_WR_REG(SE_NAT_TB_WRDATA07_RGT_REG_ADDR, m_napt_table_info_ipv6_u.data[ 7]);
     NAT_SE_WR_REG(SE_NAT_TB_WRDATA08_RGT_REG_ADDR, m_napt_table_info_ipv6_u.data[ 8]);
     NAT_SE_WR_REG(SE_NAT_TB_WRDATA09_RGT_REG_ADDR, m_napt_table_info_ipv6_u.data[ 9]);
     NAT_SE_WR_REG(SE_NAT_TB_WRDATA10_RGT_REG_ADDR, m_napt_table_info_ipv6_u.data[10]);
     NAT_SE_WR_REG(SE_NAT_TB_WRDATA11_RGT_REG_ADDR, m_napt_table_info_ipv6_u.data[11]);
     NAT_SE_WR_REG(SE_NAT_TB_WRDATA12_RGT_REG_ADDR, m_napt_table_info_ipv6_u.data[12]);
     NAT_SE_WR_REG(SE_NAT_TB_WRDATA13_RGT_REG_ADDR, m_napt_table_info_ipv6_u.data[13]);
     NAT_SE_WR_REG(SE_NAT_TB_WRDATA14_RGT_REG_ADDR, m_napt_table_info_ipv6_u.data[14]);
     NAT_SE_WR_REG(SE_NAT_TB_WRDATA15_RGT_REG_ADDR, m_napt_table_info_ipv6_u.data[15]);
     NAT_SE_WR_REG(SE_NAT_OP_ADDR_RGT_REG_ADDR, (WRITE_TABLE<<NAT_OP_ADDR_RGT_HOST_MGT_REQ_OPCODE_FIELD_OFFSET)+
                                                (NAPT01_TABLE<<NAT_OP_ADDR_RGT_HOST_MGT_REQ_ID_FIELD_OFFSET)+
                                                (napt_index<<NAT_OP_ADDR_RGT_HOST_MGT_REQ_ADDR_FIELD_OFFSET)
                  );

     update_reg(SE_NAT_CONFIG0_RGT_REG_ADDR, NAT_CONFIG0_RGT_CFG_HNAT_MODE_FIELD_OFFSET, NAT_CONFIG0_RGT_CFG_HNAT_MODE_FIELD_SIZE, nat_cfg->hnat_mode);

     napt_index++;
}


void cfg_nat_elkp_table_item(NatKey_S* nat_key, NatRsp_S* nat_rsp, NatCfg_S* nat_cfg) {

     int i = 0;

     NatHashKey_S m_nat_hash_key;
     unsigned short hash_value[8] ;
     unsigned short hash_index[8] ;
     unsigned int   acs_index[8]  ;
     unsigned int   ddr_index     ;
     unsigned int   elkp_base_addr;

     NaptTableInfoIpv4_u m_napt_table_info_ipv4_u;

     gen_nat_hash_key(nat_key, &m_nat_hash_key, nat_cfg);

    #if SE_DEBUG_INFO
     for(i=0; i<37; i=i+1) {
         printf("m_nat_hash_key.hashkey[%0d] = 0x%0x", i, m_nat_hash_key.hashkey[i]);
     }
    #endif

     hash_value[0] = crc16(&m_nat_hash_key.hashkey[0], sizeof(NatHashKey_S), 0);
     hash_value[1] = crc16(&m_nat_hash_key.hashkey[0], sizeof(NatHashKey_S), 1);
     hash_value[2] = crc16(&m_nat_hash_key.hashkey[0], sizeof(NatHashKey_S), 2);
     hash_value[3] = crc16(&m_nat_hash_key.hashkey[0], sizeof(NatHashKey_S), 3);
     hash_value[4] = crc16(&m_nat_hash_key.hashkey[0], sizeof(NatHashKey_S), 4);
     hash_value[5] = crc16(&m_nat_hash_key.hashkey[0], sizeof(NatHashKey_S), 5);
     hash_value[6] = crc16(&m_nat_hash_key.hashkey[0], sizeof(NatHashKey_S), 6);
     hash_value[7] = crc16(&m_nat_hash_key.hashkey[0], sizeof(NatHashKey_S), 7);

     #if SE_DEBUG_INFO
     for(i=0; i<8; i=i+1) {
         printf("hash_value[%0d] = 0x%0x", i, hash_value[i]);
     }
     #endif

     hash_index[0] = hash_value[1];
     hash_index[1] = hash_value[0];
     hash_index[2] = hash_value[1];
     hash_index[3] = hash_value[0];
     hash_index[4] = hash_value[1];
     hash_index[5] = hash_value[0];
     hash_index[6] = hash_value[1];
     hash_index[7] = hash_value[0];

     for(i=0; i<8; i++) {
            switch((nat_cfg->elkp_table_size<<2)+nat_cfg->elkp_v4_acs_times) {
                case ((0x0<<2)+0x0): acs_index[i] = (i<<13)+ get_data16(hash_index[i], 0, 13); break;
                case ((0x0<<2)+0x1): acs_index[i] = (i<<12)+ get_data16(hash_index[i], 0, 12); break;
                case ((0x0<<2)+0x2): acs_index[i] = (i<<11)+ get_data16(hash_index[i], 0, 11); break;
                case ((0x0<<2)+0x3): acs_index[i] = (i<<10)+ get_data16(hash_index[i], 0, 10); break;
                case ((0x1<<2)+0x0): acs_index[i] = (i<<14)+ get_data16(hash_index[i], 0, 14); break;
                case ((0x1<<2)+0x1): acs_index[i] = (i<<13)+ get_data16(hash_index[i], 0, 13); break;
                case ((0x1<<2)+0x2): acs_index[i] = (i<<12)+ get_data16(hash_index[i], 0, 12); break;
                case ((0x1<<2)+0x3): acs_index[i] = (i<<11)+ get_data16(hash_index[i], 0, 11); break;
                case ((0x2<<2)+0x0): acs_index[i] = (i<<15)+ get_data16(hash_index[i], 0, 15); break;
                case ((0x2<<2)+0x1): acs_index[i] = (i<<14)+ get_data16(hash_index[i], 0, 14); break;
                case ((0x2<<2)+0x2): acs_index[i] = (i<<13)+ get_data16(hash_index[i], 0, 13); break;
                case ((0x2<<2)+0x3): acs_index[i] = (i<<12)+ get_data16(hash_index[i], 0, 12); break;
                case ((0x3<<2)+0x0): acs_index[i] = (i<<16)+ get_data16(hash_index[i], 0, 16); break;
                case ((0x3<<2)+0x1): acs_index[i] = (i<<15)+ get_data16(hash_index[i], 0, 15); break;
                case ((0x3<<2)+0x2): acs_index[i] = (i<<14)+ get_data16(hash_index[i], 0, 14); break;
                case ((0x3<<2)+0x3): acs_index[i] = (i<<13)+ get_data16(hash_index[i], 0, 13); break;
                default:     acs_index[i] = 0; break;
            }
     }

     ddr_index = acs_index[0];

     #if SE_DEBUG_INFO
     for(i=0; i<8; i=i+1) {
         printf("acs_index[%0d] = 0x%0x", i, acs_index[i]);
     }
     #endif

     for(i=0; i<8; i++) {
         m_napt_table_info_ipv4_u.data[i] = 0x0;
     }
     //dnat_flag=0, hant_mode=3'h000
     if(nat_cfg->hnat_mode == 0x0)
     {
         if(nat_key->dnat_flag)
         {
             m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.private_ip[0] = nat_rsp->repl_ip[0];
             m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.private_ip[1] = nat_rsp->repl_ip[1];
             m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.private_ip[2] = nat_rsp->repl_ip[2];
             m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.private_ip[3] = nat_rsp->repl_ip[3];
         }
         else
         {
             m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.private_ip[0] = nat_key->sip[0];
             m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.private_ip[1] = nat_key->sip[1];
             m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.private_ip[2] = nat_key->sip[2];
             m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.private_ip[3] = nat_key->sip[3];
         }
     }
     else if(nat_cfg->hnat_mode == 0x1)
     {
         if(nat_key->dnat_flag)
         {
             m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.private_ip[0] = nat_rsp->repl_ip[0];
             m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.private_ip[1] = nat_rsp->repl_ip[1];
             m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.private_ip[2] = nat_rsp->repl_ip[2];
             m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.private_ip[3] = nat_rsp->repl_ip[3];
             m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.private_port[0] = nat_rsp->repl_port&0xFF;
             m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.private_port[1] = ((nat_rsp->repl_port&0xFF00)>>8);
         }
         else
         {
             m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.private_ip[0] = nat_key->sip[0];
             m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.private_ip[1] = nat_key->sip[1];
             m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.private_ip[2] = nat_key->sip[2];
             m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.private_ip[3] = nat_key->sip[3];
             m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.private_port[0] = nat_key->sport&0xFF;
             m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.private_port[1] = ((nat_key->sport&0xFF00)>>8);
         }
     }
     m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.l4_type  = nat_key->l4_flag;

    if(nat_cfg->hnat_mode == 0x0)
    {
        if(nat_key->dnat_flag)
        {
            m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.router_ip[0] = nat_key->dip[0];
            m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.router_ip[1] = nat_key->dip[1];
            m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.router_ip[2] = nat_key->dip[2];
            m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.router_ip[3] = nat_key->dip[3];
        }
        else
        {
            m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.router_ip[0] = nat_rsp->repl_ip[0];
            m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.router_ip[1] = nat_rsp->repl_ip[1];
            m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.router_ip[2] = nat_rsp->repl_ip[2];
            m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.router_ip[3] = nat_rsp->repl_ip[3];
        }
    }
    else if(nat_cfg->hnat_mode == 0x1)
    {
        if(nat_key->dnat_flag)
        {
            //key_srch_flag & (key_v4_dip == v4_router_ip0) & (key_dport == v4_router_port0) & (key_v4_sip == v4_public_ip0) & (key_sport == v4_public_port0) & (key_l4_type == v4_l4_type0);
            m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.router_ip[0] = nat_key->dip[0];
            m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.router_ip[1] = nat_key->dip[1];
            m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.router_ip[2] = nat_key->dip[2];
            m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.router_ip[3] = nat_key->dip[3];
            m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.router_port[0] = nat_key->dport&0xFF;
            m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.router_port[1] = ((nat_key->dport&0xFF00)>>8);
            m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.public_ip[0] = nat_key->sip[0];
            m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.public_ip[1] = nat_key->sip[1];
            m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.public_ip[2] = nat_key->sip[2];
            m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.public_ip[3] = nat_key->sip[3];
            m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.public_port[0] = nat_key->sport&0xFF;
            m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.public_port[1] = ((nat_key->sport&0xFF00)>>8);
        }
        else
        {
            // key_srch_flag & (key_v4_dip == v4_public_ip0) & (key_dport == v4_public_port0) & (key_v4_sip == v4_private_ip0) & (key_sport == v4_private_port0) & (key_l4_type == v4_l4_type0);
            m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.public_ip[0] = nat_key->dip[0];
            m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.public_ip[1] = nat_key->dip[1];
            m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.public_ip[2] = nat_key->dip[2];
            m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.public_ip[3] = nat_key->dip[3];
            m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.public_port[0] = nat_key->dport&0xFF;
            m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.public_port[1] = ((nat_key->dport&0xFF00)>>8);
            m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.router_ip[0] = nat_rsp->repl_ip[0];
            m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.router_ip[1] = nat_rsp->repl_ip[1];
            m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.router_ip[2] = nat_rsp->repl_ip[2];
            m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.router_ip[3] = nat_rsp->repl_ip[3];
            m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.router_port[0] = nat_rsp->repl_port&0xFF;
            m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.router_port[1] = ((nat_rsp->repl_port&0xFF00)>>8);
        }
    }

     m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.repl_pri_en   = nat_rsp->repl_pri_en;
     m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.repl_pri_0    = nat_rsp->repl_pri & 0x1;
     m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.repl_pri_2_1  = ((nat_rsp->repl_pri & 0x6)>>1);

     if(nat_key->dnat_flag == 1) { //dnat
         m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.rtmac_index       = nat_rsp->smac_index;
         m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.primac_index_7_0  = (nat_rsp->dmac_index&0xff);
         m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.primac_index_10_8 = ((nat_rsp->dmac_index&0x700)>>8);
     }
     else { //snat
         m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.rtmac_index       = nat_rsp->smac_index;
         m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.pubmac_index_4_0  = (nat_rsp->dmac_index&0x1f);
         m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.pubmac_index_10_5 = ((nat_rsp->dmac_index&0x7e0)>>5);
     }

     m_napt_table_info_ipv4_u.m_napt_table_info_ipv4_s.valid  = 1;

     #if SE_DEBUG_INFO
     for(i=0; i<8; i=i+1) {
         printf("m_napt_table_info_ipv4_u.data[%0d] = 0x%0x", i, m_napt_table_info_ipv4_u.data[i]);
     }
     #endif

     if(nat_key->dnat_flag)
     {
         elkp_base_addr = nat_cfg->elkp_dnat_base_addr;
     }
     else
     {
         elkp_base_addr = nat_cfg->elkp_snat_base_addr;
     }
     #if SE_DEBUG_INFO
     printf("elkp_base_addr = 0x%0x", elkp_base_addr);
     printf("ddr_index = 0x%0x", ddr_index);
     printf("elkp_base_addr+(ddr_index<<6)+0*4 = 0x%0x", elkp_base_addr+(ddr_index<<6)+0*4);
     #endif
     SF_WR_REG(elkp_base_addr+(ddr_index<<6)+0*4, m_napt_table_info_ipv4_u.data[0]);
     SF_WR_REG(elkp_base_addr+(ddr_index<<6)+1*4, m_napt_table_info_ipv4_u.data[1]);
     SF_WR_REG(elkp_base_addr+(ddr_index<<6)+2*4, m_napt_table_info_ipv4_u.data[2]);
     SF_WR_REG(elkp_base_addr+(ddr_index<<6)+3*4, m_napt_table_info_ipv4_u.data[3]);
     SF_WR_REG(elkp_base_addr+(ddr_index<<6)+4*4, m_napt_table_info_ipv4_u.data[4]);
     SF_WR_REG(elkp_base_addr+(ddr_index<<6)+5*4, m_napt_table_info_ipv4_u.data[5]);
     SF_WR_REG(elkp_base_addr+(ddr_index<<6)+6*4, m_napt_table_info_ipv4_u.data[6]);
     SF_WR_REG(elkp_base_addr+(ddr_index<<6)+7*4, m_napt_table_info_ipv4_u.data[7]);

     update_reg(SE_NAT_CONFIG0_RGT_REG_ADDR, NAT_CONFIG0_RGT_DIS_DDR_LKP_FIELD_OFFSET, NAT_CONFIG0_RGT_DIS_DDR_LKP_FIELD_SIZE, 0);
     update_reg(SE_NAT_CONFIG0_RGT_REG_ADDR, NAT_CONFIG0_RGT_ELKP_TABLE_SIZE_FIELD_OFFSET, NAT_CONFIG0_RGT_ELKP_TABLE_SIZE_FIELD_SIZE, nat_cfg->elkp_table_size);
     update_reg(SE_NAT_CONFIG0_RGT_REG_ADDR, NAT_CONFIG0_RGT_ELKP_V4_ACS_TIMES_FIELD_OFFSET, NAT_CONFIG0_RGT_ELKP_V4_ACS_TIMES_FIELD_SIZE, nat_cfg->elkp_v4_acs_times);
     NAT_SE_WR_REG(SE_NAT_CONFIG3_RGT_REG_ADDR, nat_cfg->elkp_dnat_base_addr-0x20000000);
     NAT_SE_WR_REG(SE_NAT_CONFIG4_RGT_REG_ADDR, nat_cfg->elkp_snat_base_addr-0x20000000);
}

void cfg_nat_table_item(NatKey_S* nat_key, NatRsp_S* nat_rsp, NatCfg_S* nat_cfg) {
    if(nat_key->l3_flag == 0) {
        cfg_nat_table_ipv4_item(nat_key, nat_rsp, nat_cfg);
    }
    else {
        cfg_nat_table_ipv6_item(nat_key, nat_rsp, nat_cfg);
    }
}

#endif

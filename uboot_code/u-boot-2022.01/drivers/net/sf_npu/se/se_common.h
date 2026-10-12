#ifndef SE_COMMON_H
#define SE_COMMON_H

#include <stdint.h>
#include <linux/io.h>
#include <linux/types.h>
#include "se_head.h"

typedef struct se_key {
    unsigned char  nat_mode;
    unsigned char  dnat_flag;
    unsigned char  type; // tcp or udp
    unsigned short sport;
    unsigned char  sip[4];
    unsigned short dport;
    unsigned char  dip[4];
    unsigned char  da[6];
    unsigned char  sa[6];
}Sekey;

typedef struct se_rsp {
    unsigned short rport;
    unsigned char  rip[4];
    uint64_t       rda;
    uint64_t       rsa;
    // arp
    unsigned char  pppoe_en  ;
    uint64_t       pppoe_hdr ;
    unsigned short ovport    ;

}Sersp;


typedef enum se_nat_tb_name_e {
        DNAT_HASH0_TABLE = 0,
        DNAT_HASH1_TABLE = 1,
        SNAT_HASH0_TABLE = 2,
        SNAT_HASH1_TABLE = 3,
        NAPT0_TABLE      = 4,
        NAPT1_TABLE      = 5,
        NAPT01_TABLE     = 6,
        SPL_TABLE        = 7
}SeNatTbName_e;

typedef enum se_tb_name_e {
    L2_SE_HASH0_TABLE  = 5,
    L2_SE_HASH1_TABLE  = 6,
    ARP_SE_MAC_TABLE   = 7,
    ARP_SE_MACSPL_TABLE  = 8,
    ARP_SE_INTF_DIRECT_TABLE    = 9,
    IVLAN_PORT_SE_IVLAN_IPORT_TABLE = 1,
    IVLAN_PORT_SE_IVLAN_SPL_TABLE   = 0,
    IVLAN_LKP_SE_LITE_HASH_TABLE  = 4 ,
    EVLAN_ACT_SE_DIRECT_TABLE  = 14,
    EVLAN_VID_SE_LITE_HASH_TABLE  = 13,
    EVLAN_XLT_SE_LITE_HASH_TABLE  = 12,
    IVLAN_XLT_SE_LITE_HASH_TABLE  = 2 ,
    IVLAN_PBV_SE_DIRECT_TABLE  = 3 ,
    EVLAN_OTPID_SE_DIRECT_TABLE = 10,
    EVLAN_TPID_SE_HASH_TABLE  = 11
}SeTbName_e;

#define WRITE_TABLE (1)
#define READ_TABLE (0)

#define SF_RD_REG(addr, data) data = readl((uintptr_t)addr)
#define SF_WR_REG(addr, data) writel(data, (uintptr_t)addr)
#define SE_WR_REG(addr, data) SF_WR_REG(addr, data)
#define SE_RD_REG(addr, data) SF_RD_REG(addr, data)
#define NAT_SE_WR_REG(addr, data) SF_WR_REG(addr, data)
#define NAT_SE_RD_REG(addr, data) SF_RD_REG(addr, data)

#define GET_DATA_FIELD(data, startbit, width) (((data) & (((1<<(width)) - 1) << (startbit))) >> (startbit))

#ifndef SE_DEBUG_INFO
#define SE_DEBUG_INFO 0
#endif

unsigned short crc16(unsigned char *buf, int len, int poly_sel);
unsigned char gen_all_1_data8(int width);
unsigned short gen_all_1_data16(int width);
unsigned int gen_all_1_data32(int width);
uint64_t gen_all_1_data64(int width);
void update_data8(unsigned char* data, int offset, int width, unsigned char value);
unsigned char get_data8(unsigned char data, int offset, int width);
void update_data16(unsigned short* data, int offset, int width, unsigned short value);
unsigned short get_data16(unsigned short data, int offset, int width);
void update_data32(unsigned int* data, int offset, int width, unsigned int value);
unsigned int get_data32(unsigned int data, int offset, int width);
void update_data64(uint64_t* data, int offset, int width, uint64_t value);
uint64_t get_data64(uint64_t data, int offset, int width);
void update_reg(unsigned int addr, int offset, int width, unsigned int value);

#endif

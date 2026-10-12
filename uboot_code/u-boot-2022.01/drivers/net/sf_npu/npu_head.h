//
// Version: 3350., 2021-12-17 22:14:55
//

#ifndef __NPU_REG_H__
#define __NPU_REG_H__

//-------------------------------------------------------------------------
// NPU BASE ADDR:
//-------------------------------------------------------------------------
#ifndef NPU_BASE_ADDR
#define NPU_BASE_ADDR (0x11000000)
#endif

//-------------------------------------------------------------------------
// NAT_MPP_CFG INFO:
//-------------------------------------------------------------------------
#define NPU_NAT_MPP_CFG_REG_ADDR (NPU_BASE_ADDR+0x0)
#define NAT_MPP_CFG_RSVD_FIELD_OFFSET (21)
#define NAT_MPP_CFG_RSVD_FIELD_SIZE   (11)
#define NAT_MPP_CFG_CFG_MPP_BYPASS_FIELD_OFFSET (20)
#define NAT_MPP_CFG_CFG_MPP_BYPASS_FIELD_SIZE   (1)
#define NAT_MPP_CFG_RESP_FIFO_AFULL_THRESH_FIELD_OFFSET (15)
#define NAT_MPP_CFG_RESP_FIFO_AFULL_THRESH_FIELD_SIZE   (5)
#define NAT_MPP_CFG_VOQ_1_FIFO_AFULL_THRESH_FIELD_OFFSET (10)
#define NAT_MPP_CFG_VOQ_1_FIFO_AFULL_THRESH_FIELD_SIZE   (5)
#define NAT_MPP_CFG_VOQ_0_FIFO_AFULL_THRESH_FIELD_OFFSET (5)
#define NAT_MPP_CFG_VOQ_0_FIFO_AFULL_THRESH_FIELD_SIZE   (5)
#define NAT_MPP_CFG_FP_FIFO_AFULL_THRESH_FIELD_OFFSET (0)
#define NAT_MPP_CFG_FP_FIFO_AFULL_THRESH_FIELD_SIZE   (5)

//-------------------------------------------------------------------------
// NAT_PKT_TYPE_SEARCH_MASK INFO:
//-------------------------------------------------------------------------
#define NPU_NAT_PKT_TYPE_SEARCH_MASK_REG_ADDR (NPU_BASE_ADDR+0x4)
#define NAT_PKT_TYPE_SEARCH_MASK_PKT_TYPE_SEARCH_MASK_FIELD_OFFSET (0)
#define NAT_PKT_TYPE_SEARCH_MASK_PKT_TYPE_SEARCH_MASK_FIELD_SIZE   (8)

//-------------------------------------------------------------------------
// NAT_PRIVATE_IP_V4_INFO0 INFO:
//-------------------------------------------------------------------------
#define NPU_NAT_PRIVATE_IP_V4_INFO0_REG_ADDR (NPU_BASE_ADDR+0x8)
#define NAT_PRIVATE_IP_V4_INFO0_PRIVATE_IP_V4_INFO0_FIELD_OFFSET (0)
#define NAT_PRIVATE_IP_V4_INFO0_PRIVATE_IP_V4_INFO0_FIELD_SIZE   (32)

//-------------------------------------------------------------------------
// NAT_PRIVATE_IP_V4_INFO1 INFO:
//-------------------------------------------------------------------------
#define NPU_NAT_PRIVATE_IP_V4_INFO1_REG_ADDR (NPU_BASE_ADDR+0xC)
#define NAT_PRIVATE_IP_V4_INFO1_PRIVATE_IP_V4_INFO1_FIELD_OFFSET (0)
#define NAT_PRIVATE_IP_V4_INFO1_PRIVATE_IP_V4_INFO1_FIELD_SIZE   (32)

//-------------------------------------------------------------------------
// NAT_PRIVATE_IP_V4_INFO2 INFO:
//-------------------------------------------------------------------------
#define NPU_NAT_PRIVATE_IP_V4_INFO2_REG_ADDR (NPU_BASE_ADDR+0x10)
#define NAT_PRIVATE_IP_V4_INFO2_PRIVATE_IP_V4_INFO2_FIELD_OFFSET (0)
#define NAT_PRIVATE_IP_V4_INFO2_PRIVATE_IP_V4_INFO2_FIELD_SIZE   (32)

//-------------------------------------------------------------------------
// NAT_PRIVATE_IP_V4_INFO3 INFO:
//-------------------------------------------------------------------------
#define NPU_NAT_PRIVATE_IP_V4_INFO3_REG_ADDR (NPU_BASE_ADDR+0x14)
#define NAT_PRIVATE_IP_V4_INFO3_PRIVATE_IP_V4_INFO3_FIELD_OFFSET (0)
#define NAT_PRIVATE_IP_V4_INFO3_PRIVATE_IP_V4_INFO3_FIELD_SIZE   (32)

//-------------------------------------------------------------------------
// NAT_PRIVATE_IP_V4_INFO4 INFO:
//-------------------------------------------------------------------------
#define NPU_NAT_PRIVATE_IP_V4_INFO4_REG_ADDR (NPU_BASE_ADDR+0x18)
#define NAT_PRIVATE_IP_V4_INFO4_PRIVATE_IP_V4_INFO4_FIELD_OFFSET (0)
#define NAT_PRIVATE_IP_V4_INFO4_PRIVATE_IP_V4_INFO4_FIELD_SIZE   (32)

//-------------------------------------------------------------------------
// NAT_PRIVATE_IP_V4_INFO5 INFO:
//-------------------------------------------------------------------------
#define NPU_NAT_PRIVATE_IP_V4_INFO5_REG_ADDR (NPU_BASE_ADDR+0x1C)
#define NAT_PRIVATE_IP_V4_INFO5_PRIVATE_IP_V4_INFO5_FIELD_OFFSET (0)
#define NAT_PRIVATE_IP_V4_INFO5_PRIVATE_IP_V4_INFO5_FIELD_SIZE   (32)

//-------------------------------------------------------------------------
// NAT_PRIVATE_IP_V4_INFO6 INFO:
//-------------------------------------------------------------------------
#define NPU_NAT_PRIVATE_IP_V4_INFO6_REG_ADDR (NPU_BASE_ADDR+0x20)
#define NAT_PRIVATE_IP_V4_INFO6_PRIVATE_IP_V4_INFO6_FIELD_OFFSET (0)
#define NAT_PRIVATE_IP_V4_INFO6_PRIVATE_IP_V4_INFO6_FIELD_SIZE   (32)

//-------------------------------------------------------------------------
// NAT_PRIVATE_IP_V4_INFO7 INFO:
//-------------------------------------------------------------------------
#define NPU_NAT_PRIVATE_IP_V4_INFO7_REG_ADDR (NPU_BASE_ADDR+0x24)
#define NAT_PRIVATE_IP_V4_INFO7_PRIVATE_IP_V4_INFO7_FIELD_OFFSET (0)
#define NAT_PRIVATE_IP_V4_INFO7_PRIVATE_IP_V4_INFO7_FIELD_SIZE   (32)

//-------------------------------------------------------------------------
// NAT_IPV4_MASK_LEN0123 INFO:
//-------------------------------------------------------------------------
#define NPU_NAT_IPV4_MASK_LEN0123_REG_ADDR (NPU_BASE_ADDR+0x28)
#define NAT_IPV4_MASK_LEN3_RSVD_FIELD_OFFSET (31)
#define NAT_IPV4_MASK_LEN3_RSVD_FIELD_SIZE   (1)
#define NAT_IPV4_MASK_LEN3_IP_V4_MASK_LEN3_FIELD_OFFSET (24)
#define NAT_IPV4_MASK_LEN3_IP_V4_MASK_LEN3_FIELD_SIZE   (7)
#define NAT_IPV4_MASK_LEN2_RSVD_FIELD_OFFSET (23)
#define NAT_IPV4_MASK_LEN2_RSVD_FIELD_SIZE   (1)
#define NAT_IPV4_MASK_LEN2_IP_V4_MASK_LEN2_FIELD_OFFSET (16)
#define NAT_IPV4_MASK_LEN2_IP_V4_MASK_LEN2_FIELD_SIZE   (7)
#define NAT_IPV4_MASK_LEN1_RSVD_FIELD_OFFSET (15)
#define NAT_IPV4_MASK_LEN1_RSVD_FIELD_SIZE   (1)
#define NAT_IPV4_MASK_LEN1_IP_V4_MASK_LEN1_FIELD_OFFSET (8)
#define NAT_IPV4_MASK_LEN1_IP_V4_MASK_LEN1_FIELD_SIZE   (7)
#define NAT_IPV4_MASK_LEN0_RSVD_FIELD_OFFSET (7)
#define NAT_IPV4_MASK_LEN0_RSVD_FIELD_SIZE   (1)
#define NAT_IPV4_MASK_LEN0_IP_V4_MASK_LEN0_FIELD_OFFSET (0)
#define NAT_IPV4_MASK_LEN0_IP_V4_MASK_LEN0_FIELD_SIZE   (7)

//-------------------------------------------------------------------------
// NAT_IPV4_MASK_LEN4567 INFO:
//-------------------------------------------------------------------------
#define NPU_NAT_IPV4_MASK_LEN4567_REG_ADDR (NPU_BASE_ADDR+0x2C)
#define NAT_IPV4_MASK_LEN7_RSVD_FIELD_OFFSET (31)
#define NAT_IPV4_MASK_LEN7_RSVD_FIELD_SIZE   (1)
#define NAT_IPV4_MASK_LEN7_IP_V4_MASK_LEN7_FIELD_OFFSET (24)
#define NAT_IPV4_MASK_LEN7_IP_V4_MASK_LEN7_FIELD_SIZE   (7)
#define NAT_IPV4_MASK_LEN6_RSVD_FIELD_OFFSET (23)
#define NAT_IPV4_MASK_LEN6_RSVD_FIELD_SIZE   (1)
#define NAT_IPV4_MASK_LEN6_IP_V4_MASK_LEN6_FIELD_OFFSET (16)
#define NAT_IPV4_MASK_LEN6_IP_V4_MASK_LEN6_FIELD_SIZE   (7)
#define NAT_IPV4_MASK_LEN5_RSVD_FIELD_OFFSET (15)
#define NAT_IPV4_MASK_LEN5_RSVD_FIELD_SIZE   (1)
#define NAT_IPV4_MASK_LEN5_IP_V4_MASK_LEN5_FIELD_OFFSET (8)
#define NAT_IPV4_MASK_LEN5_IP_V4_MASK_LEN5_FIELD_SIZE   (7)
#define NAT_IPV4_MASK_LEN4_RSVD_FIELD_OFFSET (7)
#define NAT_IPV4_MASK_LEN4_RSVD_FIELD_SIZE   (1)
#define NAT_IPV4_MASK_LEN4_IP_V4_MASK_LEN4_FIELD_OFFSET (0)
#define NAT_IPV4_MASK_LEN4_IP_V4_MASK_LEN4_FIELD_SIZE   (7)

//-------------------------------------------------------------------------
// NAT_PRIVATE_IP_V6_INFO0_0 INFO:
//-------------------------------------------------------------------------
#define NPU_NAT_PRIVATE_IP_V6_INFO0_0_REG_ADDR (NPU_BASE_ADDR+0x30)
#define NAT_PRIVATE_IP_V6_INFO0_0_PRIVATE_IP_V6_INFO0_0_FIELD_OFFSET (0)
#define NAT_PRIVATE_IP_V6_INFO0_0_PRIVATE_IP_V6_INFO0_0_FIELD_SIZE   (32)

//-------------------------------------------------------------------------
// NAT_PRIVATE_IP_V6_INFO0_1 INFO:
//-------------------------------------------------------------------------
#define NPU_NAT_PRIVATE_IP_V6_INFO0_1_REG_ADDR (NPU_BASE_ADDR+0x34)
#define NAT_PRIVATE_IP_V6_INFO0_1_PRIVATE_IP_V6_INFO0_1_FIELD_OFFSET (0)
#define NAT_PRIVATE_IP_V6_INFO0_1_PRIVATE_IP_V6_INFO0_1_FIELD_SIZE   (32)

//-------------------------------------------------------------------------
// NAT_PRIVATE_IP_V6_INFO0_2 INFO:
//-------------------------------------------------------------------------
#define NPU_NAT_PRIVATE_IP_V6_INFO0_2_REG_ADDR (NPU_BASE_ADDR+0x38)
#define NAT_PRIVATE_IP_V6_INFO0_2_PRIVATE_IP_V6_INFO0_2_FIELD_OFFSET (0)
#define NAT_PRIVATE_IP_V6_INFO0_2_PRIVATE_IP_V6_INFO0_2_FIELD_SIZE   (32)

//-------------------------------------------------------------------------
// NAT_PRIVATE_IP_V6_INFO0_3 INFO:
//-------------------------------------------------------------------------
#define NPU_NAT_PRIVATE_IP_V6_INFO0_3_REG_ADDR (NPU_BASE_ADDR+0x3C)
#define NAT_PRIVATE_IP_V6_INFO0_3_PRIVATE_IP_V6_INFO0_3_FIELD_OFFSET (0)
#define NAT_PRIVATE_IP_V6_INFO0_3_PRIVATE_IP_V6_INFO0_3_FIELD_SIZE   (32)

//-------------------------------------------------------------------------
// NAT_PRIVATE_IP_V6_INFO1_0 INFO:
//-------------------------------------------------------------------------
#define NPU_NAT_PRIVATE_IP_V6_INFO1_0_REG_ADDR (NPU_BASE_ADDR+0x40)
#define NAT_PRIVATE_IP_V6_INFO1_0_PRIVATE_IP_V6_INFO1_0_FIELD_OFFSET (0)
#define NAT_PRIVATE_IP_V6_INFO1_0_PRIVATE_IP_V6_INFO1_0_FIELD_SIZE   (32)

//-------------------------------------------------------------------------
// NAT_PRIVATE_IP_V6_INFO1_1 INFO:
//-------------------------------------------------------------------------
#define NPU_NAT_PRIVATE_IP_V6_INFO1_1_REG_ADDR (NPU_BASE_ADDR+0x44)
#define NAT_PRIVATE_IP_V6_INFO1_1_PRIVATE_IP_V6_INFO1_1_FIELD_OFFSET (0)
#define NAT_PRIVATE_IP_V6_INFO1_1_PRIVATE_IP_V6_INFO1_1_FIELD_SIZE   (32)

//-------------------------------------------------------------------------
// NAT_PRIVATE_IP_V6_INFO1_2 INFO:
//-------------------------------------------------------------------------
#define NPU_NAT_PRIVATE_IP_V6_INFO1_2_REG_ADDR (NPU_BASE_ADDR+0x48)
#define NAT_PRIVATE_IP_V6_INFO1_2_PRIVATE_IP_V6_INFO1_2_FIELD_OFFSET (0)
#define NAT_PRIVATE_IP_V6_INFO1_2_PRIVATE_IP_V6_INFO1_2_FIELD_SIZE   (32)

//-------------------------------------------------------------------------
// NAT_PRIVATE_IP_V6_INFO1_3 INFO:
//-------------------------------------------------------------------------
#define NPU_NAT_PRIVATE_IP_V6_INFO1_3_REG_ADDR (NPU_BASE_ADDR+0x4C)
#define NAT_PRIVATE_IP_V6_INFO1_3_PRIVATE_IP_V6_INFO1_3_FIELD_OFFSET (0)
#define NAT_PRIVATE_IP_V6_INFO1_3_PRIVATE_IP_V6_INFO1_3_FIELD_SIZE   (32)

//-------------------------------------------------------------------------
// NAT_PRIVATE_IP_V6_INFO2_0 INFO:
//-------------------------------------------------------------------------
#define NPU_NAT_PRIVATE_IP_V6_INFO2_0_REG_ADDR (NPU_BASE_ADDR+0x50)
#define NAT_PRIVATE_IP_V6_INFO2_0_PRIVATE_IP_V6_INFO2_0_FIELD_OFFSET (0)
#define NAT_PRIVATE_IP_V6_INFO2_0_PRIVATE_IP_V6_INFO2_0_FIELD_SIZE   (32)

//-------------------------------------------------------------------------
// NAT_PRIVATE_IP_V6_INFO2_1 INFO:
//-------------------------------------------------------------------------
#define NPU_NAT_PRIVATE_IP_V6_INFO2_1_REG_ADDR (NPU_BASE_ADDR+0x54)
#define NAT_PRIVATE_IP_V6_INFO2_1_PRIVATE_IP_V6_INFO2_1_FIELD_OFFSET (0)
#define NAT_PRIVATE_IP_V6_INFO2_1_PRIVATE_IP_V6_INFO2_1_FIELD_SIZE   (32)

//-------------------------------------------------------------------------
// NAT_PRIVATE_IP_V6_INFO2_2 INFO:
//-------------------------------------------------------------------------
#define NPU_NAT_PRIVATE_IP_V6_INFO2_2_REG_ADDR (NPU_BASE_ADDR+0x58)
#define NAT_PRIVATE_IP_V6_INFO2_2_PRIVATE_IP_V6_INFO2_2_FIELD_OFFSET (0)
#define NAT_PRIVATE_IP_V6_INFO2_2_PRIVATE_IP_V6_INFO2_2_FIELD_SIZE   (32)

//-------------------------------------------------------------------------
// NAT_PRIVATE_IP_V6_INFO2_3 INFO:
//-------------------------------------------------------------------------
#define NPU_NAT_PRIVATE_IP_V6_INFO2_3_REG_ADDR (NPU_BASE_ADDR+0x5C)
#define NAT_PRIVATE_IP_V6_INFO2_3_PRIVATE_IP_V6_INFO2_3_FIELD_OFFSET (0)
#define NAT_PRIVATE_IP_V6_INFO2_3_PRIVATE_IP_V6_INFO2_3_FIELD_SIZE   (32)

//-------------------------------------------------------------------------
// NAT_PRIVATE_IP_V6_INFO3_0 INFO:
//-------------------------------------------------------------------------
#define NPU_NAT_PRIVATE_IP_V6_INFO3_0_REG_ADDR (NPU_BASE_ADDR+0x60)
#define NAT_PRIVATE_IP_V6_INFO3_0_PRIVATE_IP_V6_INFO3_0_FIELD_OFFSET (0)
#define NAT_PRIVATE_IP_V6_INFO3_0_PRIVATE_IP_V6_INFO3_0_FIELD_SIZE   (32)

//-------------------------------------------------------------------------
// NAT_PRIVATE_IP_V6_INFO3_1 INFO:
//-------------------------------------------------------------------------
#define NPU_NAT_PRIVATE_IP_V6_INFO3_1_REG_ADDR (NPU_BASE_ADDR+0x64)
#define NAT_PRIVATE_IP_V6_INFO3_1_PRIVATE_IP_V6_INFO3_1_FIELD_OFFSET (0)
#define NAT_PRIVATE_IP_V6_INFO3_1_PRIVATE_IP_V6_INFO3_1_FIELD_SIZE   (32)

//-------------------------------------------------------------------------
// NAT_PRIVATE_IP_V6_INFO3_2 INFO:
//-------------------------------------------------------------------------
#define NPU_NAT_PRIVATE_IP_V6_INFO3_2_REG_ADDR (NPU_BASE_ADDR+0x68)
#define NAT_PRIVATE_IP_V6_INFO3_2_PRIVATE_IP_V6_INFO3_2_FIELD_OFFSET (0)
#define NAT_PRIVATE_IP_V6_INFO3_2_PRIVATE_IP_V6_INFO3_2_FIELD_SIZE   (32)

//-------------------------------------------------------------------------
// NAT_PRIVATE_IP_V6_INFO3_3 INFO:
//-------------------------------------------------------------------------
#define NPU_NAT_PRIVATE_IP_V6_INFO3_3_REG_ADDR (NPU_BASE_ADDR+0x6C)
#define NAT_PRIVATE_IP_V6_INFO3_3_PRIVATE_IP_V6_INFO3_3_FIELD_OFFSET (0)
#define NAT_PRIVATE_IP_V6_INFO3_3_PRIVATE_IP_V6_INFO3_3_FIELD_SIZE   (32)

//-------------------------------------------------------------------------
// NAT_PRIVATE_IP_V6_INFO4_0 INFO:
//-------------------------------------------------------------------------
#define NPU_NAT_PRIVATE_IP_V6_INFO4_0_REG_ADDR (NPU_BASE_ADDR+0x70)
#define NAT_PRIVATE_IP_V6_INFO4_0_PRIVATE_IP_V6_INFO4_0_FIELD_OFFSET (0)
#define NAT_PRIVATE_IP_V6_INFO4_0_PRIVATE_IP_V6_INFO4_0_FIELD_SIZE   (32)

//-------------------------------------------------------------------------
// NAT_PRIVATE_IP_V6_INFO4_1 INFO:
//-------------------------------------------------------------------------
#define NPU_NAT_PRIVATE_IP_V6_INFO4_1_REG_ADDR (NPU_BASE_ADDR+0x74)
#define NAT_PRIVATE_IP_V6_INFO4_1_PRIVATE_IP_V6_INFO4_1_FIELD_OFFSET (0)
#define NAT_PRIVATE_IP_V6_INFO4_1_PRIVATE_IP_V6_INFO4_1_FIELD_SIZE   (32)

//-------------------------------------------------------------------------
// NAT_PRIVATE_IP_V6_INFO4_2 INFO:
//-------------------------------------------------------------------------
#define NPU_NAT_PRIVATE_IP_V6_INFO4_2_REG_ADDR (NPU_BASE_ADDR+0x78)
#define NAT_PRIVATE_IP_V6_INFO4_2_PRIVATE_IP_V6_INFO4_2_FIELD_OFFSET (0)
#define NAT_PRIVATE_IP_V6_INFO4_2_PRIVATE_IP_V6_INFO4_2_FIELD_SIZE   (32)

//-------------------------------------------------------------------------
// NAT_PRIVATE_IP_V6_INFO4_3 INFO:
//-------------------------------------------------------------------------
#define NPU_NAT_PRIVATE_IP_V6_INFO4_3_REG_ADDR (NPU_BASE_ADDR+0x7C)
#define NAT_PRIVATE_IP_V6_INFO4_3_PRIVATE_IP_V6_INFO4_3_FIELD_OFFSET (0)
#define NAT_PRIVATE_IP_V6_INFO4_3_PRIVATE_IP_V6_INFO4_3_FIELD_SIZE   (32)

//-------------------------------------------------------------------------
// NAT_PRIVATE_IP_V6_INFO5_0 INFO:
//-------------------------------------------------------------------------
#define NPU_NAT_PRIVATE_IP_V6_INFO5_0_REG_ADDR (NPU_BASE_ADDR+0x80)
#define NAT_PRIVATE_IP_V6_INFO5_0_PRIVATE_IP_V6_INFO5_0_FIELD_OFFSET (0)
#define NAT_PRIVATE_IP_V6_INFO5_0_PRIVATE_IP_V6_INFO5_0_FIELD_SIZE   (32)

//-------------------------------------------------------------------------
// NAT_PRIVATE_IP_V6_INFO5_1 INFO:
//-------------------------------------------------------------------------
#define NPU_NAT_PRIVATE_IP_V6_INFO5_1_REG_ADDR (NPU_BASE_ADDR+0x84)
#define NAT_PRIVATE_IP_V6_INFO5_1_PRIVATE_IP_V6_INFO5_1_FIELD_OFFSET (0)
#define NAT_PRIVATE_IP_V6_INFO5_1_PRIVATE_IP_V6_INFO5_1_FIELD_SIZE   (32)

//-------------------------------------------------------------------------
// NAT_PRIVATE_IP_V6_INFO5_2 INFO:
//-------------------------------------------------------------------------
#define NPU_NAT_PRIVATE_IP_V6_INFO5_2_REG_ADDR (NPU_BASE_ADDR+0x88)
#define NAT_PRIVATE_IP_V6_INFO5_2_PRIVATE_IP_V6_INFO5_2_FIELD_OFFSET (0)
#define NAT_PRIVATE_IP_V6_INFO5_2_PRIVATE_IP_V6_INFO5_2_FIELD_SIZE   (32)

//-------------------------------------------------------------------------
// NAT_PRIVATE_IP_V6_INFO5_3 INFO:
//-------------------------------------------------------------------------
#define NPU_NAT_PRIVATE_IP_V6_INFO5_3_REG_ADDR (NPU_BASE_ADDR+0x8C)
#define NAT_PRIVATE_IP_V6_INFO5_3_PRIVATE_IP_V6_INFO5_3_FIELD_OFFSET (0)
#define NAT_PRIVATE_IP_V6_INFO5_3_PRIVATE_IP_V6_INFO5_3_FIELD_SIZE   (32)

//-------------------------------------------------------------------------
// NAT_PRIVATE_IP_V6_INFO6_0 INFO:
//-------------------------------------------------------------------------
#define NPU_NAT_PRIVATE_IP_V6_INFO6_0_REG_ADDR (NPU_BASE_ADDR+0x90)
#define NAT_PRIVATE_IP_V6_INFO6_0_PRIVATE_IP_V6_INFO6_0_FIELD_OFFSET (0)
#define NAT_PRIVATE_IP_V6_INFO6_0_PRIVATE_IP_V6_INFO6_0_FIELD_SIZE   (32)

//-------------------------------------------------------------------------
// NAT_PRIVATE_IP_V6_INFO6_1 INFO:
//-------------------------------------------------------------------------
#define NPU_NAT_PRIVATE_IP_V6_INFO6_1_REG_ADDR (NPU_BASE_ADDR+0x94)
#define NAT_PRIVATE_IP_V6_INFO6_1_PRIVATE_IP_V6_INFO6_1_FIELD_OFFSET (0)
#define NAT_PRIVATE_IP_V6_INFO6_1_PRIVATE_IP_V6_INFO6_1_FIELD_SIZE   (32)

//-------------------------------------------------------------------------
// NAT_PRIVATE_IP_V6_INFO6_2 INFO:
//-------------------------------------------------------------------------
#define NPU_NAT_PRIVATE_IP_V6_INFO6_2_REG_ADDR (NPU_BASE_ADDR+0x98)
#define NAT_PRIVATE_IP_V6_INFO6_2_PRIVATE_IP_V6_INFO6_2_FIELD_OFFSET (0)
#define NAT_PRIVATE_IP_V6_INFO6_2_PRIVATE_IP_V6_INFO6_2_FIELD_SIZE   (32)

//-------------------------------------------------------------------------
// NAT_PRIVATE_IP_V6_INFO6_3 INFO:
//-------------------------------------------------------------------------
#define NPU_NAT_PRIVATE_IP_V6_INFO6_3_REG_ADDR (NPU_BASE_ADDR+0x9C)
#define NAT_PRIVATE_IP_V6_INFO6_3_PRIVATE_IP_V6_INFO6_3_FIELD_OFFSET (0)
#define NAT_PRIVATE_IP_V6_INFO6_3_PRIVATE_IP_V6_INFO6_3_FIELD_SIZE   (32)

//-------------------------------------------------------------------------
// NAT_PRIVATE_IP_V6_INFO7_0 INFO:
//-------------------------------------------------------------------------
#define NPU_NAT_PRIVATE_IP_V6_INFO7_0_REG_ADDR (NPU_BASE_ADDR+0xA0)
#define NAT_PRIVATE_IP_V6_INFO7_0_PRIVATE_IP_V6_INFO7_0_FIELD_OFFSET (0)
#define NAT_PRIVATE_IP_V6_INFO7_0_PRIVATE_IP_V6_INFO7_0_FIELD_SIZE   (32)

//-------------------------------------------------------------------------
// NAT_PRIVATE_IP_V6_INFO7_1 INFO:
//-------------------------------------------------------------------------
#define NPU_NAT_PRIVATE_IP_V6_INFO7_1_REG_ADDR (NPU_BASE_ADDR+0xA4)
#define NAT_PRIVATE_IP_V6_INFO7_1_PRIVATE_IP_V6_INFO7_1_FIELD_OFFSET (0)
#define NAT_PRIVATE_IP_V6_INFO7_1_PRIVATE_IP_V6_INFO7_1_FIELD_SIZE   (32)

//-------------------------------------------------------------------------
// NAT_PRIVATE_IP_V6_INFO7_2 INFO:
//-------------------------------------------------------------------------
#define NPU_NAT_PRIVATE_IP_V6_INFO7_2_REG_ADDR (NPU_BASE_ADDR+0xA8)
#define NAT_PRIVATE_IP_V6_INFO7_2_PRIVATE_IP_V6_INFO7_2_FIELD_OFFSET (0)
#define NAT_PRIVATE_IP_V6_INFO7_2_PRIVATE_IP_V6_INFO7_2_FIELD_SIZE   (32)

//-------------------------------------------------------------------------
// NAT_PRIVATE_IP_V6_INFO7_3 INFO:
//-------------------------------------------------------------------------
#define NPU_NAT_PRIVATE_IP_V6_INFO7_3_REG_ADDR (NPU_BASE_ADDR+0xAC)
#define NAT_PRIVATE_IP_V6_INFO7_3_PRIVATE_IP_V6_INFO7_3_FIELD_OFFSET (0)
#define NAT_PRIVATE_IP_V6_INFO7_3_PRIVATE_IP_V6_INFO7_3_FIELD_SIZE   (32)

//-------------------------------------------------------------------------
// NAT_IPV6_MASK_LEN01 INFO:
//-------------------------------------------------------------------------
#define NPU_NAT_IPV6_MASK_LEN01_REG_ADDR (NPU_BASE_ADDR+0xB0)
#define NAT_IPV6_MASK_LEN1_RSVD_FIELD_OFFSET (25)
#define NAT_IPV6_MASK_LEN1_RSVD_FIELD_SIZE   (7)
#define NAT_IPV6_MASK_LEN1_IP_V6_MASK_LEN1_FIELD_OFFSET (16)
#define NAT_IPV6_MASK_LEN1_IP_V6_MASK_LEN1_FIELD_SIZE   (9)
#define NAT_IPV6_MASK_LEN0_RSVD_FIELD_OFFSET (9)
#define NAT_IPV6_MASK_LEN0_RSVD_FIELD_SIZE   (7)
#define NAT_IPV6_MASK_LEN0_IP_V6_MASK_LEN0_FIELD_OFFSET (0)
#define NAT_IPV6_MASK_LEN0_IP_V6_MASK_LEN0_FIELD_SIZE   (9)

//-------------------------------------------------------------------------
// NAT_IPV6_MASK_LEN23 INFO:
//-------------------------------------------------------------------------
#define NPU_NAT_IPV6_MASK_LEN23_REG_ADDR (NPU_BASE_ADDR+0xB4)
#define NAT_IPV6_MASK_LEN3_RSVD_FIELD_OFFSET (25)
#define NAT_IPV6_MASK_LEN3_RSVD_FIELD_SIZE   (7)
#define NAT_IPV6_MASK_LEN3_IP_V6_MASK_LEN3_FIELD_OFFSET (16)
#define NAT_IPV6_MASK_LEN3_IP_V6_MASK_LEN3_FIELD_SIZE   (9)
#define NAT_IPV6_MASK_LEN2_RSVD_FIELD_OFFSET (9)
#define NAT_IPV6_MASK_LEN2_RSVD_FIELD_SIZE   (7)
#define NAT_IPV6_MASK_LEN2_IP_V6_MASK_LEN2_FIELD_OFFSET (0)
#define NAT_IPV6_MASK_LEN2_IP_V6_MASK_LEN2_FIELD_SIZE   (9)

//-------------------------------------------------------------------------
// NAT_IPV6_MASK_LEN45 INFO:
//-------------------------------------------------------------------------
#define NPU_NAT_IPV6_MASK_LEN45_REG_ADDR (NPU_BASE_ADDR+0xB8)
#define NAT_IPV6_MASK_LEN5_RSVD_FIELD_OFFSET (25)
#define NAT_IPV6_MASK_LEN5_RSVD_FIELD_SIZE   (7)
#define NAT_IPV6_MASK_LEN5_IP_V6_MASK_LEN5_FIELD_OFFSET (16)
#define NAT_IPV6_MASK_LEN5_IP_V6_MASK_LEN5_FIELD_SIZE   (9)
#define NAT_IPV6_MASK_LEN4_RSVD_FIELD_OFFSET (9)
#define NAT_IPV6_MASK_LEN4_RSVD_FIELD_SIZE   (7)
#define NAT_IPV6_MASK_LEN4_IP_V6_MASK_LEN4_FIELD_OFFSET (0)
#define NAT_IPV6_MASK_LEN4_IP_V6_MASK_LEN4_FIELD_SIZE   (9)

//-------------------------------------------------------------------------
// NAT_IPV6_MASK_LEN67_HOST_MODE INFO:
//-------------------------------------------------------------------------
#define NPU_NAT_IPV6_MASK_LEN67_HOST_MODE_REG_ADDR (NPU_BASE_ADDR+0xBC)
#define NAT_IPV6_MASK_LEN67_HOST_MODE_RSVD_FIELD_OFFSET (22)
#define NAT_IPV6_MASK_LEN67_HOST_MODE_RSVD_FIELD_SIZE   (10)
#define NAT_IPV6_MASK_LEN67_HOST_MODE_HNAT_MODE_FIELD_OFFSET (19)
#define NAT_IPV6_MASK_LEN67_HOST_MODE_HNAT_MODE_FIELD_SIZE   (3)
#define NAT_IPV6_MASK_LEN67_HOST_MODE_FORCE_TTL1_UP2CPU_FIELD_OFFSET (18)
#define NAT_IPV6_MASK_LEN67_HOST_MODE_FORCE_TTL1_UP2CPU_FIELD_SIZE   (1)
#define NAT_IPV6_MASK_LEN67_HOST_MODE_IP_V6_MASK_LEN7_FIELD_OFFSET (9)
#define NAT_IPV6_MASK_LEN67_HOST_MODE_IP_V6_MASK_LEN7_FIELD_SIZE   (9)
#define NAT_IPV6_MASK_LEN67_HOST_MODE_IP_V6_MASK_LEN6_FIELD_OFFSET (0)
#define NAT_IPV6_MASK_LEN67_HOST_MODE_IP_V6_MASK_LEN6_FIELD_SIZE   (9)

//-------------------------------------------------------------------------
// IVLAN_PORT_MPP_CFG INFO:
//-------------------------------------------------------------------------
#define NPU_IVLAN_PORT_MPP_CFG_REG_ADDR (NPU_BASE_ADDR+0x4000)
#define IVLAN_PORT_MPP_CFG_RSVD_FIELD_OFFSET (17)
#define IVLAN_PORT_MPP_CFG_RSVD_FIELD_SIZE   (15)
#define IVLAN_PORT_MPP_CFG_CFG_MPP_BYPASS_FIELD_OFFSET (16)
#define IVLAN_PORT_MPP_CFG_CFG_MPP_BYPASS_FIELD_SIZE   (1)
#define IVLAN_PORT_MPP_CFG_RESP_FIFO_AFULL_THRESH_FIELD_OFFSET (12)
#define IVLAN_PORT_MPP_CFG_RESP_FIFO_AFULL_THRESH_FIELD_SIZE   (4)
#define IVLAN_PORT_MPP_CFG_VOQ_1_FIFO_AFULL_THRESH_FIELD_OFFSET (8)
#define IVLAN_PORT_MPP_CFG_VOQ_1_FIFO_AFULL_THRESH_FIELD_SIZE   (4)
#define IVLAN_PORT_MPP_CFG_VOQ_0_FIFO_AFULL_THRESH_FIELD_OFFSET (4)
#define IVLAN_PORT_MPP_CFG_VOQ_0_FIFO_AFULL_THRESH_FIELD_SIZE   (4)
#define IVLAN_PORT_MPP_CFG_FP_FIFO_AFULL_THRESH_FIELD_OFFSET (0)
#define IVLAN_PORT_MPP_CFG_FP_FIFO_AFULL_THRESH_FIELD_SIZE   (4)

//-------------------------------------------------------------------------
// IVLAN_VID_MPP_CFG INFO:
//-------------------------------------------------------------------------
#define NPU_IVLAN_VID_MPP_CFG_REG_ADDR (NPU_BASE_ADDR+0x8000)
#define IVLAN_VID_MPP_CFG_RSVD_FIELD_OFFSET (22)
#define IVLAN_VID_MPP_CFG_RSVD_FIELD_SIZE   (10)
#define IVLAN_VID_MPP_CFG_DROP_OTHER_IVLAN_FORCE_UP_FIELD_OFFSET (21)
#define IVLAN_VID_MPP_CFG_DROP_OTHER_IVLAN_FORCE_UP_FIELD_SIZE   (1)
#define IVLAN_VID_MPP_CFG_DROP_OTHER_OVLAN_FORCE_UP_FIELD_OFFSET (20)
#define IVLAN_VID_MPP_CFG_DROP_OTHER_OVLAN_FORCE_UP_FIELD_SIZE   (1)
#define IVLAN_VID_MPP_CFG_VT_MISS_DROP_FORCE_UP_FIELD_OFFSET (19)
#define IVLAN_VID_MPP_CFG_VT_MISS_DROP_FORCE_UP_FIELD_SIZE   (1)
#define IVLAN_VID_MPP_CFG_PORT_BASED_VID_ENABLE_FIELD_OFFSET (18)
#define IVLAN_VID_MPP_CFG_PORT_BASED_VID_ENABLE_FIELD_SIZE   (1)
#define IVLAN_VID_MPP_CFG_QUEUE_ID_REPLACE_EN_FIELD_OFFSET (17)
#define IVLAN_VID_MPP_CFG_QUEUE_ID_REPLACE_EN_FIELD_SIZE   (1)
#define IVLAN_VID_MPP_CFG_CFG_MPP_BYPASS_FIELD_OFFSET (16)
#define IVLAN_VID_MPP_CFG_CFG_MPP_BYPASS_FIELD_SIZE   (1)
#define IVLAN_VID_MPP_CFG_RESP_FIFO_AFULL_THRESH_FIELD_OFFSET (12)
#define IVLAN_VID_MPP_CFG_RESP_FIFO_AFULL_THRESH_FIELD_SIZE   (4)
#define IVLAN_VID_MPP_CFG_VOQ_1_FIFO_AFULL_THRESH_FIELD_OFFSET (8)
#define IVLAN_VID_MPP_CFG_VOQ_1_FIFO_AFULL_THRESH_FIELD_SIZE   (4)
#define IVLAN_VID_MPP_CFG_VOQ_0_FIFO_AFULL_THRESH_FIELD_OFFSET (4)
#define IVLAN_VID_MPP_CFG_VOQ_0_FIFO_AFULL_THRESH_FIELD_SIZE   (4)
#define IVLAN_VID_MPP_CFG_FP_FIFO_AFULL_THRESH_FIELD_OFFSET (0)
#define IVLAN_VID_MPP_CFG_FP_FIFO_AFULL_THRESH_FIELD_SIZE   (4)

//-------------------------------------------------------------------------
// IVLAN_LKP_MPP_CFG0 INFO:
//-------------------------------------------------------------------------
#define NPU_IVLAN_LKP_MPP_CFG0_REG_ADDR (NPU_BASE_ADDR+0xC000)
#define IVLAN_LKP_MPP_CFG0_RSVD_FIELD_OFFSET (19)
#define IVLAN_LKP_MPP_CFG0_RSVD_FIELD_SIZE   (13)
#define IVLAN_LKP_MPP_CFG0_PORT_STG_STATUS_FIELD_OFFSET (17)
#define IVLAN_LKP_MPP_CFG0_PORT_STG_STATUS_FIELD_SIZE   (2)
#define IVLAN_LKP_MPP_CFG0_CFG_MPP_BYPASS_FIELD_OFFSET (16)
#define IVLAN_LKP_MPP_CFG0_CFG_MPP_BYPASS_FIELD_SIZE   (1)
#define IVLAN_LKP_MPP_CFG0_RESP_FIFO_AFULL_THRESH_FIELD_OFFSET (12)
#define IVLAN_LKP_MPP_CFG0_RESP_FIFO_AFULL_THRESH_FIELD_SIZE   (4)
#define IVLAN_LKP_MPP_CFG0_VOQ_1_FIFO_AFULL_THRESH_FIELD_OFFSET (8)
#define IVLAN_LKP_MPP_CFG0_VOQ_1_FIFO_AFULL_THRESH_FIELD_SIZE   (4)
#define IVLAN_LKP_MPP_CFG0_VOQ_0_FIFO_AFULL_THRESH_FIELD_OFFSET (4)
#define IVLAN_LKP_MPP_CFG0_VOQ_0_FIFO_AFULL_THRESH_FIELD_SIZE   (4)
#define IVLAN_LKP_MPP_CFG0_FP_FIFO_AFULL_THRESH_FIELD_OFFSET (0)
#define IVLAN_LKP_MPP_CFG0_FP_FIFO_AFULL_THRESH_FIELD_SIZE   (4)

//-------------------------------------------------------------------------
// IVLAN_LKP_MPP_CFG1 INFO:
//-------------------------------------------------------------------------
#define NPU_IVLAN_LKP_MPP_CFG1_REG_ADDR (NPU_BASE_ADDR+0xC004)
#define IVLAN_LKP_MPP_CFG1_RSVD_FIELD_OFFSET (11)
#define IVLAN_LKP_MPP_CFG1_RSVD_FIELD_SIZE   (21)
#define IVLAN_LKP_MPP_CFG1_PORT_BITMAP_MISS_FORCE_UP_FIELD_OFFSET (10)
#define IVLAN_LKP_MPP_CFG1_PORT_BITMAP_MISS_FORCE_UP_FIELD_SIZE   (1)
#define IVLAN_LKP_MPP_CFG1_VLAN_MISS_FORCE_UP_FIELD_OFFSET (9)
#define IVLAN_LKP_MPP_CFG1_VLAN_MISS_FORCE_UP_FIELD_SIZE   (1)
#define IVLAN_LKP_MPP_CFG1_VLAN_MISS_FIELD_OFFSET (0)
#define IVLAN_LKP_MPP_CFG1_VLAN_MISS_FIELD_SIZE   (9)

//-------------------------------------------------------------------------
// ARP_MPP_CFG INFO:
//-------------------------------------------------------------------------
#define NPU_ARP_MPP_CFG_REG_ADDR (NPU_BASE_ADDR+0x10000)
#define ARP_MPP_CFG_RSVD_FIELD_OFFSET (22)
#define ARP_MPP_CFG_RSVD_FIELD_SIZE   (10)
#define ARP_MPP_CFG_OVID_SEL_FIELD_OFFSET (21)
#define ARP_MPP_CFG_OVID_SEL_FIELD_SIZE   (1)
#define ARP_MPP_CFG_COND_DEL_ENABLE_FIELD_OFFSET (20)
#define ARP_MPP_CFG_COND_DEL_ENABLE_FIELD_SIZE   (1)
#define ARP_MPP_CFG_COND_ADD_ENABLE_FIELD_OFFSET (19)
#define ARP_MPP_CFG_COND_ADD_ENABLE_FIELD_SIZE   (1)
#define ARP_MPP_CFG_L3_UNKNOW_ACTION_FIELD_OFFSET (18)
#define ARP_MPP_CFG_L3_UNKNOW_ACTION_FIELD_SIZE   (1)
#define ARP_MPP_CFG_MS_SMAC_EN_FIELD_OFFSET (17)
#define ARP_MPP_CFG_MS_SMAC_EN_FIELD_SIZE   (1)
#define ARP_MPP_CFG_CFG_MPP_BYPASS_FIELD_OFFSET (16)
#define ARP_MPP_CFG_CFG_MPP_BYPASS_FIELD_SIZE   (1)
#define ARP_MPP_CFG_RESP_FIFO_AFULL_THRESH_FIELD_OFFSET (12)
#define ARP_MPP_CFG_RESP_FIFO_AFULL_THRESH_FIELD_SIZE   (4)
#define ARP_MPP_CFG_VOQ_1_FIFO_AFULL_THRESH_FIELD_OFFSET (8)
#define ARP_MPP_CFG_VOQ_1_FIFO_AFULL_THRESH_FIELD_SIZE   (4)
#define ARP_MPP_CFG_VOQ_0_FIFO_AFULL_THRESH_FIELD_OFFSET (4)
#define ARP_MPP_CFG_VOQ_0_FIFO_AFULL_THRESH_FIELD_SIZE   (4)
#define ARP_MPP_CFG_FP_FIFO_AFULL_THRESH_FIELD_OFFSET (0)
#define ARP_MPP_CFG_FP_FIFO_AFULL_THRESH_FIELD_SIZE   (4)

//-------------------------------------------------------------------------
// EVLAN_LKP_CFG INFO:
//-------------------------------------------------------------------------
#define NPU_EVLAN_LKP_CFG_REG_ADDR (NPU_BASE_ADDR+0x14000)
#define EVLAN_LKP_CFG_RSVD_FIELD_OFFSET (22)
#define EVLAN_LKP_CFG_RSVD_FIELD_SIZE   (10)
#define EVLAN_LKP_CFG_STG_DIS_FORCE_UP_FIELD_OFFSET (21)
#define EVLAN_LKP_CFG_STG_DIS_FORCE_UP_FIELD_SIZE   (1)
#define EVLAN_LKP_CFG_VLAN_CHECK_ERR_FORCE_UP_FIELD_OFFSET (20)
#define EVLAN_LKP_CFG_VLAN_CHECK_ERR_FORCE_UP_FIELD_SIZE   (1)
#define EVLAN_LKP_CFG_PORT_BITMAP_DROP_FORCE_UP_FIELD_OFFSET (19)
#define EVLAN_LKP_CFG_PORT_BITMAP_DROP_FORCE_UP_FIELD_SIZE   (1)
#define EVLAN_LKP_CFG_TPID_SEL_FIELD_OFFSET (18)
#define EVLAN_LKP_CFG_TPID_SEL_FIELD_SIZE   (1)
#define EVLAN_LKP_CFG_MCAST_RVID_EN_FIELD_OFFSET (17)
#define EVLAN_LKP_CFG_MCAST_RVID_EN_FIELD_SIZE   (1)
#define EVLAN_LKP_CFG_CFG_MPP_BYPASS_FIELD_OFFSET (16)
#define EVLAN_LKP_CFG_CFG_MPP_BYPASS_FIELD_SIZE   (1)
#define EVLAN_LKP_CFG_RESP_FIFO_AFULL_THRESH_FIELD_OFFSET (12)
#define EVLAN_LKP_CFG_RESP_FIFO_AFULL_THRESH_FIELD_SIZE   (4)
#define EVLAN_LKP_CFG_VOQ_1_FIFO_AFULL_THRESH_FIELD_OFFSET (8)
#define EVLAN_LKP_CFG_VOQ_1_FIFO_AFULL_THRESH_FIELD_SIZE   (4)
#define EVLAN_LKP_CFG_VOQ_0_FIFO_AFULL_THRESH_FIELD_OFFSET (4)
#define EVLAN_LKP_CFG_VOQ_0_FIFO_AFULL_THRESH_FIELD_SIZE   (4)
#define EVLAN_LKP_CFG_FP_FIFO_AFULL_THRESH_FIELD_OFFSET (0)
#define EVLAN_LKP_CFG_FP_FIFO_AFULL_THRESH_FIELD_SIZE   (4)

//-------------------------------------------------------------------------
// EVLAN_XLT_CFG0 INFO:
//-------------------------------------------------------------------------
#define NPU_EVLAN_XLT_CFG0_REG_ADDR (NPU_BASE_ADDR+0x18000)
#define EVLAN_XLT_CFG0_COND2_RSVD_FIELD_OFFSET (30)
#define EVLAN_XLT_CFG0_COND2_RSVD_FIELD_SIZE   (2)
#define EVLAN_XLT_CFG0_TRANS_COND2_PTR_FIELD_OFFSET (24)
#define EVLAN_XLT_CFG0_TRANS_COND2_PTR_FIELD_SIZE   (6)
#define EVLAN_XLT_CFG0_COND1_RSVD_FIELD_OFFSET (23)
#define EVLAN_XLT_CFG0_COND1_RSVD_FIELD_SIZE   (1)
#define EVLAN_XLT_CFG0_TRANS_COND1_PTR_FIELD_OFFSET (17)
#define EVLAN_XLT_CFG0_TRANS_COND1_PTR_FIELD_SIZE   (6)
#define EVLAN_XLT_CFG0_CFG_MPP_BYPASS_FIELD_OFFSET (16)
#define EVLAN_XLT_CFG0_CFG_MPP_BYPASS_FIELD_SIZE   (1)
#define EVLAN_XLT_CFG0_RESP_FIFO_AFULL_THRESH_FIELD_OFFSET (12)
#define EVLAN_XLT_CFG0_RESP_FIFO_AFULL_THRESH_FIELD_SIZE   (4)
#define EVLAN_XLT_CFG0_VOQ_1_FIFO_AFULL_THRESH_FIELD_OFFSET (8)
#define EVLAN_XLT_CFG0_VOQ_1_FIFO_AFULL_THRESH_FIELD_SIZE   (4)
#define EVLAN_XLT_CFG0_VOQ_0_FIFO_AFULL_THRESH_FIELD_OFFSET (4)
#define EVLAN_XLT_CFG0_VOQ_0_FIFO_AFULL_THRESH_FIELD_SIZE   (4)
#define EVLAN_XLT_CFG0_FP_FIFO_AFULL_THRESH_FIELD_OFFSET (0)
#define EVLAN_XLT_CFG0_FP_FIFO_AFULL_THRESH_FIELD_SIZE   (4)

//-------------------------------------------------------------------------
// EVLAN_XLT_CFG1 INFO:
//-------------------------------------------------------------------------
#define NPU_EVLAN_XLT_CFG1_REG_ADDR (NPU_BASE_ADDR+0x18004)
#define EVLAN_XLT_CFG1_COND1_RSVD_FIELD_OFFSET (30)
#define EVLAN_XLT_CFG1_RSVD_FIELD_SIZE   (2)
#define EVLAN_XLT_CFG1_SECUR_COND1_PTR_FIELD_OFFSET (24)
#define EVLAN_XLT_CFG1_SECUR_COND1_PTR_FIELD_SIZE   (6)
#define EVLAN_XLT_CFG1_COND5_RSVD_FIELD_OFFSET (22)
#define EVLAN_XLT_CFG1_TRANS_COND5_PTR_FIELD_OFFSET (16)
#define EVLAN_XLT_CFG1_TRANS_COND5_PTR_FIELD_SIZE   (6)
#define EVLAN_XLT_CFG1_COND4_RSVD_FIELD_OFFSET (14)
#define EVLAN_XLT_CFG1_TRANS_COND4_PTR_FIELD_OFFSET (8)
#define EVLAN_XLT_CFG1_TRANS_COND4_PTR_FIELD_SIZE   (6)
#define EVLAN_XLT_CFG1_COND3_RSVD_FIELD_OFFSET (6)
#define EVLAN_XLT_CFG1_TRANS_COND3_PTR_FIELD_OFFSET (0)
#define EVLAN_XLT_CFG1_TRANS_COND3_PTR_FIELD_SIZE   (6)

//-------------------------------------------------------------------------
// EVLAN_XLT_CFG2 INFO:
//-------------------------------------------------------------------------
#define NPU_EVLAN_XLT_CFG2_REG_ADDR (NPU_BASE_ADDR+0x18008)
#define EVLAN_XLT_CFG2_VT_MISS_UT_DROP_FIELD_OFFSET (31)
#define EVLAN_XLT_CFG2_VT_MISS_UT_DROP_FIELD_SIZE   (1)
#define EVLAN_XLT_CFG2_VT_MISS_DROP_FIELD_OFFSET (30)
#define EVLAN_XLT_CFG2_VT_MISS_DROP_FIELD_SIZE   (1)
#define EVLAN_XLT_CFG2_VT_MISS_UT_PTR_FIELD_OFFSET (24)
#define EVLAN_XLT_CFG2_VT_MISS_UT_PTR_FIELD_SIZE   (6)
#define EVLAN_XLT_CFG2_UNTAG_RSVD_FIELD_OFFSET (22)
#define EVLAN_XLT_CFG2_UNTAG_RSVD_FIELD_SIZE   (2)
#define EVLAN_XLT_CFG2_PKT_UNTAG_PTR_FIELD_OFFSET (16)
#define EVLAN_XLT_CFG2_PKT_UNTAG_PTR_FIELD_SIZE   (6)
#define EVLAN_XLT_CFG2_COND3_RSVD_FIELD_OFFSET (14)
#define EVLAN_XLT_CFG2_COND3_RSVD_FIELD_SIZE   (2)
#define EVLAN_XLT_CFG2_SECUR_COND3_PTR_FIELD_OFFSET (8)
#define EVLAN_XLT_CFG2_SECUR_COND3_PTR_FIELD_SIZE   (6)
#define EVLAN_XLT_CFG2_COND2_RSVD_FIELD_OFFSET (6)
#define EVLAN_XLT_CFG2_COND2_RSVD_FIELD_SIZE   (2)
#define EVLAN_XLT_CFG2_SECUR_COND2_PTR_FIELD_OFFSET (0)
#define EVLAN_XLT_CFG2_SECUR_COND2_PTR_FIELD_SIZE   (6)

//-------------------------------------------------------------------------
// EVLAN_XLT_CFG3 INFO:
//-------------------------------------------------------------------------
#define NPU_EVLAN_XLT_CFG3_REG_ADDR (NPU_BASE_ADDR+0x1800C)
#define EVLAN_XLT_CFG3_OVID_RSVD_FIELD_OFFSET (20)
#define EVLAN_XLT_CFG3_OVID_RSVD_FIELD_SIZE   (12)
#define EVLAN_XLT_CFG3_BACKUP_OVID_FIELD_OFFSET (8)
#define EVLAN_XLT_CFG3_BACKUP_OVID_FIELD_SIZE   (12)
#define EVLAN_XLT_CFG3_ACT_RSVD_FIELD_OFFSET (7)
#define EVLAN_XLT_CFG3_ACT_RSVD_FIELD_SIZE   (1)
#define EVLAN_XLT_CFG3_BACKUP_ACT_PTR_FIELD_OFFSET (1)
#define EVLAN_XLT_CFG3_BACKUP_ACT_PTR_FIELD_SIZE   (6)
#define EVLAN_XLT_CFG3_VT_MISS_UT_FIELD_OFFSET (0)
#define EVLAN_XLT_CFG3_VT_MISS_UT_FIELD_SIZE   (1)

//-------------------------------------------------------------------------
// EVLAN_XLT_CFG4 INFO:
//-------------------------------------------------------------------------
#define NPU_EVLAN_XLT_CFG4_REG_ADDR (NPU_BASE_ADDR+0x18010)
#define EVLAN_XLT_CFG4_RSVD_FIELD_OFFSET (20)
#define EVLAN_XLT_CFG4_RSVD_FIELD_SIZE   (12)
#define EVLAN_XLT_CFG4_VT_MISS_UT_DROP_FORCE_UP_FIELD_OFFSET (19)
#define EVLAN_XLT_CFG4_VT_MISS_UT_DROP_FORCE_UP_FIELD_SIZE   (1)
#define EVLAN_XLT_CFG4_VT_MISS_DROP_FORCE_UP_FIELD_OFFSET (18)
#define EVLAN_XLT_CFG4_VT_MISS_DROP_FORCE_UP_FIELD_SIZE   (1)
#define EVLAN_XLT_CFG4_BACKUP_IPRI_FIELD_OFFSET (15)
#define EVLAN_XLT_CFG4_BACKUP_IPRI_FIELD_SIZE   (3)
#define EVLAN_XLT_CFG4_BACKUP_OPRI_FIELD_OFFSET (12)
#define EVLAN_XLT_CFG4_BACKUP_OPRI_FIELD_SIZE   (3)
#define EVLAN_XLT_CFG4_BACKUP_IVID_FIELD_OFFSET (0)
#define EVLAN_XLT_CFG4_BACKUP_IVID_FIELD_SIZE   (12)

//-------------------------------------------------------------------------
// EVLAN_ACT_CFG INFO:
//-------------------------------------------------------------------------
#define NPU_EVLAN_ACT_CFG_REG_ADDR (NPU_BASE_ADDR+0x1C000)
#define EVLAN_ACT_CFG_RSVD_FIELD_OFFSET (17)
#define EVLAN_ACT_CFG_RSVD_FIELD_SIZE   (15)
#define EVLAN_ACT_CFG_CFG_MPP_BYPASS_FIELD_OFFSET (16)
#define EVLAN_ACT_CFG_CFG_MPP_BYPASS_FIELD_SIZE   (1)
#define EVLAN_ACT_CFG_RESP_FIFO_AFULL_THRESH_FIELD_OFFSET (12)
#define EVLAN_ACT_CFG_RESP_FIFO_AFULL_THRESH_FIELD_SIZE   (4)
#define EVLAN_ACT_CFG_VOQ_1_FIFO_AFULL_THRESH_FIELD_OFFSET (8)
#define EVLAN_ACT_CFG_VOQ_1_FIFO_AFULL_THRESH_FIELD_SIZE   (4)
#define EVLAN_ACT_CFG_VOQ_0_FIFO_AFULL_THRESH_FIELD_OFFSET (4)
#define EVLAN_ACT_CFG_VOQ_0_FIFO_AFULL_THRESH_FIELD_SIZE   (4)
#define EVLAN_ACT_CFG_FP_FIFO_AFULL_THRESH_FIELD_OFFSET (0)
#define EVLAN_ACT_CFG_FP_FIFO_AFULL_THRESH_FIELD_SIZE   (4)

//-------------------------------------------------------------------------
// L3_MPP_CFG INFO:
//-------------------------------------------------------------------------
#define NPU_L3_MPP_CFG_REG_ADDR (NPU_BASE_ADDR+0x20000)
#define L3_MPP_CFG_RSVD_FIELD_OFFSET (28)
#define L3_MPP_CFG_RSVD_FIELD_SIZE   (4)
#define L3_MPP_CFG_L3_MISS_PUNT_EN_FIELD_OFFSET (27)
#define L3_MPP_CFG_L3_MISS_PUNT_EN_FIELD_SIZE   (1)
#define L3_MPP_CFG_MC_USE_L2_EN_FIELD_OFFSET (26)
#define L3_MPP_CFG_MC_USE_L2_EN_FIELD_SIZE   (1)
#define L3_MPP_CFG_CPU_PORT_ID_FIELD_OFFSET (20)
#define L3_MPP_CFG_CPU_PORT_ID_FIELD_SIZE   (6)
#define L3_MPP_CFG_L3_CARE_NAT_RESULT_EN_FIELD_OFFSET (19)
#define L3_MPP_CFG_L3_CARE_NAT_RESULT_EN_FIELD_SIZE   (1)
#define L3_MPP_CFG_ASM_EN_FIELD_OFFSET (18)
#define L3_MPP_CFG_ASM_EN_FIELD_SIZE   (1)
#define L3_MPP_CFG_SSM_EN_FIELD_OFFSET (17)
#define L3_MPP_CFG_SSM_EN_FIELD_SIZE   (1)
#define L3_MPP_CFG_CFG_MPP_BYPASS_FIELD_OFFSET (16)
#define L3_MPP_CFG_CFG_MPP_BYPASS_FIELD_SIZE   (1)
#define L3_MPP_CFG_RESP_FIFO_AFULL_THRESH_FIELD_OFFSET (12)
#define L3_MPP_CFG_RESP_FIFO_AFULL_THRESH_FIELD_SIZE   (4)
#define L3_MPP_CFG_VOQ_1_FIFO_AFULL_THRESH_FIELD_OFFSET (8)
#define L3_MPP_CFG_VOQ_1_FIFO_AFULL_THRESH_FIELD_SIZE   (4)
#define L3_MPP_CFG_VOQ_0_FIFO_AFULL_THRESH_FIELD_OFFSET (4)
#define L3_MPP_CFG_VOQ_0_FIFO_AFULL_THRESH_FIELD_SIZE   (4)
#define L3_MPP_CFG_FP_FIFO_AFULL_THRESH_FIELD_OFFSET (0)
#define L3_MPP_CFG_FP_FIFO_AFULL_THRESH_FIELD_SIZE   (4)

//-------------------------------------------------------------------------
// L2_MPP_CFG INFO:
//-------------------------------------------------------------------------
#define NPU_L2_MPP_CFG_REG_ADDR (NPU_BASE_ADDR+0x24000)
#define L2_MPP_CFG_RSVD_FIELD_OFFSET (17)
#define L2_MPP_CFG_RSVD_FIELD_SIZE   (15)
#define L2_MPP_CFG_CFG_MPP_BYPASS_FIELD_OFFSET (16)
#define L2_MPP_CFG_CFG_MPP_BYPASS_FIELD_SIZE   (1)
#define L2_MPP_CFG_RESP_FIFO_AFULL_THRESH_FIELD_OFFSET (12)
#define L2_MPP_CFG_RESP_FIFO_AFULL_THRESH_FIELD_SIZE   (4)
#define L2_MPP_CFG_VOQ_1_FIFO_AFULL_THRESH_FIELD_OFFSET (8)
#define L2_MPP_CFG_VOQ_1_FIFO_AFULL_THRESH_FIELD_SIZE   (4)
#define L2_MPP_CFG_VOQ_0_FIFO_AFULL_THRESH_FIELD_OFFSET (4)
#define L2_MPP_CFG_VOQ_0_FIFO_AFULL_THRESH_FIELD_SIZE   (4)
#define L2_MPP_CFG_FP_FIFO_AFULL_THRESH_FIELD_OFFSET (0)
#define L2_MPP_CFG_FP_FIFO_AFULL_THRESH_FIELD_SIZE   (4)

//-------------------------------------------------------------------------
// L2_MPP_CFG2 INFO:
//-------------------------------------------------------------------------
#define NPU_L2_MPP_CFG2_REG_ADDR (NPU_BASE_ADDR+0x24004)
#define L2_MPP_CFG2_DIS_DROP_RSVD_FIELD_OFFSET (27)
#define L2_MPP_CFG2_DIS_DROP_RSVD_FIELD_SIZE   (5)
#define L2_MPP_CFG2_PKT_DIS_DROP_FIELD_OFFSET (22)
#define L2_MPP_CFG2_PKT_DIS_DROP_FIELD_SIZE   (1)
#define L2_MPP_CFG2_DA_SRCH_EN_RSVD_FIELD_OFFSET (12)
#define L2_MPP_CFG2_DA_SRCH_EN_RSVD_FIELD_SIZE   (10)
#define L2_MPP_CFG2_BCAST_DA_SRCH_EN_FIELD_OFFSET (11)
#define L2_MPP_CFG2_BCAST_DA_SRCH_EN_FIELD_SIZE   (1)
#define L2_MPP_CFG2_MCAST_DA_SRCH_EN_FIELD_OFFSET (10)
#define L2_MPP_CFG2_MCAST_DA_SRCH_EN_FIELD_SIZE   (1)
#define L2_MPP_CFG2_I_PORT_802X_STATUS_FIELD_OFFSET (0)
#define L2_MPP_CFG2_I_PORT_802X_STATUS_FIELD_SIZE   (10)

//-------------------------------------------------------------------------
// L2_LOCAL_IPV4_0 INFO:
//-------------------------------------------------------------------------
#define NPU_L2_LOCAL_IPV4_0_REG_ADDR (NPU_BASE_ADDR+0x24008)
#define L2_LOCAL_IPV4_0_LOCAL_IPV4_FIELD_OFFSET (0)
#define L2_LOCAL_IPV4_0_LOCAL_IPV4_FIELD_SIZE   (32)

//-------------------------------------------------------------------------
// L2_LOCAL_IPV4_1 INFO:
//-------------------------------------------------------------------------
#define NPU_L2_LOCAL_IPV4_1_REG_ADDR (NPU_BASE_ADDR+0x2400C)
#define L2_LOCAL_IPV4_1_LOCAL_IPV4_0_FIELD_OFFSET (0)
#define L2_LOCAL_IPV4_1_LOCAL_IPV4_0_FIELD_SIZE   (32)

//-------------------------------------------------------------------------
// L2_LOCAL_IPV4_2 INFO:
//-------------------------------------------------------------------------
#define NPU_L2_LOCAL_IPV4_2_REG_ADDR (NPU_BASE_ADDR+0x24010)
#define L2_LOCAL_IPV4_2_LOCAL_IPV4_1_FIELD_OFFSET (0)
#define L2_LOCAL_IPV4_2_LOCAL_IPV4_1_FIELD_SIZE   (32)

//-------------------------------------------------------------------------
// L2_LOCAL_IPV4_3 INFO:
//-------------------------------------------------------------------------
#define NPU_L2_LOCAL_IPV4_3_REG_ADDR (NPU_BASE_ADDR+0x24014)
#define L2_LOCAL_IPV4_3_LOCAL_IPV4_2_FIELD_OFFSET (0)
#define L2_LOCAL_IPV4_3_LOCAL_IPV4_2_FIELD_SIZE   (32)

//-------------------------------------------------------------------------
// L2_CFG_UP INFO:
//-------------------------------------------------------------------------
#define NPU_L2_CFG_UP_REG_ADDR (NPU_BASE_ADDR+0x24018)
#define L2_CFG_UP_RSVD_FIELD_OFFSET (5)
#define L2_CFG_UP_RSVD_FIELD_SIZE   (27)
#define L2_CFG_UP_X_UNAUTH_FORCE_UP_FIELD_OFFSET (4)
#define L2_CFG_UP_X_UNAUTH_FORCE_UP_FIELD_SIZE   (1)
#define L2_CFG_UP_STG_BLOCK_FORCE_UP_FIELD_OFFSET (3)
#define L2_CFG_UP_STG_BLOCK_FORCE_UP_FIELD_SIZE   (1)
#define L2_CFG_UP_PKT_LOCAL_EN_FIELD_OFFSET (2)
#define L2_CFG_UP_PKT_LOCAL_EN_FIELD_SIZE   (1)

//-------------------------------------------------------------------------
// MODIFY_CORE_CFG INFO:
//-------------------------------------------------------------------------
#define NPU_MODIFY_CORE_CFG_REG_ADDR (NPU_BASE_ADDR+0x28000)
#define MODIFY_CORE_CFG_MCORE2MPH_HASH_CFG_RSVD_FIELD_OFFSET (20)
#define MODIFY_CORE_CFG_MCORE2MPH_HASH_CFG_RSVD_FIELD_SIZE   (12)
#define MODIFY_CORE_CFG_MCORE2MPH_HASH_CFG_FIELD_OFFSET (16)
#define MODIFY_CORE_CFG_MCORE2MPH_HASH_CFG_FIELD_SIZE   (4)
#define MODIFY_CORE_CFG_MCORE_CFG_RSVD_FIELD_OFFSET (14)
#define MODIFY_CORE_CFG_MCORE_CFG_RSVD_FIELD_SIZE   (2)
#define MODIFY_CORE_CFG_MCORE_CFG_FIELD_OFFSET (0)
#define MODIFY_CORE_CFG_MCORE_CFG_FIELD_SIZE   (14)

//-------------------------------------------------------------------------
// MODFIY_MIPP_CFG0123 INFO:
//-------------------------------------------------------------------------
#define NPU_MODFIY_MIPP_CFG0123_REG_ADDR (NPU_BASE_ADDR+0x28004)
#define MODFIY_MIPP_CFG3_RSVD_FIELD_OFFSET (31)
#define MODFIY_MIPP_CFG3_RSVD_FIELD_SIZE   (1)
#define MODFIY_MIPP_CFG3_MIPP_CFG_3_FIELD_OFFSET (24)
#define MODFIY_MIPP_CFG3_MIPP_CFG_3_FIELD_SIZE   (7)
#define MODFIY_MIPP_CFG2_RSVD_FIELD_OFFSET (23)
#define MODFIY_MIPP_CFG2_RSVD_FIELD_SIZE   (1)
#define MODFIY_MIPP_CFG2_MIPP_CFG_2_FIELD_OFFSET (16)
#define MODFIY_MIPP_CFG2_MIPP_CFG_2_FIELD_SIZE   (7)
#define MODFIY_MIPP_CFG1_RSVD_FIELD_OFFSET (15)
#define MODFIY_MIPP_CFG1_RSVD_FIELD_SIZE   (1)
#define MODFIY_MIPP_CFG1_MIPP_CFG_1_FIELD_OFFSET (8)
#define MODFIY_MIPP_CFG1_MIPP_CFG_1_FIELD_SIZE   (7)
#define MODFIY_MIPP_CFG0_RSVD_FIELD_OFFSET (7)
#define MODFIY_MIPP_CFG0_RSVD_FIELD_SIZE   (1)
#define MODFIY_MIPP_CFG0_MIPP_CFG_0_FIELD_OFFSET (0)
#define MODFIY_MIPP_CFG0_MIPP_CFG_0_FIELD_SIZE   (7)

//-------------------------------------------------------------------------
// MODFIY_MIPP_CFG4567 INFO:
//-------------------------------------------------------------------------
#define NPU_MODFIY_MIPP_CFG4567_REG_ADDR (NPU_BASE_ADDR+0x28008)
#define MODFIY_MIPP_CFG7_RSVD_FIELD_OFFSET (31)
#define MODFIY_MIPP_CFG7_RSVD_FIELD_SIZE   (1)
#define MODFIY_MIPP_CFG7_MIPP_CFG_7_FIELD_OFFSET (24)
#define MODFIY_MIPP_CFG7_MIPP_CFG_7_FIELD_SIZE   (7)
#define MODFIY_MIPP_CFG6_RSVD_FIELD_OFFSET (23)
#define MODFIY_MIPP_CFG6_RSVD_FIELD_SIZE   (1)
#define MODFIY_MIPP_CFG6_MIPP_CFG_6_FIELD_OFFSET (16)
#define MODFIY_MIPP_CFG6_MIPP_CFG_6_FIELD_SIZE   (7)
#define MODFIY_MIPP_CFG5_RSVD_FIELD_OFFSET (15)
#define MODFIY_MIPP_CFG5_RSVD_FIELD_SIZE   (1)
#define MODFIY_MIPP_CFG5_MIPP_CFG_5_FIELD_OFFSET (8)
#define MODFIY_MIPP_CFG5_MIPP_CFG_5_FIELD_SIZE   (7)
#define MODFIY_MIPP_CFG4_RSVD_FIELD_OFFSET (7)
#define MODFIY_MIPP_CFG4_RSVD_FIELD_SIZE   (1)
#define MODFIY_MIPP_CFG4_MIPP_CFG_4_FIELD_OFFSET (0)
#define MODFIY_MIPP_CFG4_MIPP_CFG_4_FIELD_SIZE   (7)

//-------------------------------------------------------------------------
// MODFIY_MIPP_CFG8_9_10_11 INFO:
//-------------------------------------------------------------------------
#define NPU_MODFIY_MIPP_CFG8_9_10_11_REG_ADDR (NPU_BASE_ADDR+0x2800C)
#define MODFIY_MIPP_CFG11_RSVD_FIELD_OFFSET (31)
#define MODFIY_MIPP_CFG11_RSVD_FIELD_SIZE   (1)
#define MODFIY_MIPP_CFG11_MIPP_CFG_11_FIELD_OFFSET (24)
#define MODFIY_MIPP_CFG11_MIPP_CFG_11_FIELD_SIZE   (7)
#define MODFIY_MIPP_CFG10_RSVD_FIELD_OFFSET (23)
#define MODFIY_MIPP_CFG10_RSVD_FIELD_SIZE   (1)
#define MODFIY_MIPP_CFG10_MIPP_CFG_10_FIELD_OFFSET (16)
#define MODFIY_MIPP_CFG10_MIPP_CFG_10_FIELD_SIZE   (7)
#define MODFIY_MIPP_CFG9_RSVD_FIELD_OFFSET (15)
#define MODFIY_MIPP_CFG9_RSVD_FIELD_SIZE   (1)
#define MODFIY_MIPP_CFG9_MIPP_CFG_9_FIELD_OFFSET (8)
#define MODFIY_MIPP_CFG9_MIPP_CFG_9_FIELD_SIZE   (7)
#define MODFIY_MIPP_CFG8_RSVD_FIELD_OFFSET (7)
#define MODFIY_MIPP_CFG8_RSVD_FIELD_SIZE   (1)
#define MODFIY_MIPP_CFG8_MIPP_CFG_8_FIELD_OFFSET (0)
#define MODFIY_MIPP_CFG8_MIPP_CFG_8_FIELD_SIZE   (7)

//-------------------------------------------------------------------------
// MODFIY_MIPP_CFG12_13_14_15 INFO:
//-------------------------------------------------------------------------
#define NPU_MODFIY_MIPP_CFG12_13_14_15_REG_ADDR (NPU_BASE_ADDR+0x28010)
#define MODFIY_MIPP_CFG15_RSVD_FIELD_OFFSET (31)
#define MODFIY_MIPP_CFG15_RSVD_FIELD_SIZE   (1)
#define MODFIY_MIPP_CFG15_MIPP_CFG_15_FIELD_OFFSET (24)
#define MODFIY_MIPP_CFG15_MIPP_CFG_15_FIELD_SIZE   (7)
#define MODFIY_MIPP_CFG14_RSVD_FIELD_OFFSET (23)
#define MODFIY_MIPP_CFG14_RSVD_FIELD_SIZE   (1)
#define MODFIY_MIPP_CFG14_MIPP_CFG_14_FIELD_OFFSET (16)
#define MODFIY_MIPP_CFG14_MIPP_CFG_14_FIELD_SIZE   (7)
#define MODFIY_MIPP_CFG13_RSVD_FIELD_OFFSET (15)
#define MODFIY_MIPP_CFG13_RSVD_FIELD_SIZE   (1)
#define MODFIY_MIPP_CFG13_MIPP_CFG_13_FIELD_OFFSET (8)
#define MODFIY_MIPP_CFG13_MIPP_CFG_13_FIELD_SIZE   (7)
#define MODFIY_MIPP_CFG12_RSVD_FIELD_OFFSET (7)
#define MODFIY_MIPP_CFG12_RSVD_FIELD_SIZE   (1)
#define MODFIY_MIPP_CFG12_MIPP_CFG_12_FIELD_OFFSET (0)
#define MODFIY_MIPP_CFG12_MIPP_CFG_12_FIELD_SIZE   (7)

//-------------------------------------------------------------------------
// MODFIY_MIPP_CFG16_17_18_19 INFO:
//-------------------------------------------------------------------------
#define NPU_MODFIY_MIPP_CFG16_17_18_19_REG_ADDR (NPU_BASE_ADDR+0x28014)
#define MODFIY_MIPP_CFG19_RSVD_FIELD_OFFSET (31)
#define MODFIY_MIPP_CFG19_RSVD_FIELD_SIZE   (1)
#define MODFIY_MIPP_CFG19_MIPP_CFG_19_FIELD_OFFSET (24)
#define MODFIY_MIPP_CFG19_MIPP_CFG_19_FIELD_SIZE   (7)
#define MODFIY_MIPP_CFG18_RSVD_FIELD_OFFSET (23)
#define MODFIY_MIPP_CFG18_RSVD_FIELD_SIZE   (1)
#define MODFIY_MIPP_CFG18_MIPP_CFG_18_FIELD_OFFSET (16)
#define MODFIY_MIPP_CFG18_MIPP_CFG_18_FIELD_SIZE   (7)
#define MODFIY_MIPP_CFG17_RSVD_FIELD_OFFSET (15)
#define MODFIY_MIPP_CFG17_RSVD_FIELD_SIZE   (1)
#define MODFIY_MIPP_CFG17_MIPP_CFG_17_FIELD_OFFSET (8)
#define MODFIY_MIPP_CFG17_MIPP_CFG_17_FIELD_SIZE   (7)
#define MODFIY_MIPP_CFG16_RSVD_FIELD_OFFSET (7)
#define MODFIY_MIPP_CFG16_RSVD_FIELD_SIZE   (1)
#define MODFIY_MIPP_CFG16_MIPP_CFG_16_FIELD_OFFSET (0)
#define MODFIY_MIPP_CFG16_MIPP_CFG_16_FIELD_SIZE   (7)

//-------------------------------------------------------------------------
// MODFIY_MIPP_CFG20_21_22 INFO:
//-------------------------------------------------------------------------
#define NPU_MODFIY_MIPP_CFG20_21_22_REG_ADDR (NPU_BASE_ADDR+0x28018)
#define MODFIY_MIPP_CFG20_21_22_RSVD_CFG_22_FIELD_OFFSET (16)
#define MODFIY_MIPP_CFG20_21_22_RSVD_CFG_22_FIELD_SIZE   (16)
#define MODFIY_MIPP_CFG20_21_22_MIPP_CFG_22_FIELD_OFFSET (15)
#define MODFIY_MIPP_CFG20_21_22_MIPP_CFG_22_FIELD_SIZE   (1)
#define MODFIY_MIPP_CFG20_21_22_MIPP_CFG_21_FIELD_OFFSET (8)
#define MODFIY_MIPP_CFG20_21_22_MIPP_CFG_21_FIELD_SIZE   (7)
#define MODFIY_MIPP_CFG20_21_22_RSVD_CFG_20_FIELD_OFFSET (7)
#define MODFIY_MIPP_CFG20_21_22_RSVD_CFG_20_FIELD_SIZE   (1)
#define MODFIY_MIPP_CFG20_21_22_MIPP_CFG_20_FIELD_OFFSET (0)
#define MODFIY_MIPP_CFG20_21_22_MIPP_CFG_20_FIELD_SIZE   (7)

//-------------------------------------------------------------------------
// MODIFY_MSCH_MFREE_CFG INFO:
//-------------------------------------------------------------------------
#define NPU_MODIFY_MSCH_MFREE_CFG_REG_ADDR (NPU_BASE_ADDR+0x2801C)
#define MODIFY_MSCH_MFREE_CFG_MSCH_CFG_FIELD_OFFSET (24)
#define MODIFY_MSCH_MFREE_CFG_MSCH_CFG_FIELD_SIZE   (8)
#define MODIFY_MSCH_MFREE_CFG_MFREE_CFG_FIELD_OFFSET (0)
#define MODIFY_MSCH_MFREE_CFG_MFREE_CFG_FIELD_SIZE   (24)

//-------------------------------------------------------------------------
// MODIFY_STS_LOW INFO:
//-------------------------------------------------------------------------
#define NPU_MODIFY_STS_LOW_REG_ADDR (NPU_BASE_ADDR+0x28020)
#define MODIFY_STS_LOW_MD2CPU_STS_LOW_FIELD_OFFSET (0)
#define MODIFY_STS_LOW_MD2CPU_STS_LOW_FIELD_SIZE   (32)

//-------------------------------------------------------------------------
// MODIFY_STS_MID INFO:
//-------------------------------------------------------------------------
#define NPU_MODIFY_STS_MID_REG_ADDR (NPU_BASE_ADDR+0x28024)
#define MODIFY_STS_MID_MD2CPU_STS_MID_FIELD_OFFSET (0)
#define MODIFY_STS_MID_MD2CPU_STS_MID_FIELD_SIZE   (32)

//-------------------------------------------------------------------------
// MODIFY_STS_HIGH INFO:
//-------------------------------------------------------------------------
#define NPU_MODIFY_STS_HIGH_REG_ADDR (NPU_BASE_ADDR+0x28028)
#define MODIFY_STS_HIGH_RSVD_FIELD_OFFSET (24)
#define MODIFY_STS_HIGH_RSVD_FIELD_SIZE   (8)
#define MODIFY_STS_HIGH_MD2CPU_STS_HIGH_FIELD_OFFSET (0)
#define MODIFY_STS_HIGH_MD2CPU_STS_HIGH_FIELD_SIZE   (24)

//-------------------------------------------------------------------------
// IACL_MPP_CFG0 INFO:
//-------------------------------------------------------------------------
#define NPU_IACL_MPP_CFG0_REG_ADDR (NPU_BASE_ADDR+0x2C000)
#define IACL_MPP_CFG0_RSVD_FIELD_OFFSET (25)
#define IACL_MPP_CFG0_RSVD_FIELD_SIZE   (7)
#define IACL_MPP_CFG0_EACL_WIFI2CPU_EN_FIELD_OFFSET (24)
#define IACL_MPP_CFG0_EACL_WIFI2CPU_EN_FIELD_SIZE   (1)
#define IACL_MPP_CFG0_IACL_IPV6_EN_FIELD_OFFSET (23)
#define IACL_MPP_CFG0_IACL_IPV6_EN_FIELD_SIZE   (1)
#define IACL_MPP_CFG0_IACL_IPV4_EN_FIELD_OFFSET (22)
#define IACL_MPP_CFG0_IACL_IPV4_EN_FIELD_SIZE   (1)
#define IACL_MPP_CFG0_IACL_KEY0_MODE_FIELD_OFFSET (19)
#define IACL_MPP_CFG0_IACL_KEY0_MODE_FIELD_SIZE   (3)
#define IACL_MPP_CFG0_NEW_DIP_DP_EN_FIELD_OFFSET (18)
#define IACL_MPP_CFG0_NEW_DIP_DP_EN_FIELD_SIZE   (1)
#define IACL_MPP_CFG0_NEW_SIP_SP_EN_FIELD_OFFSET (17)
#define IACL_MPP_CFG0_NEW_SIP_SP_EN_FIELD_SIZE   (1)
#define IACL_MPP_CFG0_CFG_MPP_BYPASS_FIELD_OFFSET (16)
#define IACL_MPP_CFG0_CFG_MPP_BYPASS_FIELD_SIZE   (1)
#define IACL_MPP_CFG0_RESP_FIFO_AFULL_THRESH_FIELD_OFFSET (12)
#define IACL_MPP_CFG0_RESP_FIFO_AFULL_THRESH_FIELD_SIZE   (4)
#define IACL_MPP_CFG0_VOQ_1_FIFO_AFULL_THRESH_FIELD_OFFSET (8)
#define IACL_MPP_CFG0_VOQ_1_FIFO_AFULL_THRESH_FIELD_SIZE   (4)
#define IACL_MPP_CFG0_VOQ_0_FIFO_AFULL_THRESH_FIELD_OFFSET (4)
#define IACL_MPP_CFG0_VOQ_0_FIFO_AFULL_THRESH_FIELD_SIZE   (4)
#define IACL_MPP_CFG0_FP_FIFO_AFULL_THRESH_FIELD_OFFSET (0)
#define IACL_MPP_CFG0_FP_FIFO_AFULL_THRESH_FIELD_SIZE   (4)

//-------------------------------------------------------------------------
// IACL_MPP_CFG1 INFO:
//-------------------------------------------------------------------------
#define NPU_IACL_MPP_CFG1_REG_ADDR (NPU_BASE_ADDR+0x2C004)
#define IACL_MPP_CFG1_RSVD_FIELD_OFFSET (26)
#define IACL_MPP_CFG1_RSVD_FIELD_SIZE   (6)
#define IACL_MPP_CFG1_CPU_PORT_ID_FIELD_OFFSET (20)
#define IACL_MPP_CFG1_CPU_PORT_ID_FIELD_SIZE   (6)
#define IACL_MPP_CFG1_IACL_OPORT_BITMAP_FIELD_OFFSET (10)
#define IACL_MPP_CFG1_IACL_OPORT_BITMAP_FIELD_SIZE   (10)
#define IACL_MPP_CFG1_IACL_IPORT_BITMAP_FIELD_OFFSET (0)
#define IACL_MPP_CFG1_IACL_IPORT_BITMAP_FIELD_SIZE   (10)

//-------------------------------------------------------------------------
// EACL_MPP_CFG0 INFO:
//-------------------------------------------------------------------------
#define NPU_EACL_MPP_CFG0_REG_ADDR (NPU_BASE_ADDR+0x30000)
#define EACL_MPP_CFG0_RSVD_FIELD_OFFSET (24)
#define EACL_MPP_CFG0_RSVD_FIELD_SIZE   (8)
#define EACL_MPP_CFG0_EACL_WIFI2CPU_EN_FIELD_OFFSET (22)
#define EACL_MPP_CFG0_EACL_WIFI2CPU_EN_FIELD_SIZE   (1)
#define EACL_MPP_CFG0_EACL_IPV6_EN_FIELD_OFFSET (21)
#define EACL_MPP_CFG0_EACL_IPV6_EN_FIELD_SIZE   (1)
#define EACL_MPP_CFG0_EACL_IPV4_EN_FIELD_OFFSET (20)
#define EACL_MPP_CFG0_EACL_IPV4_EN_FIELD_SIZE   (1)
#define EACL_MPP_CFG0_EACL_KEY0_MODE_FIELD_OFFSET (17)
#define EACL_MPP_CFG0_EACL_KEY0_MODE_FIELD_SIZE   (3)
#define EACL_MPP_CFG0_CFG_MPP_BYPASS_FIELD_OFFSET (16)
#define EACL_MPP_CFG0_CFG_MPP_BYPASS_FIELD_SIZE   (1)
#define EACL_MPP_CFG0_RESP_FIFO_AFULL_THRESH_FIELD_OFFSET (12)
#define EACL_MPP_CFG0_RESP_FIFO_AFULL_THRESH_FIELD_SIZE   (4)
#define EACL_MPP_CFG0_VOQ_1_FIFO_AFULL_THRESH_FIELD_OFFSET (8)
#define EACL_MPP_CFG0_VOQ_1_FIFO_AFULL_THRESH_FIELD_SIZE   (4)
#define EACL_MPP_CFG0_VOQ_0_FIFO_AFULL_THRESH_FIELD_OFFSET (4)
#define EACL_MPP_CFG0_VOQ_0_FIFO_AFULL_THRESH_FIELD_SIZE   (4)
#define EACL_MPP_CFG0_FP_FIFO_AFULL_THRESH_FIELD_OFFSET (0)
#define EACL_MPP_CFG0_FP_FIFO_AFULL_THRESH_FIELD_SIZE   (4)

//-------------------------------------------------------------------------
// EACL_MPP_CFG1 INFO:
//-------------------------------------------------------------------------
#define NPU_EACL_MPP_CFG1_REG_ADDR (NPU_BASE_ADDR+0x30004)
#define EACL_MPP_CFG1_RSVD_FIELD_OFFSET (26)
#define EACL_MPP_CFG1_RSVD_FIELD_SIZE   (6)
#define EACL_MPP_CFG1_CPU_PORT_ID_FIELD_OFFSET (20)
#define EACL_MPP_CFG1_CPU_PORT_ID_FIELD_SIZE   (6)
#define EACL_MPP_CFG1_EACL_OPORT_BITMAP_FIELD_OFFSET (10)
#define EACL_MPP_CFG1_EACL_OPORT_BITMAP_FIELD_SIZE   (10)
#define EACL_MPP_CFG1_EACL_IPORT_BITMAP_FIELD_OFFSET (0)
#define EACL_MPP_CFG1_EACL_IPORT_BITMAP_FIELD_SIZE   (10)

//-------------------------------------------------------------------------
// AMOUNT_RAM_WDATA_0 INFO:
//-------------------------------------------------------------------------
#define NPU_AMOUNT_RAM_WDATA_0_REG_ADDR (NPU_BASE_ADDR+0x34000)
#define AMOUNT_RAM_WDATA_0_RAM_WDATA_0_FIELD_OFFSET (0)
#define AMOUNT_RAM_WDATA_0_RAM_WDATA_0_FIELD_SIZE   (32)

//-------------------------------------------------------------------------
// AMOUNT_RAM_WDATA_1 INFO:
//-------------------------------------------------------------------------
#define NPU_AMOUNT_RAM_WDATA_1_REG_ADDR (NPU_BASE_ADDR+0x34004)
#define AMOUNT_RAM_WDATA_1_RSVD_FIELD_OFFSET (16)
#define AMOUNT_RAM_WDATA_1_RSVD_FIELD_SIZE   (16)
#define AMOUNT_RAM_WDATA_1_RAM_WDATA_1_FIELD_OFFSET (0)
#define AMOUNT_RAM_WDATA_1_RAM_WDATA_1_FIELD_SIZE   (16)

//-------------------------------------------------------------------------
// AMOUNT_RAM_WDATA_2 INFO:
//-------------------------------------------------------------------------
#define NPU_AMOUNT_RAM_WDATA_2_REG_ADDR (NPU_BASE_ADDR+0x34008)
#define AMOUNT_RAM_WDATA_2_RAM_WDATA_2_FIELD_OFFSET (0)
#define AMOUNT_RAM_WDATA_2_RAM_WDATA_2_FIELD_SIZE   (32)

//-------------------------------------------------------------------------
// AMOUNT_RAM_WDATA_3 INFO:
//-------------------------------------------------------------------------
#define NPU_AMOUNT_RAM_WDATA_3_REG_ADDR (NPU_BASE_ADDR+0x3400C)
#define AMOUNT_RAM_WDATA_3_RAM_WDATA_3_FIELD_OFFSET (0)
#define AMOUNT_RAM_WDATA_3_RAM_WDATA_3_FIELD_SIZE   (32)

//-------------------------------------------------------------------------
// AMOUNT_RAM_OP_ADDR INFO:
//-------------------------------------------------------------------------
#define NPU_AMOUNT_RAM_OP_ADDR_REG_ADDR (NPU_BASE_ADDR+0x34010)
#define AMOUNT_RAM_OP_ADDR_RSVD_FIELD_OFFSET (13)
#define AMOUNT_RAM_OP_ADDR_RSVD_FIELD_SIZE   (19)
#define AMOUNT_RAM_OP_ADDR_OPCODE_FIELD_OFFSET (11)
#define AMOUNT_RAM_OP_ADDR_OPCODE_FIELD_SIZE   (2)
#define AMOUNT_RAM_OP_ADDR_RAM_ADDR_FIELD_OFFSET (0)
#define AMOUNT_RAM_OP_ADDR_RAM_ADDR_FIELD_SIZE   (11)

//-------------------------------------------------------------------------
// AMOUNT_RAM_RDATA_0 INFO:
//-------------------------------------------------------------------------
#define NPU_AMOUNT_RAM_RDATA_0_REG_ADDR (NPU_BASE_ADDR+0x34014)
#define AMOUNT_RAM_RDATA_0_RAM_RDATA_0_FIELD_OFFSET (0)
#define AMOUNT_RAM_RDATA_0_RAM_RDATA_0_FIELD_SIZE   (32)

//-------------------------------------------------------------------------
// AMOUNT_RAM_RDATA_1 INFO:
//-------------------------------------------------------------------------
#define NPU_AMOUNT_RAM_RDATA_1_REG_ADDR (NPU_BASE_ADDR+0x34018)
#define AMOUNT_RAM_RDATA_1_RSVD_FIELD_OFFSET (16)
#define AMOUNT_RAM_RDATA_1_RSVD_FIELD_SIZE   (16)
#define AMOUNT_RAM_RDATA_1_RAM_RDATA_1_FIELD_OFFSET (0)
#define AMOUNT_RAM_RDATA_1_RAM_RDATA_1_FIELD_SIZE   (16)

//-------------------------------------------------------------------------
// AMOUNT_RAM_RDATA_2 INFO:
//-------------------------------------------------------------------------
#define NPU_AMOUNT_RAM_RDATA_2_REG_ADDR (NPU_BASE_ADDR+0x3401C)
#define AMOUNT_RAM_RDATA_2_RAM_RDATA_2_FIELD_OFFSET (0)
#define AMOUNT_RAM_RDATA_2_RAM_RDATA_2_FIELD_SIZE   (32)

//-------------------------------------------------------------------------
// AMOUNT_RAM_RDATA_3 INFO:
//-------------------------------------------------------------------------
#define NPU_AMOUNT_RAM_RDATA_3_REG_ADDR (NPU_BASE_ADDR+0x34020)
#define AMOUNT_RAM_RDATA_3_RAM_RDATA_3_FIELD_OFFSET (0)
#define AMOUNT_RAM_RDATA_3_RAM_RDATA_3_FIELD_SIZE   (32)

//-------------------------------------------------------------------------
// AMOUNT_CFG INFO:
//-------------------------------------------------------------------------
#define NPU_AMOUNT_CFG_REG_ADDR (NPU_BASE_ADDR+0x34024)
#define AMOUNT_CFG_RSVD_FIELD_OFFSET (2)
#define AMOUNT_CFG_RSVD_FIELD_SIZE   (30)
#define AMOUNT_CFG_CFG_STS_RDCLR_EN_FIELD_OFFSET (1)
#define AMOUNT_CFG_CFG_STS_RDCLR_EN_FIELD_SIZE   (1)
#define AMOUNT_CFG_CFG_STAY_FIELD_OFFSET (0)
#define AMOUNT_CFG_CFG_STAY_FIELD_SIZE   (1)

//-------------------------------------------------------------------------
// AMOUNT_RDATA_VALID INFO:
//-------------------------------------------------------------------------
#define NPU_AMOUNT_RDATA_VALID_REG_ADDR (NPU_BASE_ADDR+0x34028)
#define AMOUNT_RDATA_VALID_RAM_RDATA_VLD_FIELD_OFFSET (0)
#define AMOUNT_RDATA_VALID_RAM_RDATA_VLD_FIELD_SIZE   (1)

//-------------------------------------------------------------------------
// ARP_INTF_STAT INFO:
//-------------------------------------------------------------------------
#define NPU_ARP_INTF_STAT_REG_ADDR (NPU_BASE_ADDR+0x38000)
#define ARP_INTF_STAT_ARP_INTF_STAT_FIELD_OFFSET (0)
#define ARP_INTF_STAT_ARP_INTF_STAT_FIELD_SIZE   (10)

//-------------------------------------------------------------------------
// EACL_STAT INFO:
//-------------------------------------------------------------------------
#define NPU_EACL_STAT_REG_ADDR (NPU_BASE_ADDR+0x38004)
#define EACL_STAT_EACL_STAT_FIELD_OFFSET (0)
#define EACL_STAT_EACL_STAT_FIELD_SIZE   (10)

//-------------------------------------------------------------------------
// EVLAN_LKP__STAT INFO:
//-------------------------------------------------------------------------
#define NPU_EVLAN_LKP__STAT_REG_ADDR (NPU_BASE_ADDR+0x38008)
#define EVLAN_LKP__STAT_EVLAN_LKP_STAT_FIELD_OFFSET (0)
#define EVLAN_LKP__STAT_EVLAN_LKP_STAT_FIELD_SIZE   (14)

//-------------------------------------------------------------------------
// EVLAN_XLT__STAT INFO:
//-------------------------------------------------------------------------
#define NPU_EVLAN_XLT__STAT_REG_ADDR (NPU_BASE_ADDR+0x3800C)
#define EVLAN_XLT__STAT_EVLAN_XLT_STAT_FIELD_OFFSET (0)
#define EVLAN_XLT__STAT_EVLAN_XLT_STAT_FIELD_SIZE   (10)

//-------------------------------------------------------------------------
// EVLAN_ACT__STAT INFO:
//-------------------------------------------------------------------------
#define NPU_EVLAN_ACT__STAT_REG_ADDR (NPU_BASE_ADDR+0x38010)
#define EVLAN_ACT__STAT_EVLAN_ACT_STAT_FIELD_OFFSET (0)
#define EVLAN_ACT__STAT_EVLAN_ACT_STAT_FIELD_SIZE   (10)

//-------------------------------------------------------------------------
// IACL_STAT INFO:
//-------------------------------------------------------------------------
#define NPU_IACL_STAT_REG_ADDR (NPU_BASE_ADDR+0x38014)
#define IACL_STAT_IACL_STAT_FIELD_OFFSET (0)
#define IACL_STAT_IACL_STAT_FIELD_SIZE   (10)

//-------------------------------------------------------------------------
// IVLAN_PORT_STAT INFO:
//-------------------------------------------------------------------------
#define NPU_IVLAN_PORT_STAT_REG_ADDR (NPU_BASE_ADDR+0x38018)
#define IVLAN_PORT_STAT_IVLAN_PORT_STAT_FIELD_OFFSET (0)
#define IVLAN_PORT_STAT_IVLAN_PORT_STAT_FIELD_SIZE   (12)

//-------------------------------------------------------------------------
// IVLAN_VID_STAT INFO:
//-------------------------------------------------------------------------
#define NPU_IVLAN_VID_STAT_REG_ADDR (NPU_BASE_ADDR+0x3801C)
#define IVLAN_VID_STAT_IVLAN_VID_STAT_FIELD_OFFSET (0)
#define IVLAN_VID_STAT_IVLAN_VID_STAT_FIELD_SIZE   (14)

//-------------------------------------------------------------------------
// IVLAN_LKP_STAT INFO:
//-------------------------------------------------------------------------
#define NPU_IVLAN_LKP_STAT_REG_ADDR (NPU_BASE_ADDR+0x38020)
#define IVLAN_LKP_STAT_IVLAN_LKP_STAT_FIELD_OFFSET (0)
#define IVLAN_LKP_STAT_IVLAN_LKP_STAT_FIELD_SIZE   (10)

//-------------------------------------------------------------------------
// L2_STAT INFO:
//-------------------------------------------------------------------------
#define NPU_L2_STAT_REG_ADDR (NPU_BASE_ADDR+0x38024)
#define L2_STAT_L2_STAT_FIELD_OFFSET (0)
#define L2_STAT_L2_STAT_FIELD_SIZE   (12)

//-------------------------------------------------------------------------
// L3_PP_STAT INFO:
//-------------------------------------------------------------------------
#define NPU_L3_PP_STAT_REG_ADDR (NPU_BASE_ADDR+0x38028)
#define L3_PP_STAT_L3_PP_STAT_FIELD_OFFSET (0)
#define L3_PP_STAT_L3_PP_STAT_FIELD_SIZE   (12)

//-------------------------------------------------------------------------
// NAT_STAT INFO:
//-------------------------------------------------------------------------
#define NPU_NAT_STAT_REG_ADDR (NPU_BASE_ADDR+0x3802C)
#define NAT_STAT_NAT_STAT_FIELD_OFFSET (0)
#define NAT_STAT_NAT_STAT_FIELD_SIZE   (8)

//-------------------------------------------------------------------------
// DDR_CTRL INFO:
//-------------------------------------------------------------------------
#define NPU_DDR_CTRL_REG_ADDR (NPU_BASE_ADDR+0x3C000)
#define DDR_CTRL_RSVD_FIELD_OFFSET (2)
#define DDR_CTRL_RSVD_FIELD_SIZE   (30)
#define DDR_CTRL_DDR_CTRL_CFG_FIELD_OFFSET (0)
#define DDR_CTRL_DDR_CTRL_CFG_FIELD_SIZE   (2)

//-------------------------------------------------------------------------
// PARSE_STS INFO:
//-------------------------------------------------------------------------
#define NPU_PARSE_STS_REG_ADDR (NPU_BASE_ADDR+0x80000)
#define PARSE_STS_FIFO_FULL_FIELD_OFFSET (11)
#define PARSE_STS_FIFO_FULL_FIELD_SIZE   (1)
#define PARSE_STS_FIFO_EMPTY_FIELD_OFFSET (10)
#define PARSE_STS_FIFO_EMPTY_FIELD_SIZE   (1)
//#define PARSE_STS_FIFO_FULL_FIELD_OFFSET (9)
//#define PARSE_STS_FIFO_FULL_FIELD_SIZE   (1)
//#define PARSE_STS_FIFO_EMPTY_FIELD_OFFSET (8)
//#define PARSE_STS_FIFO_EMPTY_FIELD_SIZE   (1)
#define PARSE_STS_FSM_CUR_STATUS_FIELD_OFFSET (0)
#define PARSE_STS_FSM_CUR_STATUS_FIELD_SIZE   (3)

//-------------------------------------------------------------------------
// OUTER_TPID_01 INFO:
//-------------------------------------------------------------------------
#define NPU_OUTER_TPID_01_REG_ADDR (NPU_BASE_ADDR+0x80004)
#define OUTER_TPID_01_OTPID1_FIELD_OFFSET (16)
#define OUTER_TPID_01_OTPID1_FIELD_SIZE   (16)
#define OUTER_TPID_01_OTPID0_FIELD_OFFSET (0)
#define OUTER_TPID_01_OTPID0_FIELD_SIZE   (16)

//-------------------------------------------------------------------------
// OUTER_TPID_23 INFO:
//-------------------------------------------------------------------------
#define NPU_OUTER_TPID_23_REG_ADDR (NPU_BASE_ADDR+0x80008)
#define OUTER_TPID_23_OTPID3_FIELD_OFFSET (16)
#define OUTER_TPID_23_OTPID3_FIELD_SIZE   (16)
#define OUTER_TPID_23_OTPID2_FIELD_OFFSET (0)
#define OUTER_TPID_23_OTPID2_FIELD_SIZE   (16)

//-------------------------------------------------------------------------
// INNER_TPID_01 INFO:
//-------------------------------------------------------------------------
#define NPU_INNER_TPID_01_REG_ADDR (NPU_BASE_ADDR+0x8000C)
#define INNER_TPID_01_ITPID1_FIELD_OFFSET (16)
#define INNER_TPID_01_ITPID1_FIELD_SIZE   (16)
#define INNER_TPID_01_ITPID0_FIELD_OFFSET (0)
#define INNER_TPID_01_ITPID0_FIELD_SIZE   (16)

//-------------------------------------------------------------------------
// INNER_TPID_23 INFO:
//-------------------------------------------------------------------------
#define NPU_INNER_TPID_23_REG_ADDR (NPU_BASE_ADDR+0x80010)
#define INNER_TPID_23_ITPID3_FIELD_OFFSET (16)
#define INNER_TPID_23_ITPID3_FIELD_SIZE   (16)
#define INNER_TPID_23_ITPID2_FIELD_OFFSET (0)
#define INNER_TPID_23_ITPID2_FIELD_SIZE   (16)

//-------------------------------------------------------------------------
// PKT_CHK_CFG INFO:
//-------------------------------------------------------------------------
#define NPU_PKT_CHK_CFG_REG_ADDR (NPU_BASE_ADDR+0x80014)
#define PKT_CHK_CFG_DATA_ENDIAN_FIELD_OFFSET (4)
#define PKT_CHK_CFG_DATA_ENDIAN_FIELD_SIZE   (1)
#define PKT_CHK_CFG_CHECKSUM_EN_FIELD_OFFSET (3)
#define PKT_CHK_CFG_CHECKSUM_EN_FIELD_SIZE   (1)
#define PKT_CHK_CFG_IP_VERSION_CHK_EN_FIELD_OFFSET (2)
#define PKT_CHK_CFG_IP_VERSION_CHK_EN_FIELD_SIZE   (1)
#define PKT_CHK_CFG_TTL_ERR_CHK_EN_FIELD_OFFSET (1)
#define PKT_CHK_CFG_TTL_ERR_CHK_EN_FIELD_SIZE   (1)
#define PKT_CHK_CFG_PKT_LEN_CHK_EN_FIELD_OFFSET (0)
#define PKT_CHK_CFG_PKT_LEN_CHK_EN_FIELD_SIZE   (1)

//-------------------------------------------------------------------------
// ICMP4_MAX_LEN INFO:
//-------------------------------------------------------------------------
#define NPU_ICMP4_MAX_LEN_REG_ADDR (NPU_BASE_ADDR+0x80018)
#define ICMP4_MAX_LEN_ICMP4_MAX_LEN_FIELD_OFFSET (0)
#define ICMP4_MAX_LEN_ICMP4_MAX_LEN_FIELD_SIZE   (16)

//-------------------------------------------------------------------------
// ICMP6_MAX_LEN INFO:
//-------------------------------------------------------------------------
#define NPU_ICMP6_MAX_LEN_REG_ADDR (NPU_BASE_ADDR+0x8001C)
#define ICMP6_MAX_LEN_ICMP6_MAX_LEN_FIELD_OFFSET (0)
#define ICMP6_MAX_LEN_ICMP6_MAX_LEN_FIELD_SIZE   (16)

//-------------------------------------------------------------------------
// DOS_CHK_EN INFO:
//-------------------------------------------------------------------------
#define NPU_DOS_CHK_EN_REG_ADDR (NPU_BASE_ADDR+0x80020)
#define DOS_CHK_EN_IP6_ICMP_SMURF_EN_FIELD_OFFSET (28)
#define DOS_CHK_EN_IP6_ICMP_SMURF_EN_FIELD_SIZE   (1)
#define DOS_CHK_EN_IP6_ICMP_REDIRECT_EN_FIELD_OFFSET (27)
#define DOS_CHK_EN_IP6_ICMP_REDIRECT_EN_FIELD_SIZE   (1)
#define DOS_CHK_EN_IP6_TCP_LENTOOSHORT_FIELD_OFFSET (26)
#define DOS_CHK_EN_IP6_TCP_LENTOOSHORT_FIELD_SIZE   (1)
#define DOS_CHK_EN_IP6_TCP_FLAGS_FIELD_OFFSET (25)
#define DOS_CHK_EN_IP6_TCP_FLAGS_FIELD_SIZE   (1)
#define DOS_CHK_EN_IP6_TCP_XMAS_FIELD_OFFSET (24)
#define DOS_CHK_EN_IP6_TCP_XMAS_FIELD_SIZE   (1)
#define DOS_CHK_EN_IP6_TCP_SYN_ERR_FIELD_OFFSET (23)
#define DOS_CHK_EN_IP6_TCP_SYN_ERR_FIELD_SIZE   (1)
#define DOS_CHK_EN_IP6_FRAG_OFF_EQ_1_FIELD_OFFSET (22)
#define DOS_CHK_EN_IP6_FRAG_OFF_EQ_1_FIELD_SIZE   (1)
#define DOS_CHK_EN_IP6_TCP_SP_EQ_DP_FIELD_OFFSET (21)
#define DOS_CHK_EN_IP6_TCP_SP_EQ_DP_FIELD_SIZE   (1)
#define DOS_CHK_EN_IP6_TCP_FLAGS_ERR_FIELD_OFFSET (20)
#define DOS_CHK_EN_IP6_TCP_FLAGS_ERR_FIELD_SIZE   (1)
#define DOS_CHK_EN_IP6_UDP_SP_EQ_DP_FIELD_OFFSET (19)
#define DOS_CHK_EN_IP6_UDP_SP_EQ_DP_FIELD_SIZE   (1)
#define DOS_CHK_EN_IP6_ICMP_TOO_LONG_FIELD_OFFSET (18)
#define DOS_CHK_EN_IP6_ICMP_TOO_LONG_FIELD_SIZE   (1)
#define DOS_CHK_EN_IP6_ICMP_FRAG_FIELD_OFFSET (17)
#define DOS_CHK_EN_IP6_ICMP_FRAG_FIELD_SIZE   (1)
#define DOS_CHK_EN_IP6_SIP_EQ_DIP_FIELD_OFFSET (16)
#define DOS_CHK_EN_IP6_SIP_EQ_DIP_FIELD_SIZE   (1)
#define DOS_CHK_EN_IP4_ICMP_SMURF_EN_FIELD_OFFSET (12)
#define DOS_CHK_EN_IP4_ICMP_SMURF_EN_FIELD_SIZE   (1)
#define DOS_CHK_EN_IP4_ICMP_REDIRECT_EN_FIELD_OFFSET (11)
#define DOS_CHK_EN_IP4_ICMP_REDIRECT_EN_FIELD_SIZE   (1)
#define DOS_CHK_EN_IP4_TCP_LENTOOSHORT_FIELD_OFFSET (10)
#define DOS_CHK_EN_IP4_TCP_LENTOOSHORT_FIELD_SIZE   (1)
#define DOS_CHK_EN_IP4_TCP_FLAGS_FIELD_OFFSET (9)
#define DOS_CHK_EN_IP4_TCP_FLAGS_FIELD_SIZE   (1)
#define DOS_CHK_EN_IP4_TCP_XMAS_FIELD_OFFSET (8)
#define DOS_CHK_EN_IP4_TCP_XMAS_FIELD_SIZE   (1)
#define DOS_CHK_EN_IP4_TCP_SYN_ERR_FIELD_OFFSET (7)
#define DOS_CHK_EN_IP4_TCP_SYN_ERR_FIELD_SIZE   (1)
#define DOS_CHK_EN_IP4_FRAG_OFF_EQ_1_FIELD_OFFSET (6)
#define DOS_CHK_EN_IP4_FRAG_OFF_EQ_1_FIELD_SIZE   (1)
#define DOS_CHK_EN_IP4_TCP_SP_EQ_DP_FIELD_OFFSET (5)
#define DOS_CHK_EN_IP4_TCP_SP_EQ_DP_FIELD_SIZE   (1)
#define DOS_CHK_EN_IP4_TCP_FLAGS_ERR_FIELD_OFFSET (4)
#define DOS_CHK_EN_IP4_TCP_FLAGS_ERR_FIELD_SIZE   (1)
#define DOS_CHK_EN_IP4_UDP_SP_EQ_DP_FIELD_OFFSET (3)
#define DOS_CHK_EN_IP4_UDP_SP_EQ_DP_FIELD_SIZE   (1)
#define DOS_CHK_EN_IP4_ICMP_TOO_LONG_FIELD_OFFSET (2)
#define DOS_CHK_EN_IP4_ICMP_TOO_LONG_FIELD_SIZE   (1)
#define DOS_CHK_EN_IP4_ICMP_FRAG_FIELD_OFFSET (1)
#define DOS_CHK_EN_IP4_ICMP_FRAG_FIELD_SIZE   (1)
#define DOS_CHK_EN_IP4_SIP_EQ_DIP_FIELD_OFFSET (0)
#define DOS_CHK_EN_IP4_SIP_EQ_DIP_FIELD_SIZE   (1)

//-------------------------------------------------------------------------
// DOS_COMP_CTRL INFO:
//-------------------------------------------------------------------------
#define NPU_DOS_COMP_CTRL_REG_ADDR (NPU_BASE_ADDR+0x80024)
#define DOS_COMP_CTRL_DOS_CHK_EN_FIELD_OFFSET (4)
#define DOS_COMP_CTRL_DOS_CHK_EN_FIELD_SIZE   (1)
#define DOS_COMP_CTRL_TCPFLAGS_VECOR3_EN_FIELD_OFFSET (3)
#define DOS_COMP_CTRL_TCPFLAGS_VECOR3_EN_FIELD_SIZE   (1)
#define DOS_COMP_CTRL_TCPFLAGS_VECOR2_EN_FIELD_OFFSET (2)
#define DOS_COMP_CTRL_TCPFLAGS_VECOR2_EN_FIELD_SIZE   (1)
#define DOS_COMP_CTRL_TCPFLAGS_VECOR1_EN_FIELD_OFFSET (1)
#define DOS_COMP_CTRL_TCPFLAGS_VECOR1_EN_FIELD_SIZE   (1)
#define DOS_COMP_CTRL_TCPFLAGS_VECOR0_EN_FIELD_OFFSET (0)
#define DOS_COMP_CTRL_TCPFLAGS_VECOR0_EN_FIELD_SIZE   (1)

//-------------------------------------------------------------------------
// DOS_TCPFLAG_COMB INFO:
//-------------------------------------------------------------------------
#define NPU_DOS_TCPFLAG_COMB_REG_ADDR (NPU_BASE_ADDR+0x80028)
#define DOS_TCPFLAG_COMB_TCPFLAGS_VECOR3_FIELD_OFFSET (18)
#define DOS_TCPFLAG_COMB_TCPFLAGS_VECOR3_FIELD_SIZE   (6)
#define DOS_TCPFLAG_COMB_TCPFLAGS_VECOR2_FIELD_OFFSET (12)
#define DOS_TCPFLAG_COMB_TCPFLAGS_VECOR2_FIELD_SIZE   (6)
#define DOS_TCPFLAG_COMB_TCPFLAGS_VECOR1_FIELD_OFFSET (6)
#define DOS_TCPFLAG_COMB_TCPFLAGS_VECOR1_FIELD_SIZE   (6)
#define DOS_TCPFLAG_COMB_TCPFLAGS_VECOR0_FIELD_OFFSET (0)
#define DOS_TCPFLAG_COMB_TCPFLAGS_VECOR0_FIELD_SIZE   (6)

//-------------------------------------------------------------------------
// PPPOE_PROC INFO:
//-------------------------------------------------------------------------
#define NPU_PPPOE_PROC_REG_ADDR (NPU_BASE_ADDR+0x8002C)
#define PPPOE_PROC_PPPOE_PROC_CFG1_FIELD_OFFSET (16)
#define PPPOE_PROC_PPPOE_PROC_CFG1_FIELD_SIZE   (16)
#define PPPOE_PROC_PPPOE_PROC_CFG0_FIELD_OFFSET (0)
#define PPPOE_PROC_PPPOE_PROC_CFG0_FIELD_SIZE   (16)

//-------------------------------------------------------------------------
// FWD_PKT_TYPE_01 INFO:
//-------------------------------------------------------------------------
#define NPU_FWD_PKT_TYPE_01_REG_ADDR (NPU_BASE_ADDR+0x80030)
#define FWD_PKT_TYPE_01_FWD_PKT_TYPE_0_FIELD_OFFSET (16)
#define FWD_PKT_TYPE_01_FWD_PKT_TYPE_0_FIELD_SIZE   (16)
#define FWD_PKT_TYPE_01_FWD_PKT_TYPE_1_FIELD_OFFSET (0)
#define FWD_PKT_TYPE_01_FWD_PKT_TYPE_1_FIELD_SIZE   (16)

//-------------------------------------------------------------------------
// FWD_PKT_TYPE_23 INFO:
//-------------------------------------------------------------------------
#define NPU_FWD_PKT_TYPE_23_REG_ADDR (NPU_BASE_ADDR+0x80034)
#define FWD_PKT_TYPE_23_FWD_PKT_TYPE_2_FIELD_OFFSET (16)
#define FWD_PKT_TYPE_23_FWD_PKT_TYPE_2_FIELD_SIZE   (16)
#define FWD_PKT_TYPE_23_FWD_PKT_TYPE_3_FIELD_OFFSET (0)
#define FWD_PKT_TYPE_23_FWD_PKT_TYPE_3_FIELD_SIZE   (16)

//-------------------------------------------------------------------------
// FWD_PKT_TYPE_45 INFO:
//-------------------------------------------------------------------------
#define NPU_FWD_PKT_TYPE_45_REG_ADDR (NPU_BASE_ADDR+0x80038)
#define FWD_PKT_TYPE_45_FWD_PKT_TYPE_4_FIELD_OFFSET (16)
#define FWD_PKT_TYPE_45_FWD_PKT_TYPE_4_FIELD_SIZE   (16)
#define FWD_PKT_TYPE_45_FWD_PKT_TYPE_5_FIELD_OFFSET (0)
#define FWD_PKT_TYPE_45_FWD_PKT_TYPE_5_FIELD_SIZE   (16)

//-------------------------------------------------------------------------
// FWD_PKT_TYPE_67 INFO:
//-------------------------------------------------------------------------
#define NPU_FWD_PKT_TYPE_67_REG_ADDR (NPU_BASE_ADDR+0x8003C)
#define FWD_PKT_TYPE_67_FWD_PKT_TYPE_6_FIELD_OFFSET (16)
#define FWD_PKT_TYPE_67_FWD_PKT_TYPE_6_FIELD_SIZE   (16)
#define FWD_PKT_TYPE_67_FWD_PKT_TYPE_7_FIELD_OFFSET (0)
#define FWD_PKT_TYPE_67_FWD_PKT_TYPE_7_FIELD_SIZE   (16)

//-------------------------------------------------------------------------
// UP_PKT_TYPE_01 INFO:
//-------------------------------------------------------------------------
#define NPU_UP_PKT_TYPE_01_REG_ADDR (NPU_BASE_ADDR+0x80040)
#define UP_PKT_TYPE_01_UP_PKT_TYPE_0_FIELD_OFFSET (16)
#define UP_PKT_TYPE_01_UP_PKT_TYPE_0_FIELD_SIZE   (16)
#define UP_PKT_TYPE_01_UP_PKT_TYPE_1_FIELD_OFFSET (0)
#define UP_PKT_TYPE_01_UP_PKT_TYPE_1_FIELD_SIZE   (16)

//-------------------------------------------------------------------------
// UP_PKT_TYPE_23 INFO:
//-------------------------------------------------------------------------
#define NPU_UP_PKT_TYPE_23_REG_ADDR (NPU_BASE_ADDR+0x80044)
#define UP_PKT_TYPE_23_UP_PKT_TYPE_2_FIELD_OFFSET (16)
#define UP_PKT_TYPE_23_UP_PKT_TYPE_2_FIELD_SIZE   (16)
#define UP_PKT_TYPE_23_UP_PKT_TYPE_3_FIELD_OFFSET (0)
#define UP_PKT_TYPE_23_UP_PKT_TYPE_3_FIELD_SIZE   (16)

//-------------------------------------------------------------------------
// UP_PKT_TYPE_45 INFO:
//-------------------------------------------------------------------------
#define NPU_UP_PKT_TYPE_45_REG_ADDR (NPU_BASE_ADDR+0x80048)
#define UP_PKT_TYPE_45_UP_PKT_TYPE_4_FIELD_OFFSET (16)
#define UP_PKT_TYPE_45_UP_PKT_TYPE_4_FIELD_SIZE   (16)
#define UP_PKT_TYPE_45_UP_PKT_TYPE_5_FIELD_OFFSET (0)
#define UP_PKT_TYPE_45_UP_PKT_TYPE_5_FIELD_SIZE   (16)

//-------------------------------------------------------------------------
// UP_PKT_TYPE_67 INFO:
//-------------------------------------------------------------------------
#define NPU_UP_PKT_TYPE_67_REG_ADDR (NPU_BASE_ADDR+0x8004C)
#define UP_PKT_TYPE_67_UP_PKT_TYPE_6_FIELD_OFFSET (16)
#define UP_PKT_TYPE_67_UP_PKT_TYPE_6_FIELD_SIZE   (16)
#define UP_PKT_TYPE_67_UP_PKT_TYPE_7_FIELD_OFFSET (0)
#define UP_PKT_TYPE_67_UP_PKT_TYPE_7_FIELD_SIZE   (16)

//-------------------------------------------------------------------------
// DROP_PKT_TYPE_01 INFO:
//-------------------------------------------------------------------------
#define NPU_DROP_PKT_TYPE_01_REG_ADDR (NPU_BASE_ADDR+0x80050)
#define DROP_PKT_TYPE_01_DROP_PKT_TYPE_0_FIELD_OFFSET (16)
#define DROP_PKT_TYPE_01_DROP_PKT_TYPE_0_FIELD_SIZE   (16)
#define DROP_PKT_TYPE_01_DROP_PKT_TYPE_1_FIELD_OFFSET (0)
#define DROP_PKT_TYPE_01_DROP_PKT_TYPE_1_FIELD_SIZE   (16)

//-------------------------------------------------------------------------
// DROP_PKT_TYPE_23 INFO:
//-------------------------------------------------------------------------
#define NPU_DROP_PKT_TYPE_23_REG_ADDR (NPU_BASE_ADDR+0x80054)
#define DROP_PKT_TYPE_23_DROP_PKT_TYPE_2_FIELD_OFFSET (16)
#define DROP_PKT_TYPE_23_DROP_PKT_TYPE_2_FIELD_SIZE   (16)
#define DROP_PKT_TYPE_23_DROP_PKT_TYPE_3_FIELD_OFFSET (0)
#define DROP_PKT_TYPE_23_DROP_PKT_TYPE_3_FIELD_SIZE   (16)

//-------------------------------------------------------------------------
// DROP_PKT_TYPE_45 INFO:
//-------------------------------------------------------------------------
#define NPU_DROP_PKT_TYPE_45_REG_ADDR (NPU_BASE_ADDR+0x80058)
#define DROP_PKT_TYPE_45_DROP_PKT_TYPE_4_FIELD_OFFSET (16)
#define DROP_PKT_TYPE_45_DROP_PKT_TYPE_4_FIELD_SIZE   (16)
#define DROP_PKT_TYPE_45_DROP_PKT_TYPE_5_FIELD_OFFSET (0)
#define DROP_PKT_TYPE_45_DROP_PKT_TYPE_5_FIELD_SIZE   (16)

//-------------------------------------------------------------------------
// DROP_PKT_TYPE_67 INFO:
//-------------------------------------------------------------------------
#define NPU_DROP_PKT_TYPE_67_REG_ADDR (NPU_BASE_ADDR+0x8005C)
#define DROP_PKT_TYPE_67_DROP_PKT_TYPE_6_FIELD_OFFSET (16)
#define DROP_PKT_TYPE_67_DROP_PKT_TYPE_6_FIELD_SIZE   (16)
#define DROP_PKT_TYPE_67_DROP_PKT_TYPE_7_FIELD_OFFSET (0)
#define DROP_PKT_TYPE_67_DROP_PKT_TYPE_7_FIELD_SIZE   (16)

//-------------------------------------------------------------------------
// HOST_ID INFO:
//-------------------------------------------------------------------------
#define NPU_HOST_ID_REG_ADDR (NPU_BASE_ADDR+0x80060)
#define HOST_ID_HOST_ID_H_FIELD_OFFSET (8)
#define HOST_ID_HOST_ID_H_FIELD_SIZE   (6)
#define HOST_ID_HOST_ID_L_FIELD_OFFSET (0)
#define HOST_ID_HOST_ID_L_FIELD_SIZE   (6)

//-------------------------------------------------------------------------
// HW_PROC_PORT01_EN INFO:
//-------------------------------------------------------------------------
#define NPU_HW_PROC_PORT01_EN_REG_ADDR (NPU_BASE_ADDR+0x80064)
#define HW_PROC_PORT01_EN_PORT1_UP_ALL_PKT_EN_FIELD_OFFSET (25)
#define HW_PROC_PORT01_EN_PORT1_UP_ALL_PKT_EN_FIELD_SIZE   (1)
#define HW_PROC_PORT01_EN_PORT1_ERR_PKT_PROCE_EN_FIELD_OFFSET (23)
#define HW_PROC_PORT01_EN_PORT1_ERR_PKT_PROCE_EN_FIELD_SIZE   (2)
#define HW_PROC_PORT01_EN_PORT1_UP_UDP_ALL_EN_FIELD_OFFSET (22)
#define HW_PROC_PORT01_EN_PORT1_UP_UDP_ALL_EN_FIELD_SIZE   (1)
#define HW_PROC_PORT01_EN_PORT1_UP_TCP_ALL_EN_FIELD_OFFSET (21)
#define HW_PROC_PORT01_EN_PORT1_UP_TCP_ALL_EN_FIELD_SIZE   (1)
#define HW_PROC_PORT01_EN_PORT1_UP_TCP_PROTOCOL_EN_FIELD_OFFSET (20)
#define HW_PROC_PORT01_EN_PORT1_UP_TCP_PROTOCOL_EN_FIELD_SIZE   (1)
#define HW_PROC_PORT01_EN_PORT1_FRAG_UP_EN_FIELD_OFFSET (19)
#define HW_PROC_PORT01_EN_PORT1_FRAG_UP_EN_FIELD_SIZE   (1)
#define HW_PROC_PORT01_EN_PORT1_DROP_EN_FIELD_OFFSET (18)
#define HW_PROC_PORT01_EN_PORT1_DROP_EN_FIELD_SIZE   (1)
#define HW_PROC_PORT01_EN_PORT1_UP_EN_FIELD_OFFSET (17)
#define HW_PROC_PORT01_EN_PORT1_UP_EN_FIELD_SIZE   (1)
#define HW_PROC_PORT01_EN_PORT1_FWD_EN_FIELD_OFFSET (16)
#define HW_PROC_PORT01_EN_PORT1_FWD_EN_FIELD_SIZE   (1)
#define HW_PROC_PORT01_EN_PORT0_UP_ALL_PKT_EN_FIELD_OFFSET (9)
#define HW_PROC_PORT01_EN_PORT0_UP_ALL_PKT_EN_FIELD_SIZE   (1)
#define HW_PROC_PORT01_EN_PORT0_ERR_PKT_PROCE_EN_FIELD_OFFSET (7)
#define HW_PROC_PORT01_EN_PORT0_ERR_PKT_PROCE_EN_FIELD_SIZE   (2)
#define HW_PROC_PORT01_EN_PORT0_UP_UDP_ALL_EN_FIELD_OFFSET (6)
#define HW_PROC_PORT01_EN_PORT0_UP_UDP_ALL_EN_FIELD_SIZE   (1)
#define HW_PROC_PORT01_EN_PORT0_UP_TCP_ALL_EN_FIELD_OFFSET (5)
#define HW_PROC_PORT01_EN_PORT0_UP_TCP_ALL_EN_FIELD_SIZE   (1)
#define HW_PROC_PORT01_EN_PORT0_UP_TCP_PROTOCOL_EN_FIELD_OFFSET (4)
#define HW_PROC_PORT01_EN_PORT0_UP_TCP_PROTOCOL_EN_FIELD_SIZE   (1)
#define HW_PROC_PORT01_EN_PORT0_FRAG_UP_EN_FIELD_OFFSET (3)
#define HW_PROC_PORT01_EN_PORT0_FRAG_UP_EN_FIELD_SIZE   (1)
#define HW_PROC_PORT01_EN_PORT0_DROP_EN_FIELD_OFFSET (2)
#define HW_PROC_PORT01_EN_PORT0_DROP_EN_FIELD_SIZE   (1)
#define HW_PROC_PORT01_EN_PORT0_UP_EN_FIELD_OFFSET (1)
#define HW_PROC_PORT01_EN_PORT0_UP_EN_FIELD_SIZE   (1)
#define HW_PROC_PORT01_EN_PORT0_FWD_EN_FIELD_OFFSET (0)
#define HW_PROC_PORT01_EN_PORT0_FWD_EN_FIELD_SIZE   (1)

//-------------------------------------------------------------------------
// HW_PROC_PORT23_EN INFO:
//-------------------------------------------------------------------------
#define NPU_HW_PROC_PORT23_EN_REG_ADDR (NPU_BASE_ADDR+0x80068)
#define HW_PROC_PORT23_EN_PORT3_UP_ALL_PKT_EN_FIELD_OFFSET (25)
#define HW_PROC_PORT23_EN_PORT3_UP_ALL_PKT_EN_FIELD_SIZE   (1)
#define HW_PROC_PORT23_EN_PORT3_ERR_PKT_PROCE_EN_FIELD_OFFSET (23)
#define HW_PROC_PORT23_EN_PORT3_ERR_PKT_PROCE_EN_FIELD_SIZE   (2)
#define HW_PROC_PORT23_EN_PORT3_UP_UDP_ALL_EN_FIELD_OFFSET (22)
#define HW_PROC_PORT23_EN_PORT3_UP_UDP_ALL_EN_FIELD_SIZE   (1)
#define HW_PROC_PORT23_EN_PORT3_UP_TCP_ALL_EN_FIELD_OFFSET (21)
#define HW_PROC_PORT23_EN_PORT3_UP_TCP_ALL_EN_FIELD_SIZE   (1)
#define HW_PROC_PORT23_EN_PORT3_UP_TCP_PROTOCOL_EN_FIELD_OFFSET (20)
#define HW_PROC_PORT23_EN_PORT3_UP_TCP_PROTOCOL_EN_FIELD_SIZE   (1)
#define HW_PROC_PORT23_EN_PORT3_FRAG_UP_EN_FIELD_OFFSET (19)
#define HW_PROC_PORT23_EN_PORT3_FRAG_UP_EN_FIELD_SIZE   (1)
#define HW_PROC_PORT23_EN_PORT3_DROP_EN_FIELD_OFFSET (18)
#define HW_PROC_PORT23_EN_PORT3_DROP_EN_FIELD_SIZE   (1)
#define HW_PROC_PORT23_EN_PORT3_UP_EN_FIELD_OFFSET (17)
#define HW_PROC_PORT23_EN_PORT3_UP_EN_FIELD_SIZE   (1)
#define HW_PROC_PORT23_EN_PORT3_FWD_EN_FIELD_OFFSET (16)
#define HW_PROC_PORT23_EN_PORT3_FWD_EN_FIELD_SIZE   (1)
#define HW_PROC_PORT23_EN_PORT2_UP_ALL_PKT_EN_FIELD_OFFSET (9)
#define HW_PROC_PORT23_EN_PORT2_UP_ALL_PKT_EN_FIELD_SIZE   (1)
#define HW_PROC_PORT23_EN_PORT2_ERR_PKT_PROCE_EN_FIELD_OFFSET (7)
#define HW_PROC_PORT23_EN_PORT2_ERR_PKT_PROCE_EN_FIELD_SIZE   (2)
#define HW_PROC_PORT23_EN_PORT2_UP_UDP_ALL_EN_FIELD_OFFSET (6)
#define HW_PROC_PORT23_EN_PORT2_UP_UDP_ALL_EN_FIELD_SIZE   (1)
#define HW_PROC_PORT23_EN_PORT2_UP_TCP_ALL_EN_FIELD_OFFSET (5)
#define HW_PROC_PORT23_EN_PORT2_UP_TCP_ALL_EN_FIELD_SIZE   (1)
#define HW_PROC_PORT23_EN_PORT2_UP_TCP_PROTOCOL_EN_FIELD_OFFSET (4)
#define HW_PROC_PORT23_EN_PORT2_UP_TCP_PROTOCOL_EN_FIELD_SIZE   (1)
#define HW_PROC_PORT23_EN_PORT2_FRAG_UP_EN_FIELD_OFFSET (3)
#define HW_PROC_PORT23_EN_PORT2_FRAG_UP_EN_FIELD_SIZE   (1)
#define HW_PROC_PORT23_EN_PORT2_DROP_EN_FIELD_OFFSET (2)
#define HW_PROC_PORT23_EN_PORT2_DROP_EN_FIELD_SIZE   (1)
#define HW_PROC_PORT23_EN_PORT2_UP_EN_FIELD_OFFSET (1)
#define HW_PROC_PORT23_EN_PORT2_UP_EN_FIELD_SIZE   (1)
#define HW_PROC_PORT23_EN_PORT2_FWD_EN_FIELD_OFFSET (0)
#define HW_PROC_PORT23_EN_PORT2_FWD_EN_FIELD_SIZE   (1)

//-------------------------------------------------------------------------
// HW_PROC_PORT45_EN INFO:
//-------------------------------------------------------------------------
#define NPU_HW_PROC_PORT45_EN_REG_ADDR (NPU_BASE_ADDR+0x8006C)
#define HW_PROC_PORT45_EN_PORT5_UP_ALL_PKT_EN_FIELD_OFFSET (25)
#define HW_PROC_PORT45_EN_PORT5_UP_ALL_PKT_EN_FIELD_SIZE   (1)
#define HW_PROC_PORT45_EN_PORT5_ERR_PKT_PROCE_EN_FIELD_OFFSET (23)
#define HW_PROC_PORT45_EN_PORT5_ERR_PKT_PROCE_EN_FIELD_SIZE   (2)
#define HW_PROC_PORT45_EN_PORT5_UP_UDP_ALL_EN_FIELD_OFFSET (22)
#define HW_PROC_PORT45_EN_PORT5_UP_UDP_ALL_EN_FIELD_SIZE   (1)
#define HW_PROC_PORT45_EN_PORT5_UP_TCP_ALL_EN_FIELD_OFFSET (21)
#define HW_PROC_PORT45_EN_PORT5_UP_TCP_ALL_EN_FIELD_SIZE   (1)
#define HW_PROC_PORT45_EN_PORT5_UP_TCP_PROTOCOL_EN_FIELD_OFFSET (20)
#define HW_PROC_PORT45_EN_PORT5_UP_TCP_PROTOCOL_EN_FIELD_SIZE   (1)
#define HW_PROC_PORT45_EN_PORT5_FRAG_UP_EN_FIELD_OFFSET (19)
#define HW_PROC_PORT45_EN_PORT5_FRAG_UP_EN_FIELD_SIZE   (1)
#define HW_PROC_PORT45_EN_PORT5_DROP_EN_FIELD_OFFSET (18)
#define HW_PROC_PORT45_EN_PORT5_DROP_EN_FIELD_SIZE   (1)
#define HW_PROC_PORT45_EN_PORT5_UP_EN_FIELD_OFFSET (17)
#define HW_PROC_PORT45_EN_PORT5_UP_EN_FIELD_SIZE   (1)
#define HW_PROC_PORT45_EN_PORT5_FWD_EN_FIELD_OFFSET (16)
#define HW_PROC_PORT45_EN_PORT5_FWD_EN_FIELD_SIZE   (1)
#define HW_PROC_PORT45_EN_PORT4_UP_ALL_PKT_EN_FIELD_OFFSET (9)
#define HW_PROC_PORT45_EN_PORT4_UP_ALL_PKT_EN_FIELD_SIZE   (1)
#define HW_PROC_PORT45_EN_PORT4_ERR_PKT_PROCE_EN_FIELD_OFFSET (7)
#define HW_PROC_PORT45_EN_PORT4_ERR_PKT_PROCE_EN_FIELD_SIZE   (2)
#define HW_PROC_PORT45_EN_PORT4_UP_UDP_ALL_EN_FIELD_OFFSET (6)
#define HW_PROC_PORT45_EN_PORT4_UP_UDP_ALL_EN_FIELD_SIZE   (1)
#define HW_PROC_PORT45_EN_PORT4_UP_TCP_ALL_EN_FIELD_OFFSET (5)
#define HW_PROC_PORT45_EN_PORT4_UP_TCP_ALL_EN_FIELD_SIZE   (1)
#define HW_PROC_PORT45_EN_PORT4_UP_TCP_PROTOCOL_EN_FIELD_OFFSET (4)
#define HW_PROC_PORT45_EN_PORT4_UP_TCP_PROTOCOL_EN_FIELD_SIZE   (1)
#define HW_PROC_PORT45_EN_PORT4_FRAG_UP_EN_FIELD_OFFSET (3)
#define HW_PROC_PORT45_EN_PORT4_FRAG_UP_EN_FIELD_SIZE   (1)
#define HW_PROC_PORT45_EN_PORT4_DROP_EN_FIELD_OFFSET (2)
#define HW_PROC_PORT45_EN_PORT4_DROP_EN_FIELD_SIZE   (1)
#define HW_PROC_PORT45_EN_PORT4_UP_EN_FIELD_OFFSET (1)
#define HW_PROC_PORT45_EN_PORT4_UP_EN_FIELD_SIZE   (1)
#define HW_PROC_PORT45_EN_PORT4_FWD_EN_FIELD_OFFSET (0)
#define HW_PROC_PORT45_EN_PORT4_FWD_EN_FIELD_SIZE   (1)

//-------------------------------------------------------------------------
// HW_PROC_PORT67_EN INFO:
//-------------------------------------------------------------------------
#define NPU_HW_PROC_PORT67_EN_REG_ADDR (NPU_BASE_ADDR+0x80070)
#define HW_PROC_PORT67_EN_PORT7_UP_ALL_PKT_EN_FIELD_OFFSET (25)
#define HW_PROC_PORT67_EN_PORT7_UP_ALL_PKT_EN_FIELD_SIZE   (1)
#define HW_PROC_PORT67_EN_PORT7_ERR_PKT_PROCE_EN_FIELD_OFFSET (23)
#define HW_PROC_PORT67_EN_PORT7_ERR_PKT_PROCE_EN_FIELD_SIZE   (2)
#define HW_PROC_PORT67_EN_PORT7_UP_UDP_ALL_EN_FIELD_OFFSET (22)
#define HW_PROC_PORT67_EN_PORT7_UP_UDP_ALL_EN_FIELD_SIZE   (1)
#define HW_PROC_PORT67_EN_PORT7_UP_TCP_ALL_EN_FIELD_OFFSET (21)
#define HW_PROC_PORT67_EN_PORT7_UP_TCP_ALL_EN_FIELD_SIZE   (1)
#define HW_PROC_PORT67_EN_PORT7_UP_TCP_PROTOCOL_EN_FIELD_OFFSET (20)
#define HW_PROC_PORT67_EN_PORT7_UP_TCP_PROTOCOL_EN_FIELD_SIZE   (1)
#define HW_PROC_PORT67_EN_PORT7_FRAG_UP_EN_FIELD_OFFSET (19)
#define HW_PROC_PORT67_EN_PORT7_FRAG_UP_EN_FIELD_SIZE   (1)
#define HW_PROC_PORT67_EN_PORT7_DROP_EN_FIELD_OFFSET (18)
#define HW_PROC_PORT67_EN_PORT7_DROP_EN_FIELD_SIZE   (1)
#define HW_PROC_PORT67_EN_PORT7_UP_EN_FIELD_OFFSET (17)
#define HW_PROC_PORT67_EN_PORT7_UP_EN_FIELD_SIZE   (1)
#define HW_PROC_PORT67_EN_PORT7_FWD_EN_FIELD_OFFSET (16)
#define HW_PROC_PORT67_EN_PORT7_FWD_EN_FIELD_SIZE   (1)
#define HW_PROC_PORT67_EN_PORT6_UP_ALL_PKT_EN_FIELD_OFFSET (9)
#define HW_PROC_PORT67_EN_PORT6_UP_ALL_PKT_EN_FIELD_SIZE   (1)
#define HW_PROC_PORT67_EN_PORT6_ERR_PKT_PROCE_EN_FIELD_OFFSET (7)
#define HW_PROC_PORT67_EN_PORT6_ERR_PKT_PROCE_EN_FIELD_SIZE   (2)
#define HW_PROC_PORT67_EN_PORT6_UP_UDP_ALL_EN_FIELD_OFFSET (6)
#define HW_PROC_PORT67_EN_PORT6_UP_UDP_ALL_EN_FIELD_SIZE   (1)
#define HW_PROC_PORT67_EN_PORT6_UP_TCP_ALL_EN_FIELD_OFFSET (5)
#define HW_PROC_PORT67_EN_PORT6_UP_TCP_ALL_EN_FIELD_SIZE   (1)
#define HW_PROC_PORT67_EN_PORT6_UP_TCP_PROTOCOL_EN_FIELD_OFFSET (4)
#define HW_PROC_PORT67_EN_PORT6_UP_TCP_PROTOCOL_EN_FIELD_SIZE   (1)
#define HW_PROC_PORT67_EN_PORT6_FRAG_UP_EN_FIELD_OFFSET (3)
#define HW_PROC_PORT67_EN_PORT6_FRAG_UP_EN_FIELD_SIZE   (1)
#define HW_PROC_PORT67_EN_PORT6_DROP_EN_FIELD_OFFSET (2)
#define HW_PROC_PORT67_EN_PORT6_DROP_EN_FIELD_SIZE   (1)
#define HW_PROC_PORT67_EN_PORT6_UP_EN_FIELD_OFFSET (1)
#define HW_PROC_PORT67_EN_PORT6_UP_EN_FIELD_SIZE   (1)
#define HW_PROC_PORT67_EN_PORT6_FWD_EN_FIELD_OFFSET (0)
#define HW_PROC_PORT67_EN_PORT6_FWD_EN_FIELD_SIZE   (1)

//-------------------------------------------------------------------------
// HW_PROC_PORT89_EN INFO:
//-------------------------------------------------------------------------
#define NPU_HW_PROC_PORT89_EN_REG_ADDR (NPU_BASE_ADDR+0x80074)
#define HW_PROC_PORT89_EN_PORT9_UP_ALL_PKT_EN_FIELD_OFFSET (25)
#define HW_PROC_PORT89_EN_PORT9_UP_ALL_PKT_EN_FIELD_SIZE   (1)
#define HW_PROC_PORT89_EN_PORT9_ERR_PKT_PROCE_EN_FIELD_OFFSET (23)
#define HW_PROC_PORT89_EN_PORT9_ERR_PKT_PROCE_EN_FIELD_SIZE   (2)
#define HW_PROC_PORT89_EN_PORT9_UP_UDP_ALL_EN_FIELD_OFFSET (22)
#define HW_PROC_PORT89_EN_PORT9_UP_UDP_ALL_EN_FIELD_SIZE   (1)
#define HW_PROC_PORT89_EN_PORT9_UP_TCP_ALL_EN_FIELD_OFFSET (21)
#define HW_PROC_PORT89_EN_PORT9_UP_TCP_ALL_EN_FIELD_SIZE   (1)
#define HW_PROC_PORT89_EN_PORT9_UP_TCP_PROTOCOL_EN_FIELD_OFFSET (20)
#define HW_PROC_PORT89_EN_PORT9_UP_TCP_PROTOCOL_EN_FIELD_SIZE   (1)
#define HW_PROC_PORT89_EN_PORT9_FRAG_UP_EN_FIELD_OFFSET (19)
#define HW_PROC_PORT89_EN_PORT9_FRAG_UP_EN_FIELD_SIZE   (1)
#define HW_PROC_PORT89_EN_PORT9_DROP_EN_FIELD_OFFSET (18)
#define HW_PROC_PORT89_EN_PORT9_DROP_EN_FIELD_SIZE   (1)
#define HW_PROC_PORT89_EN_PORT9_UP_EN_FIELD_OFFSET (17)
#define HW_PROC_PORT89_EN_PORT9_UP_EN_FIELD_SIZE   (1)
#define HW_PROC_PORT89_EN_PORT9_FWD_EN_FIELD_OFFSET (16)
#define HW_PROC_PORT89_EN_PORT9_FWD_EN_FIELD_SIZE   (1)
#define HW_PROC_PORT89_EN_PORT8_UP_ALL_PKT_EN_FIELD_OFFSET (9)
#define HW_PROC_PORT89_EN_PORT8_UP_ALL_PKT_EN_FIELD_SIZE   (1)
#define HW_PROC_PORT89_EN_PORT8_ERR_PKT_PROCE_EN_FIELD_OFFSET (7)
#define HW_PROC_PORT89_EN_PORT8_ERR_PKT_PROCE_EN_FIELD_SIZE   (2)
#define HW_PROC_PORT89_EN_PORT8_UP_UDP_ALL_EN_FIELD_OFFSET (6)
#define HW_PROC_PORT89_EN_PORT8_UP_UDP_ALL_EN_FIELD_SIZE   (1)
#define HW_PROC_PORT89_EN_PORT8_UP_TCP_ALL_EN_FIELD_OFFSET (5)
#define HW_PROC_PORT89_EN_PORT8_UP_TCP_ALL_EN_FIELD_SIZE   (1)
#define HW_PROC_PORT89_EN_PORT8_UP_TCP_PROTOCOL_EN_FIELD_OFFSET (4)
#define HW_PROC_PORT89_EN_PORT8_UP_TCP_PROTOCOL_EN_FIELD_SIZE   (1)
#define HW_PROC_PORT89_EN_PORT8_FRAG_UP_EN_FIELD_OFFSET (3)
#define HW_PROC_PORT89_EN_PORT8_FRAG_UP_EN_FIELD_SIZE   (1)
#define HW_PROC_PORT89_EN_PORT8_DROP_EN_FIELD_OFFSET (2)
#define HW_PROC_PORT89_EN_PORT8_DROP_EN_FIELD_SIZE   (1)
#define HW_PROC_PORT89_EN_PORT8_UP_EN_FIELD_OFFSET (1)
#define HW_PROC_PORT89_EN_PORT8_UP_EN_FIELD_SIZE   (1)
#define HW_PROC_PORT89_EN_PORT8_FWD_EN_FIELD_OFFSET (0)
#define HW_PROC_PORT89_EN_PORT8_FWD_EN_FIELD_SIZE   (1)

//-------------------------------------------------------------------------
// ICMP_PRI_CFG INFO:
//-------------------------------------------------------------------------
#define NPU_ICMP_PRI_CFG_REG_ADDR (NPU_BASE_ADDR+0x80078)
#define ICMP_PRI_CFG_ICMP_PRI_CFG_FIELD_OFFSET (0)
#define ICMP_PRI_CFG_ICMP_PRI_CFG_FIELD_SIZE   (3)

//-------------------------------------------------------------------------
// PKT_OFFSET_CFG0 INFO:
//-------------------------------------------------------------------------
#define NPU_PKT_OFFSET_CFG0_REG_ADDR (NPU_BASE_ADDR+0x8007C)
#define PKT_OFFSET_CFG0_HOST_EXTRACT_DBYTE_EN_FIELD_OFFSET (31)
#define PKT_OFFSET_CFG0_HOST_EXTRACT_DBYTE_EN_FIELD_SIZE   (1)
#define PKT_OFFSET_CFG0_PKT_OFFSET_CFG2_FIELD_OFFSET (20)
#define PKT_OFFSET_CFG0_PKT_OFFSET_CFG2_FIELD_SIZE   (10)
#define PKT_OFFSET_CFG0_PKT_OFFSET_CFG1_FIELD_OFFSET (10)
#define PKT_OFFSET_CFG0_PKT_OFFSET_CFG1_FIELD_SIZE   (10)
#define PKT_OFFSET_CFG0_PKT_OFFSET_CFG0_FIELD_OFFSET (0)
#define PKT_OFFSET_CFG0_PKT_OFFSET_CFG0_FIELD_SIZE   (10)

//-------------------------------------------------------------------------
// PKT_OFFSET_CFG1 INFO:
//-------------------------------------------------------------------------
#define NPU_PKT_OFFSET_CFG1_REG_ADDR (NPU_BASE_ADDR+0x80080)
#define PKT_OFFSET_CFG1_PKT_OFFSET_CFG5_FIELD_OFFSET (20)
#define PKT_OFFSET_CFG1_PKT_OFFSET_CFG5_FIELD_SIZE   (10)
#define PKT_OFFSET_CFG1_PKT_OFFSET_CFG4_FIELD_OFFSET (10)
#define PKT_OFFSET_CFG1_PKT_OFFSET_CFG4_FIELD_SIZE   (10)
#define PKT_OFFSET_CFG1_PKT_OFFSET_CFG3_FIELD_OFFSET (0)
#define PKT_OFFSET_CFG1_PKT_OFFSET_CFG3_FIELD_SIZE   (10)

//-------------------------------------------------------------------------
// PKT_OFFSET_CFG2 INFO:
//-------------------------------------------------------------------------
#define NPU_PKT_OFFSET_CFG2_REG_ADDR (NPU_BASE_ADDR+0x80084)
#define PKT_OFFSET_CFG2_PKT_OFFSET_CFG7_FIELD_OFFSET (10)
#define PKT_OFFSET_CFG2_PKT_OFFSET_CFG7_FIELD_SIZE   (10)
#define PKT_OFFSET_CFG2_PKT_OFFSET_CFG6_FIELD_OFFSET (0)
#define PKT_OFFSET_CFG2_PKT_OFFSET_CFG6_FIELD_SIZE   (10)

//-------------------------------------------------------------------------
// RECLAIM_LOCAL_FIFO_SET INFO:
//-------------------------------------------------------------------------
#define NPU_RECLAIM_LOCAL_FIFO_SET_REG_ADDR (NPU_BASE_ADDR+0x200004)
#define RECLAIM_LOCAL_FIFO_SET_RECLAIM_MEM_PROG_FULL_ASSERT_FIELD_OFFSET (0)
#define RECLAIM_LOCAL_FIFO_SET_RECLAIM_MEM_PROG_FULL_ASSERT_FIELD_SIZE   (4)
#define RECLAIM_LOCAL_FIFO_SET_RECLAIM_MEM_PROG_FULL_NEGATE_FIELD_OFFSET (8)
#define RECLAIM_LOCAL_FIFO_SET_RECLAIM_MEM_PROG_FULL_NEGATE_FIELD_SIZE   (4)

//-------------------------------------------------------------------------
// LIF_PORT_PKT_RCV_EN INFO:
//-------------------------------------------------------------------------
#define NPU_LIF_PORT_PKT_RCV_EN_REG_ADDR (NPU_BASE_ADDR+0x200008)
#define LIF_PORT_PKT_RCV_EN_LIF_PORT_PKT_RCV_EN_FIELD_OFFSET (0)
#define LIF_PORT_PKT_RCV_EN_LIF_PORT_PKT_RCV_EN_FIELD_SIZE   (10)

//-------------------------------------------------------------------------
// LIF_HIF_CFG INFO:
//-------------------------------------------------------------------------
#define NPU_LIF_HIF_CFG_REG_ADDR (NPU_BASE_ADDR+0x20000C)
#define LIF_HIF_CFG_LIF_HIF_SEL_FIELD_OFFSET (0)
#define LIF_HIF_CFG_LIF_HIF_SEL_FIELD_SIZE   (10)
#define LIF_HIF_CFG_LACK_PTR_DROP_EN_FIELD_OFFSET (16)
#define LIF_HIF_CFG_LACK_PTR_DROP_EN_FIELD_SIZE   (10)

//-------------------------------------------------------------------------
// BUF_DEPTH_WIDTH INFO:
//-------------------------------------------------------------------------
#define NPU_BUF_DEPTH_WIDTH_REG_ADDR (NPU_BASE_ADDR+0x200010)
#define BUF_DEPTH_WIDTH_BUF_DEPTH_WIDTH_FIELD_OFFSET (0)
#define BUF_DEPTH_WIDTH_BUF_DEPTH_WIDTH_FIELD_SIZE   (3)

//-------------------------------------------------------------------------
// ERROR_STATUS INFO:
//-------------------------------------------------------------------------
#define NPU_ERROR_STATUS_REG_ADDR (NPU_BASE_ADDR+0x200014)
#define ERROR_STATUS_MIS_EOF_ERR_FIELD_OFFSET (0)
#define ERROR_STATUS_MIS_EOF_ERR_FIELD_SIZE   (10)
#define ERROR_STATUS_MIS_SOF_ERR_FIELD_OFFSET (10)
#define ERROR_STATUS_MIS_SOF_ERR_FIELD_SIZE   (10)
#define ERROR_STATUS_FIFO_FULL_ERR_FIELD_OFFSET (20)
#define ERROR_STATUS_FIFO_FULL_ERR_FIELD_SIZE   (10)

//-------------------------------------------------------------------------
// PKT_LIMIT0_SET INFO:
//-------------------------------------------------------------------------
#define NPU_PKT_LIMIT0_SET_REG_ADDR (NPU_BASE_ADDR+0x200018)
#define PKT_LIMIT0_SET_PKT_LIMIT_LOW_0_FIELD_OFFSET (0)
#define PKT_LIMIT0_SET_PKT_LIMIT_LOW_0_FIELD_SIZE   (14)
#define PKT_LIMIT0_SET_PKT_LIMIT_HIGH_0_FIELD_OFFSET (16)
#define PKT_LIMIT0_SET_PKT_LIMIT_HIGH_0_FIELD_SIZE   (14)

//-------------------------------------------------------------------------
// PKT_LIMIT1_SET INFO:
//-------------------------------------------------------------------------
#define NPU_PKT_LIMIT1_SET_REG_ADDR (NPU_BASE_ADDR+0x20001C)
#define PKT_LIMIT1_SET_PKT_LIMIT_LOW_1_FIELD_OFFSET (0)
#define PKT_LIMIT1_SET_PKT_LIMIT_LOW_1_FIELD_SIZE   (14)
#define PKT_LIMIT1_SET_PKT_LIMIT_HIGH_1_FIELD_OFFSET (16)
#define PKT_LIMIT1_SET_PKT_LIMIT_HIGH_1_FIELD_SIZE   (14)

//-------------------------------------------------------------------------
// PKT_LIMIT2_SET INFO:
//-------------------------------------------------------------------------
#define NPU_PKT_LIMIT2_SET_REG_ADDR (NPU_BASE_ADDR+0x200020)
#define PKT_LIMIT2_SET_PKT_LIMIT_LOW_2_FIELD_OFFSET (0)
#define PKT_LIMIT2_SET_PKT_LIMIT_LOW_2_FIELD_SIZE   (14)
#define PKT_LIMIT2_SET_PKT_LIMIT_HIGH_2_FIELD_OFFSET (16)
#define PKT_LIMIT2_SET_PKT_LIMIT_HIGH_2_FIELD_SIZE   (14)

//-------------------------------------------------------------------------
// PKT_LIMIT3_SET INFO:
//-------------------------------------------------------------------------
#define NPU_PKT_LIMIT3_SET_REG_ADDR (NPU_BASE_ADDR+0x200024)
#define PKT_LIMIT3_SET_PKT_LIMIT_LOW_3_FIELD_OFFSET (0)
#define PKT_LIMIT3_SET_PKT_LIMIT_LOW_3_FIELD_SIZE   (14)
#define PKT_LIMIT3_SET_PKT_LIMIT_HIGH_3_FIELD_OFFSET (16)
#define PKT_LIMIT3_SET_PKT_LIMIT_HIGH_3_FIELD_SIZE   (14)

//-------------------------------------------------------------------------
// PKT_LIMIT4_SET INFO:
//-------------------------------------------------------------------------
#define NPU_PKT_LIMIT4_SET_REG_ADDR (NPU_BASE_ADDR+0x200028)
#define PKT_LIMIT4_SET_PKT_LIMIT_LOW_4_FIELD_OFFSET (0)
#define PKT_LIMIT4_SET_PKT_LIMIT_LOW_4_FIELD_SIZE   (14)
#define PKT_LIMIT4_SET_PKT_LIMIT_HIGH_4_FIELD_OFFSET (16)
#define PKT_LIMIT4_SET_PKT_LIMIT_HIGH_4_FIELD_SIZE   (14)

//-------------------------------------------------------------------------
// PKT_LIMIT5_SET INFO:
//-------------------------------------------------------------------------
#define NPU_PKT_LIMIT5_SET_REG_ADDR (NPU_BASE_ADDR+0x20002C)
#define PKT_LIMIT5_SET_PKT_LIMIT_LOW_5_FIELD_OFFSET (0)
#define PKT_LIMIT5_SET_PKT_LIMIT_LOW_5_FIELD_SIZE   (14)
#define PKT_LIMIT5_SET_PKT_LIMIT_HIGH_5_FIELD_OFFSET (16)
#define PKT_LIMIT5_SET_PKT_LIMIT_HIGH_5_FIELD_SIZE   (14)

//-------------------------------------------------------------------------
// PKT_LIMIT6_SET INFO:
//-------------------------------------------------------------------------
#define NPU_PKT_LIMIT6_SET_REG_ADDR (NPU_BASE_ADDR+0x200030)
#define PKT_LIMIT6_SET_PKT_LIMIT_LOW_6_FIELD_OFFSET (0)
#define PKT_LIMIT6_SET_PKT_LIMIT_LOW_6_FIELD_SIZE   (14)
#define PKT_LIMIT6_SET_PKT_LIMIT_HIGH_6_FIELD_OFFSET (16)
#define PKT_LIMIT6_SET_PKT_LIMIT_HIGH_6_FIELD_SIZE   (14)

//-------------------------------------------------------------------------
// PKT_LIMIT7_SET INFO:
//-------------------------------------------------------------------------
#define NPU_PKT_LIMIT7_SET_REG_ADDR (NPU_BASE_ADDR+0x200034)
#define PKT_LIMIT7_SET_PKT_LIMIT_LOW_7_FIELD_OFFSET (0)
#define PKT_LIMIT7_SET_PKT_LIMIT_LOW_7_FIELD_SIZE   (14)
#define PKT_LIMIT7_SET_PKT_LIMIT_HIGH_7_FIELD_OFFSET (16)
#define PKT_LIMIT7_SET_PKT_LIMIT_HIGH_7_FIELD_SIZE   (14)

//-------------------------------------------------------------------------
// PKT_LIMIT8_SET INFO:
//-------------------------------------------------------------------------
#define NPU_PKT_LIMIT8_SET_REG_ADDR (NPU_BASE_ADDR+0x200038)
#define PKT_LIMIT8_SET_PKT_LIMIT_LOW_8_FIELD_OFFSET (0)
#define PKT_LIMIT8_SET_PKT_LIMIT_LOW_8_FIELD_SIZE   (14)
#define PKT_LIMIT8_SET_PKT_LIMIT_HIGH_8_FIELD_OFFSET (16)
#define PKT_LIMIT8_SET_PKT_LIMIT_HIGH_8_FIELD_SIZE   (14)

//-------------------------------------------------------------------------
// PKT_LIMIT9_SET INFO:
//-------------------------------------------------------------------------
#define NPU_PKT_LIMIT9_SET_REG_ADDR (NPU_BASE_ADDR+0x20003C)
#define PKT_LIMIT9_SET_PKT_LIMIT_LOW_9_FIELD_OFFSET (0)
#define PKT_LIMIT9_SET_PKT_LIMIT_LOW_9_FIELD_SIZE   (14)
#define PKT_LIMIT9_SET_PKT_LIMIT_HIGH_9_FIELD_OFFSET (16)
#define PKT_LIMIT9_SET_PKT_LIMIT_HIGH_9_FIELD_SIZE   (14)

//-------------------------------------------------------------------------
// PORT_DEBUG_SEL INFO:
//-------------------------------------------------------------------------
#define NPU_PORT_DEBUG_SEL_REG_ADDR (NPU_BASE_ADDR+0x200040)
#define PORT_DEBUG_SEL_PORT_DEBUG_SEL_FIELD_OFFSET (0)
#define PORT_DEBUG_SEL_PORT_DEBUG_SEL_FIELD_SIZE   (4)

//-------------------------------------------------------------------------
// LLM_RAM_FIFO_SET0 INFO:
//-------------------------------------------------------------------------
#define NPU_LLM_RAM_FIFO_SET0_REG_ADDR (NPU_BASE_ADDR+0x280000)
#define LLM_RAM_FIFO_SET0_LLM_RAM_PROG_FULL_ASSERT_FIELD_OFFSET (0)
#define LLM_RAM_FIFO_SET0_LLM_RAM_PROG_FULL_ASSERT_FIELD_SIZE   (13)
#define LLM_RAM_FIFO_SET0_LLM_RAM_PROG_FULL_NEGATE_FIELD_OFFSET (16)
#define LLM_RAM_FIFO_SET0_LLM_RAM_PROG_FULL_NEGATE_FIELD_SIZE   (13)

//-------------------------------------------------------------------------
// LLM_RAM_FIFO_SET1 INFO:
//-------------------------------------------------------------------------
#define NPU_LLM_RAM_FIFO_SET1_REG_ADDR (NPU_BASE_ADDR+0x280004)
#define LLM_RAM_FIFO_SET1_LLM_RAM_PROG_EMPTY_ASSERT_FIELD_OFFSET (0)
#define LLM_RAM_FIFO_SET1_LLM_RAM_PROG_EMPTY_ASSERT_FIELD_SIZE   (13)
#define LLM_RAM_FIFO_SET1_LLM_RAM_PROG_EMPTY_NEGATE_FIELD_OFFSET (16)
#define LLM_RAM_FIFO_SET1_LLM_RAM_PROG_EMPTY_NEGATE_FIELD_SIZE   (13)

//-------------------------------------------------------------------------
// RCLM_MEM_FIFO_SET INFO:
//-------------------------------------------------------------------------
#define NPU_RCLM_MEM_FIFO_SET_REG_ADDR (NPU_BASE_ADDR+0x280008)
#define RCLM_MEM_FIFO_SET_RECLAIM_MEM_PROG_FULL_ASSERT_FIELD_OFFSET (0)
#define RCLM_MEM_FIFO_SET_RECLAIM_MEM_PROG_FULL_ASSERT_FIELD_SIZE   (4)
#define RCLM_MEM_FIFO_SET_RECLAIM_MEM_PROG_FULL_NEGATE_FIELD_OFFSET (8)
#define RCLM_MEM_FIFO_SET_RECLAIM_MEM_PROG_FULL_NEGATE_FIELD_SIZE   (4)

//-------------------------------------------------------------------------
// LLM_MEM_BUF_USED_STATUS INFO:
//-------------------------------------------------------------------------
#define NPU_LLM_MEM_BUF_USED_STATUS_REG_ADDR (NPU_BASE_ADDR+0x28000C)
#define LLM_MEM_BUF_USED_STATUS_BUFFER_USED_CNT_FIELD_OFFSET (0)
#define LLM_MEM_BUF_USED_STATUS_BUFFER_USED_CNT_FIELD_SIZE   (32)

//-------------------------------------------------------------------------
// BMU_STATUS INFO:
//-------------------------------------------------------------------------
#define NPU_BMU_STATUS_REG_ADDR (NPU_BASE_ADDR+0x280010)
#define BMU_STATUS_LLM_FIFO_INIT_DONE_FIELD_OFFSET (0)
#define BMU_STATUS_LLM_FIFO_INIT_DONE_FIELD_SIZE   (1)
#define BMU_STATUS_FIFO_FULL_ERROR_FIELD_OFFSET (1)
#define BMU_STATUS_FIFO_FULL_ERROR_FIELD_SIZE   (5)

//-------------------------------------------------------------------------
// CPU_RADDR INFO:
//-------------------------------------------------------------------------
#define NPU_CPU_RADDR_REG_ADDR (NPU_BASE_ADDR+0x300000)
#define CPU_RADDR_CPU_RADDR_FIELD_OFFSET (0)
#define CPU_RADDR_CPU_RADDR_FIELD_SIZE   (32)

//-------------------------------------------------------------------------
// CPU_RDATA INFO:
//-------------------------------------------------------------------------
#define NPU_CPU_RDATA_REG_ADDR (NPU_BASE_ADDR+0x300004)
#define CPU_RDATA_CPU_RDATA_FIELD_OFFSET (0)
#define CPU_RDATA_CPU_RDATA_FIELD_SIZE   (32)

//-------------------------------------------------------------------------
// CPU_RD_STS INFO:
//-------------------------------------------------------------------------
#define NPU_CPU_RD_STS_REG_ADDR (NPU_BASE_ADDR+0x300008)
#define CPU_RD_STS_RSVD_FIELD_OFFSET (2)
#define CPU_RD_STS_RSVD_FIELD_SIZE   (30)
#define CPU_RD_STS_CPU_RD_BUSY_FIELD_OFFSET (1)
#define CPU_RD_STS_CPU_RD_BUSY_FIELD_SIZE   (1)
#define CPU_RD_STS_CPU_RD_OVER_FIELD_OFFSET (0)
#define CPU_RD_STS_CPU_RD_OVER_FIELD_SIZE   (1)

//-------------------------------------------------------------------------
// CPU_CFG0 INFO:
//-------------------------------------------------------------------------
#define NPU_CPU_CFG0_REG_ADDR (NPU_BASE_ADDR+0x300010)
#define CPU_CFG0_CPU_CFG0_FIELD_OFFSET (0)
#define CPU_CFG0_CPU_CFG0_FIELD_SIZE   (32)

//-------------------------------------------------------------------------
// CPU_CFG1 INFO:
//-------------------------------------------------------------------------
#define NPU_CPU_CFG1_REG_ADDR (NPU_BASE_ADDR+0x300014)
#define CPU_CFG1_CPU_CFG1_FIELD_OFFSET (0)
#define CPU_CFG1_CPU_CFG1_FIELD_SIZE   (32)

//-------------------------------------------------------------------------
// CPU_CFG2 INFO:
//-------------------------------------------------------------------------
#define NPU_CPU_CFG2_REG_ADDR (NPU_BASE_ADDR+0x300018)
#define CPU_CFG2_CPU_CFG2_FIELD_OFFSET (0)
#define CPU_CFG2_CPU_CFG2_FIELD_SIZE   (32)

//-------------------------------------------------------------------------
// CPU_CFG3 INFO:
//-------------------------------------------------------------------------
#define NPU_CPU_CFG3_REG_ADDR (NPU_BASE_ADDR+0x30001c)
#define CPU_CFG3_CPU_CFG3_FIELD_OFFSET (0)
#define CPU_CFG3_CPU_CFG3_FIELD_SIZE   (32)

//-------------------------------------------------------------------------
// BUF_CTRL_STS INFO:
//-------------------------------------------------------------------------
#define NPU_BUF_CTRL_STS_REG_ADDR (NPU_BASE_ADDR+0x300020)
#define BUF_CTRL_STS_RSVD_FIELD_OFFSET (12)
#define BUF_CTRL_STS_RSVD_FIELD_SIZE   (20)
#define BUF_CTRL_STS_BUF_CTRL_REAL_STS_FIELD_OFFSET (6)
#define BUF_CTRL_STS_BUF_CTRL_REAL_STS_FIELD_SIZE   (6)
#define BUF_CTRL_STS_BUF_CTRL_STS_FIELD_OFFSET (0)
#define BUF_CTRL_STS_BUF_CTRL_STS_FIELD_SIZE   (6)


#endif

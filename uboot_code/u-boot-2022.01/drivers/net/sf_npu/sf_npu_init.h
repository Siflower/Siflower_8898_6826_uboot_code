#ifndef _SF_NPU_INIT_
#define _SF_NPU_INIT_

enum nat_mode {
    ENAT,
    INAT
};

enum NPU_MPP_TYPE {
    NPU_IVLAN = 0,
    NPU_L2    = 1,
    NPU_NAT   = 2,
    NPU_L3    = 3,
    NPU_IACL  = 4,
    NPU_ARP   = 5,
    NPU_EACL  = 6,
    NPU_EVLAN = 7
};

#define NPU_CFG_BASE_ADDR   (NPU_CFG_BASE_ADDR  )
#define NPU0_CFG_BASE_ADDR  (NPU_CFG_BASE_ADDR  + 0x04000000)

#define NPU_SYSM_ADDR       (NPU_SYSM_CFG_ADDR  )

#define LIF_SYSM_BASE 0x0ce01800

#define BASIC_MODE					(0)
#define SYMMETRIC_MODE				(1)
#define FULL_CONE_MODE				(2)
#define RST_CONE_MODE				(3)
#define PORT_RST_CONE_MODE			(4)

#define  SF_SHORT_SWAP(in_usValue) (((0xFF) & ((in_usValue) >> 8)) | ((0xFF00) & ((in_usValue) << 8)))


void npu_mpp_unbypass(enum NPU_MPP_TYPE mpp_type);


#endif // end _SF_NPU_INIT_

/*
* Description
*
* Copyright (C) 2016-2022 Qin.Xia <qin.xia@siflower.com.cn>
*
* Siflower software
*/

#include "npu_head.h"
#include "sf_npu_init.h"
#include "se/se_common.h"
#include "gmac/sf_gmac.h"
#include "gmac/gmac_mdio.h"

/*
 * set gmac pad function and cfg
 */
static void gmac_io_cfg_set(void)
{
	// xgmac io config
    writel(0x11c9, 0x0ce3c090); // xgmii_mdio
    writel(0x10c9, 0x0ce3c094); // xgmii_mdc

    //RGMII tx/rx io config set
    writel(0x11a9,0x0CE3C000+0x54);
    writel(0x11a9,0x0CE3C000+0x58);
    writel(0x11a9,0x0CE3C000+0x5c);
    writel(0x11a9,0x0CE3C000+0x60);
    writel(0x11a9,0x0CE3C000+0x64);
    writel(0x11a9,0x0CE3C000+0x68);
    writel(0x11a9,0x0CE3C000+0x6c);
    writel(0x11a9,0x0CE3C000+0x70);
    writel(0x11a9,0x0CE3C000+0x74);
    writel(0x11c9,0x0CE3C000+0x78);
    writel(0x11c9,0x0CE3C000+0x7c);
    writel(0x11c9,0x0CE3C000+0x80);
    writel(0x11c9,0x0CE3C000+0x84);
    writel(0x11c9,0x0CE3C000+0x88);
    writel(0x11c9,0x0CE3C000+0x8c);
}

void sys_npu_reset(void)
{
	// lif reset release
	writel(0xff, 0x0ce01800 + 0x88);

	// gpio manager soft reset
	writel(0xff, 0x0ce0a000);
	writel(0x00, 0x0ce0a000);

	// gpio clk gating enable (means enable gating )
	writel(0x00, 0x0ce0a004);
	writel(0xff, 0x0ce0a004);

	// gpio soft boe, config channel enbale(bit0:reg  bit1:bus) (default 0x00)
	writel(0x00, 0x0ce0a00c);
	writel(0xff, 0x0ce0a00c);

	gmac_io_cfg_set();
}

void npu_mpp_bypass(enum NPU_MPP_TYPE mpp_type)
{
	if(mpp_type == NPU_NAT)
	{    //nat
		writel(readl(NPU_NAT_MPP_CFG_REG_ADDR)  | (0x1 << NAT_MPP_CFG_CFG_MPP_BYPASS_FIELD_OFFSET),  NPU_NAT_MPP_CFG_REG_ADDR);
	}
	if(mpp_type == NPU_IVLAN)
	{   //ivlan port
		writel(readl(NPU_IVLAN_PORT_MPP_CFG_REG_ADDR) | (0x1 << IVLAN_PORT_MPP_CFG_CFG_MPP_BYPASS_FIELD_OFFSET), NPU_IVLAN_PORT_MPP_CFG_REG_ADDR);
		writel(readl(NPU_IVLAN_VID_MPP_CFG_REG_ADDR)  | (0x1 << IVLAN_VID_MPP_CFG_CFG_MPP_BYPASS_FIELD_OFFSET) , NPU_IVLAN_VID_MPP_CFG_REG_ADDR);
		writel(readl(NPU_IVLAN_LKP_MPP_CFG0_REG_ADDR) | (0x1 << IVLAN_LKP_MPP_CFG0_CFG_MPP_BYPASS_FIELD_OFFSET), NPU_IVLAN_LKP_MPP_CFG0_REG_ADDR);
	}
	if(mpp_type == NPU_ARP)
	{    //arp
		writel(readl(NPU_ARP_MPP_CFG_REG_ADDR)      | (0x1 << ARP_MPP_CFG_CFG_MPP_BYPASS_FIELD_OFFSET),        NPU_ARP_MPP_CFG_REG_ADDR);
	}
	if(mpp_type == NPU_EVLAN)
	{    //evlan lkp
		writel(readl(NPU_EVLAN_LKP_CFG_REG_ADDR)    | (0x1 << EVLAN_LKP_CFG_CFG_MPP_BYPASS_FIELD_OFFSET),      NPU_EVLAN_LKP_CFG_REG_ADDR);
		writel(readl(NPU_EVLAN_XLT_CFG0_REG_ADDR)   | (0x1 << EVLAN_XLT_CFG0_CFG_MPP_BYPASS_FIELD_OFFSET),     NPU_EVLAN_XLT_CFG0_REG_ADDR);
		writel(readl(NPU_EVLAN_ACT_CFG_REG_ADDR)    | (0x1 << EVLAN_ACT_CFG_CFG_MPP_BYPASS_FIELD_OFFSET),      NPU_EVLAN_ACT_CFG_REG_ADDR);
	}
	if(mpp_type == NPU_L3)
	{    //l3
		writel(readl(NPU_L3_MPP_CFG_REG_ADDR)       | (0x1 << L3_MPP_CFG_CFG_MPP_BYPASS_FIELD_OFFSET),         NPU_L3_MPP_CFG_REG_ADDR);
	}
	if(mpp_type == NPU_L2)
	{    //l2
		writel(readl(NPU_L2_MPP_CFG_REG_ADDR)       | (0x1 << L2_MPP_CFG_CFG_MPP_BYPASS_FIELD_OFFSET),         NPU_L2_MPP_CFG_REG_ADDR);
	}
	if(mpp_type == NPU_IACL)
	{    //iacl
		writel(readl(NPU_IACL_MPP_CFG0_REG_ADDR)    | (0x1 << IACL_MPP_CFG0_CFG_MPP_BYPASS_FIELD_OFFSET),      NPU_IACL_MPP_CFG0_REG_ADDR);
	}
	if(mpp_type == NPU_EACL)
	{   //eacl
		writel(readl(NPU_EACL_MPP_CFG0_REG_ADDR)    | (0x1 << EACL_MPP_CFG0_CFG_MPP_BYPASS_FIELD_OFFSET),      NPU_EACL_MPP_CFG0_REG_ADDR);
	}
}

void npu_mpp_unbypass(enum NPU_MPP_TYPE mpp_type)
{
	if(mpp_type == NPU_NAT)
	{    //nat
		writel((readl(NPU_NAT_MPP_CFG_REG_ADDR) & 0xffefffff) | (0x0 << NAT_MPP_CFG_CFG_MPP_BYPASS_FIELD_OFFSET),  NPU_NAT_MPP_CFG_REG_ADDR);
	}
	if(mpp_type == NPU_IVLAN)
	{   //ivlan port
		writel((readl(NPU_IVLAN_PORT_MPP_CFG_REG_ADDR) & 0xfffeffff) | (0x0 << IVLAN_PORT_MPP_CFG_CFG_MPP_BYPASS_FIELD_OFFSET), NPU_IVLAN_PORT_MPP_CFG_REG_ADDR);
		writel((readl(NPU_IVLAN_VID_MPP_CFG_REG_ADDR)  & 0xfffeffff) | (0x0 << IVLAN_VID_MPP_CFG_CFG_MPP_BYPASS_FIELD_OFFSET) , NPU_IVLAN_VID_MPP_CFG_REG_ADDR);
		writel((readl(NPU_IVLAN_LKP_MPP_CFG0_REG_ADDR) & 0xfffeffff) | (0x0 << IVLAN_LKP_MPP_CFG0_CFG_MPP_BYPASS_FIELD_OFFSET), NPU_IVLAN_LKP_MPP_CFG0_REG_ADDR);
	}
	if(mpp_type == NPU_ARP)
	{    //arp
		writel((readl(NPU_ARP_MPP_CFG_REG_ADDR) & 0xfffeffff)      | (0x0 << ARP_MPP_CFG_CFG_MPP_BYPASS_FIELD_OFFSET),        NPU_ARP_MPP_CFG_REG_ADDR);
	}
	if(mpp_type == NPU_EVLAN)
	{    //evlan lkp
		writel((readl(NPU_EVLAN_LKP_CFG_REG_ADDR)  & 0xfffeffff)   | (0x0 << EVLAN_LKP_CFG_CFG_MPP_BYPASS_FIELD_OFFSET),      NPU_EVLAN_LKP_CFG_REG_ADDR);
		writel((readl(NPU_EVLAN_XLT_CFG0_REG_ADDR) & 0xfffeffff)   | (0x0 << EVLAN_XLT_CFG0_CFG_MPP_BYPASS_FIELD_OFFSET),     NPU_EVLAN_XLT_CFG0_REG_ADDR);
		writel((readl(NPU_EVLAN_ACT_CFG_REG_ADDR)  & 0xfffeffff)   | (0x0 << EVLAN_ACT_CFG_CFG_MPP_BYPASS_FIELD_OFFSET),      NPU_EVLAN_ACT_CFG_REG_ADDR);
	}
	if(mpp_type == NPU_L3)
	{    //l3
		writel((readl(NPU_L3_MPP_CFG_REG_ADDR) & 0xfffeffff)       | (0x1 << L3_MPP_CFG_CFG_MPP_BYPASS_FIELD_OFFSET),         NPU_L3_MPP_CFG_REG_ADDR);
	}
	if(mpp_type == NPU_L2)
	{    //l2
		writel((readl(NPU_L2_MPP_CFG_REG_ADDR) & 0xfffeffff)       | (0x0 << L2_MPP_CFG_CFG_MPP_BYPASS_FIELD_OFFSET),         NPU_L2_MPP_CFG_REG_ADDR);
	}
	if(mpp_type == NPU_IACL)
	{    //iacl
		writel((readl(NPU_IACL_MPP_CFG0_REG_ADDR) & 0xfffeffff)    | (0x0 << IACL_MPP_CFG0_CFG_MPP_BYPASS_FIELD_OFFSET),      NPU_IACL_MPP_CFG0_REG_ADDR);
	}
	if(mpp_type == NPU_EACL)
	{   //eacl
		writel((readl(NPU_EACL_MPP_CFG0_REG_ADDR) & 0xfffeffff)    | (0x0 << EACL_MPP_CFG0_CFG_MPP_BYPASS_FIELD_OFFSET),      NPU_EACL_MPP_CFG0_REG_ADDR);
	}
}

void npu_nat_ipv4_private_ip_set(int ip_num, int enable, uint32_t pri_ip, int mask_len)
{
	uint32_t reg_mask = 0;

	if(ip_num < 8)
	{
		writel(pri_ip, (uintptr_t)(NPU_NAT_PRIVATE_IP_V4_INFO0_REG_ADDR + ip_num * 4));
		if(ip_num < 4)
		{
			reg_mask = 0x7f << (ip_num * 8);  //TODO need to chang to 8(when rtl update)
			writel((readl(NPU_NAT_IPV4_MASK_LEN0123_REG_ADDR) & ~(reg_mask)) | (mask_len <<  (ip_num * 8)) | (enable << (6 + ip_num * 8)), NPU_NAT_IPV4_MASK_LEN0123_REG_ADDR);
		}
		else
		{
			ip_num = ip_num -4;
			reg_mask = 0x7f << (ip_num * 8);
			writel((readl(NPU_NAT_IPV4_MASK_LEN4567_REG_ADDR)& ~(reg_mask)) | (mask_len <<  (ip_num * 8)) | (enable << (6 + ip_num * 8)), NPU_NAT_IPV4_MASK_LEN4567_REG_ADDR);
		}
	}
	else
	{
		printf("PRIVATE IP num only can be set less than 8 !!");
	}
}

void npu_nat_ipv6_private_ip_set(int ip_num, int enable, uint32_t pri_ip[4], int mask_len)
{
	uint32_t reg_mask = 0;
	int i;

	if(ip_num < 8)
	{
		for(i=0; i<4; i++)
		{
			writel(pri_ip[i], (uintptr_t)(NPU_NAT_PRIVATE_IP_V6_INFO0_0_REG_ADDR + (ip_num * 16) + (i * 4)));
		}

		if(ip_num < 2)
		{
			reg_mask = 0x1ff << (ip_num * 16);
			writel((readl(NPU_NAT_IPV6_MASK_LEN01_REG_ADDR) & ~(reg_mask)) | (mask_len <<  (ip_num * 16)) | (enable << (8 + ip_num * 16)), NPU_NAT_IPV6_MASK_LEN01_REG_ADDR);
		}
		if(ip_num < 4 && ip_num >= 2)
		{
			ip_num = ip_num -2;
			reg_mask = 0x1ff << (ip_num * 16);
			writel((readl(NPU_NAT_IPV6_MASK_LEN23_REG_ADDR)& ~(reg_mask)) | (mask_len <<  (ip_num * 16)) | (enable << (8 + ip_num * 16)), NPU_NAT_IPV6_MASK_LEN23_REG_ADDR);
		}
		if(ip_num < 6 && ip_num >= 4)
		{
			ip_num = ip_num -4;
			reg_mask = 0x1ff << (ip_num * 16);
			writel((readl(NPU_NAT_IPV6_MASK_LEN45_REG_ADDR)& ~(reg_mask)) | (mask_len <<  (ip_num * 16)) | (enable << (8 + ip_num * 16)), NPU_NAT_IPV6_MASK_LEN45_REG_ADDR);
		}
		if(ip_num < 8 && ip_num >= 6)
		{
			ip_num = ip_num -6;
			reg_mask = 0x1ff << (ip_num * 16);
			writel((readl(NPU_NAT_IPV6_MASK_LEN67_HOST_MODE_REG_ADDR)& ~(reg_mask)) | (mask_len <<  (ip_num * 16)) | (enable << (8 + ip_num * 16)), NPU_NAT_IPV6_MASK_LEN67_HOST_MODE_REG_ADDR);
		}
	}
	else
	{
		printf("PRIVATE IP num only can be set less than 8 !!");
	}
}

void hnat_mode(int nat_mode)
{
	uint32_t reg_mask;

	reg_mask = NAT_IPV6_MASK_LEN67_HOST_MODE_HNAT_MODE_FIELD_SIZE << NAT_IPV6_MASK_LEN67_HOST_MODE_HNAT_MODE_FIELD_OFFSET;
	writel((readl(NPU_NAT_IPV6_MASK_LEN67_HOST_MODE_REG_ADDR)& ~(reg_mask)) | (nat_mode << NAT_IPV6_MASK_LEN67_HOST_MODE_HNAT_MODE_FIELD_OFFSET), NPU_NAT_IPV6_MASK_LEN67_HOST_MODE_REG_ADDR);
}

void l3_care_nat_result(int enable)
{
	writel((readl(NPU_L3_MPP_CFG_REG_ADDR)& 0xfff7ffff) | (enable << L3_MPP_CFG_L3_CARE_NAT_RESULT_EN_FIELD_OFFSET), NPU_L3_MPP_CFG_REG_ADDR);
}

void npu_hif_port_set(int port_num)
{
	port_num = 1 << port_num;
	writel((readl(NPU_LIF_HIF_CFG_REG_ADDR)& 0xfffffc00) | (port_num << LIF_HIF_CFG_LIF_HIF_SEL_FIELD_OFFSET), NPU_LIF_HIF_CFG_REG_ADDR);
}

void read_npu_mib(unsigned int mib_offset)
{
    unsigned long long count = 0, len = 0, val = 0;

    writel(mib_offset, 0x11034010);
    while(!readl(0x11034028));
    val = readl(0x11034018) & 0xff;
    count = readl(0x11034014) | (val << 32);

    val = readl(0x11034020) & 0xffff;
    len = readl(0x1103401c) | (val << 32);
    printf("get mib_addr:0x%x count:%llu len:%llu\n", mib_offset, count, len);
}

void dump_npu_mib(void)
{
	for (unsigned int i = 0; i < 0x623; i++)
		read_npu_mib(i);
}

void dump_lif_mib(void)
{
    printf("addr:0x0800015c %u\n", readl(0x0800015c));
    printf("addr:0x08000164 %u\n", readl(0x08000164));
    printf("addr:0x0800016c %u\n", readl(0x0800016c));
    printf("addr:0x0800017c %u\n", readl(0x0800017c));
    printf("addr:0x08000180 %u\n", readl(0x08000180));
    printf("addr:0x08000184 %u\n", readl(0x08000184));
    printf("addr:0x08000188 %u\n", readl(0x08000188));
    printf("addr:0x08000194 %u\n", readl(0x08000194));

    printf("addr:0x0801015c %u\n", readl(0x0801015c));
    printf("addr:0x08010164 %u\n", readl(0x08010164));
    printf("addr:0x0801016c %u\n", readl(0x0801016c));
    printf("addr:0x0801017c %u\n", readl(0x0801017c));
    printf("addr:0x08010180 %u\n", readl(0x08010180));
    printf("addr:0x08010184 %u\n", readl(0x08010184));
    printf("addr:0x08010188 %u\n", readl(0x08010188));
    printf("addr:0x08010194 %u\n", readl(0x08010194));
}

void dump_mib(void)
{
	dump_lif_mib();
	dump_npu_mib();
}

int do_npu_init(void)
{
	uint32_t private_ip = 0xc0a80498;

	sys_npu_reset();

	npu_mpp_bypass(NPU_IACL);
	npu_mpp_bypass(NPU_EACL);
	npu_mpp_bypass(NPU_IVLAN);
	npu_mpp_bypass(NPU_EVLAN);

	writel(readl(0x11010000) | (0x1 << 21), 0x11010000);

	npu_hif_port_set(7);
	l3_care_nat_result(0);

	npu_mpp_unbypass(NPU_NAT);
	hnat_mode(SYMMETRIC_MODE);
	npu_nat_ipv4_private_ip_set(0, 1, private_ip, 8);
	writel((readl(LIF_SYSM_BASE + 0x64) | 0x3), LIF_SYSM_BASE + 0x64);
	writel((readl(LIF_SYSM_BASE + 0x64) | (0x1 << 14)), LIF_SYSM_BASE + 0x64);
	writel((readl(LIF_SYSM_BASE + 0x68) | 0x3), LIF_SYSM_BASE + 0x68);
	writel((readl(LIF_SYSM_BASE + 0x68) | (0x1 << 14)), LIF_SYSM_BASE + 0x68);

	gmac_init();
	sf_fpga_phy_init();
	printf("end %s\n", __func__);
	return 0;
}

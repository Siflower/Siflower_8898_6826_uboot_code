/*
* Description
*
* Copyright (C) 2016-2022 Qin.Xia <qin.xia@siflower.com.cn>
*
* Siflower software
*/


#include "sf_gmac.h"


bool init_flag = false;

struct XG_macContext g_gmac_context = {
	.LOOPBACK = 0,
	.DUPLEX_MODE = DEFAULT_MAC_DUPLEX_MODE,
	.MAC_SPEED = SPEED100,
	.BUFFER_DESC_MODE = DEFAULT_MAC_DESC_MODE,
	.PHY_TESTMODE = 0,
	.TRANSMIT_DESC_SIZE = DEFAULT_DMA_TX_DESC_NUM,
	.RECEIVE_DESC_SIZE  = DEFAULT_DMA_RX_DESC_NUM,
	.CSR_CLK_DIV = DEFAULT_MAC_MDC_DIV,
	.BASE_CTRL = DEFAULT_GMAC_BASE_CTRL,
	.DEFAULT_MAC_ADDRESS = {0x00, 0x55, 0x7B, 0xB5, 0x7D, 0xF7}
};

int32_t gmac_set_mdc_clk_div(uintptr_t mac_addr_base,int32_t clk_div_val)
{
	int32_t orig_data = CSR_REG_READ(mac_addr_base + REG_GMAC_GmiiAddr);
	orig_data &= (~(0xf<<2));
	orig_data |= clk_div_val;
	CSR_REG_WRITE(mac_addr_base + REG_GMAC_GmiiAddr, orig_data);
	return 0;
}

int32_t gmac_set_mac_addr0(uintptr_t mac_base_addr,char *mac)
{
    int address_lower = 0;
    int address_upper = CSR_REG_READ(mac_base_addr + REG_GMAC_Addr0High);
    address_upper = address_upper & 0xffff0000;
    address_upper |= (*(mac + 5) << 8) | (*(mac + 4));

    CSR_REG_WRITE(mac_base_addr + REG_GMAC_Addr0High, address_upper);

    address_lower = (*(mac + 0)) | (*(mac + 1) << 8) | (*(mac + 2) << 16) | (*(mac + 3) << 24);
    CSR_REG_WRITE(mac_base_addr + REG_GMAC_Addr0Low, address_lower);

    return 0;
}

int32_t gmac_read_version(uintptr_t mac_base_addr)
{
    return CSR_REG_READ(mac_base_addr+ REG_GMAC_Version);
}

int32_t gmac_mac_init(uintptr_t mac_base_addr,uint32_t mode,uint32_t speed,int32_t mac_loopback, int32_t base_ctrl)
{

    //control reg
    int32_t mac_cfg = 0;

    if(speed == SPEED1000)
	{
		mac_cfg &= (~(1<<15));
	}
    else if(speed == SPEED100)
	{
		mac_cfg |= (1<<15) | (1<<14) ;
	}
	else
	{
		mac_cfg |= ((1<<15) & (~(1<<14))) ;

	}

    CSR_REG_WRITE(mac_base_addr + REG_GMAC_Config,mac_cfg);

	if((speed != SPEED1000) && (speed != SPEED100))
	{
		writel(0x0,0x0ce01800+0xec);
        writel(0x2,0x0ce01800+0xec);
	}

	mydl(50);

	mac_cfg |= base_ctrl;
    if(mode == FULLDUPLEX)
	{
		mac_cfg |= 0x800;
	}
	else
	{
		mac_cfg &= ~(1<<11);

	}

    if(mac_loopback)
	{
		mac_cfg |= 0x1000;
	}
    //enable mac tx/rx
    mac_cfg |= ( 0x8 | 0x4 );
    mac_cfg |= ( 0x1 << 31 );

    CSR_REG_WRITE(mac_base_addr + REG_GMAC_Config,mac_cfg);
	    //filter reg
    CSR_REG_WRITE(mac_base_addr + REG_GMAC_FrameFilter,0);
    //flow reg
    CSR_REG_WRITE(mac_base_addr + REG_GMAC_FlowControl,0x4 | 0x2 /*| 0xffff*/);

	return 0;
}

void gmac_promisc_enable(uintptr_t mac_base_addr)
{
	reg_set_bits(mac_base_addr+ REG_GMAC_FrameFilter, 1);
}

void gmac_pause_control(uintptr_t mac_base_addr)
{
	//uint32_t omr_reg;
	uint32_t mac_flow_control_reg;
	/*omr_reg = CSR_REG_READ(REG_DWCXG_DMA_Control);
	omr_reg |= DmaRxFlowCtrlAct4K | DmaRxFlowCtrlDeact5K | DmaEnHwFlowCtrl;
	CSR_REG_WRITE(REG_DWCXG_DMA_Control, omr_reg);*/


	mac_flow_control_reg = CSR_REG_READ(mac_base_addr+ REG_GMAC_FlowControl);
	mac_flow_control_reg |= GmacRxFlowControl | GmacTxFlowControl/* | 0xFFFF0000*/;
	CSR_REG_WRITE(mac_base_addr+REG_GMAC_FlowControl,mac_flow_control_reg);
}

void gmac_ptp_set_timestamp_control_reg(uintptr_t mac_addr_base,int control_value)
{
	CSR_REG_WRITE(mac_addr_base+REG_GMAC_TSControl, control_value);
	return;
}

void gmac_ptp_mask_the_timestamp_trigger_interrupt(uintptr_t mac_addr_base)
{
	reg_set_bits(mac_addr_base+REG_GMAC_InterruptMask,0x200 );
}

void gmac_ptp_enable_timestamping(uintptr_t mac_addr_base)
{
	reg_set_bits(mac_addr_base+REG_GMAC_TSControl, 1);
}

void gmac_ptp_set_sub_second(uintptr_t mac_addr_base,int ptp_clock)
{
	char SubSecondIncrementValue = 1000 / ptp_clock;
	if(readl(mac_addr_base+REG_GMAC_TSControl) & (1<<9))
	{
		SubSecondIncrementValue = 1000 / ptp_clock;
	}
	else
	{
		//SubSecondIncrementValue = 1000 / ptp_clock /0.465,
		//1000 / 0.465 = 2151
		SubSecondIncrementValue = 2151 / ptp_clock;
	}
	CSR_REG_WRITE(mac_addr_base+REG_GMAC_TSSubSecIncr, SubSecondIncrementValue);
}

void gmac_ptp_select_update_method(uintptr_t mac_addr_base,int update_method)
{
	if(update_method == 0)
	{
		reg_set_bits(mac_addr_base+REG_GMAC_TSControl, (1<<5));
	}
	else
	{
		reg_clear_bits(mac_addr_base+REG_GMAC_TSControl, (1<<5));
	}

}

void gmac_ptp_set_update_system_time_value(uintptr_t mac_addr_base,int add_or_subtract,
		uint32_t seconds_high,
		uint32_t seconds_low)
{
	uint32_t REG_GMAC_TSLowUpdate_value = seconds_low;
	if (add_or_subtract == 0)
	{
		REG_GMAC_TSLowUpdate_value = (REG_GMAC_TSLowUpdate_value | (1<<31));
    }
	CSR_REG_WRITE(mac_addr_base+REG_GMAC_TSHighUpdate, seconds_high);
	CSR_REG_WRITE(mac_addr_base+REG_GMAC_TSLowUpdate, REG_GMAC_TSLowUpdate_value);
}

void gmac_ptp_initialize_timestamp(uintptr_t mac_addr_base)
{
    reg_set_bits(mac_addr_base + REG_GMAC_TSControl, (1<<2));
}

void gmac_ptp_init(uintptr_t mac_addr_base)
{
	gmac_ptp_set_timestamp_control_reg(mac_addr_base,(1<<25)|(1<<16)|(1<<13)|(1<<11)|(1<<9)|(1<<0));
	gmac_ptp_mask_the_timestamp_trigger_interrupt(mac_addr_base);
	gmac_ptp_enable_timestamping(mac_addr_base);
	gmac_ptp_set_sub_second(mac_addr_base,50);

	//only in Fine Update method we need to set addend register.
	//gmac_ptp_set_timestamp_addend_value(PTP_CLOCK);

	gmac_ptp_select_update_method(mac_addr_base,1);
	//Timestamp Initialize
	//when we init timestamp, the system time is initialized (overwritten) with the value specified in the Register 452 and Register 453,
	//and we want the init value is 0, so we chose add(bit 31 is 0) here.
	gmac_ptp_set_update_system_time_value(mac_addr_base,1, 0, 0);
	gmac_ptp_initialize_timestamp(mac_addr_base);
}

void gmac_core_init(uintptr_t mac_addr_base,struct XG_macContext *gmacdev)
{
	gmac_set_mac_addr0(mac_addr_base,gmacdev->DEFAULT_MAC_ADDRESS);
	gmac_set_mdc_clk_div(mac_addr_base,0x14);
	writel(0xffffffff, XGMAC_ADDR_BASE + XGMAC_MDIO_C22P);
	gmacdev->version = gmac_read_version(mac_addr_base);//get mac version
	gmac_mac_init(mac_addr_base,gmacdev->DUPLEX_MODE, gmacdev->MAC_SPEED,gmacdev->LOOPBACK, gmacdev->BASE_CTRL);

	gmac_promisc_enable(mac_addr_base);
	gmac_pause_control(mac_addr_base);
	gmac_ptp_init(mac_addr_base);
}


void gmac_init(void)
{
	int32_t i = 0;
	struct XG_macContext *gmacdev = &g_gmac_context;

	if (init_flag == true)
		return;

	init_flag = true;

	//CSR_REG_WRITE(REG_DWCXG_MAC_TX_Configuration, CSR_REG_READ(REG_DWCXG_MAC_TX_Configuration) | (1<<32));//only for test

	CSR_REG_WRITE(LIF_SYSTEM, CSR_REG_READ(LIF_SYSTEM) | (1<<8));//set rgmii

	xgmac_dma_init(gmacdev);
	xgmac_init_mtl();

	for (i = 0; i < 5; i++) {
		gmac_core_init(GMA0_BASE_ADDR + i * 0x4000, gmacdev);
	}
}

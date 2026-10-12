/*
* Description
*
* Copyright (C) 2016-2022 Qin.Xia <qin.xia@siflower.com.cn>
*
* Siflower software
*/

#include "npu_head.h"
#include "sf_npu_table.h"
#include "sf_npu_init.h"

void clear_se_tables(void) {

	unsigned int rdata;

	//se table clear
	SE_WR_REG(SE_CLR_RAM_CTRL_RGT_REG_ADDR, 0xffff);
	while(1) {
		SE_RD_REG(SE_CLR_RAM_CTRL_RGT_REG_ADDR, rdata);
		if( (rdata&0xffff) == 0x0 ) {
			break;
		}
	}

	//nat se table clear
	SE_WR_REG(SE_NAT_COMMAND_RGT_REG_ADDR, 0x3fffff);
	while(1) {
		SE_RD_REG(SE_NAT_COMMAND_RGT_REG_ADDR, rdata);
		if( (rdata&0x3fffff) == 0x0 ) {
			break;
		}
	}

	//tcam se table clear, need to add
	SE_WR_REG(SE_TCAM_CLR_RGT_REG_ADDR, 0x1f);
	while(1) {
		SE_RD_REG(SE_TCAM_CLR_RGT_REG_ADDR, rdata);
		if( (rdata&0x1f) == 0x0 ) {
			break;
		}
	}
}

void l2_tb_cfg(int rule_index, int oport, int vid, int hnat_mode, Sekey* key, Sersp* rsp)
{
    L2Key_S         l2_key;
    L2Rsp_S         l2_rsp;
    L2Cfg_S         l2_cfg;

    l2_key.ovid           = vid; //12
    l2_key.mac[0]        = key->da[0];  //a85af3000226
    l2_key.mac[1]        = key->da[1];
    l2_key.mac[2]        = key->da[2];
    l2_key.mac[3]        = key->da[3];
    l2_key.mac[4]        = key->da[4];
    l2_key.mac[5]        = key->da[5];
    l2_rsp.port_bitmap    = 1 << oport; //36bit
    l2_rsp.sta_index      = 0; //10bit
    l2_rsp.repeater_index = 0; //4bit
    l2_rsp.l3_en          = 0x1; //1bit
    l2_rsp.sa_cml         = 0x2; //2bit 00:drop 01:to cpu 10:forward 11:to cpu && forward, can be diff action to da
    l2_rsp.da_cml         = 0x2; //2bit 00:drop 01:to cpu 10:forward 11:to cpu && forward

    l2_cfg.hnat_mode         = hnat_mode;

    cfg_l2_table_item(&l2_key,
                      &l2_rsp,
                      &l2_cfg);

    printf( "l2 tb ld\n");
}

void nat_tb_cfg(int rule_index, int hnat_mode, Sekey* key, Sersp* rsp)
{
    NatKey_S        nat_key;
    NatRsp_S        nat_rsp;
    NatCfg_S        nat_cfg;

    nat_key.pkt_len     =  0xa0 ; //14bit used for search and mib, hw use software not care
    nat_key.l3_flag     =  0x0  ; //1bit   0:PV4  1:PV6
    nat_key.l4_flag     =  key->type;
    nat_key.dnat_flag   =  key->dnat_flag;  //1bit 1: dnat, software use, hw has no such attr
    nat_key.frag_flag   =  0x0  ;  //2bit 0:NO FRG 1:F FRG 2: INT FRG 3:L FRG, software use
    nat_key.pkt_id      =  0xb55;     //32bit V4:16bit  V6:32bit , for fragment, software use
    nat_key.sport       =  key->sport;
    //nat_key.sip[0]      =  0xc0a80498;
    nat_key.sip[0]      =  key->sip[0];
    nat_key.sip[1]      =  key->sip[1];
    nat_key.sip[2]      =  key->sip[2];
    nat_key.sip[3]      =  key->sip[3];
    nat_key.dport       =  key->dport;
    //nat_key.dip[0]      =  0xc0a81001;
    nat_key.dip[0]      =  key->dip[0];
    nat_key.dip[1]      =  key->dip[1];
    nat_key.dip[2]      =  key->dip[2];
    nat_key.dip[3]      =  key->dip[3];
    nat_rsp.repl_pri_en =  0x1 ;
    nat_rsp.repl_pri    =  0x3 ; //  TODO:priority where to add
    // those mac_index used when l3 not hit, if l3 hit, use l3 mac_index
    nat_rsp.smac_index  =  rule_index ; // route mac table, 64
    nat_rsp.dmac_index  =  rule_index + 1; // l2 mac table = hash + mac_direct, 2k
    nat_rsp.repl_port   =  rsp->rport;
    nat_rsp.repl_ip[0] =   rsp->rip[0];
    nat_rsp.repl_ip[1] =   rsp->rip[1];
    nat_rsp.repl_ip[2] =   rsp->rip[2];
    nat_rsp.repl_ip[3] =   rsp->rip[3];

    nat_cfg.hnat_mode = hnat_mode;

    cfg_nat_table_item(&nat_key,
                       &nat_rsp,
                       &nat_cfg);

    printf( "nat tb ld\n");
}

void l3_tb_cfg(int rule_index, int vid, int hnat_mode, Sekey* key, Sersp* rsp)
{
    L3UcIpv4Key_S   l3_uc_ipv4_key;
    L3UcRsp_S       l3_uc_rsp;
    L3Cfg_S         l3_cfg;

    l3_uc_ipv4_key.key_mode =  0x00 ; // used for tcam mode
    l3_uc_ipv4_key.table_id =  0x00 ; // used for tcam mode
    l3_uc_ipv4_key.ovid     =  vid ;
    if(key->dnat_flag == 1)
    {
        l3_uc_ipv4_key.dip[0]   =  rsp->rip[0];
        l3_uc_ipv4_key.dip[1]   =  rsp->rip[1];
        l3_uc_ipv4_key.dip[2]   =  rsp->rip[2];
        l3_uc_ipv4_key.dip[3]   =  rsp->rip[3];
    }
    else
    {
        l3_uc_ipv4_key.dip[0]   =  key->dip[0];
        l3_uc_ipv4_key.dip[1]   =  key->dip[1];
        l3_uc_ipv4_key.dip[2]   =  key->dip[2];
        l3_uc_ipv4_key.dip[3]   =  key->dip[3];
    }

    l3_uc_rsp.intf_id       =  rule_index; // smac and pppoe table index, as smac_index
    l3_uc_rsp.oport_id      =  rsp->ovport;
    l3_uc_rsp.next_hop_ptr  =  rule_index + 1; // l2 mac pointer, as dmac_index

    l3_cfg.hnat_mode    = hnat_mode;

    cfg_l3_uc_ipv4_table_item(&l3_uc_ipv4_key,
                              &l3_uc_rsp,
                              &l3_cfg);
    printf( "l3 tb ld\n");

}

void arp_tb_cfg(int rule_index, int vid, int hnat_mode, Sekey* key, Sersp* rsp)
{
    IntfKey_S intf_key;
    IntfRsp_S intf_rsp;
    ArpKey_S  arp_key;
    ArpRsp_S  arp_rsp;
    ArpCfg_S  arp_cfg;

    intf_key.intf_id    = rule_index; // smac and pppoe table index, as smac_index
    intf_rsp.pppoe_en   = rsp->pppoe_en | 0x2;  // 0x2 is arp hit, as valid
    intf_rsp.pppoe_hdr  = rsp->pppoe_hdr;
    intf_rsp.smac       = rsp->rsa;
    intf_rsp.ovid       = vid;

    arp_key.next_hop_ptr  = rule_index + 1; // l2 mac pointer, as dmac_index
    arp_key.pkt_len       = 0xa0;

    arp_rsp.sta_index      = 0;
    arp_rsp.repeater_index = 0;
    arp_rsp.dmac           = rsp->rda;
    arp_rsp.ovid           = vid;

    arp_cfg.hnat_mode   = hnat_mode;

    cfg_intf_table_item(&intf_key,
                        &intf_rsp,
                        &arp_cfg);

    cfg_arp_table_item(&arp_key,
                       &arp_rsp,
                       &arp_cfg);


    printf( "arp tb ld\n");
}

void ivlan_tb_add_cfg(int oport, int vid, int hnat_mode, Sekey* key, Sersp* rsp)
{
    IvlanIportKey_S  ivlan_iport_key;
    IvlanIportRsp_S  ivlan_iport_rsp; // not config TPID

    IvlanPbvKey_S ivlan_pbv_key;
    IvlanPbvRsp_S ivlan_pbv_rsp;

    IvlanXltKey_S ivlan_xlt_key;
    IvlanXltRsp_S ivlan_xlt_rsp;

    EvlanPtpidKey_S evlan_lkp_port_key;
    EvlanPtpidRsp_S evlan_lkp_port_rsp; // config TPID
    EvlanActKey_S  evlan_act_key;
    EvlanActRsp_S  evlan_act_rsp;
    EvlanLkpKey_S  evlan_lkp_key;
    EvlanLkpRsp_S  evlan_lkp_rsp;
    EvlanCfg_S evlan_cfg;


    IvlanCfg_S ivlan_cfg;
    SplKey_S  ivlan_spl_key;

    L2Cfg_S         l2_cfg;
    L2Key_S         l2_learn_key;
    L2Rsp_S         l2_learn_rsp;

	l2_learn_key.ovid           = vid; //12
	l2_learn_key.mac[0]        = 0x0b;  //000ec6d82c0b
	l2_learn_key.mac[1]        = 0x2c;
	l2_learn_key.mac[2]        = 0xd8;
	l2_learn_key.mac[3]        = 0xc6;
	l2_learn_key.mac[4]        = 0x0e;
	l2_learn_key.mac[5]        = 0x00;

    ivlan_pbv_key.iport_num        = oport;

    //ivlan_cfg.hnat_mode        = hnat_mode;

    ivlan_pbv_rsp.vld              = 0x1;
    ivlan_pbv_rsp.transparent_en   = 0x0;
    ivlan_pbv_rsp.ovid             = 0x0;
    ivlan_pbv_rsp.ivid             = vid;
    ivlan_pbv_rsp.opri             = 0x0;
    ivlan_pbv_rsp.ipri             = 0x0;
    ivlan_pbv_rsp.dt_otag_action   = 0x0;
    ivlan_pbv_rsp.dt_potag_action  = 0x0;
    ivlan_pbv_rsp.dt_itag_action   = 0x0;
    ivlan_pbv_rsp.dt_pitag_action  = 0x0;
    ivlan_pbv_rsp.sot_otag_action  = 0x0;
    ivlan_pbv_rsp.sot_potag_action = 0x2;
    ivlan_pbv_rsp.sot_itag_action  = 0x2;
    ivlan_pbv_rsp.sot_pitag_action = 0x2;
    ivlan_pbv_rsp.sit_otag_action  = 0x2;
    ivlan_pbv_rsp.sit_potag_action = 0x2;
    ivlan_pbv_rsp.sit_itag_action  = 0x2;
    ivlan_pbv_rsp.sit_pitag_action = 0x2;
    ivlan_pbv_rsp.un_otag_action   = 0x2;
    ivlan_pbv_rsp.un_potag_action  = 0x2;
    ivlan_pbv_rsp.un_itag_action   = 0x2;
    ivlan_pbv_rsp.un_pitag_action  = 0x2;

    //act table
    evlan_act_key.tag_action_id    = 0x1;

    evlan_act_rsp.tt_atag_action   = 0x0;
    evlan_act_rsp.tt_patag_action  = 0x0;
    evlan_act_rsp.tt_otag_action   = 0x0;
    evlan_act_rsp.tt_potag_action  = 0x0;
    evlan_act_rsp.tt_itag_action   = 0x0;
    evlan_act_rsp.tt_pitag_action  = 0x0;
    evlan_act_rsp.dt_otag_action   = 0x0;
    evlan_act_rsp.dt_potag_action  = 0x0;
    evlan_act_rsp.dt_itag_action   = 0x0;
    evlan_act_rsp.dt_pitag_action  = 0x0;
    evlan_act_rsp.sot_otag_action  = 0x0;
    evlan_act_rsp.sot_potag_action = 0x0;
    evlan_act_rsp.sot_itag_action  = 0x0;
    evlan_act_rsp.sot_pitag_action = 0x0;
    //lkp port_table
    evlan_lkp_key.ovid = vid;

    evlan_lkp_rsp.port_bitmap       = 0xfffffffff;
    evlan_lkp_rsp.un_bitmap         = 0x8;
    evlan_lkp_rsp.sp_tree_port0     = 0x3;
    evlan_lkp_rsp.sp_tree_port1     = 0x3;
    evlan_lkp_rsp.sp_tree_port2     = 0x3;
    evlan_lkp_rsp.sp_tree_port3     = 0x3;
    evlan_lkp_rsp.sp_tree_port4     = 0x3;
    evlan_lkp_rsp.sp_tree_port5     = 0x3;
    evlan_lkp_rsp.sp_tree_port6     = 0x3;
    evlan_lkp_rsp.sp_tree_port7     = 0x3;
    evlan_lkp_rsp.sp_tree_port8     = 0x3;
    evlan_lkp_rsp.sp_tree_port9     = 0x3;
    evlan_lkp_rsp.outer_tpid        = 0x8100;

    evlan_lkp_port_key.tag_action_id = 0;

    evlan_lkp_port_rsp.inner_tpid = 0x8100;
    evlan_lkp_port_rsp.outer_tpid = 0x8100;
    //spl cfg, speed limit
    ivlan_spl_key.item_index = oport; // in port
    ivlan_spl_key.cnt = 0x0;
    ivlan_spl_key.credit = 0xffffff;
    //iport table
    ivlan_iport_key.iport_num     = oport;

    ivlan_iport_rsp.valid                = 0x1;
    ivlan_iport_rsp.iso_id               = 0x1;
    ivlan_iport_rsp.default_port         = 0x0;
    ivlan_iport_rsp.disable_vlan_check   = 0x0;
    ivlan_iport_rsp.ifiliter_en          = 0x0;
    ivlan_iport_rsp.use_ivid_as_ovid     = 0x0;
    ivlan_iport_rsp.vt_miss_drop         = 0x0;
    ivlan_iport_rsp.vt_en                = 0x1;
    ivlan_iport_rsp.vfp_based_vid_enable = 0x0;
    ivlan_iport_rsp.vlan_security_mode   = 0x0;
    ivlan_iport_rsp.vid_zero_handle      = 0x0;
    ivlan_iport_rsp.pass_mode            = 0x0;




    //xlt table
    ivlan_xlt_key.iport_num        = oport;
    ivlan_xlt_key.inner_vid        = 0x0;
    ivlan_xlt_key.outer_vid        = 0x0;


    ivlan_xlt_rsp.transparent_en   = 0x0;
    ivlan_xlt_rsp.new_ovid             = vid;
    ivlan_xlt_rsp.new_ivid             = 0x0;
    ivlan_xlt_rsp.new_opri             = 0x0;
    ivlan_xlt_rsp.new_ipri             = 0x0;
    ivlan_xlt_rsp.dt_otag_action   = 0x2;
    ivlan_xlt_rsp.dt_potag_action  = 0x2;
    ivlan_xlt_rsp.dt_itag_action   = 0x2;
    ivlan_xlt_rsp.dt_pitag_action  = 0x2;
    ivlan_xlt_rsp.sot_otag_action  = 0x2;
    ivlan_xlt_rsp.sot_potag_action = 0x2;
    ivlan_xlt_rsp.sot_itag_action  = 0x2;
    ivlan_xlt_rsp.sot_pitag_action = 0x2;
    ivlan_xlt_rsp.sit_otag_action  = 0x2;
    ivlan_xlt_rsp.sit_potag_action = 0x2;
    ivlan_xlt_rsp.sit_itag_action  = 0x2;
    ivlan_xlt_rsp.sit_pitag_action = 0x2;
    ivlan_xlt_rsp.un_otag_action   = 0x2;
    ivlan_xlt_rsp.un_potag_action  = 0x2;
    ivlan_xlt_rsp.un_itag_action   = 0x2;
    ivlan_xlt_rsp.un_pitag_action  = 0x2;


    cfg_ivlan_pbv_table_item(&ivlan_pbv_key,
                             &ivlan_pbv_rsp,
                             &ivlan_cfg);
    cfg_l2_table_item(&l2_learn_key,
                               &l2_learn_rsp,
                               &l2_cfg);

    cfg_evlan_ptpid_table_item(&evlan_lkp_port_key,
                               &evlan_lkp_port_rsp,
                               &evlan_cfg);

    cfg_evlan_lkp_table_item(&evlan_lkp_key,
                             &evlan_lkp_rsp,
                             &evlan_cfg);
    cfg_evlan_act_table_item(&evlan_act_key,
                             &evlan_act_rsp,
                             &evlan_cfg);
    cfg_ivlan_spl_table_item(&ivlan_spl_key);

    cfg_ivlan_iport_table_item(&ivlan_iport_key,
                             &ivlan_iport_rsp,
                             &ivlan_cfg);


    cfg_ivlan_xlt_table_item(&ivlan_xlt_key,
                             &ivlan_xlt_rsp,
                             &ivlan_cfg);

	printf("end %s\n", __func__);
}

void nat_test(int rule_index, int oport, int vid, int dnat_flag, Sekey* key, Sersp* rsp)
{
    int hnat_mode = key->nat_mode;

    key->dnat_flag = dnat_flag;
    // MAIN PART

    l2_tb_cfg(rule_index, oport, vid, hnat_mode, key, rsp);
	if (vid != 0)
	{
		npu_mpp_unbypass(NPU_IVLAN);
		npu_mpp_unbypass(NPU_EVLAN);
		// bypass lkp table here
		writel(readl(NPU_IVLAN_LKP_MPP_CFG0_REG_ADDR) | (0x1 << IVLAN_LKP_MPP_CFG0_CFG_MPP_BYPASS_FIELD_OFFSET), NPU_IVLAN_LKP_MPP_CFG0_REG_ADDR);
		ivlan_tb_add_cfg(oport, vid, hnat_mode, key, rsp);
	}

    nat_tb_cfg(rule_index, hnat_mode, key, rsp);
    l3_tb_cfg(rule_index, vid, hnat_mode, key, rsp);
    arp_tb_cfg(rule_index, vid, hnat_mode, key, rsp);
	printf("end %s\n", __func__);
}

// SPDX-License-Identifier: GPL-2.0+
/*
 * (C) Copyright 2000
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 */

/*
 * Boot support
 */
#include <common.h>
#include <bootstage.h>
#include <command.h>
#include <dm.h>
#include <env.h>
#include <image.h>
#include <net.h>
#include <net/udp.h>
#include <net/sntp.h>
#include "../drivers/net/sf_npu/se/se_common.h"
#include "../drivers/net/sf_npu/sf_npu_init.h"

unsigned long g_rule_index = 0;
unsigned long g_oport = 4;
unsigned long g_dnat_flag = 0;
unsigned long g_vid = 0;

extern int mac_table_index;
extern int napt_index;

Sekey key = {
    .nat_mode = SYMMETRIC_MODE,  //symmetric
	.type    =  0, //0: tcp or 1: udp
    .sport   =  0xa28c,
    .sip[0]  =  0x98,
    .sip[1]  =  0x04,
    .sip[2]  =  0xa8,
    .sip[3]  =  0xc0,
    .dport   =  0x50,
    .dip[0]  =  0x01,
    .dip[1]  =  0x10,
    .dip[2]  =  0xa8,
    .dip[3]  =  0xc0,
    .da[0]   =  0x26,
    .da[1]   =  0x02,
    .da[2]   =  0x00,
    .da[3]   =  0xf3,
    .da[4]   =  0x5a,
    .da[5]   =  0xa8,
};

Sersp rsp = {
	.rport    = 0x1234,
    .rip[0]   = 0x78,
    .rip[1]   = 0x56,
    .rip[2]   = 0x34,
    .rip[3]   = 0x12,
    .rsa      = 0xaaaa0000aaaa,
    .rda      = 0x555500005555,
    .pppoe_en  = 1,
    .pppoe_hdr = 0x1122334455667788,
    .ovport    = 0,
};

static int do_npu_help(struct cmd_tbl *cmdtp, int flag, int argc,
		    char *const argv[])
{
	printf("============ NPU TB Config Help =============\n");
	printf("cmd : Description\n");
	printf("npu_init : init npu and lif\n");
	printf("tb_clean : Flush npu config table\n");
	printf("tb_cfg [param] [value]: set config param, such as inport,outport,nat_mode,dnat_flag,vid,sip,sport,dip,dport,dmac,rip,rport,rsa,rda,pppoe_en,pppoe_hdr; value should use hex value\n");
	printf("tb_valid [is_overwrite]: valid config;is_overwrite[0:1] default is 1, 1 means overwrite default rule_index 0\n");
	printf("dump_mib : dump npu and lif mib\n");
	printf("============ End NPU TB Config Help =============\n");
	return CMD_RET_SUCCESS;
}

U_BOOT_CMD(
	npu_help,	1,	1,	do_npu_help,
	"help npu table config", "npuHelp"
);

extern void clear_se_tables(void);
static int do_clean(struct cmd_tbl *cmdtp, int flag, int argc,
		    char *const argv[])
{
	printf("do npu table clean\n");
	clear_se_tables();
	return CMD_RET_SUCCESS;
}

U_BOOT_CMD(
	tb_clean,	1,	1,	do_clean,
	"clean npu hw tables", "cleantable"
);

void dump_tb_config_info(void)
{
	printf("============ Dump NPU TB Config =============\n");
	printf("test port is [mac%ld] -> [mac%d]\n", g_oport, rsp.ovport);
	printf("test ip is sip:0x%x -> dip:0x%x\n", *(uint32_t *)key.sip, *(uint32_t *)key.dip);
	printf("test port is sport:0x%x -> dport:0x%x\n", key.sport, key.dport);
	printf("test replace ip is rip:0x%x rport:0x%x\n", *(uint32_t *)rsp.rip, rsp.rport);
	printf("test dmac is :0x%lx\n", *(unsigned long *)key.da);
	printf("test replace rsa is :0x%llx rda is :0x%llx\n", rsp.rsa, rsp.rda);
	printf("test pppoe_en:%d pppoe_hdr:0x%llx\n", rsp.pppoe_en, rsp.pppoe_hdr);
	printf("test dnat_flag:%ld vid:%ld\n", g_dnat_flag, g_vid);
	printf("============ End Dump NPU TB Config =============\n");
}

static int do_tb_cfg(struct cmd_tbl *cmdtp, int flag, int argc,
		    char *const argv[])
{
	int i = 0;

	if (argc < 3) {
		printf("Please input parameters, or use npu_help for help\n");
		return CMD_RET_FAILURE;
	}

	printf("config npu table parameters, argc:%d\n", argc);
	for (i = 1; i < argc; i+=2) {
		if (!strncmp(argv[i], "dnat_flag", 9)) {
			g_dnat_flag = simple_strtoul(argv[i+1], NULL, 16);
			continue;
		}

		if (!strncmp(argv[i], "nat_mode", 8)) {
			key.nat_mode = (unsigned char)simple_strtoul(argv[i+1], NULL, 16);
			continue;
		}

		if (!strncmp(argv[i], "inport", 6)) {
			g_oport = simple_strtoul(argv[i+1], NULL, 16);
			continue;
		}

		if (!strncmp(argv[i], "vid", 3)) {
			g_vid = simple_strtoul(argv[i+1], NULL, 16);
			continue;
		}

		if (!strncmp(argv[i], "outport", 7)) {
			rsp.ovport = simple_strtoul(argv[i+1], NULL, 16);
			continue;
		}

		if (!strncmp(argv[i], "sip", 3)) {
			*(uint32_t *)key.sip = (uint32_t)simple_strtoul(argv[i+1], NULL, 16);
			continue;
		}

		if (!strncmp(argv[i], "sport", 5)) {
			key.sport = (unsigned short)simple_strtoul(argv[i+1], NULL, 16);
			continue;
		}

		if (!strncmp(argv[i], "dip", 3)) {
			*(uint32_t *)key.dip = (uint32_t)simple_strtoul(argv[i+1], NULL, 16);
			continue;
		}

		if (!strncmp(argv[i], "dport", 5)) {
			key.dport = (unsigned short)simple_strtoul(argv[i+1], NULL, 16);
			continue;
		}

		if (!strncmp(argv[i], "dmac", 4)) {
			*(unsigned long *)key.da = simple_strtoul(argv[i+1], NULL, 16);
			continue;
		}

		if (!strncmp(argv[i], "rip", 3)) {
			*(uint32_t *)rsp.rip = simple_strtoul(argv[i+1], NULL, 16);
			continue;
		}

		if (!strncmp(argv[i], "rport", 5)) {
			rsp.rport = (unsigned short)simple_strtoul(argv[i+1], NULL, 16);
			continue;
		}

		if (!strncmp(argv[i], "rsa", 3)) {
			rsp.rsa = simple_strtoull(argv[i+1], NULL, 16);
			continue;
		}

		if (!strncmp(argv[i], "rda", 3)) {
			rsp.rda = simple_strtoull(argv[i+1], NULL, 16);
			continue;
		}

		if (!strncmp(argv[i], "pppoe_en", 8)) {
			rsp.pppoe_en = (unsigned char)simple_strtoul(argv[i+1], NULL, 16);
			continue;
		}

		if (!strncmp(argv[i], "pppoe_hdr", 9)) {
			*(unsigned long *)rsp.pppoe_hdr = simple_strtoul(argv[i+1], NULL, 16);
			continue;
		}
	}

	dump_tb_config_info();
	return CMD_RET_SUCCESS;
}

U_BOOT_CMD(
	tb_cfg,	20,	1,	do_tb_cfg,
	"config npu table", "tbCfg"
);

extern void nat_test(int rule_index, int oport, int vid, int dnat_flag, Sekey* key, Sersp* rsp);
static int do_tb_valid(struct cmd_tbl *cmdtp, int flag, int argc,
		    char *const argv[])
{
	unsigned long rule_index = 0, is_overwrite = 1;

	if (argc == 2) {
		is_overwrite = simple_strtoul(argv[1], NULL, 10);
		if (is_overwrite != 1) {
			g_rule_index += 2;
			rule_index = g_rule_index;
		}
	}

	if (is_overwrite == 1) {
		mac_table_index = 0;
		napt_index = 0;
	}
	printf("config table rule_index:%ld is_overwrite:%ld valid\n", rule_index, is_overwrite);
	nat_test(rule_index, g_oport, g_vid, g_dnat_flag, &key, &rsp);
	return CMD_RET_SUCCESS;
}

U_BOOT_CMD(
	tb_valid,	3,	1,	do_tb_valid,
	"truely config npu tables", "npuValid"
);

extern void dump_mib(void);
static int do_dump_mib(struct cmd_tbl *cmdtp, int flag, int argc,
		    char *const argv[])
{
	printf("dump lif and npu mib\n");
	dump_mib();
	return CMD_RET_SUCCESS;
}

U_BOOT_CMD(
	dump_mib,	1,	1,	do_dump_mib,
	"dump lif and npu mib", "dumpMib"
);


extern int do_npu_init(void);
static int do_init(struct cmd_tbl *cmdtp, int flag, int argc,
		    char *const argv[])
{
	printf("do npu and lif init\n");
	do_npu_init();
	return CMD_RET_SUCCESS;
}

U_BOOT_CMD(
	npu_init,	1,	1,	do_init,
	"init npu and lif", "npuInit"
);

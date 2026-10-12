// SPDX-License-Identifier: GPL-2.0

#include <common.h>
#include <cpu_func.h>
#include <fdtdec.h>
#include <init.h>
#include <asm/cache.h>
#include <asm/io.h>

DECLARE_GLOBAL_DATA_PTR;


int dram_init(void)
{
	return fdtdec_setup_mem_size_base();
}

int dram_init_banksize(void)
{
	return fdtdec_setup_memory_banksize();
}

// SPDX-License-Identifier: GPL-2.0

#include <common.h>
#include <cpu_func.h>
#include <dm.h>
#include <init.h>
#include <wdt.h>
#include <dm/uclass-internal.h>
#include <asm/io.h>

int arch_cpu_init(void)
{
	icache_enable();

	return 0;
}

void enable_caches(void)
{
	dcache_enable();
}

int timer_init(void)
{
	writel(0x0, 0x0ce09800);
	writel(-1, 0x0ce09804);
	writel(-1, 0x0ce09808);
	isb();
	writel(0x1, 0x0c6000c0);

	return 0;
}

// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2017 Andes Technology Corporation
 * Rick Chen, Andes Technology Corporation <rick@andestech.com>
 */

#include <common.h>
#include <cpu_func.h>
#include <dm.h>
#include <asm/cache.h>
#include <asm/csr.h>
#include <asm/io.h>
#include "custom_csr.h"

#define L1_CACHE_BYTES	64UL

#if defined(CONFIG_RISCV_SMODE) || !defined(CONFIG_SYS_ICACHE_OFF)
void invalidate_icache_range(unsigned long start, unsigned long end)
{
	unsigned long i = ALIGN_DOWN(start, L1_CACHE_BYTES);

	for (; i < end; i += L1_CACHE_BYTES)
		asm volatile ("icache.iva %0" :: "r" (i) : "memory");
}
#endif

#if defined(CONFIG_RISCV_SMODE) || !defined(CONFIG_SYS_DCACHE_OFF)
void flush_dcache_all(void)
{
	asm volatile ("dcache.ciall" ::: "memory");
	mb();
}

void flush_dcache_range(unsigned long start, unsigned long end)
{
	unsigned long i = ALIGN_DOWN(start, L1_CACHE_BYTES);

	for (; i < end; i += L1_CACHE_BYTES)
		asm volatile ("dcache.civa %0" :: "r" (i) : "memory");

	mb();
}

void invalidate_dcache_all(void)
{
	asm volatile ("dcache.iall" ::: "memory");
	mb();
}

void invalidate_dcache_range(unsigned long start, unsigned long end)
{
	unsigned long i = ALIGN_DOWN(start, L1_CACHE_BYTES);

	for (; i < end; i += L1_CACHE_BYTES)
		asm volatile ("dcache.iva %0" :: "r" (i) : "memory");

	mb();
}
#endif // DCACHE

#ifdef CONFIG_RISCV_MMODE
#ifndef CONFIG_SYS_ICACHE_OFF
void icache_enable(void)
{
	csr_set(CSR_MHCR, HCR_IE);
}

void icache_disable(void)
{
	csr_clear(CSR_MHCR, HCR_IE);
}
#endif // CONFIG_SYS_ICACHE_OFF

#ifndef CONFIG_SYS_DCACHE_OFF
void dcache_enable(void)
{
	csr_set(CSR_MHCR, HCR_DE);
}

void dcache_disable(void)
{
	csr_clear(CSR_MHCR, HCR_DE);
}
#endif // CONFIG_SYS_DCACHE_OFF
#endif // CONFIG_RISCV_MMODE

int icache_status(void)
{
	return !!(csr_read(CSR_SHCR) & HCR_IE);
}

int dcache_status(void)
{
	return !!(csr_read(CSR_SHCR) & HCR_DE);
}

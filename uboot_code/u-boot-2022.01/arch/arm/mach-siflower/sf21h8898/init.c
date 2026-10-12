// SPDX-License-Identifier: GPL-2.0

#include <common.h>
#include <fdtdec.h>
#include <init.h>
#include <asm/armv8/mmu.h>
#include <asm/cache.h>
#include <asm/io.h>

DECLARE_GLOBAL_DATA_PTR;

#define CLK_ADDR			(0x0CE0048C)
#ifdef CONFIG_SF21H8898_MPW0
#define CLK_CFG				(0x10067F)
#else
#define CLK_CFG				(0x80067f)
#endif
#define PLL_ADDR			(0x0CE00430)
#define PLL_CFG				BIT(31)
static struct bd_info bdata __attribute__ ((section(".data")));

int print_cpuinfo(void)
{
	printf("CPU:   Siflower sf21h8898\n");
	return 0;
}

int dram_init(void)
{
	if (!gd->bd)
		gd->bd = &bdata;

	gd->ram_base = 0x20000000;
	gd->ram_size = get_ram_size((void *)(size_t)0x20000000, 0x80000000);
	return 0;
}

void reset_cpu(void)
{
#ifndef CONFIG_SF21H8898_MPW0
	u32 reg;

	//add gic reset before reboot.
	reg = readl(0xce004c0);
	reg &= ~(1 << 1);
	writel(reg, 0xce004c0);
#endif
	writel(0x1, 0x0ce00014);
	while (1) asm volatile ("wfi");
}

void board_cleanup_before_linux(void)
{
	//According to SF21GH8898_Register_Map, Gating unnecessary Clk & Pll Before Linux.
#ifdef CONFIG_SF21H8898_MPW0
	unsigned int reg;
#endif

	writel(CLK_CFG, CLK_ADDR);
#ifdef CONFIG_SF21H8898_MPW0
	reg = (readl(PLL_ADDR) & ~PLL_CFG);
	writel(reg, PLL_ADDR);
#endif
}

static struct mm_region sf21h8898_mem_map[] = {
	{
		.virt = 0x00000000UL,
		.phys = 0x00000000UL,
		.size = 0x1c000000UL,
		.attrs = PTE_BLOCK_MEMTYPE(MT_DEVICE_NGNRNE) |
			 PTE_BLOCK_NON_SHARE |
			 PTE_BLOCK_PXN | PTE_BLOCK_UXN
	},
	{
		/* IROM IRAM */
		.virt = 0x1c000000UL,
		.phys = 0x1c000000UL,
		.size = 0x4000000UL,
		.attrs = PTE_BLOCK_MEMTYPE(MT_NORMAL_NC) | PTE_BLOCK_OUTER_SHARE,
	},
	{
		/* DDR */
		.virt = 0x20000000UL,
		.phys = 0x20000000UL,
		.size = 0x80000000UL,
		.attrs = PTE_BLOCK_MEMTYPE(MT_NORMAL) | PTE_BLOCK_OUTER_SHARE,
	},
	{
		0,
	}
};
struct mm_region *mem_map = sf21h8898_mem_map;

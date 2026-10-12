// SPDX-License-Identifier: GPL-2.0

#include <common.h>
#include <cpu_func.h>
#include <asm/csr.h>
#include <asm/encoding.h>
#include <asm/io.h>
#include <linux/bitfield.h>
#include "custom_csr.h"

#define PAGE_SHIFT	12
#define PAGE_SIZE	(1UL << (PAGE_SHIFT))

#define _PAGE_PRESENT   (1 << 0)
#define _PAGE_READ      (1 << 1)    /* Readable */
#define _PAGE_WRITE     (1 << 2)    /* Writable */
#define _PAGE_EXEC      (1 << 3)    /* Executable */
#define _PAGE_USER      (1 << 4)    /* User */
#define _PAGE_GLOBAL    (1 << 5)    /* Global */
#define _PAGE_ACCESSED  (1 << 6)    /* Set by hardware on any access */
#define _PAGE_DIRTY     (1 << 7)    /* Set by hardware on any write */
#define _PAGE_SOFT      (3 << 8)    /* Reserved for software */

#define _PAGE_SPECIAL   (1 << 8)    /* RSW: 0x1 */
#define _PAGE_TABLE     _PAGE_PRESENT

#define _PAGE_PFN_SHIFT 10

#define _PHYS_TO_PPN_SHIFT (PAGE_SHIFT - _PAGE_PFN_SHIFT)

/*
 * when all of R/W/X are zero, the PTE is a pointer to the next level
 * of the page table; otherwise, it is a leaf PTE.
 */
#define _PAGE_LEAF (_PAGE_READ | _PAGE_WRITE | _PAGE_EXEC)

/*
 * [62:61] Svpbmt Memory Type definitions:
 *
 *  00 - PMA    Normal Cacheable, No change to implied PMA memory type
 *  01 - NC     Non-cacheable, idempotent, weakly-ordered Main Memory
 *  10 - IO     Non-cacheable, non-idempotent, strongly-ordered I/O memory
 *  11 - Rsvd   Reserved for future standard use
 */
#define _PAGE_NOCACHE_SVPBMT	(1UL << 61)
#define _PAGE_IO_SVPBMT		(1UL << 62)
#define _PAGE_MTMASK_SVPBMT	(_PAGE_NOCACHE_SVPBMT | _PAGE_IO_SVPBMT)

/*
 * [63:59] T-Head Memory Type definitions:
 * bit[63] SO - Strong Order
 * bit[62] C - Cacheable
 * bit[61] B - Bufferable
 * bit[60] SH - Shareable
 * bit[59] Sec - Trustable
 * 00110 - NC   Weakly-ordered, Non-cacheable, Bufferable, Shareable, Non-trustable
 * 01110 - PMA  Weakly-ordered, Cacheable, Bufferable, Shareable, Non-trustable
 * 10010 - IO   Strongly-ordered, Non-cacheable, Non-bufferable, Shareable, Non-trustable
 */
#define _PAGE_PMA_THEAD		((1UL << 62) | (1UL << 61) | (1UL << 60))
#define _PAGE_NOCACHE_THEAD	((1UL << 61) | (1UL << 60))
#define _PAGE_IO_THEAD		((1UL << 63) | (1UL << 60))
#define _PAGE_MTMASK_THEAD	(_PAGE_PMA_THEAD | _PAGE_IO_THEAD | (1UL << 59))


#ifdef CONFIG_RISCV_MMODE
#define MXSTATUS_VAL	0x438000
void harts_early_init(void)
{
	csr_write(CSR_MSMPR, 0x1);
	// Don't enable cache yet, see cache.c
	csr_write(CSR_MHCR, 0x10011fc);
	csr_write(CSR_MHINT, 0x2baa10c);
	csr_write(CSR_MXSTATUS, MXSTATUS_VAL);
	csr_write(CSR_MCCR2, 0xa249000a);
	// Enable Svpbmt
	csr_set(CSR_MENVCFG, MENVCFG_PBMTE);
}
#endif // CONFIG_RISCV_MMODE

static void mmu_setup(void)
{
	static unsigned long pgds[PAGE_SIZE / sizeof(unsigned long)] __aligned(PAGE_SIZE);
	static unsigned long pmds0[PAGE_SIZE / sizeof(unsigned long)] __aligned(PAGE_SIZE);

	/* In M-mode we have the access to mxstatus register, so whether to use
	 * MAE depends on the value we programmed into it, see
	 * harts_early_init().
	 *
	 * In S-mode we only have the access to sxstatus register, which is a
	 * mostly read-only shadow of mxstatus, so we can only detect the MAE
	 * configuration.
	 */
#ifdef CONFIG_RISCV_MMODE
	const bool use_thead_mae = !!(MXSTATUS_VAL & MXSTATUS_MAEE);
#else
	const bool use_thead_mae = !!(csr_read(CSR_SXSTATUS) & MXSTATUS_MAEE);
#endif // CONFIG_RISCV_MMODE

#define PAGE_PMA	(use_thead_mae ? _PAGE_PMA_THEAD : 0)
#define PAGE_NOCACHE	(use_thead_mae ? _PAGE_NOCACHE_THEAD : _PAGE_NOCACHE_SVPBMT)
#define PAGE_IO		(use_thead_mae ? _PAGE_IO_THEAD : _PAGE_IO_SVPBMT)

#define PAGE_NON_LEAF	_PAGE_PRESENT
#define PAGE_LEAF_RAM	(PAGE_PMA | _PAGE_PRESENT | _PAGE_LEAF | _PAGE_GLOBAL | _PAGE_ACCESSED | _PAGE_DIRTY)
#define PAGE_LEAF_RAM_NC	(PAGE_NOCACHE | _PAGE_PRESENT | _PAGE_LEAF | _PAGE_GLOBAL | _PAGE_ACCESSED | _PAGE_DIRTY)
#define PAGE_LEAF_ROM	(PAGE_PMA | _PAGE_PRESENT | _PAGE_READ | _PAGE_EXEC | _PAGE_GLOBAL | _PAGE_ACCESSED)
#define PAGE_LEAF_IO	(PAGE_IO | _PAGE_PRESENT | _PAGE_READ | _PAGE_WRITE | _PAGE_GLOBAL | _PAGE_ACCESSED | _PAGE_DIRTY)
	unsigned long i;
	// Setup ID mapping
#ifdef CONFIG_SF23A2892
	// 0x00000000 ~ 0x40000000: delegate to the next level
	pgds[0] = PAGE_NON_LEAF | ((unsigned long)pmds0 >> _PHYS_TO_PPN_SHIFT);
	// 0x00000000 ~ 0x10000000: leaf 2M PTE: IO
	for (i = 0; i < 0x10000000 / SZ_2M; i++) {
		pmds0[i] = PAGE_LEAF_IO | ((0x0UL + i * SZ_2M) >> _PHYS_TO_PPN_SHIFT);
	}
	// 0x10000000 ~ 0x10200000: leaf 2M PTE: ROM
	i = 0x10000000 / SZ_2M;
	pmds0[i] = PAGE_LEAF_ROM | ((0x0UL + i * SZ_2M) >> _PHYS_TO_PPN_SHIFT);

	// 0x10200000 ~ 0x1f000000: reserved
	// 0x1f000000 ~ 0x1f200000: leaf 2M PTE: uncached MEM
	i = 0x1f000000 / SZ_2M;
	pmds0[i] = PAGE_LEAF_RAM_NC | ((0x0UL + i * SZ_2M) >> _PHYS_TO_PPN_SHIFT);

	// 0x1f200000 ~ 0x20000000: reserved
	// 0x20000000 ~ 0x40000000: leaf 2M PTE: MEM
	for (i = 0x20000000 / SZ_2M; i < 0x40000000 / SZ_2M; i++) {
		pmds0[i] = PAGE_LEAF_RAM | ((0x0UL + i * SZ_2M) >> _PHYS_TO_PPN_SHIFT);
	}

	// 0x40000000 ~ 0x80000000: leaf 1G PTE: MEM
	pgds[1] = PAGE_LEAF_RAM | (0x40000000UL >> _PHYS_TO_PPN_SHIFT);

	// 0x80000000 ~ 0xc0000000: leaf 1G PTE: IO
	pgds[2] = PAGE_LEAF_IO | (0x80000000UL >> _PHYS_TO_PPN_SHIFT);

	// 0xc0000000 ~ 0x100000000: leaf 1G PTE: IO
	pgds[3] = PAGE_LEAF_IO | (0xc0000000UL >> _PHYS_TO_PPN_SHIFT);
#else // CONFIG_SF23A2892
	static unsigned long pmds2[PAGE_SIZE / sizeof(unsigned long)] __aligned(PAGE_SIZE);

	// 0x00000000 ~ 0x40000000: delegate to the next level
	pgds[0] = PAGE_NON_LEAF | ((unsigned long)pmds0 >> _PHYS_TO_PPN_SHIFT);
	// 0x00000000 ~ 0x00200000: unmapped, to catch null pointer
	// 0x00200000 ~ 0x1c000000: leaf 2M PTE: IO
	for (i = 1; i < 0x1c000000 / SZ_2M; i++) {
		pmds0[i] = PAGE_LEAF_IO | ((0x0UL + i * SZ_2M) >> _PHYS_TO_PPN_SHIFT);
	}
	// 0x1c000000 ~ 0x1c200000: leaf 2M PTE: uncached MEM
	i = 0x1c000000 / SZ_2M;
	pmds0[i] = PAGE_LEAF_RAM_NC | ((0x0UL + i * SZ_2M) >> _PHYS_TO_PPN_SHIFT);

	// 0x1c200000 ~ 0x1f000000: reserved
	// 0x1f000000 ~ 0x1f200000: leaf 2M PTE: ROM
	i = 0x1f000000 / SZ_2M;
	pmds0[i] = PAGE_LEAF_ROM | ((0x0UL + i * SZ_2M) >> _PHYS_TO_PPN_SHIFT);
	// 0x1f200000 ~ 0x20000000: reserved
	// 0x20000000 ~ 0x40000000: leaf 2M PTE: MEM
	for (i = 0x20000000 / SZ_2M; i < 0x40000000 / SZ_2M; i++) {
		pmds0[i] = PAGE_LEAF_RAM | ((0x0UL + i * SZ_2M) >> _PHYS_TO_PPN_SHIFT);
	}

	// 0x40000000 ~ 0x80000000: leaf 1G PTE: MEM
	pgds[1] = PAGE_LEAF_RAM | (0x40000000UL >> _PHYS_TO_PPN_SHIFT);

	// 0x80000000 ~ 0xc0000000: delegate to the next level
	pgds[2] = PAGE_NON_LEAF | ((unsigned long)pmds2 >> _PHYS_TO_PPN_SHIFT);
	// 0x80000000 ~ 0xa0000000: leaf 2M PTE: MEM
	for (i = 0; i < (0xa0000000 - 0x80000000) / SZ_2M; i++) {
		pmds2[i] = PAGE_LEAF_RAM | ((0x80000000UL + i * SZ_2M) >> _PHYS_TO_PPN_SHIFT);
	}
	// 0xa0000000 ~ 0xc0000000: leaf 2M PTE: IO
	for (i = (0xa0000000 - 0x80000000) / SZ_2M; i < (0xc0000000 - 0x80000000) / SZ_2M; i++) {
		pmds2[i] = PAGE_LEAF_IO | ((0x80000000UL + i * SZ_2M) >> _PHYS_TO_PPN_SHIFT);
	}

	// 0xc0000000 ~ 0x100000000: leaf 1G PTE: IO
	pgds[3] = PAGE_LEAF_IO | (0xc0000000UL >> _PHYS_TO_PPN_SHIFT);
	// 0x100000000 ~ 0x140000000: leaf 1G PTE: IO
	pgds[4] = PAGE_LEAF_IO | (0x100000000UL >> _PHYS_TO_PPN_SHIFT);
#endif // CONFIG_SF23A2892

	if (CONFIG_IS_ENABLED(RISCV_MMODE)) {
		// Setup PMP, allow all
		csr_write(CSR_PMPADDR0, ~0UL);
		csr_write(CSR_PMPCFG0, 0x0f);
		// set mstatis.mprv and mstatus.mpp to 1, so M mode loads and stores will go through MMU
		unsigned long mstatus = csr_read(CSR_MSTATUS);
		mstatus &= ~MSTATUS_MPP;
		mstatus |= FIELD_PREP(MSTATUS_MPP, PRV_S) | MSTATUS_MPRV;
		csr_write(CSR_MSTATUS, mstatus);
	}
	// sv39
	asm volatile ("sfence.vma" ::: "memory");
	csr_write(CSR_SATP, (8UL << 60) | ((unsigned long)pgds >> PAGE_SHIFT));
}

void enable_caches(void)
{
	// called after relocation
	mmu_setup();
}

void reset_cpu(void)
{
#ifdef CONFIG_SF23A2892
	writel(0x1, 0x04e00014);
#else
	writel(0x1, 0x0ce00014);
#endif
	while (1) asm volatile ("wfi");
}

#ifdef CONFIG_SF23A2892
#define CLK_ADDR			(0x04E0048C)
#define CLK_CFG				(0x87F)
#else
#define CLK_ADDR			(0x0CE0048C)
#define CLK_CFG				(0x80067F)
#define PLL_PCIE_CFG1			(0x0CE0044C)
#define PLL_PCIE_CFG2			(0x0CE00450)
#define LOAD				(0x0CE00500)
#endif

int print_cpuinfo(void)
{
#ifdef CONFIG_SF23A2892
	printf("CPU:   Siflower sf23a2892\n");
#else
	printf("CPU:   Siflower sf21h8898\n");
#endif
	return 0;
}

static void disable_pcie_pll(void)
{
	u32 reg;
	reg = readl(PLL_PCIE_CFG1);
	reg &= ~(1 << 31);
	writel(reg, PLL_PCIE_CFG1);

	reg = readl(PLL_PCIE_CFG2);
	reg &= ~(0xf << 27);
	writel(reg, PLL_PCIE_CFG2);

	writel((1 << 4), LOAD);
	writel(0, LOAD);
}

int cleanup_before_linux(void)
{
	disable_pcie_pll();

	writel(CLK_CFG, CLK_ADDR);

	if (CONFIG_IS_ENABLED(RISCV_MMODE))
		csr_clear(CSR_MSTATUS, MSTATUS_MPRV);

	csr_write(CSR_SATP, 0);
	asm volatile ("sfence.vma" ::: "memory");
	return 0;
}

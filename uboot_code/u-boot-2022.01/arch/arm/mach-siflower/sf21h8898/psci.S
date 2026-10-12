/* SF21H8898 PSCI simple implementation
 * (C) 2022 qingfang.deng@siflower.com.cn
 */

#include <config.h>
#include <linux/linkage.h>
#include <asm/gic.h>
#include <asm/macro.h>
#include <asm/psci.h>
#include <asm/secure.h>

.pushsection ._secure.text, "ax"

kernel_load_addr:
	.quad	0
	.quad	0
	.quad	0
	.quad	0

kernel_context_id:
	.quad	0
	.quad	0
	.quad	0
	.quad	0

cpu_mask:
	.word	1

ENTRY(psci_cpu_entry)
	bl	psci_setup_vectors
	mrs	x0, scr_el3
	orr	x0, x0, #0xf			/* SCR_EL3.NS|IRQ|FIQ|EA */
	msr	scr_el3, x0
	msr	cptr_el3, xzr			/* Enable FP/SIMD */

	mrs	x10, mpidr_el1
	and	x29, x10, #3
#ifdef CONFIG_GICV3
	// Initialize ReDistributor
	lsr	x9, x10, #32
	bfi	x10, x9, #24, #8	/* w10 is aff3:aff2:aff1:aff0 */
	mov	x9, #GICR_BASE
1:	ldr	x11, [x9, GICR_TYPER]
	lsr	x11, x11, #32		/* w11 is aff3:aff2:aff1:aff0 */
	cmp	w10, w11
	b.eq	2f
	add	x9, x9, #(2 << 16)
	b	1b

	/* x9: ReDistributor Base Address of Current CPU */
2:	mov	w10, #~0x2
	ldr	w11, [x9, GICR_WAKER]
	and	w11, w11, w10		/* Clear ProcessorSleep */
	str	w11, [x9, GICR_WAKER]
	dsb	st
	isb
3:	ldr	w10, [x9, GICR_WAKER]
	tbnz	w10, #2, 3b		/* Wait Children be Alive */

	add	x10, x9, #(1 << 16)	/* SGI_Base */
	mov	w11, #~0
	str	w11, [x10, GICR_IGROUPRn]
	str	wzr, [x10, GICR_IGROUPMODRn]	/* SGIs|PPIs Group1NS */
	mov	w11, #0x1		/* Enable SGI 0 */
	str	w11, [x10, GICR_ISENABLERn]

	/* Initialize Cpu Interface */
	mrs	x10, ICC_SRE_EL3
	orr	x10, x10, #0xf		/* SRE & Disable IRQ/FIQ Bypass & */
					/* Allow EL2 access to ICC_SRE_EL2 */
	msr	ICC_SRE_EL3, x10
	isb

	mov	x10, #0x3		/* EnableGrp1NS | EnableGrp1S */
	msr	ICC_IGRPEN1_EL3, x10
	isb

	msr	ICC_CTLR_EL3, xzr
	isb

	mrs	x10, ICC_SRE_EL2
	orr	x10, x10, #0xf		/* SRE & Disable IRQ/FIQ Bypass & */
					/* Allow EL1 access to ICC_SRE_EL1 */
	msr	ICC_SRE_EL2, x10
	isb

	msr	ICC_CTLR_EL1, xzr	/* NonSecure ICC_CTLR_EL1 */
	isb

	mov	x10, #0x1 << 7		/* Non-Secure access to ICC_PMR_EL1 */
	msr	ICC_PMR_EL1, x10
	isb
#endif
#ifdef COUNTER_FREQUENCY
	ldr	x0, =COUNTER_FREQUENCY
	msr	cntfrq_el0, x0			/* Initialize CNTFRQ */
	isb
#endif
	/*
	 * Enable SMPEN bit for coherency.
	 * This register is not architectural but at the moment
	 * this bit should be set for A53/A57/A72.
	 */
#ifdef CONFIG_ARMV8_SET_SMPEN
	mrs     x0, S3_1_c15_c2_1               /* cpuectlr_el1 */
	orr     x0, x0, #0x40
	msr     S3_1_c15_c2_1, x0
	isb
#endif
#ifdef CONFIG_ARM_ERRATA_855873
	mrs	x0, midr_el1
	tst	x0, #(0xf << 20)
	b.ne	0f

	mrs	x0, midr_el1
	and	x0, x0, #0xf
	cmp	x0, #3
	b.lt	0f

	mrs	x0, S3_1_c15_c2_0	/* cpuactlr_el1 */
	/* Enable data cache clean as data cache clean/invalidate */
	orr	x0, x0, #1 << 44
	msr	S3_1_c15_c2_0, x0	/* cpuactlr_el1 */
	isb
#endif
0:
	adr	x4, kernel_load_addr
	ldr	x4, [x4, x29, lsl 3]
	adr	x0, kernel_context_id
	ldr	x0, [x0, x29, lsl 3]
	mov	x1, #0
	mov	x2, #0
	mov	x3, #0
	mov	x5, #ES_TO_AARCH64
	dsb	sy
	armv8_switch_to_el2_m	x4, x5, x6
ENDPROC(psci_cpu_entry)

ENTRY(psci_get_cpu_id)
	// get current cpu id, we should only have core 0~3
	mrs	x0, mpidr_el1
	and	x0, x0, #3
	ret
ENDPROC(psci_get_cpu_id)

ENTRY(psci_version)
	mov	w0, #ARM_PSCI_VER_0_2
	ret
ENDPROC(psci_version)

ENTRY(psci_cpu_off)
	mrs	x10, clidr_el1		/* read clidr_el1 */
	ubfx	x11, x10, #24, #3	/* x11 <- loc */
	cbz	x11, finished		/* if loc is 0, exit */
	mov	x0, #0			/* start flush at cache level 0 */
	/* x0  <- cache level */
	/* x10 <- clidr_el1 */
	/* x11 <- loc */

loop_level:
	add	x12, x0, x0, lsl #1	/* x12 <- tripled cache level */
	lsr	x12, x10, x12
	and	x12, x12, #7		/* x12 <- cache type */
	cmp	x12, #2
	b.lt	skip			/* skip if no cache or icache */
	lsl	x12, x0, #1
	msr	csselr_el1, x12		/* select cache level */
	isb				/* sync change of cssidr_el1 */
	mrs	x6, ccsidr_el1		/* read the new cssidr_el1 */
	ubfx	x2, x6,  #0,  #3	/* x2 <- log2(cache line size)-4 */
	ubfx	x3, x6,  #3, #10	/* x3 <- number of cache ways - 1 */
	ubfx	x4, x6, #13, #15	/* x4 <- number of cache sets - 1 */
	add	x2, x2, #4		/* x2 <- log2(cache line size) */
	clz	w5, w3			/* bit position of #ways */
	/* x12 <- cache level << 1 */
	/* x2 <- line length offset */
	/* x3 <- number of cache ways - 1 */
	/* x4 <- number of cache sets - 1 */
	/* x5 <- bit position of #ways */

loop_set:
	mov	x6, x3			/* x6 <- working copy of #ways */
loop_way:
	lsl	x7, x6, x5
	orr	x9, x12, x7		/* map way and level to cisw value */
	lsl	x7, x4, x2
	orr	x9, x9, x7		/* map set number to cisw value */
	dc	cisw, x9		/* clean & invalidate by set/way */
	subs	x6, x6, #1		/* decrement the way */
	b.ge	loop_way
	subs	x4, x4, #1		/* decrement the set */
	b.ge	loop_set
skip:
	add	x0, x0, #1		/* increment cache level */
	cmp	x11, x0
	b.gt	loop_level

	mov	x0, #0
	msr	csselr_el1, x0		/* restore csselr_el1 */
	dsb	sy
	isb

finished:
#ifdef CONFIG_ARMV8_SET_SMPEN
	mrs	x0, S3_1_c15_c2_1               /* cpuectlr_el1 */
	bic	x0, x0, #0x40
	msr	S3_1_c15_c2_1, x0
	isb
#endif
	bl	psci_get_cpu_id
	mov	w10, #1
	lsl	w9, w10, w0
	adr	x11, cpu_mask
	ldr	w10, [x11]
	bic	w10, w10, w9
	str	w10, [x11]
	b	wfi_loop
ENDPROC(psci_cpu_off)

ENTRY(psci_cpu_on)
ENTRY(psci_cpu_on_64)
	// x1: target cpu, x2: entry point address, x3: context id
	tst	x1, #~0x3
	b.ne	invalid
	adr	x9, kernel_load_addr
	str	x2, [x9, x1, lsl 3]
	adr	x9, kernel_context_id
	str	x3, [x9, x1, lsl 3]
	dsb	sy
	adr	x9, psci_cpu_entry
	lsr	x9, x9, #2
	mov	x10, #0x0c08
	movk	x10, #0x0ce0, lsl 16
	add	x11, x10, #8
	cmp	x1, #0
	csel	x10, x10, x11, eq
	// unlock rvbar addr regs
	lsl	w4, w1, #3
	mov	w5, #0xff
	lsl	w5, w5, w1
	mov	w6, #0xaa
	add	w6, w6, w1
	lsl	w6, w6, w4
	mov	x7, #0x0ce00000
	str	w5, [x7, #0x0c40]
	dmb	st
	str	w6, [x7, #0x0c38]
	str	x9, [x10, x1, lsl 3]
	dsb	sy
	// set cpu mask bit
	mov	w10, #1
	lsl	w9, w10, w1
	adr	x11, cpu_mask
	ldr	w10, [x11]
	orr	w10, w10, w9
	str	w10, [x11]
	// convert to rsten bit
	lsl	w9, w9, #13
	// topcrm rsten_cfg register
	mov	x10, #0x04c0
	movk	x10, #0x0ce0, lsl 16
	ldar	w11, [x10]
	tst	w11, w9
	b.ne	already_on
	orr	w11, w11, w9
	stlr	w11, [x10]
	mov	w0, #ARM_PSCI_RET_SUCCESS
	ret
invalid:
	mov	w0, #ARM_PSCI_RET_INVAL
	ret
already_on:
	mov	w0, #ARM_PSCI_RET_ALREADY_ON
	ret
ENDPROC(psci_cpu_on)
ENDPROC(psci_cpu_on_64)

ENTRY(psci_affinity_info)
ENTRY(psci_affinity_info_64)
	// x1: mpidr, x2: lowest affinity level
	cbnz	x2, cluster
	ldr	w10, cpu_mask
	and	w1, w1, #3
	mov	w9, #1
	lsl	w9, w9, w1
	tst	w10, w9
	b.eq	delayed_cpu_off
	mov	w0, #PSCI_AFFINITY_LEVEL_ON
	ret
delayed_cpu_off:
	mov	x11, #0x04c0
	movk	x11, #0x0ce0, lsl 16
	ldar	w12, [x11]
	lsl	w9, w9, #13
	bic	w12, w12, w9
	stlr	w12, [x11]
	mov	w0, #PSCI_AFFINITY_LEVEL_OFF
	ret
cluster:
	// everything else should be 0
	tst	x1, #~0x3
	b.ne	invalid
	mov	w0, #PSCI_AFFINITY_LEVEL_ON
	ret
ENDPROC(psci_affinity_info)
ENDPROC(psci_affinity_info_64)

ENTRY(psci_migrate_info_type)
	// migrate not required
	mov	w0, #2
	ret
ENDPROC(psci_migrate_info_type)

ENTRY(psci_system_off)
	// disable wdt
	mov	x9, #0x9c00
	movk	x9, #0x0ce0, lsl 16
	mov	w10, #-1
	str	w10, [x9]
	dsb	sy
	// assert reset on everything
	mov	x9, #0x0ce00000
	str	wzr, [x9, #0x04c0]
	// should never get here
	b	wfi_loop
ENDPROC(psci_system_off)

ENTRY(psci_system_reset)
	cmp	w1, #0
	csinc	w1, w1, wzr, ne
	mov	x10, #0x0ce00000
	ldr	w11, [x10, #0x04c0]
	bic	w11, w11, #(1 << 1)
	str	w11, [x10, #0x04c0]
	dsb	sy
	str	w1, [x10, #0x14]
	// should never get here
wfi_loop:
	dsb	sy
0:
	wfi
	b	0b
ENDPROC(psci_system_reset)

.popsection

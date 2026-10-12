#ifndef _SIFLOWER_CUSTOM_CSR_H
#define _SIFLOWER_CUSTOM_CSR_H

#define CSR_MENVCFG	0x30a
#define MENVCFG_PBMTE	(1UL << 62)
#define CSR_PMPCFG0	0x3a0
#define CSR_PMPADDR0	0x3b0
#define CSR_SXSTATUS	0x5c0
#define CSR_MXSTATUS	0x7c0
#define MXSTATUS_MAEE	(1UL << 21)
#define CSR_MHCR	0x7c1
#define CSR_MHINT	0x7c5
#define CSR_MCCR2	0x7c3
#define CSR_MSMPR	0x7f3
#define CSR_SHCR	0x5c1
#define HCR_IE		(1UL << 0)
#define HCR_DE		(1UL << 1)

#endif

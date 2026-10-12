/* SPDX-License-Identifier: GPL-2.0 */

#ifndef __SF23A2892_H
#define __SF23A2892_H

#include <linux/sizes.h>

#define CONFIG_PL011_CLOCK		100000000
#define CONFIG_PL01x_PORTS		{ (void *) 0x04300000, (void *) 0x04301000 }

#define CONFIG_SYS_MAXARGS		8
#define CONFIG_SYS_BOOTM_LEN		SZ_32M
#define CONFIG_SYS_CBSIZE		SZ_1K
#define CONFIG_SYS_PBSIZE		(CONFIG_SYS_CBSIZE +	\
					sizeof(CONFIG_SYS_PROMPT) + 16)

/* Uboot definition */
#define CONFIG_SYS_UBOOT_BASE	CONFIG_SYS_TEXT_BASE
/* SPL -> Uboot */
#define CONFIG_SYS_UBOOT_START	CONFIG_SYS_TEXT_BASE
#define CONFIG_SYS_INIT_SP_ADDR	(CONFIG_SYS_TEXT_BASE + SZ_2M - \
		GENERATED_GBL_DATA_SIZE)
/* DRAM */
#define CONFIG_SYS_SDRAM_BASE	0x20000000
#define CONFIG_REMAKE_ELF


#define WEBFAILSAFE_UPLOAD_RAM_ADDRESS                  0x21000000
/* U-Boot partition size and offset*/

/*cause we use spl + uboot for upgrade, so that upgrade uboot from spl*/
#define WEBFAILSAFE_UPLOAD_UBOOT_ADDRESS                0

#define WEBFAILSAFE_UPLOAD_UBOOT_SIZE_IN_BYTES          ( 128 * 1024 * 5 )
/*Firmware partition offset */
#ifdef CONFIG_MTD_SPI_NAND
#define WEBFAILSAFE_UPLOAD_KERNEL_ADDRESS               0xa0000 //CFG_KERN_ADDR
#else
#ifndef CONFIG_SFA18_UBOOT_LITE
#define WEBFAILSAFE_UPLOAD_KERNEL_ADDRESS               0xa0000 //CFG_KERN_ADDR
#else
#define WEBFAILSAFE_UPLOAD_KERNEL_ADDRESS               0x32000 //CFG_KERN_ADDR
#endif
#endif

#ifdef CONFIG_MTD_SPI_NAND
#define WEBFAILSAFE_FACTORY_ADDRESS						(0xa0000 - 0x20000)
#else
#ifndef CONFIG_SFA18_UBOOT_LITE
#define WEBFAILSAFE_FACTORY_ADDRESS						(0xa0000 - 0x10000)
#else
#define WEBFAILSAFE_FACTORY_ADDRESS						(0x32000 - 0x1000)
#endif
#endif

#ifndef CONFIG_SFA18_UBOOT_LITE
/*ART partition size and offset*/
#define WEBFAILSAFE_UPLOAD_ART_ADDRESS                  0//CFG_FACTORY_ADDR
#define WEBFAILSAFE_UPLOAD_ART_SIZE_IN_BYTES            ( 16 * 1024 * 1024 )
#endif
/*max. firmware size <= (FLASH_SIZE -  WEBFAILSAFE_UPLOAD_LIMITED_AREA_IN_BYTES)*/
/*progress state info*/
#define WEBFAILSAFE_PROGRESS_START                      0
#define WEBFAILSAFE_PROGRESS_TIMEOUT                    1
#define WEBFAILSAFE_PROGRESS_UPLOAD_READY               2
#define WEBFAILSAFE_PROGRESS_UPGRADE_READY              3
#define WEBFAILSAFE_PROGRESS_UPGRADE_FAILED             4
/*update type*/
#define WEBFAILSAFE_UPGRADE_TYPE_FIRMWARE               0
#define WEBFAILSAFE_UPGRADE_TYPE_UBOOT                  1
#ifndef CONFIG_SFA18_UBOOT_LITE
#define WEBFAILSAFE_UPGRADE_TYPE_ART                    2
#endif
#define WEBFAILSAFE_UPGRADE_TYPE_TEST                   3

#endif

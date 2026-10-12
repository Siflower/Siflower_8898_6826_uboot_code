// SPDX-License-Identifier: GPL-2.0

#include <common.h>
#include <config.h>
#include <env.h>
#include <led.h>
#include <init.h>
#include <asm/global_data.h>
#include <asm/sections.h>

DECLARE_GLOBAL_DATA_PTR;

void *board_fdt_blob_setup(int *err)
{
	*err = 0;
	if (IS_ENABLED(CONFIG_OF_SEPARATE) || IS_ENABLED(CONFIG_OF_BOARD)) {
		if (gd->arch.firmware_fdt_addr)
			return (ulong *)(uintptr_t)gd->arch.firmware_fdt_addr;
	}

	return (ulong *)&_end;
}

int board_init(void)
{
	if (IS_ENABLED(CONFIG_LED))
		led_default_state();
	return 0;
}

int board_late_init(void)
{
	return 0;
}

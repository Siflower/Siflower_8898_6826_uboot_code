#include <asm/system.h>
#include <fdtdec.h>

int psci_update_dt(void *fdt)
{
#ifdef CONFIG_ARMV8_SECURE_BASE
	int offset = -1;

	while ((offset = fdt_node_offset_by_compatible(fdt, offset, "mmio-sram")) >= 0) {
		fdt_addr_t addr;
		int suboff, rc;

		addr = fdtdec_get_addr_size_auto_noparent(fdt, offset, "reg",
							  0, NULL, false);
		if (addr != CONFIG_ARMV8_SECURE_BASE)
			continue;

		suboff = fdt_add_subnode(fdt, offset, "psci-sram@0");
		if (suboff < 0)
			break;

		rc = fdt_appendprop_addrrange(fdt, offset, suboff, "reg", 0,
					      (uintptr_t)__secure_stack_end - (uintptr_t)__secure_stack_start +
					      (uintptr_t)__secure_end - (uintptr_t)__secure_start);
		if (rc)
			fdt_del_node(fdt, suboff);

		break;
	}

	return 0;
#else
	static const struct fdt_memory psci_ram = {
		.start = (uintptr_t)__secure_start,
		.end = (uintptr_t)__secure_stack_end - 1,
	};

	return fdtdec_add_reserved_memory(fdt, "psci-ram", &psci_ram, NULL, 0, NULL,
					  FDTDEC_RESERVED_MEMORY_NO_MAP);
#endif
}

# SPDX-License-Identifier: GPL-2.0+

dtb-$(CONFIG_TARGET_AX25_AE350) += ae350_32.dtb ae350_64.dtb
dtb-$(CONFIG_TARGET_MICROCHIP_ICICLE) += microchip-mpfs-icicle-kit.dtb
dtb-$(CONFIG_TARGET_QEMU_VIRT) += qemu-virt.dtb
dtb-$(CONFIG_TARGET_OPENPITON_RISCV64) += openpiton-riscv64.dtb
dtb-$(CONFIG_TARGET_SIFIVE_UNLEASHED) += hifive-unleashed-a00.dtb
dtb-$(CONFIG_TARGET_SIFIVE_UNMATCHED) += hifive-unmatched-a00.dtb
dtb-$(CONFIG_TARGET_SIPEED_MAIX) += k210-maix-bit.dtb
dtb-$(CONFIG_TARGET_SF21A6826) += sf21a6826_fullmask_6826sg.dtb \
	sf21a6826_fullmask_6826sg_nand.dtb \
	sf21h8898_bpi-rv2-nand.dtb \
	sf21h8898_bpi-rv2-nor.dtb \
	sf21h8898_siflower_one-nand.dtb \
	sf21h8898_siflower_one-nor.dtb

targets += $(dtb-y)

DTC_FLAGS += -R 4 -p 0x1000

PHONY += dtbs
dtbs: $(addprefix $(obj)/, $(dtb-y))
	@:

clean-files := *.dtb

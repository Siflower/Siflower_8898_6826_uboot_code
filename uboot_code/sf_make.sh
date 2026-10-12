#!/bin/bash
set -e
SCRIPT_DIR="$(dirname $(readlink -f "$0"))"
TOOLS_DIR=$SCRIPT_DIR/tools
TOOLCHAIN_DIR=$SCRIPT_DIR/toolchain/Xuantie-900-gcc-linux-6.6.0-musl64-x86_64-V3.0.2
TOOLCHAIN=$TOOLCHAIN_DIR/bin/riscv64-unknown-linux-musl-
BIN_DIR=$SCRIPT_DIR/bin
OPENSBI_FW=$BIN_DIR/fw_dynamic.bin
DDR_BIN=
FBL_BIN=
#toolchain=/opt/arm_toolchain/gcc-arm-10.3-2021.07-x86_64-aarch64-none-elf/bin/aarch64-none-elf-
#toolchain=/home/mark.cai/8898/usb_device/Xuantie-900-gcc-linux-5.10.4-musl64-x86_64-V2.8.0/bin/riscv64-unknown-linux-musl-
###########################################################################
# defuale configs.
###########################################################################
cmd="dmake"
chip="sf21h8898"
ver="mpw0"
board="evb"
UBOOT=./u-boot-2022.01
nand="0"
ddr="ddr3"
ddr_size="4096"
compress="false"
uboot_mode="m"

show_help() {
	echo "Usage: $0"
	echo "    chip=sf21h8898"
	echo "    ver=mpw0|mpw1|fullmask"
	echo "    board=fpga|evb"
	echo "    [cmd=dmake|distclean|clean|make]"
	echo "    [nand=0|1]"
#echo "For sf21h8898 mpw0 fpga, use ./sf_make.sh chip=sf21h8898 ver=mpw0 board=fpga or ./make.sh chip##_##board ver e.g. ./make.sh sf21h8898_mpw0_evb"
	exit 0
}

for args in $@
do
	case $args in
		chip=*)
			chip=${args##*chip=}
			;;
		ver=*)
			ver=${args##*ver=}
			;;
		board=*)
			board=${args##*board=}
			;;
		cmd=*)
			cmd=${args##*cmd=}
			;;
		nand=*)
			nand=${args##*nand=}
			;;
		*)
			show_help
			exit 1
			;;
	esac
done

# Choose prefix of defconfig
case ${chip}_${ver}_${board} in
	sf21a6826_fullmask_6826sg)
		ddr_size="2048"
		ddr="ddr3"
		DEFCONFIG="${chip}_${ver}_${board}"
		;;
	sf21a6826_fullmask_6826sg_6.6)
		ddr_size="2048"
		ddr="ddr3"
		DEFCONFIG="${chip}_${ver}_${board}"
		;;
	sf21a6826_fullmask_6826sg_nand)
		# 6826sg use nand flash
		ddr_size="2048"
		ddr="ddr3"
		DEFCONFIG="${chip}_${ver}_${board}"
		nand=1
		;;
	sf21a6826_fullmask_6826sg_nand_6.6)
		# 6826sg use nand flash
		ddr_size="2048"
		ddr="ddr3"
		DEFCONFIG="${chip}_${ver}_${board}"
		nand=1
		;;
	sf21h8898_fullmask_bpi-rv2-nand)
		ddr_size="4096"
		ddr="ddr3"
		DEFCONFIG="${chip}_${board}"
		nand=1
		;;
	sf21h8898_fullmask_bpi-rv2-nor)
		DEFCONFIG="${chip}_${board}"
		ddr_size="4096"
		ddr="ddr3"
		compress=true
		;;
	sf21h8898_fullmask_siflower-one-nand)
		ddr_size="4096"
		ddr="ddr3"
		DEFCONFIG="${chip}_${board}"
		nand=1
		;;
	sf21h8898_fullmask_siflower-one-nor)
		ddr_size="4096"
		ddr="ddr3"
		DEFCONFIG="${chip}_${board}"
		compress=true
		;;
	*)
		echo "unsupport board ${chip}_${board}"
		show_help
		exit 1
		;;
esac

DEFCONFIG=${DEFCONFIG}_defconfig

export PATH=$TOOLS_DIR:$PATH

case $cmd in
	distclean | clean)
		echo "siflower make $cmd starting...."
		make -C $UBOOT $cmd
		rm -rf output
		rm -f u-boot.bin u-boot.img
		exit 0
		;;
	make)
		need_clean=0
		;;
	*)
		need_clean=1
		;;
esac

make -C $UBOOT CROSS_COMPILE=$TOOLCHAIN $DEFCONFIG
grep -q CONFIG_RISCV_SMODE=y $UBOOT/.config && uboot_mode=s

[ "$compress" == "true" ] && {
	sed -i '/CONFIG_SIFLOWER_UBOOT_COMPRESSED/c\CONFIG_SIFLOWER_UBOOT_COMPRESSED=y' $UBOOT/.config
}

if [ $need_clean -ne 0 ] ; then
	echo "siflower distclean then make uboot starting...."
	make -C $UBOOT clean
	rm -f u-boot.bin u-boot.img
else
	echo "siflower make uboot starting...."
fi

if [ "$nand" == "1" ] ; then
	DDR_BIN=$BIN_DIR/sf21_${ddr}_${ddr_size}_nand.bin
	FBL_BIN=$BIN_DIR/sf21h8898_nand.bin
else
	DDR_BIN=$BIN_DIR/sf21_${ddr}_${ddr_size}_nor.bin
	FBL_BIN=$BIN_DIR/sf21h8898_nor.bin
fi

echo "chip=$chip"
echo "ver=$ver"
echo "board=$board"
echo "cmd=$cmd"
echo "DEFCONFIG=$DEFCONFIG"
echo "toolchain=$TOOLCHAIN"

# compile uboot
if [ $uboot_mode == "s" ] ;then
	make -C $UBOOT CROSS_COMPILE=$TOOLCHAIN -j OPENSBI=$OPENSBI_FW || exit 1
else
	make -C $UBOOT CROSS_COMPILE=$TOOLCHAIN -j || exit 1
fi

rm -rf output
mkdir output

# package ddr + fbl
cp $FBL_BIN output/fbl.bin.tmp
dd if=output/fbl.bin.tmp of=output/fbl.bin bs=48k conv=sync

cp $DDR_BIN output/ddr.bin
openssl dgst -sha256 -binary output/fbl.bin >> output/ddr.bin

$TOOLS_DIR/checksum output/ddr.bin output/ddr.img
dd if=output/ddr.img of=output/sf_fbl.img bs=49k conv=sync
cat output/fbl.bin >> output/sf_fbl.img

if [ "$nand" == "1" ] ;then
	mv output/sf_fbl.img output/sf_fbl.img.tmp
	dd if=output/sf_fbl.img.tmp of=output/sf_fbl.img bs=2k conv=sync
	rm output/sf_fbl.img.tmp
	cp $UBOOT/u-boot.itb ./output/
	printf '00 10 16 88 %02X %02X %02X' $[RANDOM%256] $[RANDOM%256] $[RANDOM&252] | xxd -r > ./output/random_mac.bin
	ubinize -E 1 -o ./output/u-boot.ubi -p 131072 -m 2048 -e 126976 -O 2048 u-boot-ubi.ini
	dd if=./output/sf_fbl.img of=output/uboot_full.img bs=128k conv=sync
	cat ./output/u-boot.ubi >> ./output/uboot_full.img
	exit
else
	cat ./output/sf_fbl.img $UBOOT/u-boot.itb > ./output/uboot_full.img
fi

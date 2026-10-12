#!/bin/sh
FW_IN=$1

nand_get_magic_long() {
	dd if="$1" skip=$2 bs=4 count=1 2>/dev/null | hexdump -v -n 4 -e '1/1 "%02x"'
}

[ ! -f "$FW_IN" ] && {
	echo "firmware file $FW_IN not found."
	exit 1
}

if [ ! -f ./output/mac01.bin ]; then
    echo "00000000 00 00 00 00 00 01" | xxd -r > ./output/mac01.bin
fi

cat > output/fullflash-ubi.ini <<EOF

[vol_uboot]
mode=ubi
image=output/u-boot.itb
vol_id=0
vol_size=786432
vol_type=static
vol_name=u-boot

[vol_factory]
mode=ubi
image=output/mac01.bin
vol_id=1
vol_size=131072
vol_type=static
vol_name=factory
EOF

if [ "$(nand_get_magic_long $FW_IN 0)" != "d00dfeed" ]; then
mkdir output/fw_tar
tar -C output/fw_tar -xvf $FW_IN || exit -1

	cat >> output/fullflash-ubi.ini <<EOF
[vol_fit]
mode=ubi
image=$(ls output/fw_tar/*/kernel)
vol_id=2
vol_type=dynamic
vol_name=fit

[vol_rootfs]
mode=ubi
image=$(ls output/fw_tar/*/root)
vol_id=3
vol_type=dynamic
vol_name=rootfs

[vol_rootfs_data]
mode=ubi
vol_id=4
vol_type=dynamic
vol_name=rootfs_data
vol_size=1MiB
vol_flags=autoresize
EOF
else
	cat >> output/fullflash-ubi.ini <<EOF
[vol_fit]
mode=ubi
image=$FW_IN
vol_id=2
vol_type=dynamic
vol_name=fit

[vol_rootfs_data]
mode=ubi
vol_id=3
vol_type=dynamic
vol_name=rootfs_data
vol_size=1MiB
vol_flags=autoresize
EOF
fi

./tools/ubinize -E 1 -o ./output/fullflash.ubi -p 131072 -m 2048 -e 126976 -O 2048 output/fullflash-ubi.ini
rm -f nand_fullflash.img
dd if=output/sf_fbl.img of=nand_fullflash.img bs=128k conv=sync
cat ./output/fullflash.ubi >> nand_fullflash.img
rm output/fullflash.ubi output/fullflash-ubi.ini

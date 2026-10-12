#!/bin/bash

chip_ver_board=sf21h8898_mpw0_evb_v2
pcba="0"

if [ "X$1" = "Xclean" ]; then
	./sf_make.sh cmd=clean
	exit 0
fi

if [ -n "$1" ]; then
	chip_ver_board=$1
fi

if [ -n "$2" ]; then
	pcba=$3
fi

chip=`echo "$chip_ver_board" |awk -F '_' '{print $1}'`
ver=`echo "$chip_ver_board" |awk -F '_' '{print $2}'`
board=`echo "$chip_ver_board" |awk -F '_' '{print $3}'`
for i in 4 5 6 7 8 9 10
do
	mycmd="echo \"\$chip_ver_board \" | awk -F '_' '{print \$${i}}'"
	board_t=`eval ${mycmd}`
	if [ -n "$board_t" ];then
		board="${board}_${board_t}"
	fi
done

git branch > /dev/null 2>&1
if [ ! $? -eq 0 ] ; then
	echo "dose not exist git base"
	tag="0.0"
	branch="default"
else
	# branch=`git branch  -r | grep "\->" |awk -F "/" 'END{print $NF}'`
	local_branch_name=`git branch -vv |grep "*" |awk '{print $2}'`
	# echo "local branch name $local_branch_name"
	if [ "$local_branch_name" = "(no" ]; then
		echo "branch set fail no local branch"
		exit 1
	fi

	branch=`git branch -vv |grep "*" | awk -F "[][]" '{print $2}'| awk -F "[/:]" '{print $2}'`
	echo "branch is $branch"

	if [ ! -n "$tag" ] ;then
		#compatible with old version
		tag=`git tag  |  grep -v "v"  | sort -V | awk 'END{print}'`
		version=$tag
	else
		version=`printf "$tag" | awk -F "[-]" '{print $2}'`
	fi

	if [ "X$version" = "X" ];then
		version="0.0"
	fi

	echo "version is $version"
	tag_commit=`git show $tag|grep ^commit | awk '{print substr($2,0,7)}'`
	echo "tag commit $tag_commit"
	last_commit=`git rev-parse --short HEAD`
	echo "last commit $last_commit"

	if [ $tag_commit != $last_commit ]; then
		commit_suffix=$last_commit
	fi
fi

echo "build chip ver board is [${chip} ${ver} ${board}]"

if [ "$pcba" = "1" ]; then
	target_bin="output/u-boot.img"
else
	target_bin="output/uboot_full.img"
fi

if [ "$pcba" = "1" ]; then
	uboot_or_pcba=pcba
else
	uboot_or_pcba=uboot
fi

if [ -n "$commit_suffix" ]; then
	prefix=${uboot_or_pcba}_${branch}_${chip_board}_${ver}_${version}_${commit_suffix}
else
	prefix=${uboot_or_pcba}_${branch}_${xhip_board}_${ver}_${version}
fi

echo "branch=$branch  chip_board=$chip_board  ver=$ver  version=$version"

rm $target_bin -rf

./sf_make.sh cmd=clean chip=$chip board=$board ver=$ver

./sf_make.sh cmd=dmake chip=$chip board=$board ver=$ver 

if [ -f $target_bin ]; then
	cp $target_bin ${prefix}.bin
else
	echo "build fail, don't get target_bin"
fi

echo "build end"

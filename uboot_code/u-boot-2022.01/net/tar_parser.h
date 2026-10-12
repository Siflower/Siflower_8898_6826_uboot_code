#ifndef __TAR_PARSER_H__
#define __TAR_PARSER_H__

#define BLOCKSIZE 512

typedef struct {
	char name[100];
	char mode[8];
	char uid[8];
	char gid[8];
	char size[12];
	char mtime[12];
	char chksum[8];
	char typeflag;
	char linkname[100];
	char magic[6];
	char version[2];
	char uname[32];
	char gname[32];
	char devmajor[8];
	char devminor[8];
	char prefix[155];
} TarHeader;

typedef struct {
	unsigned long kernel_offset;
	unsigned long kernel_size;
	unsigned long rootfs_offset;
	unsigned long rootfs_size;
	bool is_tar;
} FileOffsets;

void parseTarFile(uint8_t *mem, size_t memSize, FileOffsets *fileOffsets);

#endif

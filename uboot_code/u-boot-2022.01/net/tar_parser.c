#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <vsprintf.h>
#include "tar_parser.h"

unsigned long octalStrToULong(const char *str)
{
	char buf[16];
	char *endp = NULL;

	strncpy(buf, str, sizeof(buf) - 1);
	buf[sizeof(buf) - 1] = '\0';

	return ustrtoul(buf, &endp, 8);
}

static int is_ustar_format(const TarHeader *header)
{
	static const char ustar_magic[] = "ustar";

	return strncmp(header->magic, ustar_magic, (sizeof(ustar_magic) - 1)) == 0;
}

static int is_tar_file(const uint8_t *buf, size_t size)
{
	if (size < BLOCKSIZE)
		return 0;

	TarHeader *header = (TarHeader *)buf;

	if (is_ustar_format(header))
		return 1;

	return 0;
}

void parseTarFile(uint8_t *mem, size_t memSize, FileOffsets *fileOffsets)
{
	off_t currentOffset = 0;
	int ret = 0;

	ret = is_tar_file(mem + currentOffset, memSize);
	if (!ret) {
		printf("Not a valid TAR file.\n");
		fileOffsets->is_tar = false;
		return;
	} else {
		fileOffsets->is_tar = true;
	}

	while (currentOffset < memSize) {
		TarHeader *header = (TarHeader *)(mem + currentOffset);

		if (memSize - currentOffset < BLOCKSIZE) {
			break;
		}

		unsigned long fileSize = octalStrToULong(header->size);

		if (header->typeflag == '0' || header->typeflag == '\0') {
			char *filename = strrchr(header->name, '/');

			if (filename != NULL && strcmp(filename, "/root") == 0) {
				printf("Found rootfs at offset: %ld, Size: %lu\n", currentOffset + BLOCKSIZE, fileSize);
				fileOffsets->rootfs_offset = currentOffset + BLOCKSIZE;
				fileOffsets->rootfs_size = fileSize;
			} else if (filename != NULL && strcmp(filename, "/kernel") == 0) {
				printf("Found kernel at offset: %ld, Size: %lu\n", currentOffset + BLOCKSIZE, fileSize);
				fileOffsets->kernel_offset = currentOffset + BLOCKSIZE;
				fileOffsets->kernel_size = fileSize;
			}
		}
		currentOffset += ((fileSize + BLOCKSIZE - 1) / BLOCKSIZE + 1) * BLOCKSIZE;
	}
}

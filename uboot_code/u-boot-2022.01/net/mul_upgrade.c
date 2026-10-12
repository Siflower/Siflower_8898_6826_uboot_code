#include <common.h>
#include <command.h>
#include <net.h>
#include <stdlib.h>
#include <mapmem.h>
#include <u-boot/md5.h>

#define MULTICAST_PORT 1758
#define MTFTP_BITMAPSIZE	0x1000
#define MAX_PACKET_DATA_SIZE 1470
#define KERNEL_ADDRESS      0xa0000
#define ERASE_SECTOR_SIZE 0x10000

static unsigned *tftp_mcast_bitmap;
unsigned char t_md5sum[16];
size_t total_size;
static unsigned short idx;
static unsigned int t_count;
static unsigned int r_count;
static uchar* image_data;

static void parse_zero_frame(uchar *pkt)
{
    memset(t_md5sum, 0, sizeof(t_md5sum));

    if (pkt) {
        memcpy(t_md5sum, pkt, sizeof(t_md5sum));
        memcpy(&total_size, pkt + 16, sizeof(total_size));
    }

    if (total_size != 0) {
        if (total_size % MAX_PACKET_DATA_SIZE == 0) {
            t_count = total_size / MAX_PACKET_DATA_SIZE;
        } else {
            t_count = (total_size / MAX_PACKET_DATA_SIZE) + 1;
        }

        r_count = 0;
    }

    image_data = (uchar *)malloc(total_size);
    if (image_data == NULL) {
        printf("image_data malloc failed !\n");
        return;
    }

    printf("get idx:%u md5sum and lenth:%ld t_count:%u\n", idx, total_size, t_count);
    for(int i = 0; i < 16; i++) {
        printf("%02x", t_md5sum[i]);
    }

    ext2_set_bit(0, tftp_mcast_bitmap);
}

static void handler_normal_data(uchar *pkt, unsigned len)
{
    memcpy(image_data + (idx - 1) * MAX_PACKET_DATA_SIZE, pkt, len);
    r_count++;
    ext2_set_bit(idx, tftp_mcast_bitmap);
}

static void upgrade_image(void)
{
    char buf[96];
    void *ptr;
    unsigned long flash_kernel_addr = KERNEL_ADDRESS;
    ulong image_load_addr = CONFIG_SYS_LOAD_ADDR;

    ptr = map_sysmem(image_load_addr, total_size);
    memcpy(ptr, image_data, total_size);

    printf("start upgrade\n");

#ifdef CONFIG_MTD_SPI_NAND
    sprintf(buf,
        "ubi part FIRMWARE;"
        "ubi remove fit;"
        "ubi remove rootfs_data;"
        "ubi create fit %#lx dynamic;"
        "ubi write %#lx fit %#lx;"
        "ubi create rootfs_data - dynamic;"
        , total_size, image_load_addr, total_size);
#else
    sprintf(buf, "mtd erase nor0 %#lx %#lx;mtd write nor0 %#lx %#lx %#lx;",
		flash_kernel_addr, ALIGN(total_size, ERASE_SECTOR_SIZE),
		image_load_addr, flash_kernel_addr, total_size);
#endif
    printf("%s\n", buf);

    run_command(buf, 0);
    unmap_sysmem(ptr);
}

static void udp_handler(uchar *pkt, unsigned dest, struct in_addr sip,
			 unsigned src, unsigned len)
{
    __be16 *s;
    uchar r_md5sum[16];

    if (dest != MULTICAST_PORT) {
        return;
    }

    if (len < 2)
		return;

    s = (__be16 *)pkt;
    idx = ntohs(*s++);
    pkt = (uchar *)s;

    if (idx == 0 && !test_bit(idx, tftp_mcast_bitmap)) {
        parse_zero_frame(pkt);
    }

    if (test_bit(0, tftp_mcast_bitmap)) {
        if (!test_bit(idx, tftp_mcast_bitmap) && (idx <= t_count)) {
            handler_normal_data(pkt, len - 2);
        } else {
            return;
        }
    } else {
        return;
    }

    if (r_count == t_count) {
        memset(r_md5sum, 0, sizeof(r_md5sum));

        md5(image_data, total_size, r_md5sum);

        if (memcmp(t_md5sum, r_md5sum, 16) == 0) {
            printf("md5 check success\n");
            upgrade_image();
        } else {
            printf("md5 check fail , restart receive pkg\n");
            memset(tftp_mcast_bitmap, 0, MTFTP_BITMAPSIZE);
            memset(image_data, 0, total_size);
            r_count = 0;

            ext2_set_bit(0, tftp_mcast_bitmap);

            return;
        }

        free(image_data);
        free(tftp_mcast_bitmap);

        printf("upgrade image done \n");
        do_reset( NULL,0,0,NULL );
    } else {
        putc('#');
    }

}

void Mulupgrade(void)
{
    tftp_mcast_bitmap = malloc(MTFTP_BITMAPSIZE);
    if (!tftp_mcast_bitmap) {
        printf("No bitmap, no multicast. Sorry.\n");
        return;
    }
    memset(tftp_mcast_bitmap, 0, MTFTP_BITMAPSIZE);

    net_set_udp_handler(udp_handler);
}


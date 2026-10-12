#include <mtd.h>
#include <double_image_backup.h>

static struct mtd_info *get_mtd_by_name(const char *name)
{
	struct mtd_info *mtd;

	mtd = get_mtd_device_nm(name);
	if (IS_ERR_OR_NULL(mtd))
		printf("MTD device %s not found, ret %ld\n", name,
		       PTR_ERR(mtd));

	return mtd;
}

static bool mtd_is_aligned_with_block_size(struct mtd_info *mtd, u64 size)
{
	return !do_div(size, mtd->erasesize);
}

void spi_read(loff_t from, size_t len,size_t *retlen, u_char *buf)
{
	struct mtd_info *mtd;
	mtd = get_mtd_by_name("nor0");
	mtd->_read(mtd, from, len, retlen, buf);
}

void spi_write(loff_t to, size_t len,size_t *retlen, const u_char *buf)
{
	struct mtd_info *mtd;
	mtd = get_mtd_by_name("nor0");
	mtd->_write(mtd, to, len, retlen,buf);
}

void spi_erase(loff_t off,size_t len)
{
	struct mtd_info *mtd;
	mtd = get_mtd_by_name("nor0");

	if (!mtd_is_aligned_with_block_size(mtd, off)) {
		printf("Offset not aligned with a block (0x%x)\n",
		       mtd->erasesize);
		return;
	}
	if (!mtd_is_aligned_with_block_size(mtd, len)) {
		printf("Size not a multiple of a block (0x%x)\n",
		       mtd->erasesize);
		return;
	}
	struct erase_info instr;
	instr.addr = off;
	instr.len = mtd->erasesize;
	instr.mtd = mtd;
	while(len){
		mtd->_erase(mtd, &instr);
		len -= mtd->erasesize;
		instr.addr += mtd->erasesize;
	}
}

static unsigned int get_flag_on_flash(void)
{
	size_t retlen;
	unsigned int flash_flag = 0;
	unsigned char factory[FACTORY_SIZE];

	spi_read(FACTORY_OFFSET, FACTORY_SIZE, &retlen, factory);
	flash_flag = *((unsigned int*)(factory + FACTORY_BACKUP_FLAG_OFFSET));

	return flash_flag;
}

static void set_flag_on_flash(unsigned int value)
{
	size_t retlen;
	unsigned char factory[FACTORY_SIZE];

	spi_read(FACTORY_OFFSET, FACTORY_SIZE, &retlen, factory);
	spi_erase(FACTORY_OFFSET, FACTORY_SIZE);
	*((unsigned int*)(factory + FACTORY_BACKUP_FLAG_OFFSET)) = value;
	spi_write(FACTORY_OFFSET, FACTORY_SIZE, &retlen, factory);
}

static u32 get_flag_on_ram(void)
{
	u32 value = *((volatile u32*)BAKUP_FLAG_ON_RAM_ADDRESS);
	return value;
}

static void set_flag_on_ram(u32 value)
{
	*((volatile u32*)BAKUP_FLAG_ON_RAM_ADDRESS) = value;
}

int need_boot_backup_img(void)
{
	mtd_probe_devices();

	u32 flash_flag = get_flag_on_flash();
	u32 ram_flag = get_flag_on_ram();

	if(ram_flag == LAST_BOOTUP_FAILED){
		if(flash_flag == MASTER_IMAGE){
			set_flag_on_flash(BACKUP_IMAGE);
			return BOOT_BACKUP;
		} else if(flash_flag == BACKUP_IMAGE) {
			set_flag_on_flash(MASTER_IMAGE);
			return BOOT_MASTER;
		} else {
			printf("boot backup image fail");
			return MASTER_IMAGE;
		}
	}else{
		if(flash_flag == MASTER_IMAGE)
			return BOOT_MASTER;
		else
			return BOOT_BACKUP;
	}
}

void staring_up_image(void)
{
	set_flag_on_ram(BOOTUP_IMAGE);
}

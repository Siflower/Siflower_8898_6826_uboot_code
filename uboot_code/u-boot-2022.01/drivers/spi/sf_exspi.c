// SPDX-License-Identifier: GPL-2.0+
/*
 * (C) Copyright 2012
 * Armando Visconti, ST Microelectronics, armando.visconti@st.com.
 *
 * (C) Copyright 2018
 * Quentin Schulz, Bootlin, quentin.schulz@bootlin.com
 *
 * Driver for ARM PL022 SPI Controller.
 */

#include <common.h>
#include <clk.h>
#include <dm.h>
#include <dm/platform_data/spi_sf_exspi.h>
#include <errno.h>
#include <spi.h>
#include <spi-mem.h>
#include <linux/io.h>
#include <asm/global_data.h>
#if CONFIG_IS_ENABLED(DM_GPIO)
#include <asm/gpio.h>
#endif

/*
 * siflower SSP fifo level
 * */
#define SF_SSP_FIFO_LEVEL			0x100

/*
 * siflower SSP register
 * */
#define SSP_CR0				0x000
#define SSP_CR1				0x004
#define SSP_DR				0x008
#define SSP_SR				0x00C
#define SSP_CPSR			0x010
#define SSP_IMSC			0x014
#define SSP_RIS				0x018
#define SSP_MIS				0x01C
#define SSP_ICR				0x020
#define SSP_DMACR			0x024
#define SSP_FIFO_LEVEL		0x028
#define SSP_EXSPI_CMD0      0x02C
#define SSP_EXSPI_CMD1      0x030
#define SSP_EXSPI_CMD2      0x034


/* SSP Control Register 0  - SSP_CR0 */
#define SSP_CR0_EXSPI_FRAME		(0x3 << 4)
#define SSP_CR0_SPO				(0x1 << 6)
#define SSP_CR0_SPH				(0x1 << 7)
#define SSP_CR0_BIT_MODE(x)		((x) - 1)
#define SSP_SCR_MIN				(0x00)
#define SSP_SCR_MAX				(0xFF)
#define SSP_SCR_SHFT			8
#define DFLT_CLKRATE			2

/* SSP Control Register 1  - SSP_CR1 */
#define SSP_CR1_MASK_SSE		(0x1 << 1)

#define SSP_CPSR_MIN			(0x02)
#define SSP_CPSR_MAX			(0xFE)
#define DFLT_PRESCALE			(0x40)

/* SSP Status Register - SSP_SR */
#define SSP_SR_MASK_TFE			(0x1 << 0) /* Transmit FIFO empty */
#define SSP_SR_MASK_TNF			(0x1 << 1) /* Transmit FIFO not full */
#define SSP_SR_MASK_RNE			(0x1 << 2) /* Receive FIFO not empty */
#define SSP_SR_MASK_RFF			(0x1 << 3) /* Receive FIFO full */
#define SSP_SR_MASK_BSY			(0x1 << 4) /* Busy Flag */

#define MAX_CS_COUNT	2
struct sf_exspi_slave {
	void *base;
#if CONFIG_IS_ENABLED(DM_GPIO)
	struct gpio_desc cs_gpio[MAX_CS_COUNT];
#endif
	unsigned int freq;
};

static int sf_exspi_probe(struct udevice *bus)
{
	struct sf_exspi_pdata *plat = dev_get_plat(bus);
	struct sf_exspi_slave *ps = dev_get_priv(bus);

#if CONFIG_IS_ENABLED(DM_GPIO)
	int ret = gpio_request_list_by_name(bus, "cs-gpios", ps->cs_gpio,
					ARRAY_SIZE(ps->cs_gpio), GPIOD_IS_OUT);
	if (ret < 0) {
		pr_debug("Can't get %s gpios! Error: %d", bus->name, ret);
	} else {
		for (int i = 0; i < ARRAY_SIZE(ps->cs_gpio); i++) {
			if (!dm_gpio_is_valid(&ps->cs_gpio[i]))
				continue;

			dm_gpio_set_dir_flags(&ps->cs_gpio[i],
					      GPIOD_IS_OUT | GPIOD_IS_OUT_ACTIVE);
			dm_gpio_set_value(&ps->cs_gpio[i], 0);
		}
	}
#endif

	ps->base = ioremap(plat->addr, plat->size);
	ps->freq = plat->freq;

	/* 8 bits per word, high polarity and default clock rate */
	writew(SSP_CR0_BIT_MODE(8), ps->base + SSP_CR0);
	writew(DFLT_PRESCALE, ps->base + SSP_CPSR);

	return 0;
}

static void sf_exspi_flush_rxfifo(struct sf_exspi_slave *ps)
{
	do {
		while (readw(ps->base + SSP_SR) & SSP_SR_MASK_RNE)
			readw(ps->base + SSP_DR);
	} while (readw(ps->base + SSP_SR) & SSP_SR_MASK_BSY);
}

static int sf_exspi_enable(struct sf_exspi_slave *ps)
{
	u16 reg;

	/* Enable the SPI hardware */
	reg = readw(ps->base + SSP_CR1);
	reg |= SSP_CR1_MASK_SSE;
	writew(reg, ps->base + SSP_CR1);

	return 0;
}

static int sf_exspi_disable(struct sf_exspi_slave *ps)
{
	u16 reg;

	sf_exspi_flush_rxfifo(ps);

	/* Disable the SPI hardware */
	reg = readw(ps->base + SSP_CR1);
	reg &= ~SSP_CR1_MASK_SSE;
	writew(reg, ps->base + SSP_CR1);

	return 0;
}

static int sf_exspi_xfer(struct sf_exspi_slave *ps, unsigned int bitlen,
		const void *dout, void *din, unsigned long flags)
{
	u32		len_tx = 0, len_rx = 0, len;
	u32		ret = 0;
	const u8	*txp = dout;
	u8		*rxp = din, value;

	if (bitlen == 0)
		/* Finish any previously submitted transfers */
		return 0;

	if (flags & SPI_XFER_BEGIN) {
		/*
		 * sometimes the RDR is not empty when we get here,
		 * in theory that should not happen, but it DOES happen.
		 * Read it here to be on the safe side.
		 * That also clears the OVRES flag. Required if the
		 * following loop exits due to OVRES!
		 */
		while (readl(ps->base + SSP_SR) & SSP_SR_MASK_RNE)
			readl(ps->base + SSP_DR);

	}

	/*
	 * TODO: The controller can do non-multiple-of-8 bit
	 * transfers, but this driver currently doesn't support it.
	 *
	 * It's also not clear how such transfers are supposed to be
	 * represented as a stream of bytes...this is a limitation of
	 * the current SPI interface.
	 */
	if (bitlen % 8) {
		/* Errors always terminate an ongoing transfer */
		flags |= SPI_XFER_END;
		ret = -1;
		goto out;
	}

	len = bitlen / 8;

	/*
	 * write data to fifo
	 * */
	while (txp && (len_tx < len)) {
		if (readw(ps->base + SSP_SR) & SSP_SR_MASK_TNF) {
			value = txp ? *txp++ : 0;
			writew(value, ps->base + SSP_DR);
			len_tx++;
		}
	}

	/*
	 * read data from fifo
	 * */
	while (rxp && (len_rx < len)) {
		if (readw(ps->base + SSP_SR) & SSP_SR_MASK_RNE) {
			value = readw(ps->base + SSP_DR);
			*rxp++ = value;
			len_rx++;
		}
	}

out:
	return ret;
}

static inline u32 spi_rate(u32 rate, u16 cpsdvsr, u16 scr)
{
	return rate / (cpsdvsr * (1 + scr));
}

static int sf_exspi_set_speed(struct udevice *bus, uint speed)
{
	struct sf_exspi_slave *ps = dev_get_priv(bus);
	u16 scr = SSP_SCR_MIN, cr0 = 0, cpsr = SSP_CPSR_MIN, best_scr = scr,
	    best_cpsr = cpsr;
	u32 min, max, best_freq = 0, tmp;
	u32 rate = ps->freq;
	bool found = false;

	max = spi_rate(rate, SSP_CPSR_MIN, SSP_SCR_MIN);
	min = spi_rate(rate, SSP_CPSR_MAX, SSP_SCR_MAX);

	if (speed > max || speed < min) {
		pr_err("Tried to set speed to %dHz but min=%d and max=%d\n",
		       speed, min, max);
		return -EINVAL;
	}

	while (cpsr <= SSP_CPSR_MAX && !found) {
		while (scr <= SSP_SCR_MAX) {
			tmp = spi_rate(rate, cpsr, scr);

			if (abs(speed - tmp) < abs(speed - best_freq)) {
				best_freq = tmp;
				best_cpsr = cpsr;
				best_scr = scr;

				if (tmp == speed) {
					found = true;
					break;
				}
			}

			scr++;
		}
		cpsr += 2;
		scr = SSP_SCR_MIN;
	}

	writew(best_cpsr, ps->base + SSP_CPSR);
	cr0 = readw(ps->base + SSP_CR0);
	writew(cr0 | (best_scr << SSP_SCR_SHFT), ps->base + SSP_CR0);

	return 0;
}

static int sf_exspi_set_mode(struct udevice *bus, uint mode)
{
	struct sf_exspi_slave *ps = dev_get_priv(bus);
	u16 reg;

	reg = readw(ps->base + SSP_CR0);
	reg &= ~(SSP_CR0_SPH | SSP_CR0_SPO);
	if (mode & SPI_CPHA)
		reg |= SSP_CR0_SPH;
	if (mode & SPI_CPOL)
		reg |= SSP_CR0_SPO;
	/*
	 * set exspi frame format
	 * */
	reg |= SSP_CR0_EXSPI_FRAME;

	writew(reg, ps->base + SSP_CR0);

	return 0;
}

static int sf_exspi_adjust_op_size(struct spi_slave *slave,
		struct spi_mem_op *op)
{
	u32 nbytes;

	nbytes = op->cmd.nbytes + op->addr.nbytes + op->dummy.nbytes;

	if (nbytes + op->data.nbytes <= SF_SSP_FIFO_LEVEL)
		return 0;

	if (nbytes >= SF_SSP_FIFO_LEVEL)
		return -ENOTSUPP;

	op->data.nbytes = SF_SSP_FIFO_LEVEL - nbytes;

	return 0;
}

static bool sf_exspi_supports_op(struct spi_slave *slave,
		const struct spi_mem_op *op)
{
	struct udevice *dev = slave->dev;
	int tx = dev_read_u32_default(dev, "spi-tx-bus-width", 1);
	int rx = dev_read_u32_default(dev, "spi-rx-bus-width", 1);
	int limit = 1;
	if (tx && tx == rx)
		limit = tx;
	if (op->cmd.buswidth > limit || op->addr.buswidth > limit ||
	    op->dummy.buswidth > limit || op->data.buswidth > limit)
		return false;

	return true;
}

static void sf_exspi_set_param(struct sf_exspi_slave *ps, const struct spi_mem_op *op)
{
	u8 cmd_io, addr_io, data_io;
	u8 cmd_count, addr_count, ehc_count;
	u8 tx_count = 0, rx_count = 0;
//	static const u8 io_tb[5] = {0, 1, 2, 3, 3};

	cmd_io  = op->cmd.buswidth  == 4 ? 3 : op->cmd.buswidth;
	addr_io = op->addr.buswidth == 4 ? 3 : op->addr.buswidth;
	data_io = op->data.buswidth == 4 ? 3 : op->data.buswidth;

	if (op->data.nbytes) {
		if (op->data.dir == SPI_MEM_DATA_IN) {
			rx_count = op->data.nbytes;
		} else {
			tx_count = op->data.nbytes;
		}
	}

	if (op->addr.nbytes > 3) {
		addr_count = 3;
		ehc_count =1;
	} else {
		addr_count = op->addr.nbytes;
		ehc_count =0;
	}
	cmd_count = op->cmd.nbytes;

	writew(cmd_io | addr_io  << 2 | data_io << 4 , 
			ps->base + SSP_EXSPI_CMD2);

	writew(op->dummy.nbytes | rx_count << 4 , 
			ps->base + SSP_EXSPI_CMD1);

	writew(1 << 15 | op->cmd.nbytes | addr_count << 1 | ehc_count << 3 | tx_count << 4 , 
			ps->base + SSP_EXSPI_CMD0);
}

static int sf_exspi_exec_op(struct spi_slave *slave,
		const struct spi_mem_op *op)
{
#if CONFIG_IS_ENABLED(DM_GPIO)
	struct dm_spi_slave_plat *slave_plat = dev_get_parent_plat(slave->dev);
	unsigned int cs = slave_plat->cs;
#endif
	struct udevice *bus = slave->dev->parent;
	struct sf_exspi_slave *ps = dev_get_priv(bus);
	unsigned int pos = 0;
	const u8 *tx_buf = NULL;
	u8 *rx_buf = NULL;
	int op_len;
	u32 flag;
	int ret;
	int i;

	if (op->data.nbytes) {
		if (op->data.dir == SPI_MEM_DATA_IN) {
			rx_buf = op->data.buf.in;
		} else {
			tx_buf = op->data.buf.out;
		}
	}
	op_len = op->cmd.nbytes + op->addr.nbytes + op->dummy.nbytes;

	sf_exspi_set_param(ps, op);

	/*
	 * Avoid using malloc() here so that we can use this code in SPL where
	 * simple malloc may be used. That implementation does not allow free()
	 * so repeated calls to this code can exhaust the space.
	 *
	 * The value of op_len is small, since it does not include the actual
	 * data being sent, only the op-code and address. In fact, it should be
	 * possible to just use a small fixed value here instead of op_len.
	 */
	u8 op_buf[op_len];

	op_buf[pos++] = op->cmd.opcode;

	if (op->addr.nbytes) {
		for (i = 0; i < op->addr.nbytes; i++)
			op_buf[pos + i] = op->addr.val >>
				(8 * (op->addr.nbytes - i - 1));

		pos += op->addr.nbytes;
	}

#if CONFIG_IS_ENABLED(DM_GPIO)
	if (dm_gpio_is_valid(&ps->cs_gpio[cs]))
		dm_gpio_set_value(&ps->cs_gpio[cs], 1);
#endif

	while (readl(ps->base + SSP_SR) & SSP_SR_MASK_RNE)
		readl(ps->base + SSP_DR);

	if (op->dummy.nbytes)
		memset(op_buf + pos, 0xff, op->dummy.nbytes);

	/* 1st transfer: opcode + address + dummy cycles */
	flag = SPI_XFER_BEGIN;
	/* Make sure to set END bit if no tx or rx data messages follow */
	if (!tx_buf && !rx_buf)
		flag |= SPI_XFER_END;

	ret = sf_exspi_xfer(ps, op_len * 8, op_buf, NULL, flag);
	if (ret)
		goto out;

	if (tx_buf) {
		ret = sf_exspi_xfer(ps, op->data.nbytes * 8, tx_buf,
			       NULL, SPI_XFER_END);
		if (ret)
			 goto out;
	}

	sf_exspi_enable(ps);

	if (rx_buf) {
		ret = sf_exspi_xfer(ps, op->data.nbytes * 8, NULL,
				rx_buf, SPI_XFER_END);
		if (ret)
			 goto out;
	}
out:

	sf_exspi_flush_rxfifo(ps);
	sf_exspi_disable(ps);

#if CONFIG_IS_ENABLED(DM_GPIO)
	if (dm_gpio_is_valid(&ps->cs_gpio[cs]))
		dm_gpio_set_value(&ps->cs_gpio[cs], 0);
#endif
	return ret;
}

static const struct spi_controller_mem_ops sf_exspi_mem_ops = {
	.adjust_op_size = sf_exspi_adjust_op_size,
	.supports_op = sf_exspi_supports_op,
	.exec_op = sf_exspi_exec_op,
};

static const struct dm_spi_ops sf_exspi_ops = {
	.set_speed      = sf_exspi_set_speed,
	.set_mode       = sf_exspi_set_mode,
	.mem_ops		= &sf_exspi_mem_ops,
};

#if CONFIG_IS_ENABLED(OF_REAL)
static int sf_exspi_of_to_plat(struct udevice *bus)
{
	struct sf_exspi_pdata *plat = dev_get_plat(bus);
	const void *fdt = gd->fdt_blob;
	int node = dev_of_offset(bus);
	struct clk clkdev;
	int ret;

	plat->addr = fdtdec_get_addr_size(fdt, node, "reg", &plat->size);

	ret = clk_get_by_index(bus, 0, &clkdev);
	if (ret)
		return ret;

	plat->freq = clk_get_rate(&clkdev);

	return 0;
}

static const struct udevice_id sf_exspi_ids[] = {
	{ .compatible = "siflower,sf-exspi" },
	{ }
};
#endif

U_BOOT_DRIVER(sf_exspi) = {
	.name   = "sf_exspi",
	.id     = UCLASS_SPI,
#if CONFIG_IS_ENABLED(OF_REAL)
	.of_match = sf_exspi_ids,
	.of_to_plat = sf_exspi_of_to_plat,
#endif
	.ops    = &sf_exspi_ops,
	.plat_auto	= sizeof(struct sf_exspi_pdata),
	.priv_auto	= sizeof(struct sf_exspi_slave),
	.probe  = sf_exspi_probe,
};

/**
 * Siflower I2C Reset Controller
 */

#include <common.h>
#include <dm.h>
#include <reset-uclass.h>
#include <asm/io.h>
#include <dm/device_compat.h>
#include <dm/device-internal.h>
#include <dm/lists.h>
#include <linux/bitops.h>

#define CLK_EN_OFFSET	0x4
#define SOFT_BOE_OFFSET	0xc

struct siflower_i2c_reset_priv {
	void *base;
	/* number of reset signals */
	int nr_reset;
};

static int get_module_clk_gate(void *soft_reset_offset, bool clk)
{

	unsigned long *reg,tmp;
	reg = soft_reset_offset;

	if(!clk)
		tmp = readl((void*)reg);

	else
		printf(KERN_ERR "Bad usage of get_module_clk_gate, the 1st parameter must be SF_IRAM_SOFT_RESET" \
				"when the 2nd parameter is true.\n");
	return tmp;

		return tmp;

}

static void set_module_clk_gate(void *soft_reset_offset, u32 val, bool clk)
{
	unsigned long *reg;
	if(!clk)
	{
		reg = soft_reset_offset;
		writel((val & 0xFF),(void *)reg);
	}
	return;
}

static int sf_rst_trigger(struct reset_ctl *rst, bool level)
{
	int num = 0, tmp;
	struct siflower_i2c_reset_priv *priv = dev_get_priv(rst->dev);

	if(rst == NULL)
		return -EINVAL;

	tmp = get_module_clk_gate((priv->base + CLK_EN_OFFSET), false);

	if(tmp == 0)
		tmp = 0xff;

	if(level){
		set_module_clk_gate((priv->base), 0, false);
		tmp = tmp | (1 << num);
		set_module_clk_gate((priv->base + SOFT_BOE_OFFSET), 0xff, false);
	}
	else{
		set_module_clk_gate((priv->base), 0x7, false);
		tmp = tmp & (~(1 << num));
		set_module_clk_gate((priv->base + SOFT_BOE_OFFSET), 0x0, false);
	}
	set_module_clk_gate((priv->base + CLK_EN_OFFSET), tmp, false);

	return 0;
}

static int sf_reset_assert(struct reset_ctl *rst)
{
	return sf_rst_trigger(rst, false);
}

static int sf_reset_deassert(struct reset_ctl *rst)
{
	return sf_rst_trigger(rst, true);
}

static int sf_reset_request(struct reset_ctl *rst)
{
	struct siflower_i2c_reset_priv *priv = dev_get_priv(rst->dev);

	debug("%s(rst=%p) (dev=%p, id=%lu) (nr_reset=%d)\n", __func__,
	      rst, rst->dev, rst->id, priv->nr_reset);

	if (rst->id > priv->nr_reset)
		return -EINVAL;

	return 0;
}

int siflower_i2c_reset_probe(struct udevice *dev)
{
	struct siflower_i2c_reset_priv *priv = dev_get_priv(dev);

	priv->base = dev_remap_addr(dev);
	if (!priv->base)
		return -ENOMEM;

	priv->nr_reset = 1;
	return 0;
}

const struct reset_ops siflower_i2c_reset_ops = {
	.request	= sf_reset_request,
	.rst_assert	= sf_reset_assert,
	.rst_deassert	= sf_reset_deassert,
};

static const struct udevice_id sf_reset_ids[] = {
	{ .compatible = "siflower_i2c_reset" },
	{ },
};

U_BOOT_DRIVER(siflower_i2c_reset) = {
	.name		= "siflower_i2c_reset",
	.id		= UCLASS_RESET,
	.of_match	= sf_reset_ids,
	.ops		= &siflower_i2c_reset_ops,
	.probe		= siflower_i2c_reset_probe,
	.priv_auto	= sizeof(struct siflower_i2c_reset_priv),
};
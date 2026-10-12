// SPDX-License-Identifier:	GPL-2.0+

#include <common.h>
#include <dm.h>
#include <errno.h>
#include <malloc.h>
#include <asm/io.h>
#include <asm/gpio.h>
#include <dm/device_compat.h>
#include <dm/pinctrl.h>

#define GPIO_IR(n)	(0x40 * (n) + 0x00)
#define GPIO_OR(n)	(0x40 * (n) + 0x04)
#define GPIO_DIR(n)	(0x40 * (n) + 0x08)

struct sfax8_gpio_priv {
	void *gpio_base;
	struct udevice *pinctrl;
	char name[2];
};

static int sf_gpio_request(struct udevice *dev, unsigned offset,
			   const char *label)
{
	struct sfax8_gpio_priv *priv = dev_get_priv(dev);

	/* pinctrl-single::request takes func as GPIO offset */
	return pinctrl_request(priv->pinctrl, offset, 0);
}

static int sf_gpio_get_value(struct udevice *dev, unsigned offset)
{
	struct sfax8_gpio_priv *priv = dev_get_priv(dev);

	return readl(priv->gpio_base + GPIO_IR(offset));
}

static int sf_gpio_set_value(struct udevice *dev, unsigned offset, int value)
{
	struct sfax8_gpio_priv *priv = dev_get_priv(dev);

	writel(!!value, priv->gpio_base + GPIO_OR(offset));

	return 0;
}

static int sf_gpio_set_flags(struct udevice *dev, unsigned offset, ulong flags)
{
	struct sfax8_gpio_priv *priv = dev_get_priv(dev);

	if (flags & GPIOD_IS_IN) {
		writel(1, priv->gpio_base + GPIO_DIR(offset));
	} else if (flags & GPIOD_IS_OUT) {
		writel(!!(flags & GPIOD_IS_OUT_ACTIVE),
		       priv->gpio_base + GPIO_OR(offset));
		writel(0, priv->gpio_base + GPIO_DIR(offset));
	} else {
		return -EINVAL;
	}

	return 0;
}

static int sf_gpio_get_flags(struct udevice *dev, unsigned offset,
			     ulong *flagsp)
{
	struct sfax8_gpio_priv *priv = dev_get_priv(dev);

	if (readl(priv->gpio_base + GPIO_DIR(offset))) {
		*flagsp |= GPIOD_IS_IN;
	} else {
		u32 out = readl(priv->gpio_base + GPIO_OR(offset));

		*flagsp |= GPIOD_IS_OUT | (out ? GPIOD_IS_OUT_ACTIVE : 0);
	}

	return 0;
}

static const struct dm_gpio_ops gpio_sfax8_ops = {
	.request	= sf_gpio_request,
	.get_value	= sf_gpio_get_value,
	.set_value	= sf_gpio_set_value,
	.set_flags	= sf_gpio_set_flags,
	.get_flags	= sf_gpio_get_flags,
};

static int sfax8_gpio_probe(struct udevice *dev)
{
	struct gpio_dev_priv *uc_priv = dev_get_uclass_priv(dev);
	struct sfax8_gpio_priv *priv = dev_get_priv(dev);
	int ret = 0;

	priv->gpio_base = dev_read_addr_ptr(dev);
	if (!priv->gpio_base) {
		dev_err(dev, "Failed to get base address\n");
		return -EINVAL;
	}

	ret = dev_read_u32(dev, "ngpios", &uc_priv->gpio_count);
	if (ret < 0) {
		dev_err(dev, "Failed to get ngpios\n");
		return ret;
	}

	ret = uclass_get_device_by_phandle(UCLASS_PINCTRL, dev, "gpio-ranges",
					   &priv->pinctrl);
	if (ret < 0) {
		dev_err(dev, "Failed to get pinctrl phandle\n");
		return ret;
	}

	priv->name[0] = 'G';
	uc_priv->bank_name = priv->name;

	return 0;
}

static const struct udevice_id sfax8_gpio_ids[] = {
	{ .compatible = "siflower,sfax8-gpio" },
	{ }
};

U_BOOT_DRIVER(gpio_sfax8) = {
	.name		= "gpio_sfax8",
	.id		= UCLASS_GPIO,
	.of_match	= sfax8_gpio_ids,
	.ops		= &gpio_sfax8_ops,
	.probe		= sfax8_gpio_probe,
	.priv_auto	= sizeof(struct sfax8_gpio_priv),
};

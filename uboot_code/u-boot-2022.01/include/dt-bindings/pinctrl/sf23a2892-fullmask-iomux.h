#ifndef _DT_BINDINGS_SF23A2892_FULLMASK_IOMUX_H
#define _DT_BINDINGS_SF23A2892_FULLMASK_IOMUX_H

#define SW_DS		0x7		/* Drive strength */
#define SW_ST		(1 << 3)	/* Schmitt enable */
#define SW_PD		(1 << 4)	/* Pull-down enable */
#define SW_PU		(1 << 5)	/* Pull-up enable */
#define SW_OEN		(1 << 6)	/* Output disable [sic] */
#define SW_IE		(1 << 7)	/* Input enable */
#define MODE_BIT0	(1 << 8)	/* Function mode LSB */
#define MODE_BIT1	(1 << 9)	/* Function mode MSB */
#define FMUX_SEL	(1 << 10)	/* GPIO mode enable */
#define FUNC_SW_SEL	(1 << 11)	/* Function mode enable */

#define FUNC_MODE_MASK	0x1f10
#define FUNC_MODE0	(FUNC_SW_SEL | SW_IE)
#define FUNC_MODE1	(FUNC_MODE0 | MODE_BIT0)
#define FUNC_MODE2	(FUNC_MODE0 | MODE_BIT1)
#define FUNC_MODE3	(FUNC_MODE0 | MODE_BIT0 | MODE_BIT1)
#define GPIO_MODE	(FUNC_MODE0 | FMUX_SEL)

#define JTAG_TDO	0x00
#define JTAG_TDI	0x04
#define JTAG_TMS	0x08
#define JTAG_TCK	0x0c
#define JTAG_RST	0x10
#define SPI0_TXD	0x14
#define SPI0_RXD	0x18
#define SPI0_CLK	0x1c
#define SPI0_CSN	0x20
#define UART0_TX	0x24
#define UART0_RX	0x28
#define I2C0_DAT	0x2c
#define I2C0_CLK	0x30
#define SPI1_TXD	0x34
#define SPI1_RXD	0x38
#define SPI1_CLK	0x3c
#define SPI1_CSN	0x40
#define RGMII_GTX_CLK	0x44
#define RGMII_TXCLK	0x48
#define RGMII_TXD0	0x4c
#define RGMII_TXD1	0x50
#define RGMII_TXD2	0x54
#define RGMII_TXD3	0x58
#define RGMII_TXCTL	0x5c
#define RGMII_RXCLK	0x60
#define RGMII_RXD0	0x64
#define RGMII_RXD1	0x68
#define RGMII_RXD2	0x6c
#define RGMII_RXD3	0x70
#define RGMII_RXCTL	0x74
#define RGMII_COL	0x78
#define RGMII_CRS	0x7c
#define MDC		0x80
#define MDIO		0x84
#define HB0_FEM_C0	0x88
#define HB0_FEM_C1	0x8c
#define HB0_FEM_C2	0x90
#define HB1_FEM_C0	0x94
#define HB1_FEM_C1	0x98
#define HB1_FEM_C2	0x9c
#define LB0_FEM_C0	0xa0
#define LB0_FEM_C1	0xa4
#define LB0_FEM_C2	0xa8
#define LB1_FEM_C0	0xac
#define LB1_FEM_C1	0xb0
#define LB1_FEM_C2	0xb4
#define EXT_CLK_IN 	0xb8
#define CLK_OUT		0xbc

#endif

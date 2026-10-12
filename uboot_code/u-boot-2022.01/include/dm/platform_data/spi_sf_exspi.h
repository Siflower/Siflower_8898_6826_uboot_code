#ifndef __spi_sf_exspi_h
#define __spi_sf_exspi_h

#include <fdtdec.h>

struct sf_exspi_pdata {
	fdt_addr_t addr;
	fdt_size_t size;
	unsigned int freq;
};

#endif /* __spi_sf_exspi_h */


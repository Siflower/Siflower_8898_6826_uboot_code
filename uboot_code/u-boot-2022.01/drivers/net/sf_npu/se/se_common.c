#ifndef SE_COMMON_C
#define SE_COMMON_C

#include <string.h>

#include "se_common.h"

unsigned short crc16(unsigned char *buf, int len, int poly_sel)
{
	unsigned short crc = 0;
	unsigned int arith;
        int i = 0;

        if(poly_sel == 0) {
        	arith = 0x1021;
        }
        else if(poly_sel == 1) {
        	arith = 0x8005;
        }
        else if(poly_sel == 2) {
        	arith = 0xA097;
        }
        else if(poly_sel == 3) {
        	arith = 0x8BB7;
        }
        else if(poly_sel == 4) {
        	arith = 0xC867;
        }
        else if(poly_sel == 5) {
        	arith = 0x3D65;
        }
        else if(poly_sel == 6) {
        	arith = 0x0589;
        }
        else if(poly_sel == 7) {
        	arith = 0x509D;
        }

	while(len--) {
		crc  = crc ^ (*buf++ << 8);
		for (i = 0; i < 8; i++)
		{
			if (crc & 0x8000)
				crc = (crc << 1) ^ arith;
			else
				crc = crc << 1;
		}
	}

	return crc;
}

unsigned char gen_all_1_data8(int width) {
    int i;
    unsigned char data = 0x0;
    for(i=0; i<width; i++) {
        data = data | (0x1<<i);
    }
    return data;
}

unsigned short gen_all_1_data16(int width) {
    int i;
    unsigned short data = 0x0;
    for(i=0; i<width; i++) {
        data = data | (0x1<<i);
    }
    return data;
}

unsigned int gen_all_1_data32(int width) {
    int i;
    unsigned int data = 0x0;
    for(i=0; i<width; i++) {
        data = data | (0x1<<i);
    }
    return data;
}

uint64_t gen_all_1_data64(int width) {
    int i;
    uint64_t data = 0x0;
    for(i=0; i<width; i++) {
        data = data | ((uint64_t)0x1<<i);
    }
    return data;
}

void update_data8(unsigned char* data, int offset, int width, unsigned char value) {
    unsigned char new_data;
    unsigned char tmp = gen_all_1_data8(width);

    new_data = (*data & ~(tmp<<offset)) | (value <<offset);
    *data = new_data;
}

unsigned char get_data8(unsigned char data, int offset, int width) {
    unsigned char new_data;
    unsigned char tmp = gen_all_1_data8(width);

    new_data = ( (data & (tmp<<offset)) >> offset );
    return new_data;
}

void update_data16(unsigned short* data, int offset, int width, unsigned short value) {
    unsigned short new_data;
    unsigned short tmp = gen_all_1_data16(width);

    new_data = (*data & ~(tmp<<offset)) | (value <<offset);
    *data = new_data;
}

unsigned short get_data16(unsigned short data, int offset, int width) {
    unsigned short new_data;
    unsigned short tmp = gen_all_1_data16(width);

    new_data = ( (data & (tmp<<offset)) >> offset );
    return new_data;
}

void update_data32(unsigned int* data, int offset, int width, unsigned int value) {
    unsigned int new_data;
    unsigned int tmp = gen_all_1_data32(width);

    new_data = (*data & ~(tmp<<offset)) | (value <<offset);
    *data = new_data;
}

unsigned int get_data32(unsigned int data, int offset, int width) {
    unsigned int new_data;
    unsigned int tmp = gen_all_1_data32(width);

    new_data = ( (data & (tmp<<offset)) >> offset );
    return new_data;
}

void update_reg(unsigned int addr, int offset, int width, unsigned int value) {
    unsigned int data;

    SF_RD_REG(addr, data);
    update_data32(&data, offset, width, value);
    SF_WR_REG(addr, data);
}

void update_data64(uint64_t* data, int offset, int width, uint64_t value) {
    uint64_t new_data;
    uint64_t tmp = gen_all_1_data64(width);

    new_data = (*data & ~(tmp<<offset)) | (value <<offset);
    *data = new_data;
}

uint64_t get_data64(uint64_t data, int offset, int width) {
    uint64_t new_data;
    uint64_t tmp = gen_all_1_data64(width);

    new_data = ( (data & (tmp<<offset)) >> offset );
    return new_data;
}

#endif

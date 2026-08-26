// Copyright 2006-2026 Speedgoat GmbH

#include "sg_fpga_IO3xx41_i2c.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include "sg_common.h"
#include "sg_printf.h"
#include "sg_fpga_xilinx_i2c.h"
int z9b7f1fec66(volatile uint8_t*z6f80acf22a,uint32_t z85a08f0628){uint8_t z4e469c7080=(0x3d1+466-0x5a3);switch(z85a08f0628){case zd753c49b18:z4e469c7080=(0x88+5646-0x1691);break;case zd12e05d1d1:z4e469c7080=(0x19d8+2673-0x2445);break;case z1ac0831d26:z4e469c7080=(0xc7+3867-0xfdb);break;case z22504f0065:z4e469c7080=(0x177b+3355-0x2490);break;default:SG_PRINTF(ERROR,"\x49\x6e\x76\x61\x6c\x69\x64\x20\x70\x6c\x75\x67\x4f\x6e\x20\x63\x68\x61\x6e\x6e\x65\x6c\x3a\x20\x30\x78\x25\x30\x32\x58" "\n",z85a08f0628);return I2C_MISC_ERROR;}uint8_t nbytes=(0x951+5569-0x1f11);uint8_t z4fc4944394=(0xe48+2497-0x1809);uint32_t result=sg_fpga_xilinx_i2c_write(z6f80acf22a,z01a9244916,(0x63+2887-0xbaa),&z4e469c7080,nbytes,z4fc4944394);if(result!=I2C_ERROR_OK){SG_PRINTF(ERROR,"\x49\x32\x43\x20\x77\x72\x69\x74\x65\x20\x66\x61\x69\x6c\x65\x64\x21\x72\x65\x73\x20\x3d\x20\x25\x64" "\n",result);return I2C_MISC_ERROR;}return I2C_ERROR_OK;}

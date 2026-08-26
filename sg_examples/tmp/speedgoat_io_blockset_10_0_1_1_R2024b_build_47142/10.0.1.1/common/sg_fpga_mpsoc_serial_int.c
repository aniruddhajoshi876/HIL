// Copyright 2006-2026 Speedgoat GmbH
static const int SG_INT_BARS[]={(0x43d+7294-0x20bb),(0xecc+919-0x1261)};
#include "sg_blocks/common/libsg/sg_common.h"
#include "sg_blocks/fpga/setup/include/sg_fpga_io3xx_util.h"
#ifdef SG_AXI_DEVICE_NAME
#include "sg_interrupt_config_axi.h"
#else
#include "sg_interrupt_config.h"
#endif
#include <stdint.h>
#define z2078598249      1081344
#define zc19a381cf7       5373952
#define z5c3f5520e2   (0.000001)
#define zc72cf764c2      (0x768+2510-0x10d6)
#define z72b0fd0e17 (0xa9f+1266-0xf41)
#define z9aa61b27a6 (0x905+5935-0x2033)
#ifndef z36db795bb0
#define z36db795bb0          (0xa9+241-0x199)
#endif
typedef struct{volatile uint32_t ISR;volatile uint32_t z2faa57e0eb;volatile uint32_t IER;volatile uint32_t z6759dc6668;volatile uint32_t zdfbc31d580;volatile uint32_t zd2888ccec8;volatile uint32_t zea83b74a38;volatile uint32_t z119ae482c7;volatile uint32_t zae4666333d;volatile uint32_t z1d07e70426;}z0ff288db65;struct SERIAL{uint32_t z5113d6a8d4;uint32_t zbc53575f66;uint32_t z937b9aa588;uint32_t zad12366ed6;uint32_t z224b61a322;uint32_t z05a38d9688;uint32_t z96ef554f24;uint32_t z41cf12af39;uint32_t version;uint32_t za6d2280101[(0x103f+3495-0x1dc6)];uint32_t zcf124b5c7b[(0xfc+2771-0xbaf)];uint32_t ze963c724bd[(0x19ea+2078-0x21e8)];uint32_t z5933ba9eef[(0x1876+859-0x1bb1)];uint32_t zb527a777b1[(0xf97+4495-0x2106)];uint32_t zbb6601ed0b[(0xb54+5501-0x20b1)];uint32_t zb2bfe8fd67[(0xd1c+4406-0x1e32)];uint32_t z9d9906152b[(0xd02+4861-0x1fdf)];uint32_t z0cb32ea574[(0xd52+3818-0x1c1c)];uint32_t z80200c8b92[(0xf46+3354-0x1c40)];uint32_t z0fac3ac62e[(0x1cc+5730-0x180e)];uint32_t z47dac54a30[(0x64+9736-0x264c)];uint32_t z00cc33cb8e[(0x1df3+825-0x210c)];uint32_t z0c6f5b8493[(0xd7+6018-0x1839)];uint32_t zb741e2a3ac[(0xf96+803-0x1299)];uint32_t z239d126e9d;uint32_t zdbfe9a161d;uint32_t z2292c73d55;uint32_t z2ccd606be7;uint32_t z3c2f87c6d7;uint32_t z20b2ce87e9;};SG_INT_START_FUNC{sg_fpga_intContext_customData*z8227d701d7=(sg_fpga_intContext_customData*)malloc(sizeof(sg_fpga_intContext_customData));if(z8227d701d7==NULL){}
#ifdef SG_AXI_DEVICE_NAME
z8227d701d7->moduleId=SG_INT_MODULE_ID;
#else
z8227d701d7->moduleId=sg_fpga_io3xx_getID(SG_INT_GET_PCIINFO);
#endif
if((0x1385+402-0x1517)==z8227d701d7->moduleId){free(z8227d701d7);}volatile z0ff288db65*z2b067ad6f2;volatile struct SERIAL*serial;volatile uint32_t*z65093051d7=(uint32_t*)(SG_INT_MAPPED_BAR((0xa78+5730-0x20da))+zc72cf764c2);volatile uint32_t*zc1156e3f7d=(uint32_t*)(SG_INT_MAPPED_BAR((0x117+2951-0xc9e))+z72b0fd0e17);uint32_t z20b2ce87e9,z9848dd6bca,i;uint32_t offset;sg_fpga_io3xx_getCmBaseAddress(z8227d701d7->moduleId,z2078598249,&offset);serial=(struct SERIAL*)((uintptr_t)SG_INT_MAPPED_BAR((0xa95+1966-0x1241))+offset);z8227d701d7->util_ptr=(void*)serial;SG_INT_CUSTOM_DATA=(void*)z8227d701d7;z2b067ad6f2=(z0ff288db65*)((uintptr_t)SG_INT_MAPPED_BAR((0x2c1+8716-0x24cb))+zc19a381cf7);SG_INT_ENABLE_FPGA_7SERIES_FIX_CI(z36db795bb0);if(!(SG_INT_IS_POLLING)){z2b067ad6f2->z6759dc6668=z36db795bb0;z2b067ad6f2->zdfbc31d580=z36db795bb0;z2b067ad6f2->z119ae482c7=(0x1791+3711-0x260d);}SG_PRINTF(DEBUG,"\x76\x65\x72\x73\x69\x6f\x6e\x20\x30\x78\x25\x78" "\n",serial->version);z20b2ce87e9=(0x1c0c+1480-0x21d4);for(i=(0x245d+481-0x263e);i<(0x6ac+2051-0xe8f);i++){if(serial->zb741e2a3ac[i]>(0x654+2991-0x1203)){z20b2ce87e9|=((0x978+187-0xa32)<<i);}}z9848dd6bca=serial->z3c2f87c6d7;serial->z20b2ce87e9=(0xe45+3920-0x1d95);serial->z3c2f87c6d7=(0x12f2+4365-0x23ff);serial->z20b2ce87e9=z20b2ce87e9;serial->z3c2f87c6d7=z9848dd6bca;*z65093051d7=(0xc3b+4250-0x1cd4);*zc1156e3f7d=z9aa61b27a6;return;}SG_INT_STOP_FUNC{sg_fpga_intContext_customData*z8227d701d7=(sg_fpga_intContext_customData*)SG_INT_CUSTOM_DATA;volatile z0ff288db65*z2b067ad6f2;volatile struct SERIAL*serial;volatile uint32_t*z65093051d7=(uint32_t*)(SG_INT_MAPPED_BAR((0x699+4606-0x1897))+zc72cf764c2);serial=(struct SERIAL*)z8227d701d7->util_ptr;z2b067ad6f2=(z0ff288db65*)((uintptr_t)SG_INT_MAPPED_BAR((0x9a9+1886-0x1105))+zc19a381cf7);*z65093051d7=(0xc67+1459-0x121a);z2b067ad6f2->zd2888ccec8=z36db795bb0;z2b067ad6f2->z119ae482c7=(0xf5b+2494-0x1919);serial->z20b2ce87e9=(0x569+7043-0x20ec);serial->z239d126e9d=4294967295;serial->z239d126e9d=(0x1269+1370-0x17c3);serial->z2292c73d55=4294967295;serial->z2292c73d55=(0x1bdb+1266-0x20cd);free(z8227d701d7);return;}SG_INT_ISR_FUNC{sg_fpga_intContext_customData*z8227d701d7=(sg_fpga_intContext_customData*)SG_INT_CUSTOM_DATA;volatile struct SERIAL*serial;volatile z0ff288db65*z2b067ad6f2;uint32_t z5450d078d5;if(z8227d701d7==NULL){return SG_DROP_ISR;}serial=(struct SERIAL*)z8227d701d7->util_ptr;z2b067ad6f2=(z0ff288db65*)((uintptr_t)SG_INT_MAPPED_BAR((0xf59+1730-0x1619))+zc19a381cf7);if((uintptr_t)SG_INT_MAPPED_BAR((0xd12+1079-0x1147))==(unsigned long)NULL)return SG_DROP_ISR;z5450d078d5=serial->zdbfe9a161d;if(z5450d078d5){serial->z239d126e9d=z5450d078d5;serial->z239d126e9d=(0x12af+1267-0x17a2);z2b067ad6f2->z6759dc6668=z36db795bb0;return SG_RUN_ISR;}else{return SG_DROP_ISR;}}

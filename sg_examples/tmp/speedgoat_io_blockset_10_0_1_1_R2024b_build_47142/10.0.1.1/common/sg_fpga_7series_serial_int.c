// Copyright 2006-2026 Speedgoat GmbH
static const int SG_INT_BARS[]={(0x132c+3971-0x22ad)};
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
#ifndef z36db795bb0
#define z36db795bb0          (0x13a7+1303-0x18bc)
#endif
typedef struct{volatile uint32_t ISR;volatile uint32_t z2faa57e0eb;volatile uint32_t IER;volatile uint32_t z6759dc6668;volatile uint32_t zdfbc31d580;volatile uint32_t zd2888ccec8;volatile uint32_t zea83b74a38;volatile uint32_t z119ae482c7;volatile uint32_t zae4666333d;volatile uint32_t z1d07e70426;}z0ff288db65;struct SERIAL{uint32_t z5113d6a8d4;uint32_t zbc53575f66;uint32_t z937b9aa588;uint32_t zad12366ed6;uint32_t z224b61a322;uint32_t z05a38d9688;uint32_t z96ef554f24;uint32_t z41cf12af39;uint32_t version;uint32_t za6d2280101[(0x540+3236-0x11c4)];uint32_t zcf124b5c7b[(0xb74+2721-0x15f5)];uint32_t ze963c724bd[(0x171+2778-0xc2b)];uint32_t z5933ba9eef[(0x28f+5602-0x1851)];uint32_t zb527a777b1[(0x1267+4453-0x23ac)];uint32_t zbb6601ed0b[(0x1438+2902-0x1f6e)];uint32_t zb2bfe8fd67[(0x115+5156-0x1519)];uint32_t z9d9906152b[(0x122b+5105-0x25fc)];uint32_t z0cb32ea574[(0x222+8231-0x2229)];uint32_t z80200c8b92[(0x697+4284-0x1733)];uint32_t z0fac3ac62e[(0x938+3574-0x170e)];uint32_t z47dac54a30[(0x3c4+3536-0x1174)];uint32_t z00cc33cb8e[(0x13bb+4730-0x2615)];uint32_t z0c6f5b8493[(0xf7+1691-0x772)];uint32_t zb741e2a3ac[(0x7c+1999-0x82b)];uint32_t z239d126e9d;uint32_t zdbfe9a161d;uint32_t z2292c73d55;uint32_t z2ccd606be7;uint32_t z3c2f87c6d7;uint32_t z20b2ce87e9;};SG_INT_START_FUNC{sg_fpga_intContext_customData*z8227d701d7=(sg_fpga_intContext_customData*)malloc(sizeof(sg_fpga_intContext_customData));if(z8227d701d7==NULL){}
#ifdef SG_AXI_DEVICE_NAME
z8227d701d7->moduleId=SG_INT_MODULE_ID;
#else
z8227d701d7->moduleId=sg_fpga_io3xx_getID(SG_INT_GET_PCIINFO);
#endif
if((0x28a+59-0x2c5)==z8227d701d7->moduleId){free(z8227d701d7);}volatile z0ff288db65*z2b067ad6f2;volatile struct SERIAL*serial;uint32_t z20b2ce87e9,z9848dd6bca,i;uint32_t offset;sg_fpga_io3xx_getCmBaseAddress(z8227d701d7->moduleId,z2078598249,&offset);serial=(struct SERIAL*)((uintptr_t)SG_INT_MAPPED_BAR((0x1ec0+1510-0x24a4))+offset);z8227d701d7->util_ptr=(void*)serial;SG_INT_CUSTOM_DATA=(void*)z8227d701d7;z2b067ad6f2=(z0ff288db65*)((uintptr_t)SG_INT_MAPPED_BAR((0x67b+4256-0x1719))+zc19a381cf7);SG_INT_ENABLE_FPGA_7SERIES_FIX_CI(z36db795bb0);if(!(SG_INT_IS_POLLING)){z2b067ad6f2->z6759dc6668=z36db795bb0;z2b067ad6f2->zdfbc31d580=z36db795bb0;z2b067ad6f2->z119ae482c7=(0xe78+4184-0x1ecd);}SG_PRINTF(DEBUG,"\x76\x65\x72\x73\x69\x6f\x6e\x20\x30\x78\x25\x78" "\n",serial->version);z20b2ce87e9=(0x561+5345-0x1a42);for(i=(0x1009+5362-0x24fb);i<(0x2ad+3475-0x1020);i++){if(serial->zb741e2a3ac[i]>(0xf33+192-0xff3)){z20b2ce87e9|=((0x174c+2400-0x20ab)<<i);}}z9848dd6bca=serial->z3c2f87c6d7;serial->z20b2ce87e9=(0x54c+5075-0x191f);serial->z3c2f87c6d7=(0x1cbd+229-0x1da2);serial->z20b2ce87e9=z20b2ce87e9;serial->z3c2f87c6d7=z9848dd6bca;return;}SG_INT_STOP_FUNC{sg_fpga_intContext_customData*z8227d701d7=(sg_fpga_intContext_customData*)SG_INT_CUSTOM_DATA;volatile z0ff288db65*z2b067ad6f2;volatile struct SERIAL*serial;serial=(struct SERIAL*)z8227d701d7->util_ptr;z2b067ad6f2=(z0ff288db65*)((uintptr_t)SG_INT_MAPPED_BAR((0xb10+3567-0x18fd))+zc19a381cf7);z2b067ad6f2->zd2888ccec8=z36db795bb0;z2b067ad6f2->z119ae482c7=(0x1342+2685-0x1dbf);serial->z20b2ce87e9=(0x1639+4263-0x26e0);serial->z239d126e9d=4294967295;serial->z239d126e9d=(0xaab+3219-0x173e);serial->z2292c73d55=4294967295;serial->z2292c73d55=(0x1aa2+1421-0x202f);free(z8227d701d7);return;}SG_INT_ISR_FUNC{sg_fpga_intContext_customData*z8227d701d7=(sg_fpga_intContext_customData*)SG_INT_CUSTOM_DATA;volatile struct SERIAL*serial;volatile z0ff288db65*z2b067ad6f2;uint32_t z5450d078d5;if(z8227d701d7==NULL){return SG_DROP_ISR;}serial=(struct SERIAL*)z8227d701d7->util_ptr;z2b067ad6f2=(z0ff288db65*)((uintptr_t)SG_INT_MAPPED_BAR((0x1394+1804-0x1a9e))+zc19a381cf7);if((uintptr_t)SG_INT_MAPPED_BAR((0x1a5c+1124-0x1ebe))==(unsigned long)NULL)return SG_DROP_ISR;z5450d078d5=serial->zdbfe9a161d;if(z5450d078d5){serial->z239d126e9d=z5450d078d5;serial->z239d126e9d=(0x16cf+3341-0x23dc);if(!(SG_INT_IS_POLLING)&&(z2b067ad6f2->ISR&z36db795bb0)){z2b067ad6f2->z6759dc6668=z36db795bb0;z2b067ad6f2->zdfbc31d580=z36db795bb0;}return SG_RUN_ISR;}else{return SG_DROP_ISR;}}

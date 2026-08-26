// Copyright 2006-2026 Speedgoat GmbH
static const int SG_INT_BARS[]={(0x8b6+522-0xac0),(0x107b+2531-0x1a5c)};
#include "sg_blocks/common/libsg/sg_common.h"
#include "sg_blocks/fpga/setup/include/sg_fpga_io3xx_util.h"
#ifdef SG_AXI_DEVICE_NAME
#include "sg_interrupt_config_axi.h"
#else
#include "sg_interrupt_config.h"
#endif
#include <stdint.h>
#define zc19a381cf7       5373952
#define z5c3f5520e2   (0.000001)
#define zc72cf764c2      (0x7bf+5861-0x1e44)
#define z72b0fd0e17 (0x411+225-0x4a2)
#define z9aa61b27a6 (0xa70+292-0xb93)
#ifndef z36db795bb0
#define z36db795bb0          (0x1df6+245-0x1eea)
#endif
typedef struct{volatile uint32_t ISR;volatile uint32_t z2faa57e0eb;volatile uint32_t IER;volatile uint32_t z6759dc6668;volatile uint32_t zdfbc31d580;volatile uint32_t zd2888ccec8;volatile uint32_t zea83b74a38;volatile uint32_t z119ae482c7;volatile uint32_t zae4666333d;volatile uint32_t z1d07e70426;}z0ff288db65;typedef struct{uint32_t zab46142f2e;uint32_t clear;uint32_t event;uint32_t version;uint32_t test1;}za276549eb0;SG_INT_START_FUNC{sg_fpga_intContext_customData*z8227d701d7=(sg_fpga_intContext_customData*)malloc(sizeof(sg_fpga_intContext_customData));if(z8227d701d7==NULL){}
#ifdef SG_AXI_DEVICE_NAME
z8227d701d7->moduleId=SG_INT_MODULE_ID;
#else
z8227d701d7->moduleId=sg_fpga_io3xx_getID(SG_INT_GET_PCIINFO);
#endif
if((0x97d+1081-0xdb6)==z8227d701d7->moduleId){free(z8227d701d7);}uint32_t offset;volatile z0ff288db65*z2b067ad6f2;volatile za276549eb0*z79f5963ede;volatile uint32_t*z65093051d7=(uint32_t*)(SG_INT_MAPPED_BAR((0xf80+2965-0x1b15))+zc72cf764c2);volatile uint32_t*zc1156e3f7d=(uint32_t*)(SG_INT_MAPPED_BAR((0x1449+4363-0x2554))+z72b0fd0e17);sg_fpga_io3xx_getCmBaseAddress(z8227d701d7->moduleId,INTA_BASE,&offset);z79f5963ede=(za276549eb0*)((uintptr_t)SG_INT_MAPPED_BAR((0xb62+721-0xe31))+offset);z8227d701d7->util_ptr=(void*)z79f5963ede;SG_INT_CUSTOM_DATA=(void*)z8227d701d7;z2b067ad6f2=(z0ff288db65*)((uintptr_t)SG_INT_MAPPED_BAR((0x907+1407-0xe84))+zc19a381cf7);SG_INT_ENABLE_FPGA_7SERIES_FIX_CI(z36db795bb0);if(!(SG_INT_IS_POLLING)){z2b067ad6f2->z6759dc6668=z36db795bb0;z2b067ad6f2->zdfbc31d580=z36db795bb0;z2b067ad6f2->z119ae482c7=(0xc52+650-0xed9);}SG_PRINTF(DEBUG,"\x76\x65\x72\x73\x69\x6f\x6e\x20\x30\x78\x25\x78" "\n",z79f5963ede->version);SG_PRINTF(DEBUG,"\x74\x65\x73\x74\x31\x20\x30\x78\x25\x78" "\n",z79f5963ede->test1);z79f5963ede->clear=(0x10d3+1289-0x15db);sg_wait_s(z5c3f5520e2);z79f5963ede->clear=(0x7bd+4396-0x18e9);z79f5963ede->zab46142f2e=z79f5963ede->zab46142f2e|(0x333+240-0x422);*z65093051d7=(0x14ba+3274-0x2183);*zc1156e3f7d=z9aa61b27a6;return;}SG_INT_STOP_FUNC{sg_fpga_intContext_customData*z8227d701d7=(sg_fpga_intContext_customData*)SG_INT_CUSTOM_DATA;volatile z0ff288db65*z2b067ad6f2;volatile za276549eb0*z79f5963ede;volatile uint32_t*z65093051d7=(uint32_t*)(SG_INT_MAPPED_BAR((0x4c6+8567-0x263d))+zc72cf764c2);z79f5963ede=(za276549eb0*)z8227d701d7->util_ptr;z2b067ad6f2=(z0ff288db65*)((uintptr_t)SG_INT_MAPPED_BAR((0x16fb+2272-0x1fd9))+zc19a381cf7);*z65093051d7=(0xb7c+818-0xeae);z79f5963ede->zab46142f2e=(0x13b0+1558-0x19c6);z79f5963ede->clear=(0xf38+5326-0x2405);sg_wait_s(z5c3f5520e2);z79f5963ede->clear=(0x557+4734-0x17d5);z2b067ad6f2->zd2888ccec8=z36db795bb0;z2b067ad6f2->z119ae482c7=(0x1d4+8110-0x2182);free(z8227d701d7);return;}SG_INT_ISR_FUNC{sg_fpga_intContext_customData*z8227d701d7=(sg_fpga_intContext_customData*)SG_INT_CUSTOM_DATA;volatile za276549eb0*z79f5963ede;volatile z0ff288db65*z2b067ad6f2;if(z8227d701d7==NULL){return SG_DROP_ISR;}z79f5963ede=(za276549eb0*)z8227d701d7->util_ptr;z2b067ad6f2=(z0ff288db65*)((uintptr_t)SG_INT_MAPPED_BAR((0x10aa+5376-0x25a8))+zc19a381cf7);if((uintptr_t)SG_INT_MAPPED_BAR((0x1448+4017-0x23f7))==(unsigned long)NULL)return SG_DROP_ISR;if(z79f5963ede->event!=(0x143+2363-0xa7e)){z79f5963ede->clear=(0xdeb+5538-0x238c);if(!(SG_INT_IS_POLLING)){z2b067ad6f2->z6759dc6668=z36db795bb0;z2b067ad6f2->zdfbc31d580=z36db795bb0;}z79f5963ede->clear=(0x12a9+2247-0x1b70);return SG_RUN_ISR;}else{return SG_DROP_ISR;}}

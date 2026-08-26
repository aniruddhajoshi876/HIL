// Copyright 2006-2026 Speedgoat GmbH
static const int SG_INT_BARS[]={(0x3a+4743-0x12bf)};
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
#ifndef z36db795bb0
#define z36db795bb0          (0xd50+2378-0x1698)
#endif
typedef struct{volatile uint32_t ISR;volatile uint32_t z2faa57e0eb;volatile uint32_t IER;volatile uint32_t z6759dc6668;volatile uint32_t zdfbc31d580;volatile uint32_t zd2888ccec8;volatile uint32_t zea83b74a38;volatile uint32_t z119ae482c7;volatile uint32_t zae4666333d;volatile uint32_t z1d07e70426;}z0ff288db65;typedef struct{uint32_t zab46142f2e;uint32_t clear;uint32_t event;uint32_t version;uint32_t test1;}za276549eb0;SG_INT_START_FUNC{sg_fpga_intContext_customData*z8227d701d7=(sg_fpga_intContext_customData*)malloc(sizeof(sg_fpga_intContext_customData));if(z8227d701d7==NULL){}
#ifdef SG_AXI_DEVICE_NAME
z8227d701d7->moduleId=SG_INT_MODULE_ID;
#else
z8227d701d7->moduleId=sg_fpga_io3xx_getID(SG_INT_GET_PCIINFO);
#endif
if((0x39a+494-0x588)==z8227d701d7->moduleId){free(z8227d701d7);}uint32_t offset;volatile z0ff288db65*z2b067ad6f2;volatile za276549eb0*z79f5963ede;sg_fpga_io3xx_getCmBaseAddress(z8227d701d7->moduleId,INTA_BASE,&offset);z79f5963ede=(za276549eb0*)((uintptr_t)SG_INT_MAPPED_BAR((0x9c7+7161-0x25be))+offset);z8227d701d7->util_ptr=(void*)z79f5963ede;SG_INT_CUSTOM_DATA=(void*)z8227d701d7;z2b067ad6f2=(z0ff288db65*)((uintptr_t)SG_INT_MAPPED_BAR((0x20dc+450-0x229c))+zc19a381cf7);SG_INT_ENABLE_FPGA_7SERIES_FIX_CI(z36db795bb0);if(!(SG_INT_IS_POLLING)){z2b067ad6f2->z6759dc6668=z36db795bb0;z2b067ad6f2->zdfbc31d580=z36db795bb0;z2b067ad6f2->z119ae482c7=(0x1356+1426-0x18e5);}SG_PRINTF(DEBUG,"\x76\x65\x72\x73\x69\x6f\x6e\x20\x30\x78\x25\x78" "\n",z79f5963ede->version);SG_PRINTF(DEBUG,"\x74\x65\x73\x74\x31\x20\x30\x78\x25\x78" "\n",z79f5963ede->test1);z79f5963ede->clear=(0x5ef+4813-0x18bb);sg_wait_s(z5c3f5520e2);z79f5963ede->clear=(0x35a+5048-0x1712);z79f5963ede->zab46142f2e=z79f5963ede->zab46142f2e|(0x214+5757-0x1890);return;}SG_INT_STOP_FUNC{sg_fpga_intContext_customData*z8227d701d7=(sg_fpga_intContext_customData*)SG_INT_CUSTOM_DATA;volatile z0ff288db65*z2b067ad6f2;volatile za276549eb0*z79f5963ede;z79f5963ede=(za276549eb0*)z8227d701d7->util_ptr;z2b067ad6f2=(z0ff288db65*)((uintptr_t)SG_INT_MAPPED_BAR((0x1232+3492-0x1fd4))+zc19a381cf7);z79f5963ede->zab46142f2e=(0x72+2438-0x9f8);z79f5963ede->clear=(0x130a+3929-0x2262);sg_wait_s(z5c3f5520e2);z79f5963ede->clear=(0xc0b+4659-0x1e3e);z2b067ad6f2->zd2888ccec8=z36db795bb0;z2b067ad6f2->z119ae482c7=(0x28+1122-0x48a);free(z8227d701d7);return;}SG_INT_ISR_FUNC{sg_fpga_intContext_customData*z8227d701d7=(sg_fpga_intContext_customData*)SG_INT_CUSTOM_DATA;volatile za276549eb0*z79f5963ede;volatile z0ff288db65*z2b067ad6f2;if(z8227d701d7==NULL){return SG_DROP_ISR;}z79f5963ede=(za276549eb0*)z8227d701d7->util_ptr;z2b067ad6f2=(z0ff288db65*)((uintptr_t)SG_INT_MAPPED_BAR((0x229+1681-0x8b8))+zc19a381cf7);if((uintptr_t)SG_INT_MAPPED_BAR((0x18bf+3560-0x26a5))==(unsigned long)NULL)return SG_DROP_ISR;if(z79f5963ede->event!=(0x22cf+812-0x25fb)){z79f5963ede->clear=(0x69d+594-0x8ee);if(!(SG_INT_IS_POLLING)){z2b067ad6f2->z6759dc6668=z36db795bb0;z2b067ad6f2->zdfbc31d580=z36db795bb0;}z79f5963ede->clear=(0x1bdf+1947-0x237a);return SG_RUN_ISR;}else{return SG_DROP_ISR;}}

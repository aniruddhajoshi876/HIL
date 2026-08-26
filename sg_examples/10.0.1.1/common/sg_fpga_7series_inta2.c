// Copyright 2006-2026 Speedgoat GmbH
static const int SG_INT_BARS[]={(0x1be0+784-0x1eee)};
#include "sg_blocks/common/libsg/sg_common.h"
#include "sg_blocks/fpga/setup/include/sg_fpga_io3xx_util.h"
#ifdef SG_AXI_DEVICE_NAME
#include "sg_interrupt_config_axi.h"
#else
#include "sg_interrupt_config.h"
#endif
#include "sg_printf.h"
#include <stdint.h>
#define zc19a381cf7               5373952
#ifndef z36db795bb0
#define z36db795bb0          (0xc9b+2717-0x1736)
#endif
typedef struct{volatile uint32_t ISR;volatile uint32_t z2faa57e0eb;volatile uint32_t IER;volatile uint32_t z6759dc6668;volatile uint32_t zdfbc31d580;volatile uint32_t zd2888ccec8;volatile uint32_t zea83b74a38;volatile uint32_t z119ae482c7;volatile uint32_t zae4666333d;volatile uint32_t z1d07e70426;}z0ff288db65;typedef struct{uint32_t enable;uint32_t event;uint32_t clear;uint32_t test1;uint32_t mode[(0x1714+1007-0x1ae3)];uint32_t delay[(0x24c+8038-0x2192)];uint32_t zaa88aaf485[(0x134f+1965-0x1adc)];uint32_t z16203ce901[(0x1266+817-0x1577)];uint32_t zbea9f5f1a5[(0xac9+4664-0x1ce1)];uint32_t zc0011fe779[(0x10d2+2550-0x1aa8)];uint32_t z7294689cde[(0x229+2929-0xd7a)];uint32_t z5541dce2ea[(0x2d+2967-0xba4)];uint32_t z9f1a7be944[(0x40d+3450-0x1167)];uint32_t version;uint32_t ze1a82e7a19;uint32_t z75adbb7c26;}za276549eb0;SG_INT_START_FUNC{sg_fpga_intContext_customData*z8227d701d7=(sg_fpga_intContext_customData*)malloc(sizeof(sg_fpga_intContext_customData));if(z8227d701d7==NULL){}
#ifdef SG_AXI_DEVICE_NAME
z8227d701d7->moduleId=SG_INT_MODULE_ID;
#else
z8227d701d7->moduleId=sg_fpga_io3xx_getID(SG_INT_GET_PCIINFO);
#endif
if((0x12c4+3410-0x2016)==z8227d701d7->moduleId){free(z8227d701d7);}uint32_t offset;sg_fpga_io3xx_getCmBaseAddress(z8227d701d7->moduleId,INTA_BASE,&offset);volatile za276549eb0*z79f5963ede=(za276549eb0*)((uintptr_t)SG_INT_MAPPED_BAR((0x115f+1955-0x1900))+offset);z8227d701d7->util_ptr=(void*)z79f5963ede;SG_INT_CUSTOM_DATA=(void*)z8227d701d7;volatile z0ff288db65*z2b067ad6f2=(z0ff288db65*)((uintptr_t)SG_INT_MAPPED_BAR((0x579+4153-0x15b0))+zc19a381cf7);SG_INT_ENABLE_FPGA_7SERIES_FIX_CI(z36db795bb0);z79f5963ede->clear=4294967295;z79f5963ede->clear=(0x2c+5931-0x1757);if(!(SG_INT_IS_POLLING)){z2b067ad6f2->z6759dc6668=z36db795bb0;z2b067ad6f2->zdfbc31d580=z36db795bb0;z2b067ad6f2->z119ae482c7=(0x1a88+2170-0x22ff);}inta2State_t*z314aa9eeaa;if(io3xxGetPointerInta2StateSgLib(z8227d701d7->moduleId,&z314aa9eeaa)){SG_PRINTF(WARNING,"\x66\x69\x6e\x61\x6c\x69\x7a\x69\x6e\x67\x20\x44\x4d\x41\x20\x69\x6e\x20\x73\x67\x5f\x66\x70\x67\x61\x5f\x37\x73\x65\x72\x69\x65\x73\x5f\x69\x6e\x74\x61\x32\x2e\x63\x3a\x20\x46\x50\x47\x41\x20\x77\x69\x74\x68\x20\x6d\x6f\x64\x75\x6c\x65\x20\x49\x44\x20\x25\x64\x20\x6e\x6f\x74\x20\x66\x6f\x75\x6e\x64" "\n",z8227d701d7->moduleId);}sg_lockMutex(z314aa9eeaa->mutex);if(z79f5963ede->test1==2864403814){sg_printf(sg_debug,"\x49\x4e\x54\x41\x20\x63\x6f\x64\x65\x6d\x6f\x64\x75\x6c\x65\x20\x74\x65\x73\x74\x20\x73\x75\x63\x63\x65\x73\x73\x66\x75\x6c\x6c" "\n");sg_printf(sg_debug,"\x43\x68\x61\x6e\x6e\x65\x6c\x3a\x20\x25\x64" "\n",SG_INT_INTERRUPT_CHANNEL);}z314aa9eeaa->enable|=(1UL<<(SG_INT_INTERRUPT_CHANNEL-(0x13d+8093-0x20d9)));z79f5963ede->enable=z314aa9eeaa->enable;sg_unlockMutex(z314aa9eeaa->mutex);return;}SG_INT_STOP_FUNC{sg_fpga_intContext_customData*z8227d701d7=(sg_fpga_intContext_customData*)SG_INT_CUSTOM_DATA;volatile z0ff288db65*z2b067ad6f2=(z0ff288db65*)((uintptr_t)SG_INT_MAPPED_BAR((0x612+4319-0x16ef))+zc19a381cf7);z2b067ad6f2->zd2888ccec8=z36db795bb0;z2b067ad6f2->z119ae482c7=(0xda4+3533-0x1b71);volatile za276549eb0*z79f5963ede=(za276549eb0*)z8227d701d7->util_ptr;z79f5963ede->enable=(0x1ba5+2866-0x26d7);z79f5963ede->clear=4294967295;z79f5963ede->clear=(0x955+5368-0x1e4d);free(z8227d701d7);return;}SG_INT_ISR_FUNC{sg_fpga_intContext_customData*z8227d701d7=(sg_fpga_intContext_customData*)SG_INT_CUSTOM_DATA;uint32_t event;if(z8227d701d7==NULL){return SG_DROP_ISR;}volatile za276549eb0*z79f5963ede=(za276549eb0*)z8227d701d7->util_ptr;volatile z0ff288db65*z2b067ad6f2=(z0ff288db65*)((uintptr_t)SG_INT_MAPPED_BAR((0x69c+7180-0x22a6))+zc19a381cf7);if(!(uintptr_t)SG_INT_MAPPED_BAR((0x4a0+2112-0xcde)))return SG_DROP_ISR;
#if defined(__QNX__) || defined(__linux__)
event=z79f5963ede->event&(1UL<<(SG_INT_INTERRUPT_CHANNEL-(0x280+370-0x3f1)));
#else
event=z79f5963ede->event;
#endif
if(event!=(0xa19+5254-0x1e9f)){z79f5963ede->clear=event;z79f5963ede->clear=(0x9d1+729-0xcaa);if(!(SG_INT_IS_POLLING)&&(z2b067ad6f2->ISR&z36db795bb0)){z2b067ad6f2->z6759dc6668=z36db795bb0;z2b067ad6f2->zdfbc31d580=z36db795bb0;}return SG_RUN_ISR;}return SG_DROP_ISR;}

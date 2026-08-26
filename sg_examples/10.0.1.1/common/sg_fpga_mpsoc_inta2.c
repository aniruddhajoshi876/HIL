// Copyright 2006-2026 Speedgoat GmbH
static const int SG_INT_BARS[]={(0x4a0+3396-0x11e4),(0x330+9062-0x2694)};
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
#define zc72cf764c2      (0x2573+376-0x268b)
#define z72b0fd0e17 (0x2479+364-0x2595)
#define z9aa61b27a6 (0xfd0+3105-0x1bf0)
#ifndef z36db795bb0
#define z36db795bb0          (0x655+6752-0x20b4)
#endif
typedef struct{volatile uint32_t ISR;volatile uint32_t z2faa57e0eb;volatile uint32_t IER;volatile uint32_t z6759dc6668;volatile uint32_t zdfbc31d580;volatile uint32_t zd2888ccec8;volatile uint32_t zea83b74a38;volatile uint32_t z119ae482c7;volatile uint32_t zae4666333d;volatile uint32_t z1d07e70426;}z0ff288db65;typedef struct{uint32_t enable;uint32_t event;uint32_t clear;uint32_t test1;uint32_t mode[(0x3c5+6278-0x1c2b)];uint32_t delay[(0x1d0+8982-0x24c6)];uint32_t zaa88aaf485[(0x885+6343-0x212c)];uint32_t z16203ce901[(0x147c+3481-0x21f5)];uint32_t zbea9f5f1a5[(0x6db+457-0x884)];uint32_t zc0011fe779[(0xa03+3067-0x15de)];uint32_t z7294689cde[(0x2083+1535-0x2662)];uint32_t z5541dce2ea[(0x156+1180-0x5d2)];uint32_t z9f1a7be944[(0x438+8073-0x23a1)];uint32_t version;uint32_t ze1a82e7a19;uint32_t z75adbb7c26;}za276549eb0;SG_INT_START_FUNC{sg_fpga_intContext_customData*z8227d701d7=(sg_fpga_intContext_customData*)malloc(sizeof(sg_fpga_intContext_customData));if(z8227d701d7==NULL){}
#ifdef SG_AXI_DEVICE_NAME
z8227d701d7->moduleId=SG_INT_MODULE_ID;
#else
z8227d701d7->moduleId=sg_fpga_io3xx_getID(SG_INT_GET_PCIINFO);
#endif
if((0x19c8+1939-0x215b)==z8227d701d7->moduleId){free(z8227d701d7);}uint32_t offset;sg_fpga_io3xx_getCmBaseAddress(z8227d701d7->moduleId,INTA_BASE,&offset);volatile za276549eb0*z79f5963ede=(za276549eb0*)((uintptr_t)SG_INT_MAPPED_BAR((0xebb+4672-0x20f9))+offset);z8227d701d7->util_ptr=(void*)z79f5963ede;SG_INT_CUSTOM_DATA=(void*)z8227d701d7;volatile z0ff288db65*z2b067ad6f2=(z0ff288db65*)((uintptr_t)SG_INT_MAPPED_BAR((0x17fb+358-0x195f))+zc19a381cf7);SG_INT_ENABLE_FPGA_7SERIES_FIX_CI(z36db795bb0);z79f5963ede->clear=4294967295;z79f5963ede->clear=(0xbb2+450-0xd74);if(!(SG_INT_IS_POLLING)){z2b067ad6f2->z6759dc6668=z36db795bb0;z2b067ad6f2->zdfbc31d580=z36db795bb0;z2b067ad6f2->z119ae482c7=(0x12db+4745-0x2561);}inta2State_t*z314aa9eeaa;if(io3xxGetPointerInta2StateSgLib(z8227d701d7->moduleId,&z314aa9eeaa)){SG_PRINTF(WARNING,"\x66\x69\x6e\x61\x6c\x69\x7a\x69\x6e\x67\x20\x44\x4d\x41\x20\x69\x6e\x20\x73\x67\x5f\x66\x70\x67\x61\x5f\x37\x73\x65\x72\x69\x65\x73\x5f\x69\x6e\x74\x61\x32\x2e\x63\x3a\x20\x46\x50\x47\x41\x20\x77\x69\x74\x68\x20\x6d\x6f\x64\x75\x6c\x65\x20\x49\x44\x20\x25\x64\x20\x6e\x6f\x74\x20\x66\x6f\x75\x6e\x64" "\n",z8227d701d7->moduleId);}sg_lockMutex(z314aa9eeaa->mutex);if(z79f5963ede->test1==2864403814){sg_printf(sg_debug,"\x49\x4e\x54\x41\x20\x63\x6f\x64\x65\x6d\x6f\x64\x75\x6c\x65\x20\x74\x65\x73\x74\x20\x73\x75\x63\x63\x65\x73\x73\x66\x75\x6c\x6c" "\n");sg_printf(sg_debug,"\x43\x68\x61\x6e\x6e\x65\x6c\x3a\x20\x25\x64" "\n",SG_INT_INTERRUPT_CHANNEL);}z314aa9eeaa->enable|=(1UL<<(SG_INT_INTERRUPT_CHANNEL-(0xd9c+579-0xfde)));z79f5963ede->enable=z314aa9eeaa->enable;sg_unlockMutex(z314aa9eeaa->mutex);volatile uint32_t*z65093051d7=(uint32_t*)(SG_INT_MAPPED_BAR((0x520+3393-0x1261))+zc72cf764c2);volatile uint32_t*zc1156e3f7d=(uint32_t*)(SG_INT_MAPPED_BAR((0x8ec+6667-0x22f7))+z72b0fd0e17);*z65093051d7=(0xfa9+3751-0x1e4f);*zc1156e3f7d=z9aa61b27a6;return;}SG_INT_STOP_FUNC{sg_fpga_intContext_customData*z8227d701d7=(sg_fpga_intContext_customData*)SG_INT_CUSTOM_DATA;volatile uint32_t*z65093051d7=(uint32_t*)(SG_INT_MAPPED_BAR((0x6b7+3988-0x164b))+zc72cf764c2);*z65093051d7=(0x1002+5004-0x238e);volatile z0ff288db65*z2b067ad6f2=(z0ff288db65*)((uintptr_t)SG_INT_MAPPED_BAR((0x1397+2575-0x1da4))+zc19a381cf7);z2b067ad6f2->zd2888ccec8=z36db795bb0;z2b067ad6f2->z119ae482c7=(0xbf3+6619-0x25ce);volatile za276549eb0*z79f5963ede=(za276549eb0*)z8227d701d7->util_ptr;z79f5963ede->enable=(0x2180+1371-0x26db);z79f5963ede->clear=4294967295;z79f5963ede->clear=(0x651+3530-0x141b);free(z8227d701d7);return;}SG_INT_ISR_FUNC{sg_fpga_intContext_customData*z8227d701d7=(sg_fpga_intContext_customData*)SG_INT_CUSTOM_DATA;uint32_t event;if(z8227d701d7==NULL){return SG_DROP_ISR;}volatile za276549eb0*z79f5963ede=(za276549eb0*)z8227d701d7->util_ptr;volatile z0ff288db65*z2b067ad6f2=(z0ff288db65*)((uintptr_t)SG_INT_MAPPED_BAR((0x1648+3173-0x22ab))+zc19a381cf7);if(!(uintptr_t)SG_INT_MAPPED_BAR((0x1211+3582-0x200d)))return SG_DROP_ISR;
#if defined(__QNX__) || defined(__linux__)
event=z79f5963ede->event&(1UL<<(SG_INT_INTERRUPT_CHANNEL-(0x169b+1556-0x1cae)));
#else
event=z79f5963ede->event;
#endif
if(event!=(0x275+7568-0x2005)){z79f5963ede->clear=event;z79f5963ede->clear=(0x1707+3724-0x2593);if(!(SG_INT_IS_POLLING)&&(z2b067ad6f2->ISR&z36db795bb0)){z2b067ad6f2->z6759dc6668=z36db795bb0;z2b067ad6f2->zdfbc31d580=z36db795bb0;}return SG_RUN_ISR;}return SG_DROP_ISR;}

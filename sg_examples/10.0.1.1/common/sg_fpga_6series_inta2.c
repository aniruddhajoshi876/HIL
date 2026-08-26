// Copyright 2006-2026 Speedgoat GmbH
static const int SG_INT_BARS[]={(0x5ac+4029-0x1567)};
#include "sg_blocks/common/libsg/sg_common.h"
#include "sg_blocks/fpga/setup/include/sg_fpga_io3xx_util.h"
#include "sg_interrupt_config.h"
#include "sg_printf.h"
#include <stdint.h>
typedef struct{uint32_t enable;uint32_t event;uint32_t clear;uint32_t test1;uint32_t mode[(0x2345+438-0x24db)];uint32_t delay[(0x18ff+1557-0x1ef4)];uint32_t zaa88aaf485[(0x1f2+8887-0x2489)];uint32_t z16203ce901[(0x696+3693-0x14e3)];uint32_t zbea9f5f1a5[(0x10ed+2739-0x1b80)];uint32_t zc0011fe779[(0x2597+243-0x266a)];uint32_t z7294689cde[(0x1bcd+2569-0x25b6)];uint32_t z5541dce2ea[(0x1ca+1599-0x7e9)];uint32_t z9f1a7be944[(0x1a7+4453-0x12ec)];uint32_t version;uint32_t ze1a82e7a19;uint32_t z75adbb7c26;}za276549eb0;SG_INT_START_FUNC{sg_fpga_intContext_customData*z8227d701d7=(sg_fpga_intContext_customData*)malloc(sizeof(sg_fpga_intContext_customData));if(z8227d701d7==NULL){}
#ifdef SG_AXI_DEVICE_NAME
z8227d701d7->moduleId=SG_INT_MODULE_ID;
#else
z8227d701d7->moduleId=sg_fpga_io3xx_getID(SG_INT_GET_PCIINFO);
#endif
if((0x1a64+42-0x1a8e)==z8227d701d7->moduleId){free(z8227d701d7);}uint32_t offset;sg_fpga_io3xx_getCmBaseAddress(z8227d701d7->moduleId,INTA_BASE,&offset);volatile za276549eb0*z79f5963ede=(za276549eb0*)((uintptr_t)SG_INT_MAPPED_BAR((0x215+6200-0x1a4b))+offset);z8227d701d7->util_ptr=(void*)z79f5963ede;SG_INT_CUSTOM_DATA=(void*)z8227d701d7;SG_INT_ENABLE_FPGA_6SERIES_INTAV2_FIX();z79f5963ede->clear=4294967295;z79f5963ede->clear=(0x494+3707-0x130f);inta2State_t*z314aa9eeaa;if(io3xxGetPointerInta2StateSgLib(z8227d701d7->moduleId,&z314aa9eeaa)){SG_PRINTF(WARNING,"\x66\x69\x6e\x61\x6c\x69\x7a\x69\x6e\x67\x20\x44\x4d\x41\x20\x69\x6e\x20\x73\x67\x5f\x66\x70\x67\x61\x5f\x36\x73\x65\x72\x69\x65\x73\x5f\x69\x6e\x74\x61\x32\x2e\x63\x3a\x20\x46\x50\x47\x41\x20\x77\x69\x74\x68\x20\x6d\x6f\x64\x75\x6c\x65\x20\x49\x44\x20\x25\x64\x20\x6e\x6f\x74\x20\x66\x6f\x75\x6e\x64" "\n",z8227d701d7->moduleId);}sg_lockMutex(z314aa9eeaa->mutex);if(z79f5963ede->test1==2864403814){sg_printf(sg_debug,"\x49\x4e\x54\x41\x20\x63\x6f\x64\x65\x6d\x6f\x64\x75\x6c\x65\x20\x74\x65\x73\x74\x20\x73\x75\x63\x63\x65\x73\x73\x66\x75\x6c\x6c" "\n");sg_printf(sg_debug,"\x43\x68\x61\x6e\x6e\x65\x6c\x3a\x20\x25\x64" "\n",SG_INT_INTERRUPT_CHANNEL);}z314aa9eeaa->enable|=(1UL<<(SG_INT_INTERRUPT_CHANNEL-(0x3d1+637-0x64d)));z79f5963ede->enable=z314aa9eeaa->enable;sg_unlockMutex(z314aa9eeaa->mutex);return;}SG_INT_STOP_FUNC{sg_fpga_intContext_customData*z8227d701d7=(sg_fpga_intContext_customData*)SG_INT_CUSTOM_DATA;volatile za276549eb0*z79f5963ede=(za276549eb0*)z8227d701d7->util_ptr;z79f5963ede->enable=(0xb28+6040-0x22c0);z79f5963ede->clear=4294967295;z79f5963ede->clear=(0x1641+721-0x1912);free(z8227d701d7);return;}SG_INT_ISR_FUNC{sg_fpga_intContext_customData*z8227d701d7=(sg_fpga_intContext_customData*)SG_INT_CUSTOM_DATA;uint32_t event;if(z8227d701d7==NULL){return SG_DROP_ISR;}volatile za276549eb0*z79f5963ede=(za276549eb0*)z8227d701d7->util_ptr;if(!(uintptr_t)SG_INT_MAPPED_BAR((0x95c+2694-0x13e0)))return SG_DROP_ISR;
#if defined(__QNX__)
event=z79f5963ede->event&(1UL<<(SG_INT_INTERRUPT_CHANNEL-(0x185+367-0x2f3)));
#elif defined(__linux__)
event=z79f5963ede->ze1a82e7a19&(1UL<<(SG_INT_INTERRUPT_CHANNEL-(0x1f38+1329-0x2468)));
#else
event=z79f5963ede->event;
#endif
if(event!=(0x1fe2+200-0x20aa)){
#ifndef __linux__
z79f5963ede->clear=event;z79f5963ede->clear=(0x1d68+309-0x1e9d);
#endif
return SG_RUN_ISR;}else{return SG_DROP_ISR;}}

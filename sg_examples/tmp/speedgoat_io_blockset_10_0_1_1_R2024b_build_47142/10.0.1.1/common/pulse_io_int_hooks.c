// Copyright 2006-2026 Speedgoat GmbH

#define SG_INT_PREFIX   Pulse_IO
#define SG_AXI_DEVICE_NAME "\x66\x70\x67\x61\x5f\x66\x61\x62\x72\x69\x63\x5f\x35"  
static const int SG_INT_BARS[]={(0xb80+6070-0x2334)};
#include <stdint.h>
#include "sg_blocks/common/libsg/sg_common.h"
#include "sg_blocks/fpga/setup/include/sg_fpga_io3xx_util.h"
#include "sg_interrupt_config_axi.h"
#define zc19a381cf7       5373952
#define z5c3f5520e2   (0.000001)
typedef struct{uint32_t zab46142f2e;uint32_t clear;uint32_t event;uint32_t version;uint32_t test1;}za276549eb0;SG_INT_START_FUNC{sg_fpga_intContext_customData*z8227d701d7=(sg_fpga_intContext_customData*)malloc(sizeof(sg_fpga_intContext_customData));if(z8227d701d7==NULL){}z8227d701d7->moduleId=SG_INT_MODULE_ID;if((0x12bb+5036-0x2667)==z8227d701d7->moduleId){free(z8227d701d7);}uint32_t offset;volatile za276549eb0*z79f5963ede;sg_fpga_io3xx_getCmBaseAddress(z8227d701d7->moduleId,INTA_BASE,&offset);z79f5963ede=(za276549eb0*)((uintptr_t)SG_INT_MAPPED_BAR((0x5fd+2742-0x10b1))+offset);z8227d701d7->util_ptr=(void*)z79f5963ede;SG_INT_CUSTOM_DATA=(void*)z8227d701d7;SG_PRINTF(DEBUG,"\x76\x65\x72\x73\x69\x6f\x6e\x20\x30\x78\x25\x78" "\n",z79f5963ede->version);SG_PRINTF(DEBUG,"\x74\x65\x73\x74\x31\x20\x30\x78\x25\x78" "\n",z79f5963ede->test1);z79f5963ede->clear=(0xbe8+4174-0x1c35);sg_wait_s(z5c3f5520e2);z79f5963ede->clear=(0x642+759-0x939);z79f5963ede->zab46142f2e=z79f5963ede->zab46142f2e|(0x13fa+978-0x17cb);return;}SG_INT_STOP_FUNC{sg_fpga_intContext_customData*z8227d701d7=(sg_fpga_intContext_customData*)SG_INT_CUSTOM_DATA;volatile za276549eb0*z79f5963ede;z79f5963ede=(za276549eb0*)z8227d701d7->util_ptr;z79f5963ede->zab46142f2e=(0x2bc+5939-0x19ef);z79f5963ede->clear=(0xe88+5277-0x2324);z79f5963ede->clear=(0x8cd+1930-0x1057);free(z8227d701d7);return;}SG_INT_ISR_FUNC{sg_fpga_intContext_customData*z8227d701d7=(sg_fpga_intContext_customData*)SG_INT_CUSTOM_DATA;volatile za276549eb0*z79f5963ede;if(z8227d701d7==NULL){return SG_DROP_ISR;}z79f5963ede=(za276549eb0*)z8227d701d7->util_ptr;if((uintptr_t)SG_INT_MAPPED_BAR((0xff+4084-0x10f1))==(unsigned long)NULL){return SG_DROP_ISR;}if(z79f5963ede->event!=(0x6b0+912-0xa40)){z79f5963ede->clear=(0xcef+1899-0x1459);z79f5963ede->clear=(0x186b+44-0x1897);return SG_RUN_ISR;}return SG_DROP_ISR;}

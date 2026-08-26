// Copyright 2006-2026 Speedgoat GmbH
static const int SG_INT_BARS[]={};
#ifdef SG_AXI_DEVICE_NAME
#include "sg_interrupt_config_axi.h"
#else
#include "sg_interrupt_config.h"
#endif
#include <stdint.h>
#include "sg_printf.h"
#include "sg_fpga_io3xx_scatter_gather_dma.h"
#include "sg_fpga_io3xx_util.h"
SG_INT_START_FUNC{sg_fpga_intContext_customData*z8227d701d7=(sg_fpga_intContext_customData*)malloc(sizeof(sg_fpga_intContext_customData));
#ifdef SG_AXI_DEVICE_NAME
z8227d701d7->moduleId=SG_INT_MODULE_ID;
#else
z8227d701d7->moduleId=sg_fpga_io3xx_getID(SG_INT_GET_PCIINFO);
#endif
if((0x2221+1204-0x26d5)==z8227d701d7->moduleId){free(z8227d701d7);SG_PRINTF(ERROR,"\x46\x50\x47\x41\x20\x62\x61\x73\x65\x64\x20\x69\x6e\x74\x65\x72\x72\x75\x70\x74\x3a\x20\x46\x50\x47\x41\x20\x49\x4f\x20\x6d\x6f\x64\x75\x6c\x65\x20\x77\x61\x73\x20\x6e\x6f\x74\x20\x66\x6f\x75\x6e\x64\x20\x69\x6e\x20\x74\x68\x65\x20\x6d\x6f\x64\x75\x6c\x65\x2d\x72\x65\x67\x69\x73\x74\x72\x79\x20" "\n");}io3xx_sgdma_finalizeDmaController(z8227d701d7->moduleId);ScatterGatherDmaState*z50b84cc2b5;if(sg_fpga_io3xx_getSharedSgDmaState(z8227d701d7->moduleId,&z50b84cc2b5)){SG_PRINTF(WARNING,"\x66\x69\x6e\x61\x6c\x69\x7a\x69\x6e\x67\x20\x44\x4d\x41\x20\x69\x6e\x20\x66\x70\x67\x61\x5f\x70\x6f\x6c\x6c\x69\x6e\x67\x5f\x69\x6e\x74\x5f\x68\x6f\x6f\x6b\x73\x2e\x63\x3a\x20\x46\x50\x47\x41\x20\x77\x69\x74\x68\x20\x6d\x6f\x64\x75\x6c\x65\x20\x49\x44\x20\x25\x64\x20\x6e\x6f\x74\x20\x66\x6f\x75\x6e\x64" "\n",z8227d701d7->moduleId);}if(!z50b84cc2b5->enableDma||!z50b84cc2b5->useFpgaDmaController){SG_PRINTF(ERROR,"\x46\x50\x47\x41\x20\x62\x61\x73\x65\x64\x20\x69\x6e\x74\x65\x72\x72\x75\x70\x74\x3a\x20\x4f\x70\x74\x69\x6d\x69\x7a\x65\x64\x20\x44\x61\x74\x61\x20\x54\x72\x61\x6e\x73\x66\x65\x72\x20\x6e\x6f\x74\x20\x65\x6e\x61\x62\x6c\x65\x64\x20\x69\x6e\x20\x49\x4f\x33\x78\x78\x20\x53\x65\x74\x75\x70\x20\x62\x6c\x6f\x63\x6b\x20\x66\x6f\x72\x20\x6d\x6f\x64\x75\x6c\x65\x20\x49\x44\x20\x25\x64" "\n",z8227d701d7->moduleId);}z8227d701d7->cycleCounterPtr=z50b84cc2b5->intPollCounterPtr;*z8227d701d7->cycleCounterPtr=(0x417+6787-0x1e9a);SG_INT_CUSTOM_DATA=(void*)z8227d701d7;z8227d701d7->cycleCounter_old=*z8227d701d7->cycleCounterPtr;io3xx_sgdma_startDmaController(z8227d701d7->moduleId);}SG_INT_ISR_FUNC{sg_fpga_intContext_customData*z8227d701d7=(sg_fpga_intContext_customData*)SG_INT_CUSTOM_DATA;if(z8227d701d7==NULL)return SG_DROP_ISR;if(*z8227d701d7->cycleCounterPtr!=z8227d701d7->cycleCounter_old){z8227d701d7->cycleCounter_old=*z8227d701d7->cycleCounterPtr;return SG_RUN_ISR;}return SG_DROP_ISR;}SG_INT_STOP_FUNC{sg_fpga_intContext_customData*z8227d701d7=(sg_fpga_intContext_customData*)SG_INT_CUSTOM_DATA;io3xx_sgdma_stopDmaController(z8227d701d7->moduleId);free(z8227d701d7);}

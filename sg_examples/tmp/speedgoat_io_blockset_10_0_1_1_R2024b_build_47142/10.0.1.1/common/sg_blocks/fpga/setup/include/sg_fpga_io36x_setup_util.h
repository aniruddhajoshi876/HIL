#ifndef __SG_FPGA_IO36x_SETUP_UTIL_H__
#define __SG_FPGA_IO36x_SETUP_UTIL_H__

#ifdef __cplusplus
extern "C" 
{
#endif

#include <stdint.h>
#include "sg_fpga_setup_util.h"
#include "sg_fpga_io3xx_util.h"

#ifndef         MATLAB_MEX_FILE
uint32_t IO36x_programmFPGA(char *devname, int16_t bus, int16_t slot, uint32_t deviceID, uint32_t moduleID, uint32_t bitstreamlength, uint8_t *bitstream,  sg_fpga_io3xxModuleIdT* moduleId, const uint32_t *io36xFront, uint32_t dirFront);
uint32_t sg_zynq_programmFPGA(char *devname, int16_t bus, int16_t slot, uint32_t deviceID, uint32_t moduleID, uint32_t bitstreamlength, uint8_t *bitstream, sg_fpga_io3xxModuleIdT* moduleId);

/*****************************************************************************
 * PCIe endpoint in IO36x is different than other modules, for DMA to work,
 * use these methods after allocation to store the pointers.
 *****************************************************************************/
int sg_io36xSetEgressPointers(int32_t moduleId, int egressIndex, void **egressPhysical,void **egressVirtual);
void *sg_io36xGetEgressPointers(int32_t moduleId, int egressIndex, void **egressPhysical);
void* sg_io3xxGetUtilityBarAddress(int32_t module_identifier);

int sg_io36xSetBar2IngressDestinationAddress(int32_t moduleId, uint64_t newDestAddress);

#endif

#ifdef __cplusplus
}
#endif 

#endif //__SG_FPGA_IO36x_SETUP_UTIL_H__
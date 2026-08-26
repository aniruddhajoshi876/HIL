#ifndef __SG_FPGA_IO337_SETUP_UTIL_H__
#define __SG_FPGA_IO337_SETUP_UTIL_H__

#ifdef __cplusplus
extern "C" 
{
#endif

#include <stdint.h>
#include "sg_fpga_setup_util.h"
#include "sg_fpga_io3xx_util.h"

#ifndef         MATLAB_MEX_FILE
uint32_t IO337_programmFPGA(char *devname, int16_t bus, int16_t slot, uint32_t deviceID, uint32_t moduleID, uint32_t bitstreamlength, uint8_t *bitstream, uint32_t pull_settings, uint32_t diff_settings, sg_fpga_io3xxModuleIdT* moduleIdentifierStruct);
#endif

#ifdef __cplusplus
}
#endif 

#endif //__SG_FPGA_IO337_SETUP_UTIL_H__
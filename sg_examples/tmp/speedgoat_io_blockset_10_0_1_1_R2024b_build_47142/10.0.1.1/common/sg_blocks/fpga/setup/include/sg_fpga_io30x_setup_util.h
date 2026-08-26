#ifndef __SG_FPGA_IO30X_SETUP_UTIL_H__
#define __SG_FPGA_IO30X_SETUP_UTIL_H__

#ifdef __cplusplus
extern "C" 
{
#endif

#include <stdint.h>
#include "sg_fpga_setup_util.h"
#include "sg_fpga_io3xx_util.h"
// functions to map I/O module memory
int32_t IO30x_programFPGA(char *devname, int16_t bus, int16_t slot, int32_t deviceID, int32_t moduleID, uint32_t IO30x_ProgSpiFlash, uint32_t bitstreamlength, uint32_t *bitstream,sg_fpga_io3xxModuleIdT* moduleId, uint32_t timestamp);

#ifdef __cplusplus
}
#endif

#endif

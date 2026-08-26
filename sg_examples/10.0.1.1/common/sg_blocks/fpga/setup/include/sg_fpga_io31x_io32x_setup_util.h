#ifndef __SG_FPGA_IO31X_IO32X_SETUP_UTIL_H__
#define __SG_FPGA_IO31X_IO32X_SETUP_UTIL_H__

#ifdef __cplusplus
extern "C" 
{
#endif

#include <stdint.h>
#include "sg_fpga_setup_util.h"
#include "sg_fpga_io3xx_util.h"

// functions to map I/O module memory
int32_t IO324_programmFPGA(char *devname, int16_t bus, int16_t slot, int32_t deviceID,
                           int32_t moduleID, uint32_t IO31x_IO32x_ProgSpiFlash,
                           uint32_t bitstreamlength, uint8_t *bitstream, uint32_t timestamp_param,
                           sg_fpga_io3xxModuleIdT *moduleId, uint32_t pull, uint32_t diffSettings);
int32_t IO31x_IO32x_programmFPGA(char *devname, int16_t bus, int16_t slot, int32_t deviceID,
                                 int32_t moduleID, uint32_t IO31x_IO32x_ProgSpiFlash,
                                 uint32_t bitstreamlength, uint8_t *bitstream,
                                 sg_fpga_io3xxModuleIdT *moduleId, uint32_t pull, uint32_t timestamp);  

#ifdef __cplusplus
}
#endif

#endif

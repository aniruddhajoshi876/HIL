#ifndef __SG_FPGA_IO3XX_SETUP_UTIL_H__
#define __SG_FPGA_IO3XX_SETUP_UTIL_H__

#ifdef __cplusplus
extern "C" 
{
#endif

#include <stdint.h>
#include "sg_fpga_setup_util.h"
#include "sg_fpga_io3xx_util.h"

/*****************************************************************************
 * IO331 function prototypes
 *****************************************************************************/
#ifndef         MATLAB_MEX_FILE
int32_t IO331_programmFPGA(char *devname, int16_t bus, int16_t slot, int32_t deviceID, int32_t moduleID, uint32_t bitstreamlength, uint32_t *bitstream, sg_fpga_io3xxModuleIdT *moduleId);
#endif
  
/*****************************************************************************
 * IO332 function prototypes
 *****************************************************************************/
#ifndef         MATLAB_MEX_FILE
  int32_t IO332_programmFPGA(char *devname, int16_t bus, int16_t slot, int32_t deviceID, int32_t moduleID, uint32_t bitstreamlength, uint32_t *bitstream, uint32_t timestamp_param, sg_fpga_io3xxModuleIdT *moduleId);
#endif  
  
/*****************************************************************************
 * IO333 function prototypes
 *****************************************************************************/
#ifndef         MATLAB_MEX_FILE
  int32_t IO333_programmFPGA(char *devname, int16_t bus, int16_t slot, int32_t deviceID, int32_t moduleID, uint32_t bitstreamlength, uint32_t *bitstream, uint32_t timestamp_param, sg_fpga_io3xxModuleIdT *moduleId);
#endif

#ifdef __cplusplus
}
#endif

#endif

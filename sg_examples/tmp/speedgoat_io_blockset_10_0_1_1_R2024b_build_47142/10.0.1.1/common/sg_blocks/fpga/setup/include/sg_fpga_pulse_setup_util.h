#ifndef SG_FPGA_PULSE_SETUP_H
#define SG_FPGA_PULSE_SETUP_H

#include <stdint.h>
#include "sg_fpga_setup_util.h"
#include "sg_fpga_io3xx_util.h"

#ifdef __cplusplus
extern "C" {
#endif

// Function Prototypes
int sg_pulse_programFpga(const char *moduleName, int deviceId, int moduleId,
                          const char *bitstreamFile, uint32_t bitstreamTimestamp);

#ifdef __cplusplus
}
#endif

#endif // SG_FPGA_PULSE_SETUP_H

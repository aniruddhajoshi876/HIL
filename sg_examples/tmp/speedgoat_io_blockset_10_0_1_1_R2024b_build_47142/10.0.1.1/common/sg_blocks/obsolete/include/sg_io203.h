#pragma once

#include <stdint.h>

// General module information
#define DEVNAME "Speedgoat IO203"
#define VENDORID 0x1498
#define DEVICEID 0x02A9

// Device structure to store in module registry
#ifndef MATLAB_MEX_FILE
    #include "sg_common.h"
    typedef struct {
        sg_PCIDevice pciinfo;
        volatile uint32_t *ioaddress0;
        volatile uint32_t * ioaddress2;
        uint32_t outEnLo;
        uint32_t outEnHi;
    } Io203_Device_t;
#endif //MATLAB_MEX_FILE

#ifndef __MB_LICENSE_H
#define __MB_LICENSE_H

#include "stdint.h"
#include "mb_def.h"

#define MBTCP_CLIENT_KEY     "Modbus TCP Client"
#define MBTCP_SERVER_KEY     "Modbus TCP Server"
#define MBRTU_CLIENT_KEY     "Modbus RTU Client"
#define MBRTU_SERVER_KEY     "Modbus RTU Server"

extern int32_t checkLicense(uint32_t ModuleType);
extern int32_t initLicense();

#endif

#ifndef SG_IO682_V3_H
#define SG_IO682_V3_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

#include "sg_error.h"
#include "sg_param.h"
#include "sg_printf.h"
#include "../../arinc429/lib/sg_IO682/include/cdev_api.h"

#define PROT_ERROR_HI		 1
#define PROT_ERROR_LO		 2
#define PROT_ERROR_SHORT_GAP 3
#define PROT_ERROR_NONE		 4

#define MIN_BITRATE_ARX				105
#define MAX_BITRATE_ARX				79998

typedef struct
{
    uint32_t word;
    uint32_t time;
} Io682_ArincMsg_t;

extern int io682_configPciAddresses(int deviceId, int16_t bus, int16_t slot, int moduleId,
    int boardId, char *err);
extern int io682_initArincApi(int boardId, char *err);
extern int io682_setConcurrencyMode(int boardId, char *err);
extern int io682_setTimerRate(int boardId, int timeSource, int timerRate);
extern int io682_startDriver(int boardId, char *err);

#ifdef __cplusplus
}
#endif

#endif  // SG_IO682_V3_H

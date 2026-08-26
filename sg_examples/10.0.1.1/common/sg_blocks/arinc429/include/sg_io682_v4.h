#ifndef SG_IO682_V4_H
#define SG_IO682_V4_H

#include <stdint.h>

#include "sg_error.h"
#include "sg_param.h"
#include "sg_printf.h"

#define PROT_ERROR_HI		 1
#define PROT_ERROR_LO		 2
#define PROT_ERROR_SHORT_GAP 3
#define PROT_ERROR_NONE		 4

#define SG_BLOCK_TYPE_IO682_RECEIVE     6821
#define SG_BLOCK_TYPE_IO682_SEND        6822
#define SG_BLOCK_TYPE_IO682_SCHED_MSG   6823

extern int io682_configPciAddresses(int deviceId, const SgParam_IntVec *pciSlotParam, int moduleId,
    int boardId, SgError *err);
extern int io682_initArincApi(int boardId, SgError *err);
extern int io682_setConcurrencyMode(int boardId, SgError *err);
extern int io682_configChannels(SimStruct *S, int moduleId, SgError *err, const mxArray *sFcnParamInConfig, const mxArray *sFcnParamOutConfig);
extern int io682_configScheduler(SimStruct *S, int moduleId, SgError *err, const mxArray *sFcnParamSchedMsg);
extern int io682_setTimerRate(int boardId, int timeSource, int timerRate);
extern int io682_startDriver(int boardId, SgError *err);

#endif  // SG_IO682_V4_H

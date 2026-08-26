#ifndef __PNM_API_H
#define __PNM_API_H

/* Includes */
#include "cifxapi.h"
#include "sg_common.h"
#include "stdint.h"

#define PNM_RECORD_BLOCK_TYPE_READ  0
#define PNM_RECORD_BLOCK_TYPE_WRITE 1

#define PNM_RECORD_MAX_DATA_LEN 1500

#define PNM_MAX_NUM_SUBMODULES 2048
#define PNM_MAX_NUM_RECORDS    PNM_MAX_NUM_SUBMODULES

typedef struct t_PNM_SUBMODULES {
    uint16_t DeviceIndex;
    uint32_t Api;
    uint16_t Slot;
    uint16_t SubSlot;
    uint16_t Handle;
} PNM_SUBMODULE_T;

typedef struct t_PNM_RECORD {
    uint32_t ID;
    uint16_t Index;
    uint32_t Error;
    uint8_t State;
    uint8_t BlockType;
    uint32_t DataLen;
    uint32_t MaxDataLen;
    uint32_t Time;
    uint32_t Timeout;

    PNM_SUBMODULE_T *SubModule;

    uint8_t Data[PNM_RECORD_MAX_DATA_LEN];

} PNM_RECORD_T;

typedef struct t_PNM_PARAM {
    PNM_RECORD_T Records[PNM_MAX_NUM_RECORDS];
    PNM_SUBMODULE_T SubModules[PNM_MAX_NUM_SUBMODULES];
    uint32_t NumSubModules;
    uint32_t NumRecords;
    uint32_t RecordBaton;
    bool OptAcyclic;

} PNM_PARAM_T;

#ifdef __cplusplus
extern "C" {
#endif

int32_t PNM_AddRecord(CIFX_CHANNEL_T *Channel, uint16_t Index, uint16_t DeviceIndex, uint32_t Api,
                      uint16_t Slot, uint16_t SubSlot, uint32_t MaxDataLen, uint8_t BlockType,
                      PNM_RECORD_T **Record);
int32_t PNM_UpdateRecord(PNM_RECORD_T *Record, bool *EnablePort, uint32_t *StatusPort,
                         uint32_t *ErrorPort, uint32_t *DataLenPort, void *DataPort);
int32_t PNM_IndicationHandler(CIFX_CHANNEL_T *Channel);
int32_t PNM_RecordHandler(CIFX_CHANNEL_T *Channel);

#ifdef __cplusplus
}
#endif

#endif
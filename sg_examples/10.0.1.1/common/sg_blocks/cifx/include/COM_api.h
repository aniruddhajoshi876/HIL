#ifndef __COM_API_H
#define __COM_API_H

/* Includes */
#include "stdint.h"
#include "sg_common.h"

#define COM_SDO_BLOCK_TYPE_READ     0
#define COM_SDO_BLOCK_TYPE_WRITE     1

#define COM_SDO_MAX_DATA_LEN             512
#define COM_NMT_MAX_NUM_NODES           127

typedef struct t_COM_SDO
{
    uint32_t NumBlocks;
    uint32_t BlockId;
    uint32_t CanNodeId;
    uint32_t Index;
    uint32_t SubIndex;
    uint32_t Error;
    uint8_t State;
    uint8_t BlockType;
    uint32_t DataLen;
    uint8_t Data[COM_SDO_MAX_DATA_LEN];

} COM_SDO_T;

typedef struct t_COM_NMT
{
    uint32_t NumNodes;
    uint32_t CurrentNodeIdx;
    uint32_t Nodes[COM_NMT_MAX_NUM_NODES];
    uint32_t States[COM_NMT_MAX_NUM_NODES];
    uint32_t Triggers[COM_NMT_MAX_NUM_NODES];

} COM_NMT_T;

typedef struct t_COM_PARAM
{
    COM_SDO_T Sdo;
    COM_NMT_T Nmt;

} COM_PARAM_T;

#ifdef __cplusplus
extern "C" {
#endif

int32_t COM_AcyclicHandler(CIFX_CHANNEL_T *Channel);
int32_t COM_SdoAddBlock(CIFX_CHANNEL_T *Channel, uint32_t *BlockId);

int32_t COM_SdoUpdateBlock(
    CIFX_CHANNEL_T* Channel,
    uint8_t BlockType,
    uint32_t BlockId,
    bool* Enable,
    uint32_t CanNodeId,
    uint32_t Index,
    uint32_t SubIndex,
    uint32_t* Status,
    uint32_t* Error,
    uint32_t DataLen,
    void* Data);

#ifdef __cplusplus
}
#endif

#endif
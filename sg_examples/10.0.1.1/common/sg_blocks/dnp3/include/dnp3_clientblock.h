#ifndef __DNP3_CLIENTBLOCK_H
#define __DNP3_CLIENTBLOCK_H

#include "stdint.h"

namespace dnp3
{
    typedef struct t_CLIENT_BLOCK
    {
        uint32_t Type;
        uint32_t Group;
        uint32_t Variation;
        uint32_t FcnCode;
        uint32_t DataType;
        uint32_t NumBytes;
        uint32_t NumBits;
        uint32_t PointIdx;
        uint32_t PointQty;
        uint32_t HostFlagsTx;
        uint32_t DevFlagsTx;
        uint32_t HostFlagsRx;
        uint32_t DevFlagsRx;

        uint64_t Value[1024];
        uint8_t Flag[1024];
        uint64_t Time[1024];
        uint64_t Time2[1024];

        void* Parent;

    } CLIENT_BLOCK_T;
}

#endif

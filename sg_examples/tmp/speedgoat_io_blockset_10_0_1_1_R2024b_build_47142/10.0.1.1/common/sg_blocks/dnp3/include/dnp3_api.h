#ifndef DNP3_API_H_
#define DNP3_API_H_

#include "stdint.h"

#define DNP3_MAX_NUM_BLOCKS     1024

#define DNP3_STATION_TYPE_UNDEF      0x00000000
#define DNP3_STATION_TYPE_CLIENT     0x00000001
#define DNP3_STATION_TYPE_SERVER 0x00000002

#define DNP3_BLOCK_TYPE_UNDEF   0x00000000
#define DNP3_BLOCK_TYPE_SETUP   0x00000001
#define DNP3_BLOCK_TYPE_COMMAND 0x00000002
#define DNP3_BLOCK_TYPE_POINT   0x00000003

#define DNP3_PORT_TYPE_VALUE    1
#define DNP3_PORT_TYPE_FLAG     2
#define DNP3_PORT_TYPE_TIME     3
#define DNP3_PORT_TYPE_ENABLE   4
#define DNP3_PORT_TYPE_NEWDATA  5
#define DNP3_PORT_TYPE_TON      6
#define DNP3_PORT_TYPE_TOFF     7
#define DNP3_PORT_TYPE_CTRLCODE 8
#define DNP3_PORT_TYPE_COUNT    9

namespace dnp3
{
    typedef struct t_DNP3_DATA_1201
    {
        uint8_t ControlCode;
        uint8_t Count;
        uint32_t TimeOn;
        uint32_t TimeOff;

    } DNP3_DATA_1201_T;

    typedef struct t_DNP3_DATA_6022
    {
        uint8_t Group;
        uint16_t StartIdx;
        uint16_t StopIdx;
        uint8_t Class;

    } DNP3_DATA_6022_T;   
}

#endif
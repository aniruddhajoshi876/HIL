#ifndef __OPCUA_DEF_H
#define __OPCUA_DEF_H

#include <stdint.h>

#pragma pack(push, 1)

#ifndef MATLAB_MEX_FILE

#ifndef NULL
#ifdef __cplusplus
#define NULL 0
#else
#define NULL ((void *)0)
#endif
#endif

#endif

#define OPCUA_MODULE_TYPE_UNDEF   0
#define OPCUA_STATION_TYPE_CLIENT 1
#define OPCUA_STATION_TYPE_SERVER 2

#define OPCUA_BLOCK_TYPE_UNDEF        0x00000000
#define OPCUA_BLOCK_TYPE_CLIENT_READ  0x00000004
#define OPCUA_BLOCK_TYPE_CLIENT_WRITE 0x00000005

#define OPCUA_IDLE_DELAY   100000
#define OPCUA_CLIENT_RETRY 1000 // milliseconds

#define OPCUA_MAX_NUM_DIM      2 // UA_MAX_ARRAY_DIMS
#define OPCUA_MAX_LEN_VAR_NAME 128

#define OPCUA_IS_STRING  0
#define OPCUA_IS_NUMERIC 1

#define OPCUA_NODE_TYPE_UNDEF    0
#define OPCUA_NODE_TYPE_VARIABLE 1
#define OPCUA_NODE_TYPE_OBJECT   2

#define OPCUA_NODEID_TYPE_NUMERIC 1
#define OPCUA_NODEID_TYPE_STRING  2
#define OPCUA_NODEID_TYPE_GUID    3
#define OPCUA_NODEID_TYPE_OPAQUE  4

#define OPCUA_STR_LEN 1024

#define OPCUA_NUM_ENDPOINTS 5

#define OPCUA_MAX_NUM_ITEMS_PER_SUBSCRIPTION 1024

namespace opcua
{

typedef struct t_NodeProps {
    const char *ParentIdentifierString;
    const char *NodeIdentifierString;
    uint32_t ParentIdentifierNumeric;
    uint32_t NodeIdentifierNumeric;

    uint32_t HasParent;
    uint16_t Namespace;
    uint8_t NodeIdType;

    const char *BrowseName;
    const char *DisplayName;
    const char *Description;
    uint32_t DataType;

    uint32_t *Dimensions;
    uint32_t NumDimensions;

    uint32_t NumElements;
    uint32_t ElementSize;

    int32_t MonitoringMode;
    double SamplingInterval;

    bool ReadAccess;
    bool WriteAccess;

    uint8_t NodeType;

} OPCUA_NODE_PROPS_T;

typedef struct t_TransceiverProps {
    bool ExtendedInterface;
    bool CreateSubscription;
    double PublishingInterval;
} OPCUA_TRANSCEIVER_PROPS_T;

} // namespace opcua

#pragma pack(pop)

#endif

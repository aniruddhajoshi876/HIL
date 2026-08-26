#ifndef __MQTT_DEF_H
#define __MQTT_DEF_H

#include <stdint.h>

#pragma pack(push, 1)

#ifndef MATLAB_MEX_FILE

#ifndef NULL
#ifdef __cplusplus
#define NULL 0
#else
#define NULL ((void*)0)
#endif
#endif

#endif

#define MQTT_MODULE_TYPE_UNDEF         0
#define MQTT_STATION_TYPE_CLIENT       1
#define MQTT_STATION_TYPE_SERVER       2

#define MQTT_BLOCK_TYPE_UNDEF             0x00000000
#define MQTT_BLOCK_TYPE_CLIENT_SUBSCRIBE       0x00000004
#define MQTT_BLOCK_TYPE_CLIENT_PUBLISH         0x00000005

#define MQTT_IDLE_DELAY                   100000
#define MQTT_CLIENT_RETRY					1000	// milliseconds

#define MQTT_MAX_NUM_DIM                   2 //UA_MAX_ARRAY_DIMS
#define MQTT_MAX_LEN_VAR_NAME              128

#define MQTT_IS_STRING                     0
#define MQTT_IS_NUMERIC                    1

#define	MQTT_NODE_TYPE_UNDEF				0
#define MQTT_NODE_TYPE_VARIABLE			1
#define MQTT_NODE_TYPE_OBJECT				2


#define MQTT_NODEID_TYPE_NUMERIC           1
#define MQTT_NODEID_TYPE_STRING            2
#define MQTT_NODEID_TYPE_GUID              3
#define MQTT_NODEID_TYPE_OPAQUE            4



namespace mqtt
{

    typedef struct t_NodeProps
    {
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
        bool ReadAccess;
        bool WriteAccess;

        uint8_t NodeType;


    } MQTT_NODE_PROPS_T;

}

#pragma pack(pop)

#endif

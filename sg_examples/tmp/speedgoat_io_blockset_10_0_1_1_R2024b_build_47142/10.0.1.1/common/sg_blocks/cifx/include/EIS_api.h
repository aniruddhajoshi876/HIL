#ifndef __EIS_API_H
#define __EIS_API_H

#include "cifxapi.h"
#include "sg_common.h"
#include "stdint.h"

#define EIS_MAX_NUM_ASSEMBLIES  32
#define EIS_MAX_NUM_CONNECTIONS 32

#define EIS_CONFIG_MODE_SIMPLE   0
#define EIS_CONFIG_MODE_EXTENDED 1

#define EIS_ASSEMBLY_HAS_HEADER   0
#define EIS_ASSEMBLY_HAS_NOHEADER 1

#define EIS_ASSEMBLY_TYPE_OUTPUT      0
#define EIS_ASSEMBLY_TYPE_INPUT       1
#define EIS_ASSEMBLY_TYPE_CONFIG      2
#define EIS_ASSEMBLY_TYPE_INPUT_ONLY  3
#define EIS_ASSEMBLY_TYPE_LISTEN_ONLY 4

#define EIS_CONNECTION_TYPE_EXCLUSIVE_OWNER 0
#define EIS_CONNECTION_TYPE_LISTEN_ONLY     1
#define EIS_CONNECTION_TYPE_INPUT_ONLY      2

typedef struct t_EIS_ASSEMBLY {
    uint32_t ID;
    uint32_t Length;
    uint32_t Offset;
    uint32_t Format;
    uint32_t Type;
    uint8_t *Data;
} EIS_ASSEMBLY_T;

typedef struct t_EIS_CONNECTION {
    uint32_t InputID;
    uint32_t OutputID;
    uint32_t ConfigID;
    uint8_t Type;
} EIS_CONNECTION_T;

typedef struct t_EIS_PARAM {
    uint8_t minRev;
    uint8_t majRev;
    uint8_t enaIPadr;
    uint8_t enaNetMask;
    uint8_t enaGateway;
    uint8_t enaBootP;
    uint8_t enaDHCP;
    uint8_t enaPort1Neg;
    uint8_t enaPort1Dplx;
    uint8_t enaPort1Speed;
    uint8_t enaPort2OwnSet;
    uint8_t enaPort2Neg;
    uint8_t enaPort2Dplx;
    uint8_t enaPort2Speed;
    uint8_t inAssFlg3;
    uint8_t inAssFlg6;
    uint8_t inAssFlg7;
    uint8_t outAssFlg3;
    uint8_t outAssFlg6;
    uint8_t outAssFlg7;
    uint8_t QoSFlg;
    uint8_t enaTag802;
    uint8_t urgentDSCP;
    uint8_t scheduleDSCP;
    uint8_t highDSCP;
    uint8_t lowDSCP;
    uint8_t explicitDSCP;
    uint8_t qckCon;
    uint8_t selAcd;
    uint16_t venID;
    uint16_t prodType;
    uint16_t prodCode;
    uint32_t outputAssInst;
    uint16_t nameSrv;
    uint16_t nameSrv2;
    uint32_t inputAssInst;
    uint32_t sysFlgs;
    uint32_t wdgTime;
    uint32_t inLen;
    uint32_t outLen;
    uint32_t IPadr;
    uint32_t netMask;
    uint32_t gateway;
    uint32_t serNo;
    char DevName[32];
    char Domain[50];
    char Hostname[66];

} EIS_PARAM_T;

typedef struct t_EIS_PARAM_2 {

    uint8_t ConfigMode;

    uint32_t IpAddress;
    uint32_t Netmask;
    uint32_t Gateway;

    uint16_t VendorID;
    uint16_t ProductType;
    uint16_t ProductCode;
    uint8_t MajorRev;
    uint8_t MinorRev;
    char DeviceName[33];

    uint32_t InputAssemblyID;
    uint32_t InputAssemblyLen;
    uint32_t InputAssemblyFormat;
    uint32_t OutputAssemblyID;
    uint32_t OutputAssemblyLen;
    uint32_t OutputAssemblyFormat;

    uint32_t NumAssemblies;
    uint32_t NumConnections;

    EIS_ASSEMBLY_T Assemblies[EIS_MAX_NUM_ASSEMBLIES];
    EIS_CONNECTION_T Connections[EIS_MAX_NUM_CONNECTIONS];

} EIS_PARAM_2_T;

extern int32_t EIS_AcyclicHandler(CIFX_CHANNEL_T *Channel);

#endif
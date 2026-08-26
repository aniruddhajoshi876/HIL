// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL (0x1076+1902-0x17e2)
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME sg_e2e_p1_check_s
#ifdef MATLAB_MEX_FILE
#include "mex.h"
#else
#include "sg_common.h"
#endif
typedef struct{double zeebfcf56dd;double za6a0a8ddf1;double z334f60a9ff;double z94d78c6fa1;double z501c96cd5d;double z4c36db9643;}zc50be82684;
#include "E2E_P01.h"
#include "simstruc.h"
#include <algorithm>
#include <exception>
#define zefdd6d55b2     (0xaa6+6276-0x2329)
#define z5cfd65b291  (0xe43+3557-0x1c28) 
#define z4ff5168d43 (0xb52+3344-0x1862) 
#define z5b80517fba (0x5e3+5094-0x19c9)
#define z15202ccf01 (0x6f8+3241-0x13a1) 
#define za859b74f53 (0x121d+2713-0x1cb4) 
#define zab82456318 ssGetSFcnParam(S, (0xd40+1860-0x1484))
#define z34ae2503e2 (0x1408+1049-0x1721) 
static void mdlInitializeSizes(SimStruct*S){ssSetNumSFcnParams(S,zefdd6d55b2);zc50be82684*zecdc28d7e9=(zc50be82684*)mxGetPr(zab82456318);if(!ssSetNumInputPorts(S,(0x768+2334-0x1085)))return;if(!ssSetNumOutputPorts(S,(0x126f+2129-0x1abf)))return;if(zecdc28d7e9->z4c36db9643==zca4756ea92){ssSetInputPortDataType(S,(0x1870+3112-0x2498),SS_UINT8);ssSetInputPortWidth(S,(0x3da+3388-0x1116),DYNAMICALLY_SIZED);ssSetInputPortRequiredContiguous(S,(0x396+6565-0x1d3b),(0xa20+7302-0x26a5));ssSetInputPortDirectFeedThrough(S,(0x96f+4643-0x1b92),(0x129c+2255-0x1b6a));}else{char z80bcff1348[(0x85a+5338-0x1d20)];if(zecdc28d7e9->z4c36db9643==z490119e7a1){sprintf(z80bcff1348,"\x43\x41\x4e\x5f\x4d\x45\x53\x53\x41\x47\x45\x5f\x42\x55\x53");}else if(zecdc28d7e9->z4c36db9643==z3678c2e0c4){sprintf(z80bcff1348,"\x43\x41\x4e\x5f\x46\x44\x5f\x4d\x45\x53\x53\x41\x47\x45\x5f\x42\x55\x53");}DTypeId z52931a15c6=(0x165+2953-0xcee);ssRegisterTypeFromNamedObject(S,z80bcff1348,&z52931a15c6);ssSetBusInputAsStruct(S,(0x121b+4520-0x23c3),(0x1376+109-0x13e2));ssSetInputPortWidth(S,(0x1462+4358-0x2568),(0x183a+1452-0x1de5));ssSetInputPortDataType(S,(0x1551+2932-0x20c5),z52931a15c6);ssSetInputPortRequiredContiguous(S,(0x129+3823-0x1018),(0x1b89+131-0x1c0b));ssSetInputPortDirectFeedThrough(S,(0x3+7476-0x1d37),(0x7a9+997-0xb8d));}ssSetOutputPortDataType(S,(0x102+9329-0x2573),SS_UINT8);ssSetOutputPortWidth(S,(0x2c8+7655-0x20af),(0x127d+5092-0x2660));ssSetNumSampleTimes(S,(0x140d+4754-0x269e));ssSetNumRWork(S,z5b80517fba);ssSetNumIWork(S,z15202ccf01);ssSetNumPWork(S,za859b74f53);ssSetNumContStates(S,(0x112c+5333-0x2601));ssSetNumDiscStates(S,(0x1199+169-0x1242));ssSetNumSampleTimes(S,(0x3f7+5078-0x17cc));ssSetNumModes(S,(0x1dd7+1903-0x2546));ssSetNumNonsampledZCs(S,(0x2005+688-0x22b5));}
#ifdef MATLAB_MEX_FILE
#define MDL_SET_INPUT_PORT_DIMENSION_INFO
static void mdlSetInputPortDimensionInfo(SimStruct*S,int_T zaaf66dafad,const DimsInfo_T*zde3f224951){if(!ssGetInputPortConnected(S,zaaf66dafad)){return;}if(zde3f224951->width>z34ae2503e2){ssSetErrorStatus(S,"\x49\x6e\x70\x75\x74\x20\x73\x69\x7a\x65\x20\x65\x78\x63\x65\x65\x64\x73\x20\x74\x68\x65\x20\x6d\x61\x78\x69\x6d\x75\x6d\x20\x61\x6c\x6c\x6f\x77\x65\x64\x20\x28\x32\x35\x36\x20\x65\x6c\x65\x6d\x65\x6e\x74\x73\x29\x2e");return;}if(!ssSetInputPortDimensionInfo(S,zaaf66dafad,zde3f224951)){return;}}
#define MDL_SET_OUTPUT_PORT_DIMENSION_INFO
static void mdlSetOutputPortDimensionInfo(SimStruct*S,int_T zaaf66dafad,const DimsInfo_T*zde3f224951){if(!ssSetOutputPortDimensionInfo(S,zaaf66dafad,zde3f224951)){return;}}
#define z4fd520fcfe
static void mdlSetDefaultPortDimensionInfo(SimStruct*S){static int_T dims[(0x990+4116-0x19a3)]={(0x931+6635-0x231b)};DimsInfo_T z17f556eb1b;z17f556eb1b.width=(0x1148+1714-0x17f9);z17f556eb1b.numDims=(0x2e2+3944-0x1249);z17f556eb1b.dims=dims;if(!ssGetInputPortConnected(S,(0xe0c+3845-0x1d11))&&ssGetInputPortWidth(S,(0x19d2+234-0x1abc))==DYNAMICALLY_SIZED){ssSetInputPortDimensionInfo(S,(0x9c8+1909-0x113d),&z17f556eb1b);}if(!ssGetOutputPortConnected(S,(0x98f+5661-0x1fac))&&ssGetOutputPortWidth(S,(0x14ec+3253-0x21a1))==DYNAMICALLY_SIZED){ssSetOutputPortDimensionInfo(S,(0x1166+3701-0x1fdb),&z17f556eb1b);}}
#define z3381248f8a
static void mdlSetInputPortSampleTime(SimStruct*S,int_T z0add1d1c25,real_T sampleTime,real_T z73acaf9d88){ssSetInputPortSampleTime(S,z0add1d1c25,sampleTime);ssSetInputPortOffsetTime(S,z0add1d1c25,z73acaf9d88);if(z0add1d1c25==(0x1538+3477-0x22cd)){ssSetSampleTime(S,(0x319+8221-0x2336),sampleTime);ssSetOffsetTime(S,(0x635+119-0x6ac),z73acaf9d88);}}
#endif
#define z37dc2032fe
static void mdlInitializeSampleTimes(SimStruct*S){ssSetSampleTime(S,(0x18f7+3287-0x25ce),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x18d+3644-0xfc9),0.0);}
#define MDL_START
static void mdlStart(SimStruct*S){zc50be82684*zecdc28d7e9=(zc50be82684*)mxGetPr(zab82456318);z363303b5ec*zff65c39abf;zff65c39abf=(z363303b5ec*)malloc(sizeof(z363303b5ec));memset(zff65c39abf,(0x104d+1630-0x16ab),sizeof(z363303b5ec));int z52cc5fa6f2=ssGetInputPortWidth(S,(0x270+1840-0x9a0));zff65c39abf->z03dbdbb858=zecdc28d7e9->zeebfcf56dd;zff65c39abf->z6f06b74505=zecdc28d7e9->za6a0a8ddf1;zff65c39abf->DataID=zecdc28d7e9->z334f60a9ff;zff65c39abf->zc99e2a69b8=(ze26aa21b7c)zecdc28d7e9->z94d78c6fa1;zff65c39abf->DataLength=(0x190c+2881-0x2445)*z52cc5fa6f2;zff65c39abf->z6cc57fec07=zecdc28d7e9->z501c96cd5d;z7195cde3cd*z6fd4d0fff0=(z7195cde3cd*)malloc(sizeof(z7195cde3cd));memset(z6fd4d0fff0,(0x365+8350-0x2403),sizeof(*z6fd4d0fff0));ssSetPWorkValue(S,(0xe3c+1499-0x1417),(void*)zff65c39abf);ssSetPWorkValue(S,(0x9a+7420-0x1d95),(void*)z6fd4d0fff0);}static void mdlOutputs(SimStruct*S,int_T z27c0327a06){z363303b5ec*zff65c39abf=(z363303b5ec*)ssGetPWorkValue(S,(0xd7+9067-0x2442));z7195cde3cd*z6fd4d0fff0=(z7195cde3cd*)ssGetPWorkValue(S,(0x826+2965-0x13ba));zc50be82684*zecdc28d7e9=(zc50be82684*)mxGetPr(zab82456318);int z52cc5fa6f2=(0x1457+620-0x16c3);uint8_t*ze1464394c1=NULL;if(zecdc28d7e9->z4c36db9643==z490119e7a1){const CANMsg*zaf1616afc8=static_cast<const CANMsg*>ssGetInputPortSignal(S,(0x822+6032-0x1fb2));ze1464394c1=(uint8_t*)zaf1616afc8->Data;z52cc5fa6f2=zaf1616afc8->Length;}else if(zecdc28d7e9->z4c36db9643==z3678c2e0c4){const CanFdMessage*zaf1616afc8=static_cast<const CanFdMessage*>ssGetInputPortSignal(S,(0xc6f+3119-0x189e));ze1464394c1=(uint8_t*)zaf1616afc8->Data;z52cc5fa6f2=zaac3790bd9[zaf1616afc8->DLC];}else if(zecdc28d7e9->z4c36db9643==zca4756ea92){z52cc5fa6f2=ssGetInputPortWidth(S,(0x795+526-0x9a3));if(z52cc5fa6f2>z34ae2503e2){ssSetErrorStatus(S,"\x52\x75\x6e\x74\x69\x6d\x65\x20\x65\x72\x72\x6f\x72\x3a\x20\x49\x6e\x70\x75\x74\x20\x73\x69\x7a\x65\x20\x65\x78\x63\x65\x65\x64\x73\x20\x32\x35\x36\x20\x65\x6c\x65\x6d\x65\x6e\x74\x73\x2e");return;}ze1464394c1=(uint8_t*)ssGetInputPortSignal(S,(0x18a1+2856-0x23c9));}zff65c39abf->DataLength=z52cc5fa6f2*(0x1a14+114-0x1a7e);z6fd4d0fff0->z6869c48bb4=(*ze1464394c1!=(0x208+8966-0x250e))?true:false;uint8_t z3419ea22c8[z52cc5fa6f2];memcpy(z3419ea22c8,ze1464394c1,z52cc5fa6f2*sizeof(uint8_t));zb29070d837(zff65c39abf,z6fd4d0fff0,z3419ea22c8);z5c65694f7b("\x63\x68\x65\x63\x6b\x3a\x20\x45\x32\x45\x5f\x50\x30\x31\x52\x65\x63\x65\x69\x76\x65\x72\x53\x74\x61\x74\x65\x2d\x3e\x53\x74\x61\x74\x75\x73\x20\x3d\x20\x25\x75" "\n",z6fd4d0fff0->Status);uint8_t*zd4dea5f443=(uint8_t*)ssGetOutputPortSignal(S,(0x864+2315-0x116f));*zd4dea5f443=z6fd4d0fff0->Status;}static void mdlTerminate(SimStruct*S){z363303b5ec*zff65c39abf=(z363303b5ec*)ssGetPWorkValue(S,(0x1d28+1973-0x24dd));free(zff65c39abf);z7195cde3cd*z6fd4d0fff0=(z7195cde3cd*)ssGetPWorkValue(S,(0x763+4119-0x1779));free(z6fd4d0fff0);}
#include "../common/libsg/sg_sfcn_glue.h"


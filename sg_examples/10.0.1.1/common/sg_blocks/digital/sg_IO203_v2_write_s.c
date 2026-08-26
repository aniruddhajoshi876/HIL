// Copyright 2006-2026 Speedgoat GmbH

#define 	S_FUNCTION_LEVEL 	(0xbf2+320-0xd30)
#undef 		S_FUNCTION_NAME
#define 	S_FUNCTION_NAME 	sg_IO203_v2_write_s
#include 	<stddef.h>
#include 	<stdlib.h>
#include    <stdbool.h>
#include "sg_io203_v2.h"
#include "simstruc.h"
#ifndef MATLAB_MEX_FILE
#include "sg_printf.h"
#include "sg_common.h"
#include "sg_module_registry.h"
#include "sg_module_types.h"
#else
#include "mex.h"
#endif
#include "sg_callback.h"
#define zdf24515981          ((0xb11+966-0xed0))
#define zf22006b8b3            ssGetSFcnParam(S,(0xd09+4828-0x1fe5))
#define z7945f7753b        ssGetSFcnParam(S,(0x24f+64-0x28e))
#define z10e6897daf          ssGetSFcnParam(S,(0xcc0+4155-0x1cf9))
#define z3832b85a32           ssGetSFcnParam(S,(0xed6+3601-0x1ce4))
#define z67d60a1365        ssGetSFcnParam(S,(0x47f+3218-0x110d))
#define ze13f49a01f       	ssGetSFcnParam(S,(0x6a4+2909-0x11fc))
#define z702a26a5e9                ssGetSFcnParam(S,(0x24da+342-0x262a))
#define z2e6483d505              ((0x3ad+1665-0xa2e))
#define zc5ce4cb81a              ((0x1212+418-0x13b4))
#define z2b17e2ee3b              ((0xe0c+966-0x11d2))
#define THRESHOLD               0.5
static char_T msg[(0x23c+3635-0xf6f)];static void mdlInitializeSizes(SimStruct*S){uint16_T i;uint8_t z23caebc4cc=(0x846+6266-0x20c0);uint8_t z336107e3a8=(0xe4c+3562-0x1c36);ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x1b6+7843-0x2059));ssSetNumDiscStates(S,(0x4ed+7531-0x2258));z23caebc4cc=mxGetPr(z7945f7753b)[(0xcd+5131-0x14d8)];z336107e3a8=(uint8_t)mxGetPr(zf22006b8b3)[(0xbea+2726-0x1690)];if(!ssSetNumOutputPorts(S,(0xe5a+419-0xffd)))return;switch(z336107e3a8){case(0x170+6761-0x1bd8):if(!ssSetNumInputPorts(S,(0x1340+4021-0x22f4)))return;ssSetInputPortWidth(S,(0x843+5458-0x1d95),(0x838+1141-0xc6d));ssSetInputPortDataType(S,(0x15fa+1804-0x1d06),DYNAMICALLY_TYPED);ssSetInputPortDirectFeedThrough(S,(0x271+5908-0x1985),(0x471+2905-0xfc9));ssSetInputPortRequiredContiguous(S,(0x1e5+7945-0x20ee),(0x53f+378-0x6b8));break;case(0x1711+3806-0x25ed):if(!ssSetNumInputPorts(S,z23caebc4cc))return;for(i=(0x21c4+1210-0x267e);i<z23caebc4cc;i++){ssSetInputPortWidth(S,i,(0x7dc+2783-0x12ba));ssSetInputPortDataType(S,i,DYNAMICALLY_TYPED);ssSetInputPortDirectFeedThrough(S,i,(0xf78+1627-0x15d2));ssSetInputPortRequiredContiguous(S,i,(0xb92+6687-0x25b0));}break;default:if(!ssSetNumInputPorts(S,(0xf42+1362-0x1494)))return;break;}ssSetNumSampleTimes(S,(0xde1+3165-0x1a3d));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x2149+446-0x2307));ssSetNumNonsampledZCs(S,(0x6b+2282-0x955));for(i=(0x124b+2808-0x1d43);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x49f+6298-0x1d39));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}
#ifdef MATLAB_MEX_FILE
static void mdlSetInputPortDataType(SimStruct*S,int z0add1d1c25,DTypeId ze97179dd68){ssSetInputPortDataType(S,z0add1d1c25,ze97179dd68);}static void mdlSetDefaultPortDataTypes(SimStruct*S){int za7ad313183=ssGetNumInputPorts(S);for(int i=(0x178f+1363-0x1ce2);i<za7ad313183;i++){ssSetInputPortDataType(S,i,SS_DOUBLE);}}
#endif 
static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0x1c67+2378-0x25b1)]==-1.0){ssSetSampleTime(S,(0x4c7+15-0x4d6),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x66+9894-0x270c),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0xa20+3125-0x1655),mxGetPr(z3832b85a32)[(0xd52+3958-0x1cc8)]);ssSetOffsetTime(S,(0x13c+5593-0x1715),0.0);}}
#ifndef MATLAB_MEX_FILE
static void sg_ModelLoad(SimStruct*S){}static void sg_ModelStart(SimStruct*S){}static void sg_ModelStep(SimStruct*S){uint8_t i=(0x20da+632-0x2352);uint8_t zb220d7e807=mxGetPr(z7945f7753b)[(0x1562+2619-0x1f9d)];uint8_t z7da5ab49fa;uint32_t ze22fda6442;uint32_t ze99784535f;uint32_t zfc752e98c0;uint32_t zbaa9f41030;uint64_t z6b07fa0be9;z6ba2595435*zae10e3f17f=NULL;uint8_t za0d38ae598=(uint32_t)mxGetPr(ze13f49a01f)[(0x74a+6472-0x2092)];uint8_t z336107e3a8=(uint8_t)mxGetPr(zf22006b8b3)[(0x50+5817-0x1709)];DTypeId ze97179dd68;double z146460d588;zae10e3f17f=(z6ba2595435*)sg_module_get_custom_data(SG_MODULE_TYPE_IO203,za0d38ae598);if(!zae10e3f17f){sprintf(msg,"\x25\x73\x20\x28\x49\x44\x20\x25\x64\x29\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x72\x65\x74\x72\x69\x65\x76\x65\x20\x6d\x6f\x64\x75\x6c\x65\x20\x66\x72\x6f\x6d\x20\x72\x65\x67\x69\x73\x74\x72\x79\x20\x69\x6e\x20\x57\x72\x69\x74\x65\x20\x4d\x6f\x64\x65\x6c\x53\x74\x65\x70" "\n",DEVNAME,za0d38ae598);ssSetErrorStatus(S,msg);return;}zfc752e98c0=(0x1704+2212-0x1fa8);zbaa9f41030=(0xdc1+5505-0x2342);z6b07fa0be9=(0x15c2+697-0x187b);switch(z336107e3a8){case(0xf94+1183-0x1432):ze97179dd68=ssGetInputPortDataType(S,(0x121d+5303-0x26d4));const void*za0fcac4809=ssGetInputPortSignal(S,(0x19fd+1624-0x2055));for(i=(0x15d4+2511-0x1fa3);i<(0x1536+787-0x1809);i++){switch(ze97179dd68){case SS_SINGLE:{z146460d588=((real32_T*)za0fcac4809)[i];break;}case SS_DOUBLE:{z146460d588=((real_T*)za0fcac4809)[i];break;}case SS_UINT8:{z146460d588=((uint8_T*)za0fcac4809)[i];break;}case SS_UINT16:{z146460d588=((uint16_T*)za0fcac4809)[i];break;}case SS_UINT32:{z146460d588=((uint32_T*)za0fcac4809)[i];break;}case SS_INT8:{z146460d588=((int8_T*)za0fcac4809)[i];break;}case SS_INT16:{z146460d588=((int16_T*)za0fcac4809)[i];break;}case SS_INT32:{z146460d588=((int32_T*)za0fcac4809)[i];break;}case SS_BOOLEAN:{z146460d588=((boolean_T*)za0fcac4809)[i];break;}default:{z146460d588=((real_T*)za0fcac4809)[i];break;}}if(z146460d588>=THRESHOLD){z6b07fa0be9|=1ULL<<i;}}zfc752e98c0=(uint32_t)(z6b07fa0be9&4294967295);zbaa9f41030=(uint32_t)((z6b07fa0be9>>(0x18a7+2519-0x225e))&4294967295);break;case(0xf2d+628-0x119f):for(i=(0x138d+4581-0x2572);i<zb220d7e807;i++){z7da5ab49fa=mxGetPr(z10e6897daf)[i];ze97179dd68=ssGetInputPortDataType(S,i);switch(ze97179dd68){case SS_SINGLE:{z146460d588=*((real32_T*)ssGetInputPortSignal(S,i));break;}case SS_DOUBLE:{z146460d588=*((real_T*)ssGetInputPortSignal(S,i));break;}case SS_UINT8:{z146460d588=*((uint8_T*)ssGetInputPortSignal(S,i));break;}case SS_UINT16:{z146460d588=*((uint16_T*)ssGetInputPortSignal(S,i));break;}case SS_UINT32:{z146460d588=*((uint32_T*)ssGetInputPortSignal(S,i));break;}case SS_INT8:{z146460d588=*((int8_T*)ssGetInputPortSignal(S,i));break;}case SS_INT16:{z146460d588=*((int16_T*)ssGetInputPortSignal(S,i));break;}case SS_INT32:{z146460d588=*((int32_T*)ssGetInputPortSignal(S,i));break;}case SS_BOOLEAN:{z146460d588=*((boolean_T*)ssGetInputPortSignal(S,i));break;}default:{z146460d588=*ssGetInputPortRealSignal(S,i);break;}}if(z146460d588>=THRESHOLD){if((0x21c+8307-0x228e)<=z7da5ab49fa&&z7da5ab49fa<=(0x11f7+3984-0x2167)){zfc752e98c0|=1U<<(z7da5ab49fa-(0x6a+8761-0x22a2));}else if((0x9cc+893-0xd28)<=z7da5ab49fa&&z7da5ab49fa<=(0xc09+5521-0x215a)){zbaa9f41030|=1U<<(z7da5ab49fa-(0xba0+4441-0x1cd8));}}}break;default:zfc752e98c0=(0x244+3909-0x1189);zbaa9f41030=(0x945+1053-0xd62);break;}ze22fda6442=zae10e3f17f->ze22fda6442;ze99784535f=zae10e3f17f->ze99784535f;if((uint32_T)mxGetPr(z67d60a1365)[(0x7af+4771-0x1a52)]==(0xf29+3377-0x1c59)){zae10e3f17f->z2ffeecda2b[(0x963+3637-0x1788)/(0x1c16+476-0x1dee)]=ze22fda6442&(~zfc752e98c0);zae10e3f17f->z2ffeecda2b[(0x8f1+4283-0x1998)/(0xf45+5722-0x259b)]=ze99784535f&(~zbaa9f41030);}else{zae10e3f17f->z2ffeecda2b[(0x1bb7+2340-0x24db)]=zfc752e98c0;zae10e3f17f->z2ffeecda2b[(0x122+4494-0x12ac)/(0x19af+2348-0x22d7)]=zbaa9f41030;}}static void sg_ModelStop(SimStruct*S){}
#endif  
#include "sg_sfcn_glue.h"   


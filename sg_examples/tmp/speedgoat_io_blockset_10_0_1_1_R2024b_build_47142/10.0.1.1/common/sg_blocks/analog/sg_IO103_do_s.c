// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL        (0x1a6b+442-0x1c23)
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME         sg_IO103_do_s
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include "simstruc.h"
#include "sg_callback_legacy.h"
#include "sg_printf.h"
#ifdef MATLAB_MEX_FILE
#include "mex.h"
#else
#include "sg_common.h"
#endif
#define DEVNAME     "\x53\x70\x65\x65\x64\x67\x6f\x61\x74\x20\x49\x4f\x31\x30\x33"
#define VENDORID    (0x1f2f+2735-0x1929)
#define DEVICEID    36992
#define SUBVENDORID (0x1115+3791-0xf2f)
#define SUBDEVICEID 10361
#define ze13f49a01f           ssGetSFcnParam(S, (0x15b2+2806-0x20a8))
#define za9d8fb6bcf             ssGetSFcnParam(S, (0x1547+2690-0x1fc8))
#define z3832b85a32           ssGetSFcnParam(S, (0x1399+1626-0x19f1))
#define z702a26a5e9                ssGetSFcnParam(S, (0x8b7+2239-0x1173))
#define zdf24515981                           ((0x1343+2869-0x1e74))
#define z7e2eeaa57c          ((0x87f+7360-0x253f))
#define z2e6483d505              ((0x33d+4794-0x15f6))
#define zc5ce4cb81a              ((0x380+8928-0x2660))
#define z0194338df7         ((0x130f+929-0x16b0))
#define z2b17e2ee3b              ((0xfbf+216-0x1096))
#define THRESHOLD               0.5
static char_T msg[(0x1dc+9722-0x26d6)];static void mdlInitializeSizes(SimStruct*S){uint32_T i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x1552+923-0x18ed));ssSetNumDiscStates(S,(0x7b6+3379-0x14e9));ssSetNumOutputPorts(S,(0x724+6245-0x1f89));ssSetNumInputPorts(S,(int)mxGetN(za9d8fb6bcf));for(i=(0x177+3016-0xd3f);i<(int)mxGetN(za9d8fb6bcf);i++){ssSetInputPortWidth(S,i,(0x7d0+1349-0xd14));ssSetInputPortDirectFeedThrough(S,i,(0xa15+2635-0x145f));ssSetInputPortRequiredContiguous(S,i,(0x11a1+527-0x13af));}ssSetNumSampleTimes(S,(0x266+4085-0x125a));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x5fa+5360-0x1aea));ssSetNumNonsampledZCs(S,(0x101b+1537-0x161c));for(i=(0x1533+1118-0x1991);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x1441+1388-0x19ad));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0x1b04+2200-0x239c)]==-1.0){ssSetSampleTime(S,(0x1a37+435-0x1bea),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0xf1d+5301-0x23d2),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0xd73+5214-0x21d1),mxGetPr(z3832b85a32)[(0xb2a+1513-0x1113)]);ssSetOffsetTime(S,(0x254+6008-0x19cc),0.0);}}
#define MDL_START
static void mdlStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
sg_PCIDevice zeccbadd9b3;int_T bus,slot;uint32_T za0d38ae598;volatile uint32_T*za42cf7dd4a;uint16_T zf91d71c6d9=(uint16_T)mxGetN(za9d8fb6bcf);if(mxGetN(z702a26a5e9)==(0xfb0+2033-0x17a0)){bus=(0x271+8168-0x2259);slot=(int_T)mxGetPr(z702a26a5e9)[(0x1cb6+97-0x1d17)];}else{bus=(int_T)mxGetPr(z702a26a5e9)[(0x176+2528-0xb56)];slot=(int_T)mxGetPr(z702a26a5e9)[(0x1bb+8063-0x2139)];}za0d38ae598=((int_T)mxGetPr(ze13f49a01f)[(0x545+7280-0x21b5)]);if(sg_findPciDevice(&zeccbadd9b3,DEVNAME,VENDORID,DEVICEID,SUBVENDORID,SUBDEVICEID,za0d38ae598,bus,slot)!=(0x136c+2147-0x1bcf)){ssSetErrorStatus(S,pSgErrorStr);return;}za42cf7dd4a=sg_mapMemory(&zeccbadd9b3,(0x9f1+3162-0x1649));ssSetPWorkValue(S,z0194338df7,(uint32_T*)za42cf7dd4a);ssSetIWorkValue(S,z7e2eeaa57c,zf91d71c6d9);
#endif
}static void mdlOutputs(SimStruct*S,int_T z27c0327a06){
#ifndef MATLAB_MEX_FILE
volatile uint32_T*za42cf7dd4a=ssGetPWorkValue(S,z0194338df7);uint_T i;uint_T z718c4c15f4,channel;real_T*zc7fdaf6331;z718c4c15f4=(0x1276+709-0x153b);for(i=(0x5bf+8438-0x26b5);i<mxGetN(za9d8fb6bcf);i++){channel=(uchar_T)mxGetPr(za9d8fb6bcf)[i]-(0x1087+1617-0x16d7);zc7fdaf6331=(real_T*)ssGetInputPortRealSignal(S,i);if(zc7fdaf6331[(0xf48+1257-0x1431)]>=THRESHOLD){z718c4c15f4|=(0x2d8+6766-0x1d45)<<channel;}}za42cf7dd4a[(0x1f79+716-0x223c)]=z718c4c15f4;
#endif
}static void mdlTerminate(SimStruct*S){}
#include "sg_sfcn_glue.h"   


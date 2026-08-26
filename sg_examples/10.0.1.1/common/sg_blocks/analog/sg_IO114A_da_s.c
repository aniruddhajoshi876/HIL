// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL        (0x1996+3008-0x2554)
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME         sg_IO114A_da_s
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
#define za9d8fb6bcf             ssGetSFcnParam(S, (0xd59+4199-0x1dc0))
#define z8fd86139be               ssGetSFcnParam(S, (0x685+1983-0xe43))
#define zabe1e0cd2c          ssGetSFcnParam(S, (0xa53+5694-0x208f))
#define z702a26a5e9                ssGetSFcnParam(S, (0x96f+768-0xc6c))
#define zc8bbaa6115               ssGetSFcnParam(S, (0x17e9+763-0x1ae0))
#define zf80b27df71                ssGetSFcnParam(S, (0xb5c+5850-0x2231))
#define ze13f49a01f           ssGetSFcnParam(S, (0x1eb0+943-0x2259))
#define zdf24515981                           ((0x29c+1752-0x96d))
#define zb901964b43            ((0x20bc+1616-0x270c))
#define zdb781881ab         ((0x149d+1378-0x19fe))
#define z2e6483d505              ((0xbc2+4678-0x1e06))
#define zc5ce4cb81a              ((0x27a+285-0x397))
#define z0194338df7         ((0x1e87+1752-0x255f))
#define z2b17e2ee3b              ((0x14c1+591-0x170f))
static char_T msg[(0x14f+2982-0xbf5)];
#define VENDORID    (0x21e2+2798-0x1886)
#define DEVICEID    25096
#define SUBVENDORID (0x16d4+1162-0x714)
#define SUBDEVICEID 25096
#define DEVNAME     "\x53\x70\x65\x65\x64\x67\x6f\x61\x74\x20\x49\x4f\x31\x31\x34\x41"  
static void mdlInitializeSizes(SimStruct*S){uint16_T i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0xf97+3609-0x1db0));ssSetNumDiscStates(S,(0x74+8996-0x2398));ssSetNumInputPorts(S,(int_T)mxGetN(za9d8fb6bcf));for(i=(0x6c+3535-0xe3b);i<(int)mxGetN(za9d8fb6bcf);i++){ssSetInputPortWidth(S,i,(0x13d5+2521-0x1dad));ssSetInputPortDirectFeedThrough(S,i,(0x475+40-0x49c));}ssSetNumOutputPorts(S,(0x1ee1+1361-0x2432));ssSetNumSampleTimes(S,(0x43b+7803-0x22b5));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x11c+7475-0x1e4f));ssSetNumNonsampledZCs(S,(0x6a0+234-0x78a));for(i=(0xa38+2511-0x1407);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0xe95+2107-0x16d0));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(zabe1e0cd2c)[(0x8b7+1385-0xe20)]==-1.0){ssSetSampleTime(S,(0x118a+887-0x1501),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0xe65+5915-0x2580),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0xba+2621-0xaf7),mxGetPr(zabe1e0cd2c)[(0x1748+3310-0x2436)]);ssSetOffsetTime(S,(0x29+1639-0x690),0.0);}}
#define MDL_START
static void mdlStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
sg_PCIDevice zeccbadd9b3;int_T bus,slot;uint32_T za0d38ae598;uintptr_t za42cf7dd4a;int offset,z429712b6a9;if(mxGetN(z702a26a5e9)==(0xde7+5311-0x22a5)){bus=(0xeb1+2351-0x17e0);slot=(int_T)mxGetPr(z702a26a5e9)[(0x10cd+3268-0x1d91)];}else{bus=(int_T)mxGetPr(z702a26a5e9)[(0xca3+5302-0x2159)];slot=(int_T)mxGetPr(z702a26a5e9)[(0xb07+2975-0x16a5)];}za0d38ae598=(int_T)mxGetPr(ze13f49a01f)[(0x17cc+3557-0x25b1)];if(sg_findPciDevice(&zeccbadd9b3,DEVNAME,VENDORID,DEVICEID,SUBVENDORID,SUBDEVICEID,za0d38ae598,bus,slot)!=(0x1f64+1561-0x257d)){ssSetErrorStatus(S,pSgErrorStr);return;}za42cf7dd4a=(uintptr_t)sg_mapIo(&zeccbadd9b3,(0x11c+2615-0xb51));ssSetPWorkValue(S,z0194338df7,(uint32_T*)za42cf7dd4a);switch((uint16_T)mxGetPr(z8fd86139be)[(0x483+8178-0x2475)]){case(0xa26+3305-0x170e):offset=(0x545+4327-0x162c);z429712b6a9=(0x1b82+1454-0x211c);break;case(0xd3a+1098-0x1182):offset=(0x1ac7+1666-0x2144);z429712b6a9=(0x160+904-0x4d4);break;case(0x536+1678-0xbc1):offset=(0xc82+3736-0x1b16);z429712b6a9=(0x905+156-0x991);break;}ssSetIWorkValue(S,zb901964b43,offset);ssSetIWorkValue(S,zdb781881ab,z429712b6a9);
#endif
}static void mdlOutputs(SimStruct*S,int_T z27c0327a06){
#ifndef MATLAB_MEX_FILE
uintptr_t za42cf7dd4a=(uintptr_t)ssGetPWorkValue(S,z0194338df7);real_T offset=ssGetIWorkValue(S,zb901964b43);real_T z429712b6a9=ssGetIWorkValue(S,zdb781881ab);uint32_T zf91d71c6d9=(uint32_T)mxGetN(za9d8fb6bcf);uint32_T i;int_T channel;real_T output;uint16_T zcb341ffb0e;InputRealPtrsType z142f9c10a3;for(i=(0x121c+2543-0x1c0b);i<zf91d71c6d9;i++){channel=(int_T)mxGetPr(za9d8fb6bcf)[i]-(0x1780+388-0x1903);z142f9c10a3=ssGetInputPortRealSignalPtrs(S,i);output=*z142f9c10a3[(0xb1a+6772-0x258e)];output-=offset;if(output<0.0){output=0.0;}zcb341ffb0e=(uint32_T)((output/z429712b6a9)*32768.0);if(zcb341ffb0e>32767){zcb341ffb0e=32767;}while(sg_inpW(za42cf7dd4a)&(0x21f7+697-0x24af)){SG_PRINTF(DEBUG,"\x77\x61\x69\x74\x20\x44\x61\x74\x61\x20\x53\x65\x6e\x64\x20\x3d\x20\x30" "\n");}sg_outpW(za42cf7dd4a+(0x55d+3363-0x127e)*channel,zcb341ffb0e);}
#endif
}static void mdlTerminate(SimStruct*S){}
#include "sg_sfcn_glue.h"   


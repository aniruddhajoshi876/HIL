// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL    (0x1111+4508-0x22ab)
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME     sg_IO105_ad_s
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include "simstruc.h"
#include "sg_callback_legacy.h"
#ifdef MATLAB_MEX_FILE
#include "mex.h"
#else
#include "sg_common.h"
#endif
#define DEVNAME "\x53\x70\x65\x65\x64\x67\x6f\x61\x74\x20\x49\x4f\x31\x30\x35"
#define VENDORID (0x1417+5822-0x1a20)
#define DEVICEID 36992
#define SUBVENDORID (0x1da4+5600-0x22cf)
#define SUBDEVICEID (0x25d0+9149-0x2586)
#define ze13f49a01f           ssGetSFcnParam(S, (0xfb1+709-0x1276))
#define z2cc9a52544            ssGetSFcnParam(S, (0x17e9+934-0x1b8e))
#define za9d8fb6bcf             ssGetSFcnParam(S, (0x3a2+5074-0x1772))
#define z8fd86139be               ssGetSFcnParam(S, (0x59a+7762-0x23e9))
#define z3832b85a32           ssGetSFcnParam(S, (0x9f5+7134-0x25cf))
#define z702a26a5e9                ssGetSFcnParam(S, (0xe36+3871-0x1d50))
#define zdf24515981                           ((0x151a+2629-0x1f59))
#define zc2f3e0cbc0        ((0xc23+897-0xfa3))
#define z2e6483d505              ((0x446+7905-0x2325))
#define z8caad2a8e6              ((0x9cc+2985-0x1575))
#define z5bfe7a2613            ((0x1051+91-0x10ab))
#define zc5ce4cb81a              ((0x13e0+1863-0x1b25))
#define z0194338df7         ((0xa9b+1696-0x113b))
#define z2b17e2ee3b              ((0x19c+9228-0x25a7))
static char_T msg[(0x3a7+2299-0xba2)];static void mdlInitializeSizes(SimStruct*S){uint16_T i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x16ef+715-0x19ba));ssSetNumDiscStates(S,(0x719+6069-0x1ece));ssSetNumInputPorts(S,(0x5d3+3040-0x11b3));switch((uint8_T)mxGetPr(z2cc9a52544)[(0x78d+7612-0x2549)]){case(0x13a8+1447-0x194e):ssSetNumOutputPorts(S,(uint16_T)mxGetN(za9d8fb6bcf));for(i=(0x1873+2775-0x234a);i<(uint16_T)mxGetN(za9d8fb6bcf);i++){ssSetOutputPortWidth(S,i,(0xc42+109-0xcae));}break;case(0x1256+1094-0x169a):ssSetNumOutputPorts(S,(0x109f+1879-0x17f5));ssSetOutputPortWidth(S,(0xcdb+5041-0x208c),(uint16_T)mxGetN(za9d8fb6bcf));break;}ssSetNumSampleTimes(S,(0x2190+509-0x238c));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x15f6+3353-0x230f));ssSetNumNonsampledZCs(S,(0x82d+1141-0xca2));for(i=(0x1d78+1339-0x22b3);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x50a+1069-0x937));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0x13ba+2624-0x1dfa)]==-1.0){ssSetSampleTime(S,(0xb6f+5870-0x225d),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x14a1+4610-0x26a3),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x315+3588-0x1119),mxGetPr(z3832b85a32)[(0x1c90+1507-0x2273)]);ssSetOffsetTime(S,(0x1623+1148-0x1a9f),0.0);}}
#define MDL_START
static void mdlStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
sg_PCIDevice zeccbadd9b3;int_T bus,slot;uint32_T za0d38ae598;void*za42cf7dd4a;uint32_T range;uint32_T zf91d71c6d9=(uint32_T)mxGetN(za9d8fb6bcf);if(mxGetN(z702a26a5e9)==(0xcd7+1881-0x142f)){bus=(0x9cd+2484-0x1381);slot=(int_T)mxGetPr(z702a26a5e9)[(0x81f+5737-0x1e88)];}else{bus=(int_T)mxGetPr(z702a26a5e9)[(0x1ffd+1675-0x2688)];slot=(int_T)mxGetPr(z702a26a5e9)[(0x25c+7657-0x2044)];}za0d38ae598=((int_T)mxGetPr(ze13f49a01f)[(0x4c7+4788-0x177b)]);if(sg_findPciDevice(&zeccbadd9b3,DEVNAME,VENDORID,DEVICEID,SUBVENDORID,SUBDEVICEID,za0d38ae598,bus,slot)!=(0x443+5713-0x1a94)){ssSetErrorStatus(S,pSgErrorStr);return;}za42cf7dd4a=sg_mapMemory(&zeccbadd9b3,(0x157b+3343-0x2288));ssSetPWorkValue(S,z0194338df7,za42cf7dd4a);ssSetIWorkValue(S,zc2f3e0cbc0,zf91d71c6d9);switch((uint16_T)mxGetPr(z8fd86139be)[(0x22a1+843-0x25ec)]){case(0xcda+2370-0x161b):ssSetRWorkValue(S,z8caad2a8e6,3276.8);ssSetRWorkValue(S,z5bfe7a2613,10.0);range=(0x1052+1873-0x17a1);break;case(0x484+5851-0x1b5d):ssSetRWorkValue(S,z8caad2a8e6,6553.6);ssSetRWorkValue(S,z5bfe7a2613,5.0);range=(0xb25+6675-0x2537);break;case(0xfaf+4074-0x1f96):ssSetRWorkValue(S,z8caad2a8e6,13107.2);ssSetRWorkValue(S,z5bfe7a2613,2.5);range=(0x7d2+6282-0x205c);break;}
#endif
}static void mdlOutputs(SimStruct*S,int_T z27c0327a06){
#ifndef MATLAB_MEX_FILE
volatile uint32_T*za42cf7dd4a=ssGetPWorkValue(S,z0194338df7);uint16_T zf91d71c6d9=ssGetIWorkValue(S,zc2f3e0cbc0);real_T z0754dd67cc=ssGetRWorkValue(S,z8caad2a8e6);real_T offset=ssGetRWorkValue(S,z5bfe7a2613);real_T*y;uint32_T i;uint32_T count;za42cf7dd4a[(0x3e8+3246-0x1096)]=za42cf7dd4a[(0x9b+2003-0x86e)]|4096;switch((uint8_T)mxGetPr(z2cc9a52544)[(0x333+3702-0x11a9)]){case(0x76b+1457-0xd1b):for(i=(0x1745+986-0x1b1f);i<zf91d71c6d9;i++){y=ssGetOutputPortSignal(S,i);while(!(za42cf7dd4a[(0x1a5d+2897-0x25ab)]&131072));count=za42cf7dd4a[(0x4e0+2961-0x106f)]&65535;y[(0x93d+5213-0x1d9a)]=(real_T)count/z0754dd67cc-offset;}break;case(0x5e1+6630-0x1fc5):y=ssGetOutputPortSignal(S,(0x392+1765-0xa77));for(i=(0x1406+3760-0x22b6);i<zf91d71c6d9;i++){while(!(za42cf7dd4a[(0xc13+6737-0x2661)]&131072));count=za42cf7dd4a[(0x18c9+2080-0x20e7)]&65535;y[i]=(real_T)count/z0754dd67cc-offset;}break;}
#endif
}static void mdlTerminate(SimStruct*S){}
#include "sg_sfcn_glue.h"   


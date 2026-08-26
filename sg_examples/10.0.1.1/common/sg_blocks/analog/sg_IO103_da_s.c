// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL        (0x11d2+1302-0x16e6)
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME         sg_IO103_da_s
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
#define DEVNAME     "\x53\x70\x65\x65\x64\x67\x6f\x61\x74\x20\x49\x4f\x31\x30\x33"
#define VENDORID    (0x2246+2871-0x1cc8)
#define DEVICEID    36992
#define SUBVENDORID (0x26c6+2220-0x1ebd)
#define SUBDEVICEID 10361
#define ze13f49a01f           ssGetSFcnParam(S, (0x1805+1157-0x1c8a))
#define za9d8fb6bcf             ssGetSFcnParam(S, (0x534+8549-0x2698))
#define z8fd86139be               ssGetSFcnParam(S, (0x10e2+2162-0x1952))
#define z3832b85a32           ssGetSFcnParam(S, (0x922+7359-0x25de))
#define z702a26a5e9                ssGetSFcnParam(S, (0x1224+1112-0x1678))
#define zdf24515981                           ((0x8d4+7687-0x26d6))
#define z7e2eeaa57c          ((0xf17+2481-0x18c8))
#define z2e6483d505              ((0x12bb+220-0x1396))
#define z8caad2a8e6              ((0x101a+23-0x1031))
#define z5bfe7a2613            ((0x16db+3778-0x259c))
#define zc5ce4cb81a              ((0x342+212-0x414))
#define z0194338df7         ((0xa46+4119-0x1a5d))
#define z2b17e2ee3b              ((0xa9d+6174-0x22ba))
static char_T msg[(0x2f0+9072-0x2560)];static void mdlInitializeSizes(SimStruct*S){uint32_T i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0xcb1+185-0xd6a));ssSetNumDiscStates(S,(0x4d7+3987-0x146a));ssSetNumOutputPorts(S,(0x1208+4434-0x235a));ssSetNumInputPorts(S,(int)mxGetN(za9d8fb6bcf));for(i=(0xb40+2740-0x15f4);i<(int)mxGetN(za9d8fb6bcf);i++){ssSetInputPortWidth(S,i,(0x126b+2453-0x1bff));ssSetInputPortDirectFeedThrough(S,i,(0x12+5375-0x1510));ssSetInputPortRequiredContiguous(S,i,(0x1654+3254-0x2309));}ssSetNumSampleTimes(S,(0xc06+3557-0x19ea));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x1037+4432-0x2187));ssSetNumNonsampledZCs(S,(0xaa1+4782-0x1d4f));for(i=(0x1581+2662-0x1fe7);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x4da+50-0x50c));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0x9d2+6039-0x2169)]==-1.0){ssSetSampleTime(S,(0x572+5216-0x19d2),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x701+2327-0x1018),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0xda5+5472-0x2305),mxGetPr(z3832b85a32)[(0x2120+168-0x21c8)]);ssSetOffsetTime(S,(0xa31+3076-0x1635),0.0);}}
#define MDL_START
static void mdlStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
sg_PCIDevice zeccbadd9b3;int_T bus,slot;uint32_T za0d38ae598;volatile uint32_T*za42cf7dd4a;uint16_T zf91d71c6d9=(uint16_T)mxGetN(za9d8fb6bcf);uint32_T range;if(mxGetN(z702a26a5e9)==(0xa66+1978-0x121f)){bus=(0x1bd7+1168-0x2067);slot=(int_T)mxGetPr(z702a26a5e9)[(0xf2d+822-0x1263)];}else{bus=(int_T)mxGetPr(z702a26a5e9)[(0xf8+8693-0x22ed)];slot=(int_T)mxGetPr(z702a26a5e9)[(0x29c+6171-0x1ab6)];}za0d38ae598=((int_T)mxGetPr(ze13f49a01f)[(0xfff+2445-0x198c)]);if(sg_findPciDevice(&zeccbadd9b3,DEVNAME,VENDORID,DEVICEID,SUBVENDORID,SUBDEVICEID,za0d38ae598,bus,slot)!=(0x476+7517-0x21d3)){ssSetErrorStatus(S,pSgErrorStr);return;}za42cf7dd4a=sg_mapMemory(&zeccbadd9b3,(0x365+3381-0x1098));ssSetPWorkValue(S,z0194338df7,(uint32_T*)za42cf7dd4a);ssSetIWorkValue(S,z7e2eeaa57c,zf91d71c6d9);switch((uint16_T)mxGetPr(z8fd86139be)[(0x1d65+1589-0x239a)]){case(0xb0a+3876-0x1a2d):ssSetRWorkValue(S,z8caad2a8e6,3276.8);ssSetRWorkValue(S,z5bfe7a2613,10.0);range=(0x1c58+988-0x2032);break;case(0x1386+2218-0x1c2e):ssSetRWorkValue(S,z8caad2a8e6,6553.6);ssSetRWorkValue(S,z5bfe7a2613,5.0);range=(0x926+31-0x944);break;case(0x51+9657-0x2607):ssSetRWorkValue(S,z8caad2a8e6,13107.2);ssSetRWorkValue(S,z5bfe7a2613,2.5);range=(0xe6+5845-0x17bb);break;}
#endif
}static void mdlOutputs(SimStruct*S,int_T z27c0327a06){
#ifndef MATLAB_MEX_FILE
volatile uint32_T*za42cf7dd4a=ssGetPWorkValue(S,z0194338df7);uint16_T zf91d71c6d9=ssGetIWorkValue(S,z7e2eeaa57c);real_T z0754dd67cc=ssGetRWorkValue(S,z8caad2a8e6);real_T offset=ssGetRWorkValue(S,z5bfe7a2613);uint16_T i;real_T*zc7fdaf6331;int32_T out;uint16_T channel;uint16_T first=(0x18f9+2319-0x2207);for(i=(0xb0d+3947-0x1a78);i<zf91d71c6d9;i++){if(first){first=(0x38b+662-0x621);}else{za42cf7dd4a[(0x1a90+34-0x1aac)]=out|(channel<<(0x312+6137-0x1afb));}channel=(uint16_T)mxGetPr(za9d8fb6bcf)[i]-(0x87b+834-0xbbc);zc7fdaf6331=(real_T*)ssGetInputPortRealSignal(S,i);out=(int32_T)((zc7fdaf6331[(0x18d5+2001-0x20a6)]+offset)*z0754dd67cc);if(out>65535){out=65535;}if(out<(0x991+3210-0x161b)){out=(0x6b+9829-0x26d0);}}za42cf7dd4a[(0xb1a+6822-0x25ba)]=out|(channel<<(0xaeb+3982-0x1a69))|1572864;za42cf7dd4a[(0x12df+603-0x153a)]=za42cf7dd4a[(0xbda+1579-0x1205)]|(0x1d7c+1875-0x1ccf);
#endif
}static void mdlTerminate(SimStruct*S){}
#include "sg_sfcn_glue.h"   


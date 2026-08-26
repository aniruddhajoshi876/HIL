// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL        (0x18cb+1315-0x1dec)
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME         sg_IO103_ad_s
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
#define VENDORID    (0x197f+6685-0x22e7)
#define DEVICEID    36992
#define SUBVENDORID (0x16ed+4992-0x19b8)
#define SUBDEVICEID 10361
#define ze13f49a01f           ssGetSFcnParam(S, (0x1baa+456-0x1d72))
#define za9d8fb6bcf             ssGetSFcnParam(S, (0x2454+219-0x252e))
#define z8fd86139be               ssGetSFcnParam(S, (0x1146+905-0x14cd))
#define z3832b85a32           ssGetSFcnParam(S, (0xe87+4012-0x1e30))
#define z702a26a5e9                ssGetSFcnParam(S, (0xd06+5604-0x22e6))
#define zdf24515981                           ((0x10a+1578-0x72f))
#define zc2f3e0cbc0        ((0x1335+1596-0x1971))
#define z2e6483d505              ((0x1ea4+2086-0x26c9))
#define z8caad2a8e6              ((0x129+4862-0x1427))
#define z5bfe7a2613            ((0x14bf+1642-0x1b28))
#define zc5ce4cb81a              ((0x278+7392-0x1f56))
#define z0194338df7         ((0xe24+3334-0x1b2a))
#define z2b17e2ee3b              ((0x5c+5771-0x16e6))
static char_T msg[(0x62d+5928-0x1c55)];static void mdlInitializeSizes(SimStruct*S){uint16_T i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0xd98+4057-0x1d71));ssSetNumDiscStates(S,(0x2d8+7984-0x2208));ssSetNumInputPorts(S,(0x2424+307-0x2557));ssSetNumOutputPorts(S,(uint16_T)mxGetN(za9d8fb6bcf));for(i=(0x35a+6325-0x1c0f);i<(uint16_T)mxGetN(za9d8fb6bcf);i++){ssSetOutputPortWidth(S,i,(0x49d+1733-0xb61));}ssSetNumSampleTimes(S,(0x84f+5468-0x1daa));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x26b+5868-0x1957));ssSetNumNonsampledZCs(S,(0x1a9+5589-0x177e));for(i=(0x1735+435-0x18e8);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0xfc7+3277-0x1c94));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0x42+6901-0x1b37)]==-1.0){ssSetSampleTime(S,(0x20ab+476-0x2287),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x209f+564-0x22d3),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x20+538-0x23a),mxGetPr(z3832b85a32)[(0x9d5+5803-0x2080)]);ssSetOffsetTime(S,(0x1204+1582-0x1832),0.0);}}
#define MDL_START
static void mdlStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
sg_PCIDevice zeccbadd9b3;int_T bus,slot;uint32_T za0d38ae598;volatile uint32_T*za42cf7dd4a;uint32_T range;uint32_T zf91d71c6d9=(uint32_T)mxGetN(za9d8fb6bcf);if(mxGetN(z702a26a5e9)==(0x720+3062-0x1315)){bus=(0x4c3+8230-0x24e9);slot=(int_T)mxGetPr(z702a26a5e9)[(0x12a5+4307-0x2378)];}else{bus=(int_T)mxGetPr(z702a26a5e9)[(0xcf4+4349-0x1df1)];slot=(int_T)mxGetPr(z702a26a5e9)[(0xff5+3039-0x1bd3)];}za0d38ae598=((int_T)mxGetPr(ze13f49a01f)[(0x166d+1077-0x1aa2)]);if(sg_findPciDevice(&zeccbadd9b3,DEVNAME,VENDORID,DEVICEID,SUBVENDORID,SUBDEVICEID,za0d38ae598,bus,slot)!=(0x19a8+2488-0x2360)){ssSetErrorStatus(S,pSgErrorStr);return;}za42cf7dd4a=sg_mapMemory(&zeccbadd9b3,(0x8d9+3695-0x1746));ssSetPWorkValue(S,z0194338df7,(uint32_T*)za42cf7dd4a);ssSetIWorkValue(S,zc2f3e0cbc0,(uint32_T)zf91d71c6d9);switch((uint16_T)mxGetPr(z8fd86139be)[(0x7c9+3837-0x16c6)]){case(0x125+4357-0x1229):ssSetRWorkValue(S,z8caad2a8e6,3276.8);ssSetRWorkValue(S,z5bfe7a2613,10.0);range=(0x19cd+338-0x1b1d);break;case(0x1c83+393-0x1e0a):ssSetRWorkValue(S,z8caad2a8e6,6553.6);ssSetRWorkValue(S,z5bfe7a2613,5.0);range=(0x2158+1429-0x26ec);break;case(0x388+7018-0x1eef):ssSetRWorkValue(S,z8caad2a8e6,13107.2);ssSetRWorkValue(S,z5bfe7a2613,2.5);range=(0x1aa+3901-0x10e7);break;}
#endif
}static void mdlOutputs(SimStruct*S,int_T z27c0327a06){
#ifndef MATLAB_MEX_FILE
volatile uint32_T*za42cf7dd4a=ssGetPWorkValue(S,z0194338df7);uint16_T zf91d71c6d9=ssGetIWorkValue(S,zc2f3e0cbc0);real_T z0754dd67cc=ssGetRWorkValue(S,z8caad2a8e6);real_T offset=ssGetRWorkValue(S,z5bfe7a2613);real_T*y;uint32_T i;uint32_T count;za42cf7dd4a[(0xd4f+2094-0x157d)]=za42cf7dd4a[(0x729+1233-0xbfa)]|(0x120f+8917-0x24e4);for(i=(0x146+2165-0x9bb);i<zf91d71c6d9;i++){y=ssGetOutputPortSignal(S,i);while(!(za42cf7dd4a[(0x335+4773-0x15d7)]&65536));count=za42cf7dd4a[(0xadb+1027-0xedc)]&65535;y[(0x4c3+1702-0xb69)]=(real_T)count/z0754dd67cc-offset;}
#endif
}static void mdlTerminate(SimStruct*S){}
#include "sg_sfcn_glue.h"   


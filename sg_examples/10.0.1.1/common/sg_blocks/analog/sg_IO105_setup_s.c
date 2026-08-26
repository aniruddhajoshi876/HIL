// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL    (0x23d+7392-0x1f1b)
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME     sg_IO105_setup_s
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
#define DEVNAME "\x53\x70\x65\x65\x64\x67\x6f\x61\x74\x20\x49\x4f\x31\x30\x35"
#define VENDORID (0x1d92+1734-0x13a3)
#define DEVICEID 36992
#define SUBVENDORID (0x10cc+6532-0x199b)
#define SUBDEVICEID 9223
#define ze13f49a01f           ssGetSFcnParam(S, (0x1b78+2506-0x2542))
#define z8fd86139be               ssGetSFcnParam(S, (0x4c5+1656-0xb3c))
#define zd6d6a44c19                 ssGetSFcnParam(S, (0xb58+3777-0x1a17))
#define z702a26a5e9                ssGetSFcnParam(S, (0xb2c+5743-0x2198))
#define z2afc595703           ssGetSFcnParam(S, (0x1192+4215-0x2205))
#define z186580de21          ssGetSFcnParam(S, (0x7c5+7895-0x2697))
#define zdf24515981                           ((0x58a+8432-0x2674))
#define zc2f3e0cbc0        ((0xa22+47-0xa51))
#define z2e6483d505              ((0x10f9+61-0x1135))
#define z8caad2a8e6              ((0x565+4186-0x15bf))
#define z5bfe7a2613            ((0x88a+4797-0x1b46))
#define zc5ce4cb81a              ((0x9a9+6461-0x22e4))
#define z0194338df7         ((0x1f8+5698-0x183a))
#define z2b17e2ee3b              ((0x4e4+5853-0x1bc0))
#define THRESHOLD               0.5
static char_T msg[(0x1c0+4760-0x1358)];static void mdlInitializeSizes(SimStruct*S){uint16_T i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x17c3+3796-0x2697));ssSetNumDiscStates(S,(0x4d2+7102-0x2090));ssSetNumInputPorts(S,(0x577+3374-0x12a5));ssSetNumOutputPorts(S,(0x98f+1712-0x103f));ssSetNumSampleTimes(S,(0x1553+3198-0x21d0));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x1e7f+965-0x2244));ssSetNumNonsampledZCs(S,(0x55c+5593-0x1b35));for(i=(0x1fa0+1786-0x269a);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x4b2+8024-0x240a));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE|SS_OPTION_PLACE_ASAP);}static void mdlInitializeSampleTimes(SimStruct*S){ssSetSampleTime(S,(0xcf7+3667-0x1b4a),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x99d+2790-0x1483),FIXED_IN_MINOR_STEP_OFFSET);}
#define MDL_START
static void mdlStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
sg_PCIDevice zeccbadd9b3;int_T bus,slot;uint32_T za0d38ae598;volatile uint32_T*za42cf7dd4a;uint32_T range,z8b9d33e44f,out;uint32_T zf91d71c6d9=(uint32_T)mxGetN(z2afc595703);int i;if(mxGetN(z702a26a5e9)==(0x217+1222-0x6dc)){bus=(0x718+5443-0x1c5b);slot=(int_T)mxGetPr(z702a26a5e9)[(0x16f2+3156-0x2346)];}else{bus=(int_T)mxGetPr(z702a26a5e9)[(0x20fd+738-0x23df)];slot=(int_T)mxGetPr(z702a26a5e9)[(0xf4d+2402-0x18ae)];}za0d38ae598=((int_T)mxGetPr(ze13f49a01f)[(0x109c+1012-0x1490)]);if(sg_findPciDevice(&zeccbadd9b3,DEVNAME,VENDORID,DEVICEID,SUBVENDORID,SUBDEVICEID,za0d38ae598,bus,slot)){ssSetErrorStatus(S,pSgErrorStr);return;}za42cf7dd4a=sg_mapMemory(&zeccbadd9b3,(0x473+8198-0x2477));ssSetPWorkValue(S,z0194338df7,(void*)za42cf7dd4a);ssSetIWorkValue(S,zc2f3e0cbc0,zf91d71c6d9);if(sg_isModelInit()&&((int)mxGetPr(zd6d6a44c19)[(0x528+6051-0x1ccb)]==(0x1911+1125-0x1d75))){za42cf7dd4a[(0x173+1310-0x691)]=8192;SG_PRINTF(INFO,"\x25\x73\x20\x61\x75\x74\x6f\x63\x61\x6c\x69\x62\x72\x61\x74\x69\x6f\x6e\x20\x73\x74\x61\x72\x74\x65\x64\x2e\x2e" "\n",DEVNAME);for(i=(0x140d+3459-0x2190);za42cf7dd4a[(0x1e8+9348-0x266c)]&8192;i++){if(i>1193000.0*7.0){sprintf(msg,"\x25\x73\x20\x61\x75\x74\x6f\x63\x61\x6c\x69\x62\x72\x61\x74\x69\x6f\x6e\x20\x74\x69\x6d\x65\x64\x20\x6f\x75\x74",DEVNAME);ssSetErrorStatus(S,msg);return;}}if((za42cf7dd4a[(0x151+7162-0x1d4b)]&16384)==16384){SG_PRINTF(INFO,"\x25\x73\x20\x61\x75\x74\x6f\x63\x61\x6c\x69\x62\x72\x61\x74\x69\x6f\x6e\x20\x73\x75\x63\x63\x65\x65\x64\x65\x64\x2e" "\n",DEVNAME);}else{sprintf(msg,"\x25\x73\x20\x61\x75\x74\x6f\x63\x61\x6c\x69\x62\x72\x61\x74\x69\x6f\x6e\x20\x66\x61\x69\x6c\x65\x64",DEVNAME);ssSetErrorStatus(S,msg);return;}}switch((uint16_T)mxGetPr(z8fd86139be)[(0x11b6+4460-0x2322)]){case(0x6d+6998-0x1bc2):ssSetRWorkValue(S,z8caad2a8e6,3276.8);ssSetRWorkValue(S,z5bfe7a2613,10.0);range=(0x18fb+2681-0x2372);break;case(0x22b+7523-0x1f8c):ssSetRWorkValue(S,z8caad2a8e6,6553.6);ssSetRWorkValue(S,z5bfe7a2613,5.0);range=(0x192c+882-0x1c9d);break;case(0x4b8+3719-0x133c):ssSetRWorkValue(S,z8caad2a8e6,13107.2);ssSetRWorkValue(S,z5bfe7a2613,2.5);range=(0x1999+3121-0x25ca);break;}if((uint16_T)mxGetPr(z186580de21)[(0x11d2+4341-0x22c7)]==(0x129f+4984-0x2616)){z8b9d33e44f=(0x14d0+4323-0x25b3);}else{z8b9d33e44f=(0x4c7+5524-0x1a5a);}za42cf7dd4a[(0x80+2923-0xbeb)]=(0x198c+956-0x1d08)|(range<<(0x4e9+8718-0x26f3))|z8b9d33e44f;out=za42cf7dd4a[(0x1a1+8001-0x20da)];out=out&(0x24b1+3823-0x23c0);out=out|(0x38d+5170-0x17a7);switch(zf91d71c6d9){case(0xe6c+4308-0x1f3f):out=out|(((uint32_T)mxGetPr(z2afc595703)[(0x79+4394-0x11a3)]-(0x200f+1079-0x2445))<<(0xf9d+4913-0x22c2));break;case(0x1513+234-0x15fb):out|=(0x97b+5790-0x2018);break;case(0x166+1567-0x781):out|=(0xb2a+5168-0x1f58);break;case(0x431+8104-0x23d1):out|=(0xe88+311-0xfbc);break;case(0x9c1+3456-0x1731):out|=(0x2eb+6491-0x1c42);break;case(0xf83+1105-0x13b4):out|=(0x66f+7678-0x2468);break;case(0x47d+4205-0x14aa):out|=(0x1578+1507-0x1b55);break;}za42cf7dd4a[(0x1190+4975-0x24f7)]=out;SG_PRINTF(DEBUG,"\x53\x63\x61\x6e\x20\x26\x20\x53\x79\x6e\x63\x3a\x20\x30\x78\x25\x78" "\n",za42cf7dd4a[(0x2617+162-0x26b1)]);za42cf7dd4a[(0xdd0+3220-0x1a61)]=65536;for(i=(0x70b+3423-0x146a);za42cf7dd4a[(0x37a+936-0x71f)]&65536;i++){if(i>1193000.0*1.0){sprintf(msg,"\x25\x73\x20\x66\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x63\x6c\x65\x61\x72\x20\x61\x6e\x61\x6c\x6f\x67\x20\x69\x6e\x70\x75\x74\x20\x46\x49\x46\x4f",DEVNAME);ssSetErrorStatus(S,msg);return;}}za42cf7dd4a[(0x1f7a+851-0x22ca)]=(0x545+235-0x630);
#endif
}static void mdlOutputs(SimStruct*S,int_T z27c0327a06){}static void mdlTerminate(SimStruct*S){}
#include "sg_sfcn_glue.h"   


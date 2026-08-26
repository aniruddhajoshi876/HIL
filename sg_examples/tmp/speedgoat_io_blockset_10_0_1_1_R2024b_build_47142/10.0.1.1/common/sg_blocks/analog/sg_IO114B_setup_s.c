// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL        (0x303+684-0x5ad)
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME         sg_IO114B_setup_s
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
#define z8fd86139be               ssGetSFcnParam(S, (0xeb+5384-0x15f3))
#define z702a26a5e9                ssGetSFcnParam(S, (0xd26+1268-0x1219))
#define ze13f49a01f           ssGetSFcnParam(S, (0x629+6651-0x2022))
#define zdf24515981                           ((0xc2+6243-0x1922))
#define zc5ce4cb81a              ((0x35d+1938-0xaef))
#define z2e6483d505              ((0x6d3+3576-0x14cb))
#define z2b17e2ee3b              ((0x72d+170-0x7d7))
static char_T msg[(0x11dd+3998-0x207b)];
#define VENDORID    (0x1d49+7469-0x262c)
#define DEVICEID    25352
#define SUBVENDORID (0x21ac+4704-0x1fc2)
#define SUBDEVICEID 25512
#define DEVNAME     "\x53\x70\x65\x65\x64\x67\x6f\x61\x74\x20\x49\x4f\x31\x31\x34\x42"
#define z8b69a77a59  ((0x5ad+2946-0x112e) << (0x7f7+3733-0x1685))
#define z6bb9663a3e ((0x4fa+5471-0x1a58) << (0x521+788-0x82d))
#define z016f702893  ((0x165c+3927-0x25b2) << (0x627+7677-0x241a))
#define z5c007b0d05 ((0x605+1707-0xcaf) << (0x11b1+3898-0x20e0))
#define z83948eb17f (0x1e59+2232-0x26c1)
static void mdlInitializeSizes(SimStruct*S){uint16_T i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x6e9+6869-0x21be));ssSetNumDiscStates(S,(0x398+3280-0x1068));ssSetNumInputPorts(S,(0x5cb+3077-0x11d0));ssSetNumOutputPorts(S,(0xb1f+3823-0x1a0e));ssSetNumSampleTimes(S,(0xe4c+356-0xfaf));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x1a1c+1726-0x20da));ssSetNumNonsampledZCs(S,(0xa9c+1673-0x1125));for(i=(0x1320+314-0x145a);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x3f4+8519-0x253b));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE|SS_OPTION_PLACE_ASAP);}static void mdlInitializeSampleTimes(SimStruct*S){ssSetSampleTime(S,(0x182a+2936-0x23a2),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x12f5+3963-0x2270),FIXED_IN_MINOR_STEP_OFFSET);}
#define MDL_START
static void mdlStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
sg_PCIDevice zeccbadd9b3;int_T bus,slot;uint32_T za0d38ae598;uint32_T zc430a259a4;uintptr_t za42cf7dd4a;if(mxGetN(z702a26a5e9)==(0x38c+2391-0xce2)){bus=(0x1a1+5872-0x1891);slot=(int_T)mxGetPr(z702a26a5e9)[(0x2211+1225-0x26da)];}else{bus=(int_T)mxGetPr(z702a26a5e9)[(0x73c+3118-0x136a)];slot=(int_T)mxGetPr(z702a26a5e9)[(0x1aec+1237-0x1fc0)];}za0d38ae598=(int_T)mxGetPr(ze13f49a01f)[(0x10d0+4523-0x227b)];if(sg_findPciDevice(&zeccbadd9b3,DEVNAME,VENDORID,DEVICEID,SUBVENDORID,SUBDEVICEID,za0d38ae598,bus,slot)){ssSetErrorStatus(S,pSgErrorStr);return;}za42cf7dd4a=(uintptr_t)sg_mapIo(&zeccbadd9b3,(0xea5+552-0x10cc));if(sg_isModelInit()){zc430a259a4=sg_inpDW(za42cf7dd4a+z83948eb17f);zc430a259a4&=~(0x2547+851-0x18da);zc430a259a4|=z8b69a77a59|z016f702893;switch((int)mxGetPr(z8fd86139be)[(0x2650+11-0x265b)]){case(0x1b95+1184-0x2034):SG_PRINTF(INFO,"\x25\x73\x3a\x20\x30\x2e\x2e\x32\x30\x6d\x41" "\n",DEVNAME);break;case(0x93a+2909-0x1495):SG_PRINTF(INFO,"\x25\x73\x3a\x20\x35\x2e\x2e\x32\x35\x6d\x41" "\n",DEVNAME);zc430a259a4|=z6bb9663a3e;break;case(0x1080+4121-0x2096):SG_PRINTF(INFO,"\x25\x73\x3a\x20\x34\x2e\x2e\x32\x30\x6d\x41" "\n",DEVNAME);zc430a259a4|=z6bb9663a3e|z5c007b0d05;break;}sg_outpW(za42cf7dd4a+z83948eb17f,zc430a259a4);}
#endif
}static void mdlOutputs(SimStruct*S,int_T z27c0327a06){}static void mdlTerminate(SimStruct*S){}
#include "sg_sfcn_glue.h"   


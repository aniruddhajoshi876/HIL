// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL        (0x1827+926-0x1bc3)
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME         sg_IO114A_setup_s
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
#define z8fd86139be               ssGetSFcnParam(S, (0x17d6+3860-0x26ea))
#define z702a26a5e9                ssGetSFcnParam(S, (0x2608+4-0x260b))
#define ze13f49a01f           ssGetSFcnParam(S, (0x473+2196-0xd05))
#define zdf24515981                           ((0x1131+850-0x1480))
#define zc5ce4cb81a              ((0x23f+9078-0x25b5))
#define z2e6483d505              ((0x9d6+2348-0x1302))
#define z2b17e2ee3b              ((0xa8+4255-0x1147))
static char_T msg[(0x1034+5585-0x2505)];
#define VENDORID    5194
#define DEVICEID    25096
#define SUBVENDORID 5194
#define SUBDEVICEID 25096
#define DEVNAME     "\x53\x70\x65\x65\x64\x67\x6f\x61\x74\x20\x49\x4f\x31\x31\x34\x41"  
#define z8b69a77a59  ((0x1e5b+364-0x1fc6) << (0x1255+1266-0x1740))
#define z6bb9663a3e ((0x6e0+3129-0x1318) << (0x7cd+2137-0x101e))
#define z016f702893  ((0x167b+3041-0x225b) << (0xc7+3517-0xe7a))
#define z5c007b0d05 ((0x643+4781-0x18ef) << (0x10+9722-0x25ff))
#define z83948eb17f (0xabb+4180-0x1abf)
static void mdlInitializeSizes(SimStruct*S){uint16_T i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x15bc+1767-0x1ca3));ssSetNumDiscStates(S,(0xe86+3535-0x1c55));ssSetNumInputPorts(S,(0x119a+2191-0x1a29));ssSetNumOutputPorts(S,(0xfd8+4724-0x224c));ssSetNumSampleTimes(S,(0xcfd+4357-0x1e01));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x42a+8655-0x25f9));ssSetNumNonsampledZCs(S,(0x18b+2397-0xae8));for(i=(0xef7+220-0xfd3);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x77f+843-0xaca));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE|SS_OPTION_PLACE_ASAP);}static void mdlInitializeSampleTimes(SimStruct*S){ssSetSampleTime(S,(0x459+3524-0x121d),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x28f+1973-0xa44),FIXED_IN_MINOR_STEP_OFFSET);}
#define MDL_START
static void mdlStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
sg_PCIDevice zeccbadd9b3;int_T bus,slot;uint32_T za0d38ae598;uint32_T zc430a259a4;uintptr_t za42cf7dd4a;if(mxGetN(z702a26a5e9)==(0xd27+4154-0x1d60)){bus=(0x1264+4673-0x24a5);slot=(int_T)mxGetPr(z702a26a5e9)[(0xc67+5829-0x232c)];}else{bus=(int_T)mxGetPr(z702a26a5e9)[(0x4a2+6645-0x1e97)];slot=(int_T)mxGetPr(z702a26a5e9)[(0x573+5651-0x1b85)];}za0d38ae598=(int_T)mxGetPr(ze13f49a01f)[(0x1043+2256-0x1913)];if(sg_findPciDevice(&zeccbadd9b3,DEVNAME,VENDORID,DEVICEID,SUBVENDORID,SUBDEVICEID,za0d38ae598,bus,slot)!=(0x5ef+3272-0x12b7)){ssSetErrorStatus(S,pSgErrorStr);return;}za42cf7dd4a=(uintptr_t)sg_mapIo(&zeccbadd9b3,(0xfbb+3669-0x1e0f));if(sg_isModelInit()){zc430a259a4=sg_inpDW(za42cf7dd4a+z83948eb17f);zc430a259a4&=~(0x115c+2145-0x9fd);zc430a259a4|=z8b69a77a59|z016f702893;switch((int)mxGetPr(z8fd86139be)[(0x3b5+3354-0x10cf)]){case(0x1297+635-0x1511):SG_PRINTF(INFO,"\x25\x73\x3a\x20\x30\x2e\x2e\x32\x30\x6d\x41" "\n",DEVNAME);break;case(0xc0f+6233-0x2466):SG_PRINTF(INFO,"\x25\x73\x3a\x20\x35\x2e\x2e\x32\x35\x6d\x41" "\n",DEVNAME);zc430a259a4|=z6bb9663a3e;break;case(0x7da+3311-0x14c6):SG_PRINTF(INFO,"\x25\x73\x3a\x20\x34\x2e\x2e\x32\x30\x6d\x41" "\n",DEVNAME);zc430a259a4|=z6bb9663a3e|z5c007b0d05;break;}sg_outpW(za42cf7dd4a+z83948eb17f,zc430a259a4);}
#endif
}static void mdlOutputs(SimStruct*S,int_T z27c0327a06){}static void mdlTerminate(SimStruct*S){}
#include "sg_sfcn_glue.h"   


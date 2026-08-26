// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL    (0xc05+6016-0x2383)
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME     sg_IO112_adstart_s
#include <stddef.h>
#include <stdlib.h>
#include "sg_callback_legacy.h"
#include "simstruc.h"
#ifdef MATLAB_MEX_FILE
#include "mex.h"
#else
#include "sg_common.h"
#endif
#include "sg_printf.h"
#define DEVNAME "\x53\x70\x65\x65\x64\x67\x6f\x61\x74\x20\x49\x4f\x31\x31\x32"
#define VENDORID (0x1f53+680-0x1146)
#define DEVICEID 36950
#define SUBVENDORID (0x1d7a+393-0xe4e)
#define SUBDEVICEID 13361
#define ze13f49a01f           ssGetSFcnParam(S, (0x3ba+625-0x62b))
#define za8bff65d14              ssGetSFcnParam(S, (0x1eb+4664-0x1422))
#define z04bce731b0             ssGetSFcnParam(S, (0x1da+8589-0x2365))
#define z3832b85a32           ssGetSFcnParam(S, (0x111d+1823-0x1839))
#define z702a26a5e9                ssGetSFcnParam(S, (0x12c3+3304-0x1fa7))
#define zdf24515981                           ((0x223+3350-0xf34))
#define zc2f3e0cbc0        ((0x7e1+158-0x87f))
#define z2e6483d505              ((0x99+2441-0xa21))
#define z8caad2a8e6              ((0x1d27+2000-0x24f7))
#define z5bfe7a2613            ((0x11c6+1907-0x1931))
#define zc5ce4cb81a              ((0x1307+2760-0x1dbf))
#define z0194338df7         ((0x19c7+2818-0x24c9))
#define z2b17e2ee3b              ((0x185c+3027-0x242e))
static char_T msg[(0xea4+762-0x109e)];static void mdlInitializeSizes(SimStruct*S){uint16_T i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0xaeb+1357-0x1038));ssSetNumDiscStates(S,(0xe55+5551-0x2404));if(!(boolean_T)mxGetPr(z04bce731b0)[(0x19+3770-0xed3)]){ssSetNumOutputPorts(S,(0x119d+1767-0x1884));}else{ssSetNumOutputPorts(S,(0xacc+1608-0x1113));ssSetOutputPortWidth(S,(0xf9d+2676-0x1a11),(0x391+6945-0x1eb1));ssSetOutputPortDataType(S,(0xab6+2614-0x14ec),SS_BOOLEAN);}if(!(boolean_T)mxGetPr(za8bff65d14)[(0xbb0+6639-0x259f)]){ssSetNumInputPorts(S,(0xb09+160-0xba9));}else{ssSetNumInputPorts(S,(0x3ab+1003-0x795));ssSetInputPortDirectFeedThrough(S,(0x142+1192-0x5ea),(0xb0+1232-0x57f));ssSetInputPortWidth(S,(0xa54+1896-0x11bc),(0x1a23+3178-0x268c));ssSetInputPortDataType(S,(0x3e7+7606-0x219d),SS_BOOLEAN);ssSetInputPortRequiredContiguous(S,(0x1562+3615-0x2381),(0x838+1453-0xde4));}ssSetNumSampleTimes(S,(0x210+1689-0x8a8));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x131c+285-0x1439));ssSetNumNonsampledZCs(S,(0xc06+1090-0x1048));for(i=(0x9c0+7370-0x268a);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x1d7c+2425-0x26f5));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0xf24+2838-0x1a3a)]==-1.0){ssSetSampleTime(S,(0x207a+216-0x2152),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x50a+5056-0x18ca),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x8eb+6569-0x2294),mxGetPr(z3832b85a32)[(0x5a2+1742-0xc70)]);ssSetOffsetTime(S,(0x413+233-0x4fc),0.0);}}
#define MDL_START
static void mdlStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
sg_PCIDevice zeccbadd9b3;int_T bus,slot;uint32_T za0d38ae598;volatile uint32_T*za42cf7dd4a;if(mxGetN(z702a26a5e9)==(0xf51+3633-0x1d81)){bus=(0xacd+2259-0x13a0);slot=(int_T)mxGetPr(z702a26a5e9)[(0x31c+3865-0x1235)];}else{bus=(int_T)mxGetPr(z702a26a5e9)[(0x1cca+1482-0x2294)];slot=(int_T)mxGetPr(z702a26a5e9)[(0x41b+4546-0x15dc)];}za0d38ae598=((int_T)mxGetPr(ze13f49a01f)[(0xcd1+2294-0x15c7)]);if(sg_findPciDevice(&zeccbadd9b3,DEVNAME,VENDORID,DEVICEID,SUBVENDORID,SUBDEVICEID,za0d38ae598,bus,slot)!=(0x1229+2663-0x1c90)){ssSetErrorStatus(S,pSgErrorStr);return;}za42cf7dd4a=(volatile uint32_T*)sg_mapMemory(&zeccbadd9b3,(0xbc4+4075-0x1bad));ssSetPWorkValue(S,z0194338df7,(uint32_T*)za42cf7dd4a);
#endif
}static void mdlOutputs(SimStruct*S,int_T z27c0327a06){
#ifndef MATLAB_MEX_FILE
volatile uint32_T*za42cf7dd4a=ssGetPWorkValue(S,z0194338df7);boolean_T*z0daf90e5e1;boolean_T enabled=true;if((int)mxGetPr(za8bff65d14)[(0x30c+6037-0x1aa1)]){z0daf90e5e1=(boolean_T*)ssGetInputPortSignal(S,(0x4f4+2598-0xf1a));enabled=z0daf90e5e1[(0x723+2559-0x1122)];}if((int)mxGetPr(z04bce731b0)[(0x1422+3199-0x20a1)]){z0daf90e5e1=(boolean_T*)ssGetOutputPortSignal(S,(0x9c1+3163-0x161c));z0daf90e5e1[(0x53d+5952-0x1c7d)]=enabled;}if(enabled){za42cf7dd4a[(0xc14+2259-0x14e7)]=za42cf7dd4a[(0x9e8+1659-0x1063)]|(0x117d+3567-0xf6c);}
#endif
}static void mdlTerminate(SimStruct*S){}
#include "sg_sfcn_glue.h"   


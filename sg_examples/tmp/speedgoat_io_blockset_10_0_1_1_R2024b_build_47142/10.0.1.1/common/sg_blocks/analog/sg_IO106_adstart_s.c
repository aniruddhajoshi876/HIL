// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL    (0x7ed+2813-0x12e8)
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME     sg_IO106_adstart_s
#include <stddef.h>
#include <stdlib.h>
#include "sg_IO106.h"
#include "simstruc.h"
#ifdef MATLAB_MEX_FILE
#include "mex.h"
#else
#include "sg_printf.h"
#include "sg_common.h"
#include "sg_module_types.h"
#include "sg_module_registry.h"
#endif
#define SG_EARLY_INIT
#include "sg_callback.h"
#define ze13f49a01f           ssGetSFcnParam(S, (0x1f9+3066-0xdf3))
#define za8bff65d14              ssGetSFcnParam(S, (0x1594+2591-0x1fb2))
#define z04bce731b0             ssGetSFcnParam(S, (0x792+3953-0x1701))
#define z3832b85a32           ssGetSFcnParam(S, (0x3d4+2899-0xf24))
#define z702a26a5e9                ssGetSFcnParam(S, (0xa17+7017-0x257c))
#define zdf24515981          ((0x12e8+3337-0x1fec))
#define z2e6483d505              ((0x1d64+64-0x1da4))
#define zc5ce4cb81a              ((0xcb8+808-0xfe0))
#define z2b17e2ee3b              ((0x6c9+1050-0xae3))
static char_T msg[(0xa62+3189-0x15d7)];static void mdlInitializeSizes(SimStruct*S){uint16_T i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x1d74+1699-0x2417));ssSetNumDiscStates(S,(0xd69+2908-0x18c5));if(!(boolean_T)mxGetPr(z04bce731b0)[(0xa7b+3764-0x192f)]){if(!ssSetNumOutputPorts(S,(0xba8+2473-0x1551)))return;}else{if(!ssSetNumOutputPorts(S,(0x9d2+5902-0x20df)))return;ssSetOutputPortWidth(S,(0xcc5+6641-0x26b6),(0xc47+309-0xd7b));ssSetOutputPortDataType(S,(0x27b+1980-0xa37),SS_BOOLEAN);}if(!(boolean_T)mxGetPr(za8bff65d14)[(0x1461+2243-0x1d24)]){if(!ssSetNumInputPorts(S,(0xfa9+2824-0x1ab1)))return;}else{if(!ssSetNumInputPorts(S,(0x1dab+519-0x1fb1)))return;ssSetInputPortDirectFeedThrough(S,(0x860+7189-0x2475),(0xd4b+5908-0x245e));ssSetInputPortWidth(S,(0x1eb0+1665-0x2531),(0x1ffb+1482-0x25c4));ssSetInputPortDataType(S,(0xe79+5547-0x2424),SS_BOOLEAN);ssSetInputPortRequiredContiguous(S,(0x129d+4760-0x2535),(0x5d5+7318-0x226a));}ssSetNumSampleTimes(S,(0x1eb+6410-0x1af4));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x22dd+235-0x23c8));ssSetNumNonsampledZCs(S,(0x188f+1197-0x1d3c));for(i=(0xfc1+874-0x132b);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0xa7d+4624-0x1c8d));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0x2fc+5350-0x17e2)]==-1.0){ssSetSampleTime(S,(0x1fa0+614-0x2206),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x2007+1616-0x2657),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x450+448-0x610),mxGetPr(z3832b85a32)[(0x9f5+6683-0x2410)]);ssSetOffsetTime(S,(0x1178+1421-0x1705),0.0);}}
#ifndef MATLAB_MEX_FILE
static void sg_ModelLoad(SimStruct*S){}static void sg_ModelStart(SimStruct*S){}static void sg_ModelStep(SimStruct*S){boolean_T*z0daf90e5e1;boolean_T enabled=true;uint32_T za0d38ae598=((uint32_T)mxGetPr(ze13f49a01f)[(0x8aa+4324-0x198e)]);z6077dd317b*zae10e3f17f=(z6077dd317b*)sg_module_get_custom_data(z12ba1d7c25,za0d38ae598);if(!zae10e3f17f){sprintf(msg,"\x49\x4f\x25\x64\x20\x28\x49\x44\x20\x25\x64\x29\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x72\x65\x74\x72\x69\x65\x76\x65\x20\x6d\x6f\x64\x75\x6c\x65\x20\x66\x72\x6f\x6d\x20\x72\x65\x67\x69\x73\x74\x72\x79\x20\x69\x6e\x20\x41\x44\x20\x53\x74\x61\x72\x74\x20\x4d\x6f\x64\x65\x6c\x53\x74\x65\x70" "\n",z12ba1d7c25,za0d38ae598);ssSetErrorStatus(S,msg);return;}if((int)mxGetPr(za8bff65d14)[(0x1a15+2394-0x236f)]){z0daf90e5e1=(boolean_T*)ssGetInputPortSignal(S,(0x7cb+7020-0x2337));enabled=z0daf90e5e1[(0x137b+4417-0x24bc)];}if((int)mxGetPr(z04bce731b0)[(0x1633+591-0x1882)]){z0daf90e5e1=(boolean_T*)ssGetOutputPortSignal(S,(0xbfa+5043-0x1fad));z0daf90e5e1[(0x1ffa+499-0x21ed)]=enabled;}if(enabled){zae10e3f17f->z3fad3d9764->z14bc320aa4|=((0x12e2+3110-0x1f07)<<z03d027903f);}}static void sg_ModelStop(SimStruct*S){}
#endif
#include "sg_sfcn_glue.h"   


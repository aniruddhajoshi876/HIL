// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL    (0x1105+4686-0x2351)
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME     sg_IO110_da_s
#include "sg_io110.h"
#include "simstruc.h"
#ifdef MATLAB_MEX_FILE
#include "mex.h"
#else
#include "sg_common.h"
#include "sg_printf.h"
#include "sg_module_registry.h"
#include "sg_module_types.h"
#endif
#define SG_EARLY_INIT
#include "sg_callback.h"
#define zdf24515981          ((0xf38+5939-0x2664))
#define ze13f49a01f           ssGetSFcnParam(S,(0x1f94+529-0x21a5))
#define z702a26a5e9                ssGetSFcnParam(S,(0x91a+5857-0x1ffa))
#define z1f7e7173d9          ssGetSFcnParam(S,(0xacb+369-0xc3a))
#define zc6f930323f            ssGetSFcnParam(S,(0xc78+1975-0x142c))
#define z3832b85a32           ssGetSFcnParam(S,(0xfd8+2709-0x1a69))
#define z84dd9a9a5c            ssGetSFcnParam(S,(0xef6+588-0x113d))
#define z4d2d92ea80         ssGetSFcnParam(S,(0x1240+3837-0x2137))
#define z2e6483d505              ((0x176c+3329-0x246d))
#define zc5ce4cb81a              ((0x11cb+3420-0x1f27))
#define z2b17e2ee3b              ((0x1b20+2124-0x236c))
static char_T msg[(0x11e3+3468-0x1e6f)];static void mdlInitializeSizes(SimStruct*S){uint16_T i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n""\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x84f+3890-0x1781));ssSetNumDiscStates(S,(0x84d+1215-0xd0c));if(!ssSetNumOutputPorts(S,(0x205d+113-0x20ce)))return;if(!ssSetNumInputPorts(S,(int)mxGetN(z1f7e7173d9)))return;for(i=(0x11d+3901-0x105a);i<(int)mxGetN(z1f7e7173d9);i++){ssSetInputPortWidth(S,i,(0x1a0b+2052-0x220e));ssSetInputPortDirectFeedThrough(S,i,(0x15c6+3514-0x237f));ssSetInputPortRequiredContiguous(S,i,(0xb31+1433-0x10c9));}ssSetNumSampleTimes(S,(0xeb+5669-0x170f));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x6cf+5055-0x1a8e));ssSetNumNonsampledZCs(S,(0x810+578-0xa52));for(i=(0x133+16-0x143);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,SS_PRM_NOT_TUNABLE);}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0x814+1791-0xf13)]==-1.0){ssSetSampleTime(S,(0xa76+2406-0x13dc),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x75c+471-0x933),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0xf05+3300-0x1be9),mxGetPr(z3832b85a32)[(0x1d7+7377-0x1ea8)]);ssSetOffsetTime(S,(0x1a28+1974-0x21de),0.0);}}
#ifndef MATLAB_MEX_FILE
static void sg_ModelLoad(SimStruct*S){}static void sg_ModelStart(SimStruct*S){}static void sg_ModelStep(SimStruct*S){uint16_T i,channel,range;real_T out,*zc7fdaf6331;uint32_T za0d38ae598=((int_T)mxGetPr(ze13f49a01f)[(0xa85+5846-0x215b)]);z2848b39198*zae10e3f17f=(z2848b39198*)sg_module_get_custom_data(z12ba1d7c25,za0d38ae598);if(!zae10e3f17f){sprintf(msg,"\x49\x4f\x25\x64\x20\x28\x49\x44\x20\x25\x64\x29\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x72\x65\x74\x72\x69\x65\x76\x65\x20\x6d\x6f\x64\x75\x6c\x65\x20\x66\x72\x6f\x6d\x20\x72\x65\x67\x69\x73\x74\x72\x79\x20\x69\x6e\x20\x44\x41\x20\x4d\x6f\x64\x65\x6c\x53\x74\x65\x70" "\n",z12ba1d7c25,za0d38ae598);ssSetErrorStatus(S,msg);return;}for(i=(0xf48+2224-0x17f8);i<mxGetN(z1f7e7173d9);i++){channel=(uint16_T)mxGetPr(z1f7e7173d9)[i]-(0x854+2195-0x10e6);range=(uint16_T)mxGetPr(zc6f930323f)[channel];zc7fdaf6331=(real_T*)ssGetInputPortRealSignal(S,i);out=zc7fdaf6331[(0x166a+572-0x18a6)]*zae10e3f17f->z0eea8c34d0[channel];zdf15c763dd(range,zae10e3f17f->z9fb53cdf50[channel],zae10e3f17f->zb817ad7ad6[channel],&out);zae10e3f17f->z571d7e98ef[z6f16ec95a7(channel)]=(int16_T)out;}}static void sg_ModelStop(SimStruct*S){}
#endif 
#include "sg_sfcn_glue.h"   


// Copyright 2006-2026 Speedgoat GmbH

#define 	S_FUNCTION_LEVEL 	(0x96f+4462-0x1adb)
#undef 		S_FUNCTION_NAME
#define 	S_FUNCTION_NAME 	sg_fpga_i2cswrite_sf_a1
#include 	<stddef.h>
#include 	<stdlib.h>
#include 	"simstruc.h" 
#ifdef 		MATLAB_MEX_FILE
#include 	"mex.h"
#endif
#ifndef         MATLAB_MEX_FILE
#include        "sg_common.h"
#include        "sg_fpga_io3xx_util.h"
#endif
#include        "sg_callback.h"
#define ze13f49a01f         ssGetSFcnParam(S, (0x20d5+1117-0x2532)) 
#define za9d8fb6bcf           ssGetSFcnParam(S, (0xae1+1802-0x11ea)) 
#define zd7a15617ca         ssGetSFcnParam(S, (0xe33+830-0x116f))
#define z3832b85a32         ssGetSFcnParam(S, (0x6ff+841-0xa45))
#define zdf24515981                         ((0x1cb1+902-0x2033))
#define z2e6483d505              ((0x1260+4373-0x2375))
#define zc5ce4cb81a              ((0x22aa+1068-0x26d6))
#define z2b17e2ee3b              ((0x50f+8563-0x2681))
#define z0194338df7         ((0xb9b+2004-0x136f))
static char_T msg[(0x3df+1726-0x99d)];typedef struct z4ffeb08593{uint32_T enable;uint32_T clear;uint32_T z553991aa78;uint32_T z039626e71b[(0x18d7+2203-0x2152)];uint32_T z7515281f6c[(0x10c7+2311-0x19ae)];uint32_T zd6e550175f[(0x973+40-0x97b)];uint32_T z2678040317[(0x1dc0+588-0x1fec)];uint32_T skipRegAddress;}z4ffeb08593;static void mdlInitializeSizes(SimStruct*S){uint32_T i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x105f+1337-0x1598));ssSetNumDiscStates(S,(0xb38+2358-0x146e));if(!ssSetNumOutputPorts(S,(0x9f9+5843-0x20cc))){return;}if(!ssSetNumInputPorts(S,(0x2b7+7414-0x1fac))){return;}ssSetInputPortWidth(S,(0x54f+660-0x7e3),mxGetN(zd7a15617ca));ssSetInputPortDirectFeedThrough(S,(0x912+7654-0x26f8),(0x1904+800-0x1c23));ssSetInputPortRequiredContiguous(S,(0xc34+3810-0x1b16),(0x5bf+4546-0x1780));ssSetNumSampleTimes(S,(0x674+7700-0x2487));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x2a3+261-0x3a8));ssSetNumNonsampledZCs(S,(0x88a+4486-0x1a10));for(i=(0x1c22+2012-0x23fe);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x778+6009-0x1ef1));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0x948+6362-0x2222)]==-1.0){ssSetSampleTime(S,(0xc65+5094-0x204b),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x117b+4083-0x216e),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0xbf0+2569-0x15f9),mxGetPr(z3832b85a32)[(0x555+7947-0x2460)]);ssSetOffsetTime(S,(0xb45+49-0xb76),0.0);}}static void sg_ModelLoad(SimStruct*S){
#ifndef MATLAB_MEX_FILE
volatile z4ffeb08593*z77b62f8983;int moduleId=(int)mxGetScalar(ze13f49a01f);char*boardName=io3xxGetBoardNameSgLib(moduleId);if(!io3xxGetAddressSgLib((int32_t)(int)mxGetPr(ze13f49a01f)[(0x163+1004-0x54f)],SG_FPGA_IO3XX_BAR2)){ssSetErrorStatus(S,pSgErrorStr);return;}uint32_t zf7ccd17be8=(0x6b0+2243-0xf73);if(sg_fpga_io3xx_getCmBaseAddress(moduleId,I2CS_BASE,&zf7ccd17be8)){sprintf(msg,"\x25\x73\x20\x49\x32\x43\x53\x20\x6d\x6f\x64\x75\x6c\x65\x3a\x20\x4f\x66\x66\x73\x65\x74\x20\x6c\x6f\x6f\x6b\x75\x70\x20\x75\x6e\x73\x75\x63\x63\x65\x73\x73\x66\x75\x6c\x21" "\n",boardName);ssSetErrorStatus(S,msg);return;}z77b62f8983=(volatile z4ffeb08593*)((uintptr_t)io3xxGetAddressSgLib((int32_t)(int)mxGetPr(ze13f49a01f)[(0x1110+2612-0x1b44)],SG_FPGA_IO3XX_BAR2)+zf7ccd17be8);ssSetPWorkValue(S,z0194338df7,(void*)z77b62f8983);
#endif
}static void sg_ModelStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE	
#endif
}static void sg_ModelStep(SimStruct*S){
#ifndef MATLAB_MEX_FILE
uint32_T i,channel;real_T*y;volatile z4ffeb08593*z77b62f8983=(volatile z4ffeb08593*)ssGetPWorkValue(S,z0194338df7);y=(real_T*)ssGetInputPortSignal(S,(0x296+6747-0x1cf1));for(i=(0xd1a+3707-0x1b95);i<mxGetN(zd7a15617ca);i++){channel=(uint32_T)mxGetPr(za9d8fb6bcf)[(0x2ca+2070-0xae0)]-(0x1185+2120-0x19cc);z77b62f8983->z7515281f6c[channel]=(uint32_T)mxGetPr(zd7a15617ca)[i]-(0x66f+955-0xa29);z77b62f8983->zd6e550175f[channel]=(uint32_T)y[i];z77b62f8983->z553991aa78=((0x8b2+42-0x8db)<<channel);z77b62f8983->z553991aa78=(0x1d0d+1342-0x224b);}
#endif
}static void sg_ModelStop(SimStruct*S){
#ifndef MATLAB_MEX_FILE    
#endif
}
#include "sg_sfcn_glue.h"   


// Copyright 2006-2026 Speedgoat GmbH

#define 	S_FUNCTION_LEVEL 	(0x98a+1891-0x10eb)
#undef 		S_FUNCTION_NAME
#define 	S_FUNCTION_NAME 	sg_fpga_ad_sf_a1
#include 	<stddef.h>
#include 	<stdlib.h>
#include    <stdint.h>
#include    <stdbool.h>
#include 	"simstruc.h" 
#ifdef 		MATLAB_MEX_FILE
#include 	"mex.h"
#endif
#ifndef         MATLAB_MEX_FILE
#include        "sg_common.h"
#include        "sg_fpga_io3xx_util.h"
#endif
#include        "sg_callback.h"
#define zdf24515981        ((0x1750+2804-0x223f))
#define za9d8fb6bcf           ssGetSFcnParam(S, (0x2d2+7773-0x212f)) 
#define z4eb7791e75     ssGetSFcnParam(S, (0x15f1+807-0x1917)) 
#define z8fd86139be             ssGetSFcnParam(S, (0x1090+3145-0x1cd7))
#define z3832b85a32         ssGetSFcnParam(S, (0x11db+629-0x144d))
#define z58f464b4bb                ssGetSFcnParam(S, (0x3dc+2615-0xe0f))
#define z2b17e2ee3b              ((0x15ff+4334-0x26ec))
#define z0194338df7         ((0x13a4+2524-0x1d80))
#define zc5ce4cb81a              ((0x1cd7+19-0x1ce8))
#define z8caad2a8e6              ((0xfb+8065-0x207c))
#define z5bfe7a2613            ((0xc63+266-0xd6c))
#define z2e6483d505              ((0x1fc4+748-0x22b0))
static char msg[(0x17f3+2653-0x2150)];struct zfe084664e7{uint32_t z0754dd67cc;uint32_t zc78a7188e6;uint32_t zaf91a33927;uint32_t done;int32_t data[(0x2cf+3848-0x11c7)];};static void mdlInitializeSizes(SimStruct*S){uint32_t i,za0df33019b;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0xeeb+2825-0x19f4));ssSetNumDiscStates(S,(0xf12+4662-0x2148));za0df33019b=(uint32_t)mxGetN(za9d8fb6bcf);if(!ssSetNumOutputPorts(S,za0df33019b)){return;}for(i=(0x3e7+2897-0xf38);i<za0df33019b;i++){ssSetOutputPortWidth(S,i,(0x3a+183-0xf0));}if(!ssSetNumInputPorts(S,(0x1d9b+1987-0x255e))){return;}ssSetNumSampleTimes(S,(0x576+2345-0xe9e));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0xee7+5413-0x240c));ssSetNumNonsampledZCs(S,(0x388+4766-0x1626));for(i=(0xba+5171-0x14ed);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x8b3+2313-0x11bc));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0xff3+672-0x1293)]==-1.0){ssSetSampleTime(S,(0x1180+5359-0x266f),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x1e4+267-0x2ef),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x638+4176-0x1688),mxGetPr(z3832b85a32)[(0x19b+4629-0x13b0)]);ssSetOffsetTime(S,(0x157d+1815-0x1c94),0.0);}}static void sg_ModelLoad(SimStruct*S){
#ifndef MATLAB_MEX_FILE
uintptr_t z70fcda5f5d;volatile struct zfe084664e7*z8a0c00cf66;int moduleId=(int)mxGetScalar(z58f464b4bb);char*boardName=io3xxGetBoardNameSgLib(moduleId);z70fcda5f5d=(uintptr_t)io3xxGetAddressSgLib((int)mxGetPr(z58f464b4bb)[(0x1aec+1178-0x1f86)],SG_FPGA_IO3XX_BAR2);if(z70fcda5f5d==(0x1030+4917-0x2365)){ssSetErrorStatus(S,pSgErrorStr);return;}uint32_t zf7ccd17be8=(0x130+8329-0x21b9);if(sg_fpga_io3xx_getCmBaseAddress(moduleId,ADBASE,&zf7ccd17be8)){sprintf(msg,"\x25\x73\x20\x41\x44\x20\x6d\x6f\x64\x75\x6c\x65\x3a\x20\x4f\x66\x66\x73\x65\x74\x20\x6c\x6f\x6f\x6b\x75\x70\x20\x75\x6e\x73\x75\x63\x63\x65\x73\x73\x66\x75\x6c\x21" "\n",boardName);ssSetErrorStatus(S,msg);return;}z8a0c00cf66=(struct zfe084664e7*)(z70fcda5f5d+zf7ccd17be8);ssSetPWorkValue(S,z0194338df7,(void*)z8a0c00cf66);switch((uint32_t)mxGetPr(z8fd86139be)[(0x1066+4692-0x22ba)]){case(0x2fa+5184-0x1739):ssSetRWorkValue(S,z8caad2a8e6,3200.0);ssSetRWorkValue(S,z5bfe7a2613,10.24);break;case(0x1b5+4224-0x1233):ssSetRWorkValue(S,z8caad2a8e6,6400.0);ssSetRWorkValue(S,z5bfe7a2613,5.12);break;case(0xd6+6733-0x1b20):ssSetRWorkValue(S,z8caad2a8e6,12800);ssSetRWorkValue(S,z5bfe7a2613,2.56);break;case(0x672+4344-0x1766):ssSetRWorkValue(S,z8caad2a8e6,25600);ssSetRWorkValue(S,z5bfe7a2613,1.28);break;}
#endif   
}static void sg_ModelStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
volatile struct zfe084664e7*z8a0c00cf66=(struct zfe084664e7*)(ssGetPWorkValue(S,z0194338df7));z8a0c00cf66->z0754dd67cc=(uint32_t)mxGetPr(z8fd86139be)[(0x890+2265-0x1169)]-(0x531+1105-0x981);z8a0c00cf66->zaf91a33927=(0x222a+155-0x22c5);z8a0c00cf66->zc78a7188e6=(0x105b+4838-0x2340);z8a0c00cf66->zc78a7188e6=(0x530+6744-0x1f88);z8a0c00cf66->zaf91a33927=(uint32_t)mxGetPr(z4eb7791e75)[(0x4ad+1693-0xb4a)]-(0x137d+2822-0x1e82);
#endif
}static void sg_ModelStep(SimStruct*S){
#ifndef MATLAB_MEX_FILE
uint32_t i,channel,done;double*y;volatile struct zfe084664e7*z8a0c00cf66=(struct zfe084664e7*)(ssGetPWorkValue(S,z0194338df7));double z0754dd67cc=ssGetRWorkValue(S,z8caad2a8e6);if((uint32_t)mxGetPr(z4eb7791e75)[(0x207+2019-0x9ea)]==(0xd87+2262-0x165c)){z8a0c00cf66->zc78a7188e6=(0x1394+47-0x13c2);z8a0c00cf66->zc78a7188e6=(0x153b+204-0x1607);}done=(0x225+8653-0x23f2);for(i=(0x1819+1755-0x1ef4);i<mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0xf98+3517-0x1d54);done|=((0x44b+6657-0x1e4b)<<channel);}while((z8a0c00cf66->done&done)!=done);for(i=(0x5ab+4118-0x15c1);i<mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0xb46+878-0xeb3);y=(double*)ssGetOutputPortSignal(S,i);y[(0x12c6+3727-0x2155)]=(z8a0c00cf66->data[channel]-32768)/z0754dd67cc;}
#endif
}static void sg_ModelStop(SimStruct*S){
#ifndef MATLAB_MEX_FILE    
#endif
}
#include "sg_sfcn_glue.h"   


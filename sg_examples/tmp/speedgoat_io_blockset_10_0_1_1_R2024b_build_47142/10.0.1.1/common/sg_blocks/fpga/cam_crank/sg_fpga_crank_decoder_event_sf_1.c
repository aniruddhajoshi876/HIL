// Copyright 2006-2026 Speedgoat GmbH

#define 	S_FUNCTION_LEVEL 	(0x1bf7+1884-0x2351)
#undef 		S_FUNCTION_NAME
#define 	S_FUNCTION_NAME 	sg_fpga_crank_decoder_event_sf_1
#include 	<stddef.h>
#include 	<stdlib.h>
#include    <stdint.h>
#include    <stdbool.h>
#include 	"simstruc.h" 
#ifdef MATLAB_MEX_FILE
#include "mex.h"
#endif
#ifndef MATLAB_MEX_FILE
#include "sg_common.h"
#include "sg_fpga_io3xx_util.h"
#include "sg_printf.h"
#endif
#include "sg_callback.h"
typedef enum{CHANNEL,ze344b15ab1,z6c561dc4d0,z9664ce1e38,z053e0f8837,zccf541aa07,ID,z88c63e0ba1,zdf24515981}z78601b6217;
#define za9d8fb6bcf                 ssGetSFcnParam(S, CHANNEL) 
#define z3832b85a32               ssGetSFcnParam(S, ze344b15ab1)
#define z7cd927ffe6             ssGetSFcnParam(S, z6c561dc4d0) 
#define z399d208005     ssGetSFcnParam(S, z9664ce1e38) 
#define zff81a2b69b             ssGetSFcnParam(S, z053e0f8837) 
#define z6742a813c5    ssGetSFcnParam(S, zccf541aa07) 
#define z58f464b4bb                      ssGetSFcnParam(S, ID) 
#define za08eaecce0               ssGetSFcnParam(S, z88c63e0ba1) 
#define z2e6483d505                  (0xf07+5207-0x235e)
#define zc5ce4cb81a                  (0x13e5+4808-0x26ad)
#define z2b17e2ee3b                  (0x6fc+4949-0x1a50)
#define z0194338df7             (0x199d+2-0x199f)
#define z5bbcf8be2c                (0x1ecd+2047-0x26cb)
static char msg[(0x1896+3722-0x2620)];typedef struct{uint32_t version;uint32_t enable[(0x4e8+1920-0xc66)];uint32_t z230b1088f7[(0x577+506-0x731)];uint32_t z2ed09dc5c9[(0xbd0+6800-0x2620)];uint32_t z294275e553[(0x78d+6799-0x21dc)];uint32_t z2811672a69[(0xe59+1737-0x14e2)];}zf87eb4a563;static void mdlInitializeSizes(SimStruct*S){uint32_t i,za0df33019b;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x4d4+5187-0x1917));ssSetNumDiscStates(S,(0x151b+869-0x1880));ssSetNumInputPorts(S,(0x1faa+857-0x2303));za0df33019b=(0x2e7+1092-0x72b);ssSetNumOutputPorts(S,za0df33019b);for(i=(0x13b4+390-0x153a);i<za0df33019b;i++){ssSetOutputPortWidth(S,i,mxGetN(za9d8fb6bcf));}ssSetNumSampleTimes(S,(0x3c0+5062-0x1785));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0xe05+5398-0x231b));ssSetNumNonsampledZCs(S,(0x452+6132-0x1c46));for(i=(0x6b8+5872-0x1da8);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x21ab+320-0x22eb));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0x21ca+1322-0x26f4)]==-1.0){ssSetSampleTime(S,(0x46+7872-0x1f06),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x6a5+8244-0x26d9),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0xf52+5165-0x237f),mxGetPr(z3832b85a32)[(0xc27+5587-0x21fa)]);ssSetOffsetTime(S,(0x57+983-0x42e),0.0);}}static void sg_ModelLoad(SimStruct*S){
#ifndef MATLAB_MEX_FILE
volatile zf87eb4a563*ze5c21f4368;void*bar2ptr;int moduleId=(int)mxGetScalar(z58f464b4bb);char*boardName=io3xxGetBoardNameSgLib(moduleId);if(!io3xxGetAddressSgLib((int32_t)(int)mxGetPr(z58f464b4bb)[(0x3a0+2319-0xcaf)],SG_FPGA_IO3XX_BAR2)){ssSetErrorStatus(S,pSgErrorStr);return;}uint32_t zf7ccd17be8=(0x4d9+7718-0x22ff);if(sg_fpga_io3xx_getCmBaseAddress(moduleId,CRANK_DECODER_EVENT_BASE,&zf7ccd17be8)){sprintf(msg,"\x25\x73\x20\x43\x72\x61\x6e\x6b\x20\x44\x65\x63\x6f\x64\x65\x72\x20\x45\x76\x65\x6e\x74\x20\x6d\x6f\x64\x75\x6c\x65\x3a\x20\x4f\x66\x66\x73\x65\x74\x20\x6c\x6f\x6f\x6b\x75\x70\x20\x75\x6e\x73\x75\x63\x63\x65\x73\x73\x66\x75\x6c\x21" "\n",boardName);ssSetErrorStatus(S,msg);return;}bar2ptr=io3xxGetAddressSgLib((int32_t)(int)mxGetPr(z58f464b4bb)[(0x1159+3336-0x1e61)],SG_FPGA_IO3XX_BAR2);ze5c21f4368=(zf87eb4a563*)((uintptr_t)bar2ptr+(uintptr_t)zf7ccd17be8);ssSetPWorkValue(S,z0194338df7,(void*)ze5c21f4368);if(sg_isFirstModelLoad()){if(sg_fpga_io3xx_checkCodeModuleVersion(ze5c21f4368->version,z5bbcf8be2c,moduleId)){sprintf(msg,"\x25\x73\x20\x77\x72\x6f\x6e\x67\x20\x76\x65\x72\x73\x69\x6f\x6e\x20\x6f\x66\x20\x43\x72\x61\x6e\x6b\x20\x44\x65\x63\x6f\x64\x65\x72\x20\x45\x76\x65\x6e\x74\x20\x63\x6f\x64\x65\x20\x6d\x6f\x64\x75\x6c\x65\x21" "\n",boardName);ssSetErrorStatus(S,msg);return;}}
#endif  
}static void sg_ModelStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
uint32_t i;uint32_t channel,zec8bd79de8,z8124be4115;double z230b1088f7,z64198f8f6d;double z7dab6f6958;volatile zf87eb4a563*ze5c21f4368;ze5c21f4368=(zf87eb4a563*)(ssGetPWorkValue(S,z0194338df7));z7dab6f6958=(double)mxGetPr(za08eaecce0)[(0x78a+1071-0xbb9)];for(i=(0x1344+1269-0x1839);i<mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0x1df7+1194-0x22a0);z230b1088f7=(double)mxGetPr(z7cd927ffe6)[i];z64198f8f6d=(double)180.0/z230b1088f7;ze5c21f4368->z230b1088f7[channel]=(uint32_t)z230b1088f7;ze5c21f4368->z2ed09dc5c9[channel]=(uint32_t)mxGetPr(z399d208005)[i];ze5c21f4368->z294275e553[channel]=(uint32_t)((double)mxGetPr(zff81a2b69b)[i]/z64198f8f6d);ze5c21f4368->z2811672a69[channel]=(uint32_t)((double)mxGetPr(z6742a813c5)[i]*z7dab6f6958);}zec8bd79de8=ze5c21f4368->enable[(0x21f+6119-0x1a06)];z8124be4115=ze5c21f4368->enable[(0x460+8511-0x259e)];for(i=(0x9f6+853-0xd4b);i<mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0x138c+4847-0x267a);if(channel<(0x1573+603-0x17ae)){zec8bd79de8|=((0x1438+4754-0x26c9)<<channel);}else{z8124be4115|=((0x22cc+716-0x2597)<<(channel-(0x104+8617-0x228d)));}}ze5c21f4368->enable[(0x211+200-0x2d9)]=zec8bd79de8;ze5c21f4368->enable[(0x16f0+2686-0x216d)]=z8124be4115;
#endif
}static void sg_ModelStep(SimStruct*S){
#ifndef MATLAB_MEX_FILE
#endif
}static void sg_ModelStop(SimStruct*S){
#ifndef MATLAB_MEX_FILE
volatile zf87eb4a563*ze5c21f4368;ze5c21f4368=(zf87eb4a563*)(ssGetPWorkValue(S,z0194338df7));ze5c21f4368->enable[(0x20e9+920-0x2481)]=(0x40a+4431-0x1559);ze5c21f4368->enable[(0x1adf+2533-0x24c3)]=(0x14d7+397-0x1664);
#endif
}
#include "sg_sfcn_glue.h"   


// Copyright 2006-2026 Speedgoat GmbH

#define 	S_FUNCTION_LEVEL 	(0xc13+4750-0x1e9f)
#undef 		S_FUNCTION_NAME
#define 	S_FUNCTION_NAME 	sg_fpga_i2cs_sf_a1
#include 	<stddef.h>
#include 	<stdlib.h>
#include 	"simstruc.h" 
#ifdef 		MATLAB_MEX_FILE
#include 	"mex.h"
#endif
#ifndef         MATLAB_MEX_FILE
#include        "sg_common.h"
#include        "sg_fpga_io3xx_util.h"
#include        "sg_printf.h"
#endif
#include        "sg_callback.h"
#define ze13f49a01f         ssGetSFcnParam(S, (0x6fc+3433-0x1465)) 
#define za9d8fb6bcf           ssGetSFcnParam(S, (0x387+4650-0x15b0)) 
#define z4bd6be73a3           ssGetSFcnParam(S, (0xe2d+454-0xff1))
#define z7c2036cdc8    ssGetSFcnParam(S, (0x3c9+5478-0x192c))
#define z3832b85a32         ssGetSFcnParam(S, (0x1d27+2156-0x258f))
#define zdf24515981                        ((0xdeb+2427-0x1761))
#define z2e6483d505              ((0x1f8a+480-0x216a))
#define zc5ce4cb81a              ((0x38+7432-0x1d40))
#define z2b17e2ee3b              ((0x1045+978-0x1416))
#define z0194338df7         ((0xb24+6698-0x254e))
#define z5bbcf8be2c            (0xaa2+3151-0x16f0)
static char_T msg[(0x434+9147-0x26ef)];typedef struct z4ffeb08593{uint32_T enable;uint32_T clear;uint32_T z553991aa78;uint32_T z039626e71b[(0x162+5534-0x16e0)];uint32_T z7515281f6c[(0x1c87+1768-0x234f)];uint32_T zd6e550175f[(0x976+642-0xbd8)];uint32_T z2678040317[(0x1949+1429-0x1ebe)];uint32_T skipRegAddress;uint32_T version;}z4ffeb08593;static void mdlInitializeSizes(SimStruct*S){uint32_T i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0xb02+2139-0x135d));ssSetNumDiscStates(S,(0x888+6950-0x23ae));if(!ssSetNumOutputPorts(S,(0x18c0+161-0x1961))){return;}if(!ssSetNumInputPorts(S,(0x6dc+1029-0xae1))){return;}ssSetNumSampleTimes(S,(0x1524+1252-0x1a07));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x913+5868-0x1fff));ssSetNumNonsampledZCs(S,(0x1910+1315-0x1e33));for(i=(0xb40+1742-0x120e);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x823+5626-0x1e1d));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0x173+2670-0xbe1)]==-1.0){ssSetSampleTime(S,(0xc8c+3126-0x18c2),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0xf0d+309-0x1042),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x9b4+2051-0x11b7),mxGetPr(z3832b85a32)[(0x50c+7541-0x2281)]);ssSetOffsetTime(S,(0x19f6+1788-0x20f2),0.0);}}static void sg_ModelLoad(SimStruct*S){
#ifndef MATLAB_MEX_FILE
int moduleId=(int)mxGetScalar(ze13f49a01f);char*boardName=io3xxGetBoardNameSgLib(moduleId);volatile z4ffeb08593*z77b62f8983;if(!io3xxGetAddressSgLib((int32_t)(int)mxGetPr(ze13f49a01f)[(0x14a0+4224-0x2520)],SG_FPGA_IO3XX_BAR2)){ssSetErrorStatus(S,pSgErrorStr);return;}uint32_t zf7ccd17be8=(0x1543+4275-0x25f6);if(sg_fpga_io3xx_getCmBaseAddress(moduleId,I2CS_BASE,&zf7ccd17be8)){sprintf(msg,"\x25\x73\x20\x49\x32\x43\x53\x20\x6d\x6f\x64\x75\x6c\x65\x3a\x20\x4f\x66\x66\x73\x65\x74\x20\x6c\x6f\x6f\x6b\x75\x70\x20\x75\x6e\x73\x75\x63\x63\x65\x73\x73\x66\x75\x6c\x21" "\n",boardName);ssSetErrorStatus(S,msg);return;}z77b62f8983=(volatile z4ffeb08593*)((uintptr_t)io3xxGetAddressSgLib((int32_t)(int)mxGetPr(ze13f49a01f)[(0xc29+6059-0x23d4)],SG_FPGA_IO3XX_BAR2)+zf7ccd17be8);ssSetPWorkValue(S,z0194338df7,(void*)z77b62f8983);if(sg_fpga_io3xx_checkCodeModuleVersion(z77b62f8983->version,z5bbcf8be2c,moduleId)){sprintf(msg,"\x25\x73\x20\x77\x72\x6f\x6e\x67\x20\x76\x65\x72\x73\x69\x6f\x6e\x20\x6f\x66\x20\x49\x32\x43\x53\x20\x63\x6f\x64\x65\x20\x6d\x6f\x64\x75\x6c\x65\x21" "\n",boardName);ssSetErrorStatus(S,msg);return;}
#endif
}static void sg_ModelStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE	
uint32_T channel;i2cState_t*z48b6195cd9;volatile z4ffeb08593*z77b62f8983=(volatile z4ffeb08593*)ssGetPWorkValue(S,z0194338df7);channel=(uint32_T)mxGetPr(za9d8fb6bcf)[(0xf7a+2561-0x197b)]-(0x11a1+807-0x14c7);z77b62f8983->z039626e71b[channel]=(uint32_T)mxGetPr(z4bd6be73a3)[(0x6f0+3874-0x1612)];io3xxGetPointerI2cStateSgLib((int)mxGetPr(ze13f49a01f)[(0x88a+5196-0x1cd6)],&z48b6195cd9);sg_lockMutex(z48b6195cd9->mutex);z48b6195cd9->skipRegAddress|=((uint32_T)mxGetPr(z7c2036cdc8)[(0x18d+1117-0x5ea)]<<channel);z77b62f8983->skipRegAddress=z48b6195cd9->skipRegAddress;sg_unlockMutex(z48b6195cd9->mutex);z77b62f8983->enable|=((0x49f+7989-0x23d3)<<channel);
#endif
}static void sg_ModelStep(SimStruct*S){
#ifndef MATLAB_MEX_FILE
#endif
}static void sg_ModelStop(SimStruct*S){
#ifndef MATLAB_MEX_FILE
volatile z4ffeb08593*z77b62f8983=(volatile z4ffeb08593*)(ssGetPWorkValue(S,z0194338df7));if(!sg_isModelInit()){z77b62f8983->enable=(0x54a+2232-0xe02);}
#endif
}
#include "sg_sfcn_glue.h"   


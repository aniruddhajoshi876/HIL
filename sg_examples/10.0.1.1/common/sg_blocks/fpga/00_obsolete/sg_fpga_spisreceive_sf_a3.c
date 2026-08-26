// Copyright 2006-2026 Speedgoat GmbH

#define 	S_FUNCTION_LEVEL 	(0xabc+2282-0x13a4)
#undef 		S_FUNCTION_NAME
#define 	S_FUNCTION_NAME 	sg_fpga_spisreceive_sf_a3
#include 	<stddef.h>
#include 	<stdlib.h>
#include  <stdint.h>
#include 	"simstruc.h"
#ifdef 		MATLAB_MEX_FILE
#include 	"mex.h"
#endif
#ifndef  MATLAB_MEX_FILE
#include "sg_common.h"
#include "sg_fpga_io3xx_util.h"
#include "sg_callback_legacy.h"
#include "sg_printf.h"
#endif
enum{zf80bd68bc8,ID,CHANNEL,ze344b15ab1,PCI_SLOT,WIDTH,zdf24515981};
#define z533b11d03f               ssGetSFcnParam(S, zf80bd68bc8           )
#define z58f464b4bb                      ssGetSFcnParam(S, ID                  )
#define za9d8fb6bcf                 ssGetSFcnParam(S, CHANNEL             )
#define z3832b85a32               ssGetSFcnParam(S, ze344b15ab1           )
#define ze7b39f8507                ssGetSFcnParam(S, PCI_SLOT            )
#define z3d4ad966bd                   ssGetSFcnParam(S, WIDTH               )
#define z2e6483d505            (0x1a13+723-0x1ce6)
#define zc5ce4cb81a            (0x355+5542-0x18fb)
#define z2b17e2ee3b            (0x729+6203-0x1f63)
#define z93d7dbe681       (0xc77+4556-0x1e43)
#define za7eea138ec								212992
static char_T msg[(0xf52+2620-0x188e)];typedef struct{volatile uint32_t enable;volatile uint32_t z13e3aff50f;volatile uint32_t MSBFirst;volatile uint32_t z79c39f7a01;volatile uint32_t z21ab44ce3e;volatile uint32_t z05095ec8c5;volatile uint32_t z633e4d0b43[(0x10aa+3591-0x1ea1)];volatile uint32_t z1907ddba6c[(0x12f6+3609-0x20ff)];volatile uint32_t z17cbe2a22e[(0x401+5036-0x179d)];volatile uint32_t z45128425fd[(0x413+114-0x475)];}ze823aa19b7;static void mdlInitializeSizes(SimStruct*S){uint32_t i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0xcd+4606-0x12cb));ssSetNumDiscStates(S,(0xa34+6640-0x2424));ssSetNumOutputPorts(S,mxGetN(za9d8fb6bcf));for(i=(0xf06+4263-0x1fad);i<mxGetN(za9d8fb6bcf);i++){ssSetOutputPortWidth(S,i,(uint32_t)mxGetPr(z3d4ad966bd)[(0xa5c+1587-0x108f)]+(0x18eb+3607-0x2701));}ssSetNumSampleTimes(S,(0x15d0+3370-0x22f9));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x8d0+5314-0x1d92));ssSetNumNonsampledZCs(S,(0x461+5814-0x1b17));for(i=(0x5e8+6611-0x1fbb);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x199+2359-0xad0));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0x1cf+1801-0x8d8)]==-1.0){ssSetSampleTime(S,(0x1ba+4014-0x1168),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0xfba+283-0x10d5),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x2e6+7701-0x20fb),mxGetPr(z3832b85a32)[(0xd91+2746-0x184b)]);ssSetOffsetTime(S,(0x447+7819-0x22d2),0.0);}}
#define MDL_START
static void mdlStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
int32_t bus,slot;uint32_t boardType;sg_fpga_io3xxModuleIdT moduleId;volatile ze823aa19b7*z380706df00;boardType=(uint32_t)mxGetPr(z533b11d03f)[(0x6a7+511-0x8a6)];if((int32_t)sg_fpga_IO3xxGetModuleId(boardType,&moduleId)<(0x485+6734-0x1ed3)){sprintf(msg,"\x53\x50\x49\x20\x62\x6c\x6f\x63\x6b\x3a\x20\x62\x6f\x61\x72\x64\x20\x74\x79\x70\x65\x20\x69\x6e\x63\x6f\x72\x72\x65\x63\x74\x2e");ssSetErrorStatus(S,msg);}if(mxGetN(ze7b39f8507)==(0x904+206-0x9d1)){bus=(0x595+925-0x932);slot=(int_T)mxGetPr(ze7b39f8507)[(0xf81+275-0x1094)];}else{bus=(int_T)mxGetPr(ze7b39f8507)[(0x225+6947-0x1d48)];slot=(int_T)mxGetPr(ze7b39f8507)[(0xa5+1769-0x78d)];}if(!io3xxGetAddressSgLib((int32_t)(int)mxGetPr(z58f464b4bb)[(0x603+6490-0x1f5d)],SG_FPGA_IO3XX_BAR2)){ssSetErrorStatus(S,pSgErrorStr);return;}z380706df00=(volatile ze823aa19b7*)((uintptr_t)io3xxGetAddressSgLib((int32_t)(int)mxGetPr(z58f464b4bb)[(0xa8+3760-0xf58)],SG_FPGA_IO3XX_BAR2)+za7eea138ec);ssSetPWorkValue(S,z93d7dbe681,(void*)z380706df00);
#endif
}static void mdlOutputs(SimStruct*S,int_T z27c0327a06){
#ifndef MATLAB_MEX_FILE
volatile ze823aa19b7*z380706df00;uint32_t z26dbd73a5e,i,width,count;double*out;uint32_t channel;z380706df00=(volatile ze823aa19b7*)ssGetPWorkValue(S,z93d7dbe681);width=(uint32_t)mxGetPr(z3d4ad966bd)[(0xd08+5593-0x22e1)]+(0x11bc+2082-0x19dd);for(i=(0x571+7882-0x243b);i<mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0xb15+2493-0x14d1);count=z380706df00->z45128425fd[channel];out=ssGetOutputPortSignal(S,i);if(count>(0x4b9+356-0x61d)){for(z26dbd73a5e=(0x1854+2361-0x218d);z26dbd73a5e<(uint8_T)mxGetPr(z3d4ad966bd)[(0x577+8360-0x261f)];z26dbd73a5e++){out[z26dbd73a5e]=(0x8e8+2928-0x1458);}for(z26dbd73a5e=(0x1811+2673-0x2282);z26dbd73a5e<count;z26dbd73a5e++){z380706df00->z17cbe2a22e[channel]=z26dbd73a5e;out[z26dbd73a5e+(0xd61+6377-0x2649)]=(double)z380706df00->z1907ddba6c[channel];}z380706df00->z05095ec8c5=((0x1675+3711-0x24f3)<<channel);z380706df00->z05095ec8c5=(0x9d0+2431-0x134f);}out[(0xe07+436-0xfbb)]=(double)count;}
#endif
}static void mdlTerminate(SimStruct*S){
#ifndef MATLAB_MEX_FILE
#endif
}
#include "sg_sfcn_glue.h"   


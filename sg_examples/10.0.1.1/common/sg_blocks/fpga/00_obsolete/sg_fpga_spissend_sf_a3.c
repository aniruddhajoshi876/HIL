// Copyright 2006-2026 Speedgoat GmbH

#define 	S_FUNCTION_LEVEL 	(0x1772+492-0x195c)
#undef 		S_FUNCTION_NAME
#define 	S_FUNCTION_NAME 	sg_fpga_spissend_sf_a3
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
#define z2e6483d505            (0x7f4+369-0x965)
#define zc5ce4cb81a            (0xa10+7269-0x2675)
#define z2b17e2ee3b            (0x1885+2665-0x22ed)
#define z93d7dbe681       (0x67a+6248-0x1ee2)
#define za7eea138ec								212992
static char_T msg[(0x1603+3227-0x219e)];typedef struct{volatile uint32_t enable;volatile uint32_t z13e3aff50f;volatile uint32_t MSBFirst;volatile uint32_t z79c39f7a01;volatile uint32_t z21ab44ce3e;volatile uint32_t z05095ec8c5;volatile uint32_t z633e4d0b43[(0x690+2332-0xf9c)];volatile uint32_t z1907ddba6c[(0x517+311-0x63e)];volatile uint32_t z17cbe2a22e[(0x87+8749-0x22a4)];volatile uint32_t z45128425fd[(0x10c+2238-0x9ba)];}ze823aa19b7;static void mdlInitializeSizes(SimStruct*S){uint32_t i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x7db+1648-0xe4b));ssSetNumDiscStates(S,(0x851+7505-0x25a2));ssSetNumOutputPorts(S,(0x1190+2179-0x1a13));ssSetNumInputPorts(S,mxGetN(za9d8fb6bcf));for(i=(0x145+890-0x4bf);i<mxGetN(za9d8fb6bcf);i++){ssSetInputPortWidth(S,i,(uint32_t)mxGetPr(z3d4ad966bd)[(0x1176+4680-0x23be)]+(0x14cb+3421-0x2227));ssSetInputPortDirectFeedThrough(S,i,(0x1811+1708-0x1ebc));ssSetInputPortRequiredContiguous(S,i,(0x8a1+550-0xac6));}ssSetNumSampleTimes(S,(0x59f+5017-0x1937));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0xd9+6621-0x1ab6));ssSetNumNonsampledZCs(S,(0x1d6d+440-0x1f25));for(i=(0x11eb+487-0x13d2);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x1d40+198-0x1e06));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0x806+1725-0xec3)]==-1.0){ssSetSampleTime(S,(0xab0+1741-0x117d),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x1c64+796-0x1f80),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x870+1039-0xc7f),mxGetPr(z3832b85a32)[(0xa6d+2941-0x15ea)]);ssSetOffsetTime(S,(0x4df+5302-0x1995),0.0);}}
#define MDL_START
static void mdlStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
int32_t bus,slot;uint32_t boardType;sg_fpga_io3xxModuleIdT moduleId;volatile ze823aa19b7*z380706df00;boardType=(uint32_t)mxGetPr(z533b11d03f)[(0xf01+4965-0x2266)];if((int32_t)sg_fpga_IO3xxGetModuleId(boardType,&moduleId)<(0x1a01+1610-0x204b)){sprintf(msg,"\x53\x50\x49\x20\x62\x6c\x6f\x63\x6b\x3a\x20\x62\x6f\x61\x72\x64\x20\x74\x79\x70\x65\x20\x69\x6e\x63\x6f\x72\x72\x65\x63\x74\x2e");ssSetErrorStatus(S,msg);}if(mxGetN(ze7b39f8507)==(0x7d5+3178-0x143e)){bus=(0x336+2070-0xb4c);slot=(int_T)mxGetPr(ze7b39f8507)[(0x1643+418-0x17e5)];}else{bus=(int_T)mxGetPr(ze7b39f8507)[(0x3e9+6525-0x1d66)];slot=(int_T)mxGetPr(ze7b39f8507)[(0xd23+3991-0x1cb9)];}if(!io3xxGetAddressSgLib((int32_t)(int)mxGetPr(z58f464b4bb)[(0xe98+3460-0x1c1c)],SG_FPGA_IO3XX_BAR2)){ssSetErrorStatus(S,pSgErrorStr);return;}z380706df00=(volatile ze823aa19b7*)((uintptr_t)io3xxGetAddressSgLib((int32_t)(int)mxGetPr(z58f464b4bb)[(0x15f3+1797-0x1cf8)],SG_FPGA_IO3XX_BAR2)+za7eea138ec);ssSetPWorkValue(S,z93d7dbe681,(void*)z380706df00);
#endif
}static void mdlOutputs(SimStruct*S,int_T z27c0327a06){
#ifndef MATLAB_MEX_FILE     
volatile ze823aa19b7*z380706df00;uint32_t z26dbd73a5e,i,width,count;double*in;uint32_t channel;z380706df00=(volatile ze823aa19b7*)ssGetPWorkValue(S,z93d7dbe681);width=(uint32_t)mxGetPr(z3d4ad966bd)[(0xbba+6621-0x2597)]+(0x59d+5512-0x1b24);for(i=(0x94+447-0x253);i<mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0x1539+2296-0x1e30);in=(double*)ssGetInputPortSignal(S,i);count=(uint32_t)in[(0xa22+6795-0x24ad)];for(z26dbd73a5e=(0x80c+3961-0x1785);z26dbd73a5e<count;z26dbd73a5e++){z380706df00->z633e4d0b43[channel]=(uint32_t)in[z26dbd73a5e+(0x1c94+1737-0x235c)];z380706df00->z17cbe2a22e[channel]=z26dbd73a5e;z380706df00->z21ab44ce3e=((0x19d0+1131-0x1e3a)<<channel);z380706df00->z21ab44ce3e=(0x1e0f+1332-0x2343);}}
#endif
}static void mdlTerminate(SimStruct*S){
#ifndef MATLAB_MEX_FILE   
#endif
}
#include "sg_sfcn_glue.h"   


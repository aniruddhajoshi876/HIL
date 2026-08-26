// Copyright 2006-2026 Speedgoat GmbH

#define 	S_FUNCTION_LEVEL 	(0x396+8822-0x260a)
#undef 		S_FUNCTION_NAME
#define 	S_FUNCTION_NAME 	sg_fpga_spis_sf_a3
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
enum{zf80bd68bc8,ID,CHANNEL,PCI_SLOT,z13e3aff50f,z79c39f7a01,zba9d17be1b,zdf24515981};
#define z533b11d03f               ssGetSFcnParam(S, zf80bd68bc8           )
#define z58f464b4bb                      ssGetSFcnParam(S, ID                  )
#define za9d8fb6bcf                 ssGetSFcnParam(S, CHANNEL             )
#define ze7b39f8507                ssGetSFcnParam(S, PCI_SLOT            )
#define z86af52d74e                    ssGetSFcnParam(S, z13e3aff50f                )
#define z31fb671cb8                    ssGetSFcnParam(S, z79c39f7a01                )
#define zea4d7ef473                ssGetSFcnParam(S, zba9d17be1b            )
#define z2e6483d505            (0x8bb+3667-0x170e)
#define zc5ce4cb81a            (0xead+822-0x11e3)
#define z2b17e2ee3b            (0xdb6+869-0x111a)
#define z93d7dbe681       (0x1b54+2543-0x2543)
#define za7eea138ec								212992
static char_T msg[(0xf83+6254-0x26f1)];typedef struct{volatile uint32_t enable;volatile uint32_t z13e3aff50f;volatile uint32_t MSBFirst;volatile uint32_t z79c39f7a01;volatile uint32_t z21ab44ce3e;volatile uint32_t z05095ec8c5;volatile uint32_t z633e4d0b43[(0x1453+1827-0x1b66)];volatile uint32_t z1907ddba6c[(0x3ed+2784-0xebd)];volatile uint32_t z17cbe2a22e[(0x797+2653-0x11e4)];volatile uint32_t z45128425fd[(0x785+3646-0x15b3)];}ze823aa19b7;static void mdlInitializeSizes(SimStruct*S){uint32_t i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0xaac+2968-0x1644));ssSetNumDiscStates(S,(0x26f+3390-0xfad));ssSetNumOutputPorts(S,(0x77b+4730-0x19f5));ssSetNumInputPorts(S,(0xde4+26-0xdfe));ssSetNumSampleTimes(S,(0xc5a+2201-0x14f2));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x74b+5494-0x1cc1));ssSetNumNonsampledZCs(S,(0x878+6155-0x2083));for(i=(0x14bf+3052-0x20ab);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0xdab+3829-0x1ca0));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){ssSetSampleTime(S,(0x337+3670-0x118d),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x41b+2812-0xf17),FIXED_IN_MINOR_STEP_OFFSET);}
#define MDL_START
static void mdlStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
int32_t bus,slot;uint32_t boardType;sg_fpga_io3xxModuleIdT moduleId;volatile ze823aa19b7*z380706df00;boardType=(uint32_t)mxGetPr(z533b11d03f)[(0x663+304-0x793)];if((int32_t)sg_fpga_IO3xxGetModuleId(boardType,&moduleId)<(0xc6b+5130-0x2075)){sprintf(msg,"\x53\x50\x49\x20\x62\x6c\x6f\x63\x6b\x3a\x20\x62\x6f\x61\x72\x64\x20\x74\x79\x70\x65\x20\x69\x6e\x63\x6f\x72\x72\x65\x63\x74\x2e");ssSetErrorStatus(S,msg);}if(mxGetN(ze7b39f8507)==(0xf7f+65-0xfbf)){bus=(0xb48+3955-0x1abb);slot=(int_T)mxGetPr(ze7b39f8507)[(0x518+4114-0x152a)];}else{bus=(int_T)mxGetPr(ze7b39f8507)[(0xc3b+1113-0x1094)];slot=(int_T)mxGetPr(ze7b39f8507)[(0x271+3952-0x11e0)];}if(!io3xxGetAddressSgLib((int32_t)(int)mxGetPr(z58f464b4bb)[(0x995+5690-0x1fcf)],SG_FPGA_IO3XX_BAR2)){ssSetErrorStatus(S,pSgErrorStr);return;}z380706df00=(volatile ze823aa19b7*)((uintptr_t)io3xxGetAddressSgLib((int32_t)(int)mxGetPr(z58f464b4bb)[(0x263+752-0x553)],SG_FPGA_IO3XX_BAR2)+za7eea138ec);ssSetPWorkValue(S,z93d7dbe681,(void*)z380706df00);
#endif
}static void mdlOutputs(SimStruct*S,int_T z27c0327a06){
#ifndef MATLAB_MEX_FILE       
#endif
}static void mdlTerminate(SimStruct*S){
#ifndef MATLAB_MEX_FILE   
volatile ze823aa19b7*z380706df00;uint16_t i;uint32_t channel,z1209c02d78,zdc0d676974,zbea4a89f24,z9e58a4ec45;z380706df00=(volatile ze823aa19b7*)ssGetPWorkValue(S,z93d7dbe681);z1209c02d78=z380706df00->enable;zdc0d676974=z380706df00->z13e3aff50f;zbea4a89f24=z380706df00->z79c39f7a01;z9e58a4ec45=z380706df00->MSBFirst;for(i=(0x254+6400-0x1b54);i<mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0x15a6+1677-0x1c32);z1209c02d78|=((0x17c+1787-0x876)<<channel);zdc0d676974|=(((uint32_t)mxGetPr(z86af52d74e)[i])<<channel);zbea4a89f24|=(((uint32_t)mxGetPr(z31fb671cb8)[i])<<channel);z9e58a4ec45|=(((uint32_t)mxGetPr(zea4d7ef473)[i])<<channel);}z380706df00->z13e3aff50f=zdc0d676974;z380706df00->MSBFirst=z9e58a4ec45;z380706df00->z79c39f7a01=zbea4a89f24;z380706df00->enable=z1209c02d78;
#endif
}
#include "sg_sfcn_glue.h"   


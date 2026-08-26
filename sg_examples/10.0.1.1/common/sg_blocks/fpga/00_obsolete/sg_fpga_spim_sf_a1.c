// Copyright 2006-2026 Speedgoat GmbH

#define 	S_FUNCTION_LEVEL 	(0x13e9+1158-0x186d)
#undef 		S_FUNCTION_NAME
#define 	S_FUNCTION_NAME 	sg_fpga_spim_sf_a1
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
enum{zf80bd68bc8,ID,CHANNEL,ze344b15ab1,PCI_SLOT,z0a8f104140,z5b624326a1,zb22cb2c4ac,z9439a8e903,zbc2a62807e,z7dc2625b3f,z13e3aff50f,z79c39f7a01,zba9d17be1b,WIDTH,z8f072e8f91,z398db81385,zdf24515981};
#define z533b11d03f               ssGetSFcnParam(S, zf80bd68bc8           )
#define z58f464b4bb                      ssGetSFcnParam(S, ID                  )
#define za9d8fb6bcf                 ssGetSFcnParam(S, CHANNEL             )
#define z3832b85a32               ssGetSFcnParam(S, ze344b15ab1           )
#define ze7b39f8507                ssGetSFcnParam(S, PCI_SLOT            )
#define zf6f668e67a         ssGetSFcnParam(S, z0a8f104140     )
#define zbb0d1897b2     ssGetSFcnParam(S, z5b624326a1 )
#define z8f7a5b7479           ssGetSFcnParam(S, zb22cb2c4ac       )
#define zdc5f8981b7              ssGetSFcnParam(S, z9439a8e903          )
#define zc09b06e5fc             ssGetSFcnParam(S, zbc2a62807e         )
#define z7039def18e              ssGetSFcnParam(S, z7dc2625b3f          )
#define z86af52d74e                    ssGetSFcnParam(S, z13e3aff50f                )
#define z31fb671cb8                    ssGetSFcnParam(S, z79c39f7a01                )
#define zea4d7ef473                ssGetSFcnParam(S, zba9d17be1b            )
#define z3d4ad966bd                   ssGetSFcnParam(S, WIDTH               )
#define z62fc1d1d8e              ssGetSFcnParam(S, z8f072e8f91          )
#define z08a9674173        ssGetSFcnParam(S, z398db81385    )
#define z2e6483d505            (0x5a8+4344-0x16a0)
#define zc5ce4cb81a            (0x8a+2046-0x888)
#define z2b17e2ee3b            (0x194f+3103-0x256d)
#define z93d7dbe681       (0xf34+440-0x10ec)
#define zc31238bb68           163840
static char_T msg[(0x261+2813-0xc5e)];typedef struct{volatile uint32_t enable;volatile uint32_t z13e3aff50f;volatile uint32_t MSBFirst;volatile uint32_t z79c39f7a01;volatile uint32_t z03312e422a;volatile uint32_t z21ab44ce3e;volatile uint32_t z05095ec8c5;volatile uint32_t status;volatile uint32_t z633e4d0b43[(0xb6b+2412-0x14b7)];volatile uint32_t z1907ddba6c[(0x22cc+433-0x245d)];volatile uint32_t z185b3cf79e[(0xfec+3564-0x1db8)];volatile uint32_t z17cbe2a22e[(0xdec+6438-0x26f2)];volatile uint32_t z45128425fd[(0xf10+4647-0x2117)];volatile uint32_t zef72e5f2d0[(0x11f8+4748-0x2464)];volatile uint32_t z8a775a0c78[(0x74c+6483-0x207f)];volatile uint32_t zfac62c691a[(0x1def+133-0x1e54)];volatile uint32_t zd5c4841bfc[(0x113c+5459-0x266f)];volatile uint32_t zac3cfff3eb[(0xa73+5616-0x2043)];}ze52d134951;static void mdlInitializeSizes(SimStruct*S){uint32_t i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x1816+3368-0x253e));ssSetNumDiscStates(S,(0x315+3494-0x10bb));if(mxGetPr(z62fc1d1d8e)[(0x19ec+3236-0x2690)]){ssSetNumOutputPorts(S,mxGetN(za9d8fb6bcf));for(i=(0x1a7b+3182-0x26e9);i<mxGetN(za9d8fb6bcf);i++){ssSetOutputPortWidth(S,i,(uint32_t)mxGetPr(z3d4ad966bd)[(0x1d1a+816-0x204a)]+(0xf28+2921-0x1a90));}}else{ssSetNumOutputPorts(S,(0x182a+568-0x1a62));}if(mxGetPr(z08a9674173)[(0xb75+5817-0x222e)]){ssSetNumInputPorts(S,mxGetN(za9d8fb6bcf)+(0x10c4+4055-0x209a));}else{ssSetNumInputPorts(S,mxGetN(za9d8fb6bcf));}for(i=(0xab8+6395-0x23b3);i<mxGetN(za9d8fb6bcf);i++){ssSetInputPortWidth(S,i,(uint32_t)mxGetPr(z3d4ad966bd)[(0x546+1080-0x97e)]+(0xbe0+5520-0x216f));ssSetInputPortDirectFeedThrough(S,i,(0x1722+3393-0x2462));ssSetInputPortRequiredContiguous(S,i,(0x6a9+8154-0x2682));}if(mxGetPr(z08a9674173)[(0x1fec+1394-0x255e)]){ssSetInputPortWidth(S,mxGetN(za9d8fb6bcf),mxGetN(za9d8fb6bcf));ssSetInputPortDirectFeedThrough(S,mxGetN(za9d8fb6bcf),(0x52+2328-0x969));ssSetInputPortRequiredContiguous(S,mxGetN(za9d8fb6bcf),(0x734+2665-0x119c));}ssSetNumSampleTimes(S,(0x328+2027-0xb12));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x88c+377-0xa05));ssSetNumNonsampledZCs(S,(0x347+1498-0x921));for(i=(0xde9+2074-0x1603);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0xc47+2656-0x16a7));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0x13f4+3852-0x2300)]==-1.0){ssSetSampleTime(S,(0x1440+1685-0x1ad5),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x2090+1459-0x2643),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x41a+6311-0x1cc1),mxGetPr(z3832b85a32)[(0x178f+827-0x1aca)]);ssSetOffsetTime(S,(0x150+4897-0x1471),0.0);}}
#define MDL_START
static void mdlStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
int32_t bus,slot;uint32_t boardType;sg_fpga_io3xxModuleIdT moduleId;volatile ze52d134951*z7b342dc82d;uint32_t enable,i,channel;boardType=(uint32_t)mxGetPr(z533b11d03f)[(0x148a+3042-0x206c)];if((int32_t)sg_fpga_IO3xxGetModuleId(boardType,&moduleId)<(0x22c0+713-0x2589)){sprintf(msg,"\x53\x50\x49\x20\x62\x6c\x6f\x63\x6b\x3a\x20\x62\x6f\x61\x72\x64\x20\x74\x79\x70\x65\x20\x69\x6e\x63\x6f\x72\x72\x65\x63\x74\x2e");ssSetErrorStatus(S,msg);}if(mxGetN(ze7b39f8507)==(0x3a1+7150-0x1f8e)){bus=(0x13c8+4318-0x24a6);slot=(int_T)mxGetPr(ze7b39f8507)[(0x23+7907-0x1f06)];}else{bus=(int_T)mxGetPr(ze7b39f8507)[(0x1a8b+2397-0x23e8)];slot=(int_T)mxGetPr(ze7b39f8507)[(0x866+7675-0x2660)];}if(!io3xxGetAddressSgLib((int32_t)(int)mxGetPr(z58f464b4bb)[(0x13d0+1138-0x1842)],SG_FPGA_IO3XX_BAR2)){ssSetErrorStatus(S,pSgErrorStr);return;}z7b342dc82d=(volatile ze52d134951*)((uintptr_t)io3xxGetAddressSgLib((int32_t)(int)mxGetPr(z58f464b4bb)[(0x1150+2576-0x1b60)],SG_FPGA_IO3XX_BAR2)+zc31238bb68);ssSetPWorkValue(S,z93d7dbe681,(void*)z7b342dc82d);if(!sg_isModelInit()){enable=(0xa43+4412-0x1b7f);for(i=(0x5cc+4103-0x15d3);i<mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0x1cbd+2122-0x2506);enable|=((0x1ad5+2926-0x2642)<<channel);}z7b342dc82d->enable=enable;}
#endif
}static void mdlOutputs(SimStruct*S,int_T z27c0327a06){
#ifndef MATLAB_MEX_FILE
volatile ze52d134951*z7b342dc82d;uint32_t z26dbd73a5e,i,width,count,z03312e422a;double*in,*out,*z46c2b7bc26;uint32_t channel,status;z7b342dc82d=(volatile ze52d134951*)ssGetPWorkValue(S,z93d7dbe681);width=(uint32_t)mxGetPr(z3d4ad966bd)[(0x5c6+2553-0xfbf)]+(0x5a3+1396-0xb16);z03312e422a=(0x108+4396-0x1234);for(i=(0x1916+2986-0x24c0);i<mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0x959+4235-0x19e3);in=(double*)ssGetInputPortSignal(S,i);count=z7b342dc82d->z45128425fd[channel];if(count>(0xeb1+1590-0x14e7)){sprintf(msg,"\x54\x72\x69\x65\x64\x20\x74\x6f\x20\x77\x72\x69\x74\x65\x20\x69\x6e\x20\x61\x20\x6e\x6f\x6e\x2d\x65\x6d\x70\x74\x79\x20\x62\x75\x66\x66\x65\x72");ssSetErrorStatus(S,msg);return;}if(mxGetPr(z08a9674173)[(0x12f9+3271-0x1fc0)]){z46c2b7bc26=(double*)ssGetInputPortSignal(S,mxGetN(za9d8fb6bcf));z7b342dc82d->zef72e5f2d0[channel]=(uint32_t)z46c2b7bc26[i];}count=(uint32_t)in[(0xe0c+642-0x108e)];for(z26dbd73a5e=(0xac4+2360-0x13fc);z26dbd73a5e<count;z26dbd73a5e++){z7b342dc82d->z633e4d0b43[channel]=(uint32_t)in[z26dbd73a5e+(0xac7+6886-0x25ac)];z7b342dc82d->z17cbe2a22e[channel]=z26dbd73a5e;z7b342dc82d->z21ab44ce3e=((0x6f8+740-0x9db)<<channel);z7b342dc82d->z21ab44ce3e=(0xd3+1546-0x6dd);}z7b342dc82d->z45128425fd[channel]=count;z7b342dc82d->z03312e422a=((0xfb2+2610-0x19e3)<<channel);z7b342dc82d->z03312e422a=(0x1936+2252-0x2202);}if(mxGetPr(z62fc1d1d8e)[(0x92a+6783-0x23a9)]){for(i=(0xa71+498-0xc63);i<mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0x2a6+77-0x2f2);out=ssGetOutputPortSignal(S,channel);in=(double*)ssGetInputPortSignal(S,channel);if(in[(0xfa0+2399-0x18ff)]>(0x2347+737-0x2628)){do{status=z7b342dc82d->status;}while((status&((0x74+636-0x2ef)<<channel))==(0x7ba+2385-0x110b));}for(z26dbd73a5e=(0x1b74+1101-0x1fc1);z26dbd73a5e<(uint8_t)mxGetPr(z3d4ad966bd)[(0xc06+2651-0x1661)];z26dbd73a5e++){out[z26dbd73a5e]=(0x109+4503-0x12a0);}for(z26dbd73a5e=(0xd53+2566-0x1759);z26dbd73a5e<in[(0xd67+3763-0x1c1a)];z26dbd73a5e++){z7b342dc82d->z17cbe2a22e[channel]=z26dbd73a5e;out[z26dbd73a5e+(0x22b0+529-0x24c0)]=(double)z7b342dc82d->z1907ddba6c[channel];}out[(0xfcc+4157-0x2009)]=in[(0x7bd+7398-0x24a3)];z7b342dc82d->z05095ec8c5=((0x916+6435-0x2238)<<channel);z7b342dc82d->z05095ec8c5=(0x1380+3233-0x2021);}}
#endif
}static void mdlTerminate(SimStruct*S){
#ifndef MATLAB_MEX_FILE
volatile ze52d134951*z7b342dc82d;uint16_t i;uint32_t channel,z1209c02d78,zdc0d676974,zbea4a89f24,z9e58a4ec45;z7b342dc82d=(volatile ze52d134951*)ssGetPWorkValue(S,z93d7dbe681);z1209c02d78=(uint32_t)z7b342dc82d->enable;zdc0d676974=(uint32_t)z7b342dc82d->z13e3aff50f;zbea4a89f24=(uint32_t)z7b342dc82d->z79c39f7a01;z9e58a4ec45=(uint32_t)z7b342dc82d->MSBFirst;for(i=(0x11b9+4934-0x24ff);i<mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0x547+5468-0x1aa2);z7b342dc82d->z185b3cf79e[channel]=(uint32_t)mxGetPr(z7039def18e)[i];z7b342dc82d->zef72e5f2d0[channel]=(uint32_t)mxGetPr(zf6f668e67a)[i];z7b342dc82d->z8a775a0c78[channel]=(uint32_t)mxGetPr(zbb0d1897b2)[i];z7b342dc82d->zfac62c691a[channel]=(uint32_t)mxGetPr(z8f7a5b7479)[i];z7b342dc82d->zd5c4841bfc[channel]=(uint32_t)mxGetPr(zdc5f8981b7)[i];z7b342dc82d->zac3cfff3eb[channel]=(uint32_t)mxGetPr(zc09b06e5fc)[i];z1209c02d78|=((0x1da+4612-0x13dd)<<channel);zdc0d676974|=(((uint32_t)mxGetPr(z86af52d74e)[i])<<channel);zbea4a89f24|=(((uint32_t)mxGetPr(z31fb671cb8)[i])<<channel);z9e58a4ec45|=(((uint32_t)mxGetPr(zea4d7ef473)[i])<<channel);}z7b342dc82d->z13e3aff50f=zdc0d676974;z7b342dc82d->MSBFirst=z9e58a4ec45;z7b342dc82d->z79c39f7a01=zbea4a89f24;z7b342dc82d->enable=(0x1526+2819-0x2029);
#endif
}
#include "sg_sfcn_glue.h"   


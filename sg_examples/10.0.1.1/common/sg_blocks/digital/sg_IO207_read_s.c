// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL    (0x1a7b+1254-0x1f5f)
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME     sg_IO207_read_s
#include "sg_io207.h"
#include "simstruc.h"
#ifndef MATLAB_MEX_FILE
#include "sg_printf.h"
#include "sg_common.h"
#include "sg_module_registry.h"
#include "sg_module_types.h"
static const int z0e14cce82f=zd59e28c17b;
#else
#include "mex.h"
#endif
#define SG_EARLY_INIT   
#include "sg_callback.h"
static char msg[(0xd25+5262-0x20b3)];
#define zdf24515981          ((0x4ac+4202-0x150a))
#define zabe1e0cd2c          ssGetSFcnParam(S,(0x11e8+1894-0x194e))
#define z58f464b4bb                  ssGetSFcnParam(S,(0x466+196-0x529))
#define zb3316c569f       ssGetSFcnParam(S,(0x215b+67-0x219c))
#define z671bf8a532           ssGetSFcnParam(S,(0x1c9f+2531-0x267f))
#define z856e0a9c33           ssGetSFcnParam(S,(0x2a1+4618-0x14a7))
#define z8c90cbca92            ssGetSFcnParam(S,(0xc48+1547-0x124e))
#define zb2cdde0c32             ssGetSFcnParam(S,(0x1093+3120-0x1cbd))
#define z7cfb0149c9            ssGetSFcnParam(S,(0x1010+1726-0x16c7))
#define zd1cdc9602c        ssGetSFcnParam(S,(0x3b5+144-0x43d))
#define z702a26a5e9                ssGetSFcnParam(S,(0x1243+2895-0x1d89))
#define zffdb79f3bd           ssGetSFcnParam(S,(0x525+7070-0x20b9))
#define zea4ff5f58f          ssGetSFcnParam(S,(0x9ec+4892-0x1cfd))
#define z2e6483d505              ((0x10b+8896-0x23cb))
#define zc5ce4cb81a              ((0x18f3+1599-0x1f32))
#define z2b17e2ee3b              ((0x13cf+37-0x13f4))
#define z53e64be319                ((0xbd6+4698-0x1e30))
#define zdf898925a0               ((0xaba+6611-0x248d))
static void mdlInitializeSizes(SimStruct*S){int32_T i;int32_T zb4e63f2976=(0x14bc+842-0x1806);ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x10f0+2051-0x18f3));ssSetNumDiscStates(S,(0x1bb6+1923-0x2339));ssSetNumSampleTimes(S,(0x1978+344-0x1acf));ssSetNumModes(S,(0x1e7+1310-0x705));ssSetNumNonsampledZCs(S,(0xa6f+1851-0x11aa));for(i=(0xa0a+590-0xc58);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x1902+3537-0x26d3));}switch((uint32_T)mxGetPr(zb3316c569f)[(0x5b1+3482-0x134b)]){case FRONT:if(((uint32_T)mxGetPr(z7cfb0149c9)[(0xf2d+4467-0x20a0)]==zb8557d490d)){zb4e63f2976=(0xcb+4244-0x113f);}else{zb4e63f2976=(0x851+694-0xac7);}break;case z722b515dc6:if(((uint32_T)mxGetPr(zb2cdde0c32)[(0xd71+3258-0x1a2b)]==z25297a45fe)){zb4e63f2976=(0x61+6075-0x17fc);}else{zb4e63f2976=(0x230a+100-0x232e);}break;}switch((uint32_T)mxGetPr(z671bf8a532)[(0x206a+1088-0x24aa)]){case z5778f7a1a3:if(!ssSetNumOutputPorts(S,zb4e63f2976))return;for(i=(0x378+4242-0x140a);i<zb4e63f2976;i++){ssSetOutputPortWidth(S,i,(0x470+1726-0xb2d));}break;case z97d9bed5dc:if(!ssSetNumOutputPorts(S,zb4e63f2976))return;for(i=(0x113c+4214-0x21b2);i<zb4e63f2976;i++){ssSetOutputPortWidth(S,i,(0xbcb+4053-0x1b9f));ssSetOutputPortDataType(S,i,SS_BOOLEAN);}break;case z509f1627a2:if(!ssSetNumOutputPorts(S,(0x22c+8081-0x21bc)))return;ssSetOutputPortWidth(S,(0xd7f+1763-0x1462),zb4e63f2976);break;case z9e732d4c07:if(!ssSetNumOutputPorts(S,(0x378+8278-0x23cd)))return;ssSetOutputPortWidth(S,(0x137d+3851-0x2288),zb4e63f2976);ssSetOutputPortDataType(S,(0x510+4150-0x1546),SS_BOOLEAN);break;}ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if((uint32_T)mxGetPr(zabe1e0cd2c)[(0xfd+5461-0x1652)]==-1.0){ssSetSampleTime(S,(0xf69+5893-0x266e),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x527+3684-0x138b),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x8ed+6457-0x2226),mxGetPr(zabe1e0cd2c)[(0x9db+6629-0x23c0)]);ssSetOffsetTime(S,(0x3bf+7552-0x213f),0.0);}}
#ifndef MATLAB_MEX_FILE
static void sg_ModelLoad(SimStruct*S){}static void sg_ModelStart(SimStruct*S){}static void sg_ModelStep(SimStruct*S){ze7230a05ed*zae10e3f17f=NULL;int za0d38ae598;uint32_T i;uint32_T z5f08228267=(0x3eb+2286-0xcd9);uint32_T z71b4fadaa0=(0x398+3116-0xfc4);real_T*y1;boolean_T*y2;za0d38ae598=(int)mxGetPr(z58f464b4bb)[(0x901+2821-0x1406)];zae10e3f17f=(ze7230a05ed*)sg_module_get_custom_data(z0e14cce82f,za0d38ae598);if(!zae10e3f17f){sprintf(msg,"\x25\x73\x20\x28\x49\x44\x20\x25\x64\x29\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x72\x65\x74\x72\x69\x65\x76\x65\x20\x6d\x6f\x64\x75\x6c\x65\x20\x66\x72\x6f\x6d\x20\x72\x65\x67\x69\x73\x74\x72\x79\x20\x69\x6e\x20\x52\x65\x61\x64\x20\x4d\x6f\x64\x65\x6c\x53\x74\x65\x70" "\n",DEVNAME,za0d38ae598);ssSetErrorStatus(S,msg);return;}if(((uint32_T)mxGetPr(zea4ff5f58f)[(0x858+5263-0x1ce7)]==ON)&&((uint32_T)mxGetPr(z7cfb0149c9)[(0x210a+594-0x235c)]==zd5722e7b54)){zae10e3f17f->z3e5b8e05d8->z96d6777a46=z2499c861b0;}if(((uint32_T)mxGetPr(zffdb79f3bd)[(0x1ad3+3024-0x26a3)]==ON)&&((uint32_T)mxGetPr(zb2cdde0c32)[(0x62+756-0x356)]==zbd6eb35fcd)){zae10e3f17f->z3e5b8e05d8->z96d6777a46=zc6ba819607;}if((uint32_T)mxGetPr(zb3316c569f)[(0x1492+2128-0x1ce2)]==FRONT){z5f08228267=zae10e3f17f->z3e5b8e05d8->z84bb67aac4.z7f3e6de1c9;if((uint32_T)mxGetPr(z7cfb0149c9)[(0x29b+4417-0x13dc)]==zd5722e7b54){z71b4fadaa0=zae10e3f17f->z3e5b8e05d8->z84bb67aac4.zc8d0c471e2;}}if((uint32_T)mxGetPr(zb3316c569f)[(0x18a5+1176-0x1d3d)]==z722b515dc6){z5f08228267=zae10e3f17f->z3e5b8e05d8->z84bb67aac4.zf555a21781;if((uint32_T)mxGetPr(zb2cdde0c32)[(0x489+96-0x4e9)]==zbd6eb35fcd){z71b4fadaa0=zae10e3f17f->z3e5b8e05d8->z84bb67aac4.ze863a41864;}}switch((uint32_T)mxGetPr(z671bf8a532)[(0xd08+4255-0x1da7)]){case z5778f7a1a3:for(i=(0x1e09+236-0x1ef5);i<(0x11e8+3692-0x2034);i++){y1=(real_T*)ssGetOutputPortSignal(S,i);y1[(0x1186+2185-0x1a0f)]=(real_T)((z5f08228267>>i)&(0x88f+4672-0x1ace));if((((uint32_T)mxGetPr(z7cfb0149c9)[(0x471+7553-0x21f2)]==zd5722e7b54)&&((uint32_T)mxGetPr(zb3316c569f)[(0x25a+4597-0x144f)]==FRONT))||(((uint32_T)mxGetPr(zb2cdde0c32)[(0x6b2+2546-0x10a4)]==zbd6eb35fcd)&&((uint32_T)mxGetPr(zb3316c569f)[(0x1800+213-0x18d5)]==z722b515dc6))){y1=(real_T*)ssGetOutputPortSignal(S,(i+(0x967+2276-0x122b)));y1[(0x263d+127-0x26bc)]=(real_T)((z71b4fadaa0>>i)&(0xa5a+4318-0x1b37));}}break;case z97d9bed5dc:for(i=(0x138c+167-0x1433);i<(0x36c+1229-0x819);i++){y2=(boolean_T*)ssGetOutputPortSignal(S,i);y2[(0x63d+300-0x769)]=(boolean_T)((z5f08228267>>i)&(0xfb9+3291-0x1c93));if((((uint32_T)mxGetPr(z7cfb0149c9)[(0x1340+5-0x1345)]==zd5722e7b54)&&((uint32_T)mxGetPr(zb3316c569f)[(0x390+4972-0x16fc)]==FRONT))||(((uint32_T)mxGetPr(zb2cdde0c32)[(0x390+1658-0xa0a)]==zbd6eb35fcd)&&((uint32_T)mxGetPr(zb3316c569f)[(0x12c+5434-0x1666)]==z722b515dc6))){y2=(boolean_T*)ssGetOutputPortSignal(S,(i+(0x8c6+5227-0x1d11)));y2[(0x1229+1404-0x17a5)]=(boolean_T)((z71b4fadaa0>>i)&(0x1a15+1380-0x1f78));}}break;case z509f1627a2:y1=(real_T*)ssGetOutputPortSignal(S,(0x22e3+493-0x24d0));for(i=(0x920+944-0xcd0);i<(0x3a8+8634-0x2542);i++){y1[i]=(real_T)((z5f08228267>>i)&(0x42a+2197-0xcbe));if((((uint32_T)mxGetPr(z7cfb0149c9)[(0xd3a+3779-0x1bfd)]==zd5722e7b54)&&((uint32_T)mxGetPr(zb3316c569f)[(0xfa7+5392-0x24b7)]==FRONT))||(((uint32_T)mxGetPr(zb2cdde0c32)[(0x277+7359-0x1f36)]==zbd6eb35fcd)&&((uint32_T)mxGetPr(zb3316c569f)[(0x5b1+2299-0xeac)]==z722b515dc6))){y1[i+(0xa55+1942-0x11cb)]=(real_T)((z71b4fadaa0>>(i))&(0x12f1+2040-0x1ae8));}}break;case z9e732d4c07:y2=(boolean_T*)ssGetOutputPortSignal(S,(0x1bb6+1118-0x2014));for(i=(0x118d+1653-0x1802);i<(0x107+4157-0x1124);i++){y2[i]=(boolean_T)((z5f08228267>>i)&(0x1064+3460-0x1de7));if((((uint32_T)mxGetPr(z7cfb0149c9)[(0x1b40+35-0x1b63)]==zd5722e7b54)&&((uint32_T)mxGetPr(zb3316c569f)[(0x1bfb+2356-0x252f)]==FRONT))||(((uint32_T)mxGetPr(zb2cdde0c32)[(0xd9a+3211-0x1a25)]==zbd6eb35fcd)&&((uint32_T)mxGetPr(zb3316c569f)[(0xf5a+4141-0x1f87)]==z722b515dc6))){y2[i+(0xc5a+2910-0x1798)]=(boolean_T)((z71b4fadaa0>>(i))&(0x16c7+3820-0x25b2));}}break;}}static void sg_ModelStop(SimStruct*S){}
#endif  
#include "sg_sfcn_glue.h"   


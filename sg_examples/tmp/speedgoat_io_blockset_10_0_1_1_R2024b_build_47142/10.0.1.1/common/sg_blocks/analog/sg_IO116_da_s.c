// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL    (0x128+4399-0x1255)
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME     sg_IO116_da_s
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include "sg_io116.h"
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
#define za9d8fb6bcf             ssGetSFcnParam(S, (0x1605+2260-0x1ed9))
#define z39cbd24432         ssGetSFcnParam(S, (0x61+9746-0x2672))
#define z702a26a5e9                ssGetSFcnParam(S, (0x74f+1966-0xefb))
#define zda964b0978                ssGetSFcnParam(S, (0x52a+5548-0x1ad3))
#define z8e2c007185      ssGetSFcnParam(S, (0xfe5+235-0x10cc))
#define z323aba6146    ssGetSFcnParam(S, (0x1918+150-0x19a9))
#define zfa5e89fbb8           ssGetSFcnParam(S, (0x1ddc+1683-0x2469))
#define ze13f49a01f           ssGetSFcnParam(S, (0x918+1733-0xfd6))
#define zdf24515981          ((0xd09+6493-0x265e))
#define z2e6483d505              ((0x7fd+5842-0x1ecf))
#define zc5ce4cb81a              ((0x13dd+624-0x164d))
#define z2b17e2ee3b              ((0x1685+1954-0x1e27))
static char msg[(0x1b35+1714-0x20e7)];static void mdlInitializeSizes(SimStruct*S){uint32_T i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x6c0+4889-0x19d9));ssSetNumDiscStates(S,(0x13f4+571-0x162f));ssSetNumSampleTimes(S,(0x5+331-0x14f));ssSetNumModes(S,(0x3a5+8340-0x2439));ssSetNumNonsampledZCs(S,(0x7c1+6640-0x21b1));for(i=(0x25a+7842-0x20fc);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,SS_PRM_NOT_TUNABLE);}if(!ssSetNumInputPorts(S,(int)mxGetN(za9d8fb6bcf)))return;for(i=(0xfb8+5198-0x2406);i<(int)mxGetN(za9d8fb6bcf);i++){ssSetInputPortWidth(S,i,(0xd97+4203-0x1e01));ssSetInputPortDirectFeedThrough(S,i,(0x4ca+773-0x7ce));ssSetInputPortRequiredContiguous(S,i,(0x88+1821-0x7a4));}if((uint32_T)mxGetPr(z323aba6146)[(0x133a+905-0x16c3)]==(0x6bc+5535-0x1c5a)&&(uint32_T)mxGetPr(z8e2c007185)[(0x22e1+797-0x25fe)]==(0x209+715-0x4d3)){if(!ssSetNumOutputPorts(S,(0x1c32+601-0x1e87)))return;for(i=(0x23f3+373-0x2568);i<(0xe4c+884-0x11bc);i++){ssSetOutputPortWidth(S,i,(0x411+6497-0x1d71));}}else{if(!ssSetNumOutputPorts(S,(0x5eb+906-0x975)))return;}ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z39cbd24432)[(0x84c+5380-0x1d50)]==-1.0){ssSetSampleTime(S,(0x8d3+261-0x9d8),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x26+3429-0xd8b),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x1157+5044-0x250b),mxGetPr(z39cbd24432)[(0xe3a+591-0x1089)]);ssSetOffsetTime(S,(0x1109+3022-0x1cd7),0.0);}}
#ifndef MATLAB_MEX_FILE
static void sg_ModelLoad(SimStruct*S){}static void sg_ModelStart(SimStruct*S){}static void sg_ModelStep(SimStruct*S){uint32_T za0d38ae598=((uint32_T)mxGetPr(ze13f49a01f)[(0x1b44+803-0x1e67)]);uint32_T i;uint32_T zcb322daed6;uint32_T zf91d71c6d9=(uint32_T)mxGetN(za9d8fb6bcf);uint32_T alarm;real_T z0754dd67cc=(real_T)mxGetPr(zda964b0978)[(0x18a6+1880-0x1ffe)];real_T*z6811465ec0;real_T*zc7fc760ccc;int32_T z2ee0b44103=(0xe74+5007-0x2203);z08779af635*zae10e3f17f=(z08779af635*)sg_module_get_custom_data(z12ba1d7c25,za0d38ae598);if(!zae10e3f17f){sprintf(msg,"\x49\x4f\x25\x64\x20\x28\x49\x44\x20\x25\x64\x29\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x72\x65\x74\x72\x69\x65\x76\x65\x20\x6d\x6f\x64\x75\x6c\x65\x20\x66\x72\x6f\x6d\x20\x72\x65\x67\x69\x73\x74\x72\x79\x20\x69\x6e\x20\x44\x41\x20\x4d\x6f\x64\x65\x6c\x53\x74\x65\x70" "\n",z12ba1d7c25,za0d38ae598);ssSetErrorStatus(S,msg);return;}for(i=(0x924+7167-0x2523);i<zf91d71c6d9;i++){zcb322daed6=(uint16_T)mxGetPr(za9d8fb6bcf)[i]-(0x8bd+6441-0x21e5);z6811465ec0=(real_T*)ssGetInputPortRealSignal(S,i);if((uint32_T)mxGetPr(zfa5e89fbb8)[(0x70a+1828-0xe2e)]==(0xad8+3257-0x178f)&&(uint32_T)mxGetPr(z8e2c007185)[(0x5e3+1264-0xad3)]==(0x37a+3715-0x11fc)){z2ee0b44103=(int32_T)((*z6811465ec0-0.004)*z0754dd67cc);}else{z2ee0b44103=(int32_T)((*z6811465ec0)*z0754dd67cc);}if(z2ee0b44103>65535){z2ee0b44103=65535;}if(z2ee0b44103<(0x1cd2+1992-0x249a)){z2ee0b44103=(0xb8c+4735-0x1e0b);}if(i>=(zf91d71c6d9-(0x17a+8826-0x23f3))){zae10e3f17f->z3fad3d9764->z1c94a69882=z2ee0b44103|(zcb322daed6<<(0x323+6931-0x1e26))|((0xb91+6942-0x26ae)<<(0x9e5+3560-0x17bb))|((0xf88+157-0x1024)<<(0xa12+7378-0x26d1));zae10e3f17f->z3fad3d9764->z14bc320aa4|=((0x362+1637-0x9c6)<<(0x1093+1186-0x152a));}else{zae10e3f17f->z3fad3d9764->z1c94a69882=z2ee0b44103|(zcb322daed6<<(0x19a7+1912-0x210f));}}if((uint32_T)mxGetPr(z323aba6146)[(0x1113+4333-0x2200)]==(0x16a5+703-0x1963)&&(uint32_T)mxGetPr(z8e2c007185)[(0xf1b+3858-0x1e2d)]==(0xb64+3478-0x18f9)){alarm=zae10e3f17f->z3fad3d9764->z720c2d0954;for(i=(0x2025+867-0x2388);i<(0x3fb+8621-0x25a4);i++){zc7fc760ccc=ssGetOutputPortSignal(S,i);*zc7fc760ccc=(real_T)((alarm&((0x22f3+398-0x2480)<<((0xc5a+2844-0x1765)+i)))>>((0x9d3+5594-0x1f9c)+i));}}}static void sg_ModelStop(SimStruct*S){}
#endif 
#include "sg_sfcn_glue.h"   


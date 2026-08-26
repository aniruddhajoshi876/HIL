// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL    (0x574+3676-0x13ce)
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME     sg_IO113_20_do_s
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include "sg_io113_20.h"
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
#define ze13f49a01f           ssGetSFcnParam(S, (0x2d7+1266-0x7c9))
#define z3832b85a32           ssGetSFcnParam(S, (0x206+1187-0x6a8))
#define z702a26a5e9                ssGetSFcnParam(S, (0x22ef+458-0x24b7))
#define z5bc3ce0d50           ssGetSFcnParam(S, (0xe9c+6110-0x2677))
#define z2d8f240c11           ssGetSFcnParam(S, (0x1196+4420-0x22d6))
#define z1f9bebb47b             ssGetSFcnParam(S, (0x7fc+1697-0xe98))
#define zdf24515981                           ((0xd7c+4342-0x1e6c))
#define z2e6483d505              ((0xca6+1895-0x140d))
#define zc5ce4cb81a              ((0x1d60+537-0x1f79))
#define z2b17e2ee3b              ((0x7c+4923-0x13b7))
#define THRESHOLD               0.5
static char_T msg[(0x390+215-0x367)];static void mdlInitializeSizes(SimStruct*S){uint32_T i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0xb12+1548-0x111e));ssSetNumDiscStates(S,(0x564+7993-0x249d));if(!ssSetNumOutputPorts(S,(0xec7+500-0x10bb)))return;if(!ssSetNumInputPorts(S,(int)mxGetN(z5bc3ce0d50)))return;for(i=(0x11b0+1779-0x18a3);i<(int)mxGetN(z5bc3ce0d50);i++){ssSetInputPortWidth(S,i,(0x1504+1000-0x18eb));ssSetInputPortDirectFeedThrough(S,i,(0x1d1f+1043-0x2131));ssSetInputPortRequiredContiguous(S,i,(0xe42+4096-0x1e41));}ssSetNumSampleTimes(S,(0xc8+4250-0x1161));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x1f2+7696-0x2002));ssSetNumNonsampledZCs(S,(0xb38+3983-0x1ac7));for(i=(0x34f+8555-0x24ba);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x222+8412-0x22fe));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0x2dc+6153-0x1ae5)]==-1.0){ssSetSampleTime(S,(0x189b+661-0x1b30),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x7c6+122-0x840),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x166c+1077-0x1aa1),mxGetPr(z3832b85a32)[(0x220a+728-0x24e2)]);ssSetOffsetTime(S,(0x1d07+747-0x1ff2),0.0);}}
#ifndef MATLAB_MEX_FILE
static void z95e7ebbeb7(SimStruct*S,zd63abbc96e*zae10e3f17f,int z4f19fbae54){uint16_T z344fcf0ef3=(uint16_T)mxGetN(z5bc3ce0d50);uint16_T i;uint32_T channel;uint32_T z718c4c15f4;z718c4c15f4=z4f19fbae54?(zae10e3f17f->z3fad3d9764[z9621b996a9]&32896):zae10e3f17f->z3fad3d9764[z9621b996a9];for(i=(0xbc2+802-0xee4);i<z344fcf0ef3;i++){if(!z4f19fbae54&&!(int)mxGetPr(z1f9bebb47b)[i])continue;channel=(uint32_T)mxGetPr(z5bc3ce0d50)[i]-(0x3aa+7096-0x1f61);if(mxGetPr(z2d8f240c11)[i]>=THRESHOLD){if((channel<=(0x5a5+3478-0x1338))&&(zae10e3f17f->z3fad3d9764[z9621b996a9]&(1u<<(0x81a+1718-0xec9))))z718c4c15f4|=(1u<<channel);else if(zae10e3f17f->z3fad3d9764[z9621b996a9]&(1u<<(0x1a41+1226-0x1efc)))z718c4c15f4|=(1u<<(channel+(0x11ab+161-0x1248)));}else{if(channel<=(0x15bb+981-0x198d))z718c4c15f4&=~(1u<<channel);else z718c4c15f4&=~(1u<<(channel+(0x15f6+1946-0x1d8c)));}}zae10e3f17f->z3fad3d9764[z9621b996a9]=z718c4c15f4;SG_PRINTF(DEBUG,"\x52\x45\x47\x5f\x44\x50\x52\x20\x28\x64\x6f\x20\x25\x73\x29\x3a\x20\x30\x78\x25\x78" "\n",z4f19fbae54?"\x69\x6e\x69\x74":"\x72\x65\x73\x65\x74",zae10e3f17f->z3fad3d9764[z9621b996a9]);}static void sg_ModelLoad(SimStruct*S){uint32_T za0d38ae598=(uint32_T)mxGetPr(ze13f49a01f)[(0x1f40+1362-0x2492)];zd63abbc96e*zae10e3f17f=(zd63abbc96e*)sg_module_get_custom_data(z12ba1d7c25,za0d38ae598);if(!zae10e3f17f){sprintf(msg,"\x25\x73\x20\x28\x49\x44\x20\x25\x75\x29\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x72\x65\x74\x72\x69\x65\x76\x65\x20\x6d\x6f\x64\x75\x6c\x65\x20\x69\x6e\x20\x44\x4f\x20\x4d\x6f\x64\x65\x6c\x4c\x6f\x61\x64" "\n",DEVNAME,za0d38ae598);ssSetErrorStatus(S,msg);return;}z95e7ebbeb7(S,zae10e3f17f,(0x1e1c+1821-0x2538));}static void sg_ModelStart(SimStruct*S){}static void sg_ModelStep(SimStruct*S){uint16_T z344fcf0ef3=(uint16_T)mxGetN(z5bc3ce0d50);uint32_T za0d38ae598=(uint32_T)mxGetPr(ze13f49a01f)[(0x9e0+3437-0x174d)];uint16_T i;uint32_T z718c4c15f4,channel;real_T*zc7fdaf6331;zd63abbc96e*zae10e3f17f=(zd63abbc96e*)sg_module_get_custom_data(z12ba1d7c25,za0d38ae598);if(!zae10e3f17f){sprintf(msg,"\x25\x73\x20\x28\x49\x44\x20\x25\x75\x29\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x72\x65\x74\x72\x69\x65\x76\x65\x20\x6d\x6f\x64\x75\x6c\x65\x20\x69\x6e\x20\x44\x4f\x20\x4d\x6f\x64\x65\x6c\x53\x74\x65\x70" "\n",DEVNAME,za0d38ae598);ssSetErrorStatus(S,msg);return;}z718c4c15f4=zae10e3f17f->z3fad3d9764[z9621b996a9]&32896;for(i=(0x24f+6044-0x19eb);i<z344fcf0ef3;i++){channel=(uint32_T)mxGetPr(z5bc3ce0d50)[i]-(0x1bc8+781-0x1ed4);zc7fdaf6331=(real_T*)ssGetInputPortRealSignal(S,i);if(zc7fdaf6331[(0x7a+5649-0x168b)]>=THRESHOLD){if((channel<=(0x697+364-0x800))&&(zae10e3f17f->z3fad3d9764[z9621b996a9]&(1u<<(0x370+9087-0x26e8)))){z718c4c15f4|=(0x192+2519-0xae9);z718c4c15f4|=(1u<<channel);}else if(zae10e3f17f->z3fad3d9764[z9621b996a9]&(1u<<(0x1a3f+1860-0x2174))){z718c4c15f4|=32768;z718c4c15f4|=1u<<(channel+(0x813+4874-0x1b19));}}}zae10e3f17f->z3fad3d9764[z9621b996a9]=z718c4c15f4;SG_PRINTF(TRACE,"\x52\x45\x47\x5f\x44\x50\x52\x20\x28\x64\x6f\x29\x3a\x20\x30\x78\x25\x78" "\n",zae10e3f17f->z3fad3d9764[z9621b996a9]);}static void sg_ModelStop(SimStruct*S){uint32_T za0d38ae598=(uint32_T)mxGetPr(ze13f49a01f)[(0x597+5782-0x1c2d)];zd63abbc96e*zae10e3f17f=(zd63abbc96e*)sg_module_get_custom_data(z12ba1d7c25,za0d38ae598);if(!zae10e3f17f){sprintf(msg,"\x25\x73\x20\x28\x49\x44\x20\x25\x75\x29\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x72\x65\x74\x72\x69\x65\x76\x65\x20\x6d\x6f\x64\x75\x6c\x65\x20\x69\x6e\x20\x44\x4f\x20\x4d\x6f\x64\x65\x6c\x53\x74\x6f\x70" "\n",DEVNAME,za0d38ae598);ssSetErrorStatus(S,msg);return;}z95e7ebbeb7(S,zae10e3f17f,(0x10f8+5433-0x2631));}
#endif 
#include "sg_sfcn_glue.h"   


// Copyright 2006-2026 Speedgoat GmbH

#define 	S_FUNCTION_LEVEL 	(0x633+7645-0x240e)
#undef 		S_FUNCTION_NAME
#define 	S_FUNCTION_NAME 	sg_fpga_inta_sf_a1
#include    <stddef.h>
#include    <stdlib.h>
#include    <stdint.h>
#include    <stdbool.h>
#include    "simstruc.h"
#include    "sg_callback.h"
#ifdef MATLAB_MEX_FILE
#include    "mex.h"
#endif
#ifndef MATLAB_MEX_FILE
#include    "sg_common.h"
#include    "sg_fpga_io3xx_util.h"
#include    "sg_printf.h"
#endif
#define ze13f49a01f           ssGetSFcnParam(S,(0x125+6590-0x1ae3))
#define z1120e7330e            ssGetSFcnParam(S,(0xb63+6053-0x2307))
#define z644559a0a7               ssGetSFcnParam(S,(0x89b+1810-0xfab))
#define ze9153280f8            ssGetSFcnParam(S,(0x1191+627-0x1401))
#define z3832b85a32           ssGetSFcnParam(S,(0x773+745-0xa58))
#define zdf24515981                          ((0x1115+1906-0x1882))
#define z2e6483d505              ((0x16d+7931-0x2067))
#define z7e2eeaa57c          ((0x628+6435-0x1f4b))
#define zc5ce4cb81a              ((0x7ab+3269-0x1460))
#define z2b17e2ee3b              ((0x109d+1830-0x17c2))
#define z0194338df7         ((0xae8+7043-0x266b))
#define z5bbcf8be2c            (0x148a+4445-0x25e6)
#define z5c3f5520e2           (0.000001)
static char msg[(0x20cf+1406-0x254d)];typedef struct{uint32_t zab46142f2e;uint32_t clear;uint32_t event;uint32_t version;uint32_t test1;}z79f5963ede;static void mdlInitializeSizes(SimStruct*S){uint32_t i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x1359+4946-0x26ab));ssSetNumDiscStates(S,(0x2cd+9193-0x26b6));if(!ssSetNumOutputPorts(S,(0x2f4+3336-0xffc))){return;}if(!ssSetNumInputPorts(S,(0x2a3+1978-0xa5d))){return;}ssSetNumSampleTimes(S,(0x10ea+3968-0x2069));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x2d0+563-0x503));ssSetNumNonsampledZCs(S,(0x175+7712-0x1f95));for(i=(0x1484+2795-0x1f6f);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0xc81+5153-0x20a2));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0x12f+1356-0x67b)]==-1.0){ssSetSampleTime(S,(0x16e8+1087-0x1b27),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x1b1f+1309-0x203c),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x91c+2114-0x115e),mxGetPr(z3832b85a32)[(0x672+2093-0xe9f)]);ssSetOffsetTime(S,(0xac7+2879-0x1606),0.0);}}static void sg_ModelLoad(SimStruct*S){
#ifndef MATLAB_MEX_FILE
volatile z79f5963ede*zf97bbfdf00;void*bar2ptr;int moduleId=(int)mxGetScalar(ze13f49a01f);char*boardName=io3xxGetBoardNameSgLib(moduleId);if(!io3xxGetAddressSgLib((int32_t)(int)mxGetPr(ze13f49a01f)[(0x6b+2518-0xa41)],SG_FPGA_IO3XX_BAR2)){ssSetErrorStatus(S,pSgErrorStr);return;}bar2ptr=io3xxGetAddressSgLib((int32_t)(int)mxGetPr(ze13f49a01f)[(0xe70+2066-0x1682)],SG_FPGA_IO3XX_BAR2);SG_PRINTF(INFO,"\x25\x73\x20\x42\x41\x52\x32\x20\x61\x64\x64\x72\x65\x73\x73\x3a\x20\x30\x78\x25\x78" "\n",boardName,bar2ptr);uint32_t zf7ccd17be8=(0x19ea+1177-0x1e83);if(sg_fpga_io3xx_getCmBaseAddress(moduleId,INTA_BASE,&zf7ccd17be8)){sprintf(msg,"\x25\x73\x20\x49\x4e\x54\x41\x20\x6d\x6f\x64\x75\x6c\x65\x3a\x20\x4f\x66\x66\x73\x65\x74\x20\x6c\x6f\x6f\x6b\x75\x70\x20\x75\x6e\x73\x75\x63\x63\x65\x73\x73\x66\x75\x6c\x21" "\n",boardName);return;}SG_PRINTF(INFO,"\x25\x73\x20\x49\x4e\x54\x41\x20\x6d\x6f\x64\x75\x6c\x65\x3a\x20\x4f\x66\x66\x73\x65\x74\x20\x30\x78\x25\x78" "\n",boardName,zf7ccd17be8);zf97bbfdf00=(z79f5963ede*)((uintptr_t)bar2ptr+zf7ccd17be8);ssSetPWorkValue(S,z0194338df7,(void*)zf97bbfdf00);if(sg_fpga_io3xx_checkCodeModuleVersion(zf97bbfdf00->version,z5bbcf8be2c,moduleId)){sprintf(msg,"\x25\x73\x20\x77\x72\x6f\x6e\x67\x20\x76\x65\x72\x73\x69\x6f\x6e\x20\x6f\x66\x20\x49\x4e\x54\x41\x20\x63\x6f\x64\x65\x20\x6d\x6f\x64\x75\x6c\x65\x21" "\n",boardName);ssSetErrorStatus(S,msg);return;}
#endif
}static void sg_ModelStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
uint32_t z7be9105675,val;volatile z79f5963ede*zf97bbfdf00;zf97bbfdf00=(void*)ssGetPWorkValue(S,z0194338df7);val=(0x124c+2343-0x1b73);z7be9105675=(uint32_t)mxGetPr(ze9153280f8)[(0x10b4+5062-0x247a)];val=val|(z7be9105675<<(0xd77+1721-0x142f));z7be9105675=(uint32_t)mxGetPr(z1120e7330e)[(0x371+189-0x42e)];val=val|(z7be9105675<<(0x2b0+4327-0x1395));z7be9105675=(uint32_t)mxGetPr(z644559a0a7)[(0x9b+1995-0x866)];val=val|(z7be9105675<<(0x138b+4146-0x23b1));zf97bbfdf00->zab46142f2e=val;
#endif
}static void sg_ModelStep(SimStruct*S){
#ifndef MATLAB_MEX_FILE
#endif
}static void sg_ModelStop(SimStruct*S){
#ifndef MATLAB_MEX_FILE
volatile z79f5963ede*zf97bbfdf00;zf97bbfdf00=(void*)ssGetPWorkValue(S,z0194338df7);zf97bbfdf00->zab46142f2e=(0x1ba+3380-0xeee);zf97bbfdf00->clear=(0xee2+5844-0x25b5);sg_wait_s(z5c3f5520e2);zf97bbfdf00->clear=(0x1d8b+12-0x1d97);
#endif
}
#include "sg_sfcn_glue.h"   


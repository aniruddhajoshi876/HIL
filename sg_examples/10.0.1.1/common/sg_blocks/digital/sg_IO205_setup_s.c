// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL (0x10a2+4807-0x2367)
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME sg_IO205_setup_s
#include "sg_io205.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "simstruc.h"
#ifdef MATLAB_MEX_FILE
#include "mex.h"
#else
#include "sg_common.h"
#include "sg_module_registry.h"
#include "sg_module_types.h"
#include "sg_printf.h"
#endif
#define SG_HAS_MDL_EXIT 
#define SG_EARLY_INIT   
#include "sg_callback.h"
#define za00184cdc1   ssGetSFcnParam(S, (0x1023+3566-0x1e11))
#define z702a26a5e9       ssGetSFcnParam(S, (0x15b5+3343-0x22c3))
#define zc8bbaa6115      ssGetSFcnParam(S, (0x6a4+3396-0x13e6))
#define zd1b4794672      ssGetSFcnParam(S, (0x778+2844-0x1291))
#define zdf24515981 ((0x9a1+4853-0x1c92))
#define z2e6483d505 ((0xd48+1931-0x14d3))
#define zc5ce4cb81a ((0x18cc+250-0x19c6))
#define z0194338df7 ((0x1c6b+1487-0x223a))
#define z2b17e2ee3b      ((0x9dc+1958-0x1181))
#define THRESHOLD 0.5
static char_T msg[(0x3f0+774-0x5f6)];static void mdlInitializeSizes(SimStruct*S){uint16_T i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x251d+325-0x2662));ssSetNumDiscStates(S,(0x646+4457-0x17af));ssSetNumInputPorts(S,(0x58d+8241-0x25be));ssSetNumOutputPorts(S,(0x463+4513-0x1604));ssSetNumSampleTimes(S,(0x816+1793-0xf16));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x1841+652-0x1acd));ssSetNumNonsampledZCs(S,(0x529+6257-0x1d9a));for(i=(0x8db+7069-0x2478);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x716+4624-0x1926));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE|SS_OPTION_PLACE_ASAP);}static void mdlInitializeSampleTimes(SimStruct*S){ssSetSampleTime(S,(0xb5b+937-0xf04),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x1c1+6442-0x1aeb),FIXED_IN_MINOR_STEP_OFFSET);}
#ifndef MATLAB_MEX_FILE
static void sg_ModelLoad(SimStruct*S){z6003b3247e*zae10e3f17f;sg_mod_info*mod_info;int bus,slot;int za0d38ae598;za0d38ae598=(int)mxGetPr(za00184cdc1)[(0x17c+4067-0x115f)];SG_PRINTF(DEBUG,"\x25\x73\x20\x28\x49\x44\x20\x25\x64\x29\x20\x53\x65\x74\x75\x70\x3a\x20\x25\x73\x20\x73\x67\x5f\x4d\x6f\x64\x65\x6c\x4c\x6f\x61\x64" "\n",DEVNAME,za0d38ae598,sg_isFirstModelLoad()?"\x20\x46\x69\x72\x73\x74":"");if(mxGetN(z702a26a5e9)==(0x19ef+901-0x1d73)){bus=(0xf9f+4351-0x209e);slot=(int)mxGetPr(z702a26a5e9)[(0x15b4+3106-0x21d6)];}else{bus=(int)mxGetPr(z702a26a5e9)[(0x1907+3083-0x2512)];slot=(int)mxGetPr(z702a26a5e9)[(0x463+8843-0x26ed)];}if(sg_module_get_single(zd215f6920d,za0d38ae598)){SG_PRINTF(DEBUG,"\x25\x73\x20\x28\x49\x44\x20\x25\x64\x29\x20\x53\x65\x74\x75\x70\x3a\x20\x4d\x6f\x64\x75\x6c\x65\x20\x72\x65\x67\x69\x73\x74\x65\x72\x65\x64\x20\x61\x6c\x72\x65\x61\x64\x79" "\n",DEVNAME,za0d38ae598);return;}SG_PRINTF(DEBUG,"\x25\x73\x20\x28\x49\x44\x20\x25\x64\x29\x20\x53\x65\x74\x75\x70\x3a\x20\x52\x65\x67\x69\x73\x74\x65\x72\x20\x6d\x6f\x64\x75\x6c\x65" "\n",DEVNAME,za0d38ae598);mod_info=sg_module_register(zd215f6920d,za0d38ae598);zae10e3f17f=malloc(sizeof(z6003b3247e));mod_info->custom_data=(void*)zae10e3f17f;if(sg_findPciDevice(&zae10e3f17f->ze296e0333d,DEVNAME,VENDORID,DEVICEID,SG_NO_SUB,SG_NO_SUB,za0d38ae598,bus,slot)){ssSetErrorStatus(S,pSgErrorStr);return;}zae10e3f17f->z8a7a7fdd39=(volatile uint32_t*)sg_mapMemory(&(zae10e3f17f->ze296e0333d),(0xb+6508-0x1977));zae10e3f17f->z919abdb780=(volatile uint32_t*)sg_mapMemory(&(zae10e3f17f->ze296e0333d),(0x6ed+457-0x8b4));zae10e3f17f->z8a7a7fdd39[(0xf81+2282-0x1861)]=zae10e3f17f->z8a7a7fdd39[(0xe49+2276-0x1723)]&4278190079;uint32_T out;for(uint32_T i=(0x410+762-0x70a);i<(0xb3d+3162-0x1777);i++){if(mxGetPr(zd1b4794672)[i]>=THRESHOLD){out|=((0x14b1+3564-0x229c)<<i);}else{out&=~((0x2df+514-0x4e0)<<i);}}zae10e3f17f->z919abdb780[(0x827+4186-0x1881)]=out;}static void sg_ModelStart(SimStruct*S){SG_PRINTF(DEBUG,"\x25\x73\x20\x28\x49\x44\x20\x25\x64\x29\x20\x53\x65\x74\x75\x70\x3a\x20\x73\x67\x5f\x4d\x6f\x64\x65\x6c\x53\x74\x61\x72\x74" "\n",DEVNAME,(int)mxGetPr(za00184cdc1)[(0x1c6+7477-0x1efb)]);}static void sg_ModelStep(SimStruct*S){}static void sg_ModelStop(SimStruct*S){int za0d38ae598=(int)mxGetPr(za00184cdc1)[(0x1e67+1037-0x2274)];SG_PRINTF(DEBUG,"\x25\x73\x20\x28\x49\x44\x20\x25\x64\x29\x20\x53\x65\x74\x75\x70\x3a\x20\x73\x67\x5f\x4d\x6f\x64\x65\x6c\x53\x74\x6f\x70" "\n",DEVNAME,za0d38ae598);z6003b3247e*zae10e3f17f=(z6003b3247e*)sg_module_get_custom_data(zd215f6920d,za0d38ae598);if(!zae10e3f17f){sprintf(msg,"\x25\x73\x20\x28\x49\x44\x20\x25\x64\x29\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x72\x65\x74\x72\x69\x65\x76\x65\x20\x6d\x6f\x64\x75\x6c\x65\x20\x66\x72\x6f\x6d\x20\x72\x65\x67\x69\x73\x74\x72\x79" "\n",DEVNAME,za0d38ae598);ssSetErrorStatus(S,msg);return;}uint32_T out=zae10e3f17f->z919abdb780[(0x43f+6659-0x1e42)];for(uint32_T i=(0x19f2+1690-0x208c);i<(0xff3+2108-0x180f);i++){if((uint32_T)mxGetPr(zc8bbaa6115)[i]){if(mxGetPr(zd1b4794672)[i]>=THRESHOLD){out|=((0x993+2311-0x1299)<<i);}else{out&=~((0x1d06+2021-0x24ea)<<i);}}}zae10e3f17f->z919abdb780[(0x1ac+500-0x3a0)]=out;}static void sg_ModelExit(SimStruct*S){int za0d38ae598=(int)mxGetPr(za00184cdc1)[(0x1421+4159-0x2460)];SG_PRINTF(DEBUG,"\x25\x73\x20\x28\x49\x44\x20\x25\x64\x29\x20\x53\x65\x74\x75\x70\x3a\x20\x73\x67\x5f\x4d\x6f\x64\x65\x6c\x45\x78\x69\x74" "\n",DEVNAME,za0d38ae598);z6003b3247e*zae10e3f17f=(z6003b3247e*)sg_module_get_custom_data(zd215f6920d,za0d38ae598);if(zae10e3f17f){SG_PRINTF(DEBUG,"\x25\x73\x20\x28\x49\x44\x20\x25\x64\x29\x20\x53\x65\x74\x75\x70\x3a\x20\x46\x72\x65\x65\x20\x64\x65\x76\x69\x63\x65\x20\x73\x74\x72\x75\x63\x74" "\n",DEVNAME,za0d38ae598);free(zae10e3f17f);SG_PRINTF(DEBUG,"\x25\x73\x20\x28\x49\x44\x20\x25\x64\x29\x20\x53\x65\x74\x75\x70\x3a\x20\x55\x6e\x72\x65\x67\x69\x73\x74\x65\x72\x20\x6d\x6f\x64\x75\x6c\x65" "\n",DEVNAME,za0d38ae598);sg_module_unregister(zd215f6920d,za0d38ae598);}}
#endif 
#include "sg_sfcn_glue.h" 


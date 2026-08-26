// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL (0x976+2903-0x14cb)
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME sg_IO204_setup_s
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "sg_io204.h"
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
#define za00184cdc1   ssGetSFcnParam(S, (0x19db+3277-0x26a8))
#define z702a26a5e9       ssGetSFcnParam(S, (0x21f2+249-0x22ea))
#define z1120e7330e   ssGetSFcnParam(S, (0x16fc+1511-0x1ce1))
#define zc8bbaa6115      ssGetSFcnParam(S, (0x22a4+481-0x2482))
#define zd1b4794672      ssGetSFcnParam(S, (0x878+6272-0x20f4))
#define zdf24515981 ((0xa18+4585-0x1bfc))
#define z8b20b92ea1 0.5
static char msg[(0x1938+3694-0x26a6)];static void mdlInitializeSizes(SimStruct*S){ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x1dd2+225-0x1eb3));ssSetNumDiscStates(S,(0xbcc+5261-0x2059));(void)ssSetNumInputPorts(S,(0x32+6727-0x1a79));(void)ssSetNumOutputPorts(S,(0x3d2+6370-0x1cb4));ssSetNumSampleTimes(S,(0x2012+1276-0x250d));ssSetNumRWork(S,(0x1c09+2347-0x2534));ssSetNumIWork(S,(0x15f8+3483-0x2393));ssSetNumPWork(S,(0x75b+4222-0x17d9));ssSetNumModes(S,(0x34d+6699-0x1d78));ssSetNumNonsampledZCs(S,(0xfaf+5467-0x250a));for(uint16_T i=(0x7a5+2107-0xfe0);i<zdf24515981;i++)ssSetSFcnParamTunable(S,i,(0xc81+3654-0x1ac7));ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE|SS_OPTION_PLACE_ASAP);}static void mdlInitializeSampleTimes(SimStruct*S){ssSetSampleTime(S,(0x158f+275-0x16a2),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x1059+4552-0x2221),FIXED_IN_MINOR_STEP_OFFSET);}
#ifndef MATLAB_MEX_FILE
static void sg_ModelLoad(SimStruct*S){z36f890056f*zae10e3f17f;sg_mod_info*mod_info;int bus,slot;int za0d38ae598;za0d38ae598=(int)mxGetPr(za00184cdc1)[(0x5cd+936-0x975)];SG_PRINTF(DEBUG,"\x25\x73\x20\x28\x49\x44\x20\x25\x64\x29\x20\x53\x65\x74\x75\x70\x3a\x20\x25\x73\x20\x73\x67\x5f\x4d\x6f\x64\x65\x6c\x4c\x6f\x61\x64" "\n",DEVNAME,za0d38ae598,sg_isFirstModelLoad()?"\x20\x46\x69\x72\x73\x74":"");if(mxGetN(z702a26a5e9)==(0xe2b+3064-0x1a22)){bus=(0xbfc+1016-0xff4);slot=(int)mxGetPr(z702a26a5e9)[(0x49d+3084-0x10a9)];}else{bus=(int)mxGetPr(z702a26a5e9)[(0x1854+3198-0x24d2)];slot=(int)mxGetPr(z702a26a5e9)[(0xa74+2326-0x1389)];}if(sg_module_get_single(zc2d861b965,za0d38ae598)){SG_PRINTF(DEBUG,"\x25\x73\x20\x28\x49\x44\x20\x25\x64\x29\x20\x53\x65\x74\x75\x70\x3a\x20\x4d\x6f\x64\x75\x6c\x65\x20\x72\x65\x67\x69\x73\x74\x65\x72\x65\x64\x20\x61\x6c\x72\x65\x61\x64\x79" "\n",DEVNAME,za0d38ae598);return;}SG_PRINTF(DEBUG,"\x25\x73\x20\x28\x49\x44\x20\x25\x64\x29\x20\x53\x65\x74\x75\x70\x3a\x20\x52\x65\x67\x69\x73\x74\x65\x72\x20\x6d\x6f\x64\x75\x6c\x65" "\n",DEVNAME,za0d38ae598);mod_info=sg_module_register(zc2d861b965,za0d38ae598);zae10e3f17f=malloc(sizeof(z36f890056f));mod_info->custom_data=(void*)zae10e3f17f;if(sg_findPciDevice(&zae10e3f17f->ze296e0333d,DEVNAME,VENDORID,DEVICEID,SG_NO_SUB,SG_NO_SUB,za0d38ae598,bus,slot)){ssSetErrorStatus(S,pSgErrorStr);return;}zae10e3f17f->z8a7a7fdd39=(volatile uint32_t*)sg_mapMemory(&(zae10e3f17f->ze296e0333d),(0x1354+3039-0x1f33));
#if defined(__QNX__)
zae10e3f17f->z422873c946=(int)zae10e3f17f->ze296e0333d.BaseAddress_raw[(0x1426+1157-0x18a9)].type;
#elif defined(__linux__)
if(zae10e3f17f->ze296e0333d.Length[(0x2cc+3782-0x1190)]==(0x58b+7185-0x219c)){sprintf(msg,"\x25\x73\x20\x28\x49\x44\x20\x25\x64\x29\x3a\x20\x55\x6e\x73\x75\x70\x70\x6f\x72\x74\x65\x64\x20\x50\x43\x49\x20\x64\x65\x76\x69\x63\x65\x20\x28\x49\x2f\x4f\x20\x6d\x61\x70\x70\x65\x64\x20\x42\x41\x52\x29" "\n",DEVNAME,za0d38ae598);ssSetErrorStatus(S,msg);return;}else{
#if defined(__aarch64__)
zae10e3f17f->z422873c946=(0x79c+5053-0x1b58);
#elif defined(__x86_64__)
if((zae10e3f17f->ze296e0333d.BaseAddress_raw[(0xf9b+173-0x1046)]&(0x1b98+1656-0x220f))==(0xa67+2671-0x14d5)){zae10e3f17f->z422873c946=(0x135d+4392-0x2483);}else{zae10e3f17f->z422873c946=(0x150d+1889-0x1c6d);}
#endif
}
#else
#error "Unsupported platform"
#endif
if(zae10e3f17f->z422873c946==(0xee1+4708-0x2144)){zae10e3f17f->zc3873c1935=(z6ace18ed94*)sg_mapMemory(&(zae10e3f17f->ze296e0333d),(0x1985+765-0x1c80));}else if(zae10e3f17f->z422873c946==(0x116f+1575-0x1794)){zae10e3f17f->ze8d6ac6ed7=(uintptr_t)sg_mapIo(&(zae10e3f17f->ze296e0333d),(0xf19+5460-0x246b));}else{sprintf(msg,"\x25\x73\x20\x28\x49\x44\x20\x25\x64\x29\x3a\x20\x55\x6e\x73\x75\x70\x70\x6f\x72\x74\x65\x64\x20\x50\x43\x49\x20\x64\x65\x76\x69\x63\x65\x20\x74\x79\x70\x65" "\n",DEVNAME,za0d38ae598);ssSetErrorStatus(S,msg);return;}zae10e3f17f->z8a7a7fdd39[(0x9d3+7453-0x26e6)]=zae10e3f17f->z8a7a7fdd39[(0x703+1767-0xde0)]&4278190079;if(mxGetPr(z1120e7330e)[(0xe47+1491-0x141a)]<0.0){SG_PRINTF(DEBUG,"\x25\x73\x20\x28\x49\x44\x20\x25\x64\x29\x20\x53\x65\x74\x75\x70\x3a\x20\x44\x69\x73\x61\x62\x6c\x65\x20\x64\x65\x62\x6f\x75\x6e\x63\x65" "\n",DEVNAME,za0d38ae598);if(zae10e3f17f->z422873c946==(0xf44+3917-0x1e90)){zae10e3f17f->zc3873c1935->z5e65790c24=(0x15b7+3137-0x21f8);}else if(zae10e3f17f->z422873c946==(0x15dc+3240-0x2282)){sg_outpW((uintptr_t)(zae10e3f17f->ze8d6ac6ed7)+(0xd0d+3339-0x1a14),(0x279+3826-0x116b));}}else{uint16_t ze39694ad62=(uint16_t)mxGetPr(z1120e7330e)[(0x13c1+4766-0x265f)];SG_PRINTF(DEBUG,"\x25\x73\x20\x28\x49\x44\x20\x25\x64\x29\x20\x53\x65\x74\x75\x70\x3a\x20\x45\x6e\x61\x62\x6c\x65\x20\x64\x65\x62\x6f\x75\x6e\x63\x65\x3a\x20\x25\x69" "\n",DEVNAME,za0d38ae598,ze39694ad62);if(zae10e3f17f->z422873c946==(0x1088+2689-0x1b08)){zae10e3f17f->zc3873c1935->z5e65790c24=(0xdca+3074-0x19c8);zae10e3f17f->zc3873c1935->z3f03120386=ze39694ad62;}else if(zae10e3f17f->z422873c946==(0x8e7+623-0xb54)){sg_outpW((uintptr_t)(zae10e3f17f->ze8d6ac6ed7)+(0x8ad+1081-0xce2),(0x287+953-0x63c));sg_outpW((uintptr_t)(zae10e3f17f->ze8d6ac6ed7)+(0x103c+1278-0x152c),ze39694ad62);}}zae10e3f17f->z8a7a7fdd39[(0x1f71+605-0x2182)/(0xe95+4266-0x1f3b)]&=~(0xb96+2009-0x1270);uint32_t out=(0x222+3131-0xe5d);for(int i=(0x1085+3912-0x1fcd);i<z069b97c2dc;i++)if(mxGetPr(zd1b4794672)[i]>=z8b20b92ea1)out|=((0xb7c+6418-0x248d)<<i);if(zae10e3f17f->z422873c946==(0x1fcc+131-0x204e)){zae10e3f17f->zc3873c1935->z87ef16205f=out;}else if(zae10e3f17f->z422873c946==(0x843+7642-0x261b)){sg_outpW((uintptr_t)(zae10e3f17f->ze8d6ac6ed7)+(0x3a9+27-0x3c4),out);}}static void sg_ModelStart(SimStruct*S){SG_PRINTF(DEBUG,"\x25\x73\x20\x28\x49\x44\x20\x25\x64\x29\x20\x53\x65\x74\x75\x70\x3a\x20\x73\x67\x5f\x4d\x6f\x64\x65\x6c\x53\x74\x61\x72\x74" "\n",DEVNAME,(int)mxGetPr(za00184cdc1)[(0x1d63+169-0x1e0c)]);}static void sg_ModelStep(SimStruct*S){}static void sg_ModelStop(SimStruct*S){int za0d38ae598=(int)mxGetPr(za00184cdc1)[(0x195+458-0x35f)];SG_PRINTF(DEBUG,"\x25\x73\x20\x28\x49\x44\x20\x25\x64\x29\x20\x53\x65\x74\x75\x70\x3a\x20\x73\x67\x5f\x4d\x6f\x64\x65\x6c\x53\x74\x6f\x70" "\n",DEVNAME,za0d38ae598);z36f890056f*zae10e3f17f=(z36f890056f*)sg_module_get_custom_data(zc2d861b965,za0d38ae598);if(!zae10e3f17f){sprintf(msg,"\x25\x73\x20\x28\x49\x44\x20\x25\x64\x29\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x72\x65\x74\x72\x69\x65\x76\x65\x20\x6d\x6f\x64\x75\x6c\x65\x20\x66\x72\x6f\x6d\x20\x72\x65\x67\x69\x73\x74\x72\x79" "\n",DEVNAME,za0d38ae598);ssSetErrorStatus(S,msg);return;}uint32_t out=(0x16d0+2460-0x206c);if(zae10e3f17f->z422873c946==(0xa30+4088-0x1a27)){out=zae10e3f17f->zc3873c1935->z87ef16205f;}else if(zae10e3f17f->z422873c946==(0x4d7+4769-0x1776)){out=sg_inpW((uintptr_t)(zae10e3f17f->ze8d6ac6ed7)+(0x352+3747-0x11f5));}for(int i=(0x183+2204-0xa1f);i<z069b97c2dc;i++)if((uint32_t)mxGetPr(zc8bbaa6115)[i]){if(mxGetPr(zd1b4794672)[i]>=z8b20b92ea1)out|=((0x18d5+1686-0x1f6a)<<i);else out&=~((0x10b+1645-0x777)<<i);}if(zae10e3f17f->z422873c946==(0xcf8+5151-0x2116)){zae10e3f17f->zc3873c1935->z87ef16205f=out;}else if(zae10e3f17f->z422873c946==(0x16ec+2016-0x1eca)){sg_outpW((uintptr_t)(zae10e3f17f->ze8d6ac6ed7)+(0x12c+68-0x170),out);}}static void sg_ModelExit(SimStruct*S){int za0d38ae598=(int)mxGetPr(za00184cdc1)[(0x564+3141-0x11a9)];SG_PRINTF(DEBUG,"\x25\x73\x20\x28\x49\x44\x20\x25\x64\x29\x20\x53\x65\x74\x75\x70\x3a\x20\x73\x67\x5f\x4d\x6f\x64\x65\x6c\x45\x78\x69\x74" "\n",
DEVNAME,za0d38ae598);z36f890056f*zae10e3f17f=(z36f890056f*)sg_module_get_custom_data(zc2d861b965,za0d38ae598);if(zae10e3f17f){SG_PRINTF(DEBUG,"\x25\x73\x20\x28\x49\x44\x20\x25\x64\x29\x20\x53\x65\x74\x75\x70\x3a\x20\x46\x72\x65\x65\x20\x64\x65\x76\x69\x63\x65\x20\x73\x74\x72\x75\x63\x74" "\n",DEVNAME,za0d38ae598);free(zae10e3f17f);SG_PRINTF(DEBUG,"\x25\x73\x20\x28\x49\x44\x20\x25\x64\x29\x20\x53\x65\x74\x75\x70\x3a\x20\x55\x6e\x72\x65\x67\x69\x73\x74\x65\x72\x20\x6d\x6f\x64\x75\x6c\x65" "\n",DEVNAME,za0d38ae598);sg_module_unregister(zc2d861b965,za0d38ae598);}}
#endif 
#include "sg_sfcn_glue.h" 


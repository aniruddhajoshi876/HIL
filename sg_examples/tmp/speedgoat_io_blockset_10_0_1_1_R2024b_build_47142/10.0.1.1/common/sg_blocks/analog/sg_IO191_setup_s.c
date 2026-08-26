// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL    (0xfb5+2273-0x1894)
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME     sg_IO191_setup_s
#include "sg_io191.h"
#ifndef MATLAB_MEX_FILE
#include "sg_printf.h"
#include "sg_common.h"
#include "sg_module_registry.h"
#include "sg_module_types.h"
static const int z0e14cce82f=z3cbf6b0256;void readPciBar(sg_PCIDevice*z7c46aa329e,int16_t bus,int16_t slot,int16_t z1e0fd5210f);
#else
#include "mex.h"
#endif
#define SG_HAS_MDL_EXIT 
#define SG_EARLY_INIT   
#include "sg_callback.h"
#define z702a26a5e9                ssGetSFcnParam(S, (0xb78+3314-0x186a))
#define ze13f49a01f           ssGetSFcnParam(S, (0x59a+158-0x637))
#define z1e0b67709d       ssGetSFcnParam(S, (0x231+467-0x402))
#define z3644586f49         ssGetSFcnParam(S, (0x21db+823-0x250f))
#define z8d5c288b32         ssGetSFcnParam(S, (0x637+2064-0xe43))
#define z9876548c58         ssGetSFcnParam(S, (0x1732+3509-0x24e2))
#define zfa79626a1f        ssGetSFcnParam(S, (0x1423+4029-0x23da))
#define z832477988f        ssGetSFcnParam(S, (0x12c6+3982-0x224d))
#define z4526a8632b         ssGetSFcnParam(S, (0x79b+6833-0x2244))
#define zdf24515981                           ((0x1a6+5823-0x185c))
#define z2e6483d505              ((0x130+4860-0x142c))
#define zc5ce4cb81a              ((0x441+8422-0x2527))
#define z2b17e2ee3b              ((0x8a0+592-0xaf0))
static char msg[z71934bf57c];static void mdlInitializeSizes(SimStruct*S){uint16_t i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x20d7+329-0x2220));ssSetNumDiscStates(S,(0x960+3978-0x18ea));if(!ssSetNumInputPorts(S,(0xf9c+5831-0x2663)))return;if(!ssSetNumOutputPorts(S,(0xc13+3954-0x1b85)))return;ssSetNumSampleTimes(S,(0x1285+445-0x1441));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x752+6487-0x20a9));ssSetNumNonsampledZCs(S,(0x85b+7725-0x2688));for(i=(0x80a+1153-0xc8b);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x67b+4769-0x191c));}ssSetOptions(S,SS_OPTION_DISALLOW_CONSTANT_SAMPLE_TIME|SS_OPTION_EXCEPTION_FREE_CODE|SS_OPTION_RUNTIME_EXCEPTION_FREE_CODE|SS_OPTION_PLACE_ASAP);}static void mdlInitializeSampleTimes(SimStruct*S){ssSetSampleTime(S,(0x162b+69-0x1670),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x36+4022-0xfec),FIXED_IN_MINOR_STEP_OFFSET);ssSetModelReferenceSampleTimeDefaultInheritance(S);}
#ifndef MATLAB_MEX_FILE
static void sg_ModelLoad(SimStruct*S){sg_PCIDevice zeccbadd9b3;int16_t bus,slot,za0d38ae598,i;uint16_t channel,z0e26ef1137;z883f474cfe*zae10e3f17f=NULL;sg_mod_info*mod_info=NULL;if(mxGetN(z702a26a5e9)==(0xaa2+5977-0x21fa)){bus=(0xf55+3938-0x1eb7);slot=(int16_t)mxGetPr(z702a26a5e9)[(0xf37+4696-0x218f)];}else{bus=(int16_t)mxGetPr(z702a26a5e9)[(0xce8+4421-0x1e2d)];slot=(int16_t)mxGetPr(z702a26a5e9)[(0xb86+1963-0x1330)];}za0d38ae598=((int16_t)mxGetPr(ze13f49a01f)[(0xc16+191-0xcd5)]);if(sg_module_get_single(z0e14cce82f,za0d38ae598)){SG_PRINTF(DEBUG,"\x25\x73\x20\x28\x49\x44\x20\x25\x64\x29\x20\x53\x65\x74\x75\x70\x3a\x20\x4d\x6f\x64\x75\x6c\x65\x20\x61\x6c\x72\x65\x61\x64\x79\x20\x72\x65\x67\x69\x73\x74\x65\x72\x65\x64\x21" "\n",DEVNAME,za0d38ae598);return;}SG_PRINTF(DEBUG,"\x25\x73\x20\x28\x49\x44\x20\x25\x64\x29\x20\x53\x65\x74\x75\x70\x3a\x20\x52\x65\x67\x69\x73\x74\x65\x72\x69\x6e\x67\x20\x6d\x6f\x64\x75\x6c\x65" "\n",DEVNAME,za0d38ae598);mod_info=sg_module_register(z0e14cce82f,za0d38ae598);zae10e3f17f=(z883f474cfe*)malloc(sizeof(z883f474cfe));mod_info->custom_data=(void*)zae10e3f17f;if(sg_findPciDevice(&zeccbadd9b3,DEVNAME,VENDORID,za1afbacc4a,z78f5b4c5a6,z2bc00458b9,za0d38ae598,bus,slot)!=(0xa14+619-0xc7f)){if(sg_findPciDevice(&zeccbadd9b3,DEVNAME,VENDORID,zb765876dc5,z44a525e63d,za64fcbac7d,za0d38ae598,bus,slot)!=(0x265+1822-0x983)){ssSetErrorStatus(S,pSgErrorStr);return;}}
#ifdef _MSC_BUILD
readPciBar(&zeccbadd9b3,zeccbadd9b3.bus,zeccbadd9b3.slot,(0x1aa+2030-0x998));
#endif
zae10e3f17f->zeccbadd9b3=zeccbadd9b3;zae10e3f17f->z3e5b8e05d8=(zeb49e172d5*)sg_mapMemory(&zeccbadd9b3,(0xf2+1635-0x755));zae10e3f17f->z27fd94ac66=(z5419123aee*)sg_mapMemory(&zeccbadd9b3,(0x977+3683-0x17d8));SG_PRINTF_DEBUG("\x25\x73\x3a\x20\x46\x50\x47\x41\x20\x72\x65\x76\x20\x30\x78\x25\x58" "\n",DEVNAME,zae10e3f17f->z27fd94ac66->revision);zae10e3f17f->revision=zae10e3f17f->z27fd94ac66->revision;z0e26ef1137=(0x1f3f+683-0x21ea);for(i=(0xe65+1423-0x13f4);i<(uint32_t)mxGetN(z4526a8632b);i++){channel=(uint32_t)mxGetPr(z4526a8632b)[i];if(channel==(0x1100+576-0x133f)){z0e26ef1137=(0x19a8+2362-0x22e1);}else{z0e26ef1137|=((0xcf4+3399-0x1a3a)<<(channel+(0x14a3+763-0x1798)));}}zae10e3f17f->z27fd94ac66->z294066ffb4=z0e26ef1137;}static void sg_ModelStart(SimStruct*S){}static void sg_ModelStep(SimStruct*S){}static void sg_ModelStop(SimStruct*S){}static void sg_ModelExit(SimStruct*S){int za0d38ae598=(int)mxGetPr(ze13f49a01f)[(0x24b7+57-0x24f0)];SG_PRINTF(DEBUG,"\x25\x73\x20\x28\x49\x44\x20\x25\x64\x29\x20\x53\x65\x74\x75\x70\x3a\x20\x73\x67\x5f\x4d\x6f\x64\x65\x6c\x45\x78\x69\x74" "\n",DEVNAME,za0d38ae598);z883f474cfe*zae10e3f17f=(z883f474cfe*)sg_module_get_custom_data(z0e14cce82f,za0d38ae598);if(zae10e3f17f){SG_PRINTF(DEBUG,"\x25\x73\x20\x28\x49\x44\x20\x25\x64\x29\x20\x53\x65\x74\x75\x70\x3a\x20\x46\x72\x65\x65\x20\x64\x65\x76\x69\x63\x65\x20\x73\x74\x72\x75\x63\x74" "\n",DEVNAME,za0d38ae598);free(zae10e3f17f);SG_PRINTF(DEBUG,"\x25\x73\x20\x28\x49\x44\x20\x25\x64\x29\x20\x53\x65\x74\x75\x70\x3a\x20\x55\x6e\x72\x65\x67\x69\x73\x74\x65\x72\x20\x6d\x6f\x64\x75\x6c\x65" "\n",DEVNAME,za0d38ae598);sg_module_unregister(z0e14cce82f,za0d38ae598);}}
#endif  
#include "sg_sfcn_glue.h"   


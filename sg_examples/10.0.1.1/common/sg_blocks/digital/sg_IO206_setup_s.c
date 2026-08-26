// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL    (0x4ca+3327-0x11c7)
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME    sg_IO206_setup_s
#include "sg_io206.h"
#include "simstruc.h"
#ifndef MATLAB_MEX_FILE
#include "sg_printf.h"
#include "sg_common.h"
#include "sg_module_registry.h"
#include "sg_module_types.h"
static const int z0e14cce82f=zedc83d0317;
#else
#include "mex.h"
#endif
#define SG_HAS_MDL_EXIT 
#define SG_EARLY_INIT   
#include "sg_callback.h"
#define z702a26a5e9                ssGetSFcnParam(S, (0xd6a+6564-0x270e))
#define z1120e7330e            ssGetSFcnParam(S, (0x1278+1616-0x18c7))
#define ze13f49a01f           ssGetSFcnParam(S, (0xfc4+5136-0x23d2))
#define zdf24515981          ((0x975+2386-0x12c4))
#define z2e6483d505              ((0x19c0+158-0x1a5e))
#define zc5ce4cb81a              ((0x1e12+1608-0x245a))
#define z2b17e2ee3b              ((0xe7+9090-0x2469))
static char_T msg[(0xecd+4204-0x1e39)];static void mdlInitializeSizes(SimStruct*S){uint16_T i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0xd9b+3671-0x1bf2));ssSetNumDiscStates(S,(0x399+3622-0x11bf));if(!ssSetNumInputPorts(S,(0xed2+5561-0x248b)))return;if(!ssSetNumOutputPorts(S,(0xb0b+6941-0x2628)))return;ssSetNumSampleTimes(S,(0xb2b+115-0xb9d));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x14da+2174-0x1d58));ssSetNumNonsampledZCs(S,(0x12aa+2995-0x1e5d));for(i=(0xef8+1355-0x1443);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x1579+1448-0x1b21));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE|SS_OPTION_PLACE_ASAP);}static void mdlInitializeSampleTimes(SimStruct*S){ssSetSampleTime(S,(0x5d4+6598-0x1f9a),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x393+3532-0x115f),FIXED_IN_MINOR_STEP_OFFSET);}
#ifndef MATLAB_MEX_FILE
static void sg_ModelLoad(SimStruct*S){sg_PCIDevice zeccbadd9b3;int_T bus,slot,za0d38ae598;z854dcf9b8c*zae10e3f17f=NULL;sg_mod_info*mod_info;if(mxGetN(z702a26a5e9)==(0xe2b+5050-0x21e4)){bus=(0x633+3376-0x1363);slot=(int_T)mxGetPr(z702a26a5e9)[(0xf81+321-0x10c2)];}else{bus=(int_T)mxGetPr(z702a26a5e9)[(0x20a+2921-0xd73)];slot=(int_T)mxGetPr(z702a26a5e9)[(0x16a2+3956-0x2615)];}za0d38ae598=(int_T)mxGetPr(ze13f49a01f)[(0x1595+1847-0x1ccc)];if(sg_module_get_single(z0e14cce82f,za0d38ae598)){SG_PRINTF(DEBUG,"\x25\x73\x20\x28\x49\x44\x20\x25\x64\x29\x20\x53\x65\x74\x75\x70\x3a\x20\x4d\x6f\x64\x75\x6c\x65\x20\x61\x6c\x72\x65\x61\x64\x79\x20\x72\x65\x67\x69\x73\x74\x65\x72\x65\x64\x21" "\n",DEVNAME,za0d38ae598);return;}SG_PRINTF(DEBUG,"\x25\x73\x20\x28\x49\x44\x20\x25\x64\x29\x20\x53\x65\x74\x75\x70\x3a\x20\x52\x65\x67\x69\x73\x74\x65\x72\x69\x6e\x67\x20\x6d\x6f\x64\x75\x6c\x65" "\n",DEVNAME,za0d38ae598);mod_info=sg_module_register(z0e14cce82f,za0d38ae598);zae10e3f17f=(z854dcf9b8c*)malloc(sizeof(z854dcf9b8c));mod_info->custom_data=(void*)zae10e3f17f;if(sg_findPciDevice(&zeccbadd9b3,DEVNAME,VENDORID,DEVICEID,SG_NO_SUB,SG_NO_SUB,za0d38ae598,bus,slot)){ssSetErrorStatus(S,pSgErrorStr);return;}zae10e3f17f->zeccbadd9b3=zeccbadd9b3;zae10e3f17f->z27fd94ac66=(z4abf807e6e*)sg_mapMemory(&zeccbadd9b3,(0x1d+559-0x24a));}static void sg_ModelStart(SimStruct*S){int_T za0d38ae598;z854dcf9b8c*zae10e3f17f=NULL;uint32_t z0a08618570;za0d38ae598=(int)mxGetPr(ze13f49a01f)[(0x238+4080-0x1228)];zae10e3f17f=(z854dcf9b8c*)sg_module_get_custom_data(z0e14cce82f,za0d38ae598);if(!zae10e3f17f){sprintf(msg,"\x25\x73\x20\x28\x49\x44\x20\x25\x64\x29\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x72\x65\x74\x72\x69\x65\x76\x65\x20\x6d\x6f\x64\x75\x6c\x65\x20\x66\x72\x6f\x6d\x20\x72\x65\x67\x69\x73\x74\x72\x79\x20\x69\x6e\x20\x53\x65\x74\x75\x70\x20\x4d\x6f\x64\x65\x6c\x53\x74\x61\x72\x74" "\n",DEVNAME,za0d38ae598);ssSetErrorStatus(S,msg);return;}if(mxGetPr(z1120e7330e)[(0xf3d+4549-0x2102)]<0.0){zae10e3f17f->z27fd94ac66->zc430a259a4=(0x1a00+477-0x1bdd);}else{zae10e3f17f->z27fd94ac66->zc430a259a4=67108864;z0a08618570=(uint32_t)mxGetPr(z1120e7330e)[(0x245f+83-0x24b2)];zae10e3f17f->z27fd94ac66->z0a08618570=(uint32_t)zf683046c76(z0a08618570);}}static void sg_ModelStep(SimStruct*S){}static void sg_ModelStop(SimStruct*S){}static void sg_ModelExit(SimStruct*S){int za0d38ae598=(int)mxGetPr(ze13f49a01f)[(0xfb8+2197-0x184d)];SG_PRINTF(DEBUG,"\x25\x73\x20\x28\x49\x44\x20\x25\x64\x29\x20\x53\x65\x74\x75\x70\x3a\x20\x73\x67\x5f\x4d\x6f\x64\x65\x6c\x45\x78\x69\x74" "\n",DEVNAME,za0d38ae598);z854dcf9b8c*zae10e3f17f=(z854dcf9b8c*)sg_module_get_custom_data(z0e14cce82f,za0d38ae598);if(zae10e3f17f){SG_PRINTF(DEBUG,"\x25\x73\x20\x28\x49\x44\x20\x25\x64\x29\x20\x53\x65\x74\x75\x70\x3a\x20\x46\x72\x65\x65\x20\x64\x65\x76\x69\x63\x65\x20\x73\x74\x72\x75\x63\x74" "\n",DEVNAME,za0d38ae598);free(zae10e3f17f);SG_PRINTF(DEBUG,"\x25\x73\x20\x28\x49\x44\x20\x25\x64\x29\x20\x53\x65\x74\x75\x70\x3a\x20\x55\x6e\x72\x65\x67\x69\x73\x74\x65\x72\x20\x6d\x6f\x64\x75\x6c\x65" "\n",DEVNAME,za0d38ae598);sg_module_unregister(z0e14cce82f,za0d38ae598);}}
#endif  
#include "sg_sfcn_glue.h"   


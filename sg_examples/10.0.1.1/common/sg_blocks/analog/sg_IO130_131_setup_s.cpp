// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL (0xc0c+2036-0x13fe)
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME sg_IO130_131_setup_s
#include "sg_IO130_131.h"
#include <sstream>
#include "simstruc.h"
#ifdef MATLAB_MEX_FILE
#include "mex.h"
#else
#include "sg_common.h"
#include "sg_module_registry.h"
#include "sg_module_types.h"
#include "sg_printf.h"
static const int z0e14cce82f[]={SG_MODULE_TYPE_IO130,SG_MODULE_TYPE_IO131};
#endif
#define SG_HAS_MDL_EXIT 
#define SG_EARLY_INIT   
#include "sg_callback.h"
#define z702a26a5e9         ssGetSFcnParam(S, (0x3e6+2634-0xe30)) 
#define ze13f49a01f    ssGetSFcnParam(S, (0x189a+2658-0x22fb)) 
#define z89d5fad8dc   ssGetSFcnParam(S, (0x10a5+5482-0x260d)) 
#define z3510107221 ssGetSFcnParam(S, (0xf36+1819-0x164e)) 
#define z723d9d6187    ssGetSFcnParam(S, (0xfb5+2032-0x17a1)) 
#define zfd98694cb2    ssGetSFcnParam(S, (0x1daf+1895-0x2511)) 
#define zdf24515981   ((0xe3a+5320-0x22fc))
#define z2e6483d505 ((0xdf7+1729-0x14b8))
#define zc5ce4cb81a ((0xa02+3853-0x190f))
#define zcf7805d649 ((0xea7+4712-0x210f))
#define z2b17e2ee3b      ((0x2c+1462-0x5e1))
static char msg[(0x1470+1207-0x1827)];static void mdlInitializeSizes(SimStruct*S){int i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x14dc+3543-0x22b3));ssSetNumDiscStates(S,(0x1747+1737-0x1e10));if(!ssSetNumInputPorts(S,(0x1244+796-0x1560))){
#ifndef MATLAB_MEX_FILE
SG_PRINTF(ERROR,"\x65\x72\x72\x6f\x72\x20\x77\x68\x69\x6c\x65\x20\x73\x65\x74\x74\x69\x6e\x67\x20\x69\x6e\x70\x75\x74\x20\x70\x6f\x72\x74\x73" "\n");
#endif 
return;}if(!ssSetNumOutputPorts(S,(0x11d5+4305-0x22a6))){
#ifndef MATLAB_MEX_FILE
SG_PRINTF(ERROR,"\x65\x72\x72\x6f\x72\x20\x77\x68\x69\x6c\x65\x20\x73\x65\x74\x74\x69\x6e\x67\x20\x6f\x75\x74\x70\x75\x74\x20\x70\x6f\x72\x74\x73" "\n");
#endif 
return;}ssSetNumSampleTimes(S,(0x1624+1563-0x1c3e));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x191+3523-0xf54));ssSetNumNonsampledZCs(S,(0xaf4+6635-0x24df));for(i=(0x1949+1266-0x1e3b);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,SS_PRM_NOT_TUNABLE);}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE|SS_OPTION_PLACE_ASAP);}static void mdlInitializeSampleTimes(SimStruct*S){ssSetSampleTime(S,(0x473+985-0x84c),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x63f+790-0x955),FIXED_IN_MINOR_STEP_OFFSET);}
#ifndef MATLAB_MEX_FILE
static void sg_ModelLoad(SimStruct*S){sg_PCIDevice zeccbadd9b3;uint32_t bus,slot;int boardType;uint32_t za0d38ae598;uint32_t is_initiator;uint32_t z7be9105675;z061f49348b*zae10e3f17f=nullptr;sg_mod_info*mod_info=nullptr;if(mxGetN(z702a26a5e9)==(0x18e6+1451-0x1e90)){bus=(0x1b4+4749-0x1441);slot=(int)mxGetPr(z702a26a5e9)[(0x620+2315-0xf2b)];}else{bus=(int)mxGetPr(z702a26a5e9)[(0x63a+5901-0x1d47)];slot=(int)mxGetPr(z702a26a5e9)[(0x26d+9149-0x2629)];}za0d38ae598=(int)mxGetPr(ze13f49a01f)[(0x1a3+1898-0x90d)];boardType=((int)mxGetPr(z89d5fad8dc)[(0x6fd+3462-0x1483)])-(0x39b+2878-0xe57);if((boardType>(0x12b6+664-0x154d))||(boardType<(0x1a77+2418-0x23e9))){sprintf(msg,"\x53\x70\x65\x65\x64\x67\x6f\x61\x74\x20\x49\x4f\x31\x33\x30\x20\x2f\x20\x49\x4f\x31\x33\x31\x3a\x20\x49\x6e\x76\x61\x6c\x69\x64\x20\x62\x6f\x61\x72\x64\x20\x74\x79\x70\x65");ssSetErrorStatus(S,msg);return;}if(sg_module_get_single(z0e14cce82f[boardType],za0d38ae598)){SG_PRINTF(DEBUG,"\x25\x73\x20\x28\x49\x44\x20\x25\x64\x29\x20\x53\x65\x74\x75\x70\x3a\x20\x4d\x6f\x64\x75\x6c\x65\x20\x61\x6c\x72\x65\x61\x64\x79\x20\x72\x65\x67\x69\x73\x74\x65\x72\x65\x64\x21" "\n",DEVNAME[boardType],za0d38ae598);return;}SG_PRINTF(DEBUG,"\x25\x73\x20\x28\x49\x44\x20\x25\x64\x29\x20\x53\x65\x74\x75\x70\x3a\x20\x52\x65\x67\x69\x73\x74\x65\x72\x69\x6e\x67\x20\x6d\x6f\x64\x75\x6c\x65" "\n",DEVNAME[boardType],za0d38ae598);mod_info=sg_module_register(z0e14cce82f[boardType],za0d38ae598);is_initiator=(uint32_t)mxGetPr(z3510107221)[(0x1d41+2123-0x258c)];mod_info->is_initiator=(is_initiator==(0x411+4218-0x1489));zae10e3f17f=(z061f49348b*)malloc(sizeof(z061f49348b));zae10e3f17f->z48366712fe=is_initiator;mod_info->custom_data=(void*)zae10e3f17f;if(sg_findPciDevice(&zeccbadd9b3,DEVNAME[boardType],VENDORID,DEVICEID,SUBVENDORID,SUBDEVICEID[boardType],za0d38ae598,bus,slot)){ssSetErrorStatus(S,pSgErrorStr);return;}zae10e3f17f->zeccbadd9b3=zeccbadd9b3;zae10e3f17f->z3e5b8e05d8=(z794df240b5*)sg_mapMemory(&zeccbadd9b3,(0xfe3+3312-0x1cd3));if(zae10e3f17f->z48366712fe!=(0x265+3648-0x10a4))z2717f55476();zae10e3f17f->z3e5b8e05d8->z36e163aa13=(0xa29+5723-0x2083);switch(zae10e3f17f->z48366712fe){case(0xa10+338-0xb61):zae10e3f17f->z3e5b8e05d8->ze99b39b3a2=(0xfac+893-0x1329);break;case(0x80+2241-0x93f):z7be9105675=(mxGetPr(z723d9d6187)[(0x1418+3115-0x2043)])?(zf162765a8b<<z991b628b00):(z83fc38c749<<z991b628b00);z7be9105675|=(mxGetPr(zfd98694cb2)[(0x1d6+5043-0x1589)])?(z22bfb69a2d<<zc2a6ca8247):(z92cf5ad3dd<<zc2a6ca8247);zae10e3f17f->z3e5b8e05d8->ze99b39b3a2=z7be9105675;break;case(0x210a+399-0x2296):zae10e3f17f->z3e5b8e05d8->ze99b39b3a2=((0xd9a+4974-0x2107)<<zc142561f01)|((0x716+2834-0x1227)<<z6fd12002bd);break;default:break;}}static void sg_ModelStart(SimStruct*S){SG_PRINTF(DEBUG,"\x25\x73\x20\x28\x49\x44\x20\x25\x64\x29\x20\x53\x65\x74\x75\x70\x3a\x20\x73\x67\x5f\x4d\x6f\x64\x65\x6c\x53\x74\x61\x72\x74" "\n",DEVNAME[((int)mxGetPr(z89d5fad8dc)[(0x6f4+579-0x937)])-(0x453+6347-0x1c9c)],(int)mxGetPr(ze13f49a01f)[(0xec4+5151-0x22e3)]);}static void sg_ModelStep(SimStruct*S){}static void sg_ModelStop(SimStruct*S){int boardType;int za0d38ae598;boardType=((int)mxGetPr(z89d5fad8dc)[(0x13a+8690-0x232c)])-(0x1e80+1288-0x2306);za0d38ae598=((int)mxGetPr(ze13f49a01f)[(0x825+1580-0xe51)]);SG_PRINTF(DEBUG,"\x25\x73\x20\x28\x49\x44\x20\x25\x64\x29\x20\x53\x65\x74\x75\x70\x3a\x20\x73\x67\x5f\x4d\x6f\x64\x65\x6c\x53\x74\x6f\x70" "\n",DEVNAME[boardType],za0d38ae598);z061f49348b*zae10e3f17f=(z061f49348b*)sg_module_get_custom_data(z0e14cce82f[boardType],za0d38ae598);if(!zae10e3f17f){sprintf(msg,"\x25\x73\x20\x28\x49\x44\x20\x25\x64\x29\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x72\x65\x74\x72\x69\x65\x76\x65\x20\x6d\x6f\x64\x75\x6c\x65\x20\x66\x72\x6f\x6d\x20\x72\x65\x67\x69\x73\x74\x72\x79" "\n",DEVNAME[boardType],za0d38ae598);ssSetErrorStatus(S,msg);return;}zae10e3f17f->z3e5b8e05d8->ze99b39b3a2=(0x929+7122-0x24fb);}static void sg_ModelExit(SimStruct*S){int za0d38ae598=(int)mxGetPr(ze13f49a01f)[(0x6a7+993-0xa88)];int boardType=((int)mxGetPr(z89d5fad8dc)[(0xb28+6321-0x23d9)])-(0x1bf5+388-0x1cf7);SG_PRINTF(DEBUG,
"\x25\x73\x20\x28\x49\x44\x20\x25\x64\x29\x20\x53\x65\x74\x75\x70\x3a\x20\x73\x67\x5f\x4d\x6f\x64\x65\x6c\x45\x78\x69\x74" "\n",DEVNAME[boardType],za0d38ae598);z061f49348b*zae10e3f17f=(z061f49348b*)sg_module_get_custom_data(z0e14cce82f[boardType],za0d38ae598);if(zae10e3f17f){SG_PRINTF(DEBUG,"\x25\x73\x20\x28\x49\x44\x20\x25\x64\x29\x20\x53\x65\x74\x75\x70\x3a\x20\x46\x72\x65\x65\x20\x64\x65\x76\x69\x63\x65\x20\x73\x74\x72\x75\x63\x74" "\n",DEVNAME[boardType],za0d38ae598);free(zae10e3f17f);SG_PRINTF(DEBUG,"\x25\x73\x20\x28\x49\x44\x20\x25\x64\x29\x20\x53\x65\x74\x75\x70\x3a\x20\x55\x6e\x72\x65\x67\x69\x73\x74\x65\x72\x20\x6d\x6f\x64\x75\x6c\x65" "\n",DEVNAME[boardType],za0d38ae598);sg_module_unregister(z0e14cce82f[boardType],za0d38ae598);}}
#endif 
#include "sg_sfcn_glue.h" 


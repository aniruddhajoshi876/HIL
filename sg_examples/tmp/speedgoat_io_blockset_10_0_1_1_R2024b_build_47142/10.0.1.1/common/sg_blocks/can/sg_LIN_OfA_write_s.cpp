// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL (0x460+7055-0x1fed)
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME sg_LIN_OfA_write_s
#ifdef MATLAB_MEX_FILE
#include "mex.h"
#else
#include "sg_common.h"
#endif
#define SG_EARLY_INIT   
#include "simstruc.h"
#include "sg_callback.h"
#include "ESD_OfA.h"
#include "ESD_Module.h"
#include <exception>
#define zefdd6d55b2 (0x1194+1475-0x1756)
#define z5cfd65b291 (0x9fa+4836-0x1cdd)  
#define z4ff5168d43 (0x336+6549-0x1ccb) 
#define z5b80517fba (0x1113+125-0x1190)
#define z15202ccf01 (0x484+6053-0x1c29) 
#define za859b74f53 (0xcc7+5898-0x23d1) 
#define zab82456318 ssGetSFcnParam(S, (0xb6+9138-0x2468))
#ifdef MATLAB_MEX_FILE
static void SetSFunctionInputPortProperties(int32_T z7da5ab49fa,uint32_T zbc29571b7b,uint32_T ze97179dd68,boolean_T z5cda1a8b01,boolean_T zbac08145fb,uint8_T z2548e6cd9c,SimStruct*S);static void SetSFunctionOutputPortProperties(int32_T z7da5ab49fa,int32_T zbc29571b7b,uint32_T ze97179dd68,uint8_T z2548e6cd9c,SimStruct*S);
#endif
static void mdlInitializeSizes(SimStruct*S){ssSetNumSFcnParams(S,zefdd6d55b2);for(int i=(0x1dbf+2368-0x26ff);i<zefdd6d55b2;i++){ssSetSFcnParamTunable(S,i,(0x56a+8136-0x2532));}const LinWriteInitValues*z4965681e9e=reinterpret_cast<const LinWriteInitValues*>(mxGetPr(zab82456318));
#ifdef MATLAB_MEX_FILE
#endif 
ssSetNumRWork(S,z5b80517fba);ssSetNumIWork(S,z15202ccf01);ssSetNumPWork(S,za859b74f53);if(z4965681e9e->dlc!=(0xb89+5337-0x2062)){if(z4965681e9e->z5649cd6678==(0x1769+1452-0x1d14)){ssSetNumInputPorts(S,(0x12f1+438-0x14a5));ssSetInputPortWidth(S,(0x8b1+5753-0x1f2a),(int)z4965681e9e->dlc);ssSetInputPortDataType(S,(0x268+6903-0x1d5f),SS_UINT8);ssSetInputPortRequiredContiguous(S,(0x78b+2274-0x106d),true);ssSetInputPortDirectFeedThrough(S,(0x157a+899-0x18fd),true);ssSetInputPortWidth(S,(0x533+5426-0x1a64),(0x1672+561-0x18a2));ssSetInputPortDataType(S,(0x1ee9+2028-0x26d4),SS_UINT8);ssSetInputPortRequiredContiguous(S,(0x1f3+5367-0x16e9),true);ssSetInputPortDirectFeedThrough(S,(0x14a3+1309-0x19bf),true);}else{ssSetNumInputPorts(S,(0x1994+1152-0x1e13));ssSetInputPortWidth(S,(0x306+4115-0x1319),(int)z4965681e9e->dlc);ssSetInputPortDataType(S,(0xe08+2480-0x17b8),SS_UINT8);ssSetInputPortRequiredContiguous(S,(0xe72+3831-0x1d69),true);ssSetInputPortDirectFeedThrough(S,(0x442+109-0x4af),true);}}else{ssSetNumInputPorts(S,(0x3ef+7516-0x214b));}ssSetNumOutputPorts(S,(0xfb8+1141-0x142d));ssSetNumContStates(S,(0x2c6+2996-0xe7a));ssSetNumDiscStates(S,(0x1a73+2912-0x25d3));ssSetNumSampleTimes(S,(0x13b+7021-0x1ca7));ssSetNumModes(S,(0x21b5+437-0x236a));ssSetNumNonsampledZCs(S,(0x896+1252-0xd7a));ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){const LinWriteInitValues*z4965681e9e=reinterpret_cast<const LinWriteInitValues*>(mxGetPr(zab82456318));if(z4965681e9e->SampleTime==-1.0){ssSetSampleTime(S,(0x702+5735-0x1d69),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0xbe4+5815-0x229b),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x1134+2596-0x1b58),z4965681e9e->SampleTime);ssSetOffsetTime(S,(0xa77+7283-0x26ea),0.0);}}static void sg_ModelLoad(SimStruct*S){
#ifndef MATLAB_MEX_FILE
const LinWriteInitValues*z4965681e9e=reinterpret_cast<const LinWriteInitValues*>(mxGetPr(zab82456318));ESD_Module*module=reinterpret_cast<ESD_Module*>(sg_module_get_custom_data((int)z4965681e9e->Module,(int)z4965681e9e->Id));int z700cd050bf=(int)z4965681e9e->z29d3677448+module->z5b9677fabb();NTLIN_HANDLE za1fc0f0ef5=module->Ports[z700cd050bf]->z59662a1925();NTLIN_RESULT z0e7a5d53db;char z59441137bf[(0x74c+5206-0x1b66)];z0e7a5d53db=linOpen(module->Ports[z700cd050bf]->za9d23ef9b1(),(0x272+3299-0xf55),(0xb20+4040-0x1aa8),&za1fc0f0ef5);if(z0e7a5d53db!=NTLIN_SUCCESS){canFormatError(z0e7a5d53db,NTCAN_ERROR_FORMAT_LONG,z59441137bf,sizeof(z59441137bf));SG_PRINTF(DEBUG,"\x52\x58\x3a\x20\x6c\x69\x6e\x4f\x70\x65\x6e\x20\x66\x6f\x72\x20\x69\x64\x20\x25\x30\x32\x78\x20\x28\x6e\x65\x74\x20\x25\x64\x29\x20\x66\x61\x69\x6c\x65\x64\x3a\x20\x72\x63\x3d\x25\x64\x2c\x20\x25\x73" "\n",(int32_t)z4965681e9e->z9fa29891db,module->Ports[z700cd050bf]->za9d23ef9b1(),z0e7a5d53db,z59441137bf);}z0e7a5d53db=linIdAdd(za1fc0f0ef5,z4965681e9e->z9fa29891db,z98e07f4d2d);if(z0e7a5d53db!=NTLIN_SUCCESS){canFormatError(z0e7a5d53db,NTCAN_ERROR_FORMAT_LONG,z59441137bf,sizeof(z59441137bf));SG_PRINTF(DEBUG,"\x54\x58\x3a\x20\x6c\x69\x6e\x49\x64\x41\x64\x64\x20\x66\x6f\x72\x20\x69\x64\x20\x25\x30\x32\x78\x20\x66\x61\x69\x6c\x65\x64\x3a\x20\x72\x63\x3d\x25\x64\x2c\x20\x25\x73" "\n",(int32_t)z4965681e9e->z9fa29891db,z0e7a5d53db,z59441137bf);}else{SG_PRINTF(DEBUG,"\x54\x58\x3a\x20\x6c\x69\x6e\x49\x64\x41\x64\x64\x20\x66\x6f\x72\x20\x69\x64\x20\x25\x30\x32\x78\x20\x73\x75\x63\x63\x65\x64\x65\x64\x20\x28\x68\x61\x6e\x64\x6c\x65\x20\x3d\x20\x25\x69\x29" "\n",(int32_t)z4965681e9e->z9fa29891db,(int)za1fc0f0ef5);}z0e7a5d53db=linSlaveTxCreate((NTLIN_HANDLE)za1fc0f0ef5,(int32_t)z4965681e9e->z9fa29891db,(0xee4+2601-0x190d));if(z0e7a5d53db!=NTLIN_SUCCESS){canFormatError(z0e7a5d53db,NTCAN_ERROR_FORMAT_LONG,z59441137bf,sizeof(z59441137bf));SG_PRINTF(DEBUG,"\x54\x58\x3a\x20\x6c\x69\x6e\x53\x6c\x61\x76\x65\x54\x78\x43\x72\x65\x61\x74\x65\x28\x29\x20\x63\x68\x49\x64\x78\x20\x3d\x20\x25\x69\x20\x66\x61\x69\x6c\x65\x64\x20\x77\x69\x74\x68\x20\x65\x72\x72\x6f\x72\x20\x25\x69\x2c\x20\x25\x73\x21" "\n",z700cd050bf,z0e7a5d53db,z59441137bf);}else{SG_PRINTF(DEBUG,"\x54\x58\x3a\x20\x6c\x69\x6e\x53\x6c\x61\x76\x65\x54\x78\x43\x72\x65\x61\x74\x65\x20\x66\x6f\x72\x20\x69\x64\x20\x25\x30\x32\x78\x20\x73\x75\x63\x63\x65\x64\x65\x64\x20\x28\x68\x61\x6e\x64\x6c\x65\x20\x3d\x20\x25\x69\x29" "\n",(int32_t)z4965681e9e->z9fa29891db,(int)za1fc0f0ef5);}
#endif
}static void sg_ModelStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
#endif
}static void sg_ModelStep(SimStruct*S){
#ifndef MATLAB_MEX_FILE
char z59441137bf[(0x713+8117-0x268c)];int32_t z161edf608c=(0xd6c+4880-0x207c);const LinWriteInitValues*z4965681e9e=reinterpret_cast<const LinWriteInitValues*>(mxGetPr(zab82456318));ESD_Module*module=reinterpret_cast<ESD_Module*>(sg_module_get_custom_data((int)z4965681e9e->Module,(int)z4965681e9e->Id));NTLIN_RESULT z0e7a5d53db;int z700cd050bf=(int)z4965681e9e->z29d3677448+module->z5b9677fabb();NTLIN_HANDLE za1fc0f0ef5=module->Ports[z700cd050bf]->z59662a1925();if((int32_t)z4965681e9e->dlc>(0x14ec+4009-0x2495)){uint8_t*zedd46d6a35=(uint8_t*)ssGetInputPortSignal(S,(0x8e9+824-0xc21));if(z4965681e9e->z5649cd6678==(0x17f+8303-0x21ed)){uint8_t*z97c6bd869e=(uint8_t*)ssGetInputPortSignal(S,(0x2a0+2138-0xaf9));if(z97c6bd869e[(0x10f9+1221-0x15be)]==(0xa6a+4771-0x1d0c)){z161edf608c=(int32_t)z4965681e9e->dlc;}else{z161edf608c=(0x14c+2093-0x979);}}else{z161edf608c=(int32_t)z4965681e9e->dlc;}if(z161edf608c!=(0xa38+7104-0x25f8)){z0e7a5d53db=linSlaveTxUpdate(za1fc0f0ef5,(int32_t)z4965681e9e->z9fa29891db,z161edf608c,zedd46d6a35);}else{z0e7a5d53db=linSlaveTxUpdate(za1fc0f0ef5,(int32_t)z4965681e9e->z9fa29891db,(0x1c23+976-0x1ff3),NULL);}if(z0e7a5d53db!=NTLIN_SUCCESS){canFormatError(z0e7a5d53db,NTCAN_ERROR_FORMAT_LONG,z59441137bf,sizeof(z59441137bf));SG_PRINTF(DEBUG,"\x54\x58\x3a\x20\x6c\x69\x6e\x53\x6c\x61\x76\x65\x54\x78\x55\x70\x64\x61\x74\x65\x28\x69\x64\x20\x3d\x20\x25\x69\x29\x20\x66\x61\x69\x6c\x65\x64\x20\x77\x69\x74\x68\x20\x65\x72\x72\x6f\x72\x20\x25\x73\x21" "\n",(int)z4965681e9e->z9fa29891db,z59441137bf);}}if((int)z4965681e9e->z89575a706a==z7752b55472){z0e7a5d53db=linMasterTxHeader((NTLIN_HANDLE)za1fc0f0ef5,(uint32_t)z4965681e9e->z9fa29891db);if(z0e7a5d53db!=NTLIN_SUCCESS){canFormatError(z0e7a5d53db,NTCAN_ERROR_FORMAT_LONG,z59441137bf,sizeof(z59441137bf));SG_PRINTF(DEBUG,"\x54\x58\x3a\x20\x6c\x69\x6e\x4d\x61\x73\x74\x65\x72\x54\x78\x48\x65\x61\x64\x65\x72\x28\x69\x64\x20\x3d\x20\x25\x69\x29\x20\x66\x61\x69\x6c\x65\x64\x20\x77\x69\x74\x68\x20\x65\x72\x72\x6f\x72\x20\x25\x73\x21" "\n",(int)z4965681e9e->z9fa29891db,z59441137bf);}}
#endif
}static void sg_ModelStop(SimStruct*S){
#ifndef MATLAB_MEX_FILE
#endif
}
#ifdef MATLAB_MEX_FILE
static void SetSFunctionInputPortProperties(int32_T z7da5ab49fa,uint32_T zbc29571b7b,uint32_T ze97179dd68,boolean_T z5cda1a8b01,boolean_T zbac08145fb,uint8_T z2548e6cd9c,SimStruct*S){if((0x1adc+404-0x1c6f)==z2548e6cd9c){ssSetInputPortWidth(S,z7da5ab49fa,zbc29571b7b);}else if((0x1604+3811-0x24e5)==z2548e6cd9c){ssSetInputPortDataType(S,z7da5ab49fa,ze97179dd68);}else if((0x23ea+790-0x26fd)==z2548e6cd9c){ssSetInputPortRequiredContiguous(S,z7da5ab49fa,z5cda1a8b01);}else if((0x1e55+342-0x1fa7)==z2548e6cd9c){ssSetInputPortDirectFeedThrough(S,z7da5ab49fa,zbac08145fb);}else{ssSetInputPortWidth(S,z7da5ab49fa,zbc29571b7b);ssSetInputPortDataType(S,z7da5ab49fa,ze97179dd68);ssSetInputPortRequiredContiguous(S,z7da5ab49fa,z5cda1a8b01);ssSetInputPortDirectFeedThrough(S,z7da5ab49fa,zbac08145fb);}}static void SetSFunctionOutputPortProperties(int32_T z7da5ab49fa,int32_T zbc29571b7b,uint32_T ze97179dd68,uint8_T z2548e6cd9c,SimStruct*S){if((0x15ed+3466-0x2376)==z2548e6cd9c){ssSetOutputPortWidth(S,z7da5ab49fa,zbc29571b7b);}else if((0xf57+3100-0x1b71)==z2548e6cd9c){ssSetOutputPortDataType(S,z7da5ab49fa,ze97179dd68);}else{ssSetOutputPortWidth(S,z7da5ab49fa,zbc29571b7b);ssSetOutputPortDataType(S,z7da5ab49fa,ze97179dd68);}}
#endif
#include "../common/libsg/sg_sfcn_glue.h"


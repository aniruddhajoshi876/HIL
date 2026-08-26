// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL    (0x1edb+1835-0x2604)
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME     sg_IO601_linmasterwrite_v2_s
#include "sg_callback.h"
#include "include/IO601_sfunc_help.h"
#define zefdd6d55b2 (0x2cf+6057-0x1a71)     
#define z5cfd65b291 (0x10a4+4590-0x2291)  
#define z4ff5168d43 (0x90b+5543-0x1eb2) 
#define zfaa050b79d (uint32_T)mxGetPr(ssGetSFcnParam(S, (0x465+5285-0x190a)))[(0x97f+4146-0x19b1)]        
#define z069b403600 ssGetSFcnParam(S, (0x113+7770-0x1f6c))                           
#define z0c47de6d18 (uint8_T)mxGetPr(ssGetSFcnParam(S, (0x1071+1383-0x15d6)))[(0xa5c+6188-0x2288)]           
#define z40dfd36503 (uint8_T)mxGetPr(ssGetSFcnParam(S, (0x1b1+251-0x2a9)))[(0x584+5589-0x1b59)]           
#define zbff3b0b689 (uint8_T)mxGetPr(ssGetSFcnParam(S, (0x1ceb+534-0x1efd)))[(0x1981+2091-0x21ac)]          
#define z4d36849b0e (boolean_T)mxGetPr(ssGetSFcnParam(S, (0x12f0+1974-0x1aa1)))[(0xa0c+6069-0x21c1)] 
#define zea91db2247 (uint8_T)mxGetPr(ssGetSFcnParam(S, (0x4b3+6598-0x1e73)))[(0x1010+625-0x1281)]       
static char_T zf48d371149[(0xb40+4680-0x1c88)];static void mdlInitializeSizes(SimStruct*S){if((0x1343+1721-0x19fc)==SetAndCheckSFunctionParams((0x1c51+1173-0x20e6),S,zefdd6d55b2)){sprintf(zf48d371149,"\x49\x4f\x36\x30\x31\x20\x4d\x6f\x64\x75\x6c\x65\x49\x44\x20\x25\x69\x3a\x20\x43\x68\x65\x63\x6b\x20\x6c\x69\x73\x74\x20\x6f\x66\x20\x70\x61\x72\x61\x6d\x65\x74\x65\x72\x73\x2c\x20\x25\x69\x20\x70\x61\x72\x61\x6d\x65\x74\x65\x72\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64\x21\x21\x21",zfaa050b79d,zefdd6d55b2);ssSetErrorStatus(S,zf48d371149);return;}CreateSFunctionOutputPorts(z4ff5168d43,S);CreateSFunctionInputPorts(z5cfd65b291,S);if((0x1a40+1618-0x2090)==zbff3b0b689){SetSFunctionInputPortProperties((0x1ceb+1551-0x22fa),z40dfd36503,SS_UINT8,(0xc8d+4307-0x1d5f),(0x53f+4698-0x1798),(0x1de7+484-0x1fcb),S);}else{sprintf(zf48d371149,"\x44\x61\x74\x61\x20\x74\x79\x70\x65\x20\x4c\x49\x4e\x2d\x4d\x65\x73\x73\x61\x67\x65\x20\x63\x75\x72\x72\x65\x6e\x74\x6c\x79\x20\x6e\x6f\x74\x20\x73\x75\x70\x70\x6f\x72\x74\x65\x64");ssSetErrorStatus(S,zf48d371149);return;}ssSetNumRWork(S,z508028c6d3);ssSetNumIWork(S,ze6b81d1e11);ssSetNumPWork(S,za4418501d4);ssSetNumContStates(S,(0xec0+5285-0x2365));ssSetNumDiscStates(S,(0x820+4435-0x1973));ssSetNumSampleTimes(S,(0xc62+5917-0x237e));ssSetNumModes(S,(0x2f6+8998-0x261c));ssSetNumNonsampledZCs(S,(0xec0+2651-0x191b));ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z069b403600)[(0x161+7018-0x1ccb)]==-1.0){ssSetSampleTime(S,(0xf3b+111-0xfaa),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x15a1+4106-0x25ab),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x10+4561-0x11e1),mxGetPr(z069b403600)[(0x511+5292-0x19bd)]);ssSetOffsetTime(S,(0xb5d+158-0xbfb),0.0);}}static void sg_ModelLoad(SimStruct*){}static void sg_ModelStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
sg_IO601_Module_T*sg_IO601_pModule=zca5e8f4677(zfaa050b79d);if(!sg_IO601_pModule||!sg_IO601_pModule->z8920b096dd){sprintf(zf48d371149,"\x25\x73\x20\x49\x44\x25\x69\x20\x44\x72\x69\x76\x65\x72\x20\x77\x61\x73\x20\x6e\x6f\x74\x20\x69\x6e\x69\x74\x69\x61\x6c\x69\x7a\x65\x64\x20\x63\x6f\x72\x72\x65\x63\x74\x6c\x79\x2e",DEVNAME,zfaa050b79d);ze78d5288c1();ssSetErrorStatus(S,zf48d371149);return;}if(!sg_IO601_pModule->LIN.z578fb42053.ze232fe4686){sprintf(zf48d371149,"\x25\x73\x20\x49\x44\x25\x69\x20\x4c\x49\x4e\x20\x43\x68\x61\x6e\x6e\x65\x6c\x20\x77\x61\x73\x20\x6e\x6f\x74\x20\x69\x6e\x69\x74\x69\x61\x6c\x69\x7a\x65\x64\x20\x63\x6f\x72\x72\x65\x63\x74\x6c\x79\x2e",DEVNAME,zfaa050b79d);ze78d5288c1();ssSetErrorStatus(S,zf48d371149);return;}int*idx=z5f74c0daa0<int>(zfaa050b79d,z0f1c32f54d::z8a9abfb9ab,(size_t)S);if(!z8f423b706f(sg_IO601_pModule,true,true,z0c47de6d18,idx,zf48d371149)){ssSetErrorStatus(S,zf48d371149);return;}
#endif
}static void sg_ModelStep(SimStruct*S){
#ifndef MATLAB_MEX_FILE
sg_IO601_Module_T*sg_IO601_pModule=zca5e8f4677(zfaa050b79d);if(!sg_IO601_pModule||!sg_IO601_pModule->z8920b096dd){sprintf(zf48d371149,"\x25\x73\x20\x49\x44\x25\x69\x20\x44\x72\x69\x76\x65\x72\x20\x77\x61\x73\x20\x6e\x6f\x74\x20\x69\x6e\x69\x74\x69\x61\x6c\x69\x7a\x65\x64\x20\x63\x6f\x72\x72\x65\x63\x74\x6c\x79\x2e",DEVNAME,zfaa050b79d);ze78d5288c1();ssSetErrorStatus(S,zf48d371149);return;}int*idx=z5f74c0daa0<int>(zfaa050b79d,z0f1c32f54d::z8a9abfb9ab,(size_t)S);z9c620282bd msg={(0x910+1542-0xf16)};msg.ProtID=z0c47de6d18;msg.zfb67aef112=z4d36849b0e;msg.DLC=z40dfd36503;msg.zc28ec0870c=(0xe33+6307-0x26d5);memcpy(msg.Data,(void*)ssGetInputPortSignal(S,(0x1b2c+2508-0x24f8)),z40dfd36503);zd51062ac81(sg_IO601_pModule,(0xb8d+2662-0x15f1),*idx,(void*)&msg);z53bb41ed20(sg_IO601_pModule);
#endif
}static void sg_ModelStop(SimStruct*S){
#ifndef MATLAB_MEX_FILE
z59757a9fb2<int>(zfaa050b79d,z0f1c32f54d::z8a9abfb9ab,(size_t)S);
#endif 
}static void za9f8aa9e36(SimStruct*S){}
#include "../common/libsg/sg_sfcn_glue.h"


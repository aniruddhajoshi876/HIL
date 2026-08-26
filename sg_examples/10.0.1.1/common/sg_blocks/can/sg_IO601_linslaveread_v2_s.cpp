// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL    (0x1025+5854-0x2701)
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME     sg_IO601_linslaveread_v2_s
#include "sg_callback.h"
#include "include/IO601_sfunc_help.h"
#define zefdd6d55b2 (0xdc5+1855-0x14fb)     
#define z5cfd65b291 (0x1748+3905-0x2689)  
#define z4ff5168d43 (0x59+9723-0x2654) 
#define zfaa050b79d (uint32_T)mxGetPr(ssGetSFcnParam(S, (0x6f4+3949-0x1661)))[(0xf50+1274-0x144a)]        
#define z069b403600 ssGetSFcnParam(S, (0x5b+9619-0x25ed))                           
#define z0c47de6d18 (uint8_T)mxGetPr(ssGetSFcnParam(S, (0x8b5+540-0xacf)))[(0x540+3534-0x130e)]           
#define z40dfd36503 (uint8_T)mxGetPr(ssGetSFcnParam(S, (0xab6+4469-0x1c28)))[(0x319+7737-0x2152)]               
#define z3bbb46552b (boolean_T)mxGetPr(ssGetSFcnParam(S, (0xcb2+4525-0x1e5b)))[(0x1bbd+261-0x1cc2)]   
#define zac71d27b93 (boolean_T)mxGetPr(ssGetSFcnParam(S, (0x46b+4174-0x14b4)))[(0x75c+6374-0x2042)]        
#define zbff3b0b689 (uint8_T)mxGetPr(ssGetSFcnParam(S, (0x1c7+3852-0x10cd)))[(0x1045+3129-0x1c7e)]          
#define z4d36849b0e (boolean_T)mxGetPr(ssGetSFcnParam(S, (0xb04+6874-0x25d7)))[(0x808+1165-0xc95)] 
#define zea91db2247 (uint8_T)mxGetPr(ssGetSFcnParam(S, (0xac+2515-0xa77)))[(0xf9a+2286-0x1888)]       
static char_T zf48d371149[(0x90f+2628-0x1253)];static void mdlInitializeSizes(SimStruct*S){uint8_T zb4b90c3f49=(0xbb1+522-0xdba);if((0xa0b+5715-0x205e)==SetAndCheckSFunctionParams((0x487+4269-0x1534),S,zefdd6d55b2)){sprintf(zf48d371149,"\x43\x68\x65\x63\x6b\x20\x6c\x69\x73\x74\x20\x6f\x66\x20\x70\x61\x72\x61\x6d\x65\x74\x65\x72\x73\x2c\x20\x25\x69\x20\x70\x61\x72\x61\x6d\x65\x74\x65\x72\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64\x21\x21\x21",zefdd6d55b2);ssSetErrorStatus(S,zf48d371149);return;}CreateSFunctionInputPorts(z5cfd65b291,S);zb4b90c3f49+=(z3bbb46552b)?(0x72+9554-0x25c3):(0x504+3852-0x1410);zb4b90c3f49+=(zac71d27b93)?(0x805+5566-0x1dc2):(0xf6b+2437-0x18f0);CreateSFunctionOutputPorts(zb4b90c3f49,S);zb4b90c3f49=(0x322+3479-0x10b9);if(z3bbb46552b){SetSFunctionOutputPortProperties(zb4b90c3f49++,(0x497+1448-0xa3e),SS_INT32,(0x1f0c+458-0x20d6),S);}if(zac71d27b93){SetSFunctionOutputPortProperties(zb4b90c3f49++,(0x1c22+941-0x1fce),SS_UINT32,(0x1cfb+2487-0x26b2),S);}SetSFunctionOutputPortProperties(zb4b90c3f49,z40dfd36503,SS_UINT8,(0x488+7372-0x2154),S);ssSetNumRWork(S,z508028c6d3);ssSetNumIWork(S,ze6b81d1e11);ssSetNumPWork(S,za4418501d4);ssSetNumContStates(S,(0x4b3+863-0x812));ssSetNumDiscStates(S,(0x20e1+478-0x22bf));ssSetNumSampleTimes(S,(0x23b+411-0x3d5));ssSetNumModes(S,(0x617+2269-0xef4));ssSetNumNonsampledZCs(S,(0xbe3+3095-0x17fa));ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z069b403600)[(0x1197+4878-0x24a5)]==-1.0){ssSetSampleTime(S,(0x13c1+4017-0x2372),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x372+2694-0xdf8),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x311+8422-0x23f7),mxGetPr(z069b403600)[(0x47d+8023-0x23d4)]);ssSetOffsetTime(S,(0xe80+3987-0x1e13),0.0);}}static void sg_ModelLoad(SimStruct*){}static void sg_ModelStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
sg_IO601_Module_T*sg_IO601_pModule=zca5e8f4677(zfaa050b79d);if(!sg_IO601_pModule||!sg_IO601_pModule->z8920b096dd){sprintf(zf48d371149,"\x25\x73\x20\x49\x44\x25\x69\x20\x44\x72\x69\x76\x65\x72\x20\x77\x61\x73\x20\x6e\x6f\x74\x20\x69\x6e\x69\x74\x69\x61\x6c\x69\x7a\x65\x64\x20\x63\x6f\x72\x72\x65\x63\x74\x6c\x79\x2e",DEVNAME,zfaa050b79d);ze78d5288c1();ssSetErrorStatus(S,zf48d371149);return;}if(!sg_IO601_pModule->LIN.z578fb42053.ze232fe4686){sprintf(zf48d371149,"\x25\x73\x20\x49\x44\x25\x69\x20\x4c\x49\x4e\x20\x43\x68\x61\x6e\x6e\x65\x6c\x20\x77\x61\x73\x20\x6e\x6f\x74\x20\x69\x6e\x69\x74\x69\x61\x6c\x69\x7a\x65\x64\x20\x63\x6f\x72\x72\x65\x63\x74\x6c\x79\x2e",DEVNAME,zfaa050b79d);ze78d5288c1();ssSetErrorStatus(S,zf48d371149);return;}int*idx=z5f74c0daa0<int>(zfaa050b79d,z0f1c32f54d::z5f2bb645a9,(size_t)S,false);if(!z8f423b706f(sg_IO601_pModule,false,false,z0c47de6d18,idx,zf48d371149)){ssSetErrorStatus(S,zf48d371149);return;}
#endif
}static void sg_ModelStep(SimStruct*S){
#ifndef MATLAB_MEX_FILE
sg_IO601_Module_T*sg_IO601_pModule=zca5e8f4677(zfaa050b79d);if(!sg_IO601_pModule||!sg_IO601_pModule->z8920b096dd){sprintf(zf48d371149,"\x25\x73\x20\x49\x44\x25\x69\x20\x44\x72\x69\x76\x65\x72\x20\x77\x61\x73\x20\x6e\x6f\x74\x20\x69\x6e\x69\x74\x69\x61\x6c\x69\x7a\x65\x64\x20\x63\x6f\x72\x72\x65\x63\x74\x6c\x79\x2e",DEVNAME,zfaa050b79d);ze78d5288c1();ssSetErrorStatus(S,zf48d371149);return;}uint8_T zee7c235605=(0x900+2731-0x13ab);int32_T z7f91b0f862=(0x183a+274-0x194c);uint32_T timeStamp=(0x2f9+3120-0xf29);uint8_T data[(0x49c+8011-0x23df)]={(0x12+2645-0xa67)};zc524d0bc63(sg_IO601_pModule,(0x783+3494-0x1527),ssGetTaskTime(S,(0x1a2a+3088-0x263a)));zcfcd07fc0a(sg_IO601_pModule,(0x460+2414-0xdcc),z0c47de6d18,&z7f91b0f862,&timeStamp,data);SG_PRINTF(DEBUG,"\x75\x70\x64\x61\x74\x65\x53\x74\x61\x74\x65\x20\x25\x69\x2c\x20\x64\x61\x74\x61\x5b\x37\x5d\x20\x25\x64" "\n",z7f91b0f862,data[(0x1746+3059-0x2332)]);if(z3bbb46552b)*(int32_T*)ssGetOutputPortSignal(S,zee7c235605++)=z7f91b0f862;if(zac71d27b93){if((0x1c6f+1452-0x221a)==z7f91b0f862)*(uint32_T*)ssGetOutputPortSignal(S,zee7c235605)=timeStamp;zee7c235605++;}if((0x2a+490-0x213)==z7f91b0f862)memcpy((void*)ssGetOutputPortSignal(S,zee7c235605),data,z40dfd36503);
#endif
}static void sg_ModelStop(SimStruct*S){
#ifndef MATLAB_MEX_FILE
z59757a9fb2<int>(zfaa050b79d,z0f1c32f54d::z5f2bb645a9,(size_t)S);
#endif 
}static void za9f8aa9e36(SimStruct*S){}
#include "../common/libsg/sg_sfcn_glue.h"


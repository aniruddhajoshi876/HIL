// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL    (0x646+4017-0x15f5)
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME     sg_IO601_linslavewrite_v2_s
#include "sg_callback.h"
#include "include/IO601_sfunc_help.h"
#define zefdd6d55b2 (0x1da4+1483-0x2367)     
#define z5cfd65b291 (0xcbd+2782-0x179a)  
#define z4ff5168d43 (0x638+4012-0x15e4) 
#define zfaa050b79d (uint32_T)mxGetPr(ssGetSFcnParam(S, (0x657+5757-0x1cd4)))[(0x1378+3688-0x21e0)]        
#define z069b403600 ssGetSFcnParam(S, (0x1ca2+677-0x1f46))                           
#define z0c47de6d18 (uint8_T)mxGetPr(ssGetSFcnParam(S, (0x2b0+4659-0x14e1)))[(0xb30+1891-0x1293)]           
#define z40dfd36503 (uint8_T)mxGetPr(ssGetSFcnParam(S, (0xf17+117-0xf89)))[(0x1140+1028-0x1544)]           
#define zf8c98de94c ssGetSFcnParam(S, (0x11aa+2618-0x1be0))                          
#define zbff3b0b689 (uint8_T)mxGetPr(ssGetSFcnParam(S, (0x1721+1801-0x1e25)))[(0x292+424-0x43a)]          
#define z4d36849b0e (boolean_T)mxGetPr(ssGetSFcnParam(S, (0x1737+884-0x1aa5)))[(0x1e0d+971-0x21d8)] 
#define zea91db2247 (uint8_T)mxGetPr(ssGetSFcnParam(S, (0x10bd+3287-0x1d8d)))[(0xcd+1205-0x582)]       
static char_T zf48d371149[(0x2160+768-0x2360)];static void mdlInitializeSizes(SimStruct*S){if((0x40c+7209-0x2035)==SetAndCheckSFunctionParams((0xbf9+156-0xc95),S,zefdd6d55b2)){sprintf(zf48d371149,"\x43\x68\x65\x63\x6b\x20\x6c\x69\x73\x74\x20\x6f\x66\x20\x70\x61\x72\x61\x6d\x65\x74\x65\x72\x73\x2c\x20\x25\x69\x20\x70\x61\x72\x61\x6d\x65\x74\x65\x72\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64\x21\x21\x21",zefdd6d55b2);ssSetErrorStatus(S,zf48d371149);return;}CreateSFunctionOutputPorts(z4ff5168d43,S);CreateSFunctionInputPorts(z5cfd65b291,S);if((0xf60+3659-0x1da9)==zbff3b0b689){SetSFunctionInputPortProperties((0x175b+120-0x17d3),z40dfd36503,SS_UINT8,(0x450+5794-0x1af1),(0x12ad+1223-0x1773),(0x357+2698-0xde1),S);}else{sprintf(zf48d371149,"\x44\x61\x74\x61\x20\x74\x79\x70\x65\x20\x4c\x49\x4e\x2d\x4d\x65\x73\x73\x61\x67\x65\x20\x63\x75\x72\x72\x65\x6e\x74\x6c\x79\x20\x6e\x6f\x74\x20\x73\x75\x70\x70\x6f\x72\x74\x65\x64");ssSetErrorStatus(S,zf48d371149);return;}ssSetNumRWork(S,z508028c6d3);ssSetNumIWork(S,ze6b81d1e11);ssSetNumPWork(S,za4418501d4);ssSetNumContStates(S,(0x7f4+2937-0x136d));ssSetNumDiscStates(S,(0x2c1+9039-0x2610));ssSetNumSampleTimes(S,(0x1801+3238-0x24a6));ssSetNumModes(S,(0x29+500-0x21d));ssSetNumNonsampledZCs(S,(0x18b9+410-0x1a53));ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z069b403600)[(0x828+1784-0xf20)]==-1.0){ssSetSampleTime(S,(0xd64+6274-0x25e6),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x26c+7455-0x1f8b),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x1f79+957-0x2336),mxGetPr(z069b403600)[(0xb0f+3842-0x1a11)]);ssSetOffsetTime(S,(0x178c+520-0x1994),0.0);}}static void sg_ModelLoad(SimStruct*){}static void sg_ModelStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
sg_IO601_Module_T*sg_IO601_pModule=zca5e8f4677(zfaa050b79d);if(!sg_IO601_pModule||!sg_IO601_pModule->z8920b096dd){sprintf(zf48d371149,"\x25\x73\x20\x49\x44\x25\x69\x20\x44\x72\x69\x76\x65\x72\x20\x77\x61\x73\x20\x6e\x6f\x74\x20\x69\x6e\x69\x74\x69\x61\x6c\x69\x7a\x65\x64\x20\x63\x6f\x72\x72\x65\x63\x74\x6c\x79\x2e",DEVNAME,zfaa050b79d);ze78d5288c1();ssSetErrorStatus(S,zf48d371149);return;}if(!sg_IO601_pModule->LIN.z578fb42053.ze232fe4686){sprintf(zf48d371149,"\x25\x73\x20\x49\x44\x25\x69\x20\x4c\x49\x4e\x20\x43\x68\x61\x6e\x6e\x65\x6c\x20\x77\x61\x73\x20\x6e\x6f\x74\x20\x69\x6e\x69\x74\x69\x61\x6c\x69\x7a\x65\x64\x20\x63\x6f\x72\x72\x65\x63\x74\x6c\x79\x2e",DEVNAME,zfaa050b79d);ze78d5288c1();ssSetErrorStatus(S,zf48d371149);return;}int*idx=z5f74c0daa0<int>(zfaa050b79d,z0f1c32f54d::z8a9abfb9ab,(size_t)S);if(!z8f423b706f(sg_IO601_pModule,true,false,z0c47de6d18,idx,zf48d371149)){ssSetErrorStatus(S,zf48d371149);return;}
#endif
}static void sg_ModelStep(SimStruct*S){
#ifndef MATLAB_MEX_FILE
sg_IO601_Module_T*sg_IO601_pModule=zca5e8f4677(zfaa050b79d);if(!sg_IO601_pModule||!sg_IO601_pModule->z8920b096dd){sprintf(zf48d371149,"\x25\x73\x20\x49\x44\x25\x69\x20\x44\x72\x69\x76\x65\x72\x20\x77\x61\x73\x20\x6e\x6f\x74\x20\x69\x6e\x69\x74\x69\x61\x6c\x69\x7a\x65\x64\x20\x63\x6f\x72\x72\x65\x63\x74\x6c\x79\x2e",DEVNAME,zfaa050b79d);ze78d5288c1();ssSetErrorStatus(S,zf48d371149);return;}int*idx=z5f74c0daa0<int>(zfaa050b79d,z0f1c32f54d::z8a9abfb9ab,(size_t)S);z9c620282bd msg={(0xe5+3095-0xcfc)};msg.ProtID=z0c47de6d18;msg.zfb67aef112=z4d36849b0e;msg.DLC=z40dfd36503;msg.zc28ec0870c=(0x12c7+3369-0x1fef);memcpy(msg.Data,(void*)ssGetInputPortSignal(S,(0x150d+2009-0x1ce6)),z40dfd36503);zd51062ac81(sg_IO601_pModule,(0x1b63+820-0x1e95),*idx,(void*)&msg);z53bb41ed20(sg_IO601_pModule);
#endif
}static void sg_ModelStop(SimStruct*S){
#ifndef MATLAB_MEX_FILE
z59757a9fb2<int>(zfaa050b79d,z0f1c32f54d::z8a9abfb9ab,(size_t)S);
#endif 
}static void za9f8aa9e36(SimStruct*S){}
#include "../common/libsg/sg_sfcn_glue.h"


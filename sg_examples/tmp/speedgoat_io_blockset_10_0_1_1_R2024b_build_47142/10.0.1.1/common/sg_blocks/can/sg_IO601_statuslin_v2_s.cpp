// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL    (0xc9d+5189-0x20e0)
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME     sg_IO601_statuslin_v2_s
#include "sg_callback.h"
#include "include/IO601_sfunc_help.h"
#define zefdd6d55b2 (0xfd+1128-0x55f)     
#define z5cfd65b291 (0x13a9+2061-0x1bb6)  
#define z4ff5168d43 (0xd74+1974-0x152a) 
#define zfaa050b79d (uint32_T)mxGetPr(ssGetSFcnParam(S, (0x375+1872-0xac5)))[(0x14a9+2479-0x1e58)]       
#define z069b403600 ssGetSFcnParam(S, (0x657+3354-0x1370))                       
#define z09b001dd00 (boolean_T)mxGetPr(ssGetSFcnParam(S, (0x207f+887-0x23f4)))[(0x3b7+543-0x5d6)]    
#define z15cc5ad301 (boolean_T)mxGetPr(ssGetSFcnParam(S, (0x25cd+127-0x2649)))[(0x2d0+7337-0x1f79)] 
#define ze994c420e8 (boolean_T)mxGetPr(ssGetSFcnParam(S, (0x44f+7602-0x21fd)))[(0x1467+4019-0x241a)] 
#define zc5f932c264 (boolean_T)mxGetPr(ssGetSFcnParam(S, (0x1366+3702-0x21d7)))[(0xd13+1839-0x1442)]  
static char_T zf48d371149[(0xf2f+6332-0x26eb)];static void mdlInitializeSizes(SimStruct*S){uint8_T zda6d87f1d2=(0x397+2594-0xdb9);if((0x154d+2069-0x1d62)==SetAndCheckSFunctionParams((0x13e4+687-0x1693),S,zefdd6d55b2)){sprintf(zf48d371149,"\x43\x68\x65\x63\x6b\x20\x6c\x69\x73\x74\x20\x6f\x66\x20\x70\x61\x72\x61\x6d\x65\x74\x65\x72\x73\x2c\x20\x25\x69\x20\x70\x61\x72\x61\x6d\x65\x74\x65\x72\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64\x21\x21\x21",zefdd6d55b2);ssSetErrorStatus(S,zf48d371149);return;}CreateSFunctionInputPorts(z5cfd65b291,S);zda6d87f1d2+=(z09b001dd00)?(0x6b1+5833-0x1d79):(0x298+3230-0xf36);zda6d87f1d2+=(z15cc5ad301)?(0xc9c+1868-0x13e7):(0x311+4009-0x12ba);zda6d87f1d2+=(ze994c420e8)?(0x162b+2062-0x1e38):(0xac+7186-0x1cbe);zda6d87f1d2+=(zc5f932c264)?(0x501+4173-0x154d):(0xf4b+2489-0x1904);CreateSFunctionOutputPorts(zda6d87f1d2,S);zda6d87f1d2=(0x1264+958-0x1622);if(z09b001dd00){SetSFunctionOutputPortProperties(zda6d87f1d2,(0xfcb+2402-0x192c),SS_UINT32,(0x68a+5338-0x1b64),S);zda6d87f1d2+=(0x14f5+1533-0x1af1);}if(z15cc5ad301){SetSFunctionOutputPortProperties(zda6d87f1d2,(0xaf7+3686-0x195c),SS_UINT32,(0xa82+5530-0x201c),S);zda6d87f1d2+=(0xc62+6248-0x24c9);}if(ze994c420e8){SetSFunctionOutputPortProperties(zda6d87f1d2,(0x548+7732-0x237b),SS_UINT32,(0x4f4+6962-0x2026),S);zda6d87f1d2+=(0xd61+3369-0x1a89);}if(zc5f932c264){SetSFunctionOutputPortProperties(zda6d87f1d2,(0x29+9818-0x2682),SS_UINT32,(0x121b+3930-0x2175),S);}ssSetNumRWork(S,z508028c6d3);ssSetNumIWork(S,ze6b81d1e11);ssSetNumPWork(S,za4418501d4);ssSetNumContStates(S,(0x3c7+2005-0xb9c));ssSetNumDiscStates(S,(0xa9+9423-0x2578));ssSetNumSampleTimes(S,(0xc89+3741-0x1b25));ssSetNumModes(S,(0x11d2+4293-0x2297));ssSetNumNonsampledZCs(S,(0x12aa+1007-0x1699));ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z069b403600)[(0x9ff+4566-0x1bd5)]==-1.0){ssSetSampleTime(S,(0x391+1977-0xb4a),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x68+256-0x168),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x1a9+3325-0xea6),mxGetPr(z069b403600)[(0x972+5460-0x1ec6)]);ssSetOffsetTime(S,(0x1a70+1160-0x1ef8),0.0);}}static void sg_ModelLoad(SimStruct*){}static void sg_ModelStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
sg_IO601_Module_T*sg_IO601_pModule=zca5e8f4677(zfaa050b79d);if(!sg_IO601_pModule||!sg_IO601_pModule->z8920b096dd){sprintf(zf48d371149,"\x25\x73\x20\x49\x44\x25\x69\x20\x44\x72\x69\x76\x65\x72\x20\x77\x61\x73\x20\x6e\x6f\x74\x20\x69\x6e\x69\x74\x69\x61\x6c\x69\x7a\x65\x64\x20\x63\x6f\x72\x72\x65\x63\x74\x6c\x79\x2e",DEVNAME,zfaa050b79d);ze78d5288c1();ssSetErrorStatus(S,zf48d371149);return;}if(!sg_IO601_pModule->LIN.z578fb42053.ze232fe4686){sprintf(zf48d371149,"\x25\x73\x20\x49\x44\x25\x69\x20\x4c\x49\x4e\x20\x43\x68\x61\x6e\x6e\x65\x6c\x20\x77\x61\x73\x20\x6e\x6f\x74\x20\x69\x6e\x69\x74\x69\x61\x6c\x69\x7a\x65\x64\x20\x63\x6f\x72\x72\x65\x63\x74\x6c\x79\x2e",DEVNAME,zfaa050b79d);ze78d5288c1();ssSetErrorStatus(S,zf48d371149);return;}(void)z5f74c0daa0<bool>(zfaa050b79d,z0f1c32f54d::z58a51650cb,(size_t)S,false);
#endif
}static void sg_ModelStep(SimStruct*S){
#ifndef MATLAB_MEX_FILE
sg_IO601_Module_T*sg_IO601_pModule=zca5e8f4677(zfaa050b79d);if(!sg_IO601_pModule||!sg_IO601_pModule->z8920b096dd){sprintf(zf48d371149,"\x25\x73\x20\x49\x44\x25\x69\x20\x44\x72\x69\x76\x65\x72\x20\x77\x61\x73\x20\x6e\x6f\x74\x20\x69\x6e\x69\x74\x69\x61\x6c\x69\x7a\x65\x64\x20\x63\x6f\x72\x72\x65\x63\x74\x6c\x79\x2e",DEVNAME,zfaa050b79d);ze78d5288c1();ssSetErrorStatus(S,zf48d371149);return;}if(zec82ccf254(sg_IO601_pModule,true)){uint8_T zda6d87f1d2=(0x129+6685-0x1b46);if(z09b001dd00){z25d5abac79(sg_IO601_pModule,(uint32_T*)ssGetOutputPortSignal(S,zda6d87f1d2));zda6d87f1d2+=(0xe30+3162-0x1a89);}if(z15cc5ad301){z2783a38d68(sg_IO601_pModule,(uint32_T*)ssGetOutputPortSignal(S,zda6d87f1d2));zda6d87f1d2+=(0x1813+3579-0x260d);}if(ze994c420e8){z6a316799fa(sg_IO601_pModule,(uint32_T*)ssGetOutputPortSignal(S,zda6d87f1d2));zda6d87f1d2+=(0x76d+854-0xac2);}if(zc5f932c264){zfd82ef2641(sg_IO601_pModule,(uint32_T*)ssGetOutputPortSignal(S,zda6d87f1d2));}zec82ccf254(sg_IO601_pModule,false);}
#endif
}static void sg_ModelStop(SimStruct*S){
#ifndef MATLAB_MEX_FILE
z59757a9fb2<bool>(zfaa050b79d,z0f1c32f54d::z58a51650cb,(size_t)S);
#endif 
}static void za9f8aa9e36(SimStruct*S){}
#include "../common/libsg/sg_sfcn_glue.h"


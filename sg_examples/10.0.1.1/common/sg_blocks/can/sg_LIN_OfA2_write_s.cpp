// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL    (0x1187+4639-0x23a4)
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME     sg_LIN_OfA2_write_s
#include "simstruc.h"
#ifndef MATLAB_MEX_FILE
#include "../common/libsg/sg_common.h"
#else
#include "mex.h"
#endif
#include "../common/libsg/sg_callback.h"
#include "../common/libsg/sg_printf.h"
#include "include/LIN_Message_Definition.h"
#include "include/OfA2_SFunctionInterface.h"
#define zefdd6d55b2 (0xbc1+3617-0x19e0)         
#define z5cfd65b291 (0xa22+371-0xb95)      
#define z4ff5168d43 (0x206+7981-0x2133)     
#define zab82456318 ssGetSFcnParam(S, (0x8ff+3550-0x16dd))
#define z44bda6b2bf ssGetSFcnParam(S, (0x1407+4338-0x24f8))
static char_T ze03e9e0a0d[(0x412+9169-0x26e3)];static int SetAndCheckSFunctionParams(uint8_T ze58e331f42,SimStruct*S);static void CreateSFunctionInputPorts(int32_T zcf9aed83ba,SimStruct*S);static void SetSFunctionInputPortProperties(int32_T z7da5ab49fa,uint32_T zbc29571b7b,uint32_T ze97179dd68,boolean_T z5cda1a8b01,boolean_T zbac08145fb,uint8_T z2548e6cd9c,SimStruct*S);static void CreateSFunctionOutputPorts(int32_T z7f34f9d205,SimStruct*S);static void mdlInitializeSizes(SimStruct*S){
#ifdef MATLAB_MEX_FILE
const sg::ofa::LinWriteInitValues*z5df65ca785=reinterpret_cast<const sg::ofa::LinWriteInitValues*>(mxGetPr(zab82456318));bool inputEnableResponse=static_cast<bool>(z5df65ca785->inputEnableResponse);uint8_t messageType=static_cast<uint8_t>(z5df65ca785->Channel.messageType);uint32_t dlc=static_cast<uint32_t>(z5df65ca785->dlc);int_T status=(0xde5+6087-0x25ac);DTypeId zb1d627659d=(0x742+2665-0x11ab);zb1d627659d=ssRegisterDataType(S,"\x4c\x49\x4e\x5f\x4d\x45\x53\x53\x41\x47\x45");if(INVALID_DTYPE_ID==zb1d627659d){return;}status=ssSetDataTypeSize(S,zb1d627659d,sizeof(LINMsg));if((0x15ec+2786-0x20ce)==status){return;}
#endif 
if((0x5ba+4139-0x15e5)==SetAndCheckSFunctionParams((0x7d+2243-0x940),S)){sprintf(ze03e9e0a0d,"\x43\x68\x65\x63\x6b\x20\x6c\x69\x73\x74\x20\x6f\x66\x20\x70\x61\x72\x61\x6d\x65\x74\x65\x72\x73\x2c\x20\x25\x69\x20\x70\x61\x72\x61\x6d\x65\x74\x65\x72\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64\x21\x21\x21",zefdd6d55b2);ssSetErrorStatus(S,ze03e9e0a0d);return;}
#ifdef MATLAB_MEX_FILE
CreateSFunctionOutputPorts(z4ff5168d43,S);int z09f59c7290=(0x137f+4407-0x24b5);if(inputEnableResponse)z09f59c7290++;CreateSFunctionInputPorts(z09f59c7290,S);if((0xac6+783-0xdd4)==messageType){sprintf(ze03e9e0a0d,"\x4d\x65\x73\x73\x61\x67\x65\x20\x74\x79\x70\x65\x20\x27\x4c\x49\x4e\x27\x20\x69\x73\x20\x6e\x6f\x74\x20\x73\x75\x70\x70\x6f\x72\x74\x65\x64\x20\x79\x65\x74\x21\x21\x21");ssSetErrorStatus(S,ze03e9e0a0d);return;}else{SetSFunctionInputPortProperties((0x61+7821-0x1eee),dlc,SS_UINT8,(0x527+4116-0x153a),(0x1d9+2867-0xd0b),(0x26f+1103-0x6be),S);if(inputEnableResponse)SetSFunctionInputPortProperties((0xc13+6109-0x23ef),(0x819+789-0xb2d),SS_UINT8,(0x74b+3828-0x163e),(0x135c+1128-0x17c3),(0x1a4+1739-0x86f),S);}
#endif 
ssSetNumRWork(S,(0x124+3561-0xf0d));ssSetNumIWork(S,(0x62b+6191-0x1e5a));ssSetNumPWork(S,(0x2e2+8554-0x244c));ssSetNumContStates(S,(0xb2c+4423-0x1c73));ssSetNumDiscStates(S,(0x115b+21-0x1170));ssSetNumSampleTimes(S,(0x4e2+6400-0x1de1));ssSetNumModes(S,(0x5f7+5810-0x1ca9));ssSetNumNonsampledZCs(S,(0x1455+1627-0x1ab0));ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static int SetAndCheckSFunctionParams(uint8_T ze58e331f42,SimStruct*S){int i=(0x7ff+7917-0x26ec);ssSetNumSFcnParams(S,zefdd6d55b2);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){return(0x1f64+1471-0x2523);}for(i=(0xa04+336-0xb54);i<zefdd6d55b2;i++){ssSetSFcnParamTunable(S,i,ze58e331f42);}return(0x130c+2682-0x1d85);}static void CreateSFunctionInputPorts(int32_T zcf9aed83ba,SimStruct*S){if((0x360+3071-0xf5f)==zcf9aed83ba){ssSetNumInputPorts(S,z5cfd65b291);}else{ssSetNumInputPorts(S,zcf9aed83ba);}}static void CreateSFunctionOutputPorts(int32_T z7f34f9d205,SimStruct*S){if((0x1023+944-0x13d3)==z7f34f9d205){ssSetNumOutputPorts(S,z4ff5168d43);}else{ssSetNumOutputPorts(S,z7f34f9d205);}}static void SetSFunctionInputPortProperties(int32_T z7da5ab49fa,uint32_T zbc29571b7b,uint32_T ze97179dd68,boolean_T z5cda1a8b01,boolean_T zbac08145fb,uint8_T z2548e6cd9c,SimStruct*S){if((0xae4+4948-0x1e37)==z2548e6cd9c){ssSetInputPortWidth(S,z7da5ab49fa,zbc29571b7b);}else if((0x111c+144-0x11aa)==z2548e6cd9c){ssSetInputPortDataType(S,z7da5ab49fa,ze97179dd68);}else if((0x2075+1471-0x2631)==z2548e6cd9c){ssSetInputPortRequiredContiguous(S,z7da5ab49fa,z5cda1a8b01);}else if((0x16ab+497-0x1898)==z2548e6cd9c){ssSetInputPortDirectFeedThrough(S,z7da5ab49fa,zbac08145fb);}else{ssSetInputPortWidth(S,z7da5ab49fa,zbc29571b7b);ssSetInputPortDataType(S,z7da5ab49fa,ze97179dd68);ssSetInputPortRequiredContiguous(S,z7da5ab49fa,z5cda1a8b01);ssSetInputPortDirectFeedThrough(S,z7da5ab49fa,zbac08145fb);}}static void mdlInitializeSampleTimes(SimStruct*S){const double*zbe8c45f9f4=mxGetPr(zab82456318);if(zbe8c45f9f4[(0x1c80+943-0x202d)]==-1.0){ssSetSampleTime(S,(0x21ad+287-0x22cc),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x414+902-0x79a),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0xaea+6273-0x236b),zbe8c45f9f4[(0xb0d+6386-0x23fd)]);ssSetOffsetTime(S,(0xdc7+4270-0x1e75),0.0);}}static void sg_ModelLoad(SimStruct*S){}static void sg_ModelStart(SimStruct*S){const sg::ofa::LinWriteInitValues*z5df65ca785=reinterpret_cast<const sg::ofa::LinWriteInitValues*>(mxGetPr(zab82456318));uint8_t isSlv=static_cast<uint8_t>(z5df65ca785->Channel.isSlv);
#ifndef MATLAB_MEX_FILE
sg::ofa::Lin_Write_Start(*z5df65ca785,reinterpret_cast<size_t>(S));
#endif
}static void sg_ModelStep(SimStruct*S){
#ifndef MATLAB_MEX_FILE
const sg::ofa::LinWriteInitValues*z5df65ca785=reinterpret_cast<const sg::ofa::LinWriteInitValues*>(mxGetPr(zab82456318));uint8_t protIdent=static_cast<uint8_t>(z5df65ca785->protIdent);uint8_t isEnhcdChksum=static_cast<uint8_t>(z5df65ca785->isEnhcdChksum);uint8_t dlc=static_cast<uint8_t>(z5df65ca785->dlc);uint8_t inputEnableResponse=static_cast<uint8_t>(z5df65ca785->inputEnableResponse);LINMsg2 m={(0xd1a+5618-0x230c)};m.msg.ProtID=protIdent;m.msg.EnhcdCksm=isEnhcdChksum;m.msg.Len=dlc;m.msg.IDOnly=(0x8d4+993-0xcb5);if(inputEnableResponse)m.senderOfResponse=*(uint8_T*)ssGetInputPortSignal(S,(0xbb4+4388-0x1cd7));else m.senderOfResponse=(0xf3a+4899-0x225c);memcpy(m.msg.Data,(void*)ssGetInputPortSignal(S,(0x3f2+4192-0x1452)),dlc);(void)sg::ofa::Lin_Write_Step(*z5df65ca785,(void*)&m,reinterpret_cast<size_t>(S));
#endif
}static void sg_ModelStop(SimStruct*S){
#ifndef MATLAB_MEX_FILE
const sg::ofa::LinWriteInitValues*z5df65ca785=reinterpret_cast<const sg::ofa::LinWriteInitValues*>(mxGetPr(zab82456318));sg::ofa::Lin_Write_Stop(*z5df65ca785,reinterpret_cast<size_t>(S));
#endif
}
#include "../common/libsg/sg_sfcn_glue.h"

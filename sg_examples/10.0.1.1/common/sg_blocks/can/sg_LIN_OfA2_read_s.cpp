// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL    (0x164+3036-0xd3e)
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME     sg_LIN_OfA2_read_s
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
#define zefdd6d55b2 (0xfca+2740-0x1a7d)        
#define z5cfd65b291 (0x63c+8238-0x266a)      
#define z4ff5168d43 (0x43+8502-0x2179)     
#define zab82456318 ssGetSFcnParam(S, (0x18f0+1970-0x20a2))
static char_T ze03e9e0a0d[(0xe03+3309-0x19f0)];static int SetAndCheckSFunctionParams(uint8_T ze58e331f42,SimStruct*S);static void CreateSFunctionInputPorts(int32_T zcf9aed83ba,SimStruct*S);static void CreateSFunctionOutputPorts(int32_T z7f34f9d205,SimStruct*S);static void SetSFunctionOutputPortProperties(int32_T z7da5ab49fa,int32_T zbc29571b7b,uint32_T ze97179dd68,uint8_T z2548e6cd9c,SimStruct*S);static void mdlInitializeSizes(SimStruct*S){
#ifdef MATLAB_MEX_FILE
const sg::ofa::LinReadInitValues*z5df65ca785=reinterpret_cast<const sg::ofa::LinReadInitValues*>(mxGetPr(zab82456318));bool enaUpdateState=static_cast<bool>(z5df65ca785->enaUpdateState);bool enaMsgType=static_cast<bool>(z5df65ca785->enaMsgType);bool enaDataOverrun=static_cast<bool>(z5df65ca785->enaDataOverrun);bool enaTimeStamp=static_cast<bool>(z5df65ca785->enaTimeStamp);uint8_t messageType=static_cast<uint8_t>(z5df65ca785->Channel.messageType);uint32_t dlc=static_cast<uint32_t>(z5df65ca785->dlc);uint8_T z36543df51b=(0x41+7503-0x1d8f);int_T status=(0x289+1976-0xa41);DTypeId zb1d627659d=(0xb21+664-0xdb9);zb1d627659d=ssRegisterDataType(S,"\x4c\x49\x4e\x5f\x4d\x45\x53\x53\x41\x47\x45");if(INVALID_DTYPE_ID==zb1d627659d){return;}status=ssSetDataTypeSize(S,zb1d627659d,sizeof(LINMsg));if((0xcb8+3905-0x1bf9)==status){return;}
#endif 
if((0x26b+3429-0xfd0)==SetAndCheckSFunctionParams((0x134a+893-0x16c7),S)){sprintf(ze03e9e0a0d,"\x43\x68\x65\x63\x6b\x20\x6c\x69\x73\x74\x20\x6f\x66\x20\x70\x61\x72\x61\x6d\x65\x74\x65\x72\x73\x2c\x20\x25\x69\x20\x70\x61\x72\x61\x6d\x65\x74\x65\x72\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64\x21\x21\x21",zefdd6d55b2);ssSetErrorStatus(S,ze03e9e0a0d);return;}
#ifdef MATLAB_MEX_FILE
z36543df51b+=(enaUpdateState)?(0x2a8+7154-0x1e99):(0x2bd+7689-0x20c6);z36543df51b+=(enaMsgType)?(0x1078+5208-0x24cf):(0xe4b+1442-0x13ed);z36543df51b+=(enaDataOverrun)?(0x4cf+803-0x7f1):(0x2662+4-0x2666);z36543df51b+=(enaTimeStamp)?(0x9a3+2818-0x14a4):(0x866+2458-0x1200);CreateSFunctionOutputPorts(z36543df51b,S);CreateSFunctionInputPorts(z5cfd65b291,S);z36543df51b=(0xcc7+5693-0x2304);if(enaUpdateState){SetSFunctionOutputPortProperties(z36543df51b,(0x571+1843-0xca3),SS_INT32,(0x13aa+2711-0x1e41),S);z36543df51b+=(0xe65+3418-0x1bbe);}if(enaMsgType){SetSFunctionOutputPortProperties(z36543df51b,(0xcc8+5474-0x2229),SS_UINT32,(0x188c+1530-0x1e86),S);z36543df51b+=(0x3a7+2161-0xc17);}if(enaDataOverrun){SetSFunctionOutputPortProperties(z36543df51b,(0x11ad+3116-0x1dd8),SS_UINT32,(0xb5+517-0x2ba),S);z36543df51b+=(0xc70+1439-0x120e);}if(enaTimeStamp){SetSFunctionOutputPortProperties(z36543df51b,(0x1bd9+484-0x1dbc),SS_DOUBLE,(0x1d8f+236-0x1e7b),S);z36543df51b+=(0x28f+7062-0x1e24);}if((0x560+5128-0x1967)==messageType){sprintf(ze03e9e0a0d,"\x4d\x65\x73\x73\x61\x67\x65\x20\x74\x79\x70\x65\x20\x27\x4c\x49\x4e\x27\x20\x69\x73\x20\x6e\x6f\x74\x20\x73\x75\x70\x70\x6f\x72\x74\x65\x64\x20\x79\x65\x74\x21\x21\x21");ssSetErrorStatus(S,ze03e9e0a0d);return;}else{SetSFunctionOutputPortProperties(z36543df51b,dlc,SS_UINT8,(0x2+475-0x1dd),S);}
#endif 
ssSetNumRWork(S,(0x68b+4924-0x19c7));ssSetNumIWork(S,(0x1461+3536-0x2231));ssSetNumPWork(S,(0xc74+6319-0x2523));ssSetNumContStates(S,(0x13a9+789-0x16be));ssSetNumDiscStates(S,(0x11ac+505-0x13a5));ssSetNumSampleTimes(S,(0x918+1543-0xf1e));ssSetNumModes(S,(0x180a+1401-0x1d83));ssSetNumNonsampledZCs(S,(0x1f57+618-0x21c1));ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static int SetAndCheckSFunctionParams(uint8_T ze58e331f42,SimStruct*S){int i=(0x33c+6186-0x1b66);ssSetNumSFcnParams(S,zefdd6d55b2);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){return(0x2369+454-0x252f);}for(i=(0x901+5582-0x1ecf);i<zefdd6d55b2;i++){ssSetSFcnParamTunable(S,i,ze58e331f42);}return(0x2467+662-0x26fc);}static void CreateSFunctionInputPorts(int32_T zcf9aed83ba,SimStruct*S){if((0x98b+3311-0x167a)==zcf9aed83ba){ssSetNumInputPorts(S,z5cfd65b291);}else{ssSetNumInputPorts(S,zcf9aed83ba);}}static void CreateSFunctionOutputPorts(int32_T z7f34f9d205,SimStruct*S){if((0x12c1+3114-0x1eeb)==z7f34f9d205){ssSetNumOutputPorts(S,z4ff5168d43);}else{ssSetNumOutputPorts(S,z7f34f9d205);}}static void SetSFunctionOutputPortProperties(int32_T z7da5ab49fa,int32_T zbc29571b7b,uint32_T ze97179dd68,uint8_T z2548e6cd9c,SimStruct*S){if((0xbd2+4823-0x1ea8)==z2548e6cd9c){ssSetOutputPortWidth(S,z7da5ab49fa,zbc29571b7b);}else if((0x15f+6017-0x18de)==z2548e6cd9c){ssSetOutputPortDataType(S,z7da5ab49fa,ze97179dd68);}else{ssSetOutputPortWidth(S,z7da5ab49fa,zbc29571b7b);ssSetOutputPortDataType(S,z7da5ab49fa,ze97179dd68);}}static void mdlInitializeSampleTimes(SimStruct*S){const double*zbe8c45f9f4=mxGetPr(zab82456318);if(zbe8c45f9f4[(0x1bf2+2723-0x2693)]==-1.0){ssSetSampleTime(S,(0x4f+2243-0x912),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x1208+2169-0x1a81),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0xb06+5746-0x2178),zbe8c45f9f4[(0x83c+1606-0xe80)]);ssSetOffsetTime(S,(0xda0+4890-0x20ba),0.0);}}static void sg_ModelLoad(SimStruct*S){}static void sg_ModelStart(SimStruct*S){const sg::ofa::LinReadInitValues*z5df65ca785=reinterpret_cast<const sg::ofa::LinReadInitValues*>(mxGetPr(zab82456318));
#ifndef MATLAB_MEX_FILE
sg::ofa::Lin_Read_Start(*z5df65ca785,reinterpret_cast<size_t>(S));
#endif
}static void sg_ModelStep(SimStruct*S){
#ifndef MATLAB_MEX_FILE
uint8_T zee7c235605=(0xf29+2296-0x1821);int32_T z7f91b0f862=(0x1580+2460-0x1f1c);uint32_T zfd43d855a7=(0x4e8+1062-0x90e);uint32_T z1605f34305=(0x1569+1006-0x1957);double timeStamp=0.0;uint8_T data[(0x133a+2012-0x1b0e)]={(0x61f+2674-0x1091)};const sg::ofa::LinReadInitValues*z5df65ca785=reinterpret_cast<const sg::ofa::LinReadInitValues*>(mxGetPr(zab82456318));bool enaUpdateState=static_cast<bool>(z5df65ca785->enaUpdateState);bool enaMsgType=static_cast<bool>(z5df65ca785->enaMsgType);bool enaDataOverrun=static_cast<bool>(z5df65ca785->enaDataOverrun);bool enaTimeStamp=static_cast<bool>(z5df65ca785->enaTimeStamp);uint8_t dlc=static_cast<uint8_t>(z5df65ca785->dlc);uint8_t isSlv=static_cast<uint8_t>(z5df65ca785->Channel.isSlv);uint8_t protIdent=static_cast<uint8_t>(z5df65ca785->protIdent);uint8_t isEnhcdChksum=static_cast<uint8_t>(z5df65ca785->isEnhcdChksum);bool success=sg::ofa::Lin_Read_Step(*z5df65ca785,&z7f91b0f862,&zfd43d855a7,&z1605f34305,&timeStamp,data);if(enaUpdateState){*(int32_T*)ssGetOutputPortSignal(S,zee7c235605)=z7f91b0f862;zee7c235605+=(0x1cb6+263-0x1dbc);}if(success){if(enaMsgType){*(uint32_T*)ssGetOutputPortSignal(S,zee7c235605)=zfd43d855a7;zee7c235605+=(0xd2b+5137-0x213b);}if(enaDataOverrun){*(uint32_T*)ssGetOutputPortSignal(S,zee7c235605)=z1605f34305;zee7c235605+=(0x12d7+298-0x1400);}if(enaTimeStamp){*(double*)ssGetOutputPortSignal(S,zee7c235605)=timeStamp;zee7c235605+=(0x566+1012-0x959);}memcpy((void*)ssGetOutputPortSignal(S,zee7c235605),data,dlc);}if((0x1fdd+1707-0x2688)==isSlv){uint8_t protIdent=static_cast<uint8_t>(z5df65ca785->protIdent);uint8_t isEnhcdChksum=static_cast<uint8_t>(z5df65ca785->isEnhcdChksum);uint8_t dlc=static_cast<uint8_t>(z5df65ca785->dlc);LINMsg2 m={(0xe26+5552-0x23d6)};m.msg.ProtID=protIdent;m.msg.EnhcdCksm=isEnhcdChksum;m.msg.Len=dlc;m.msg.IDOnly=(0x20aa+383-0x2228);(void)sg::ofa::Lin_Write_Step_From_Read(*z5df65ca785,(void*)&m,reinterpret_cast<size_t>(S));}
#endif
}static void sg_ModelStop(SimStruct*S){
#ifndef MATLAB_MEX_FILE
const sg::ofa::LinReadInitValues*z5df65ca785=reinterpret_cast<const sg::ofa::LinReadInitValues*>(mxGetPr(zab82456318));sg::ofa::Lin_Read_Stop(*z5df65ca785,reinterpret_cast<size_t>(S));
#endif 
}
#include "../common/libsg/sg_sfcn_glue.h"


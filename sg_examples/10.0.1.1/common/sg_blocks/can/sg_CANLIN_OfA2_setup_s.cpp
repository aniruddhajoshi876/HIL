// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL (0x7c0+812-0xaea)
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME sg_CANLIN_OfA2_setup_s
#include "simstruc.h"
#ifndef MATLAB_MEX_FILE
#include "../common/libsg/sg_common.h"
#else
#include "mex.h"
#endif
#define SG_EARLY_INIT
#define SG_HAS_MDL_EXIT
#include "../common/libsg/sg_callback.h"
#include "../common/libsg/sg_printf.h"
#include <exception>
#include "include/OfA2_SFunctionInterface.h"
#define zefdd6d55b2 (0x12a9+840-0x15ee)         
#define z5cfd65b291 (0xce1+254-0xddf)      
#define z4ff5168d43 (0x1839+3306-0x2523)     
#define z5c1f4c33a0 mxGetPr(ssGetSFcnParam(S, (0x1919+1441-0x1eba)))
#define z2fd83f618e mxGetPr(ssGetSFcnParam(S, (0x8cf+7211-0x24f9)))
#define za5518baf08 mxGetPr(ssGetSFcnParam(S, (0x1df1+1175-0x2286)))
#define z887810b744 (0x10ad+5264-0x243e)
static char_T z5899ef8b71[z887810b744+(0x1fc+8719-0x240a)];static int z99c2bb5a6a(uint8_T ze58e331f42,SimStruct*S);static void CreateSFunctionInputPorts(int32_T zcf9aed83ba,SimStruct*S);static void CreateSFunctionOutputPorts(int32_T z7f34f9d205,SimStruct*S);static void mdlInitializeSizes(SimStruct*S){if((0x985+4730-0x1bff)==z99c2bb5a6a((0xb5f+3430-0x18c5),S)){sprintf(z5899ef8b71,"\x43\x68\x65\x63\x6b\x20\x6c\x69\x73\x74\x20\x6f\x66\x20\x70\x61\x72\x61\x6d\x65\x74\x65\x72\x73\x2c\x20\x25\x69\x20\x70\x61\x72\x61\x6d\x65\x74\x65\x72\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64\x21\x21\x21",zefdd6d55b2);ssSetErrorStatus(S,z5899ef8b71);return;}CreateSFunctionInputPorts((0xd6+4878-0x13e4),S);CreateSFunctionOutputPorts((0x179b+2370-0x20dd),S);ssSetNumRWork(S,(0xebd+5233-0x232e));ssSetNumIWork(S,(0x136f+560-0x159f));ssSetNumPWork(S,(0x20d6+762-0x23d0));ssSetNumContStates(S,(0x10a7+4741-0x232c));ssSetNumDiscStates(S,(0xd5d+5366-0x2253));ssSetNumSampleTimes(S,(0x1c9f+237-0x1d8b));ssSetNumModes(S,(0x1b96+1083-0x1fd1));ssSetNumNonsampledZCs(S,(0x110+1226-0x5da));ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE|SS_OPTION_PLACE_ASAP);}static int z99c2bb5a6a(uint8_T ze58e331f42,SimStruct*S){int i=(0x892+7379-0x2565);ssSetNumSFcnParams(S,zefdd6d55b2);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){return(0x15f3+489-0x17dc);}for(i=(0x4a2+6494-0x1e00);i<zefdd6d55b2;i++){ssSetSFcnParamTunable(S,i,ze58e331f42);}return(0x368+245-0x45c);}static void CreateSFunctionInputPorts(int32_T zcf9aed83ba,SimStruct*S){if((0xb82+4320-0x1c62)==zcf9aed83ba){ssSetNumInputPorts(S,z5cfd65b291);}else{ssSetNumInputPorts(S,zcf9aed83ba);}}static void CreateSFunctionOutputPorts(int32_T z7f34f9d205,SimStruct*S){if((0xcfc+685-0xfa9)==z7f34f9d205){ssSetNumOutputPorts(S,z4ff5168d43);}else{ssSetNumOutputPorts(S,z7f34f9d205);}}static void mdlInitializeSampleTimes(SimStruct*S){ssSetSampleTime(S,(0x1a01+1976-0x21b9),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x1285+3478-0x201b),FIXED_IN_MINOR_STEP_OFFSET);}static void sg_ModelLoad(SimStruct*S){const sg::ofa::SetupInitValues*z5df65ca785=reinterpret_cast<const sg::ofa::SetupInitValues*>(z5c1f4c33a0);try{
#ifndef MATLAB_MEX_FILE
sg::ofa::Setup_Load(*z5df65ca785);
#endif
}catch(const std::exception&e){strncpy(z5899ef8b71,e.what(),z887810b744);z5899ef8b71[z887810b744]=(0x3c8+6119-0x1baf);ssSetErrorStatus(S,z5899ef8b71);return;}}static void sg_ModelStart(SimStruct*S){const sg::ofa::SetupInitValues*z5df65ca785=reinterpret_cast<const sg::ofa::SetupInitValues*>(z5c1f4c33a0);try{
#ifndef MATLAB_MEX_FILE
sg::ofa::Setup_Start(*z5df65ca785,z2fd83f618e);
#endif
}catch(const std::exception&e){strncpy(z5899ef8b71,e.what(),z887810b744);z5899ef8b71[z887810b744]=(0x24c2+194-0x2584);ssSetErrorStatus(S,z5899ef8b71);return;}}static void sg_ModelStep(SimStruct*){}static void sg_ModelStop(SimStruct*S){const sg::ofa::SetupInitValues*z5df65ca785=reinterpret_cast<const sg::ofa::SetupInitValues*>(z5c1f4c33a0);try{
#ifndef MATLAB_MEX_FILE
sg::ofa::Setup_Stop(*z5df65ca785,za5518baf08);
#endif
}catch(const std::exception&e){
#ifndef MATLAB_MEX_FILE
SG_PRINTF(ERROR,"\x65\x78\x63\x65\x70\x74\x69\x6f\x6e\x20\x69\x6e\x20\x53\x65\x74\x75\x70\x20\x53\x2d\x46\x75\x6e\x63\x74\x69\x6f\x6e\x3a\x20\x25\x73\x20" "\n",e.what());
#endif
strncpy(z5899ef8b71,e.what(),z887810b744);z5899ef8b71[z887810b744]=(0x4f4+7115-0x20bf);ssSetErrorStatus(S,z5899ef8b71);return;}}static void sg_ModelExit(SimStruct*S){const sg::ofa::SetupInitValues*z5df65ca785=reinterpret_cast<const sg::ofa::SetupInitValues*>(z5c1f4c33a0);sg::ofa::Setup_Exit(*z5df65ca785);}
#include "../common/libsg/sg_sfcn_glue.h"


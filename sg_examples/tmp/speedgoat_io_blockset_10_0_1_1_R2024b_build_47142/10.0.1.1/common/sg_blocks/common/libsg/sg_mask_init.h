// Copyright 2006-2026 Speedgoat GmbH

#ifndef z52ab558952
#define z52ab558952
#define RTW_GENERATED_S_FUNCTION
#include "simstruc.h"
#ifdef __cplusplus
extern"C"{
#endif
typedef struct{int numberOfParams;int integerWorkVecLength;int realWorkVecLength;int pointerWorkVecLength;}SgMaskInit_SetupSettingsArgs;extern int sgMaskInit_initSizesForSetupBlock(SimStruct*S,SgMaskInit_SetupSettingsArgs*args);extern int sgMaskInit_initSizesForRegularBlock(SimStruct*S,SgMaskInit_SetupSettingsArgs*args);extern void sgMaskInit_initSampleTimesForSetupBlock(SimStruct*S);extern void sgMaskInit_initSampleTimesForRegularBlock(SimStruct*S,double sampleTime);extern void sgMaskInit_setNoInputPorts(SimStruct*S);extern void sgMaskInit_setInputPorts(SimStruct*S,int z23caebc4cc,int zbc29571b7b);extern void sgMaskInit_setNoOutputPorts(SimStruct*S);extern void sgMaskInit_setOutputPorts(SimStruct*S,int z23caebc4cc,int zbc29571b7b);extern int sgMaskInit_setNumberOfSFunctionParams(SimStruct*S,int numberOfParams);extern void sgMaskInit_setZeroNumberOfStates(SimStruct*S);extern void sgMaskInit_setToSingleRate(SimStruct*S);extern void sgMaskInit_setVectorSizes(SimStruct*S,int integerWorkVecLength,int realWorkVecLength,int pointerWorkVecLength);extern void sgMaskInit_setOptionsForSetupBlock(SimStruct*S);extern void sgMaskInit_setOptionsForGeneralBlock(SimStruct*S);
#ifdef __cplusplus
}
#endif
#endif  


// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL    (0x1f6+3971-0x1177)
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME     sg_IO143_IO144_do_s_v2
#include "sg_IO143_IO144_v2.h"
#include "simstruc.h"
#ifdef MATLAB_MEX_FILE
#include "mex.h"
#else
#include "sg_common.h"
#include "sg_printf.h"
#include "sg_module_registry.h"
#include "sg_module_types.h"
#endif
#define SG_EARLY_INIT
#include "sg_callback.h"
#define z533b11d03f               ssGetSFcnParam(S,  (0xdaf+3092-0x19c3)) 
#define za00184cdc1                ssGetSFcnParam(S,  (0x12b4+4430-0x2401)) 
#define z702a26a5e9                    ssGetSFcnParam(S,  (0x117c+3295-0x1e59)) 
#define zabe1e0cd2c              ssGetSFcnParam(S,  (0xf91+670-0x122c)) 
#define ze43f97b6ea             ssGetSFcnParam(S,  (0x6c5+6391-0x1fb8)) 
#define zf1feb900ea              ssGetSFcnParam(S,  (0x11b6+278-0x12c7)) 
#define z724139b233                ssGetSFcnParam(S,  (0x1f49+1618-0x2595)) 
#define zcc03c07da0 ssGetSFcnParam(S,  (0x1d25+1894-0x2484)) 
#define ze5bdce7221  ssGetSFcnParam(S,  (0xc43+2836-0x174f)) 
#define zdf24515981                            (    (0x321+4968-0x1680))
#define z2e6483d505              ((0x16fd+721-0x19ce))
#define zc5ce4cb81a              ((0x89f+3844-0x17a3))
#define z2b17e2ee3b              ((0x135b+2429-0x1cd8))
static char msg[(0x654+5501-0x1ad1)];static int zdc01648b54;static void mdlInitializeSizes(SimStruct*S){uint_T i;zdc01648b54=sprintf(msg,"\x49\x6e\x20\x49\x4f\x25\x64\x2c\x20\x44\x69\x67\x69\x74\x61\x6c\x20\x6f\x75\x74\x70\x75\x74\x20\x62\x6c\x6f\x63\x6b\x2c\x20\x49\x44\x20\x25\x64\x3a\x20",(int)mxGetPr(z533b11d03f)[(0x9dc+5982-0x213a)],(int)mxGetPr(za00184cdc1)[(0x48c+1890-0xbee)]);ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf((msg+zdc01648b54),"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n""\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64\x2e" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x446+6423-0x1d5d));ssSetNumDiscStates(S,(0x743+7229-0x2380));if(!ssSetNumOutputPorts(S,(0x42c+7504-0x217c)))return;if(!ssSetNumInputPorts(S,(int)mxGetN(ze43f97b6ea)))return;for(i=(0x98a+7127-0x2561);i<(uint_T)mxGetN(ze43f97b6ea);i++){ssSetInputPortWidth(S,i,(0x224a+594-0x249b));ssSetInputPortDirectFeedThrough(S,i,(0x80f+4077-0x17fb));ssSetInputPortRequiredContiguous(S,i,(0x1272+4963-0x25d4));}ssSetNumSampleTimes(S,(0xb19+3012-0x16dc));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x242+3482-0xfdc));ssSetNumNonsampledZCs(S,(0x1aea+1532-0x20e6));for(i=(0x1801+2386-0x2153);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,SS_PRM_NOT_TUNABLE);}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(zabe1e0cd2c)[(0x12ad+2274-0x1b8f)]==-1.0){ssSetSampleTime(S,(0x15ff+2115-0x1e42),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x907+3987-0x189a),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x1bf7+122-0x1c71),mxGetPr(zabe1e0cd2c)[(0x146c+2877-0x1fa9)]);ssSetOffsetTime(S,(0x636+2047-0xe35),0.0);}}
#ifndef MATLAB_MEX_FILE
static void sg_ModelLoad(SimStruct*S){}static void sg_ModelStart(SimStruct*S){}static void sg_ModelStep(SimStruct*S){uint32_T z85c496e7c0;real_T y;uint_T i;int boardType=(int)mxGetPr(z533b11d03f)[(0x13fa+1739-0x1ac5)];int za0d38ae598=(int)mxGetPr(za00184cdc1)[(0x40d+1800-0xb15)];uint32_T zf91d71c6d9=(uint32_T)mxGetN(ze43f97b6ea);zc8ee45929d*zae10e3f17f=(zc8ee45929d*)sg_module_get_custom_data(boardType,za0d38ae598);if(!zae10e3f17f){sprintf(msg,"\x49\x4f\x25\x64\x20\x28\x49\x44\x20\x25\x64\x29\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x72\x65\x74\x72\x69\x65\x76\x65\x20\x6d\x6f\x64\x75\x6c\x65\x20\x66\x72\x6f\x6d\x20\x72\x65\x67\x69\x73\x74\x72\x79\x20\x69\x6e\x20\x44\x4f\x20\x4d\x6f\x64\x65\x6c\x53\x74\x65\x70" "\n",boardType,za0d38ae598);ssSetErrorStatus(S,msg);return;}uint32_T ze9367ce973=(0x745+3844-0x1649);uint32_T z8b0d5b4a4e=zae10e3f17f->z3fad3d9764->ze6c8560b12;if(((uint32_T)mxGetPr(zcc03c07da0)[(0x269+9282-0x26ab)]-(0x1a6+6788-0x1c29))==z1686dc734b){for(i=(0x416+2231-0xccd);i<zf91d71c6d9;i++){z85c496e7c0=(uint32_T)mxGetPr(ze43f97b6ea)[i]-(0x3ea+2556-0xde5);y=*ssGetInputPortRealSignal(S,i);if(y==1.0){z8b0d5b4a4e&=~((0x1828+2445-0x21b4)<<z85c496e7c0);}else{z8b0d5b4a4e|=(0x1119+3750-0x1fbe)<<z85c496e7c0;}}}else{for(i=(0xa43+6855-0x250a);i<zf91d71c6d9;i++){z85c496e7c0=(uint32_T)mxGetPr(ze43f97b6ea)[i]-(0x2014+112-0x2083);y=*ssGetInputPortRealSignal(S,i);if(y==1.0){ze9367ce973|=(0x1139+2647-0x1b8f)<<z85c496e7c0;}}}SG_PRINTF(TRACE,"\x44\x4f\x20\x65\x6e\x61\x62\x6c\x65\x3a\x20\x25\x58" "\n",z8b0d5b4a4e);zae10e3f17f->z3fad3d9764->ze6c8560b12=z8b0d5b4a4e;SG_PRINTF(TRACE,"\x44\x4f\x20\x64\x61\x74\x61\x3a\x20\x25\x58" "\n",ze9367ce973);zae10e3f17f->z3fad3d9764->zf86f2f7cb9=ze9367ce973;}static void sg_ModelStop(SimStruct*S){}
#endif 
#include "sg_sfcn_glue.h"   


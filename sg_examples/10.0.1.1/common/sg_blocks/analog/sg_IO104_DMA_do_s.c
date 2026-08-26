// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL    (0x52b+3586-0x132b)
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME     sg_IO104_DMA_do_s
#include <stdlib.h>
#ifdef MATLAB_MEX_FILE
#include "mex.h"
#else
#include "sg_common.h"
#endif
#define SG_EARLY_INIT   
#include "sg_io104.h"
#include "sg_callback.h"
#define z96b1a4487e          ssGetSFcnParam(S, (0x18c+1757-0x869))
#define z702a26a5e9                ssGetSFcnParam(S, (0x1307+2705-0x1d97))
#define z3832b85a32           ssGetSFcnParam(S, (0xbdc+2335-0x14f9))
#define z1038324b81       ssGetSFcnParam(S, (0x1a77+2359-0x23ab))
#define z724139b233            ssGetSFcnParam(S, (0x171a+2089-0x1f3f))
#define za00184cdc1            ssGetSFcnParam(S, (0xcac+142-0xd35)) 
#define zdf24515981                           ((0x40b+2184-0xc8d))
#define z2e6483d505              ((0x3c0+803-0x6e3))
#define zc5ce4cb81a              ((0xf8d+5040-0x233d))
#define z2b17e2ee3b              ((0x1a03+2606-0x2431))
static char msg[(0xd7c+600-0xed4)];
#ifndef MATLAB_MEX_FILE
static void zd98b6312f7(SimStruct*S,z50df7b81b0*zae10e3f17f,bool z2e7c70562d);
#endif
static void mdlInitializeSizes(SimStruct*S){int i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e\x20\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x14d9+1503-0x1ab8));ssSetNumDiscStates(S,(0xae6+4437-0x1c3b));if(!ssSetNumOutputPorts(S,(0x180+4079-0x116f))){return;}if(!ssSetNumInputPorts(S,(int)mxGetN(z96b1a4487e))){return;}for(i=(0x15f2+3300-0x22d6);i<(int)mxGetN(z96b1a4487e);i++){ssSetInputPortWidth(S,i,(0x183+7515-0x1edd));ssSetInputPortDirectFeedThrough(S,i,(0x1737+859-0x1a91));ssSetInputPortRequiredContiguous(S,i,(0x1e2a+1075-0x225c));}ssSetNumSampleTimes(S,(0x1d36+975-0x2104));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x400+6218-0x1c4a));ssSetNumNonsampledZCs(S,(0x5c3+4351-0x16c2));for(i=(0x9fc+4397-0x1b29);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x203a+1161-0x24c3));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0x11f+6171-0x193a)]==-1.0){ssSetSampleTime(S,(0x28a+3493-0x102f),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0xa35+3712-0x18b5),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x9d9+5897-0x20e2),mxGetPr(z3832b85a32)[(0x125f+790-0x1575)]);ssSetOffsetTime(S,(0x3a+352-0x19a),0.0);}}
#ifndef MATLAB_MEX_FILE
static void sg_ModelLoad(SimStruct*S){uint32_t moduleId;moduleId=(int)mxGetPr(za00184cdc1)[(0xd82+5540-0x2326)];z50df7b81b0*zae10e3f17f=(z50df7b81b0*)sg_module_get_custom_data(SG_MODULE_TYPE_IO104,moduleId);if(!zae10e3f17f){sprintf(msg,"\x25\x73\x20\x28\x49\x44\x20\x25\x64\x29\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x72\x65\x74\x72\x69\x65\x76\x65\x20\x6d\x6f\x64\x75\x6c\x65\x20\x73\x74\x61\x74\x65\x20\x66\x72\x6f\x6d\x20\x72\x65\x67\x69\x73\x74\x72\x79" "\n",DEVNAME,moduleId);ssSetErrorStatus(S,msg);return;}else{SG_PRINTF_DEBUG("\x44\x4f\x5f\x4c\x6f\x61\x64\x3a\x20\x4d\x6f\x64\x75\x6c\x65\x20\x61\x6c\x72\x65\x61\x64\x79\x20\x72\x65\x67\x69\x73\x74\x65\x72\x65\x64" "\n");}zae10e3f17f->z183fd27444=(z020494c81d*)(zae10e3f17f->z919abdb780);zd98b6312f7(S,zae10e3f17f,true);}static void sg_ModelStart(SimStruct*S){}static void sg_ModelStep(SimStruct*S){uint32_t zf91d71c6d9=(uint32_t)mxGetN(z96b1a4487e);uint32_t z718c4c15f4,bit,ch,ze1dce08a7a,i;double const*z2a6249eb7a;double const*zc53bd62959;zc53bd62959=mxGetPr(z96b1a4487e);int moduleId=(int)mxGetPr(za00184cdc1)[(0x1856+3493-0x25fb)];z50df7b81b0*zae10e3f17f=(z50df7b81b0*)sg_module_get_custom_data(SG_MODULE_TYPE_IO104,moduleId);if(!zae10e3f17f){sprintf(msg,"\x25\x73\x20\x28\x49\x44\x20\x25\x64\x29\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x72\x65\x74\x72\x69\x65\x76\x65\x20\x6d\x6f\x64\x75\x6c\x65\x20\x73\x74\x61\x74\x65\x20\x66\x72\x6f\x6d\x20\x72\x65\x67\x69\x73\x74\x72\x79" "\n",DEVNAME,moduleId);ssSetErrorStatus(S,msg);return;}z718c4c15f4=zae10e3f17f->z183fd27444->dio;for(i=(0xa8+2757-0xb6d);i<zf91d71c6d9;i++){ch=(int32_t)zc53bd62959[i]-(0x1931+2041-0x2129);ze1dce08a7a=i;z2a6249eb7a=ssGetInputPortRealSignal(S,ze1dce08a7a);bit=((0xfe3+4804-0x22a6)<<(ch+((ch>(0x75f+4101-0x175d))?(zd4f65135a2-(0xa8+4251-0x113b)):(0x57d+1002-0x967))));if(!z2a6249eb7a){sprintf(msg,"\x25\x73\x3a\x20\x4e\x75\x6c\x6c\x20\x70\x6f\x69\x6e\x74\x65\x72\x20\x69\x6e\x20\x64\x69\x67\x69\x74\x61\x6c\x20\x6f\x75\x74\x70\x75\x74\x73\x2e\x20\x43\x6f\x6e\x74\x61\x63\x74\x20\x73\x70\x65\x65\x64\x67\x6f\x61\x74\x21",DEVNAME);ssSetErrorStatus(S,msg);return;}if(*z2a6249eb7a>(0x1642+1897-0x1dab)){z718c4c15f4|=bit;}else{z718c4c15f4&=~bit;}}zae10e3f17f->z183fd27444->dio=z718c4c15f4;}static void sg_ModelStop(SimStruct*S){uint32_t moduleId=(int)mxGetPr(za00184cdc1)[(0x169b+2865-0x21cc)];z50df7b81b0*zae10e3f17f=(z50df7b81b0*)sg_module_get_custom_data(SG_MODULE_TYPE_IO104,moduleId);if(!zae10e3f17f){sprintf(msg,"\x25\x73\x20\x28\x49\x44\x20\x25\x64\x29\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x72\x65\x74\x72\x69\x65\x76\x65\x20\x6d\x6f\x64\x75\x6c\x65\x20\x73\x74\x61\x74\x65\x20\x66\x72\x6f\x6d\x20\x72\x65\x67\x69\x73\x74\x72\x79" "\n",DEVNAME,moduleId);ssSetErrorStatus(S,msg);return;}zd98b6312f7(S,zae10e3f17f,false);}static void zd98b6312f7(SimStruct*S,z50df7b81b0*zae10e3f17f,bool z2e7c70562d){uint32_t zf91d71c6d9=(uint32_t)mxGetN(z96b1a4487e);uint32_t z718c4c15f4,bit,ch,i,moduleId;z718c4c15f4=zae10e3f17f->z183fd27444->dio;for(i=(0x1aab+3074-0x26ad);i<zf91d71c6d9;i++){if(z2e7c70562d||(int)mxGetPr(z724139b233)[i]){ch=(uint32_t)mxGetPr(z96b1a4487e)[i]-(0xf5c+3192-0x1bd3);bit=((0x973+6101-0x2147)<<(ch+((ch>(0xea+2979-0xc86))?(zd4f65135a2-(0x748+4081-0x1731)):(0x1256+1816-0x196e))));if(mxGetPr(z1038324b81)[i]){z718c4c15f4|=bit;}else{z718c4c15f4&=~bit;}}}zae10e3f17f->z183fd27444->dio=z718c4c15f4;}
#endif
#include "sg_sfcn_glue.h"


// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL    (0x1b89+1079-0x1fbe)
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME     sg_IO113_20_di_s
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include "sg_io113_20.h"
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
#define ze13f49a01f           ssGetSFcnParam(S, (0x636+4032-0x15f6))
#define z3832b85a32           ssGetSFcnParam(S, (0x62f+3803-0x1509))
#define z702a26a5e9                ssGetSFcnParam(S, (0xe3+4552-0x12a9))
#define zb18e38a301           ssGetSFcnParam(S, (0xf81+5062-0x2344))
#define zdf24515981                           ((0xca5+2479-0x1650))
#define z2e6483d505              ((0xe4c+2816-0x194c))
#define zc5ce4cb81a              ((0x1e0d+188-0x1ec9))
#define z2b17e2ee3b              ((0x50f+5845-0x1be4))
static char_T msg[(0xfbd+2893-0x1a0a)];static void mdlInitializeSizes(SimStruct*S){uint32_T i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x1ed0+185-0x1f89));ssSetNumDiscStates(S,(0x211+5213-0x166e));if(!ssSetNumInputPorts(S,(0x554+2617-0xf8d)))return;if(!ssSetNumOutputPorts(S,(int)mxGetN(zb18e38a301)))return;for(i=(0xf08+3382-0x1c3e);i<(int)mxGetN(zb18e38a301);i++){ssSetOutputPortWidth(S,i,(0xf17+5330-0x23e8));ssSetOutputPortDataType(S,i,SS_DOUBLE);}ssSetNumSampleTimes(S,(0xed+8196-0x20f0));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x1614+622-0x1882));ssSetNumNonsampledZCs(S,(0xe79+4559-0x2048));for(i=(0xbdb+6747-0x2636);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x1123+320-0x1263));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0x4b1+2403-0xe14)]==-1.0){ssSetSampleTime(S,(0x4f7+3692-0x1363),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0xd7+2318-0x9e5),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x882+2498-0x1244),mxGetPr(z3832b85a32)[(0x1590+4151-0x25c7)]);ssSetOffsetTime(S,(0x18c+7292-0x1e08),0.0);}}
#ifndef MATLAB_MEX_FILE
static void sg_ModelLoad(SimStruct*S){}static void sg_ModelStart(SimStruct*S){}static void sg_ModelStep(SimStruct*S){uint32_T zf91d71c6d9=(uint32_T)mxGetN(zb18e38a301);uint32_T i,channel;uint32_T input;real_T*y;uint32_T za0d38ae598=(uint32_T)mxGetPr(ze13f49a01f)[(0x2439+678-0x26df)];zd63abbc96e*zae10e3f17f=(zd63abbc96e*)sg_module_get_custom_data(z12ba1d7c25,za0d38ae598);if(!zae10e3f17f){sprintf(msg,"\x25\x73\x20\x28\x49\x44\x20\x25\x75\x29\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x72\x65\x74\x72\x69\x65\x76\x65\x20\x6d\x6f\x64\x75\x6c\x65\x20\x69\x6e\x20\x44\x49\x20\x4d\x6f\x64\x65\x6c\x53\x74\x65\x70" "\n",DEVNAME,za0d38ae598);ssSetErrorStatus(S,msg);return;}input=zae10e3f17f->z3fad3d9764[z9621b996a9];SG_PRINTF(TRACE,"\x52\x45\x47\x5f\x44\x50\x52\x20\x28\x64\x69\x29\x3a\x20\x30\x78\x25\x78" "\n",input);for(i=(0x1484+416-0x1624);i<zf91d71c6d9;i++){channel=(uint32_T)mxGetPr(zb18e38a301)[i]-(0x205c+1090-0x249d);y=ssGetOutputPortSignal(S,i);switch(channel){case(0x38a+6088-0x1b52):y[(0x253+8311-0x22ca)]=(input&(0xf9+9662-0x26b6));break;case(0x423+2099-0xc55):y[(0x1217+8-0x121f)]=(input&(0x12b4+4369-0x23c3))>>(0x1167+102-0x11cc);break;case(0x354+5162-0x177c):y[(0x228+462-0x3f6)]=(input&(0x44d+6634-0x1e33))>>(0x4f6+7631-0x22c3);break;case(0x171c+677-0x19be):y[(0xd35+3805-0x1c12)]=(input&(0x1b91+2323-0x249c))>>(0x702+555-0x92a);break;case(0x1690+3275-0x2357):y[(0x18a1+2500-0x2265)]=(input&(0x717+4658-0x1849))>>(0x123c+3788-0x2100);break;case(0x1327+3458-0x20a4):y[(0xa97+1815-0x11ae)]=(input&(0x472+1577-0x89b))>>(0x177b+1932-0x1efe);break;case(0xc4+2189-0x94b):y[(0x2318+644-0x259c)]=(input&(0x4d9+2904-0xc31))>>(0x10ef+2368-0x1a25);break;case(0xc1c+4300-0x1ce1):y[(0xfd+9059-0x2460)]=(input&(0x1253+6928-0x2563))>>(0x121+1507-0x6f9);break;default:y[(0x155f+4505-0x26f8)]=0.0;break;}}}static void sg_ModelStop(SimStruct*S){}
#endif 
#include "sg_sfcn_glue.h"   


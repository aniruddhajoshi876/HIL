// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL    (0x2026+840-0x236c)
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME     sg_IO206_read_s
#include "sg_io206.h"
#include "simstruc.h"
#ifndef MATLAB_MEX_FILE
#include "sg_printf.h"
#include "sg_common.h"
#include "sg_module_registry.h"
#include "sg_module_types.h"
static const int z0e14cce82f=zedc83d0317;
#else
#include "mex.h"
#endif
#include "sg_callback.h"
#define z2cc9a52544            ssGetSFcnParam(S, (0x1c90+932-0x2034))
#define z3832b85a32           ssGetSFcnParam(S, (0x915+5469-0x1e71))
#define z702a26a5e9                ssGetSFcnParam(S, (0x39+3724-0xec3))
#define ze13f49a01f           ssGetSFcnParam(S, (0x3a9+8073-0x232f))
#define zdf24515981          ((0xafc+6756-0x255c))
#define z2e6483d505              ((0x1323+1886-0x1a81))
#define zc5ce4cb81a              ((0x879+53-0x8ae))
#define z2b17e2ee3b              ((0x271+1699-0x914))
static char_T msg[(0x2af+6926-0x1cbd)];static void mdlInitializeSizes(SimStruct*S){uint16_t i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x45c+4355-0x155f));ssSetNumDiscStates(S,(0x7e5+2385-0x1136));if(!ssSetNumInputPorts(S,(0x161+6064-0x1911)))return;switch((uint8_t)mxGetPr(z2cc9a52544)[(0x2b7+7185-0x1ec8)]){case(0xec8+3537-0x1c98):if(!ssSetNumOutputPorts(S,(0xb12+605-0xd4f)))return;for(i=(0xc2d+586-0xe77);i<(0x2bc+2501-0xc61);i++){ssSetOutputPortWidth(S,i,(0x634+5996-0x1d9f));}break;case(0xe18+2499-0x17d9):if(!ssSetNumOutputPorts(S,(0xffa+1490-0x15ac)))return;for(i=(0x80c+3521-0x15cd);i<(0x2f8+7575-0x206f);i++){ssSetOutputPortWidth(S,i,(0x366+4864-0x1665));ssSetOutputPortDataType(S,i,SS_BOOLEAN);}break;case(0x16f5+1084-0x1b2e):if(!ssSetNumOutputPorts(S,(0xb83+3920-0x1ad2)))return;ssSetOutputPortWidth(S,(0xd86+5415-0x22ad),(0xc15+3587-0x19f8));break;case(0x59+5059-0x1418):if(!ssSetNumOutputPorts(S,(0x833+6375-0x2119)))return;ssSetOutputPortWidth(S,(0x23a+8704-0x243a),(0xd2a+2922-0x1874));ssSetOutputPortDataType(S,(0x77c+5291-0x1c27),SS_BOOLEAN);break;case(0x69f+3660-0x14e6):if(!ssSetNumOutputPorts(S,(0x752+934-0xaf7)))return;ssSetOutputPortWidth(S,(0x259+5550-0x1807),(0x157f+3870-0x249c));ssSetOutputPortDataType(S,(0xb22+131-0xba5),SS_UINT32);break;}ssSetNumSampleTimes(S,(0x623+352-0x782));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x922+7467-0x264d));ssSetNumNonsampledZCs(S,(0x17a5+3187-0x2418));for(i=(0x42a+4212-0x149e);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0xd69+1399-0x12e0));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0x11c9+3781-0x208e)]==-1.0){ssSetSampleTime(S,(0x8c6+4919-0x1bfd),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x1557+1596-0x1b93),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0xfb3+2002-0x1785),mxGetPr(z3832b85a32)[(0xae3+4637-0x1d00)]);ssSetOffsetTime(S,(0x80+4625-0x1291),0.0);}}
#ifndef MATLAB_MEX_FILE
static void sg_ModelLoad(SimStruct*S){}static void sg_ModelStart(SimStruct*S){}static void sg_ModelStep(SimStruct*S){z854dcf9b8c*zae10e3f17f=NULL;uint8_t i;uint32_t ze1464394c1,input;real_T*y1;boolean_T*y2;uint32_t*z671e76e748;uint32_t za0d38ae598=(uint32_t)mxGetPr(ze13f49a01f)[(0x1e7+4997-0x156c)];zae10e3f17f=(z854dcf9b8c*)sg_module_get_custom_data(z0e14cce82f,za0d38ae598);if(!zae10e3f17f){sprintf(msg,"\x25\x73\x20\x28\x49\x44\x20\x25\x64\x29\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x72\x65\x74\x72\x69\x65\x76\x65\x20\x6d\x6f\x64\x75\x6c\x65\x20\x66\x72\x6f\x6d\x20\x72\x65\x67\x69\x73\x74\x72\x79\x20\x69\x6e\x20\x52\x65\x61\x64\x20\x4d\x6f\x64\x65\x6c\x53\x74\x65\x70" "\n",DEVNAME,za0d38ae598);ssSetErrorStatus(S,msg);return;}input=(uint32_t)zae10e3f17f->z27fd94ac66->z99688dac0f;ze1464394c1=zf683046c76(input);switch((uint8_t)mxGetPr(z2cc9a52544)[(0x8b0+7418-0x25aa)]){case(0x1df+4067-0x11c1):for(i=(0x14e7+1950-0x1c85);i<(0x162c+4012-0x25b8);i++){y1=(real_T*)ssGetOutputPortSignal(S,i);y1[(0xdc0+3073-0x19c1)]=(real_T)((ze1464394c1>>i)&(0x72b+6208-0x1f6a));}break;case(0x1809+1401-0x1d80):for(i=(0xba8+3225-0x1841);i<(0x2d2+2840-0xdca);i++){y2=(boolean_T*)ssGetOutputPortSignal(S,i);y2[(0xce9+6526-0x2667)]=(boolean_T)((ze1464394c1>>i)&(0x1853+2305-0x2153));}break;case(0x386+2171-0xbfe):y1=(real_T*)ssGetOutputPortSignal(S,(0xfd8+3456-0x1d58));for(i=(0x320+1332-0x854);i<(0x12c2+1100-0x16ee);i++){y1[i]=(real_T)((ze1464394c1>>i)&(0x6b8+7502-0x2405));}break;case(0x872+1092-0xcb2):y2=(boolean_T*)ssGetOutputPortSignal(S,(0x8e4+4982-0x1c5a));for(i=(0x12bc+267-0x13c7);i<(0xcd4+2477-0x1661);i++){y2[i]=(boolean_T)((ze1464394c1>>i)&(0x13d6+1510-0x19bb));}break;case(0x576+7425-0x2272):z671e76e748=(uint32_t*)ssGetOutputPortSignal(S,(0x1d40+2414-0x26ae));z671e76e748[(0x1996+1525-0x1f8b)]=ze1464394c1;break;}}static void sg_ModelStop(SimStruct*S){}
#endif  
#include "sg_sfcn_glue.h"   


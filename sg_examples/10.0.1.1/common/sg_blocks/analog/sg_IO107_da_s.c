// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL    (0x1c6+732-0x4a0)
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME     sg_IO107_da_s
#include "sg_io107.h"
#include "simstruc.h"
#ifdef MATLAB_MEX_FILE
#include "mex.h"
#else
#include "sg_common.h"
#include "sg_printf.h"
#include "sg_module_registry.h"
#include "sg_module_types.h" 
#endif
#include "sg_callback.h"
#define ze13f49a01f           ssGetSFcnParam(S, (0x3e0+4670-0x161e))
#define z2b4281b393               ssGetSFcnParam(S, (0x135a+3325-0x2056))
#define za9d8fb6bcf             ssGetSFcnParam(S, (0xd93+4865-0x2092))
#define z8fd86139be               ssGetSFcnParam(S, (0xe5b+1972-0x160c))
#define z3832b85a32           ssGetSFcnParam(S, (0xfbf+3844-0x1ebf))
#define z702a26a5e9                ssGetSFcnParam(S, (0x14b5+2083-0x1cd3))
#define z89d5fad8dc          ssGetSFcnParam(S, (0x1559+3098-0x216d))
#define zc8bbaa6115               ssGetSFcnParam(S, (0x10d1+2611-0x1afd))
#define zd8eb92e45e            ssGetSFcnParam(S, (0xe54+2615-0x1883))
#define zdf24515981          ((0x13dc+452-0x1597))
#define z2e6483d505              ((0x1cea+730-0x1fc4))
#define zc5ce4cb81a              ((0x878+2833-0x1389))
#define z2b17e2ee3b              ((0x19cc+1099-0x1e17))
static void zd98b6312f7(SimStruct*S,z0c4990fb68*zae10e3f17f,int zb2d484c895);static char_T msg[(0x199+7901-0x1f76)];static void mdlInitializeSizes(SimStruct*S){uint32_T i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x143d+3331-0x2140));ssSetNumDiscStates(S,(0x1f78+515-0x217b));if(!ssSetNumOutputPorts(S,(0x3a0+8990-0x26be)))return;if(!ssSetNumInputPorts(S,(int)mxGetN(za9d8fb6bcf)))return;for(i=(0x5f6+981-0x9cb);i<(int)mxGetN(za9d8fb6bcf);i++){ssSetInputPortWidth(S,i,(0x12e4+3772-0x219f));ssSetInputPortDirectFeedThrough(S,i,(0xd0+9588-0x2643));ssSetInputPortRequiredContiguous(S,i,(0x936+5487-0x1ea4));}ssSetNumSampleTimes(S,(0x17b4+925-0x1b50));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x1f54+1795-0x2657));ssSetNumNonsampledZCs(S,(0xf7b+5024-0x231b));for(i=(0x534+1523-0xb27);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,SS_PRM_NOT_TUNABLE);}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0x1833+2086-0x2059)]==-1.0){ssSetSampleTime(S,(0x1c1f+1554-0x2231),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x36+8590-0x21c4),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x101a+5137-0x242b),mxGetPr(z3832b85a32)[(0x19cd+722-0x1c9f)]);ssSetOffsetTime(S,(0x224+4019-0x11d7),0.0);}}
#ifndef MATLAB_MEX_FILE
static void sg_ModelLoad(SimStruct*S){real_T max=(0xf82+5160-0x23aa);char z9a1876ef4c[(0x4ba+5703-0x1aed)];uint32_T za0d38ae598=((uint32_T)mxGetPr(ze13f49a01f)[(0x18fd+1704-0x1fa5)]);uint32_T boardType=(uint32_T)mxGetScalar(z89d5fad8dc);sprintf(z9a1876ef4c,"\x53\x70\x65\x65\x64\x67\x6f\x61\x74\x20\x49\x4f\x25\x64",(int)mxGetScalar(z89d5fad8dc));z0c4990fb68*zae10e3f17f=(z0c4990fb68*)sg_module_get_custom_data(boardType,za0d38ae598);if(!zae10e3f17f){sprintf(msg,"\x49\x4f\x25\x64\x20\x28\x49\x44\x20\x25\x64\x29\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x72\x65\x74\x72\x69\x65\x76\x65\x20\x6d\x6f\x64\x75\x6c\x65\x20\x66\x72\x6f\x6d\x20\x72\x65\x67\x69\x73\x74\x72\x79\x20\x69\x6e\x20\x44\x41\x20\x4d\x6f\x64\x65\x6c\x4c\x6f\x61\x64" "\n",boardType,za0d38ae598);ssSetErrorStatus(S,msg);return;}switch((uint16_T)mxGetPr(z8fd86139be)[(0x1e69+1712-0x2519)]){case(0x412+4112-0x1421):max=10.0;break;case(0xcc6+6465-0x2605):max=5.0;break;case(0x16f6+2229-0x1fa8):max=2.5;break;case(0x7f8+493-0x9e1):max=1.25;break;case(0x1479+1195-0x191f):max=20.0;break;case(0x1055+4234-0x20d9):max=10.0;break;case(0xa3+5720-0x16f4):max=5.0;break;default:ssSetErrorStatus(S,"\x49\x6e\x76\x61\x6c\x69\x64\x20\x76\x6f\x6c\x74\x61\x67\x65\x20\x72\x61\x6e\x67\x65" "\n");return;}zae10e3f17f->z9fb53cdf50=32768.0/max;zae10e3f17f->zb817ad7ad6=max;zd98b6312f7(S,zae10e3f17f,(0x758+5001-0x1ae0));}static void sg_ModelStart(SimStruct*S){SG_PRINTF(DEBUG,"\x44\x41\x3a\x20\x73\x67\x5f\x4d\x6f\x64\x65\x6c\x53\x74\x61\x72\x74" "\n");}static void sg_ModelStep(SimStruct*S){uint16_T i;real_T*zc7fdaf6331;int32_T out;uint16_T index;uint16_T zf91d71c6d9=(uint16_T)mxGetN(za9d8fb6bcf);uint32_T za0d38ae598=((uint32_T)mxGetPr(ze13f49a01f)[(0x11e5+2408-0x1b4d)]);uint32_T boardType=(uint32_T)mxGetScalar(z89d5fad8dc);z0c4990fb68*zae10e3f17f=(z0c4990fb68*)sg_module_get_custom_data(boardType,za0d38ae598);if(!zae10e3f17f){sprintf(msg,"\x49\x4f\x25\x64\x20\x28\x49\x44\x20\x25\x64\x29\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x72\x65\x74\x72\x69\x65\x76\x65\x20\x6d\x6f\x64\x75\x6c\x65\x20\x66\x72\x6f\x6d\x20\x72\x65\x67\x69\x73\x74\x72\x79\x20\x69\x6e\x20\x44\x41\x20\x4d\x6f\x64\x65\x6c\x53\x74\x65\x70" "\n",boardType,za0d38ae598);ssSetErrorStatus(S,msg);return;}for(i=(0xe19+5802-0x24c3);i<zf91d71c6d9;i++){index=(uint16_T)mxGetPr(z2b4281b393)[i]-(0x333+8174-0x2320);zc7fdaf6331=(real_T*)ssGetInputPortRealSignal(S,index);out=(int32_T)((zc7fdaf6331[(0x14f3+1304-0x1a0b)]+zae10e3f17f->zb817ad7ad6)*zae10e3f17f->z9fb53cdf50);if(out>65535)out=65535;if(out<(0xbb+7017-0x1c24))out=(0xd91+738-0x1073);zae10e3f17f->z3fad3d9764->data=out;}}static void sg_ModelStop(SimStruct*S){uint32_T za0d38ae598=((uint32_T)mxGetPr(ze13f49a01f)[(0x1a3c+3202-0x26be)]);uint32_T boardType=(uint32_T)mxGetScalar(z89d5fad8dc);SG_PRINTF(DEBUG,"\x44\x41\x3a\x20\x73\x67\x5f\x4d\x6f\x64\x65\x6c\x53\x74\x6f\x70" "\n");z0c4990fb68*zae10e3f17f=(z0c4990fb68*)sg_module_get_custom_data(boardType,za0d38ae598);if(!zae10e3f17f){sprintf(msg,"\x49\x4f\x25\x64\x20\x28\x49\x44\x20\x25\x64\x29\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x72\x65\x74\x72\x69\x65\x76\x65\x20\x6d\x6f\x64\x75\x6c\x65\x20\x66\x72\x6f\x6d\x20\x72\x65\x67\x69\x73\x74\x72\x79\x20\x69\x6e\x20\x44\x41\x20\x4d\x6f\x64\x65\x6c\x53\x74\x6f\x70" "\n",boardType,za0d38ae598);ssSetErrorStatus(S,msg);return;}zd98b6312f7(S,zae10e3f17f,(0x19d0+652-0x1c5c));}static void zd98b6312f7(SimStruct*S,z0c4990fb68*zae10e3f17f,int zb2d484c895){uint16_T i;int32_T out;uint16_T index;uint16_T zf91d71c6d9=(uint16_T)mxGetN(za9d8fb6bcf);for(i=(0x167b+3201-0x22fc);i<zf91d71c6d9;i++){if(zb2d484c895||(int)mxGetPr(zc8bbaa6115)[i]){index=(uint16_T)mxGetPr(z2b4281b393)[i]-(0x182+8100-0x2125);out=(int32_T)(((real_T)mxGetPr(zd8eb92e45e)[index]+zae10e3f17f->zb817ad7ad6)*zae10e3f17f->z9fb53cdf50);if(out>65535)out=65535;if(out<(0x1002+1953-0x17a3))out=(0xc8f+2279-0x1576);zae10e3f17f->z3fad3d9764->data=out;}}}
#endif 
#include "sg_sfcn_glue.h"   


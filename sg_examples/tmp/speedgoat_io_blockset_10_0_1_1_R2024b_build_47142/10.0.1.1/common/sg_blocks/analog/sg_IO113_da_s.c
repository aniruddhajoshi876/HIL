// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL    (0x9c4+2056-0x11ca)
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME     sg_IO113_da_s
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include "sg_io113_18.h"
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
#define ze13f49a01f           ssGetSFcnParam(S, (0x1052+1457-0x1603))
#define z2b4281b393               ssGetSFcnParam(S, (0x80b+3674-0x1664))
#define za9d8fb6bcf             ssGetSFcnParam(S, (0x1478+2766-0x1f44))
#define z8fd86139be               ssGetSFcnParam(S, (0x10c7+3928-0x201c))
#define z3832b85a32           ssGetSFcnParam(S, (0xd57+1095-0x119a))
#define z702a26a5e9                ssGetSFcnParam(S, (0x871+185-0x925))
#define z5317f28eb6           ssGetSFcnParam(S, (0x1a37+1792-0x2131))
#define za6b3fb79a3             ssGetSFcnParam(S, (0x66c+1893-0xdca))
#define zdf24515981                           ((0xa85+6665-0x2486))
#define z2e6483d505              ((0xbbf+1395-0x1132))
#define zc5ce4cb81a              ((0x11e3+1548-0x17ef))
#define z2b17e2ee3b              ((0x3e3+5832-0x1aab))
static char_T msg[(0x382+5957-0x19c7)];static void mdlInitializeSizes(SimStruct*S){uint32_T i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x1769+2368-0x20a9));ssSetNumDiscStates(S,(0x808+6897-0x22f9));if(!ssSetNumOutputPorts(S,(0xc26+1247-0x1105)))return;if(!ssSetNumInputPorts(S,(int)mxGetN(za9d8fb6bcf)))return;for(i=(0x2317+191-0x23d6);i<(int)mxGetN(za9d8fb6bcf);i++){ssSetInputPortWidth(S,i,(0x326+1847-0xa5c));ssSetInputPortDirectFeedThrough(S,i,(0x14c+3640-0xf83));ssSetInputPortRequiredContiguous(S,i,(0x895+6575-0x2243));}ssSetNumSampleTimes(S,(0x49f+7046-0x2024));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0xc09+5384-0x2111));ssSetNumNonsampledZCs(S,(0xd88+4604-0x1f84));for(i=(0xc61+4575-0x1e40);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x7d2+717-0xa9f));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0x12e5+2455-0x1c7c)]==-1.0){ssSetSampleTime(S,(0xb99+3655-0x19e0),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x3c7+8202-0x23d1),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x29f+1903-0xa0e),mxGetPr(z3832b85a32)[(0x234+988-0x610)]);ssSetOffsetTime(S,(0x304+8918-0x25da),0.0);}}
#ifndef MATLAB_MEX_FILE
static void z95e7ebbeb7(SimStruct*S,za7f5fcb87c*zae10e3f17f,int z4f19fbae54){uint16_T zf91d71c6d9=(uint16_T)mxGetN(za9d8fb6bcf);uint16_T i,index;uint32_T z7711a772ed;for(i=(0x1e5+1289-0x6ee);i<zf91d71c6d9;i++){if(!z4f19fbae54&&!(int)mxGetPr(za6b3fb79a3)[i])continue;index=(uint16_T)mxGetPr(z2b4281b393)[i]-(0x2198+954-0x2551);z7711a772ed=(uint32_T)(((real_T)mxGetPr(z5317f28eb6)[index]+zae10e3f17f->offset)*zae10e3f17f->z0754dd67cc);if(z7711a772ed>z7935114df5)z7711a772ed=z7935114df5;zae10e3f17f->z3fad3d9764[z6071a79265]=z7711a772ed;
#ifdef SG_DEBUG_PRINT
uint16_T channel=(uint16_T)mxGetPr(za9d8fb6bcf)[i]-(0x17b+5020-0x1516);SG_PRINTF(DEBUG,"\x25\x73\x3a\x20\x63\x68\x25\x75\x20\x25\x73\x20\x74\x6f\x20\x25\x66\x56\x20\x28\x25\x75\x29" "\n",DEVNAME,channel,z4f19fbae54?"\x69\x6e\x69\x74\x69\x61\x6c\x69\x73\x65\x64":"\x72\x65\x73\x65\x74",(real_T)mxGetPr(z5317f28eb6)[index],z7711a772ed);
#endif
}zae10e3f17f->z3fad3d9764[z307adcf8f5]|=(0x1u<<(0x1c3f+1869-0x2385))|(0x1u<<(0xff3+181-0x10a3));}static void sg_ModelLoad(SimStruct*S){uint32_T za0d38ae598=(uint32_T)mxGetPr(ze13f49a01f)[(0xa2+9405-0x255f)];za7f5fcb87c*zae10e3f17f=(za7f5fcb87c*)sg_module_get_custom_data(z12ba1d7c25,za0d38ae598);if(!zae10e3f17f){sprintf(msg,"\x25\x73\x20\x28\x49\x44\x20\x25\x75\x29\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x72\x65\x74\x72\x69\x65\x76\x65\x20\x6d\x6f\x64\x75\x6c\x65\x20\x69\x6e\x20\x44\x41\x20\x4d\x6f\x64\x65\x6c\x4c\x6f\x61\x64" "\n",DEVNAME,za0d38ae598);ssSetErrorStatus(S,msg);return;}z95e7ebbeb7(S,zae10e3f17f,(0xfaa+704-0x1269));}static void sg_ModelStart(SimStruct*S){}static void sg_ModelStep(SimStruct*S){uint16_T zf91d71c6d9=(uint16_T)mxGetN(za9d8fb6bcf);uint16_T i,index;real_T*zc7fdaf6331;int32_T out;uint32_T za0d38ae598=(uint32_T)mxGetPr(ze13f49a01f)[(0x518+4032-0x14d8)];za7f5fcb87c*zae10e3f17f=(za7f5fcb87c*)sg_module_get_custom_data(z12ba1d7c25,za0d38ae598);if(!zae10e3f17f){sprintf(msg,"\x25\x73\x20\x28\x49\x44\x20\x25\x75\x29\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x72\x65\x74\x72\x69\x65\x76\x65\x20\x6d\x6f\x64\x75\x6c\x65\x20\x69\x6e\x20\x44\x41\x20\x4d\x6f\x64\x65\x6c\x53\x74\x65\x70" "\n",DEVNAME,za0d38ae598);ssSetErrorStatus(S,msg);return;}for(i=(0x156b+3694-0x23d9);i<zf91d71c6d9;i++){index=(uint16_T)mxGetPr(z2b4281b393)[i]-(0xfad+1494-0x1582);zc7fdaf6331=(real_T*)ssGetInputPortRealSignal(S,index);out=(int32_T)((zc7fdaf6331[(0x189c+1007-0x1c8b)]+zae10e3f17f->offset)*zae10e3f17f->z0754dd67cc);if(out>(int32_T)z7935114df5)out=(int32_T)z7935114df5;else if(out<(0x862+7574-0x25f8))out=(0x1279+3631-0x20a8);zae10e3f17f->z3fad3d9764[z6071a79265]=(uint32_T)out;}zae10e3f17f->z3fad3d9764[z307adcf8f5]|=(0x1u<<(0x2a8+4535-0x1458))|(0x1u<<(0x11f+9119-0x24b9));}static void sg_ModelStop(SimStruct*S){uint32_T za0d38ae598=(uint32_T)mxGetPr(ze13f49a01f)[(0xa9d+5294-0x1f4b)];za7f5fcb87c*zae10e3f17f=(za7f5fcb87c*)sg_module_get_custom_data(z12ba1d7c25,za0d38ae598);if(!zae10e3f17f){sprintf(msg,"\x25\x73\x20\x28\x49\x44\x20\x25\x75\x29\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x72\x65\x74\x72\x69\x65\x76\x65\x20\x6d\x6f\x64\x75\x6c\x65\x20\x69\x6e\x20\x44\x41\x20\x4d\x6f\x64\x65\x6c\x53\x74\x6f\x70" "\n",DEVNAME,za0d38ae598);ssSetErrorStatus(S,msg);return;}z95e7ebbeb7(S,zae10e3f17f,(0x1434+4670-0x2672));}
#endif 
#include "sg_sfcn_glue.h"   


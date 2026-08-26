// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL    (0x6b3+1933-0xe3e)
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME     sg_IO117_ad_s
#include "sg_io117.h"
#include "sg_io117_error.h"
#ifdef MATLAB_MEX_FILE
#include "mex.h"
#else
#include "sg_common.h"
#include "sg_printf.h"
#include "sg_module_registry.h"
#include "sg_module_types.h"
#endif
#include "sg_callback.h"
enum zbb18ad4e15{z9c785bce48=(0x1340+1430-0x18d6),z7380b0f336,z68a4e5dee8,z43a460ca9d,zd29409c1b8,z0503ea7bdd,zbfbc2a9fe6,z2041d72f5c};
#define zc7d8502b91           ssGetSFcnParam(S, z9c785bce48)
#define za7bf7122c6            ssGetSFcnParam(S, z7380b0f336)
#define za2c6d5f765         ssGetSFcnParam(S, z68a4e5dee8)
#define z3a92bf64d8        ssGetSFcnParam(S, z43a460ca9d)
#define z7eaaaf8104       ssGetSFcnParam(S, zd29409c1b8)
#define z1720d3154c      ssGetSFcnParam(S, z0503ea7bdd)
#define z8ca82ce659           ssGetSFcnParam(S, zbfbc2a9fe6)
enum z6070f8b59b{z32297f1282=(0x5db+5815-0x1c92)};enum z61bde0e0ae{z81b97a1b0d=(0x11a3+4032-0x2163)};enum z57e26ce0cd{zbeb0b06c22=(0x2c6+3647-0x1105)};
#ifndef MATLAB_MEX_FILE
static void zba3524f24b(SimStruct*S);
#endif
static char_T z5d418554e0[(0x1bb+3649-0xf7c)];static void mdlInitializeSizes(SimStruct*S){int_T i=(0x6fc+4269-0x17a9);int_T za56cbc2a4d=(0x1b18+2007-0x22ef);ssSetNumSFcnParams(S,z2041d72f5c);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(z5d418554e0,"\x49\x6e\x20\x49\x4f\x31\x31\x37\x2c\x20\x41\x6e\x61\x6c\x6f\x67\x20\x69\x6e\x70\x75\x74\x20\x62\x6c\x6f\x63\x6b\x2c\x20\x49\x44\x20\x25\x64\x3a\x20\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n""\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64\x2e" "\n",(int_T)mxGetScalar(zc7d8502b91),z2041d72f5c);ssSetErrorStatus(S,z5d418554e0);return;}ssSetNumContStates(S,(0x1e39+1161-0x22c2));ssSetNumDiscStates(S,(0x8c0+5856-0x1fa0));if(!ssSetNumInputPorts(S,(0x497+4896-0x17b7)))return;za56cbc2a4d=(int_T)mxGetN(z3a92bf64d8);if(!ssSetNumOutputPorts(S,za56cbc2a4d))return;for(i=(0x1d6b+1530-0x2365);i<za56cbc2a4d;i++){ssSetOutputPortWidth(S,i,(0x729+6275-0x1fab));}ssSetNumSampleTimes(S,(0xd13+1685-0x13a7));ssSetNumRWork(S,z81b97a1b0d);ssSetNumIWork(S,z32297f1282);ssSetNumPWork(S,zbeb0b06c22);ssSetNumModes(S,(0x651+8054-0x25c7));ssSetNumNonsampledZCs(S,(0xda4+6387-0x2697));for(i=(0x145a+4774-0x2700);i<z2041d72f5c;i++){ssSetSFcnParamTunable(S,i,SS_PRM_NOT_TUNABLE);}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetScalar(za2c6d5f765)==-1.0){ssSetSampleTime(S,(0x159+7941-0x205e),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x1956+999-0x1d3d),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0xd09+492-0xef5),mxGetScalar(za2c6d5f765));ssSetOffsetTime(S,(0x18c5+1237-0x1d9a),0.0);}}
#ifndef MATLAB_MEX_FILE
static void sg_ModelLoad(SimStruct*S){}static void sg_ModelStart(SimStruct*S){}static void sg_ModelStep(SimStruct*S){uint32_T zc3ac25f204=((int_T)mxGetPr(zc7d8502b91)[(0x18a3+2193-0x2134)]);int_T i;real_T*out;zecc5e49691*zae10e3f17f=(zecc5e49691*)sg_module_get_custom_data(z12ba1d7c25,zc3ac25f204);if(!zae10e3f17f){z0b799d87d7("\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x72\x65\x74\x72\x69\x65\x76\x65\x20\x6d\x6f\x64\x75\x6c\x65\x20\x66\x72\x6f\x6d\x20\x72\x65\x67\x69\x73\x74\x72\x79\x20\x69\x6e\x20\x41\x44\x20\x4d\x6f\x64\x65\x6c\x53\x74\x65\x70" "\n");zba3524f24b(S);return;}for(i=(0xefd+1520-0x14ed);i<(zae10e3f17f->z0c3eef007f+(0x1690+253-0x178c));i++){if(z2f30a295d4(zae10e3f17f,z16682623a4,zc5e9895f63,z907277d41e)){z0b799d87d7("\x54\x69\x6d\x65\x6f\x75\x74\x20\x64\x75\x72\x69\x6e\x67\x20\x64\x61\x74\x61\x20\x61\x63\x71\x75\x69\x73\x69\x74\x69\x6f\x6e");zba3524f24b(S);return;}z9d01a45f9b(zae10e3f17f,z26e2f0437a,z1a15806673);if(i<(zae10e3f17f->z0c3eef007f-(0xd5f+5116-0x215a))){z9d01a45f9b(zae10e3f17f,zbb6f9b10be,zae10e3f17f->z4648a2f958[i+(0x1e2+4083-0x11d4)]);}else if(i==(zae10e3f17f->z0c3eef007f-(0x503+7861-0x23b7))){z9d01a45f9b(zae10e3f17f,zbb6f9b10be,zae10e3f17f->z4648a2f958[(0x1524+1731-0x1be7)]);}else{}if(z2f30a295d4(zae10e3f17f,z16682623a4,zf60f04aedc,z907277d41e)){z0b799d87d7("\x54\x69\x6d\x65\x6f\x75\x74\x20\x64\x75\x72\x69\x6e\x67\x20\x64\x61\x74\x61\x20\x61\x63\x71\x75\x69\x73\x69\x74\x69\x6f\x6e");zba3524f24b(S);return;}if(i>(0x9e4+80-0xa34)){out=(real_T*)ssGetOutputPortSignal(S,i-(0x2380+692-0x2633));if((int_T)mxGetScalar(z8ca82ce659)==(0x1299+38-0x12be)){*out=(int16_T)zc41552c420(zae10e3f17f,z9dd1a3523f)*zae10e3f17f->ze47081d006[i-(0x1c3+7343-0x1e71)].z0754dd67cc-zae10e3f17f->ze47081d006[i-(0x17db+3411-0x252d)].offset;*out*=zae10e3f17f->z32b35fb51b[i-(0xbac+5065-0x1f74)];}else{*out=(int16_T)zc41552c420(zae10e3f17f,z9dd1a3523f)*zae10e3f17f->z32b35fb51b[i-(0xd27+1414-0x12ac)];}}}}static void sg_ModelStop(SimStruct*S){}static void zba3524f24b(SimStruct*S){const char_T*zd1826cf292="\x41\x6e\x61\x6c\x6f\x67\x20\x69\x6e\x70\x75\x74";const int_T zc3ac25f204=(int_T)mxGetScalar(zc7d8502b91);const char_T*zd990b1a163=z620c52af23(zd1826cf292,zc3ac25f204);ssSetErrorStatus(S,zd990b1a163);}
#endif  
#include "sg_sfcn_glue.h"   


// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL    (0x602+1132-0xa6c)
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME     sg_IO191_di_s
#include "sg_io191.h"
#ifdef MATLAB_MEX_FILE
#include "mex.h"
#else
#include "sg_common.h"
#include "sg_printf.h"
#include "sg_module_types.h"
#include "sg_module_registry.h"
static const int z0e14cce82f=z3cbf6b0256;
#endif
#define SG_EARLY_INIT   
#include "sg_callback.h"
#define ze13f49a01f           ssGetSFcnParam(S, (0xb12+7076-0x26b6))
#define z3832b85a32           ssGetSFcnParam(S, (0x57a+1772-0xc65))
#define z702a26a5e9                ssGetSFcnParam(S, (0x220d+287-0x232a))
#define zb18e38a301           ssGetSFcnParam(S, (0x485+2608-0xeb2))
#define z9197f08e0c           ssGetSFcnParam(S, (0x130b+2487-0x1cbe))
#define z4848d060ef           ssGetSFcnParam(S, (0x41f+2197-0xcaf))
#define zdf24515981                           ((0x1e68+96-0x1ec2))
#define z2e6483d505              ((0x921+4053-0x18f6))
#define zc5ce4cb81a              ((0x313+5000-0x169b))
#define z2b17e2ee3b              ((0x1b5c+132-0x1be0))
static char msg[z71934bf57c];static void mdlInitializeSizes(SimStruct*S){ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x3f2+6043-0x1b8d));ssSetNumDiscStates(S,(0x508+802-0x82a));if(!ssSetNumInputPorts(S,(0x7ea+4908-0x1b16)))return;uint8_t z336107e3a8=(uint8_t)mxGetPr(z9197f08e0c)[(0x9e1+722-0xcb3)];uint8_t ze97179dd68=(uint8_t)mxGetPr(z4848d060ef)[(0x1209+1947-0x19a4)];switch(z336107e3a8){case(0x958+2572-0x1363):if(!ssSetNumOutputPorts(S,(0x638+7743-0x2476)))return;ssSetOutputPortWidth(S,(0x918+266-0xa22),(0x914+6594-0x22c6));switch(ze97179dd68){case(0x1168+2241-0x1a28):ssSetOutputPortDataType(S,(0xbe9+1239-0x10c0),SS_DOUBLE);break;case(0x7a4+2888-0x12ea):ssSetOutputPortDataType(S,(0x1060+3863-0x1f77),SS_BOOLEAN);break;}break;case(0x14aa+46-0x14d6):if(!ssSetNumOutputPorts(S,(int)mxGetN(zb18e38a301)))return;for(int i=(0x617+7045-0x219c);i<(int)mxGetN(zb18e38a301);i++){ssSetOutputPortWidth(S,i,(0x5ea+8103-0x2590));switch(ze97179dd68){case(0x10fb+3959-0x2071):ssSetOutputPortDataType(S,i,SS_DOUBLE);break;case(0xd40+6156-0x254a):ssSetOutputPortDataType(S,i,SS_BOOLEAN);break;}}break;}ssSetNumSampleTimes(S,(0x902+3620-0x1725));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x1d1d+60-0x1d59));ssSetNumNonsampledZCs(S,(0xf3c+5440-0x247c));for(int i=(0x1671+2405-0x1fd6);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x639+2797-0x1126));}ssSetOptions(S,SS_OPTION_DISALLOW_CONSTANT_SAMPLE_TIME|SS_OPTION_EXCEPTION_FREE_CODE|SS_OPTION_RUNTIME_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0x24c+370-0x3be)]==-1.0){ssSetSampleTime(S,(0x15+4488-0x119d),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0xfff+4853-0x22f4),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0xf6c+3535-0x1d3b),mxGetPr(z3832b85a32)[(0xa9a+1582-0x10c8)]);ssSetOffsetTime(S,(0x505+1989-0xcca),0.0);}ssSetModelReferenceSampleTimeDefaultInheritance(S);}
#ifndef MATLAB_MEX_FILE
static void sg_ModelLoad(SimStruct*S){}static void sg_ModelStart(SimStruct*S){}static void sg_ModelStep(SimStruct*S){uint32_t input;uint32_t channel;double*z523150ed5d;bool*zdf4e20019d;z883f474cfe*zae10e3f17f=NULL;uint32_t za0d38ae598;uint8_t z336107e3a8=(uint8_t)mxGetPr(z9197f08e0c)[(0xa52+6918-0x2558)];uint8_t ze97179dd68=(uint8_t)mxGetPr(z4848d060ef)[(0xc72+4535-0x1e29)];za0d38ae598=((uint32_t)mxGetPr(ze13f49a01f)[(0x1c0+8650-0x238a)]);zae10e3f17f=(z883f474cfe*)sg_module_get_custom_data(z0e14cce82f,za0d38ae598);if(!zae10e3f17f){sprintf(msg,"\x25\x73\x20\x28\x49\x44\x20\x25\x64\x29\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x72\x65\x74\x72\x69\x65\x76\x65\x20\x6d\x6f\x64\x75\x6c\x65\x20\x66\x72\x6f\x6d\x20\x72\x65\x67\x69\x73\x74\x72\x79\x20\x69\x6e\x20\x44\x49\x20\x4d\x6f\x64\x65\x6c\x53\x74\x65\x70" "\n",DEVNAME,za0d38ae598);ssSetErrorStatus(S,msg);return;}input=zae10e3f17f->z27fd94ac66->z6b1be4e609;switch(z336107e3a8){case(0xe3f+4507-0x1fd9):switch(ze97179dd68){case(0x176b+3932-0x26c6):z523150ed5d=ssGetOutputPortSignal(S,(0xc51+4189-0x1cae));for(uint32_t i=(0x1bab+1525-0x21a0);i<(0x157+6854-0x1c0d);i++){z523150ed5d[i]=(input&((0xc9f+2153-0x1507)<<i))?1.0:0.0;}break;case(0xdf2+5476-0x2354):zdf4e20019d=ssGetOutputPortSignal(S,(0x95+2622-0xad3));for(uint32_t i=(0x22b+7069-0x1dc8);i<(0x1f19+36-0x1f2d);i++){zdf4e20019d[i]=(input&((0x123d+1365-0x1791)<<i))?1.0:0.0;}break;}break;case(0xe33+2086-0x1657):for(uint32_t i=(0x2d9+2108-0xb15);i<(uint32_t)mxGetN(zb18e38a301);i++){channel=(uint32_t)mxGetPr(zb18e38a301)[i]-(0x1cc5+450-0x1e86);switch(ze97179dd68){case(0xbff+3194-0x1878):z523150ed5d=ssGetOutputPortSignal(S,i);z523150ed5d[(0x16a5+3144-0x22ed)]=(input&((0x1560+4283-0x261a)<<channel))?1.0:0.0;break;case(0x13ec+935-0x1791):zdf4e20019d=ssGetOutputPortSignal(S,i);zdf4e20019d[(0x1580+4459-0x26eb)]=(input&((0x1559+1697-0x1bf9)<<channel))?1.0:0.0;break;}}break;}}static void sg_ModelStop(SimStruct*S){}
#endif  
#include "sg_sfcn_glue.h"   


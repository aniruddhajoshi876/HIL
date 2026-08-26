// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL    (0x1074+3292-0x1d4e)
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME     sg_io623_send_s
#include "simstruc.h"
#ifdef MATLAB_MEX_FILE
#include "mex.h"
#else
#include "IoModuleRegistry.h"
#endif
#include "sg_callback.h"
#include "sg_mask_init.h"
#include "sg_param.h"
#include "sg_printf.h"
#include "Io623Module.h"
enum ze78e16dd0b{zc7d8502b91,zb573e5d54b,z00e5939a5d,zd404a05677,za2c6d5f765,z2041d72f5c};enum zbb1f615c1d{z32297f1282};enum z93bcf30780{z81b97a1b0d};enum zb06a9f15ae{zbeb0b06c22};static void z16c5d92797(SimStruct*S,sg::zd43ee5c691*zae10e3f17f);static void ze335a86a93(SimStruct*S,zb40709057e*params);static void z25874d50af(const zb40709057e*params);static void mdlInitializeSizes(SimStruct*S){SgMaskInit_SetupSettingsArgs args;args.numberOfParams=z2041d72f5c;args.integerWorkVecLength=z32297f1282;args.realWorkVecLength=z81b97a1b0d;args.pointerWorkVecLength=zbeb0b06c22;if(sgMaskInit_initSizesForRegularBlock(S,&args)){static char z658c413ec2[(0x13d8+1426-0x18ea)];sprintf(z658c413ec2,"\x49\x6e\x20\x49\x4f\x36\x32\x33\x2c\x20\x53\x65\x6e\x64\x20\x62\x6c\x6f\x63\x6b\x2c\x20\x49\x44\x20\x25\x64\x3a\x20\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n""\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64\x2e",sgParam_getInt(S,zc7d8502b91),z2041d72f5c);ssSetErrorStatus(S,z658c413ec2);return;}int z7af9cda755=sgParam_getInt(S,zd404a05677);sgMaskInit_setInputPorts(S,(0x1020+5794-0x26c1),z7af9cda755);ssSetInputPortDataType(S,(0x933+3734-0x17c9),SS_UINT16);sgMaskInit_setNoOutputPorts(S);}static void mdlInitializeSampleTimes(SimStruct*S){double sampleTime=sgParam_getDouble(S,za2c6d5f765);sgMaskInit_initSampleTimesForRegularBlock(S,sampleTime);}static void sg_ModelLoad(SimStruct*S){}static void sg_ModelStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
int moduleId=sgParam_getInt(S,zc7d8502b91);sg::zd43ee5c691*zae10e3f17f=static_cast<sg::zd43ee5c691*>(sg::IoModuleRegistry::find(sg::ModuleTypes::zda9a6809a6,moduleId));if(zae10e3f17f==nullptr){zae10e3f17f=new sg::zd43ee5c691(moduleId);zae10e3f17f->z798a78318b("\x49\x6e\x20\x49\x4f\x36\x32\x33\x2c\x20\x53\x65\x6e\x64\x20\x62\x6c\x6f\x63\x6b\x2c\x20\x49\x44\x20\x25\x64\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x72\x65\x74\x72\x65\x69\x76\x65\x20\x6d\x6f\x64\x65\x6c\x20\x66\x72\x6f\x6d\x20\x72\x65\x67\x69\x73\x74\x72\x79\x20\x69\x6e\x20\x4d\x6f\x64\x65\x6c\x53\x74\x61\x72\x74\x2e" "\n",moduleId);z16c5d92797(S,zae10e3f17f);return;}SG_PRINTF(DEBUG,"\x49\x4f\x36\x32\x33\x2c\x20\x53\x65\x6e\x64\x20\x62\x6c\x6f\x63\x6b\x2c\x20\x49\x44\x3a\x20\x25\x64" "\n",moduleId);ze335a86a93(S,&zae10e3f17f->zdf8f47045e);z25874d50af(&zae10e3f17f->zdf8f47045e);if(!zae10e3f17f->zc8c1fb94ca(zae10e3f17f->zdf8f47045e.cc-(0x14b+8501-0x227f),zae10e3f17f->zdf8f47045e.zacf2715ec1)){zae10e3f17f->z798a78318b("\x4e\x6f\x20\x6d\x65\x73\x73\x61\x67\x65\x20\x62\x75\x66\x66\x65\x72\x20\x25\x64\x20\x6f\x6e\x20\x43\x43\x25\x64\x20\x63\x6f\x6e\x66\x69\x67\x75\x72\x65\x64\x2e",zae10e3f17f->zdf8f47045e.zacf2715ec1,zae10e3f17f->zdf8f47045e.cc);z16c5d92797(S,zae10e3f17f);return;}
#endif  
}static void sg_ModelStep(SimStruct*S){
#ifndef MATLAB_MEX_FILE
int moduleId=sgParam_getInt(S,zc7d8502b91);sg::zd43ee5c691*zae10e3f17f=static_cast<sg::zd43ee5c691*>(sg::IoModuleRegistry::find(sg::ModuleTypes::zda9a6809a6,moduleId));if(zae10e3f17f==nullptr){zae10e3f17f=new sg::zd43ee5c691(moduleId);zae10e3f17f->z798a78318b("\x49\x6e\x20\x49\x4f\x36\x32\x33\x2c\x20\x53\x65\x6e\x64\x20\x62\x6c\x6f\x63\x6b\x2c\x20\x49\x44\x20\x25\x64\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x72\x65\x74\x72\x65\x69\x76\x65\x20\x6d\x6f\x64\x65\x6c\x20\x66\x72\x6f\x6d\x20\x72\x65\x67\x69\x73\x74\x72\x79\x20\x69\x6e\x20\x4d\x6f\x64\x65\x6c\x53\x74\x65\x70\x2e" "\n",moduleId);z16c5d92797(S,zae10e3f17f);return;}uint16_t*z146460d588=static_cast<uint16_t*>(const_cast<void*>(ssGetInputPortSignal(S,(0x1bd3+2030-0x23c1))));int cc=zae10e3f17f->zdf8f47045e.cc-(0x19ba+2621-0x23f6);if(zae10e3f17f->zf96e9b1966(cc,zae10e3f17f->zdf8f47045e.zacf2715ec1,z146460d588,zae10e3f17f->zdf8f47045e.z8ac130b21e)){z16c5d92797(nullptr,zae10e3f17f);return;}
#endif  
}static void sg_ModelStop(SimStruct*S){}static void z16c5d92797(SimStruct*S,sg::zd43ee5c691*zae10e3f17f){const char*z4576acf721=zae10e3f17f->z3af791a73f("\x53\x65\x6e\x64");if(S==nullptr){SG_PRINTF(WARNING,"\x25\x73" "\n",z4576acf721);}else{ssSetErrorStatus(S,z4576acf721);return;}}static void ze335a86a93(SimStruct*S,zb40709057e*params){params->moduleId=sgParam_getInt(S,zc7d8502b91);params->cc=sgParam_getInt(S,zb573e5d54b);params->zacf2715ec1=sgParam_getInt(S,z00e5939a5d);params->z8ac130b21e=sgParam_getInt(S,zd404a05677);params->sampleTime=sgParam_getInt(S,za2c6d5f765);}static void z25874d50af(const zb40709057e*params){SG_PARAM_PRINT_INT(params,moduleId);SG_PARAM_PRINT_INT(params,cc);SG_PARAM_PRINT_INT(params,zacf2715ec1);SG_PARAM_PRINT_INT(params,z8ac130b21e);SG_PARAM_PRINT_INT(params,sampleTime);}
#include "sg_sfcn_glue.h"   


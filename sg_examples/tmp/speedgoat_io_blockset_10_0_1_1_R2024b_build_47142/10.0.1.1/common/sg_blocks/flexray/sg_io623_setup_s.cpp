// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL    (0x1c17+1349-0x215a)
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME     sg_io623_setup_s
#include <stdio.h>
#include "simstruc.h"
#ifdef MATLAB_MEX_FILE
#include "mex.h"
#else
#include "IoModuleRegistry.h"
#endif
#define SG_HAS_MDL_EXIT 
#define SG_EARLY_INIT   
#include "sg_callback.h"
#include "sg_mask_init.h"
#include "sg_param.h"
#include "sg_printf.h"
#include "Io623Module.h"
enum zdca05d7df4{zc7d8502b91,za7bf7122c6,z3b2ca49b81,za42e75771c,z1988ad2ba5,z1d5352ef59,z6192027552,z820204dc2d,z2041d72f5c};enum zbb1f615c1d{z32297f1282};enum z93bcf30780{z81b97a1b0d};enum zb06a9f15ae{zbeb0b06c22,};static void z16c5d92797(SimStruct*S,sg::zd43ee5c691*zae10e3f17f);static void z33b5ae86ac(SimStruct*S,z13d0aa5fbb*params);static void z245c751b2b(z13d0aa5fbb*params);static void zdcc579ab16(const z13d0aa5fbb*params);static void mdlInitializeSizes(SimStruct*S){SgMaskInit_SetupSettingsArgs args;args.numberOfParams=z2041d72f5c;args.integerWorkVecLength=z32297f1282;args.realWorkVecLength=z81b97a1b0d;args.pointerWorkVecLength=zbeb0b06c22;if(sgMaskInit_initSizesForSetupBlock(S,&args)){static char z658c413ec2[(0x178b+1455-0x1cba)];sprintf(z658c413ec2,"\x49\x6e\x20\x49\x4f\x36\x32\x33\x2c\x20\x53\x65\x74\x75\x70\x20\x62\x6c\x6f\x63\x6b\x2c\x20\x49\x44\x20\x25\x64\x3a\x20\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n""\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64\x2e" "\n",sgParam_getInt(S,zc7d8502b91),z2041d72f5c);ssSetErrorStatus(S,z658c413ec2);return;}}static void mdlInitializeSampleTimes(SimStruct*S){sgMaskInit_initSampleTimesForSetupBlock(S);}static void sg_ModelLoad(SimStruct*S){
#ifndef MATLAB_MEX_FILE
int moduleId=sgParam_getInt(S,zc7d8502b91);SG_PRINTF(INFO,"\x53\x70\x65\x65\x64\x67\x6f\x61\x74\x20\x49\x4f\x36\x32\x33\x2c\x20\x49\x44\x3a\x20\x25\x64\x2c\x20" "\n",moduleId);SG_PRINTF(DEBUG,"\x53\x65\x74\x75\x70\x20\x62\x6c\x6f\x63\x6b" "\n");sg::zd43ee5c691*zae10e3f17f=static_cast<sg::zd43ee5c691*>(sg::IoModuleRegistry::find(sg::ModuleTypes::zda9a6809a6,moduleId));if(zae10e3f17f==nullptr){zae10e3f17f=new sg::zd43ee5c691(moduleId);sg::IoModuleRegistry::add(zae10e3f17f);}z33b5ae86ac(S,&zae10e3f17f->z3e96791c0d);zdcc579ab16(&zae10e3f17f->z3e96791c0d);if(zae10e3f17f->init(zae10e3f17f->z3e96791c0d.zfba97307b4)){z16c5d92797(S,zae10e3f17f);return;}if(zae10e3f17f->z13e569b276()){z16c5d92797(S,zae10e3f17f);return;}SG_PRINTF(INFO,"\x49\x6e\x69\x74\x69\x61\x6c\x69\x7a\x61\x74\x69\x6f\x6e\x20\x4f\x4b" "\n");
#endif  
}static void sg_ModelStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
int moduleId=sgParam_getInt(S,zc7d8502b91);sg::zd43ee5c691*zae10e3f17f=static_cast<sg::zd43ee5c691*>(sg::IoModuleRegistry::find(sg::ModuleTypes::zda9a6809a6,moduleId));if(zae10e3f17f==nullptr){zae10e3f17f=new sg::zd43ee5c691(zae10e3f17f->z3e96791c0d.moduleId);zae10e3f17f->z798a78318b("\x49\x6e\x20\x49\x4f\x36\x32\x33\x2c\x20\x53\x65\x74\x75\x70\x20\x62\x6c\x6f\x63\x6b\x2c\x20\x49\x44\x20\x25\x64\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x72\x65\x74\x72\x65\x69\x76\x65\x20\x6d\x6f\x64\x65\x6c\x20\x66\x72\x6f\x6d\x20\x72\x65\x67\x69\x73\x74\x72\x79\x20\x69\x6e\x20\x4d\x6f\x64\x65\x6c\x53\x74\x61\x72\x74\x2e" "\n",moduleId);z16c5d92797(S,zae10e3f17f);return;}for(int i=(0x8c+5202-0x14de);i<zae10e3f17f->z3e96791c0d.z3af98d0046->len;i++){if(zae10e3f17f->z3e96791c0d.z3af98d0046->val[i]){if(zae10e3f17f->zed4044b959(i,zae10e3f17f->z3e96791c0d.z4bbe48c546[i])){z16c5d92797(S,zae10e3f17f);return;}}}if(zae10e3f17f->za3b9e36c6f(zae10e3f17f->z3e96791c0d.zdc7a2ff6e0)){z16c5d92797(S,zae10e3f17f);return;}
#endif  
}static void sg_ModelStep(SimStruct*S){}static void sg_ModelStop(SimStruct*S){}static void sg_ModelExit(SimStruct*S){
#ifndef MATLAB_MEX_FILE
int moduleId=sgParam_getInt(S,zc7d8502b91);sg::zd43ee5c691*zae10e3f17f=static_cast<sg::zd43ee5c691*>(sg::IoModuleRegistry::find(sg::ModuleTypes::zda9a6809a6,moduleId));if(zae10e3f17f==nullptr){zae10e3f17f=new sg::zd43ee5c691(moduleId);zae10e3f17f->z798a78318b("\x49\x6e\x20\x49\x4f\x36\x32\x33\x2c\x20\x53\x65\x74\x75\x70\x20\x62\x6c\x6f\x63\x6b\x2c\x20\x49\x44\x20\x25\x64\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x72\x65\x74\x72\x65\x69\x76\x65\x20\x6d\x6f\x64\x65\x6c\x20\x66\x72\x6f\x6d\x20\x72\x65\x67\x69\x73\x74\x72\x79\x20\x69\x6e\x20\x4d\x6f\x64\x65\x6c\x45\x78\x69\x74\x2e" "\n",moduleId);z16c5d92797(S,zae10e3f17f);return;}z245c751b2b(&zae10e3f17f->z3e96791c0d);if(zae10e3f17f->zfdda11441c()){z16c5d92797(S,zae10e3f17f);return;}
#endif  
}static void z16c5d92797(SimStruct*S,sg::zd43ee5c691*zae10e3f17f){ssSetErrorStatus(S,zae10e3f17f->z3af791a73f("\x53\x65\x74\x75\x70"));return;}static void z33b5ae86ac(SimStruct*S,z13d0aa5fbb*params){params->moduleId=sgParam_getInt(S,zc7d8502b91);params->zfba97307b4=sgParam_newIntVec(S,za7bf7122c6);params->z3af98d0046=sgParam_newBoolVec(S,z3b2ca49b81);params->z4bbe48c546[(0x1fa+4472-0x1372)]=sgParam_newCharVec(S,za42e75771c);params->z4bbe48c546[(0x88d+1864-0xfd4)]=sgParam_newCharVec(S,z1988ad2ba5);params->z4bbe48c546[(0xc0f+2835-0x1720)]=sgParam_newCharVec(S,z1d5352ef59);params->z4bbe48c546[(0x16d6+2646-0x2129)]=sgParam_newCharVec(S,z6192027552);params->zdc7a2ff6e0=sgParam_newBoolVec(S,z820204dc2d);return;}static void z245c751b2b(z13d0aa5fbb*params){sgParam_deleteIntVec(params->zfba97307b4);sgParam_deleteBoolVec(params->z3af98d0046);sgParam_deleteCharVec(params->z4bbe48c546[(0x1366+4798-0x2624)]);sgParam_deleteCharVec(params->z4bbe48c546[(0xa53+340-0xba6)]);sgParam_deleteCharVec(params->z4bbe48c546[(0xc4b+3008-0x1809)]);sgParam_deleteCharVec(params->z4bbe48c546[(0xf1a+2414-0x1885)]);sgParam_deleteBoolVec(params->zdc7a2ff6e0);}static void zdcc579ab16(const z13d0aa5fbb*params){SG_PARAM_PRINT_INT(params,moduleId);SG_PARAM_PRINT_INT_VEC(params,zfba97307b4);SG_PARAM_PRINT_BOOL_VEC(params,z3af98d0046);SG_PARAM_PRINT_CHAR_VEC(params,z4bbe48c546[(0x90f+5599-0x1eee)]);SG_PARAM_PRINT_CHAR_VEC(params,z4bbe48c546[(0x4e4+7560-0x226b)]);SG_PARAM_PRINT_CHAR_VEC(params,z4bbe48c546[(0x2bf+1686-0x953)]);SG_PARAM_PRINT_CHAR_VEC(params,z4bbe48c546[(0x17af+962-0x1b6e)]);SG_PARAM_PRINT_BOOL_VEC(params,zdc7a2ff6e0);}
#include "sg_sfcn_glue.h"   


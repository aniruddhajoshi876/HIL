// Copyright 2006-2026 Speedgoat GmbH

#pragma once
#include "simstruc.h"
#ifdef MATLAB_MEX_FILE
#include "mex.h"
#else
#include "sg_common.h"
#include <errno.h>
#endif
#include "sg_printf.h"
#include "sg_module_types.h"
#include "sg_time.h"
#include <stdlib.h>
#include <stdio.h>
#include "IO601_fcn.h"
#include "IO601_datatypes.h"
#include "IO601_iConcurrentExecution.h"
#include "../include/CAN_Message_Definition.h"
#include "../include/LIN_Message_Definition.h"
#define z508028c6d3 (0x2f0+4245-0x1385)
#define ze6b81d1e11 (0x1ad7+473-0x1cb0)
#define za4418501d4 (0xac+1086-0x4ea)
#define z401b532867 (0x186b+2151-0x20d1)
#define zecb096c322 (0xc19+6607-0x25e6)
static int SetAndCheckSFunctionParams(uint8_T ze58e331f42,SimStruct*S,int za20737d291){int i=(0x1fb8+1326-0x24e6);ssSetNumSFcnParams(S,za20737d291);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){return(0x1a89+1832-0x21b1);}for(i=(0x5b2+8454-0x26b8);i<za20737d291;i++){ssSetSFcnParamTunable(S,i,ze58e331f42);}return(0x1129+359-0x128f);}static void CreateSFunctionInputPorts(int zcf9aed83ba,SimStruct*S){ssSetNumInputPorts(S,zcf9aed83ba);}static int CheckSFunctionInputPorts(int zcf9aed83ba,SimStruct*S){if(zcf9aed83ba!=ssGetNumInputPorts(S)){return(0x1265+4540-0x2421);}return(0x90f+6531-0x2291);}static void SetSFunctionInputPortProperties(int_T z7da5ab49fa,uint32_T zbc29571b7b,BuiltInDTypeId ze97179dd68,boolean_T z5cda1a8b01,boolean_T zbac08145fb,uint8_T z2548e6cd9c,SimStruct*S){if((0xc5+5108-0x14b8)==z2548e6cd9c){ssSetInputPortWidth(S,z7da5ab49fa,zbc29571b7b);}else if((0xec4+90-0xf1c)==z2548e6cd9c){ssSetInputPortDataType(S,z7da5ab49fa,ze97179dd68);}else if((0x19af+3087-0x25bb)==z2548e6cd9c){ssSetInputPortRequiredContiguous(S,z7da5ab49fa,z5cda1a8b01);}else if((0x1d55+1464-0x2309)==z2548e6cd9c){ssSetInputPortDirectFeedThrough(S,z7da5ab49fa,zbac08145fb);}else{ssSetInputPortWidth(S,z7da5ab49fa,zbc29571b7b);ssSetInputPortDataType(S,z7da5ab49fa,ze97179dd68);ssSetInputPortRequiredContiguous(S,z7da5ab49fa,z5cda1a8b01);ssSetInputPortDirectFeedThrough(S,z7da5ab49fa,zbac08145fb);}}static void CreateSFunctionOutputPorts(int z7f34f9d205,SimStruct*S){ssSetNumOutputPorts(S,z7f34f9d205);}static int CheckSFunctionOutputPorts(int z7f34f9d205,SimStruct*S){if(z7f34f9d205!=ssGetNumOutputPorts(S)){return(0x842+7060-0x23d6);}return(0x7a6+1026-0xba7);}static void SetSFunctionOutputPortProperties(int z7da5ab49fa,int32_T zbc29571b7b,BuiltInDTypeId ze97179dd68,uint8_T z2548e6cd9c,SimStruct*S){if((0x28f+7528-0x1ff6)==z2548e6cd9c){ssSetOutputPortWidth(S,z7da5ab49fa,zbc29571b7b);}else if((0xd66+4959-0x20c3)==z2548e6cd9c){ssSetOutputPortDataType(S,z7da5ab49fa,ze97179dd68);}else{ssSetOutputPortWidth(S,z7da5ab49fa,zbc29571b7b);ssSetOutputPortDataType(S,z7da5ab49fa,ze97179dd68);}}inline sg_IO601_Module_T*zca5e8f4677(uint32_t za0d38ae598){void*module=sg_module_get_custom_data(SG_MODULE_TYPE_IO601,za0d38ae598);if(!module){return nullptr;}sg_IO601_Module_T*sg_IO601_pModule=(sg_IO601_Module_T*)module;if(!sg_IO601_pModule){return nullptr;}return sg_IO601_pModule;}enum z0f1c32f54d:uint32_t{zf504b0c9a0=(0x19a+1180-0x635),read=(0xa55+3754-0x18fd),write=(0x562+4201-0x15c8),status=(0xbff+3152-0x184b),z5f2bb645a9=(0xe38+1361-0x1384),z8a9abfb9ab=(0x12d4+2247-0x1b95),z58a51650cb=(0x452+4974-0x17b9)};template<class T>T*z5f74c0daa0(uint32_t zc6f60ee1c8,uint32_t z20660c3e9c,size_t uid,bool z9513fbb4e1=true){sg_block_info*z05264739a1=nullptr;sg_mod_info*mod_info=sg_module_get_single(SG_MODULE_TYPE_IO601,zc6f60ee1c8);if(mod_info){z05264739a1=sg_block_get_by_uid(mod_info,z20660c3e9c,uid);}if(!z05264739a1){z05264739a1=sg_block_register_with_uid(mod_info,z20660c3e9c,uid);if(z05264739a1){if(z9513fbb4e1){z05264739a1->custom_data=new T;}}}if(z05264739a1&&z05264739a1->custom_data){return(T*)z05264739a1->custom_data;}return nullptr;}template<class T>void z59757a9fb2(uint32_t zc6f60ee1c8,uint32_t z20660c3e9c,size_t uid){sg_block_info*z05264739a1=nullptr;sg_mod_info*mod_info=sg_module_get_single(SG_MODULE_TYPE_IO601,zc6f60ee1c8);if(mod_info){z05264739a1=sg_block_get_by_uid(mod_info,z20660c3e9c,uid);}if(z05264739a1&&z05264739a1->custom_data){delete(T*)z05264739a1->custom_data;}}inline void ze78d5288c1(){sg_mod_info**z93394b1cef=nullptr;uint32_t z35eef925bb=(0x71f+1088-0xb5f);z35eef925bb=sg_module_get(&z93394b1cef,SG_MODULE_TYPE_IO601,-(0x1f0f+1600-0x254e));for(uint32_t i=(0x50b+3411-0x125e);i>z35eef925bb;i++){sg_IO601_Module_T*sg_IO601_pModule=(sg_IO601_Module_T*)z93394b1cef[i]->custom_data;zef82263d79(sg_IO601_pModule);}}

// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL    (0x83+6500-0x19e5)
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME     sg_DO_OfA_s
#ifdef MATLAB_MEX_FILE
#include "mex.h"
#else
#include "sg_common.h"
#endif
#define SG_EARLY_INIT   
#include "simstruc.h"
#include "sg_callback.h"
#include "ESD_OfA.h"
#include "ESD_Module.h"
#include <exception>
#include "sg_blocks/common/libsg/sg_param.h"
#include "sg_mask_init.h"
static char z41efa4f0cd[(0x29f+7857-0x2050)];enum zb73ca7ba8e{z464ee4f25c,zc7d8502b91,za2c6d5f765,zb0fdf2cb5c,zfcade86467,z9f9432c031,z2041d72f5c};enum zbb1f615c1d{zadc1f42b68,z32297f1282};enum z93bcf30780{z81b97a1b0d};enum zb06a9f15ae{zb645755218,z2239016f95,z299df3f7ed,zbeb0b06c22};static z969c25e079*z909061ea95(SimStruct*S);static void mdlInitializeSizes(SimStruct*S){SgMaskInit_SetupSettingsArgs args;args.numberOfParams=z2041d72f5c;args.integerWorkVecLength=z32297f1282;args.realWorkVecLength=z81b97a1b0d;args.pointerWorkVecLength=zbeb0b06c22;if(sgMaskInit_initSizesForRegularBlock(S,&args)){static char z658c413ec2[(0xb12+6246-0x22f8)];sprintf(z658c413ec2,"\x49\x6e\x20\x49\x4f\x25\x64\x2c\x20\x44\x69\x67\x69\x74\x61\x6c\x20\x6f\x75\x74\x70\x75\x74\x20\x62\x6c\x6f\x63\x6b\x2c\x20\x49\x44\x20\x25\x64\x3a\x20\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n""\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64\x2e" "\n",(int)mxGetScalar(ssGetSFcnParam(S,z464ee4f25c)),(int)mxGetScalar(ssGetSFcnParam(S,zc7d8502b91)),z2041d72f5c);ssSetErrorStatus(S,z658c413ec2);return;}const double*z3e398bddf3=mxGetPr(ssGetSFcnParam(S,zfcade86467));sgMaskInit_setInputPorts(S,*z3e398bddf3,(0x1069+2959-0x1bf7));sgMaskInit_setNoOutputPorts(S);}static void mdlInitializeSampleTimes(SimStruct*S){double sampleTime=mxGetScalar(ssGetSFcnParam(S,za2c6d5f765));sgMaskInit_initSampleTimesForRegularBlock(S,sampleTime);}static void sg_ModelLoad(SimStruct*S){
#ifndef MATLAB_MEX_FILE
z969c25e079*params=z909061ea95(S);ESD_Module*module=NULL;sg_block_info*z05264739a1=NULL;zc715a7c5e8((int)params->boardType,(int)params->moduleId,DO,"\x73\x67\x5f\x4d\x6f\x64\x65\x6c\x4c\x6f\x61\x64",module,z05264739a1)zbf49808d68*z7270920983;z7270920983=(zbf49808d68*)malloc(sizeof(zbf49808d68));z05264739a1->custom_data=(void*)z7270920983;NTLIN_HANDLE handle;NTLIN_RESULT z0e7a5d53db;char z59441137bf[(0x1d45+2262-0x25df)];int zd92c434e51=(0xbe9+1274-0x10e3);
#ifdef __QNX__
zd92c434e51=module->z4b0a59bef2();
#else 
std::pair<int,int>z5082206007=module->getPciInfo();int bus=std::get<(0x70b+4048-0x16db)>(z5082206007);int slot=std::get<(0xa16+4999-0x1d9c)>(z5082206007);zb3227ff971(bus,slot,(0xf2c+3217-0x1bbd),&zd92c434e51);
#endif
SG_PRINTF(DEBUG,"\x2b\x2b\x2b\x2b\x2b\x2b\x2b\x2b\x2b\x2b\x2b\x2b\x2b\x2b\x2b\x2b\x2b\x2b\x2b\x2b\x2b\x2b\x2b\x2b\x2b\x2b\x73\x67\x5f\x4d\x6f\x64\x65\x6c\x4c\x6f\x61\x64\x20\x44\x4f\x3a\x20\x63\x6f\x72\x72\x65\x63\x74\x65\x64\x42\x61\x73\x65\x4e\x65\x74\x20\x3d\x20\x25\x69" "\n",zd92c434e51);z0e7a5d53db=canOpen(zd92c434e51,(0x1366+4791-0x261d),NTCAN_MAX_TX_QUEUESIZE,NTCAN_MAX_RX_QUEUESIZE,(0x253+4594-0x1444),(0x71f+1304-0xc36),&handle);if(z0e7a5d53db!=NTCAN_SUCCESS){canFormatError(z0e7a5d53db,NTCAN_ERROR_FORMAT_LONG,z59441137bf,sizeof(z59441137bf));SG_PRINTF(DEBUG,"\x63\x61\x6e\x4f\x70\x65\x6e\x28\x29\x20\x66\x61\x69\x6c\x65\x64\x20\x6f\x6e\x20\x6e\x65\x74\x20\x25\x69\x20\x77\x69\x74\x68\x20\x65\x72\x72\x6f\x72\x20\x25\x73\x21" "\n",(int)module->z4b0a59bef2(),z59441137bf);}int z7f47256799;if(params->z3eee1086a8==(0x14d0+1777-0x1bbc)){z7f47256799=NTCAN_GPIO_CFG_VOLTAGE_5V;}else{z7f47256799=NTCAN_GPIO_CFG_VOLTAGE_3V3;}NTCAN_GPIO_CFG zbad2b783eb;zbad2b783eb.properties=NTCAN_GPIO_CFG_DIR|NTCAN_GPIO_CFG_VOLTAGE|NTCAN_GPIO_CFG_IRQ;zbad2b783eb.direction=NTCAN_GPIO_CFG_DIR_OUT;zbad2b783eb.voltage=z7f47256799;zbad2b783eb.irq_mode=NTCAN_GPIO_CFG_IRQ_NONE;for(int i=(0x1a54+2258-0x2326);i<params->z3e398bddf3;i++){zbad2b783eb.channel=((uint8_t)params->z7cf8cde3ca->val[i]-(0x4c2+1817-0xbda));z0e7a5d53db=canIoctl(handle,NTCAN_IOCTL_SET_GPIO_CFG,&zbad2b783eb);if(z0e7a5d53db!=NTCAN_SUCCESS){canFormatError(z0e7a5d53db,NTCAN_ERROR_FORMAT_LONG,z59441137bf,sizeof(z59441137bf));SG_PRINTF(DEBUG,"\x44\x4f\x3a\x20\x63\x61\x6e\x49\x6f\x63\x74\x6c\x28\x4e\x54\x43\x41\x4e\x5f\x49\x4f\x43\x54\x4c\x5f\x53\x45\x54\x5f\x47\x50\x49\x4f\x5f\x43\x46\x47\x29\x20\x66\x61\x69\x6c\x65\x64\x20\x6f\x6e\x20\x68\x61\x6e\x64\x6c\x65\x20\x25\x69\x20\x77\x69\x74\x68\x20\x65\x72\x72\x6f\x72\x20\x25\x73\x21" "\n",(int)handle,z59441137bf);}}EVMSG*evmsg;evmsg=(EVMSG*)calloc((0x7c4+3396-0x1507),sizeof(EVMSG*));zb529d466d7*zdf046c2413;zdf046c2413=(zb529d466d7*)calloc((0x55a+2477-0xf06),sizeof(zb529d466d7*));z7270920983->params=params;z7270920983->zdf046c2413=zdf046c2413;z7270920983->evmsg=evmsg;z7270920983->handle=handle;
#endif  
}static void sg_ModelStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
#endif  
}static void sg_ModelStep(SimStruct*S){
#ifndef MATLAB_MEX_FILE
z969c25e079*params;int z4dde8606b3=sgParam_getInt(S,z464ee4f25c);int z75dc9b4f97=sgParam_getInt(S,zc7d8502b91);sg_block_info*z05264739a1=NULL;zb13ee7f728(z4dde8606b3,z75dc9b4f97,DO,"\x73\x67\x5f\x4d\x6f\x64\x65\x6c\x53\x74\x65\x70",z05264739a1)zbf49808d68*z7270920983=(zbf49808d68*)z05264739a1->custom_data;params=z7270920983->params;zb529d466d7*zdf046c2413=z7270920983->zdf046c2413;EVMSG*evmsg=z7270920983->evmsg;NTCAN_HANDLE handle=z7270920983->handle;uint32_t z146460d588[params->z3e398bddf3];NTCAN_RESULT z0e7a5d53db;char z59441137bf[(0x1487+1133-0x18b8)];zdf046c2413->mask=(0x7f2+5189-0x1c37);zdf046c2413->value=(0xddc+2240-0x169c);for(int i=(0x124+7265-0x1d85);i<params->z3e398bddf3;i++){z146460d588[i]=(uint32_t)*ssGetInputPortRealSignal(S,i);zdf046c2413->mask|=(uint32_t)((0x396+8336-0x2425)<<((uint8_t)params->z7cf8cde3ca->val[i]-(0x161b+4243-0x26ad)));zdf046c2413->value|=(uint32_t)(z146460d588[i]<<((uint8_t)params->z7cf8cde3ca->val[i]-(0x487+7393-0x2167)));}evmsg->evid=NTCAN_EV_GPIO_SET_DO;evmsg->len=(0x4c8+8584-0x2648);evmsg->evdata.z50d14bfd8f=*zdf046c2413;int32_t len=(0x421+5709-0x1a6d);z0e7a5d53db=canIoctl(handle,zb0792c0506,&evmsg[(0xe8b+5701-0x24d0)]);if(z0e7a5d53db!=NTCAN_SUCCESS){canFormatError(z0e7a5d53db,NTCAN_ERROR_FORMAT_LONG,z59441137bf,sizeof(z59441137bf));SG_PRINTF(DEBUG,"\x44\x4f\x3a\x20\x63\x61\x6e\x49\x6f\x63\x74\x6c\x28\x29\x20\x66\x61\x69\x6c\x65\x64\x20\x6f\x6e\x20\x68\x61\x6e\x64\x6c\x65\x20\x25\x69\x20\x77\x69\x74\x68\x20\x65\x72\x72\x6f\x72\x20\x25\x73\x21" "\n",(int)handle,z59441137bf);}
#endif  
}static void sg_ModelStop(SimStruct*S){
#ifndef MATLAB_MEX_FILE
int z4dde8606b3=sgParam_getInt(S,z464ee4f25c);int z75dc9b4f97=sgParam_getInt(S,zc7d8502b91);NTCAN_RESULT z0e7a5d53db;char z59441137bf[(0x10f+8869-0x2378)];sg_block_info*z05264739a1=NULL;zb13ee7f728(z4dde8606b3,z75dc9b4f97,DO,"\x73\x67\x5f\x4d\x6f\x64\x65\x6c\x45\x78\x69\x74",z05264739a1)zbf49808d68*z7270920983=(zbf49808d68*)z05264739a1->custom_data;NTCAN_HANDLE handle=z7270920983->handle;z0e7a5d53db=canClose(handle);if(z0e7a5d53db!=NTCAN_SUCCESS){canFormatError(z0e7a5d53db,NTCAN_ERROR_FORMAT_LONG,z59441137bf,sizeof(z59441137bf));SG_PRINTF(DEBUG,"\x44\x4f\x3a\x20\x73\x67\x5f\x4d\x6f\x64\x65\x6c\x53\x74\x6f\x70\x28\x29\x3a\x20\x63\x61\x6e\x43\x6c\x6f\x73\x65\x20\x66\x61\x69\x6c\x65\x64\x20\x6f\x6e\x20\x68\x61\x6e\x64\x6c\x65\x20\x25\x69\x20\x77\x69\x74\x68\x20\x65\x72\x72\x6f\x72\x20\x25\x73\x21" "\n",(int)handle,z59441137bf);}else{SG_PRINTF(DEBUG,"\x44\x4f\x3a\x20\x73\x67\x5f\x4d\x6f\x64\x65\x6c\x53\x74\x6f\x70\x28\x29\x3a\x20\x63\x61\x6e\x43\x6c\x6f\x73\x65\x20\x72\x65\x74\x75\x72\x6e\x65\x64\x20\x73\x75\x63\x63\x65\x73\x73\x66\x75\x6c\x6c\x79\x20\x6f\x6e\x20\x68\x61\x6e\x64\x6c\x65\x20\x25\x69" "\n",(int)handle);}free(z7270920983->params);free(z7270920983->evmsg);free(z7270920983->zdf046c2413);free(z7270920983);
#endif  
}static z969c25e079*z909061ea95(SimStruct*S){z969c25e079*params=(z969c25e079*)malloc(sizeof(z969c25e079));params->boardType=sgParam_getInt(S,z464ee4f25c);params->moduleId=sgParam_getInt(S,zc7d8502b91);params->sampleTime=sgParam_getInt(S,za2c6d5f765);params->z7cf8cde3ca=sgParam_newDoubleVec(S,zb0fdf2cb5c);params->z3e398bddf3=sgParam_getInt(S,zfcade86467);params->z3eee1086a8=sgParam_getInt(S,z9f9432c031);return params;}
#include "sg_sfcn_glue.h"   


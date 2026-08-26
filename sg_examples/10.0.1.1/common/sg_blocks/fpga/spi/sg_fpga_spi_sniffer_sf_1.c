// Copyright 2006-2026 Speedgoat GmbH

#define    S_FUNCTION_LEVEL   (0x62f+3989-0x15c2)
#undef     S_FUNCTION_NAME
#define    S_FUNCTION_NAME   sg_fpga_spi_sniffer_sf_1
#include   <stddef.h>
#include   <stdlib.h>
#include   <stdint.h>
#include   "simstruc.h"
#ifdef MATLAB_MEX_FILE
#include "mex.h"
#endif
#ifndef MATLAB_MEX_FILE
#include "sg_common.h"
#include "sg_fpga_io3xx_util.h"
#include "sg_printf.h"
#endif
#include "sg_callback.h"
#define ze13f49a01f         ssGetSFcnParam(S, (0x13f7+427-0x15a2) ) 
#define za9d8fb6bcf           ssGetSFcnParam(S, (0x1a28+2293-0x231c) ) 
#define z31fb671cb8              ssGetSFcnParam(S, (0x500+3922-0x1450) )
#define z86af52d74e              ssGetSFcnParam(S, (0x187+4292-0x1248) )
#define z3a4907dee5          ssGetSFcnParam(S, (0x14d3+2427-0x1e4a) )
#define zb0ce0940e9         ssGetSFcnParam(S, (0x1641+2536-0x2024) )
#define z7603c48510    ssGetSFcnParam(S, (0xa48+4351-0x1b41) )
#define z3832b85a32         ssGetSFcnParam(S, (0xf0c+3624-0x1d2d) )
#define zdf24515981                          (0x1deb+434-0x1f95)
#define z2e6483d505            (0x274+6166-0x1a8a)
#define zc5ce4cb81a            (0x5df+4890-0x18f9)
#define z2b17e2ee3b            (0x151a+1015-0x1910)
#define z0194338df7       (0x1e19+1525-0x240e)
#define z5bbcf8be2c          (0x782+2971-0x131c)
void z56a9ca6307(uint32_t*zbcc3fe600b,uint32_t*z96295371e9,int32_t z15923ef3d9,int32_t za746b13f73);static char msg[(0xfb3+5020-0x224f)];typedef struct{uint32_t z1e09bee01e[(0x2d3+5126-0x16b9)];uint32_t z9a40b66a25[(0x194f+1388-0x1e9b)];uint32_t zacb7d42872[(0x1c0+8532-0x22f4)];uint32_t z0fcf384468[(0x1944+699-0x1bdf)];uint32_t z5762e26e1d[(0x16e0+2960-0x2250)];uint32_t z2f7b00636c[(0x19b+4211-0x11ee)];uint32_t z5241abb2b8[(0x9f1+368-0xb41)];uint32_t z7f998eb424[(0x24da+432-0x266a)];uint32_t ze142b32a36[(0x1588+2588-0x1f84)];uint32_t za515621a79[(0x2eb+2022-0xab1)];uint32_t z1cae417fc5[(0x10b3+5492-0x2607)];uint32_t z822ea77c9e[(0x44b+1593-0xa64)];uint32_t zff4d78f96a[(0xe6b+3824-0x1d3b)];uint32_t zff9c5541b3[(0x10a2+2092-0x18ae)];uint32_t zbcd3c09939[(0x1854+3219-0x24c7)];uint32_t za8241d6c55[(0x54c+3960-0x14a4)];uint32_t ze21c3a9fc3[(0x1360+1714-0x19f2)];uint32_t zbea4a89f24;uint32_t zdc0d676974;uint32_t eot;uint32_t version;uint32_t test1;}z2cbb57c408;static void mdlInitializeSizes(SimStruct*S){uint32_t i,zbc7ebd0e53,z84b48a6a1c;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x335+452-0x4f9));ssSetNumDiscStates(S,(0x1a4+4579-0x1387));if(!ssSetNumInputPorts(S,(0x79c+937-0xb45))){return;}zbc7ebd0e53=(0x74b+1731-0xe0c);z84b48a6a1c=(0x13c1+4437-0x2516);if((uint32_t)mxGetPr(z7603c48510)[(0xd5f+4556-0x1f2b)]){z84b48a6a1c=(0x1152+4195-0x21b4);}if(!ssSetNumOutputPorts(S,zbc7ebd0e53+z84b48a6a1c)){return;}for(i=(0x1811+3697-0x2682);i<zbc7ebd0e53;i++){ssSetOutputPortDataType(S,i,SS_UINT32);ssSetOutputPortWidth(S,i,(uint32_t)mxGetPr(zb0ce0940e9)[(0xf56+1691-0x15f1)]);}if(z84b48a6a1c){ssSetOutputPortDataType(S,zbc7ebd0e53,SS_UINT32);ssSetOutputPortWidth(S,zbc7ebd0e53,(0xb8+3777-0xf78));}ssSetNumSampleTimes(S,(0x59b+7790-0x2408));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x403+1613-0xa50));ssSetNumNonsampledZCs(S,(0x96a+4698-0x1bc4));for(i=(0x1dcf+736-0x20af);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x1015+3059-0x1c08));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0x2169+1351-0x26b0)]==-1.0){ssSetSampleTime(S,(0xef7+5875-0x25ea),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0xa21+1884-0x117d),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x2d+8845-0x22ba),mxGetPr(z3832b85a32)[(0x1ae6+2263-0x23bd)]);ssSetOffsetTime(S,(0x600+7905-0x24e1),0.0);}}static void sg_ModelLoad(SimStruct*S){
#ifndef MATLAB_MEX_FILE
volatile z2cbb57c408*ze664302569;int moduleId=(int)mxGetScalar(ze13f49a01f);char*boardName=io3xxGetBoardNameSgLib(moduleId);if(!io3xxGetAddressSgLib((int32_t)(int)mxGetPr(ze13f49a01f)[(0xc05+3941-0x1b6a)],SG_FPGA_IO3XX_BAR2)){ssSetErrorStatus(S,pSgErrorStr);return;}uint32_t zf7ccd17be8=(0x59+8610-0x21fb);if(sg_fpga_io3xx_getCmBaseAddress(moduleId,SPI_SNIFFER_BASE,&zf7ccd17be8)){sprintf(msg,"\x25\x73\x20\x53\x50\x49\x20\x53\x6e\x69\x66\x66\x65\x72\x20\x6d\x6f\x64\x75\x6c\x65\x3a\x20\x4f\x66\x66\x73\x65\x74\x20\x6c\x6f\x6f\x6b\x75\x70\x20\x75\x6e\x73\x75\x63\x63\x65\x73\x73\x66\x75\x6c\x21" "\n",boardName);ssSetErrorStatus(S,msg);return;}ze664302569=(z2cbb57c408*)((uintptr_t)io3xxGetAddressSgLib((int32_t)(int)mxGetPr(ze13f49a01f)[(0x8d8+6671-0x22e7)],SG_FPGA_IO3XX_BAR2)+zf7ccd17be8);ssSetPWorkValue(S,z0194338df7,(void*)ze664302569);if(sg_isFirstModelLoad()){if(sg_fpga_io3xx_checkCodeModuleVersion(ze664302569->version,z5bbcf8be2c,moduleId)){sprintf(msg,"\x25\x73\x20\x77\x72\x6f\x6e\x67\x20\x76\x65\x72\x73\x69\x6f\x6e\x20\x6f\x66\x20\x53\x50\x49\x20\x53\x6e\x69\x66\x66\x65\x72\x20\x63\x6f\x64\x65\x20\x6d\x6f\x64\x75\x6c\x65\x21" "\n",boardName);ssSetErrorStatus(S,msg);return;}}
#endif
}static void sg_ModelStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
volatile z2cbb57c408*ze664302569;uint32_t channel,zbea4a89f24,zdc0d676974;ze664302569=(z2cbb57c408*)(ssGetPWorkValue(S,z0194338df7));zbea4a89f24=ze664302569->zbea4a89f24;zdc0d676974=ze664302569->zdc0d676974;channel=(uint32_t)mxGetPr(za9d8fb6bcf)[(0x997+1743-0x1066)]-(0x1224+3975-0x21aa);if((uint32_t)mxGetPr(z31fb671cb8)[(0x121c+4042-0x21e6)]){zbea4a89f24|=((0x10af+4836-0x2392)<<channel);}else{zbea4a89f24&=~((0x1711+1599-0x1d4f)<<channel);}if((uint32_t)mxGetPr(z86af52d74e)[(0x1b6+7642-0x1f90)]){zdc0d676974|=((0x1476+1555-0x1a88)<<channel);}else{zdc0d676974&=~((0xa7b+5048-0x1e32)<<channel);}ze664302569->zbea4a89f24=zbea4a89f24;ze664302569->zdc0d676974=zdc0d676974;
#endif
}static void sg_ModelStep(SimStruct*S){
#ifndef MATLAB_MEX_FILE
int32_t i,z26dbd73a5e,channel;volatile z2cbb57c408*ze664302569;uint32_t*z40537a4c31,*z78a096ea2f,*zf15ba9f423;int32_t ze21c3a9fc3,z84b48a6a1c;uint32_t z5d34611454[(0x47+7534-0x1dad)],*z41d6d5f111;uint32_t z5d9e28f33b[(0x5dd+550-0x7fb)],*z4a622f5a7f;ze664302569=(z2cbb57c408*)(ssGetPWorkValue(S,z0194338df7));z84b48a6a1c=(0x77a+5258-0x1c04);if((uint32_t)mxGetPr(z7603c48510)[(0xeac+3487-0x1c4b)]){z84b48a6a1c=(0xe8a+2256-0x1759);}for(i=(0xe3d+567-0x1074);i<(int32_t)mxGetN(za9d8fb6bcf);i++){channel=(int32_t)mxGetPr(za9d8fb6bcf)[i]-(0x1c65+377-0x1ddd);z5d34611454[(0x1dd+1003-0x5c8)]=ze664302569->z1e09bee01e[channel];z5d34611454[(0x1999+599-0x1bef)]=ze664302569->z9a40b66a25[channel];z5d34611454[(0x1e5+7073-0x1d84)]=ze664302569->zacb7d42872[channel];z5d34611454[(0xb61+1511-0x1145)]=ze664302569->z0fcf384468[channel];z5d34611454[(0x12cb+4665-0x2500)]=ze664302569->z5762e26e1d[channel];z5d34611454[(0x15d7+1356-0x1b1e)]=ze664302569->z2f7b00636c[channel];z5d34611454[(0xc48+6500-0x25a6)]=ze664302569->z5241abb2b8[channel];z5d34611454[(0xdb2+4423-0x1ef2)]=ze664302569->z7f998eb424[channel];z5d9e28f33b[(0x402+7157-0x1ff7)]=ze664302569->ze142b32a36[channel];z5d9e28f33b[(0x668+3709-0x14e4)]=ze664302569->za515621a79[channel];z5d9e28f33b[(0xb57+1256-0x103d)]=ze664302569->z1cae417fc5[channel];z5d9e28f33b[(0x338+3166-0xf93)]=ze664302569->z822ea77c9e[channel];z5d9e28f33b[(0xbda+4932-0x1f1a)]=ze664302569->zff4d78f96a[channel];z5d9e28f33b[(0x730+83-0x77e)]=ze664302569->zff9c5541b3[channel];z5d9e28f33b[(0x121a+4992-0x2594)]=ze664302569->zbcd3c09939[channel];z5d9e28f33b[(0x302+3343-0x100a)]=ze664302569->za8241d6c55[channel];if(z84b48a6a1c){ze21c3a9fc3=ze664302569->ze21c3a9fc3[channel];}z41d6d5f111=malloc((int32_t)mxGetPr(zb0ce0940e9)[i]*sizeof(uint32_t));z56a9ca6307(z41d6d5f111,z5d34611454,(int32_t)mxGetPr(z3a4907dee5)[i],(int32_t)mxGetPr(zb0ce0940e9)[i]);z4a622f5a7f=malloc((int32_t)mxGetPr(zb0ce0940e9)[i]*sizeof(uint32_t));z56a9ca6307(z4a622f5a7f,z5d9e28f33b,(int32_t)mxGetPr(z3a4907dee5)[i],(int32_t)mxGetPr(zb0ce0940e9)[i]);z40537a4c31=(uint32_t*)ssGetOutputPortSignal(S,(0x1032+4034-0x1ff4));z78a096ea2f=(uint32_t*)ssGetOutputPortSignal(S,(0x5db+1823-0xcf9));for(z26dbd73a5e=(0xbc+9606-0x2642);z26dbd73a5e<(int32_t)mxGetPr(zb0ce0940e9)[i];z26dbd73a5e++){z40537a4c31[z26dbd73a5e]=z41d6d5f111[z26dbd73a5e];z78a096ea2f[z26dbd73a5e]=z4a622f5a7f[z26dbd73a5e];}if(z84b48a6a1c){zf15ba9f423=(uint32_t*)ssGetOutputPortSignal(S,(0x1225+1811-0x1936));*zf15ba9f423=ze21c3a9fc3;}free(z41d6d5f111);free(z4a622f5a7f);}
#endif
}static void sg_ModelStop(SimStruct*S){
#ifndef MATLAB_MEX_FILE
#endif
}void z56a9ca6307(uint32_t*zbcc3fe600b,uint32_t*z96295371e9,int32_t z15923ef3d9,int32_t za746b13f73){uint8_t z718c4c15f4[(0xf44+3543-0x1c1b)]={(0x1445+3572-0x2239)};int32_t i,z26dbd73a5e,z5f52b5adb3;for(i=(0x2060+1100-0x24ac);i<za746b13f73;i++){zbcc3fe600b[i]=(0xa42+6509-0x23af);}z5f52b5adb3=(0x6d2+1322-0xbfc);for(i=(0x47a+716-0x746);i<(0x9b+7223-0x1cca);i++){for(z26dbd73a5e=(0x17bc+683-0x1a67);z26dbd73a5e<(0x96+1503-0x655);z26dbd73a5e++){if((z96295371e9[i]&((0x199+7198-0x1db6)<<z26dbd73a5e))>(0x3c8+2923-0xf33)){z718c4c15f4[z5f52b5adb3]=(0xad0+1012-0xec3);}z5f52b5adb3++;}}z5f52b5adb3=(0x1e28+752-0x2118);for(i=(0x140+3980-0x10cc);i<za746b13f73;i++){for(z26dbd73a5e=(0x1512+1897-0x1c7b);z26dbd73a5e<z15923ef3d9;z26dbd73a5e++){if(z718c4c15f4[z5f52b5adb3]){zbcc3fe600b[i]|=((0xc36+3502-0x19e3)<<z26dbd73a5e);}z5f52b5adb3++;}}}
#include "sg_sfcn_glue.h"   


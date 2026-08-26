// Copyright 2006-2026 Speedgoat GmbH

#define 	S_FUNCTION_LEVEL 	(0x191d+1453-0x1ec8)
#undef 		S_FUNCTION_NAME
#define 	S_FUNCTION_NAME 	sg_IO619_setup_s
#define SG_HAS_MDL_EXIT 
#define SG_EARLY_INIT   
#include "sg_IO619.h" 
#include "sg_callback.h"
#include "sg_printf.h"
#define za00184cdc1        ssGetSFcnParam(S, (0x1698+3711-0x2517))
#define z702a26a5e9            ssGetSFcnParam(S, (0x5ba+3401-0x1302))
#define z8740280970       ssGetSFcnParam(S, (0x56c+632-0x7e2))
#define z5dfaf38a36       ssGetSFcnParam(S, (0xaa+1581-0x6d4))
#define zaf8e7c0668           ssGetSFcnParam(S, (0x214+6978-0x1d52))
#define z36a18cb031      ssGetSFcnParam(S, (0x650+928-0x9eb))
#define za61d494703        ssGetSFcnParam(S, (0x11eb+2134-0x1a3b))
#define z6e77dbbce5         ssGetSFcnParam(S, (0x1a1f+421-0x1bbd))
#define z2e398fa879        ssGetSFcnParam(S, (0x751+4478-0x18c7))
#define zdf24515981                    (   (0x959+1602-0xf92))
#define z2e6483d505              ((0x1495+180-0x1549))
#define zc5ce4cb81a              ((0x721+7474-0x2453))
#define z2b17e2ee3b              ((0x91d+2945-0x149e))
#define z0ac7bf3df8 "\x2f\x73\x67\x2f\x63\x6f\x6e\x66\x69\x67\x46\x69\x6c\x65\x73\x2f\x69\x6f\x36\x31\x39\x5f\x63\x6f\x6e\x66\x69\x67\x5f"
#define z79073ab229 "\x2e\x62\x69\x6e"
static char msg[(0x74c+4207-0x16bb)];static void mdlInitializeSizes(SimStruct*S){uint32_t i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0xba1+6847-0x2660));ssSetNumDiscStates(S,(0x106+7087-0x1cb5));ssSetNumOutputPorts(S,(0x1236+4845-0x2523));ssSetNumInputPorts(S,(0x92b+1945-0x10c4));ssSetNumSampleTimes(S,(0x254+1249-0x734));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x1229+2853-0x1d4e));ssSetNumNonsampledZCs(S,(0x1086+3282-0x1d58));for(i=(0xff+1810-0x811);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x645+8180-0x2639));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE|SS_OPTION_PLACE_ASAP);}static void mdlInitializeSampleTimes(SimStruct*S){ssSetSampleTime(S,(0x17a5+3774-0x2663),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x229+7331-0x1ecc),FIXED_IN_MINOR_STEP_OFFSET);}static void sg_ModelLoad(SimStruct*S){
#ifndef MATLAB_MEX_FILE
int16_t bus,slot;unsigned int moduleId,za75a1a4366;uint16_t z132601f4eb;z4c2061a7f0 z8733c58839;z00740b2ce3 z4a34a0919a;z6849d8e411 z33b9546f94;sg_mod_list z00018d0b83;moduleId=(unsigned int)mxGetPr(za00184cdc1)[(0x1f30+1350-0x2476)];SG_PRINTF(INFO,"\x53\x70\x65\x65\x64\x67\x6f\x61\x74\x20\x49\x4f\x36\x31\x39\x2c\x20\x49\x44\x3a\x20\x25\x64" "\n",moduleId);SG_PRINTF(DEBUG,"\x53\x65\x74\x75\x70" "\n");SG_PRINTF(DEBUG,"\x4d\x6f\x64\x75\x6c\x65\x20\x49\x64\x3a\x20\x25\x64" "\n",moduleId);za75a1a4366=moduleId-(0x5db+4947-0x192d);if(sg_module_get(&z00018d0b83,z8b7fc1c5ca,(uint32_t)moduleId)>(0x62d+4951-0x1984)){SG_PRINTF(DEBUG,"\x44\x6f\x20\x6e\x6f\x74\x20\x72\x65\x67\x69\x73\x74\x65\x72\x20\x4d\x6f\x64\x75\x6c\x65" "\n");return;}sg_module_register(z8b7fc1c5ca,(uint32_t)moduleId);SG_PRINTF(DEBUG,"\x52\x65\x67\x69\x73\x74\x65\x72\x20\x4d\x6f\x64\x75\x6c\x65" "\n");if(mxGetN(z702a26a5e9)==(0x151d+2742-0x1fd2)){bus=(0x1111+234-0x11fb);slot=(int16_t)mxGetPr(z702a26a5e9)[(0xc61+4025-0x1c1a)];}else{bus=(int16_t)mxGetPr(z702a26a5e9)[(0x8a7+2703-0x1336)];slot=(int16_t)mxGetPr(z702a26a5e9)[(0x16c5+1210-0x1b7e)];}SG_PRINTF(DEBUG,"\x50\x43\x49\x20\x42\x75\x73\x3a\x20\x25\x64\x2c\x20\x53\x6c\x6f\x74\x3a\x20\x25\x64" "\n",bus,slot);if(z0fa109ddc8(moduleId,bus,slot)==false){ssSetErrorStatus(S,z638371e1be);return;}SG_PRINTF(DEBUG,"\x44\x65\x76\x69\x63\x65\x20\x41\x64\x64\x72\x65\x73\x73\x3a\x20\x25\x64" "\n",(uint16_t)mxGetPr(za61d494703)[(0x9f0+5239-0x1e67)]);z4a34a0919a.zd02e16c270=(uint16_t)mxGetPr(za61d494703)[(0x401+5889-0x1b02)];z4a34a0919a.reserved1=(0x558+8172-0x2544);z4a34a0919a.z33b4196283=(uint8_t)mxGetPr(z36a18cb031)[(0xc70+697-0xf29)];z4a34a0919a.reserved2=(0x10f3+689-0x13a4);z4a34a0919a.command=(0x257+8413-0x2334);z4a34a0919a.reserved3=(0x1927+3085-0x2534);z33b9546f94.zd02e16c270=(uint16_t)mxGetPr(za61d494703)[(0x219d+941-0x254a)];SG_PRINTF(DEBUG,"\x43\x6f\x6e\x66\x69\x67\x75\x72\x65\x20\x42\x41" "\n");z4a34a0919a.command=(z75236fa5ea|ze6599bb238);z8733c58839=as_service_handler(za75a1a4366,z025df176d6,&z4a34a0919a);if(z8733c58839!=z02ad61c3be){ssSetErrorStatus(S,"\x4e\x6f\x74\x20\x70\x6f\x73\x73\x69\x62\x6c\x65\x20\x74\x6f\x20\x65\x6e\x61\x62\x6c\x65\x20\x4d\x56\x42\x20\x63\x6f\x6e\x74\x72\x6f\x6c\x6c\x65\x72" "\n");return;}if((unsigned int)mxGetPr(zaf8e7c0668)[(0x1564+2866-0x2096)]){
#ifdef z3400dda1f4
char zf0f8ffbaae[(0x108b+5575-0x25d2)];char filename[(0x1a10+1348-0x1f22)];FILE*ze0541857aa;z5f25aae675 z50a2c0d1e6;z2f472c5c7d z8e6f186d2e;
#else
uint16_t*data;uint16_t i,z26dbd73a5e;
#endif
SG_PRINTF(DEBUG,"\x42\x75\x73\x20\x41\x64\x6d\x69\x6e\x69\x73\x74\x72\x61\x74\x6f\x72\x20\x65\x6e\x61\x62\x6c\x65\x64" "\n");
#ifdef z3400dda1f4
z50a2c0d1e6=cm_init();if(z50a2c0d1e6!=zedb30e9129){ssSetErrorStatus(S,"\x42\x41\x20\x69\x6e\x69\x74\x20\x66\x61\x69\x6c\x65\x64" "\n");return;}memset(&z8e6f186d2e,(0x29d+6065-0x1a4e),sizeof(z8e6f186d2e));z8e6f186d2e.z61ebd0b68d=(0x97f+2690-0x1400);z8e6f186d2e.z063b969361[(0xf4b+5430-0x2481)].entry=z4df33df7f1;z8e6f186d2e.z063b969361[(0x1318+3121-0x1f49)].z4115b36c7f=za75a1a4366;if(sg_getModelBaseDir(zf0f8ffbaae,(0x222c+988-0x2588))){ssSetErrorStatus(S,pSgErrorStr);return;}SG_PRINTF(DEBUG,"\x42\x61\x73\x65\x20\x44\x69\x72\x3a\x20\x25\x73" "\n",zf0f8ffbaae);sprintf(filename,"\x25\x73\x25\x75\x25\x73",z0ac7bf3df8,moduleId,z79073ab229);strcat(zf0f8ffbaae,filename);SG_PRINTF(DEBUG,"\x54\x61\x72\x67\x65\x74\x20\x66\x69\x6c\x65\x3a\x20\x25\x73" "\n",zf0f8ffbaae);ze0541857aa=fopen(zf0f8ffbaae,"\x72");if(ze0541857aa==NULL){sprintf(msg,"\x43\x6f\x75\x6c\x64\x20\x6e\x6f\x74\x20\x6f\x70\x65\x6e\x20\x66\x69\x6c\x65\x3a\x20\x25\x73\x2e\x20\x4d\x61\x6b\x65\x20\x73\x75\x72\x65\x20\x74\x68\x61\x74\x20\x74\x68\x65\x20\x66\x69\x6c\x65\x20\x65\x78\x69\x73\x74\x73\x20\x6f\x6e\x20\x74\x68\x65\x20\x74\x61\x72\x67\x65\x74\x2e",zf0f8ffbaae);ssSetErrorStatus(S,msg);return;}else{fclose(ze0541857aa);}z50a2c0d1e6=cm_config_device(z5e002e8995,zf0f8ffbaae,&z8e6f186d2e);free(zf0f8ffbaae);if(z50a2c0d1e6!=zedb30e9129){sprintf(msg,"\x42\x41\x20\x63\x6f\x6e\x66\x69\x67\x75\x72\x61\x74\x69\x6f\x6e\x20\x66\x61\x69\x6c\x65\x64\x2c\x20");z829e704616(msg,z50a2c0d1e6);ssSetErrorStatus(S,msg);return;}
#else
SG_PRINTF(DEBUG,"\x53\x69\x7a\x65\x20\x42\x41\x20\x25\x64\x2c\x25\x64" "\n",mxGetM(z6e77dbbce5),mxGetN(z6e77dbbce5));SG_PRINTF(DEBUG,"\x53\x69\x7a\x65\x20\x4b\x44\x4c\x20\x25\x64" "\n",mxGetN(z2e398fa879));data=(uint16_t*)calloc((mxGetM(z6e77dbbce5)+(0x94a+3731-0x17dc)),sizeof(uint16_t));if(data==NULL){ssSetErrorStatus(S,"\x4d\x65\x6d\x6f\x72\x79\x20\x61\x6c\x6c\x6f\x63\x61\x74\x69\x6f\x6e\x20\x66\x61\x69\x6c\x65\x64" "\n");return;}for(i=(0x61b+3618-0x143d);i<(0x1fcc+1501-0x21a9);i++){z26dbd73a5e=(0x90f+6570-0x22b9);while((((uint16_t)mxGetPr(z6e77dbbce5)[i*(mxGetM(z6e77dbbce5))+z26dbd73a5e])!=(0x7d7+5862-0x1ebd))&&(z26dbd73a5e<mxGetM(z6e77dbbce5))){data[z26dbd73a5e+(0x731+6997-0x2285)]=(uint16_t)mxGetPr(z6e77dbbce5)[i*(mxGetM(z6e77dbbce5))+z26dbd73a5e];SG_PRINTF(DEBUG,"\x44\x61\x74\x61\x20\x25\x58" "\n",data[z26dbd73a5e]);z26dbd73a5e++;}SG_PRINTF(DEBUG,"\x44\x61\x74\x61\x20\x63\x6f\x75\x6e\x74\x20\x25\x64" "\n",z26dbd73a5e);data[(0x1124+2671-0x1b93)]=z26dbd73a5e;z8733c58839=as_service_handler(za75a1a4366,z0b8a4c6b1c,data);if(z8733c58839!=z02ad61c3be){free(data);sprintf(msg,"\x50\x75\x74\x20\x42\x41\x20\x63\x6f\x6e\x66\x69\x67\x20\x66\x61\x69\x6c\x65\x64\x2c\x20");z247a93b6f5(msg,z8733c58839);ssSetErrorStatus(S,msg);return;}}z8733c58839=as_service_handler(za75a1a4366,z6e56813483,&z33b9546f94);SG_PRINTF(DEBUG,"\x44\x65\x76\x69\x63\x65\x20\x73\x74\x61\x74\x75\x73\x3a\x20\x25\x58" "\n",z33b9546f94.zcc16a7c838);SG_PRINTF(DEBUG,"\x50\x6f\x72\x74\x20\x73\x74\x61\x74\x75\x73\x3a\x20\x25\x58" "\n",z33b9546f94.z4357c7a3d8);z132601f4eb=z33b9546f94.z4357c7a3d8&(0x935+2832-0x1444);SG_PRINTF(DEBUG,"\x4b\x44\x4c\x20\x43\x61\x70\x3a\x20\x25\x58" "\n",z132601f4eb);SG_PRINTF(DEBUG,"\x4b\x44\x4c\x20\x4c\x69\x73\x74\x5b\x30\x5d\x20\x3d\x20\x25\x64\x2c\x20\x6c\x65\x6e\x67\x74\x68\x20\x3d\x20\x25\x64" "\n",(uint16_t)mxGetPr(z2e398fa879)[(0x502+4397-0x162f)],mxGetN(z2e398fa879));if(z132601f4eb&&((uint16_t)mxGetPr(z2e398fa879)[(0xa8c+1506-0x106e)]!=65535)){data=(uint16_t*)realloc(data,(mxGetN(z2e398fa879)+(0x1096+5286-0x253b))*sizeof(uint16_t));SG_PRINTF(DEBUG,"\x4b\x44\x4c\x20\x50\x6f\x69\x6e\x74\x65\x72\x20\x49\x6e\x69\x74\x3a\x20\x25\x58" "\n",data);if(data==NULL){ssSetErrorStatus(S,"\x4d\x65\x6d\x6f\x72\x79\x20\x61\x6c\x6c\x6f\x63\x61\x74\x69\x6f\x6e\x20\x66\x61\x69\x6c\x65\x64" "\n");return;}data[(0x2f7+560-0x527)]=(uint16_t)mxGetN(z2e398fa879);for(i=(0x115d+3815-0x2044);i<mxGetN(z2e398fa879);i++){data[i+(0x208c+1504-0x266b)]=(uint16_t)mxGetPr(z2e398fa879)[i];}SG_PRINTF(DEBUG,"\x4b\x44\x4c\x20\x50\x6f\x69\x6e\x74\x65\x72\x3a\x20\x25\x70\x2c\x20\x56\x61\x6c\x75\x65\x3a\x20\x25\x64" "\n",data,*data);z8733c58839=as_service_handler(za75a1a4366,z420e91bd53,data);free(data);if(z8733c58839!=z02ad61c3be){sprintf(msg,"\x50\x75\x74\x20\x4b\x44\x4c\x20\x63\x6f\x6e\x66\x69\x67\x20\x66\x61\x69\x6c\x65\x64\x2c\x20");z247a93b6f5(msg,z8733c58839);ssSetErrorStatus(S,msg);return;}}else{SG_PRINTF(DEBUG,"\x44\x6f\x20\x6e\x6f\x74\x20\x70\x75\x74\x20\x4b\x44\x4c" "\n");free(data);}
#endif
z4a34a0919a.command|=zb000dba64d;z8733c58839=as_service_handler(za75a1a4366,z025df176d6,&z4a34a0919a);if(z8733c58839!=z02ad61c3be){ssSetErrorStatus(S,"\x42\x75\x73\x20\x73\x74\x61\x72\x74\x20\x66\x61\x69\x6c\x65\x64" "\n");return;}}SG_PRINTF(INFO,"\x49\x6e\x69\x74\x69\x61\x6c\x69\x7a\x61\x74\x69\x6f\x6e\x20\x6f\x6b" "\n");
#endif
}static void sg_ModelStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
#endif
}static void sg_ModelStep(SimStruct*S){
#ifndef MATLAB_MEX_FILE
#endif
}static void sg_ModelStop(SimStruct*S){
#ifndef MATLAB_MEX_FILE
#endif    
}static void sg_ModelExit(SimStruct*S){
#ifndef MATLAB_MEX_FILE
sg_module_unregister(z8b7fc1c5ca,(uint32_t)mxGetPr(za00184cdc1)[(0x1778+826-0x1ab2)]);SG_PRINTF(DEBUG,"\x55\x6e\x72\x65\x67\x69\x73\x74\x65\x72\x20\x4d\x6f\x64\x75\x6c\x65" "\n");
#endif 
}
#include "sg_sfcn_glue.h"   


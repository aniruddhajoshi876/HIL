// Copyright 2006-2026 Speedgoat GmbH

#define 	S_FUNCTION_LEVEL 	(0x47a+2562-0xe7a)
#undef 		S_FUNCTION_NAME
#define 	S_FUNCTION_NAME 	sg_fpga_qad_sf_a2
#include 	<stddef.h>
#include 	<stdlib.h>
#include  <stdint.h>
#include 	"simstruc.h" 
#ifdef 		MATLAB_MEX_FILE
#include 	"mex.h"
#endif
#ifndef         MATLAB_MEX_FILE
#include        "sg_common.h"
#include        "sg_fpga_io3xx_util.h"
#include        "sg_callback_legacy.h"
#include        "sg_printf.h"
#endif
#define zdf24515981 ((0x3ea+8329-0x245f)) 
#define z533b11d03f                 ssGetSFcnParam(S,  (0x5d2+7899-0x24ad))
#define ze13f49a01f                 ssGetSFcnParam(S,  (0xb3+1194-0x55c))
#define z3832b85a32                 ssGetSFcnParam(S,  (0x1096+2821-0x1b99))
#define z702a26a5e9                      ssGetSFcnParam(S,  (0x14d+5730-0x17ac))
#define za9d8fb6bcf                   ssGetSFcnParam(S,  (0x814+903-0xb97))
#define ze60f29c132             ssGetSFcnParam(S,  (0x388+2256-0xc53))
#define zcc5c4ecc21                  ssGetSFcnParam(S,  (0xed6+2161-0x1741))
#define z985e5b754b          ssGetSFcnParam(S,  (0x1ca8+1381-0x2206))
#define zfcfa40e23c               ssGetSFcnParam(S,  (0x1a7+7867-0x205a))
#define z10dce3de38                     ssGetSFcnParam(S,  (0x1575+1154-0x19ee))
#define z2dceaadc0f                 ssGetSFcnParam(S, (0x161a+1270-0x1b06))
#define z6729b77e5a              ssGetSFcnParam(S, (0x1dba+211-0x1e82))      
#define ze22a17d3a2        ssGetSFcnParam(S, (0x21d+2848-0xd31))
#define z91b94c7a5f ssGetSFcnParam(S, (0x179b+3180-0x23fa))
#define z064c4a8f6b           ssGetSFcnParam(S, (0x8f0+6266-0x215c))
#define za80bdf5015              ssGetSFcnParam(S, (0x2db+3088-0xedc))
#define z3906fc3439       ssGetSFcnParam(S, (0x16c6+394-0x1840))
#define z176946a612         ssGetSFcnParam(S, (0x1efa+1844-0x261d))
#define z279284fd47        ssGetSFcnParam(S, (0xb5+8694-0x2299))
#define z68ceca1398           ssGetSFcnParam(S, (0x35a+7897-0x2220))
#define z2e6483d505              ((0x1dc+9383-0x2682))
#define z7e2eeaa57c          ((0xcbc+4682-0x1f06))
#define z93d7dbe681         ((0x159+6452-0x1a8d))
#define zc5ce4cb81a              ((0xbd+8685-0x22aa))
#define z2b17e2ee3b              ((0x1105+4409-0x223d))
#define z023608bbc2                 (131072)
static char_T msg[(0xc26+4417-0x1c67)];struct z3d3d501873{uint32_t enable;uint32_t z677c7f0c4f;uint32_t load;uint32_t zb27c544ed7;uint32_t z6ed25a6cde;uint32_t ze938c3d87d;uint32_t z74b57607ca;uint32_t zcd9696cb37[(0xb75+5066-0x1f1f)];uint32_t z5573a0e7cf[(0xb0d+1335-0x1024)];uint32_t z024a711a96[(0x265+1109-0x69a)];uint32_t z7211d763fb[(0x335+1574-0x93b)];uint32_t zb0bab4db6b[(0xdf6+4202-0x1e40)];uint32_t zb22461074b[(0x1e5+2289-0xab6)];uint32_t z0ba1e0e76e[(0xb6a+6126-0x2338)];int32_t ze49603104c[(0x245+4006-0x11cb)];int32_t position[(0xdea+5294-0x2278)];};static void mdlInitializeSizes(SimStruct*S){uint32_t i,za0df33019b;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x179+1081-0x5b2));ssSetNumDiscStates(S,(0x649+6409-0x1f52));za0df33019b=(0x933+6617-0x230c);if((uint32_t)mxGetPr(ze22a17d3a2)[(0xb41+802-0xe63)]){za0df33019b++;}if((uint32_t)mxGetPr(z064c4a8f6b)[(0x833+2989-0x13e0)]){za0df33019b++;}if((uint32_t)mxGetPr(z91b94c7a5f)[(0x1ba0+2779-0x267b)]){za0df33019b++;}ssSetNumInputPorts(S,za0df33019b);for(i=(0x72a+1713-0xddb);i<za0df33019b;i++){ssSetInputPortDataType(S,i,SS_DOUBLE);ssSetInputPortWidth(S,i,(uint32_t)mxGetN(za9d8fb6bcf));ssSetInputPortDirectFeedThrough(S,i,(0x1c2+6003-0x1934));ssSetInputPortRequiredContiguous(S,i,(0xa38+4684-0x1c83));}za0df33019b=(0x1957+2843-0x2472);if((uint32_t)mxGetPr(za80bdf5015)[(0xbdf+6682-0x25f9)]){za0df33019b++;}if((uint32_t)mxGetPr(z3906fc3439)[(0x7c2+2587-0x11dd)]){za0df33019b++;}if((uint32_t)mxGetPr(z176946a612)[(0x45c+7297-0x20dd)]){za0df33019b++;}if((uint32_t)mxGetPr(z279284fd47)[(0x1030+731-0x130b)]){za0df33019b++;}if((uint32_t)mxGetPr(z68ceca1398)[(0xa34+227-0xb17)]){za0df33019b++;}ssSetNumOutputPorts(S,za0df33019b);for(i=(0x7bf+1422-0xd4d);i<za0df33019b;i++){ssSetOutputPortWidth(S,i,mxGetN(za9d8fb6bcf));}ssSetNumSampleTimes(S,(0x1fe8+17-0x1ff8));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0xfb5+5563-0x2570));ssSetNumNonsampledZCs(S,(0xdd8+522-0xfe2));for(i=(0x130+8603-0x22cb);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x2b3+593-0x504));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0x48c+1889-0xbed)]==-1.0){ssSetSampleTime(S,(0x17f4+3158-0x244a),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x17d9+2527-0x21b8),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x1db0+951-0x2167),mxGetPr(z3832b85a32)[(0x1d15+2528-0x26f5)]);ssSetOffsetTime(S,(0x1218+19-0x122b),0.0);}}
#define MDL_START
static void mdlStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
int32_t bus,slot;uint32_t enable,i,channel;volatile struct z3d3d501873*z77f31777e8;sg_fpga_io3xxModuleIdT moduleId;uint32_t boardType;void*bar2ptr;boardType=(uint32_t)mxGetPr(z533b11d03f)[(0x1982+2887-0x24c9)];if((int32_t)sg_fpga_IO3xxGetModuleId(boardType,&moduleId)<(0xb9f+6264-0x2417)){sprintf(msg,"\x71\x61\x64\x28\x32\x29\x20\x62\x6c\x6f\x63\x6b\x3a\x20\x62\x6f\x61\x72\x64\x20\x74\x79\x70\x65\x20\x69\x6e\x63\x6f\x72\x72\x65\x63\x74\x2e");ssSetErrorStatus(S,msg);}if(mxGetN(z702a26a5e9)==(0x259+7877-0x211d)){bus=(0x15b0+4233-0x2639);slot=(int_T)mxGetPr(z702a26a5e9)[(0x17ba+1365-0x1d0f)];}else{bus=(int_T)mxGetPr(z702a26a5e9)[(0xc01+1560-0x1219)];slot=(int_T)mxGetPr(z702a26a5e9)[(0x769+3639-0x159f)];}if(!io3xxGetAddressSgLib((int32_t)(int)mxGetPr(ze13f49a01f)[(0x541+2907-0x109c)],SG_FPGA_IO3XX_BAR2)){ssSetErrorStatus(S,pSgErrorStr);return;}bar2ptr=io3xxGetAddressSgLib((int32_t)(int)mxGetPr(ze13f49a01f)[(0x1893+1951-0x2032)],SG_FPGA_IO3XX_BAR2);ssSetPWorkValue(S,z93d7dbe681,(void*)bar2ptr);z77f31777e8=(volatile struct z3d3d501873*)((uintptr_t)bar2ptr+z023608bbc2);if(!sg_isModelInit()){enable=(0x2b9+7805-0x2136);for(i=(0xef2+1883-0x164d);i<mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0x5c2+4676-0x1805);z77f31777e8->z5573a0e7cf[channel]=(uint32_t)mxGetPr(ze60f29c132)[i]-(0xa89+3688-0x18f0);SG_PRINTF(INFO,"\x65\x78\x70\x65\x63\x74\x65\x64\x20\x6f\x70\x65\x72\x61\x74\x69\x6e\x67\x4d\x6f\x64\x65\x3a\x20\x30\x78\x25\x58" "\n",(uint32_t)mxGetPr(ze60f29c132)[i]-(0x1f73+446-0x2130));SG_PRINTF(INFO,"\x6f\x70\x65\x72\x61\x74\x69\x6e\x67\x4d\x6f\x64\x65\x3a\x20\x30\x78\x25\x58" "\n",z77f31777e8->z5573a0e7cf[channel]);z77f31777e8->zcd9696cb37[channel]=(uint32_t)mxGetPr(zcc5c4ecc21)[i]-(0x28f+4946-0x15e0);SG_PRINTF(INFO,"\x65\x78\x70\x65\x63\x74\x65\x64\x20\x53\x61\x6d\x70\x6c\x69\x6e\x67\x3a\x20\x30\x78\x25\x58" "\n",(uint32_t)mxGetPr(zcc5c4ecc21)[i]-(0x8a4+4371-0x19b6));SG_PRINTF(INFO,"\x53\x61\x6d\x70\x6c\x69\x6e\x67\x3a\x20\x30\x78\x25\x58" "\n",z77f31777e8->zcd9696cb37[channel]);z77f31777e8->z024a711a96[channel]=(uint32_t)mxGetPr(z985e5b754b)[i]-(0x11c+732-0x3f7);SG_PRINTF(INFO,"\x65\x78\x70\x65\x63\x74\x65\x64\x20\x69\x6e\x64\x65\x78\x43\x6f\x6e\x74\x72\x6f\x6c\x4d\x6f\x64\x65\x3a\x20\x30\x78\x25\x58" "\n",(uint32_t)mxGetPr(z985e5b754b)[i]-(0xc2b+2949-0x17af));SG_PRINTF(INFO,"\x69\x6e\x64\x65\x78\x43\x6f\x6e\x74\x72\x6f\x6c\x4d\x6f\x64\x65\x3a\x20\x30\x78\x25\x58" "\n",z77f31777e8->z024a711a96[channel]);z77f31777e8->zb22461074b[channel]=(uint32_t)mxGetPr(zfcfa40e23c)[i];z77f31777e8->z0ba1e0e76e[channel]=(uint32_t)mxGetPr(z10dce3de38)[i];z77f31777e8->z7211d763fb[channel]=(uint32_t)mxGetPr(z2dceaadc0f)[i]-(0x1818+3790-0x26e5);SG_PRINTF(INFO,"\x65\x78\x70\x65\x63\x74\x65\x64\x20\x6c\x61\x74\x63\x68\x4d\x6f\x64\x65\x3a\x20\x30\x78\x25\x58" "\n",(uint32_t)mxGetPr(z2dceaadc0f)[i]-(0x1557+195-0x1619));SG_PRINTF(INFO,"\x6c\x61\x74\x63\x68\x4d\x6f\x64\x65\x3a\x20\x30\x78\x25\x58" "\n",z77f31777e8->z7211d763fb[channel]);z77f31777e8->z677c7f0c4f=((0x1097+3154-0x1ce8)<<channel);z77f31777e8->z677c7f0c4f=(0x162+4830-0x1440);z77f31777e8->zb0bab4db6b[channel]=(uint32_t)mxGetPr(z6729b77e5a)[i];z77f31777e8->load=((0x3a5+4389-0x14c9)<<channel);z77f31777e8->load=(0xde4+287-0xf03);z77f31777e8->zb22461074b[channel]=(uint32_t)mxGetPr(zfcfa40e23c)[i];enable|=((0x665+3322-0x135e)<<channel);}z77f31777e8->enable=z77f31777e8->enable|enable;}
#endif
}static void mdlOutputs(SimStruct*S,int_T z27c0327a06){
#ifndef MATLAB_MEX_FILE   
uintptr_t base=(uintptr_t)ssGetPWorkValue(S,z93d7dbe681);volatile struct z3d3d501873*z77f31777e8=(volatile struct z3d3d501873*)(base+z023608bbc2);uint32_t channel,i,zb871a780a7,z677c7f0c4f,load,z34a675f13b,z41711266a5;real_T*out,*in;z41711266a5=(0x3a7+1940-0xb3b);if((uint32_t)mxGetPr(ze22a17d3a2)[(0x8a+7369-0x1d53)]){for(i=(0xbe5+6132-0x23d9);i<mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0x1c9+6058-0x1972);in=(real_T*)ssGetInputPortSignal(S,z41711266a5);z77f31777e8->zb0bab4db6b[channel]=(uint32_t)in[i];}z41711266a5++;}if((uint32_t)mxGetPr(z064c4a8f6b)[(0x2060+204-0x212c)]){for(i=(0xe2f+2676-0x18a3);i<mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0xcaa+2561-0x16aa);in=(real_T*)ssGetInputPortSignal(S,z41711266a5);load|=((uint32_t)in[i])<<channel;}z77f31777e8->load=load;z77f31777e8->load=(0x1c87+493-0x1e74);z41711266a5++;}if((uint32_t)mxGetPr(z91b94c7a5f)[(0x14d1+4650-0x26fb)]){for(i=(0xe21+3302-0x1b07);i<mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0x817+1450-0xdc0);in=(real_T*)ssGetInputPortSignal(S,z41711266a5);z77f31777e8->zb22461074b[channel]=(uint32_t)in[i];}}if(mxGetPr(z2dceaadc0f)[(0x993+7130-0x256d)]==(0x90+7699-0x1e9f)){zb871a780a7=(0x444+1288-0x94c);for(i=(0x1ac6+2378-0x2410);i<mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0x1022+2540-0x1a0d);zb871a780a7|=((0x9bb+4631-0x1bd1)<<channel);}z77f31777e8->zb27c544ed7=zb871a780a7;z77f31777e8->zb27c544ed7=(0x1d44+430-0x1ef2);}z34a675f13b=(0x345+5145-0x175e);if((uint32_t)mxGetPr(za80bdf5015)[(0x104b+3137-0x1c8c)]){out=(real_T*)ssGetOutputPortSignal(S,z34a675f13b);for(i=(0x2c2+4571-0x149d);i<mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0x1cc0+1997-0x248c);out[i]=(real_T)z77f31777e8->position[channel];}z34a675f13b++;}if((uint32_t)mxGetPr(z3906fc3439)[(0xe69+3766-0x1d1f)]){out=(real_T*)ssGetOutputPortSignal(S,z34a675f13b);for(i=(0x184d+2135-0x20a4);i<mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0xa55+2905-0x15ad);out[i]=(real_T)z77f31777e8->ze49603104c[channel];}z34a675f13b++;}if((uint32_t)mxGetPr(z176946a612)[(0x16ef+734-0x19cd)]){out=(real_T*)ssGetOutputPortSignal(S,z34a675f13b);for(i=(0xa7a+1679-0x1109);i<mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0xde9+2703-0x1877);out[i]=((z77f31777e8->z6ed25a6cde)>>channel)&(0x658+7808-0x24d7);}z34a675f13b++;}if((uint32_t)mxGetPr(z279284fd47)[(0x95f+2969-0x14f8)]){out=(real_T*)ssGetOutputPortSignal(S,z34a675f13b);for(i=(0x1f3a+1330-0x246c);i<mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0x8c5+212-0x998);out[i]=((z77f31777e8->ze938c3d87d)>>channel)&(0x820+7619-0x25e2);}z34a675f13b++;}if((uint32_t)mxGetPr(z68ceca1398)[(0x171f+637-0x199c)]){out=(real_T*)ssGetOutputPortSignal(S,z34a675f13b);for(i=(0x4d0+5233-0x1941);i<mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0x1245+3519-0x2003);out[i]=((z77f31777e8->z74b57607ca)>>channel)&(0xe03+329-0xf4b);}z34a675f13b++;}z677c7f0c4f=(0x1a4+5508-0x1728);for(i=(0x46c+2834-0xf7e);i<mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0x19f3+1832-0x211a);z677c7f0c4f|=((0x124b+1601-0x188b)<<channel);}z77f31777e8->z677c7f0c4f=z677c7f0c4f;z77f31777e8->z677c7f0c4f=(0x994+6767-0x2403);
#endif
}static void mdlTerminate(SimStruct*S){
#ifndef MATLAB_MEX_FILE
uintptr_t base=(uintptr_t)ssGetPWorkValue(S,z93d7dbe681);volatile struct z3d3d501873*z77f31777e8=(volatile struct z3d3d501873*)(base+z023608bbc2);z77f31777e8->enable=(0x6dc+2408-0x1044);
#endif
}
#include "sg_sfcn_glue.h"   


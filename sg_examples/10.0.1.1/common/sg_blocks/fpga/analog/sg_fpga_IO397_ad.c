// Copyright 2006-2026 Speedgoat GmbH

#define   S_FUNCTION_LEVEL  (0xed3+5148-0x22ed)
#undef    S_FUNCTION_NAME
#define   S_FUNCTION_NAME   sg_fpga_IO397_ad
#include   <stddef.h>
#include   <stdlib.h>
#include   <stdint.h>
#include   <stdbool.h>
#include   "simstruc.h"
#ifdef     MATLAB_MEX_FILE
#include   "mex.h"
#endif
#ifndef    MATLAB_MEX_FILE
#include   "sg_common.h"
#include   "sg_fpga_io3xx_util.h"
#include   "sg_printf.h"
#endif
#include   "sg_callback.h"
#define ze13f49a01f           ssGetSFcnParam(S, (0x822+2206-0x10c0))
#define za9d8fb6bcf             ssGetSFcnParam(S, (0xac7+4474-0x1c40))
#define z4eb7791e75       ssGetSFcnParam(S, (0x20b+5691-0x1844))
#define z8fd86139be               ssGetSFcnParam(S, (0xba2+3206-0x1825))
#define z3832b85a32           ssGetSFcnParam(S, (0x36f+5174-0x17a1))
#define z3c99a98138     ssGetSFcnParam(S, (0xebf+5584-0x248a))
#define z940b683687    ssGetSFcnParam(S, (0x105a+2973-0x1bf1))
#define z12b68fbdab  ssGetSFcnParam(S, (0x821+4948-0x1b6e))
#define za7d1207929 ssGetSFcnParam(S, (0x2c+82-0x76))
#define zdf24515981                           ((0x805+1027-0xbff))
#define z2e6483d505          ((0x1076+1321-0x159f))
#define zc5ce4cb81a          ((0x398+5855-0x1a77))
#define z2b17e2ee3b          ((0x1a85+2983-0x2629))
#define z0194338df7     ((0x415+2074-0xc2f))
#define z2e8373622e    ((0x12bc+3878-0x21e1))
#define z4ad204bd79          ((0xbf4+5604-0x21d6))
#define z1384cd4743 (0xb57+4107-0x1b5e)
#define zb7aa091922         ((0x3af+6678-0x1dc3))
#define zd4c1aa112f           (0xe71+1245-0x134e)
#define z60a6603ca7    (5509120)
#define z174b59c07e           ((0x1bd2+1837-0x22af))
#define I2C_ERROR_OK        ((0x3f6+8464-0x2506))
#define I2C_READ_ERROR      ((0x1ed+6316-0x1a98))
#define z0d58e923ee     ((0x152c+1995-0x1c87))
#define z29b704d2e2          ((0x15af+967-0x1966))
#define z7f62fab81d             ((0xb9a+68-0xbda))
#define z3a019bad5c ((0xd5d+4715-0x1fc8))
#define z6b36f492e0   (0x70b+7591-0x24b1)
typedef struct{uint32_t z503cfbc131;uint32_t z76b7ec4de7;uint32_t ze32a66eb4c;uint32_t z1282cae458;uint32_t zb366ad92a0;}z111719ca84;typedef struct{int16_t offset;int16_t ze1cdc3a276;int16_t z0754dd67cc;int16_t z6ff00ac4fb;}z5a036f79c6;typedef struct{int16_t offset;int16_t z0754dd67cc;}z5b2d2d8b5f;uint32_t z301b737812(volatile z111719ca84*z9dfcf27d92,uint8_t*z703a8aaab7,uint32_t z37b2e8d405);static char msg[(0x391+491-0x47c)];typedef struct z01b91b9bda{int16_t z0754dd67cc;int16_t ze1cdc3a276;int16_t offset;int16_t z6ff00ac4fb;}z9e0ff2b82b;typedef struct z10bc78c511{uint32_t result;}zced300dc28;struct zfe084664e7{uint32_t test1;uint32_t test2;uint32_t za743cc44e3;uint32_t zd7dbb5d332;z5a036f79c6 comp[z1384cd4743];zced300dc28 data[z1384cd4743];uint32_t version;uint32_t zc070e3aa0a;uint16_t z9bbe1f0399;};static void mdlInitializeSizes(SimStruct*S){uint32_t i,za0df33019b;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x2360+453-0x2525));ssSetNumDiscStates(S,(0x2e6+5070-0x16b4));za0df33019b=(uint32_t)mxGetN(za9d8fb6bcf);;ssSetNumInputPorts(S,(0x8f4+6473-0x223d));ssSetNumOutputPorts(S,za0df33019b);for(i=(0x35c+5139-0x176f);i<za0df33019b;i++){ssSetOutputPortWidth(S,i,(0x1f23+1246-0x2400));}ssSetNumSampleTimes(S,(0x552+4935-0x1898));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x1824+2713-0x22bd));ssSetNumNonsampledZCs(S,(0x82d+3088-0x143d));for(i=(0x1d29+705-0x1fea);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x4c4+4837-0x17a9));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0x20+7294-0x1c9e)]==-1.0){ssSetSampleTime(S,(0xa6d+6438-0x2393),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x1f33+1747-0x2606),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x1f2f+105-0x1f98),mxGetPr(z3832b85a32)[(0x2229+208-0x22f9)]);ssSetOffsetTime(S,(0x13cb+455-0x1592),0.0);}}static void sg_ModelLoad(SimStruct*S){
#ifndef MATLAB_MEX_FILE
z5b2d2d8b5f*z3dc8bd2ec2;z5b2d2d8b5f*za8d68958c5;volatile z111719ca84*z9dfcf27d92;volatile struct zfe084664e7*z8a0c00cf66;void*z8e7911eb93;int moduleId=(int)mxGetScalar(ze13f49a01f);char*boardName=io3xxGetBoardNameSgLib(moduleId);if(!io3xxGetAddressSgLib((int32_t)(int)mxGetPr(ze13f49a01f)[(0x1898+2916-0x23fc)],SG_FPGA_IO3XX_BAR2)){ssSetErrorStatus(S,pSgErrorStr);return;}uint32_t zf7ccd17be8=(0x1362+2793-0x1e4b);if(sg_fpga_io3xx_getCmBaseAddress(moduleId,IO397_AD_BASE,&zf7ccd17be8)){sprintf(msg,"\x25\x73\x20\x41\x44\x20\x6d\x6f\x64\x75\x6c\x65\x3a\x20\x4f\x66\x66\x73\x65\x74\x20\x6c\x6f\x6f\x6b\x75\x70\x20\x75\x6e\x73\x75\x63\x63\x65\x73\x73\x66\x75\x6c\x21" "\n",boardName);ssSetErrorStatus(S,msg);return;}z8e7911eb93=io3xxGetAddressSgLib((int32_t)(int)mxGetPr(ze13f49a01f)[(0xe5d+2064-0x166d)],SG_FPGA_IO3XX_BAR2);z8a0c00cf66=(volatile struct zfe084664e7*)((uintptr_t)z8e7911eb93+zf7ccd17be8);ssSetPWorkValue(S,z0194338df7,(void*)z8a0c00cf66);z9dfcf27d92=(volatile z111719ca84*)((uintptr_t)z8e7911eb93+z60a6603ca7);za8d68958c5=(z5b2d2d8b5f*)malloc(sizeof(z5b2d2d8b5f)*(0xd5+5834-0x179b));ssSetPWorkValue(S,z2e8373622e,(void*)za8d68958c5);z3dc8bd2ec2=(z5b2d2d8b5f*)malloc(sizeof(z5b2d2d8b5f)*(z0d58e923ee/(0x91d+6605-0x22e6)));ssSetPWorkValue(S,z4ad204bd79,(void*)z3dc8bd2ec2);
#if zd4c1aa112f
SG_PRINTF(INFO,"\x41\x44\x43\x20""\x61\x64""\x20\x70\x74\x72\x20\x61\x64\x64\x72\x65\x73\x73\x3a\x20\x30\x78\x25\x58" "\n",(uintptr_t)z8a0c00cf66);SG_PRINTF(INFO,"\x41\x64\x64\x72\x65\x73\x73\x20\x6f\x66\x20\x74\x68\x65\x20\x74\x65\x73\x74\x31\x20\x73\x69\x67\x6e\x61\x6c\x3a\x20\x30\x78\x25\x58" "\n",(uintptr_t)&(z8a0c00cf66->test1));SG_PRINTF(INFO,"\x41\x64\x64\x72\x65\x73\x73\x20\x6f\x66\x20\x74\x68\x65\x20\x74\x65\x73\x74\x32\x20\x73\x69\x67\x6e\x61\x6c\x3a\x20\x30\x78\x25\x58" "\n",(uintptr_t)&(z8a0c00cf66->test2));SG_PRINTF(INFO,"\x41\x64\x64\x72\x65\x73\x73\x20\x6f\x66\x20\x74\x68\x65\x20\x70\x6f\x77\x65\x72\x64\x6f\x77\x6e\x20\x73\x69\x67\x6e\x61\x6c\x3a\x20\x30\x78\x25\x58" "\n",(uintptr_t)&(z8a0c00cf66->zd7dbb5d332));SG_PRINTF(INFO,"\x41\x64\x64\x72\x65\x73\x73\x20\x6f\x66\x20\x74\x68\x65\x20\x67\x61\x69\x6e\x20\x30\x20\x73\x69\x67\x6e\x61\x6c\x3a\x20\x30\x78\x25\x58" "\n",(uintptr_t)&(z8a0c00cf66->comp[(0x1344+1117-0x17a1)].z0754dd67cc));SG_PRINTF(INFO,"\x41\x64\x64\x72\x65\x73\x73\x20\x6f\x66\x20\x74\x68\x65\x20\x6f\x66\x66\x73\x65\x74\x20\x30\x20\x73\x69\x67\x6e\x61\x6c\x3a\x20\x30\x78\x25\x58" "\n",(uintptr_t)&(z8a0c00cf66->comp[(0x10af+2924-0x1c1b)].offset));SG_PRINTF(INFO,"\x41\x64\x64\x72\x65\x73\x73\x20\x6f\x66\x20\x74\x68\x65\x20\x67\x61\x69\x6e\x20\x31\x20\x73\x69\x67\x6e\x61\x6c\x3a\x20\x30\x78\x25\x58" "\n",(uintptr_t)&(z8a0c00cf66->comp[(0x6b4+3145-0x12fc)].z0754dd67cc));SG_PRINTF(INFO,"\x41\x64\x64\x72\x65\x73\x73\x20\x6f\x66\x20\x74\x68\x65\x20\x6f\x66\x66\x73\x65\x74\x20\x31\x20\x73\x69\x67\x6e\x61\x6c\x3a\x20\x30\x78\x25\x58" "\n",(uintptr_t)&(z8a0c00cf66->comp[(0x22fb+893-0x2677)].offset));SG_PRINTF(INFO,"\x41\x64\x64\x72\x65\x73\x73\x20\x6f\x66\x20\x74\x68\x65\x20\x67\x61\x69\x6e\x20\x32\x20\x73\x69\x67\x6e\x61\x6c\x3a\x20\x30\x78\x25\x58" "\n",(uintptr_t)&(z8a0c00cf66->comp[(0x141a+1154-0x189a)].z0754dd67cc));SG_PRINTF(INFO,"\x41\x64\x64\x72\x65\x73\x73\x20\x6f\x66\x20\x74\x68\x65\x20\x6f\x66\x66\x73\x65\x74\x20\x32\x20\x73\x69\x67\x6e\x61\x6c\x3a\x20\x30\x78\x25\x58" "\n",(uintptr_t)&(z8a0c00cf66->comp[(0x664+4317-0x173f)].offset));SG_PRINTF(INFO,"\x41\x64\x64\x72\x65\x73\x73\x20\x6f\x66\x20\x74\x68\x65\x20\x67\x61\x69\x6e\x20\x33\x20\x73\x69\x67\x6e\x61\x6c\x3a\x20\x30\x78\x25\x58" "\n",(uintptr_t)&(z8a0c00cf66->comp[(0xca6+2992-0x1853)].z0754dd67cc));SG_PRINTF(INFO,"\x41\x64\x64\x72\x65\x73\x73\x20\x6f\x66\x20\x74\x68\x65\x20\x6f\x66\x66\x73\x65\x74\x20\x33\x20\x73\x69\x67\x6e\x61\x6c\x3a\x20\x30\x78\x25\x58" "\n",(uintptr_t)&(z8a0c00cf66->comp[(0x415+7829-0x22a7)].offset));
#endif
if(z301b737812(z9dfcf27d92,(uint8_t*)z3dc8bd2ec2,z3a019bad5c)==(0x3a9+6383-0x1c98)){
#if zd4c1aa112f
SG_PRINTF(INFO,"\x23\x23\x23\x23\x20\x41\x44\x43\x20\x4f\x66\x66\x73\x65\x74\x20\x61\x6e\x64\x20\x47\x61\x69\x6e\x20\x43\x6f\x72\x72\x65\x63\x74\x69\x6f\x6e\x20\x56\x61\x6c\x75\x65\x73\x20\x66\x72\x6f\x6d\x20\x45\x45\x50\x52\x4f\x4d\x20\x23\x23\x23\x23" "\n");for(int i=(0x14c+9635-0x26ef);i<z0d58e923ee/(0x42+9521-0x256f);i++){if(i%(0x142+3101-0xd5b)==(0xfb6+3308-0x1ca2)){char ze00583cac9[(0x4e6+3443-0x1249)];switch(i/(0xaf4+984-0xec8)){case(0xb04+4629-0x1d18):sprintf(ze00583cac9,"\x2b\x2d\x35\x56");break;case(0x547+8400-0x2615):sprintf(ze00583cac9,"\x2b\x2d\x35\x2e\x31\x32\x56");break;case(0x33b+7108-0x1efc):sprintf(ze00583cac9,"\x2b\x31\x30\x56");break;case(0x36a+2246-0xc2c):sprintf(ze00583cac9,"\x2b\x31\x30\x2e\x32\x34\x56");break;case(0x210+7607-0x1fc2):sprintf(ze00583cac9,"\x2b\x2d\x31\x30\x56");break;case(0x334+4913-0x165f):sprintf(ze00583cac9,"\x2b\x2d\x31\x30\x2e\x32\x34\x56");break;default:sprintf(ze00583cac9,"\x2b\x35\x2e\x31\x32\x56");break;}SG_PRINTF(INFO,"\x2a\x2a\x2a\x2a\x2a\x20\x4f\x66\x66\x73\x65\x74\x20\x61\x6e\x64\x20\x47\x61\x69\x6e\x20\x56\x61\x6c\x75\x65\x73\x20\x66\x6f\x72\x20\x73\x70\x61\x6e\x20\x25\x73\x20\x2a\x2a\x2a\x2a\x2a" "\n",ze00583cac9);}SG_PRINTF(INFO,"\x41\x44\x43\x20\x43\x48\x25\x69\x3a\x20\x6f\x66\x66\x73\x65\x74\x20\x3d\x20\x25\x69\x20\x2c\x20\x67\x61\x69\x6e\x20\x3d\x20\x25\x69" "\n",(i%(0x38d+5904-0x1a99)+(0x1db1+1472-0x2370)),z3dc8bd2ec2[i].offset,z3dc8bd2ec2[i].z0754dd67cc);}
#endif
}else{SG_PRINTF(INFO,"\x50\x52\x4f\x4d\x20\x49\x32\x43\x20\x65\x72\x72\x6f\x72\x2e" "\n");}
#endif
}static void sg_ModelStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
volatile struct zfe084664e7*z8a0c00cf66;z5b2d2d8b5f*za8d68958c5;z5b2d2d8b5f*z3dc8bd2ec2;uint32_t channel,i,z33d8b3e65a,z08d378f018;int32_t zfa2215d30f;z8a0c00cf66=(volatile struct zfe084664e7*)ssGetPWorkValue(S,z0194338df7);za8d68958c5=(z5b2d2d8b5f*)ssGetPWorkValue(S,z2e8373622e);z3dc8bd2ec2=(z5b2d2d8b5f*)ssGetPWorkValue(S,z4ad204bd79);
#if zd4c1aa112f
SG_PRINTF(INFO,"\x54\x65\x73\x74\x31\x20\x76\x61\x6c\x75\x65\x3a\x20\x30\x78\x25\x58" "\n",z8a0c00cf66->test1);z8a0c00cf66->test2=2863311530;SG_PRINTF(INFO,"\x54\x65\x73\x74\x32\x20\x76\x61\x6c\x75\x65\x3a\x20\x30\x78\x25\x58" "\n",z8a0c00cf66->test2);
#endif
z8a0c00cf66->zd7dbb5d332=(0x1b60+1170-0x1ff2);zfa2215d30f=(uint32_t)mxGetPr(z8fd86139be)[(0x32b+3836-0x1227)];z8a0c00cf66->za743cc44e3=zfa2215d30f|zfa2215d30f<<(0x1b5a+1157-0x1fdc)|zfa2215d30f<<(0x116a+1426-0x16f6)|zfa2215d30f<<(0x12b6+2626-0x1cef)|zfa2215d30f<<(0x1289+3640-0x20b5)|zfa2215d30f<<(0x17dc+2237-0x208a)|zfa2215d30f<<(0x2ad+6331-0x1b56)|zfa2215d30f<<(0xb1a+4113-0x1b16);z8a0c00cf66->zc070e3aa0a=(uint32_t)mxGetPr(z940b683687)[(0x2a1+3113-0xeca)];z33d8b3e65a=(uint32_t)mxGetPr(z3c99a98138)[(0x1d2+9258-0x25fc)];if(z33d8b3e65a==(0xb65+3537-0x1936)){z08d378f018=((uint32_t)mxGetPr(za7d1207929)[(0x10f9+1513-0x16e2)]-(0x219b+389-0x231f));}else if(z33d8b3e65a==(0x127f+465-0x144f)){z08d378f018=((uint32_t)mxGetPr(z12b68fbdab)[(0xbe0+439-0xd97)]-(0x87c+1076-0xcae));}else{z08d378f018=(0x8bc+2182-0x1142);}z8a0c00cf66->z9bbe1f0399=((0x3ea+1628-0xa43)|z33d8b3e65a<<(0xedc+2676-0x194d)|z08d378f018<<(0x3a6+1018-0x79a));
#if zd4c1aa112f
SG_PRINTF(INFO,"\x23\x23\x23\x23\x20\x41\x70\x70\x6c\x69\x65\x64\x20\x4f\x66\x66\x73\x65\x74\x20\x61\x6e\x64\x20\x47\x61\x69\x6e\x20\x43\x6f\x72\x72\x65\x63\x74\x69\x6f\x6e\x20\x56\x61\x6c\x75\x65\x73\x20\x23\x23\x23\x23" "\n");SG_PRINTF(INFO,"\x73\x70\x61\x6e\x20\x70\x61\x72\x61\x6d\x65\x74\x65\x72\x3a\x20\x30\x78\x25\x58" "\n",zfa2215d30f);switch(zfa2215d30f-(0x275+2893-0xdc1)){case(0x1cb+6406-0x1ad0):SG_PRINTF(INFO,"\x41\x44\x43\x20\x73\x70\x61\x6e\x20\x69\x73\x3a\x20\x2b\x2d\x35\x56" "\n");break;case(0x3d7+4056-0x13ad):SG_PRINTF(INFO,"\x41\x44\x43\x20\x73\x70\x61\x6e\x20\x69\x73\x3a\x20\x2b\x2d\x35\x2e\x31\x32\x56" "\n");break;case(0x478+741-0x75a):SG_PRINTF(INFO,"\x41\x44\x43\x20\x73\x70\x61\x6e\x20\x69\x73\x3a\x20\x2b\x31\x30\x56" "\n");break;case(0xbf1+883-0xf60):SG_PRINTF(INFO,"\x41\x44\x43\x20\x73\x70\x61\x6e\x20\x69\x73\x3a\x20\x2b\x31\x30\x2e\x32\x34\x56" "\n");break;case(0x306+317-0x43e):SG_PRINTF(INFO,"\x41\x44\x43\x20\x73\x70\x61\x6e\x20\x69\x73\x3a\x20\x2b\x2d\x31\x30\x56" "\n");break;case(0xdc7+1801-0x14ca):SG_PRINTF(INFO,"\x41\x44\x43\x20\x73\x70\x61\x6e\x20\x69\x73\x3a\x20\x2b\x2d\x31\x30\x2e\x32\x34\x56" "\n");break;default:SG_PRINTF(INFO,"\x41\x44\x43\x20\x73\x70\x61\x6e\x20\x69\x73\x3a\x20\x2b\x35\x2e\x31\x32\x56" "\n");break;}SG_PRINTF(INFO,"\n");
#endif
for(i=(0x977+439-0xb2e);i<mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0xa8c+1620-0x10df);z8a0c00cf66->comp[channel].z0754dd67cc=z3dc8bd2ec2[channel+(zfa2215d30f-(0x115+8084-0x20a8))*(0x178+3299-0xe57)].z0754dd67cc;za8d68958c5[channel].z0754dd67cc=z8a0c00cf66->comp[channel].z0754dd67cc;z8a0c00cf66->comp[channel].offset=z3dc8bd2ec2[channel+(zfa2215d30f-(0x96d+6838-0x2422))*(0xbd3+146-0xc61)].offset;za8d68958c5[channel].offset=z8a0c00cf66->comp[channel].offset;
#if zd4c1aa112f
SG_PRINTF(INFO,"\x69\x6e\x64\x65\x78\x20\x3d\x20\x25\x69\x2c\x20\x41\x44\x43\x20\x43\x48\x25\x69\x3a\x20\x6f\x66\x66\x73\x65\x74\x3d\x20\x25\x69\x20\x2c\x20\x67\x61\x69\x6e\x3d\x25\x69" "\n",i,channel+(0x572+3521-0x1332),za8d68958c5[channel].offset,za8d68958c5[channel].z0754dd67cc);
#endif
}
#endif
}static void sg_ModelStep(SimStruct*S){
#ifndef MATLAB_MEX_FILE
uint32_t i,channel,z33d8b3e65a;int16_t z58960266a3;uint16_t zeb269dee7b;double z247776ba29,zc19b62e2e0,z0754dd67cc,offset;double*y;volatile struct zfe084664e7*z8a0c00cf66;z5b2d2d8b5f*za8d68958c5;z8a0c00cf66=(volatile struct zfe084664e7*)ssGetPWorkValue(S,z0194338df7);za8d68958c5=(z5b2d2d8b5f*)ssGetPWorkValue(S,z2e8373622e);z33d8b3e65a=(uint32_t)mxGetPr(z3c99a98138)[(0x96+7780-0x1efa)];if(z33d8b3e65a==(0x751+3688-0x15b6)){z8a0c00cf66->z9bbe1f0399=(z8a0c00cf66->z9bbe1f0399|(0x5af+6037-0x1d43)<<(0x15f6+1286-0x1aef));}for(i=(0x74b+718-0xa19);i<mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0xbf8+2673-0x1668);z58960266a3=(int16_t)(z8a0c00cf66->data[channel].result>>(0x187+1083-0x5ba));zeb269dee7b=(uint16_t)z58960266a3;z0754dd67cc=(0x190b+2642-0x235c)-(double)za8d68958c5[channel].z0754dd67cc/262144.0f;offset=(double)za8d68958c5[channel].offset/4.0f;if(z6b36f492e0){z247776ba29=(double)zeb269dee7b*z0754dd67cc-offset;zc19b62e2e0=(double)z58960266a3*z0754dd67cc-offset;}else{z247776ba29=(double)zeb269dee7b;zc19b62e2e0=(double)z58960266a3;}y=(double*)ssGetOutputPortSignal(S,i);switch((uint32_t)mxGetPr(z8fd86139be)[(0x1058+5270-0x24ee)]){case(0x16f5+304-0x1825):y[(0x20d+6022-0x1993)]=(0x266a+47-0x2699);break;case(0x90d+5613-0x1ef9):y[(0xca9+2048-0x14a9)]=(z247776ba29/65535.0f)*5.12;break;case(0x78d+5982-0x1ee9):y[(0x1b4+6000-0x1924)]=(zc19b62e2e0/32767.0f)*5.0;break;case(0x16a7+1696-0x1d44):y[(0x6c0+3272-0x1388)]=(zc19b62e2e0/32767.0f)*5.12;break;case(0xa12+155-0xaa9):y[(0x25c+8254-0x229a)]=(z247776ba29/65535.0f)*10.0;break;case(0x48+8026-0x1f9d):y[(0x1dbf+26-0x1dd9)]=(z247776ba29/65535.0f)*10.24;break;case(0x1dc1+1457-0x236c):y[(0x5bb+725-0x890)]=(zc19b62e2e0/32767.0f)*10.0;break;case(0x1336+196-0x13f3):y[(0xc52+2051-0x1455)]=(zc19b62e2e0/32767.0f)*10.24;break;default:y[(0x6cc+7994-0x2606)]=(0x448+2719-0xee7);}
#if zd4c1aa112f
SG_PRINTF(INFO,"\x2a\x2a\x2a\x2a\x2a\x20\x41\x44\x43\x20\x43\x48\x25\x64\x20\x2a\x2a\x2a\x2a\x2a" "\n",channel+(0x1ef2+440-0x20a9));SG_PRINTF(INFO,"\x52\x41\x57\x20\x75\x6e\x73\x69\x67\x6e\x65\x64\x3a\x20\x30\x78\x25\x58\x20\x2c\x20\x73\x69\x67\x6e\x65\x64\x3a\x20\x30\x78\x25\x58" "\n",zeb269dee7b,z58960266a3);SG_PRINTF(INFO,"\x52\x41\x57\x20\x6f\x66\x66\x73\x65\x74\x20\x3d\x20\x25\x64\x20\x2c\x20\x52\x41\x57\x20\x67\x61\x69\x6e\x20\x3d\x20\x25\x64" "\n",za8d68958c5[channel].offset,za8d68958c5[channel].z0754dd67cc);SG_PRINTF(INFO,"\x45\x66\x66\x65\x63\x74\x69\x76\x65\x20\x6f\x66\x66\x73\x65\x74\x20\x3d\x20\x25\x66\x20\x2c\x20\x45\x66\x66\x65\x63\x74\x69\x76\x65\x20\x67\x61\x69\x6e\x20\x3d\x20\x25\x66" "\n",offset,z0754dd67cc);SG_PRINTF(INFO,"\x43\x6f\x6d\x70\x65\x6e\x73\x61\x74\x65\x64\x20\x76\x61\x6c\x75\x65\x3a\x20\x25\x66" "\n",y[(0x89f+1027-0xca2)]);
#endif
}
#endif
}static void sg_ModelStop(SimStruct*S){
#ifndef MATLAB_MEX_FILE
volatile struct zfe084664e7*z8a0c00cf66;z8a0c00cf66=(volatile struct zfe084664e7*)ssGetPWorkValue(S,z0194338df7);z8a0c00cf66->z9bbe1f0399=(z8a0c00cf66->z9bbe1f0399|(0xf7+8894-0x23b5)<<(0x223b+486-0x2421));free((z5b2d2d8b5f*)ssGetPWorkValue(S,z2e8373622e));
#endif
}
#ifndef MATLAB_MEX_FILE
uint32_t z301b737812(volatile z111719ca84*z9dfcf27d92,uint8_t*z703a8aaab7,uint32_t z37b2e8d405){double start;uint32_t i,z26dbd73a5e,z812c65ff2f;uint8_t z7be9105675;
#if zd4c1aa112f
SG_PRINTF(INFO,"\x50\x52\x4f\x4d\x52\x65\x67\x2d\x3e\x53\x52\x20\x3d\x20\x30\x78\x25\x58" "\n",z9dfcf27d92->z76b7ec4de7);
#endif
z9dfcf27d92->ze32a66eb4c=(0x19a5+2916-0x2502);sg_wait_s(0.100);z9dfcf27d92->z503cfbc131=(0xae2+1085-0xf1f);sg_wait_s(0.100);
#if zd4c1aa112f
SG_PRINTF(INFO,"\x50\x6f\x73\x74\x20\x52\x53\x54\x20\x50\x52\x4f\x4d\x52\x65\x67\x2d\x3e\x53\x52\x20\x3d\x20\x30\x78\x25\x58" "\n",z9dfcf27d92->z76b7ec4de7);SG_PRINTF(INFO,"\x43\x4d\x3a\x20\x30\x78\x25\x58" "\n",z9dfcf27d92->ze32a66eb4c);SG_PRINTF(INFO,"\x50\x6f\x73\x74\x20\x52\x53\x54\x20\x50\x52\x4f\x4d\x52\x65\x67\x2d\x3e\x53\x52\x20\x3d\x20\x30\x78\x25\x58" "\n",z9dfcf27d92->z76b7ec4de7);
#endif
z9dfcf27d92->z503cfbc131|=(z174b59c07e<<(0x56d+6742-0x1fb3));
#if zd4c1aa112f
SG_PRINTF(INFO,"\x50\x72\x6f\x6d\x20\x61\x64\x64\x72\x65\x73\x73\x20\x69\x73\x3a\x20\x30\x78\x25\x58" "\n",(uintptr_t)z9dfcf27d92);
#endif
for(z812c65ff2f=(0x15d0+522-0x17da);z812c65ff2f<z0d58e923ee;z812c65ff2f+=z29b704d2e2){z9dfcf27d92->ze32a66eb4c=(0x890+326-0x9d0);z9dfcf27d92->z1282cae458=z37b2e8d405+z812c65ff2f;z9dfcf27d92->ze32a66eb4c=(0x216d+234-0x224f);z9dfcf27d92->z503cfbc131|=(z29b704d2e2);z9dfcf27d92->z503cfbc131|=((0x2da+1327-0x808)<<(0x60a+3689-0x146b));
#if zd4c1aa112f
SG_PRINTF(INFO,"\x50\x72\x65\x2d\x74\x72\x61\x6e\x73\x61\x63\x74\x69\x6f\x6e\x20\x77\x72\x69\x74\x65\x20\x66\x69\x66\x6f\x20\x66\x69\x6c\x6c\x20\x6c\x65\x76\x65\x6c\x3a\x20\x30\x78\x25\x58" "\n",(z9dfcf27d92->z76b7ec4de7&(0xa0a+3311-0x16ea)));
#endif
z9dfcf27d92->ze32a66eb4c|=((0x679+1202-0xb2a)<<(0x17ca+3467-0x2550));z26dbd73a5e=(0x1a8c+2329-0x23a5);start=sg_getElapsedTime();while(z26dbd73a5e<z29b704d2e2){if(sg_getElapsedTime()-start>3.0){
#if zd4c1aa112f
SG_PRINTF(INFO,"\x50\x52\x4f\x4d\x20\x49\x32\x43\x20\x61\x64\x63\x20\x76\x61\x6c\x75\x65\x73\x20\x74\x69\x6d\x65\x6f\x75\x74\x2e\x20\x25\x69\x20\x62\x79\x74\x65\x73\x20\x72\x65\x61\x64\x2e" "\n",z26dbd73a5e);
#endif
return I2C_ERROR_OK;}z26dbd73a5e=(z9dfcf27d92->z76b7ec4de7&65280)>>(0x4a4+3977-0x1425);}
#if zd4c1aa112f
SG_PRINTF(INFO,"\x50\x6f\x73\x74\x2d\x74\x72\x61\x6e\x73\x61\x63\x74\x69\x6f\x6e\x20\x77\x72\x69\x74\x65\x20\x66\x69\x66\x6f\x20\x66\x69\x6c\x6c\x20\x6c\x65\x76\x65\x6c\x3a\x20\x30\x78\x25\x58" "\n",(z9dfcf27d92->z76b7ec4de7&(0x1e95+1557-0x23ab)));SG_PRINTF(INFO,"\x42\x79\x74\x65\x73\x20\x61\x71\x75\x69\x72\x65\x64\x3a\x30\x78\x25\x58" "\n",z26dbd73a5e);
#endif
for(i=z812c65ff2f;i<z26dbd73a5e+z812c65ff2f;i++){z703a8aaab7[i]=z9dfcf27d92->zb366ad92a0;
#if zd4c1aa112f
SG_PRINTF(INFO,"\x44\x61\x74\x61\x20\x42\x79\x74\x65\x20\x25\x64\x3a\x20\x30\x78\x25\x58" "\n",i,z9dfcf27d92->zb366ad92a0);
#endif
z9dfcf27d92->ze32a66eb4c=((0x5da+911-0x968)<<(0xaef+1327-0x101a));}}
#if zd4c1aa112f
SG_PRINTF(INFO,"\x41\x44\x43\x20\x43\x4f\x4d\x50\x20\x56\x41\x4c\x55\x45\x53\x3a" "\n");for(i=(0x1237+4872-0x253f);i<z0d58e923ee;i+=z29b704d2e2){for(z812c65ff2f=(0xd56+2882-0x1898);z812c65ff2f<z29b704d2e2;z812c65ff2f+=(0xcab+4019-0x1c5c)){SG_PRINTF(INFO,"\x25\x64\x20" "\n",(int16_t)(((int16_t)z703a8aaab7[i+z812c65ff2f]<<(0x511+6260-0x1d7d))+z703a8aaab7[i+z812c65ff2f+(0x1313+1515-0x18fd)]));}SG_PRINTF(INFO,"\n");}
#endif
for(i=(0xbd4+4207-0x1c43);i<z0d58e923ee;i+=(0x1c14+133-0x1c97)){z7be9105675=z703a8aaab7[i];z703a8aaab7[i]=z703a8aaab7[i+(0x42b+3114-0x1054)];z703a8aaab7[i+(0x157b+4030-0x2538)]=z7be9105675;}z9dfcf27d92->ze32a66eb4c=(0x122b+645-0x14a9);
#if zd4c1aa112f
SG_PRINTF(INFO,"\x50\x52\x4f\x4d\x52\x65\x67\x2d\x3e\x53\x52\x20\x3d\x20\x30\x78\x25\x58" "\n",z9dfcf27d92->z76b7ec4de7);
#endif
return I2C_ERROR_OK;}
#endif
#include "sg_sfcn_glue.h"   


// Copyright 2006-2026 Speedgoat GmbH

#define         S_FUNCTION_LEVEL        (0x982+6096-0x2150)
#undef          S_FUNCTION_NAME
#define         S_FUNCTION_NAME         sg_IO901_IO902_get_state_s
#include        <stddef.h>
#include        <stdlib.h>
#include        <stdint.h>
#include        "simstruc.h"
#include        "sg_IO901_IO902.h"
#ifdef          MATLAB_MEX_FILE
#include        "mex.h"
#endif
#include    "sg_callback.h"
#define zdf24515981        ((0x1feb+1501-0x25c4))
#define z1fed5b96d5              ssGetSFcnParam(S, (0x2b2+8440-0x23aa))
#define zabe1e0cd2c        ssGetSFcnParam(S, (0x1895+2846-0x23b2))
#define z702a26a5e9              ssGetSFcnParam(S, (0x5c1+3867-0x14da))
#define zfaa050b79d             ssGetSFcnParam(S, (0x619+4475-0x1791))
#define z2e6483d505            ((0x12aa+666-0x1544))
#define zc5ce4cb81a            ((0x14f4+3944-0x245c))
#define z2b17e2ee3b            ((0xcb0+5122-0x20b2))
#define z95835284b8             ((0x1789+8641-0x25c3))
#define zdd9aa31c07             (21264)
#define z55367ad797           "\x53\x43\x52\x41\x4d\x4e\x65\x74\x20\x47\x54"
static char msg[(0xd3d+3598-0x1a4b)];static void mdlInitializeSizes(SimStruct*S){int i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n""\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x7a+111-0xe9));ssSetNumDiscStates(S,(0x138+8491-0x2263));ssSetNumInputPorts(S,(0x253+2679-0xcca));ssSetNumOutputPorts(S,(0x6ea+3116-0x1315));ssSetOutputPortWidth(S,(0x9a4+5043-0x1d57),(0x7fd+341-0x951));ssSetOutputPortDataType(S,(0x10ec+2785-0x1bcd),SS_UINT32);ssSetNumSampleTimes(S,(0x85b+7634-0x262c));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0xa93+5301-0x1f48));ssSetNumNonsampledZCs(S,(0x176a+808-0x1a92));for(i=(0xf17+5655-0x252e);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x1366+1708-0x1a12));}ssSetOptions(S,SS_OPTION_RUNTIME_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(zabe1e0cd2c)[(0x306+7843-0x21a9)]==-1.0){ssSetSampleTime(S,(0x46c+6457-0x1da5),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x17ab+3879-0x26d2),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x525+4736-0x17a5),mxGetPr(zabe1e0cd2c)[(0x3f3+3383-0x112a)]);ssSetOffsetTime(S,(0x3d1+2866-0xf03),0.0);}}static void sg_ModelLoad(SimStruct*S){}static void sg_ModelStart(SimStruct*S){}
#ifndef MATLAB_MEX_FILE
uint32_t zd94d692be2(z78d32bde66*zae10e3f17f,uint32_t zfb5864bba6,uint32_t*val){switch(zfb5864bba6){case z4cffc2f0b2:*val=z2f79b3ce40(zae10e3f17f,z0b8c5d9cd1);break;case z10ffdb545a:*val=z2f79b3ce40(zae10e3f17f,zd96d34ea7d);break;case zeecab84541:*val=z2f79b3ce40(zae10e3f17f,zc8305b5c82);break;case z3ddc07895c:*val=z2f79b3ce40(zae10e3f17f,z504b467e27);break;case zd3036dfb21:*val=z2f79b3ce40(zae10e3f17f,z3467d7a3c0)>>(0x162c+4244-0x26a8);break;case z9b47479987:*val=(z2f79b3ce40(zae10e3f17f,z3467d7a3c0)&zbda6535434)>>(0x290+4762-0x1522);break;case zda19d5ddd1:*val=(z2f79b3ce40(zae10e3f17f,z3467d7a3c0)&z47f588865a)?(0x1de6+2071-0x25fc):(0x23bd+190-0x247b);break;case z18645dde27:*val=(z2f79b3ce40(zae10e3f17f,z3467d7a3c0)&zd8f8076068)?(0x173f+2847-0x225d):(0x1e65+155-0x1f00);break;case zdf91ed8876:*val=z2f79b3ce40(zae10e3f17f,zcedf27d995)&(0xe3c+5747-0x24ae);break;case ze6a190570a:*val=z2f79b3ce40(zae10e3f17f,zca99244c80);break;case z972cd03334:*val=(z2f79b3ce40(zae10e3f17f,z3467d7a3c0)&z400fe4c453)?(0x15d0+735-0x18ae):(0x75a+1496-0xd32);break;case z430e2fe086:*val=(z2f79b3ce40(zae10e3f17f,z00a167e921)>>(0x8bb+3468-0x162f))+(0x6a3+2705-0x1133);break;case z9c6a241d9c:*val=z2f79b3ce40(zae10e3f17f,zd31d0adf01)>>(0xd99+2211-0x1624);break;case z53332f4605:*val=(z2f79b3ce40(zae10e3f17f,z3467d7a3c0)&z26925dc366)?(0x208a+272-0x2199):(0xc9b+2468-0x163f);break;case z154c5fec50:*val=z2f79b3ce40(zae10e3f17f,za5d8e62835);break;case z4a59ed83bc:*val=(z2f79b3ce40(zae10e3f17f,z3467d7a3c0)&z0a3d3e254b)?(0x1177+3338-0x1e80):(0x48b+1172-0x91f);break;case zcd113d1a6f:*val=(z2f79b3ce40(zae10e3f17f,z3467d7a3c0)&zdefbe72d1f)?(0x5d8+5705-0x1c20):(0x1aeb+981-0x1ec0);break;case z616ff59839:*val=(z2f79b3ce40(zae10e3f17f,z3467d7a3c0)&z2cde59733e)?(0x23c+162-0x2dd):(0x252f+432-0x26df);break;case z4522a05e8b:*val=(z2f79b3ce40(zae10e3f17f,z3467d7a3c0)&z20c32a2b03)?(0x456+4854-0x174b):(0x435+6390-0x1d2b);break;case z7e6cc5c15d:*val=(z2f79b3ce40(zae10e3f17f,z3467d7a3c0)&z371efee7e9)?(0x1993+1039-0x1da1):(0x9ef+1150-0xe6d);break;case z2dcb54e260:*val=(z2f79b3ce40(zae10e3f17f,z00a167e921)&zb1149c4c67)?(0x1ebb+347-0x2015):(0x8d6+2157-0x1143);break;case z8a6a7287b8:*val=(z2f79b3ce40(zae10e3f17f,z00a167e921)&z99f6a90c06)?(0x18e2+322-0x1a23):(0x1568+4317-0x2645);break;case z07fa2857cf:*val=(z2f79b3ce40(zae10e3f17f,z00a167e921)&z219d3b4562)?(0x6d8+3561-0x14c0):(0xdf2+463-0xfc1);break;case zda5e4e23f8:*val=(z2f79b3ce40(zae10e3f17f,z0194814bbb)&z4870c1c6de)?(0xe2c+994-0x120e):(0xc8+442-0x281);break;case z1c88efa91f:*val=(z2f79b3ce40(zae10e3f17f,z0194814bbb)&zaa09e848eb)?(0x1ca+7720-0x1ff1):(0x21b+6305-0x1abc);break;case z0312fa97b7:*val=(z2f79b3ce40(zae10e3f17f,z0194814bbb)&z17f480a646)?(0x446+4536-0x15fd):(0x161+183-0x218);break;case zd48de2dfc6:*val=(z2f79b3ce40(zae10e3f17f,zc5c239bae8)&z08e94c98fb)?(0xf5d+813-0x1289):(0x457+4518-0x15fd);break;case z7e4d3eb9bb:*val=(z2f79b3ce40(zae10e3f17f,zd31d0adf01)&z57700002a6)?(0x10c2+716-0x138e):(0x11f3+4125-0x220f);break;case zee7e3c684a:*val=z2f79b3ce40(zae10e3f17f,z2317f9bc10);break;case zb62a041887:*val=z2f79b3ce40(zae10e3f17f,z240d834252);break;case z16aaca8fc2:*val=z2f79b3ce40(zae10e3f17f,z62ddca45c5);break;default:return z75ea319f1c;}return z8d2ae93cab;}
#endif
static void sg_ModelStep(SimStruct*S){
#ifndef MATLAB_MEX_FILE
uint32_t*val=(uint32_t*)ssGetOutputPortSignal(S,(0x222+6283-0x1aad));uint32_t z4108b73b87=(uint32_t)mxGetPr(z1fed5b96d5)[(0xc51+5550-0x21ff)];z78d32bde66*zae10e3f17f;zae10e3f17f=(z78d32bde66*)sg_module_get_custom_data(z6cd618c289,(uint32_t)mxGetPr(zfaa050b79d)[(0xbc2+4426-0x1d0c)]);if(zae10e3f17f==NULL){ssSetErrorStatus(S,"\x49\x4f\x39\x30\x31\x20\x47\x65\x74\x20\x53\x74\x61\x74\x65\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x72\x65\x74\x72\x69\x65\x76\x65\x20\x6d\x6f\x64\x75\x6c\x65\x20\x66\x72\x6f\x6d\x20\x72\x65\x67\x69\x73\x74\x72\x79\x20\x69\x6e\x20\x4d\x6f\x64\x65\x6c\x53\x74\x65\x70" "\n");return;}if(zd94d692be2(zae10e3f17f,z4108b73b87,val)==z75ea319f1c){sprintf(msg,"\x49\x6e\x70\x75\x74\x20\x53\x74\x61\x74\x65\x49\x64\x20\x76\x61\x6c\x75\x65\x20\x30\x78\x25\x78\x20\x69\x73\x20\x6e\x6f\x74\x20\x76\x61\x6c\x69\x64",z4108b73b87);ssSetErrorStatus(S,msg);return;}
#endif
}static void sg_ModelStop(SimStruct*S){}
#include "sg_sfcn_glue.h"   


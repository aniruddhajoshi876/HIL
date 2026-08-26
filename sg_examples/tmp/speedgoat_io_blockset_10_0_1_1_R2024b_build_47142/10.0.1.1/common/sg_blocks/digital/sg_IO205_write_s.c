// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL (0x836+2645-0x1289)
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME sg_IO205_write_s
#include "sg_io205.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "simstruc.h"
#ifdef MATLAB_MEX_FILE
#include "mex.h"
#else
#include "sg_common.h"
#include "sg_module_registry.h"
#include "sg_module_types.h"
#include "sg_printf.h"
#endif
#define SG_EARLY_INIT 
#include "sg_callback.h"
#define za00184cdc1   ssGetSFcnParam(S, (0x214+7405-0x1f01))
#define z2cc9a52544   ssGetSFcnParam(S, (0x390+6517-0x1d04))
#define z3832b85a32  ssGetSFcnParam(S, (0x80f+3616-0x162d))
#define z702a26a5e9       ssGetSFcnParam(S, (0x2b6+4577-0x1494))
#define zdf24515981 ((0x1697+3802-0x256d))
#define z2e6483d505 ((0x59c+3891-0x14cf))
#define zc5ce4cb81a ((0x453+3916-0x139f))
#define z0194338df7 ((0x9c6+1917-0x1143))
#define z2b17e2ee3b      ((0x1b22+2187-0x23ac))
#define THRESHOLD 0.5
static char_T msg[(0x1e34+2248-0x25fc)];static void mdlInitializeSizes(SimStruct*S){uint16_T i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x1882+1689-0x1f1b));ssSetNumDiscStates(S,(0x1969+1763-0x204c));ssSetNumOutputPorts(S,(0x512+3891-0x1445));switch((uint8_T)mxGetPr(z2cc9a52544)[(0x1e5d+1949-0x25fa)]){case(0x3c3+7097-0x1f7b):ssSetNumInputPorts(S,(0x961+1346-0xe83));for(i=(0x1d40+1839-0x246f);i<(0xb0+4853-0x1385);i++){ssSetInputPortWidth(S,i,(0x8a6+7585-0x2646));ssSetInputPortRequiredContiguous(S,i,(0x1fc9+1112-0x2420));}break;case(0x10f+780-0x419):ssSetNumInputPorts(S,(0x1457+4600-0x262f));for(i=(0x57d+2901-0x10d2);i<(0x1c55+2283-0x2520);i++){ssSetInputPortWidth(S,i,(0x48a+3910-0x13cf));ssSetInputPortDataType(S,i,SS_BOOLEAN);ssSetInputPortRequiredContiguous(S,i,(0x1832+3300-0x2515));}break;case(0x2c+1669-0x6ae):ssSetNumInputPorts(S,(0x190+8338-0x2221));ssSetInputPortWidth(S,(0x444+5933-0x1b71),(0x435+1599-0xa54));ssSetInputPortRequiredContiguous(S,(0x613+75-0x65e),(0x275+2144-0xad4));break;case(0x3f2+5144-0x1806):ssSetNumInputPorts(S,(0x1608+2993-0x21b8));ssSetInputPortWidth(S,(0xd4d+4290-0x1e0f),(0x4e6+563-0x6f9));ssSetInputPortDataType(S,(0x10a7+2542-0x1a95),SS_BOOLEAN);ssSetInputPortRequiredContiguous(S,(0x5c7+1939-0xd5a),(0x823+5974-0x1f78));break;case(0x4a5+5249-0x1921):ssSetNumInputPorts(S,(0x1820+2050-0x2021));ssSetInputPortWidth(S,(0x37f+6973-0x1ebc),(0xb14+1158-0xf99));ssSetInputPortDataType(S,(0x1d61+607-0x1fc0),SS_UINT32);ssSetInputPortRequiredContiguous(S,(0x10b4+3909-0x1ff9),(0x1297+614-0x14fc));break;}ssSetNumSampleTimes(S,(0x63+877-0x3cf));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x168a+3443-0x23fd));ssSetNumNonsampledZCs(S,(0xd06+1922-0x1488));for(i=(0x979+3840-0x1879);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x1ad3+720-0x1da3));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0x5d7+2053-0xddc)]==-1.0){ssSetSampleTime(S,(0x1027+1681-0x16b8),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x162+6160-0x1972),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x14b1+1887-0x1c10),mxGetPr(z3832b85a32)[(0xd0b+2139-0x1566)]);ssSetOffsetTime(S,(0x70a+2341-0x102f),0.0);}}
#ifndef MATLAB_MEX_FILE
static void sg_ModelLoad(SimStruct*S){SG_PRINTF(DEBUG,"\x25\x73\x20\x28\x49\x44\x20\x25\x64\x29\x20\x57\x72\x69\x74\x65\x3a\x20\x25\x73\x20\x73\x67\x5f\x4d\x6f\x64\x65\x6c\x4c\x6f\x61\x64" "\n",DEVNAME,(int)mxGetPr(za00184cdc1)[(0x1140+4702-0x239e)],sg_isFirstModelLoad()?"\x20\x46\x69\x72\x73\x74":"");}static void sg_ModelStart(SimStruct*S){SG_PRINTF(DEBUG,"\x25\x73\x20\x28\x49\x44\x20\x25\x64\x29\x20\x57\x72\x69\x74\x65\x3a\x20\x73\x67\x5f\x4d\x6f\x64\x65\x6c\x53\x74\x61\x72\x74" "\n",DEVNAME,(int)mxGetPr(za00184cdc1)[(0x267a+36-0x269e)]);}static void sg_ModelStep(SimStruct*S){uint32_T i,output;real_T*y1;boolean_T*y2;uint32_T*z671e76e748;int za0d38ae598=(int)mxGetPr(za00184cdc1)[(0x2da+3538-0x10ac)];z6003b3247e*zae10e3f17f=(z6003b3247e*)sg_module_get_custom_data(zd215f6920d,za0d38ae598);if(!zae10e3f17f){sprintf(msg,"\x25\x73\x20\x28\x49\x44\x20\x25\x64\x29\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x72\x65\x74\x72\x69\x65\x76\x65\x20\x6d\x6f\x64\x75\x6c\x65\x20\x73\x74\x61\x74\x65\x20\x66\x72\x6f\x6d\x20\x72\x65\x67\x69\x73\x74\x72\x79" "\n",DEVNAME,za0d38ae598);ssSetErrorStatus(S,msg);return;}switch((uint8_T)mxGetPr(z2cc9a52544)[(0x445+1340-0x981)]){case(0x3b9+8294-0x241e):output=(0x25+5464-0x157d);for(i=(0x3a4+6985-0x1eed);i<(0x647+2685-0x10a4);i++){y1=(real_T*)ssGetInputPortSignal(S,i);if(y1[(0x18cf+2436-0x2253)]>=THRESHOLD){output|=((0xf44+426-0x10ed)<<i);}}break;case(0x953+1126-0xdb7):output=(0x1a27+1078-0x1e5d);for(i=(0xdb+6862-0x1ba9);i<(0xc62+2449-0x15d3);i++){y2=(boolean_T*)ssGetInputPortSignal(S,i);if(y2[(0x163d+3264-0x22fd)]){output|=((0x1a5+4060-0x1180)<<i);}}break;case(0xe25+663-0x10b9):output=(0x5f8+767-0x8f7);y1=(real_T*)ssGetInputPortSignal(S,(0x1d61+890-0x20db));for(i=(0x149f+3249-0x2150);i<(0xe4c+1892-0x1590);i++){if(y1[i]>=THRESHOLD){output|=((0x1a11+2036-0x2204)<<i);}}break;case(0x120+5109-0x1511):output=(0x1f48+1639-0x25af);y2=(boolean_T*)ssGetInputPortSignal(S,(0x1a86+1189-0x1f2b));for(i=(0x2040+1209-0x24f9);i<(0x21a+3061-0xdef);i++){if(y2[i]){output|=((0x1697+3882-0x25c0)<<i);}}break;case(0x91f+606-0xb78):z671e76e748=(uint32_T*)ssGetInputPortSignal(S,(0x3d5+1030-0x7db));output=z671e76e748[(0x6f0+1620-0xd44)];break;}zae10e3f17f->z919abdb780[(0x3a9+1277-0x8a6)]=output;}static void sg_ModelStop(SimStruct*S){SG_PRINTF(DEBUG,"\x25\x73\x20\x28\x49\x44\x20\x25\x64\x29\x20\x57\x72\x69\x74\x65\x3a\x20\x73\x67\x5f\x4d\x6f\x64\x65\x6c\x53\x74\x6f\x70" "\n",DEVNAME,(int)mxGetPr(za00184cdc1)[(0x1a1+1346-0x6e3)]);}
#endif 
#include "sg_sfcn_glue.h" 


// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL    (0x3f5+4893-0x1710)
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME     sg_IO204_read_s
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include "sg_io204.h"
#include "simstruc.h" 
#ifdef MATLAB_MEX_FILE
#include "mex.h"
#else
#include "sg_common.h"
#include "sg_printf.h"
#include "sg_module_types.h"
#include "sg_module_registry.h"
#endif
#define SG_EARLY_INIT 
#include "sg_callback.h"
#define za00184cdc1            ssGetSFcnParam(S, (0x7cc+2059-0xfd7))
#define ze072c43310               ssGetSFcnParam(S, (0x339+6871-0x1e0f))
#define z2cc9a52544            ssGetSFcnParam(S, (0x1857+180-0x1909))
#define z3832b85a32           ssGetSFcnParam(S, (0x10ec+1027-0x14ec))
#define z702a26a5e9                ssGetSFcnParam(S, (0x300+3909-0x1241))
#define zdf24515981                           ((0x34b+134-0x3cc))
static char msg[(0x59c+4500-0x1630)];static void mdlInitializeSizes(SimStruct*S){ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x25\x73\x3a\x20\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",DEVNAME,zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0xb4c+6790-0x25d2));ssSetNumDiscStates(S,(0x68d+39-0x6b4));(void)ssSetNumInputPorts(S,(0xd40+5936-0x2470));switch((uint8_T)mxGetPr(z2cc9a52544)[(0x4ec+8401-0x25bd)]){case(0x14ff+528-0x170e):(void)ssSetNumOutputPorts(S,z384ca5c8f4);for(int i=(0x1d+2467-0x9c0);i<z384ca5c8f4;i++){ssSetOutputPortWidth(S,i,(0xaa7+6871-0x257d));}break;case(0x587+2053-0xd8a):(void)ssSetNumOutputPorts(S,z384ca5c8f4);for(int i=(0x16c5+3195-0x2340);i<z384ca5c8f4;i++){ssSetOutputPortWidth(S,i,(0x3eb+8387-0x24ad));ssSetOutputPortDataType(S,i,SS_BOOLEAN);}break;case(0xa8f+3871-0x19ab):(void)ssSetNumOutputPorts(S,(0x10f7+897-0x1477));ssSetOutputPortWidth(S,(0x1e93+1313-0x23b4),z384ca5c8f4);break;case(0x1f17+1087-0x2352):(void)ssSetNumOutputPorts(S,(0x347+2564-0xd4a));ssSetOutputPortWidth(S,(0x12b8+2817-0x1db9),z384ca5c8f4);ssSetOutputPortDataType(S,(0xb76+6694-0x259c),SS_BOOLEAN);break;case(0x60b+928-0x9a6):(void)ssSetNumOutputPorts(S,(0x2212+372-0x2385));ssSetOutputPortWidth(S,(0x1fc+2989-0xda9),(0x135f+3167-0x1fbd));ssSetOutputPortDataType(S,(0x8f6+4465-0x1a67),SS_UINT16);break;default:sprintf(msg,"\x25\x73\x3a\x20\x55\x6e\x65\x78\x70\x65\x63\x74\x65\x64\x20\x70\x72\x74\x20\x74\x79\x70\x65\x3a\x20\x25\x64" "\n",DEVNAME,(uint8_T)mxGetPr(z2cc9a52544)[(0x2197+769-0x2498)]);ssSetErrorStatus(S,msg);return;}ssSetNumSampleTimes(S,(0xe7a+4208-0x1ee9));ssSetNumRWork(S,(0x1717+1474-0x1cd9));ssSetNumIWork(S,(0x1408+1531-0x1a03));ssSetNumPWork(S,(0x200+4098-0x1202));ssSetNumModes(S,(0x109f+2054-0x18a5));ssSetNumNonsampledZCs(S,(0x2068+129-0x20e9));for(int i=(0x457+1905-0xbc8);i<zdf24515981;i++)ssSetSFcnParamTunable(S,i,(0x55a+29-0x577));ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0x132b+699-0x15e6)]==-1.0){ssSetSampleTime(S,(0x1553+3473-0x22e4),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x163b+2589-0x2058),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x15f2+260-0x16f6),mxGetPr(z3832b85a32)[(0x2558+223-0x2637)]);ssSetOffsetTime(S,(0x10ba+5236-0x252e),0.0);}}
#ifndef MATLAB_MEX_FILE
static void sg_ModelLoad(SimStruct*S){SG_PRINTF(DEBUG,"\x25\x73\x20\x28\x49\x44\x20\x25\x64\x29\x20\x52\x65\x61\x64\x3a\x20\x25\x73\x20\x73\x67\x5f\x4d\x6f\x64\x65\x6c\x4c\x6f\x61\x64" "\n",DEVNAME,(int)mxGetPr(za00184cdc1)[(0x1d36+2120-0x257e)],sg_isFirstModelLoad()?"\x20\x46\x69\x72\x73\x74":"");}static void sg_ModelStart(SimStruct*S){SG_PRINTF(DEBUG,"\x25\x73\x20\x28\x49\x44\x20\x25\x64\x29\x20\x52\x65\x61\x64\x3a\x20\x73\x67\x5f\x4d\x6f\x64\x65\x6c\x53\x74\x61\x72\x74" "\n",DEVNAME,(int)mxGetPr(za00184cdc1)[(0x23e1+562-0x2613)]);}static void sg_ModelStep(SimStruct*S){double*y1;bool*y2;uint16_t*z671e76e748;int za0d38ae598=(int)mxGetPr(za00184cdc1)[(0xcb8+2234-0x1572)];z36f890056f*zae10e3f17f=(z36f890056f*)sg_module_get_custom_data(zc2d861b965,za0d38ae598);if(!zae10e3f17f){sprintf(msg,"\x25\x73\x20\x28\x49\x44\x20\x25\x64\x29\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x72\x65\x74\x72\x69\x65\x76\x65\x20\x6d\x6f\x64\x75\x6c\x65\x20\x73\x74\x61\x74\x65\x20\x66\x72\x6f\x6d\x20\x72\x65\x67\x69\x73\x74\x72\x79" "\n",DEVNAME,za0d38ae598);ssSetErrorStatus(S,msg);return;}uint16_t input=(0x18c+1873-0x8dd);if(zae10e3f17f->z422873c946==(0xced+5562-0x22a6)){input=zae10e3f17f->zc3873c1935->zba943a0a53;}else if(zae10e3f17f->z422873c946==(0x993+2300-0x128d)){input=sg_inpW((uintptr_t)(zae10e3f17f->ze8d6ac6ed7)+(0xc53+4865-0x1f52));}switch((uint8_t)mxGetPr(z2cc9a52544)[(0x4a8+51-0x4db)]){case(0x785+1664-0xe04):for(int i=(0x1a07+2897-0x2558);i<z384ca5c8f4;i++){y1=(double*)ssGetOutputPortSignal(S,i);y1[(0x66b+73-0x6b4)]=(input&((0x1a15+1991-0x21db)<<i))?1.0:0.0;}break;case(0x1e2d+570-0x2065):for(int i=(0xe24+4482-0x1fa6);i<z384ca5c8f4;i++){y2=(bool*)ssGetOutputPortSignal(S,i);y2[(0x4a2+2327-0xdb9)]=(input&((0x8cd+4577-0x1aad)<<i))?true:false;}break;case(0x119c+3224-0x1e31):y1=(double*)ssGetOutputPortSignal(S,(0x13c0+906-0x174a));for(int i=(0x161+567-0x398);i<z384ca5c8f4;i++)y1[i]=(input&((0x18a+5278-0x1627)<<i))?1.0:0.0;break;case(0x67a+4432-0x17c6):y2=(bool*)ssGetOutputPortSignal(S,(0x22d+7933-0x212a));for(int i=(0x15bd+1974-0x1d73);i<z384ca5c8f4;i++)y2[i]=(input&((0xbf7+3647-0x1a35)<<i))?true:false;break;case(0xe26+5514-0x23ab):z671e76e748=(uint16_t*)ssGetOutputPortSignal(S,(0xfe8+5046-0x239e));z671e76e748[(0xcc0+6533-0x2645)]=(uint16_t)input;break;}}static void sg_ModelStop(SimStruct*S){SG_PRINTF(DEBUG,"\x25\x73\x20\x28\x49\x44\x20\x25\x64\x29\x20\x52\x65\x61\x64\x3a\x20\x73\x67\x5f\x4d\x6f\x64\x65\x6c\x53\x74\x6f\x70" "\n",DEVNAME,(int)mxGetPr(za00184cdc1)[(0xb3a+3874-0x1a5c)]);}
#endif  
#include "sg_sfcn_glue.h"   


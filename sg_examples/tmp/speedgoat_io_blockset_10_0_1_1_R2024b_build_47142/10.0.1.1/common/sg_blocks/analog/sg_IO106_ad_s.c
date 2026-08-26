// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL    (0x159+1964-0x903)
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME     sg_IO106_ad_s
#include <stddef.h>
#include <stdlib.h>
#include "sg_IO106.h"
#include "simstruc.h"
#ifdef MATLAB_MEX_FILE
#include "mex.h"
#else
#include "sg_common.h"
#include "sg_printf.h"
#include "sg_module_registry.h"
#include "sg_module_types.h"
#endif
#define SG_EARLY_INIT
#include "sg_callback.h"
#define ze13f49a01f           ssGetSFcnParam(S, (0x58+3786-0xf22))
#define za9d8fb6bcf             ssGetSFcnParam(S, (0xec1+1674-0x154a))
#define z8fd86139be               ssGetSFcnParam(S, (0x637+1998-0xe03))
#define z8e37b80355            ssGetSFcnParam(S, (0xa45+5864-0x212a))
#define z3832b85a32           ssGetSFcnParam(S, (0x931+5432-0x1e65))
#define z1c6ce8e1bc           ssGetSFcnParam(S, (0x1f0+1818-0x905))
#define z702a26a5e9                ssGetSFcnParam(S, (0x5ff+3230-0x1297))
#define zdf24515981          ((0x1891+2004-0x205e))
#define z2e6483d505              ((0x4a+716-0x316))
#define zc5ce4cb81a              ((0x133+1961-0x8dc))
#define z2b17e2ee3b              ((0x8b2+5935-0x1fe1))
static char_T msg[(0x1507+2971-0x1fa2)];static void mdlInitializeSizes(SimStruct*S){uint16_T i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0xc88+6486-0x25de));ssSetNumDiscStates(S,(0x9a5+763-0xca0));if(!ssSetNumInputPorts(S,(0x562+7896-0x243a)))return;if(!ssSetNumOutputPorts(S,(0x3c2+4785-0x1672)))return;switch((uint32_T)mxGetPr(z8e37b80355)[(0xf9f+2886-0x1ae5)]){case(0xb85+465-0xd55):ssSetOutputPortWidth(S,(0x742+4555-0x190d),(uint32_T)mxGetPr(za9d8fb6bcf)[(0xd12+5606-0x22f8)]);break;case(0x23bb+167-0x2460):ssSetOutputPortWidth(S,(0x1c54+1374-0x21b2),(uint32_T)mxGetPr(za9d8fb6bcf)[(0x12da+967-0x16a1)]-(0x10b+7209-0x1d33));break;case(0x4f0+3002-0x10a7):ssSetOutputPortWidth(S,(0x448+1782-0xb3e),(uint32_T)mxGetPr(za9d8fb6bcf)[(0x14e5+3793-0x23b6)]);break;}ssSetNumSampleTimes(S,(0x54+5158-0x1479));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x343+1906-0xab5));ssSetNumNonsampledZCs(S,(0x1dc+5828-0x18a0));for(i=(0x15dd+3751-0x2484);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x12ec+3996-0x2288));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0x13fd+3798-0x22d3)]==-1.0){ssSetSampleTime(S,(0x167b+839-0x19c2),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0xdb5+5629-0x23b2),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0xedf+581-0x1124),mxGetPr(z3832b85a32)[(0x70+2254-0x93e)]);ssSetOffsetTime(S,(0x18ad+2123-0x20f8),0.0);}}
#ifndef MATLAB_MEX_FILE
static void sg_ModelLoad(SimStruct*S){}static void sg_ModelStart(SimStruct*S){}static void sg_ModelStep(SimStruct*S){uint32_T zf91d71c6d9=(uint32_T)mxGetPr(za9d8fb6bcf)[(0xb11+3108-0x1735)];uint32_T z8b9d33e44f=(uint32_T)mxGetPr(z8e37b80355)[(0xefd+3382-0x1c33)];uint32_T za0d38ae598=((uint32_T)mxGetPr(ze13f49a01f)[(0x6ec+1687-0xd83)]);real_T*y;uint32_T i;uint32_T count;z6077dd317b*zae10e3f17f=(z6077dd317b*)sg_module_get_custom_data(z12ba1d7c25,za0d38ae598);if(!zae10e3f17f){sprintf(msg,"\x49\x4f\x25\x64\x20\x28\x49\x44\x20\x25\x64\x29\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x72\x65\x74\x72\x69\x65\x76\x65\x20\x6d\x6f\x64\x75\x6c\x65\x20\x66\x72\x6f\x6d\x20\x72\x65\x67\x69\x73\x74\x72\x79\x20\x69\x6e\x20\x41\x44\x20\x4d\x6f\x64\x65\x6c\x53\x74\x65\x70" "\n",z12ba1d7c25,za0d38ae598);ssSetErrorStatus(S,msg);return;}if((uint16_T)mxGetPr(z1c6ce8e1bc)[(0x1eb7+1854-0x25f5)]==(0x1609+2374-0x1f4e)){zae10e3f17f->z3fad3d9764->z14bc320aa4|=((0x1caa+256-0x1da9)<<z03d027903f);}y=ssGetOutputPortSignal(S,(0xc7d+869-0xfe2));i=(0x12a+8839-0x23b1);while(!(zae10e3f17f->z3fad3d9764->z8727c368fa&((0x77f+5882-0x1e78)<<z452dd4baee))){i++;}count=zae10e3f17f->z3fad3d9764->z690d720321;for(i=(0xc5+9772-0x26f1);i<(uint16_T)(zf91d71c6d9/(0x183+180-0x235));i++){count=zae10e3f17f->z3fad3d9764->z690d720321;if(z8b9d33e44f==(0x1066+4370-0x2176)){if(i==(0x2002+1793-0x2703)){y[(0x129b+3611-0x20b5)+i*(0xcac+1721-0x1363)-(0x228b+921-0x2623)]=2.0*((real_T)((count&4294901760)>>(0x1a82+2030-0x2260))/zae10e3f17f->z409f51ac11-zae10e3f17f->za59ce6481a);}else{y[(0x14f+6802-0x1be1)+i*(0x9c5+1804-0x10cf)-(0x114a+5471-0x26a8)]=2.0*((real_T)(count&65535)/zae10e3f17f->z409f51ac11-zae10e3f17f->za59ce6481a);y[(0x183+1946-0x91c)+i*(0x1e3b+990-0x2217)-(0x729+3215-0x13b7)]=2.0*((real_T)((count&4294901760)>>(0xcbb+4550-0x1e71))/zae10e3f17f->z409f51ac11-zae10e3f17f->za59ce6481a);}}else{if(z8b9d33e44f==(0x737+641-0x9b5)){y[(0x1e83+903-0x220a)+i*(0x5d0+3386-0x1308)]=2.0*((real_T)(count&65535)/zae10e3f17f->z409f51ac11-zae10e3f17f->za59ce6481a);y[(0xc35+1384-0x119c)+i*(0x3bf+7960-0x22d5)]=2.0*((real_T)((count&4294901760)>>(0x1652+313-0x177b))/zae10e3f17f->z409f51ac11-zae10e3f17f->za59ce6481a);}else{y[(0x2ca+2332-0xbe6)+i*(0x169b+4185-0x26f2)]=(real_T)(count&65535)/zae10e3f17f->z409f51ac11-zae10e3f17f->za59ce6481a;y[(0x767+6209-0x1fa7)+i*(0x10aa+335-0x11f7)]=(real_T)((count&4294901760)>>(0x98+6542-0x1a16))/zae10e3f17f->z409f51ac11-zae10e3f17f->za59ce6481a;}}}}static void sg_ModelStop(SimStruct*S){}
#endif 
#include "sg_sfcn_glue.h"   


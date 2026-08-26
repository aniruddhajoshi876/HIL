// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL   (0x3cd+73-0x414)
#undef  S_FUNCTION_NAME
#define S_FUNCTION_NAME    sg_getmeminfo_s
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "simstruc.h"
#ifndef MATLAB_MEX_FILE
#include <sys/stat.h>
#ifdef __QNX__
#include <sys/syspage.h>
#else 
#include <sys/sysinfo.h>
#endif
#include "sg_common.h"
#include "sg_printf.h" 
#include "sg_callback_legacy.h"
#else
#include "mex.h"
#endif
#define zfe483006a0          ssGetSFcnParam(S,(0xa27+451-0xbea))
#define ze38a755273     ssGetSFcnParam(S,(0xa72+3005-0x162e))
#define zaf04e774f8          ssGetSFcnParam(S,(0x18d7+384-0x1a55))
#define z4555f0480f     ssGetSFcnParam(S,(0x4d1+6449-0x1dff))
#define z39cbd24432         ssGetSFcnParam(S,(0x6d6+1579-0xcfd))
#define zdf24515981          ((0x14eb+999-0x18cd))
#ifndef MATLAB_MEX_FILE
static uint64_t zd29a1caf05(void);
#endif
static char msg[(0x1786+124-0x1702)];static double z0d7bcd069a;static void mdlInitializeSizes(SimStruct*S){ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0xb26+1107-0xf79));ssSetNumDiscStates(S,(0xc61+4698-0x1ebb));int z49c1c6abb8=(0x5bf+1910-0xd35);int i=(0x65c+1607-0xca3);if((int)mxGetPr(zfe483006a0)[(0x12+6152-0x181a)]){z49c1c6abb8+=(0x953+6775-0x23c9);}if((int)mxGetPr(ze38a755273)[(0xeba+2221-0x1767)]){z49c1c6abb8+=(0x1f8f+1263-0x247d);}if((int)mxGetPr(zaf04e774f8)[(0xf4d+1454-0x14fb)]){z49c1c6abb8+=(0x494+1357-0x9e0);}if((int)mxGetPr(z4555f0480f)[(0xf02+2659-0x1965)]){z49c1c6abb8+=(0xe0+6175-0x18fe);}if(!ssSetNumOutputPorts(S,z49c1c6abb8))return;for(i=(0x3a+5076-0x140e);i<z49c1c6abb8;i++){ssSetOutputPortWidth(S,i,(0x12eb+2729-0x1d93));ssSetOutputPortDataType(S,i,SS_DOUBLE);}if(!ssSetNumInputPorts(S,(0x11dc+2567-0x1be3))){return;}ssSetNumSampleTimes(S,(0x53c+1336-0xa73));ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){ssSetSampleTime(S,(0x2a8+5520-0x1838),mxGetPr(z39cbd24432)[(0x17a+7197-0x1d97)]);ssSetOffsetTime(S,(0x232+7787-0x209d),0.0);}
#define MDL_START
static void mdlStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE    
z0d7bcd069a=zd29a1caf05();SG_PRINTF(DEBUG,"\x54\x6f\x74\x61\x6c\x20\x4d\x65\x6d\x6f\x72\x79\x3a\x20\x25\x2e\x30\x66\x20\x42\x79\x74\x65\x73" "\n",z0d7bcd069a);
#endif
}static void mdlOutputs(SimStruct*S,int_T z27c0327a06){
#ifndef MATLAB_MEX_FILE
int z49c1c6abb8=(0x8b4+1077-0xce9);double zc3082b4ee5;
#ifdef __linux__
struct sysinfo info;if(sysinfo(&info)==-(0x14c+301-0x278)){ssSetErrorStatus(S,"\x47\x65\x74\x20\x4d\x65\x6d\x6f\x72\x79\x20\x69\x6e\x66\x6f\x20\x66\x61\x69\x6c\x65\x64\x20\x28\x73\x79\x73\x69\x6e\x66\x6f\x29");return;}zc3082b4ee5=info.freeram;
#else   
struct stat64 za19f99840b;if(stat64("\x2f\x70\x72\x6f\x63",&za19f99840b)==-(0xacd+3901-0x1a09)){ssSetErrorStatus(S,"\x47\x65\x74\x20\x4d\x65\x6d\x6f\x72\x79\x20\x69\x6e\x66\x6f\x20\x66\x61\x69\x6c\x65\x64\x20\x28\x73\x74\x61\x74\x29");return;}zc3082b4ee5=(double)za19f99840b.st_size;
#endif
if((int)mxGetPr(zfe483006a0)[(0x1ac7+1125-0x1f2c)]){*(double*)ssGetOutputPortSignal(S,z49c1c6abb8)=zc3082b4ee5;SG_PRINTF(DEBUG,"\x46\x72\x65\x65\x3a\x20\x25\x2e\x30\x66\x20\x6f\x66\x20\x25\x2e\x30\x66\x20\x42\x79\x74\x65\x73" "\n",zc3082b4ee5,z0d7bcd069a);z49c1c6abb8+=(0x8c5+671-0xb63);}if((int)mxGetPr(ze38a755273)[(0x93b+3349-0x1650)]){*(double*)ssGetOutputPortSignal(S,z49c1c6abb8)=(0x164b+4017-0x2598)*zc3082b4ee5/z0d7bcd069a;SG_PRINTF(DEBUG,"\x46\x72\x65\x65\x3a\x20\x25\x2e\x32\x66\x20\x25\x25" "\n",(0xa36+5497-0x1f4b)*zc3082b4ee5/z0d7bcd069a);z49c1c6abb8+=(0x735+614-0x99a);}if((int)mxGetPr(zaf04e774f8)[(0x1c1b+2122-0x2465)]){*(double*)ssGetOutputPortSignal(S,z49c1c6abb8)=z0d7bcd069a-zc3082b4ee5;SG_PRINTF(DEBUG,"\x55\x73\x65\x64\x3a\x20\x25\x2e\x30\x66\x20\x6f\x66\x20\x25\x2e\x30\x66\x20\x42\x79\x74\x65\x73" "\n",z0d7bcd069a-zc3082b4ee5,z0d7bcd069a);z49c1c6abb8+=(0x1ebf+1022-0x22bc);}if((int)mxGetPr(z4555f0480f)[(0xfa5+3387-0x1ce0)]){*(double*)ssGetOutputPortSignal(S,z49c1c6abb8)=(0x4b4+5800-0x1af8)*(z0d7bcd069a-zc3082b4ee5)/z0d7bcd069a;SG_PRINTF(DEBUG,"\x55\x73\x65\x64\x3a\x20\x25\x2e\x32\x66\x20\x25\x25" "\n",(0xe91+5621-0x2422)*(z0d7bcd069a-zc3082b4ee5)/z0d7bcd069a);z49c1c6abb8+=(0xdc8+2263-0x169e);}
#endif
}static void mdlTerminate(SimStruct*S){}
#ifndef MATLAB_MEX_FILE
static uint64_t zd29a1caf05(void){uint64_t z0d7bcd069a=(0x98d+5341-0x1e6a);
#ifdef __linux__
struct sysinfo info;sysinfo(&info);z0d7bcd069a=info.totalram;
#else   
char*str=SYSPAGE_ENTRY(strings)->data;struct asinfo_entry*zdd4178f6f7=SYSPAGE_ENTRY(asinfo);unsigned zbae7a7c07a;for(zbae7a7c07a=_syspage_ptr->asinfo.entry_size/sizeof(*zdd4178f6f7);zbae7a7c07a>(0x1e4+9037-0x2531);--zbae7a7c07a){if(strcmp(&str[zdd4178f6f7->name],"\x72\x61\x6d")==(0x1583+789-0x1898)){z0d7bcd069a+=zdd4178f6f7->end-zdd4178f6f7->start+(0x1165+4292-0x2228);}++zdd4178f6f7;}
#endif
return z0d7bcd069a;}
#endif
#ifdef  MATLAB_MEX_FILE    
#include "simulink.c"      
#else
#include "cg_sfun.h"       
#endif


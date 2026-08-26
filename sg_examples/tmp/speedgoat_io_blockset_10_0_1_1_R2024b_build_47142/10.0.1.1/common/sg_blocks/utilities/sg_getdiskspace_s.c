// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL   (0x246c+560-0x269a)
#undef  S_FUNCTION_NAME
#define S_FUNCTION_NAME    sg_getdiskspace_s
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "simstruc.h"
#ifndef MATLAB_MEX_FILE
#ifdef __QNX__
#include <sys/types.h>
#include <errno.h>
#include <dirent.h>
#else
#include <sys/statvfs.h>
#endif
#include "sg_common.h"
#include "sg_printf.h" 
#include "sg_callback_legacy.h"
#else
#include "mex.h"
#endif
#define zfe483006a0          ssGetSFcnParam(S,(0x16cd+3702-0x2543))
#define ze38a755273     ssGetSFcnParam(S,(0x1749+3374-0x2476))
#define zaf04e774f8          ssGetSFcnParam(S,(0x387+4155-0x13c0))
#define z4555f0480f     ssGetSFcnParam(S,(0x892+1422-0xe1d))
#define z39cbd24432         ssGetSFcnParam(S,(0x160f+4119-0x2622))
#define zdf24515981          ((0x1030+1944-0x17c3))
#define za3260fca3b         ((0x4cb+8869-0x2370))
#define z4abbe0c0d6         ((0x1b65+2867-0x2634))
#define z494bc8eeb3        ((0xa3c+2662-0x1498))
static char_T msg[(0x1086+6017-0x2707)];static void mdlInitializeSizes(SimStruct*S){ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x1234+2717-0x1cd1));ssSetNumDiscStates(S,(0x196+4519-0x133d));int z49c1c6abb8=(0xaeb+5931-0x2216);int i=(0x13ed+2209-0x1c8e);if((int)mxGetPr(zfe483006a0)[(0x106a+5192-0x24b2)]){z49c1c6abb8+=(0x3ab+7268-0x200e);}if((int)mxGetPr(ze38a755273)[(0x1061+1819-0x177c)]){z49c1c6abb8+=(0x1602+3545-0x23da);}if((int)mxGetPr(zaf04e774f8)[(0x19a1+1321-0x1eca)]){z49c1c6abb8+=(0x7fc+3522-0x15bd);}if((int)mxGetPr(z4555f0480f)[(0x757+8066-0x26d9)]){z49c1c6abb8+=(0x474+6414-0x1d81);}if(!ssSetNumOutputPorts(S,z49c1c6abb8))return;for(i=(0x203c+1215-0x24fb);i<z49c1c6abb8;i++){ssSetOutputPortWidth(S,i,(0x43d+1104-0x88c));ssSetOutputPortDataType(S,i,SS_DOUBLE);}if(!ssSetNumInputPorts(S,(0x9a8+3479-0x173f))){return;}ssSetNumSampleTimes(S,(0x1bad+2200-0x2444));ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){ssSetSampleTime(S,(0x1181+3719-0x2008),mxGetPr(z39cbd24432)[(0x14fa+4002-0x249c)]);ssSetOffsetTime(S,(0x773+2027-0xf5e),0.0);}
#define MDL_START
static void mdlStart(SimStruct*S){}static void mdlOutputs(SimStruct*S,int_T z27c0327a06){
#ifndef MATLAB_MEX_FILE
#ifdef __QNX__ 
DIR*z85b945f771;struct dirent*zf6a8621288;char zc835f817af[(0x866+8100-0x270a)];char zac6925ddcd[(0x17fd+1116-0x1b59)]="\0";double z0d7bcd069a=(0xe3d+5625-0x2436);double z63e9ab68f4=(0x867+6252-0x20d3);int z49c1c6abb8=(0xffa+410-0x1194);z85b945f771=opendir("\x2f\x64\x65\x76");if(z85b945f771!=NULL){for(;;){zf6a8621288=readdir(z85b945f771);if(zf6a8621288==NULL)break;strcpy(zc835f817af,"\x2f\x64\x65\x76\x2f");strcat(zc835f817af,zf6a8621288->d_name);if(sg_statPath(zc835f817af,zac6925ddcd,&z0d7bcd069a,&z63e9ab68f4)!=-(0x147a+2391-0x1dd0)){SG_PRINTF(TRACE,"\x4d\x6f\x75\x6e\x74\x20\x70\x6f\x69\x6e\x74\x20\x25\x73\x3a\x20\x54\x6f\x74\x61\x6c\x20\x2f\x20\x41\x76\x61\x69\x6c\x20\x62\x79\x74\x65\x73\x3a\x20\x25\x2e\x30\x66\x20\x2f\x20\x25\x2e\x30\x66\x20" "\n",zac6925ddcd,z0d7bcd069a,z63e9ab68f4);if(strcmp(zc835f817af,"\x69\x66\x73")&&!strcmp(zac6925ddcd,"\x2f")){if((int)mxGetPr(zfe483006a0)[(0x115+7470-0x1e43)]){*(double*)ssGetOutputPortSignal(S,z49c1c6abb8)=z63e9ab68f4;SG_PRINTF(DEBUG,"\x46\x72\x65\x65\x3a\x20\x25\x2e\x30\x66\x20\x6f\x66\x20\x25\x2e\x30\x66\x20\x42\x79\x74\x65\x73" "\n",z63e9ab68f4,z0d7bcd069a);z49c1c6abb8+=(0x18c6+605-0x1b22);}if((int)mxGetPr(ze38a755273)[(0x222a+628-0x249e)]){*(double*)ssGetOutputPortSignal(S,z49c1c6abb8)=(0x9fc+2958-0x1526)*z63e9ab68f4/z0d7bcd069a;SG_PRINTF(DEBUG,"\x46\x72\x65\x65\x3a\x20\x25\x2e\x32\x66\x20\x25\x25" "\n",(0x1a15+123-0x1a2c)*z63e9ab68f4/z0d7bcd069a);z49c1c6abb8+=(0x136a+2079-0x1b88);}if((int)mxGetPr(zaf04e774f8)[(0x204+1887-0x963)]){*(double*)ssGetOutputPortSignal(S,z49c1c6abb8)=z0d7bcd069a-z63e9ab68f4;SG_PRINTF(DEBUG,"\x55\x73\x65\x64\x3a\x20\x25\x2e\x30\x66\x20\x6f\x66\x20\x25\x2e\x30\x66\x20\x42\x79\x74\x65\x73" "\n",z0d7bcd069a-z63e9ab68f4,z0d7bcd069a);z49c1c6abb8+=(0xb64+5525-0x20f8);}if((int)mxGetPr(z4555f0480f)[(0x89+3729-0xf1a)]){*(double*)ssGetOutputPortSignal(S,z49c1c6abb8)=(0xcfd+5276-0x2135)*(z0d7bcd069a-z63e9ab68f4)/z0d7bcd069a;SG_PRINTF(DEBUG,"\x55\x73\x65\x64\x3a\x20\x25\x2e\x32\x66\x20\x25\x25" "\n",(0x95b+5201-0x1d48)*(z0d7bcd069a-z63e9ab68f4)/z0d7bcd069a);z49c1c6abb8+=(0x11a+4489-0x12a2);}}zac6925ddcd[(0x563+4779-0x180e)]='\0';}}closedir(z85b945f771);}else{SG_PRINTF(ERROR,"\x4e\x6f\x20\x62\x79\x74\x65\x73\x20\x74\x6f\x20\x72\x65\x61\x64" "\n");}
#else 
struct statvfs stat;double z0d7bcd069a,z63e9ab68f4;int z49c1c6abb8=(0x14bb+1108-0x190f);if(statvfs("\x2f\x68\x6f\x6d\x65",&stat)!=(0x1043+1173-0x14d8)){SG_PRINTF(ERROR,"\x4e\x6f\x20\x62\x79\x74\x65\x73\x20\x74\x6f\x20\x72\x65\x61\x64");return;}z63e9ab68f4=stat.f_bsize*stat.f_bfree;z0d7bcd069a=stat.f_frsize*stat.f_blocks;if((int)mxGetPr(zfe483006a0)[(0x166c+1562-0x1c86)]){*(double*)ssGetOutputPortSignal(S,z49c1c6abb8)=z63e9ab68f4;SG_PRINTF(DEBUG,"\x46\x72\x65\x65\x3a\x20\x25\x2e\x30\x66\x20\x6f\x66\x20\x25\x2e\x30\x66\x20\x42\x79\x74\x65\x73" "\n",z63e9ab68f4,z0d7bcd069a);z49c1c6abb8+=(0xb3d+5982-0x229a);}if((int)mxGetPr(ze38a755273)[(0x134f+1381-0x18b4)]){*(double*)ssGetOutputPortSignal(S,z49c1c6abb8)=(0x351+1290-0x7f7)*z63e9ab68f4/z0d7bcd069a;SG_PRINTF(DEBUG,"\x46\x72\x65\x65\x3a\x20\x25\x2e\x32\x66\x20\x25\x25" "\n",(0x1d06+1856-0x23e2)*z63e9ab68f4/z0d7bcd069a);z49c1c6abb8+=(0x691+7530-0x23fa);}if((int)mxGetPr(zaf04e774f8)[(0xf60+3015-0x1b27)]){*(double*)ssGetOutputPortSignal(S,z49c1c6abb8)=z0d7bcd069a-z63e9ab68f4;SG_PRINTF(DEBUG,"\x55\x73\x65\x64\x3a\x20\x25\x2e\x30\x66\x20\x6f\x66\x20\x25\x2e\x30\x66\x20\x42\x79\x74\x65\x73" "\n",z0d7bcd069a-z63e9ab68f4,z0d7bcd069a);z49c1c6abb8+=(0x13b6+1640-0x1a1d);}if((int)mxGetPr(z4555f0480f)[(0x786+2739-0x1239)]){*(double*)ssGetOutputPortSignal(S,z49c1c6abb8)=(0x1156+3077-0x1cf7)*(z0d7bcd069a-z63e9ab68f4)/z0d7bcd069a;SG_PRINTF(DEBUG,"\x55\x73\x65\x64\x3a\x20\x25\x2e\x32\x66\x20\x25\x25" "\n",(0x1d29+1836-0x23f1)*(z0d7bcd069a-z63e9ab68f4)/z0d7bcd069a);z49c1c6abb8+=(0x1567+53-0x159b);}
#endif
#endif
}static void mdlTerminate(SimStruct*S){}
#ifdef  MATLAB_MEX_FILE    
#include "simulink.c"      
#else
#include "cg_sfun.h"       
#endif


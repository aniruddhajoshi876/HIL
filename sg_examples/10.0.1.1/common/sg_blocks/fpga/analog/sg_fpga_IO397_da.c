// Copyright 2006-2026 Speedgoat GmbH

#define   S_FUNCTION_LEVEL  (0xbdc+1078-0x1010)
#undef    S_FUNCTION_NAME
#define   S_FUNCTION_NAME   sg_fpga_IO397_da
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
#define ze13f49a01f     ssGetSFcnParam(S, (0x1535+902-0x18bb))  
#define za9d8fb6bcf       ssGetSFcnParam(S, (0xeaf+6171-0x26c9))  
#define z159ecbe81e       ssGetSFcnParam(S, (0x661+9-0x668))  
#define z04f0a23313      ssGetSFcnParam(S, (0xb32+4600-0x1d27))  
#define z3832b85a32     ssGetSFcnParam(S, (0x1145+2171-0x19bc))
#define zad03d924d8          ssGetSFcnParam(S, (0x95a+971-0xd20))
#define zdf24515981                     ((0x407+2405-0xd66))
#define zd7444a6eb4        (0x1093+5498-0x260d)
#define z56d9a5f3fc        (0x11b9+3596-0x1fc4)
#define z224e3428b1 (0x1520+3640-0x2356)
#define z2e6483d505          ((0xf3+1910-0x868))
#define zad6b2ff006       ((0x960+5224-0x1dc8))
#define zc5ce4cb81a          ((0x589+7929-0x2482))
#define z2b17e2ee3b          ((0xa98+232-0xb7e))
#define z0194338df7     ((0x4d0+7992-0x2408))
#define z2e8373622e    ((0x55f+3397-0x12a3))
#define zb7aa091922         ((0x5dd+2841-0x10f4))
#define z1cefd620f8       (32767/(0x18bf+1393-0x1e26))
#define z5674e18e88        ((0x13b1+2162-0x1c1f))
#define zd4c1aa112f           (0x2276+654-0x2504)
#define z60a6603ca7    (5509120)
#define z174b59c07e           ((0xff1+1354-0x14eb))
#define I2C_ERROR_OK        ((0x1c46+2235-0x2501))
#define I2C_READ_ERROR      ((0x1269+3144-0x1eb0))
#define z0d58e923ee     ((0xbf8+2260-0x146c))
#define z29b704d2e2          ((0x80c+1518-0xd9a))
#define zbd529ad5b7             ((0x59b+2051-0xd9a))
#define zf1714589ac ((0x323+631-0x51a))
#define z6b36f492e0   (0x435+5682-0x1a66)
typedef struct{uint32_t z503cfbc131;uint32_t z76b7ec4de7;uint32_t ze32a66eb4c;uint32_t z1282cae458;uint32_t zb366ad92a0;}z111719ca84;typedef struct{int16_t offset;int16_t ze1cdc3a276;int16_t z0754dd67cc;int16_t z6ff00ac4fb;}zcc7ad83a61;typedef struct{int16_t offset;int16_t z0754dd67cc;}ze7c2a94e2f;uint32_t zb7b3968d12(volatile z111719ca84*z9dfcf27d92,uint8_t*z703a8aaab7,uint32_t z37b2e8d405);void zaedc6b3aec(SimStruct*S);static char msg[(0x1d4+4393-0x11fd)];struct z6e54179dbd{uint32_t test1;uint32_t test2;uint32_t zaa30651ded[z5674e18e88];uint32_t zc430a259a4;uint32_t status;uint32_t z17847416da;uint32_t zde83594af4;zcc7ad83a61 comp[z5674e18e88];uint32_t z2942391f65[z5674e18e88];uint32_t version;};static void mdlInitializeSizes(SimStruct*S){uint32_t i,za0df33019b;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x96d+3995-0x1908));ssSetNumDiscStates(S,(0x815+1930-0xf9f));za0df33019b=(uint32_t)mxGetN(za9d8fb6bcf);ssSetNumInputPorts(S,za0df33019b);ssSetNumOutputPorts(S,(0x1702+1808-0x1e12));for(i=(0x1768+2364-0x20a4);i<za0df33019b;i++){ssSetInputPortWidth(S,i,(0x1bad+353-0x1d0d));ssSetInputPortDirectFeedThrough(S,i,(0x216+9311-0x2674));ssSetInputPortRequiredContiguous(S,i,(0x41f+7669-0x2213));}ssSetNumSampleTimes(S,(0xc4+7330-0x1d65));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x17b3+2078-0x1fd1));ssSetNumNonsampledZCs(S,(0xfd4+5534-0x2572));for(i=(0xdd+7906-0x1fbf);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0xf64+3162-0x1bbe));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0x13c3+2015-0x1ba2)]==-1.0){ssSetSampleTime(S,(0x4a9+7670-0x229f),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x318+4396-0x1444),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x1207+3957-0x217c),mxGetPr(z3832b85a32)[(0xee5+5713-0x2536)]);ssSetOffsetTime(S,(0x1b90+2914-0x26f2),0.0);}}static void sg_ModelLoad(SimStruct*S){
#ifndef MATLAB_MEX_FILE
uint32_t m,channel,i;ze7c2a94e2f z8d4dfa85da[z0d58e923ee/(0xa5b+4354-0x1b59)];ze7c2a94e2f*zccb6539844;volatile z111719ca84*z9dfcf27d92;volatile struct z6e54179dbd*zf1756dff08;void*z8e7911eb93;int moduleId=(int)mxGetScalar(ze13f49a01f);char*boardName=io3xxGetBoardNameSgLib(moduleId);if(!io3xxGetAddressSgLib((int32_t)(int)mxGetPr(ze13f49a01f)[(0x20ec+900-0x2470)],SG_FPGA_IO3XX_BAR2)){ssSetErrorStatus(S,pSgErrorStr);return;}uint32_t zf7ccd17be8=(0x2fa+3922-0x124c);if(sg_fpga_io3xx_getCmBaseAddress(moduleId,IO397_DA_BASE,&zf7ccd17be8)){sprintf(msg,"\x25\x73\x20\x44\x41\x20\x6d\x6f\x64\x75\x6c\x65\x3a\x20\x4f\x66\x66\x73\x65\x74\x20\x6c\x6f\x6f\x6b\x75\x70\x20\x75\x6e\x73\x75\x63\x63\x65\x73\x73\x66\x75\x6c\x21" "\n",boardName);ssSetErrorStatus(S,msg);return;}z8e7911eb93=io3xxGetAddressSgLib((int32_t)(int)mxGetPr(ze13f49a01f)[(0x5c1+644-0x845)],SG_FPGA_IO3XX_BAR2);zf1756dff08=(volatile struct z6e54179dbd*)((uintptr_t)z8e7911eb93+zf7ccd17be8);ssSetPWorkValue(S,z0194338df7,(void*)zf1756dff08);z9dfcf27d92=(volatile z111719ca84*)((uintptr_t)z8e7911eb93+z60a6603ca7);zccb6539844=(ze7c2a94e2f*)malloc(sizeof(ze7c2a94e2f)*(0xdb0+5155-0x21cf));ssSetPWorkValue(S,z2e8373622e,(void*)zccb6539844);if(zb7b3968d12(z9dfcf27d92,(uint8_t*)z8d4dfa85da,zf1714589ac)==(0xeb8+3692-0x1d24)){
#if zd4c1aa112f
SG_PRINTF(INFO,"\x23\x23\x23\x23\x20\x44\x41\x43\x20\x4f\x66\x66\x73\x65\x74\x20\x61\x6e\x64\x20\x47\x61\x69\x6e\x20\x43\x6f\x72\x72\x65\x63\x74\x69\x6f\x6e\x20\x56\x61\x6c\x75\x65\x73\x20\x66\x72\x6f\x6d\x20\x45\x45\x50\x52\x4f\x4d\x20\x23\x23\x23\x23" "\n");for(i=(0xda1+3283-0x1a74);i<z0d58e923ee/(0x4f7+6138-0x1ced);i++){if(i%(0x335+5434-0x186b)==(0x15a1+2328-0x1eb9)){SG_PRINTF(INFO,"\x2a\x2a\x2a\x2a\x2a\x20\x4f\x66\x66\x73\x65\x74\x20\x61\x6e\x64\x20\x47\x61\x69\x6e\x20\x56\x61\x6c\x75\x65\x73\x20\x66\x6f\x72\x20\x73\x70\x61\x6e\x20" "\n");switch(i/(0x15c9+4097-0x25c6)){case(0xefd+320-0x103c):SG_PRINTF(INFO,"\x2b\x31\x30\x56" "\n");break;case(0x154+5869-0x183f):SG_PRINTF(INFO,"\x2b\x2d\x35\x56" "\n");break;case(0x1d23+1729-0x23e1):SG_PRINTF(INFO,"\x2b\x2d\x31\x30\x56" "\n");break;case(0xdb7+5796-0x2457):SG_PRINTF(INFO,"\x2b\x31\x30\x2e\x38\x56" "\n");break;case(0x12ac+1414-0x182d):SG_PRINTF(INFO,"\x2b\x2d\x31\x30\x2e\x38\x56" "\n");break;default:SG_PRINTF(INFO,"\x2b\x35\x56" "\n");}SG_PRINTF(INFO,"\x20\x2a\x2a\x2a\x2a\x2a" "\n");}SG_PRINTF(INFO,"\x44\x41\x43\x20\x43\x48\x25\x69\x3a\x20\x6f\x66\x66\x73\x65\x74\x20\x3d\x20\x25\x69\x20\x2c\x20\x67\x61\x69\x6e\x20\x3d\x20\x25\x69" "\n",(i%(0xd8f+1853-0x14c8)+(0x3a5+1950-0xb42)),z8d4dfa85da[i].offset,z8d4dfa85da[i].z0754dd67cc);}
#endif
}else{SG_PRINTF(INFO,"\x50\x52\x4f\x4d\x20\x49\x32\x43\x20\x65\x72\x72\x6f\x72\x2e" "\n");}switch((uint32_t)mxGetPr(zad03d924d8)[(0xb9d+506-0xd97)]){case(0x321+4099-0x1323):zf1756dff08->zde83594af4=(0x90+2491-0xa36);m=(0xbf8+5550-0x21a3);break;case(0x580+3793-0x144f):zf1756dff08->zde83594af4=(0xd73+2112-0x159f);m=(0x60f+5539-0x1bb0);break;case(0x10fd+2816-0x1bfa):zf1756dff08->zde83594af4=(0x658+5061-0x1a07);m=(0x7fd+6000-0x1f6d);break;case(0x49d+6361-0x1d72):zf1756dff08->zde83594af4=(0x810+7907-0x26dc);m=(0x84+5837-0x1750);break;case(0xb79+1951-0x1313):zf1756dff08->zde83594af4=(0x11c2+3067-0x1d66);m=(0x154b+1640-0x1baf);break;case(0xe75+6142-0x266d):zf1756dff08->zde83594af4=(0xa27+5537-0x1f73);m=(0x182a+1474-0x1de7);break;default:zf1756dff08->zde83594af4=(0x413+8685-0x25eb);m=(0x747+6111-0x1f23);}
#if zd4c1aa112f
SG_PRINTF(INFO,"\x23\x23\x23\x23\x20\x41\x70\x70\x6c\x69\x65\x64\x20\x4f\x66\x66\x73\x65\x74\x20\x61\x6e\x64\x20\x47\x61\x69\x6e\x20\x43\x6f\x72\x72\x65\x63\x74\x69\x6f\x6e\x20\x56\x61\x6c\x75\x65\x73\x20\x23\x23\x23\x23" "\n");SG_PRINTF(INFO,"\x73\x70\x61\x6e\x20\x70\x61\x72\x61\x6d\x65\x74\x65\x72\x3a\x20\x30\x78\x25\x58" "\n",(uint32_t)mxGetPr(zad03d924d8)[(0x1c7d+99-0x1ce0)]);SG_PRINTF(INFO,"\x44\x41\x43\x20\x73\x70\x61\x6e\x20\x69\x73\x3a\x20" "\n");switch(m){case(0x13b+3857-0x104b):SG_PRINTF(INFO,"\x2b\x31\x30\x56" "\n");break;case(0x165d+2929-0x21cc):SG_PRINTF(INFO,"\x2b\x2d\x35\x56" "\n");break;case(0x541+945-0x8ef):SG_PRINTF(INFO,"\x2b\x2d\x31\x30\x56" "\n");break;case(0x50f+7771-0x2366):SG_PRINTF(INFO,"\x2b\x31\x30\x2e\x38\x56" "\n");break;case(0xf20+3102-0x1b39):SG_PRINTF(INFO,"\x2b\x2d\x31\x30\x2e\x38\x56" "\n");break;default:SG_PRINTF(INFO,"\x2b\x35\x56" "\n");}SG_PRINTF(INFO,"\n");
#endif
for(i=(0x12a+1896-0x892);i<mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0x1632+2112-0x1e71);zf1756dff08->comp[channel].z0754dd67cc=z8d4dfa85da[channel+m*(0xe15+5352-0x22f9)].z0754dd67cc;zccb6539844[channel].z0754dd67cc=zf1756dff08->comp[channel].z0754dd67cc;zf1756dff08->comp[channel].offset=z8d4dfa85da[channel+m*(0x879+3286-0x154b)].offset;zccb6539844[channel].offset=zf1756dff08->comp[channel].offset;
#if zd4c1aa112f
SG_PRINTF(INFO,"\x44\x41\x43\x20\x43\x48\x25\x69\x3a\x20\x6f\x66\x66\x73\x65\x74\x20\x3d\x20\x25\x69\x20\x2c\x20\x67\x61\x69\x6e\x20\x3d\x20\x25\x69\x20" "\n",channel+(0x519+578-0x75a),zf1756dff08->comp[channel].offset,zf1756dff08->comp[channel].z0754dd67cc);
#endif
}ssSetIWorkValue(S,zad6b2ff006,(uint32_t)zd7444a6eb4);zf1756dff08->zc430a259a4=(0x1bed+360-0x1d54);zf1756dff08->zc430a259a4=(0x405+4406-0x153b);zaedc6b3aec(S);sg_wait_s(0.0001);
#endif
}static void sg_ModelStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
uint32_t channel,i;volatile struct z6e54179dbd*zf1756dff08;ze7c2a94e2f*zccb6539844;zf1756dff08=(volatile struct z6e54179dbd*)ssGetPWorkValue(S,z0194338df7);zccb6539844=(ze7c2a94e2f*)ssGetPWorkValue(S,z2e8373622e);ssSetIWorkValue(S,zad6b2ff006,z56d9a5f3fc);for(i=(0x18a+2483-0xb3d);i<mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0xffb+5135-0x2409);zccb6539844[channel].z0754dd67cc=zf1756dff08->comp[channel].z0754dd67cc;zccb6539844[channel].offset=zf1756dff08->comp[channel].offset;}
#if zd4c1aa112f
SG_PRINTF(INFO,"\x53\x74\x61\x74\x75\x73\x20\x72\x65\x67\x69\x73\x74\x65\x72\x20\x63\x6f\x6e\x74\x65\x6e\x74\x73\x3a\x20\x30\x78\x25\x58" "\n",zf1756dff08->status);
#endif
#endif
}static void sg_ModelStep(SimStruct*S){
#ifndef MATLAB_MEX_FILE
zaedc6b3aec(S);
#endif
}static void sg_ModelStop(SimStruct*S){
#ifndef MATLAB_MEX_FILE
uint32_t z0f0c5d6bfa;z0f0c5d6bfa=(uint32_t)ssGetIWorkValue(S,zad6b2ff006);SG_PRINTF(INFO,"\x53\x69\x6d\x5f\x53\x74\x61\x74\x65\x20\x3d\x20\x25\x64" "\n",z0f0c5d6bfa);if(z56d9a5f3fc==z0f0c5d6bfa){ssSetIWorkValue(S,zad6b2ff006,z224e3428b1);zaedc6b3aec(S);}free((void*)ssGetPWorkValue(S,z2e8373622e));
#endif
}
#ifndef MATLAB_MEX_FILE
uint32_t zb7b3968d12(volatile z111719ca84*z9dfcf27d92,uint8_t*z703a8aaab7,uint32_t z37b2e8d405){double start;uint32_t i,z26dbd73a5e,z812c65ff2f;uint8_t z7be9105675;
#if zd4c1aa112f
SG_PRINTF(INFO,"\x50\x52\x4f\x4d\x52\x65\x67\x2d\x3e\x53\x52\x20\x3d\x20\x30\x78\x25\x58" "\n",z9dfcf27d92->z76b7ec4de7);
#endif
z9dfcf27d92->ze32a66eb4c=(0x4a5+1797-0xba3);sg_wait_s(0.100);z9dfcf27d92->z503cfbc131=(0x567+4593-0x1758);sg_wait_s(0.100);
#if zd4c1aa112f
SG_PRINTF(INFO,"\x50\x6f\x73\x74\x20\x52\x53\x54\x20\x50\x52\x4f\x4d\x52\x65\x67\x2d\x3e\x53\x52\x20\x3d\x20\x30\x78\x25\x58" "\n",z9dfcf27d92->z76b7ec4de7);SG_PRINTF(INFO,"\x43\x4d\x3a\x20\x30\x78\x25\x58" "\n",z9dfcf27d92->ze32a66eb4c);SG_PRINTF(INFO,"\x50\x6f\x73\x74\x20\x52\x53\x54\x20\x50\x52\x4f\x4d\x52\x65\x67\x2d\x3e\x53\x52\x20\x3d\x20\x30\x78\x25\x58" "\n",z9dfcf27d92->z76b7ec4de7);
#endif
z9dfcf27d92->z503cfbc131|=(z174b59c07e<<(0x785+7724-0x25a1));
#if zd4c1aa112f
SG_PRINTF(INFO,"\x50\x72\x6f\x6d\x20\x61\x64\x64\x72\x65\x73\x73\x20\x69\x73\x3a\x20\x30\x78\x25\x58" "\n",z9dfcf27d92);SG_PRINTF(INFO,"\x53\x74\x61\x72\x74\x20\x61\x64\x64\x72\x65\x73\x73\x20\x69\x73\x3a\x20\x30\x78\x25\x58" "\n",z37b2e8d405);
#endif
for(z812c65ff2f=(0x178c+2044-0x1f88);z812c65ff2f<z0d58e923ee;z812c65ff2f+=z29b704d2e2){z9dfcf27d92->ze32a66eb4c=(0xb99+1819-0x12ae);
#if zd4c1aa112f
SG_PRINTF(INFO,"\x61\x64\x64\x72\x3d\x20\x30\x78\x25\x58" "\n",z37b2e8d405+z812c65ff2f);
#endif
z9dfcf27d92->z1282cae458=z37b2e8d405+z812c65ff2f;z9dfcf27d92->ze32a66eb4c=(0x8e9+2501-0x12a6);z9dfcf27d92->z503cfbc131|=(z29b704d2e2);z9dfcf27d92->z503cfbc131|=((0x61b+7401-0x2303)<<(0x30c+2626-0xd46));
#if zd4c1aa112f
SG_PRINTF(INFO,"\x50\x72\x65\x2d\x74\x72\x61\x6e\x73\x61\x63\x74\x69\x6f\x6e\x20\x77\x72\x69\x74\x65\x20\x66\x69\x66\x6f\x20\x66\x69\x6c\x6c\x20\x6c\x65\x76\x65\x6c\x3a\x20\x30\x78\x25\x58" "\n",(z9dfcf27d92->z76b7ec4de7&(0x6c7+4227-0x173b)));
#endif
z9dfcf27d92->ze32a66eb4c|=((0x7a8+3309-0x1494)<<(0x229+7645-0x2001));z26dbd73a5e=(0x718+954-0xad2);start=sg_getElapsedTime();while(z26dbd73a5e<z29b704d2e2){if(sg_getElapsedTime()-start>3.0){
#if zd4c1aa112f
SG_PRINTF(INFO,"\x50\x52\x4f\x4d\x20\x49\x32\x43\x20\x64\x61\x63\x20\x76\x61\x6c\x75\x65\x73\x20\x74\x69\x6d\x65\x6f\x75\x74\x2e\x20\x25\x69\x20\x62\x79\x74\x65\x73\x20\x72\x65\x61\x64\x2e" "\n" "\x20\x28\x61\x74\x20\x61\x64\x64\x72\x3a\x20\x30\x78\x25\x58" "\n",z26dbd73a5e,z37b2e8d405+z812c65ff2f);
#endif
return I2C_READ_ERROR;}z26dbd73a5e=(z9dfcf27d92->z76b7ec4de7&65280)>>(0x2a6+5334-0x1774);}
#if zd4c1aa112f
SG_PRINTF(INFO,"\x50\x6f\x73\x74\x2d\x74\x72\x61\x6e\x73\x61\x63\x74\x69\x6f\x6e\x20\x77\x72\x69\x74\x65\x20\x66\x69\x66\x6f\x20\x66\x69\x6c\x6c\x20\x6c\x65\x76\x65\x6c\x3a\x20\x30\x78\x25\x58" "\n",(z9dfcf27d92->z76b7ec4de7&(0x1138+4520-0x21e1)));SG_PRINTF(INFO,"\x42\x79\x74\x65\x73\x20\x61\x71\x75\x69\x72\x65\x64\x3a\x30\x78\x25\x58" "\n",z26dbd73a5e);
#endif
for(i=z812c65ff2f;i<z26dbd73a5e;i++){z703a8aaab7[i]=z9dfcf27d92->zb366ad92a0;
#if zd4c1aa112f
SG_PRINTF(INFO,"\x44\x61\x74\x61\x20\x42\x79\x74\x65\x20\x25\x64\x3a\x20\x30\x78\x25\x58" "\n",i,z9dfcf27d92->zb366ad92a0);
#endif
z9dfcf27d92->ze32a66eb4c=((0xffa+4900-0x231d)<<(0xd37+3475-0x1ac6));}}
#if zd4c1aa112f
SG_PRINTF(INFO,"\x44\x41\x43\x20\x43\x4f\x4d\x50\x20\x56\x41\x4c\x55\x45\x53\x3a" "\n");for(i=(0x162+6274-0x19e4);i<z0d58e923ee;i+=z29b704d2e2){for(z812c65ff2f=(0xa82+1936-0x1212);z812c65ff2f<z29b704d2e2;z812c65ff2f+=(0xe99+295-0xfbe)){SG_PRINTF(INFO,"\x25\x64\x20" "\n",(int16_t)(((int16_t)z703a8aaab7[i+z812c65ff2f]<<(0x11da+2033-0x19c3))+(int16_t)z703a8aaab7[i+z812c65ff2f+(0xdb4+4115-0x1dc6)]));}}
#endif
for(i=(0xb10+838-0xe56);i<z0d58e923ee;i+=(0x1417+295-0x153c)){z7be9105675=z703a8aaab7[i];z703a8aaab7[i]=z703a8aaab7[i+(0x8ad+5744-0x1f1c)];z703a8aaab7[i+(0x55+3188-0xcc8)]=z7be9105675;}z9dfcf27d92->ze32a66eb4c=(0xa55+6889-0x2537);
#if zd4c1aa112f
SG_PRINTF(INFO,"\x50\x52\x4f\x4d\x52\x65\x67\x2d\x3e\x53\x52\x20\x3d\x20\x30\x78\x25\x58" "\n",z9dfcf27d92->z76b7ec4de7);
#endif
return I2C_ERROR_OK;}
#endif
#ifndef MATLAB_MEX_FILE
void zaedc6b3aec(SimStruct*S){double*zaf9f0b2dbc;double ze8c6171b31,z0754dd67cc,offset,z56cade6b3a;uint32_t i,channel,zfc0eea4f31;uint8_t z3ff4e9e346=(0x1a4f+1459-0x2002);uint32_t z0f0c5d6bfa;volatile struct z6e54179dbd*zf1756dff08;ze7c2a94e2f*zccb6539844;z0f0c5d6bfa=(uint32_t)ssGetIWorkValue(S,zad6b2ff006);zf1756dff08=(volatile struct z6e54179dbd*)ssGetPWorkValue(S,z0194338df7);zccb6539844=(ze7c2a94e2f*)ssGetPWorkValue(S,z2e8373622e);
#if zd4c1aa112f
SG_PRINTF(INFO,"\x23\x23\x23\x23\x61\x70\x70\x6c\x79\x69\x6e\x67\x20\x6e\x65\x78\x74\x20\x6f\x75\x74\x70\x75\x74\x20\x76\x6f\x6c\x74\x61\x67\x65\x20\x23\x23\x23\x23" "\n");
#endif
for(i=(0x429+817-0x75a);i<mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0xefd+3416-0x1c54);zfc0eea4f31=(uint32_t)mxGetPr(zad03d924d8)[(0xc97+1348-0x11db)];z0754dd67cc=(0x2363+684-0x260e)-(double)zccb6539844[channel].z0754dd67cc/262144.0f;offset=(double)zccb6539844[channel].offset/4.0f;if(z56d9a5f3fc==z0f0c5d6bfa){zaf9f0b2dbc=(double*)ssGetInputPortSignal(S,i);ze8c6171b31=zaf9f0b2dbc[(0x11d3+3596-0x1fdf)];}else{ze8c6171b31=(double)mxGetPr(z159ecbe81e)[i];}switch(zfc0eea4f31){case(0x22c6+644-0x2549):z56cade6b3a=(ze8c6171b31/10.0f*32767);z3ff4e9e346=(0x1d3c+2095-0x256a);break;case(0x18d1+2751-0x238e):z56cade6b3a=(ze8c6171b31/5.0f*32767);z3ff4e9e346=(0xa33+1244-0xf0e);break;case(0xfa4+2479-0x1950):z56cade6b3a=(ze8c6171b31/5.0f*65535);z3ff4e9e346=(0x8da+6-0x8e0);break;case(0x590+6792-0x2014):z56cade6b3a=(ze8c6171b31/10.0f*65535);z3ff4e9e346=(0x120d+2127-0x1a5c);break;case(0x71f+2489-0x10d3):z56cade6b3a=(ze8c6171b31/10.8f*65535);z3ff4e9e346=(0x737+7407-0x2426);break;case(0x1e9+5411-0x1706):z56cade6b3a=(ze8c6171b31/10.8f*32767);z3ff4e9e346=(0xc75+4403-0x1da7);break;default:z56cade6b3a=(0x1252+2398-0x1bb0);break;}if(z6b36f492e0){z56cade6b3a=(z56cade6b3a*z0754dd67cc-offset);}if(z3ff4e9e346){if(z56cade6b3a>32767)z56cade6b3a=32767;if(z56cade6b3a<-32767)z56cade6b3a=-32767;}else{if(z56cade6b3a>65535)z56cade6b3a=65535;if(z56cade6b3a<(0x96b+2383-0x12ba))z56cade6b3a=(0xa52+4593-0x1c43);}if((z224e3428b1!=z0f0c5d6bfa)||(uint32_t)mxGetPr(z04f0a23313)[i]){zf1756dff08->zaa30651ded[channel]=(uint32_t)((int32_t)z56cade6b3a);}
#if zd4c1aa112f
SG_PRINTF(INFO,"\x2a\x2a\x2a\x2a\x2a\x20\x44\x41\x43\x20\x43\x48\x25\x69\x20\x2a\x2a\x2a\x2a\x2a" "\n",channel+(0x632+5065-0x19fa));SG_PRINTF(INFO,"\x56\x6f\x6c\x74\x61\x67\x65\x3a\x20\x25\x66" "\n",ze8c6171b31);SG_PRINTF(INFO,"\x52\x41\x57\x20\x6f\x66\x66\x73\x65\x74\x3a\x20\x25\x64\x20\x2f\x2f\x20\x52\x41\x57\x20\x67\x61\x69\x6e\x3a\x20\x25\x64" "\n",zccb6539844[channel].offset,zccb6539844[channel].z0754dd67cc);SG_PRINTF(INFO,"\x45\x66\x66\x65\x63\x74\x69\x76\x65\x20\x6f\x66\x66\x73\x65\x74\x3a\x20\x25\x66\x20\x2f\x2f\x20\x45\x66\x66\x65\x63\x74\x69\x76\x65\x20\x67\x61\x69\x6e\x3a\x20\x25\x66" "\n",offset,z0754dd67cc);SG_PRINTF(INFO,"\x56\x61\x6c\x75\x65\x20\x77\x72\x69\x74\x74\x65\x6e\x20\x74\x6f\x20\x46\x50\x47\x41\x3a\x20\x30\x78\x25\x58" "\n",(uint32_t)((int32_t)z56cade6b3a));
#endif
}}
#endif
#include "sg_sfcn_glue.h"   


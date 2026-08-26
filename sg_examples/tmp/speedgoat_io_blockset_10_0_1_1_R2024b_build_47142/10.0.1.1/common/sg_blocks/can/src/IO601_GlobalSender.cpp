// Copyright 2006-2026 Speedgoat GmbH

#include <iostream>
#include <list>
#include <vector>
#include <pthread.h>
#include <unistd.h>
#include "IO601_Port.h"
#include "CAN_Message_Definition.h"
#include "IO601_BufferFifo.h"
#include "IO601_fcn.h"
#include "sg_printf.h"
void*z04bdc21d6e(void*zd30357c8a1){sg_IO601_Module_T*sg_IO601_pModule=(sg_IO601_Module_T*)zd30357c8a1;zddef351d79*zd0123dee73=(zddef351d79*)sg_IO601_pModule->ze232fe4686;SG_PRINTF(DEBUG,"\x53\x74\x61\x72\x74\x69\x6e\x67\x20\x47\x6c\x6f\x62\x61\x6c\x53\x65\x6e\x64\x65\x72\x20\x74\x68\x72\x65\x61\x64\x20\x66\x6f\x72\x20\x6d\x6f\x64\x75\x6c\x65\x20\x49\x44\x3a\x20\x25\x69" "\n",zd0123dee73->Idx+(0xcf2+1742-0x13bf));while(zd0123dee73->z1e9e004566){if((0x20bd+686-0x236b)==sg_waitForSemaphore(zd0123dee73->z2c4bf88f18)){unsigned int zafbf77ea0f=zd0123dee73->z79f8cf7707;unsigned int i=zafbf77ea0f;do{if((0x12b8+3660-0x2104)==zd0123dee73->z1e9e004566){goto z01caf8969c;}i=(i+(0x54b+5212-0x19a6))%(0x100b+906-0x1392);zd0123dee73->z79f8cf7707=i;if(z4ebbdba9a8!=sg_IO601_pModule->zfc9e60c9cc[i])continue;z75eb4775d3*z8681468931=NULL;if(i<(0x18+7987-0x1f49))z8681468931=(z75eb4775d3*)sg_IO601_pModule->CAN.zddad8a0171[i].z578fb42053.ze232fe4686;else z8681468931=(z75eb4775d3*)sg_IO601_pModule->LIN.z578fb42053.ze232fe4686;if(z8681468931==nullptr)continue;z8681468931->z7e9a628da0();}while(i!=zafbf77ea0f);}}z01caf8969c:SG_PRINTF(DEBUG,"\x46\x69\x6e\x69\x73\x68\x20\x47\x6c\x6f\x62\x61\x6c\x53\x65\x6e\x64\x65\x72\x20\x74\x68\x72\x65\x61\x64\x20\x66\x6f\x72\x20\x6d\x6f\x64\x75\x6c\x65\x20\x49\x44\x3a\x20\x25\x69" "\n",zd0123dee73->Idx+(0x1317+4272-0x23c6));zd0123dee73->z1e9e004566=(0x15cc+2691-0x204d);while(true)usleep((0x140a+1658-0x169c));return(void*)(0x2eb+5702-0x1931);}

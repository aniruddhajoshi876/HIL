// Copyright 2006-2026 Speedgoat GmbH

#pragma once
#if _MSC_VER > (0x15ca+316-0x10c6) || defined(__QNX__) || defined(__linux__)
#include <forward_list>
#include <list>
#include <vector>
#include <unordered_map>
#include <atomic>
#include <iostream>
#include "IO601_Port.h"
#include "IO601_fcn.h"
#include "IO601_BufferFifo.h"
class z6a2f506f50:public z75eb4775d3{public:z6a2f506f50(sg_IO601_Module_T*sg_IO601_pModule,unsigned char zb9276e93a2,bool ze9219a8eed);~z6a2f506f50();bool z7e9a628da0();bool zc6404ed94c(int z3e423c83e6=-(0x225+6602-0x1bee));bool zc897337106(int idx,void*zb499b90f58);int ze0625a3479(bool z86da42d288=true,unsigned int z9fdf3c9a1c=(0xab7+5651-0x20ca));bool ze75d150153();bool za4b310a2ed(unsigned char ze95d0de000,int*z2a9eb828a0,int*z0614da6382,int*zdd83b4727d,unsigned int*zab7a895c5c,void*zb425515a78);void zc09f785d3c(unsigned short z6f13d0cde5);unsigned short zab5d17a77b();private:bool z8a025f10ab;volatile bool zd56d22216e;std::atomic<unsigned char>z7e0125e502;std::atomic<unsigned char>ze82870b419;unsigned short z01839d579d[(0x248+2451-0xb9b)];std::vector<z09f3f22084<z9c620282bd,(0x35c+1311-0x847)>>z5c40c74a16;std::unordered_map<int,z09f3f22084<z9c620282bd,(0x152d+1561-0x1b12)>>z3473467bc6;unsigned char zf381a06625(unsigned char zaf816b563a);};
#endif


// Copyright 2006-2026 Speedgoat GmbH

#ifndef z8eae05395f
#define z8eae05395f
#ifndef MATLAB_MEX_FILE
#include <vector>
#include <sys/types.h>
#include <signal.h>
#ifdef __QNX__
#include <sys/neutrino.h>
#if defined(__QNX__) && (_NTO_VERSION >= (0xabc+2561-0x11f7))
#define z8da92480ce "\x64\x65\x76\x63\x61\x6e\x2d\x70\x63\x69\x65\x34\x30\x32\x2d\x65\x73\x64\x61\x63\x63\x2d\x71\x6e\x78\x37\x31\x30"
#else
#define z8da92480ce "\x64\x65\x76\x63\x61\x6e\x2d\x70\x63\x69\x65\x34\x30\x32\x2d\x65\x73\x64\x61\x63\x63\x2d\x71\x6e\x78\x37\x30\x30"
#endif
#endif
#include "IoModule.h"
#include "ESD_OfA_datatypes.h"
#include "ESD_Port.h"
#include "ESD_CAN_Port.h"
#include "ESD_LIN_Port.h"
#include "simstruc.h"
#define z3c56112bca "\x2f\x75\x73\x72\x2f\x73\x70\x65\x65\x64\x67\x6f\x61\x74\x2f\x73\x62\x69\x6e"
class ESD_Module:public sg::IoModule{private:bool z2e7c70562d;int pid;int z364b693676;uint8_t zc521bc5f62;uint8_t za74dad39f1;public:std::vector<z5bb7e7233c*>Ports;ESD_Module();ESD_Module(int z7ee7ea31cd,int id,int zcab18afec3,int Bus,int Slot);int z3ec0d782fc(SimStruct*S);int getPid();uint8_t z5b9677fabb();uint8_t z1218a3ae91();int z4b0a59bef2();void z3b7fee4e46();void z01237523a8();void z3b5ff4bc13(int z743e9390e5,uint32_t mode);void z8dd675c14e(const SetupInitValues*z11412ea6fa);void zd5ab0a77bb();~ESD_Module();};
#endif
#endif


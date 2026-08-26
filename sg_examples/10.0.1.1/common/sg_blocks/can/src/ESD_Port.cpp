// Copyright 2006-2026 Speedgoat GmbH

#include "ESD_Port.h"
#include "ESD_OfA.h"
z5bb7e7233c::z5bb7e7233c(){}z5bb7e7233c::z5bb7e7233c(int idx):index(idx){}z5bb7e7233c::z5bb7e7233c(int idx,int zeb694bba8f):index(idx),net(zeb694bba8f){}NTCAN_HANDLE z5bb7e7233c::z59662a1925(){return(NTCAN_HANDLE)handle;}void z5bb7e7233c::z2632697e45(int z9f18a118bc){handle=(NTCAN_HANDLE)z9f18a118bc;}void z5bb7e7233c::z9684946e0f(){SG_PRINTF_DEBUG("\x2a\x2a\x2a\x20\x50\x72\x69\x6e\x74\x50\x6f\x72\x74\x5b\x69\x64\x78\x20\x3d\x20\x25\x69\x5d\x3a\x20\x68\x61\x6e\x64\x6c\x65\x20\x3d\x20\x25\x69\x20\x74\x79\x70\x65\x20\x3d\x20\x25\x73" "\n",index,(int)handle,this->getType()==z7371dee8d9?"\x43\x41\x4e":"\x4c\x49\x4e");}void z5bb7e7233c::zcd7663b34b(int n){this->net=n;return;}int z5bb7e7233c::za9d23ef9b1(){return(int)net;}int z5bb7e7233c::z9deb312aac(){return index;}

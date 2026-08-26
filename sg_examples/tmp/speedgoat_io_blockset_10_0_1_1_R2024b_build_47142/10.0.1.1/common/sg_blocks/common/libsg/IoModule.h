// Copyright 2006-2026 Speedgoat GmbH

#ifndef z01854e276b
#define z01854e276b
#include <utility>
namespace sg{enum ModuleTypes{z9c22d16176=(0x446+4013-0x13f3),z9f46a6fb5b=(0x85f+1113-0xc36),z5c52701f3b=(0xbdd+5305-0x2013),z6a355dc6d4=(0x168b+2722-0x1ed3),zd88cd95267=(0x2017+1661-0xf0e),z5430874e8f=(0x1f63+422-0x981),z138604ba4c=(0xeb5+3300-0x193e),zda9a6809a6=(0xe36+1637-0x122c),ze8c316641c=(0xef2+383-0xdbe)};class IoModule{public:IoModule();IoModule(ModuleTypes type,int id);~IoModule();void setType(ModuleTypes type){z1c25fde91e=type;}ModuleTypes getType(){return z1c25fde91e;}void setId(int id){z79c95c2c58=id;}int getId(){return z79c95c2c58;}void z77e06df2b5(int zcab18afec3){zd740493682=zcab18afec3;}int z05c0bd4680(){return zd740493682;}void setPciInfo(int bus,int slot){z5082206007=std::make_pair(bus,slot);}std::pair<int,int>getPciInfo(){return z5082206007;}private:ModuleTypes z1c25fde91e;int z79c95c2c58;int zd740493682;std::pair<int,int>z5082206007;};}
#endif 


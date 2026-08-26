// Copyright 2006-2026 Speedgoat GmbH

#ifndef zf7f777c3ea
#define zf7f777c3ea
#include <list>
#include "IoModule.h"
#include "sg_common.h"
namespace sg{class IoModuleRegistry{public:static void add(IoModule*z91fc41457c);static IoModule*find(ModuleTypes type,int id);static IoModule*find(sg_PCIDevice*za6895d3edb);static void remove(ModuleTypes type,int id);private:IoModuleRegistry();static std::list<IoModule*>z91993b80b6;};}
#endif 


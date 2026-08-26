#ifndef __IEC_SERVER_BLOCK_H
#define __IEC_SERVER_BLOCK_H

#include "stdint.h"
//#include <map>
#include "iec_def.h"
#include "iec_block.h"

namespace iec61850
{

class cServerSetupBlock : public cBlock
{
    private:


    public:

        cServerSetupBlock() : cBlock() {};
        ~cServerSetupBlock();
};

class cServerReadBlock : public cBlock
{
    private:


    public:



        cServerReadBlock() : cBlock() {};
        ~cServerReadBlock();
};

}


#endif

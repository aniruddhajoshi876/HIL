#ifndef __IEC_CLIENT_BLOCK_H
#define __IEC_CLIENT_BLOCK_H

#include "stdint.h"
//#include <map>
#include "iec_def.h"
#include "iec_block.h"

namespace iec61850
{

class cClientSetupBlock : public cBlock
{
    private:


    public:

        cClientSetupBlock() : cBlock() {};
        ~cClientSetupBlock();
};

class cClientConnectionBlock : public cBlock
{
    private:


    public:

		cClientConnectionBlock() : cBlock() {};
        ~cClientConnectionBlock();
};

class cClientReadBlock : public cBlock
{
    private:


    public:



        cClientReadBlock() : cBlock() {};
        ~cClientReadBlock();
};

}


#endif

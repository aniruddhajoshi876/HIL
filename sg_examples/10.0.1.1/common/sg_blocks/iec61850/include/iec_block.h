#ifndef __IEC_BLOCK_H
#define __IEC_BLOCK_H

#include "sg_common.h"
#include "stdint.h"
#include "errno.h"
namespace iec61850
{

class cBlock
{
    private:



    public:
		bool InitDone = false;
        uint8_t BlockType = 0;
        void *DataAddress = NULL;
        void *Node = NULL;

        uint32_t remoteIP = 0;
        uint16_t remoteTcpPort = 102;

        uint16_t DataTable = 0;
        uint16_t DataIndex = 0;
        uint16_t DataQuantity = 0;

        int32_t assignDataAddress(uint16_t DataTable, uint16_t DataIndex, uint16_t DataQuantity);
        int32_t init(uint16_t DataTable, uint16_t DataIndex, uint16_t DataQuantity);

        cBlock();
        ~cBlock();
};

}

#endif

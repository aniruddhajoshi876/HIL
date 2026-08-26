#ifndef __MBTCP_SERVER_BLOCK_H
#define __MBTCP_SERVER_BLOCK_H

#include "stdint.h"
#include <stddef.h>

namespace modbusTCP
{

class cServerBlock
{
    private:



    public:

		bool InitDone = false;
        uint8_t BlockType = 0;
        void *DataAddress = NULL;
        void *Unit = NULL;

        uint32_t remoteIP = 0;
        uint16_t remoteTcpPort = 502;

        uint16_t DataTable = 0;
        uint16_t DataIndex = 0;
        uint16_t DataQuantity = 0;

        int32_t assignDataAddress(uint16_t DataTable, uint16_t DataIndex, uint16_t DataQuantity);
        int32_t init(uint16_t DataTable, uint16_t DataIndex, uint16_t DataQuantity);
        int32_t read(void *Destination);
        int32_t write(void *Source);

        cServerBlock();
        ~cServerBlock();
};

}

#endif

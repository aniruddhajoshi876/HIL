#ifndef __IEC_TRANSCEIVER_H
#define __IEC_TRANSCEIVER_H

#include "stdint.h"
#include "iec_def.h"
#include "iec_node.h"
#include "iec_block.h"
//#include <map>

namespace iec61850
{
class cTransceiver
{
    private:



    public:
    
        uint16_t TransceiverID;

        uint8_t FunctionCode = 0;
        uint16_t UnitID = 0;
        uint16_t address = 0;
        uint16_t quantity = 0;
        uint8_t byteCount = 0;
        uint8_t ErrorCode = 0;
        uint8_t ExceptionCode = 0;
        bool ERROR = false;
        void *DataAddress = NULL;
        void **value = NULL;
        uint8_t *val8 = NULL;
        uint16_t *val16 = NULL;

        int32_t process();
        int32_t init(uint8_t FunctionCode, uint16_t UnitID, uint16_t address, uint16_t quantity);
        int32_t terminate();

        int32_t read(void *Destination);
        int32_t write(void *Source);

        //TODO: einlesen: buffer[] with bytecount+malloc -> semafore&mutex (handshake/counter) atomic calls

        void *Connection;

        cTransceiver(uint16_t ID);
        ~cTransceiver();
};
    
}

#endif

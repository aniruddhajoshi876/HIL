#ifndef __MBTCP_CLIENT_TRANSCEIVER_H
#define __MBTCP_CLIENT_TRANSCEIVER_H

#include "stdint.h"
#include "mb_def.h"
#include "mbtcp_node.h"
#include "mbtcp_server_block.h"
#include <map>
#include <list>

namespace modbusTCP
{
class cClientTransceiver
{
    private:



    public:
    
		bool InitDone = false;
        uint16_t ID;

        uint8_t FunctionCode = 0;
        uint16_t UnitID = 0;
        uint16_t Address = 0;
        uint16_t Quantity = 0;
        uint8_t ByteCount = 0;
        uint8_t ErrorCode = 0;
        uint8_t ExceptionCode = 0;
        bool ERROR = false;
        bool EnaSend = true;
        uint32_t RequestTrigger = 0;
        uint32_t RequestTriggerOld = 0;
        bool Waiting_on_Response = false;
        bool EnableUpdateOnChange = false;
        uint64_t PollingTimer = 0;
        uint32_t PollingInterval = 0;

        void *DataAddress = NULL;
        void **Value = NULL;
        uint8_t *Val8 = NULL;
        uint16_t *Val16 = NULL;

        void log(Severity l, const char *m, ...);
        int32_t process();
        int32_t init(uint8_t FunctionCode, uint16_t UnitID, bool EnaSend, uint32_t PollingTimer, uint16_t Address, uint16_t Quantity, bool UpdateOnChange);

        int32_t read(void *Destination);
        int32_t write(void *Source);

        void *Connection;

        cClientTransceiver(uint16_t ID);
        ~cClientTransceiver();
};

} // namespace modbusTCP

#endif

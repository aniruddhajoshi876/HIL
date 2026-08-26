#ifndef __DNP3_SERVERSTATION_H
#define __DNP3_SERVERSTATION_H

#include "stdint.h"
#include <map>
#include "Outstation.h"
#include "DNPServer.h"
#include "ConnectionTCP.h"
#include "dnp3_api.h"
#include "dnp3_station.h"
#include "dnp3_serverblock.h"

namespace dnp3
{
    class cServerStation : public cStation
    {
    private:

        /* jpe object instances */
        DNPServerConfig CommunicationConfig;
        CConnectionTCP* ConnectionObject;
        CDNPServer* ServerObject;
        COutstation* CommunicationObject;

    public:

        uint32_t LocalIpAddr;
        uint16_t LocalTcpPort;
        uint32_t NumBlocks = 0;
        float Deadband = 0;

        SERVER_BLOCK_T* Blocks[DNP3_MAX_NUM_BLOCKS];

        void log(Severity l, const char* m, ...);

        int32_t addBlock(SERVER_BLOCK_T**);
        int32_t changeValue(SERVER_BLOCK_T* Block);
        int32_t init(uint32_t LocalIpAddr, uint16_t LocalTcpPort, void* Out);
        int32_t start();
        int32_t process();
        int32_t terminate();
        int32_t setDeadBand(uint8_t grp, uint16_t idx, float band);
        int32_t setDeadBand(uint8_t grp, float band);

        cServerStation(uint16_t ID) : cStation(ID) {};
        ~cServerStation();
    };

    class cServerCallback : public IOutstationCallback
    {
    private:
        virtual DNP3_STATUS_t handle_appInit(int8u* p_app, int16u len);
        virtual DNP3_STATUS_t handle_appStart(int8u* p_app, int16u len);
        virtual DNP3_STATUS_t handle_operateBOut(int16u idx, int8u ctrlCode, int8u cnt, int32u, int32u);
        virtual DNP3_STATUS_t handle_operateAOut(int16u idx, int8u flags, double64 val);
        virtual DNP3_STATUS_t handle_restart(int8u bCold);
    public:
        cServerCallback() {};
        ~cServerCallback() {};
    };

}

#endif
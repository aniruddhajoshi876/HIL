#ifndef __MBRTU_CLIENT_INTERFACE_H
#define __MBRTU_CLIENT_INTERFACE_H

#include "stdint.h"
#include <vector>

#include "mbrtu_client_connection.h"
#include "mbrtu_interface.h"



namespace modbusRTU
{

class cClientInterface : public cInterface
{
  private:
  public:
    bool Stop = false;

    uint16_t ModuleType;
    uint16_t ModuleID;
    uint8_t Channel;
    uint32_t ResponseTimeout;
    uint8_t Baton;

    bool InitialRequest = true;
    bool Successive = false;
    uint32_t ResponseTimer;

    std::vector<cClientConnection *> Connections;
   
    int32_t processRxData();

    bool isWaiting();
    void stopWaiting();
    void passBaton();

    int32_t addConnection(uint8_t NodeID, cClientConnection **Connection);
    int32_t getConnection(uint8_t NodeID, cClientConnection **Connection);
    bool isConnection(uint8_t NodeID);
   

    int32_t process();
    int32_t terminate();
    int32_t init(uint16_t ModuleType, uint16_t ModuleID, uint8_t Channel, uint32_t ResponseTimeout,
                 bool ByteSwap, uint32_t InterfaceID, MB_SERIAL_INFO_T SerialInfo);

    cClientInterface(uint16_t ID) : cInterface(ID) {};
    ~cClientInterface();
};

} // namespace modbusRTU

#endif

#ifndef __MBRTU_SERVER_INTERFACE_H
#define __MBRTU_SERVER_INTERFACE_H

#include "mbrtu_server_node.h"
#include "stdint.h"
#include <cstdint>

#include <fcntl.h>
#include <stdarg.h>
#include <sys/types.h>
#include <unistd.h>

namespace modbusRTU
{
class cServerInterface : public cInterface
{
  private:
  public:
    uint16_t ModuleType;
    uint16_t ModuleID;
    uint8_t Channel;
    uint32_t ResponseDelay;


    
    std::map<uint16_t, cNode *> Nodes;

    int32_t processRxData();
    int32_t addNode(uint8_t ID, cNode **Node);
    int32_t getNode(uint8_t ID, bool Redirect255, cNode **Node);
    int32_t getFirstNode(cNode **Node);
    bool isNode(uint8_t ID);
    int32_t process();
    int32_t terminate();
    int32_t init(uint16_t ModuleType, uint16_t ModuleID, uint8_t Channel, uint32_t ResponseDelay,
                 bool ByteSwap, MB_SERIAL_INFO_T SerialInfo);
    int32_t getDataAddress(uint8_t ID, uint16_t DataTable, uint16_t DataIndex,
                           uint16_t DataQuantity, void **Address);

    cServerInterface(uint16_t ID) : cInterface(ID) {};
    ~cServerInterface();
};
} // namespace modbusRTU

#endif

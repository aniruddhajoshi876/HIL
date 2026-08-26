#ifndef __IEC_GOOSE_SUBSCRIBER_H
#define __IEC_GOOSE_SUBSCRIBER_H

#include "sg_printf.h"

#include "iec_def.h"
#include "iec_goose_node.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

#include "goose_receiver.h"
#include "goose_subscriber.h"
#include "hal_thread.h"
#include "linked_list.h"
#include "mms_value.h"

namespace iec61850
{
  class cGooseSNode : public cNodeGoose
  {
  private:
  public:
    std::string Interface;
    std::string EthLabel;
    int8_t* DataOut = NULL;
    uint32_t DataType = 0;
    uint8_t NumVariables = 0;
    uint16_t DataTypeBytes = 0;
    uint16_t DataLength = 0;
    uint64_t MacAddr;
    uint16_t AppID;
    std::vector<std::string> stReadVect;

    GooseReceiver receiver = NULL;
    GooseSubscriber subscriber = NULL;

    void log(Severity l, const char* m, ...);

    int32_t process();
    int32_t start();
    int32_t terminate();
    int32_t init(uint32_t DataType, uint16_t nouse, uint16_t NumVariables, uint64_t MacAddr,
      std::string Interface, std::string EthLabel, uint16_t AppID,
      std::vector<std::string> stReadVect);

    cGooseSNode(uint16_t ID) : cNodeGoose(ID) {};
    ~cGooseSNode();
  };

} // namespace iec61850

#endif

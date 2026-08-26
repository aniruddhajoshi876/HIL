#ifndef __IEC_GOOSE_PUBLISHER_H
#define __IEC_GOOSE_PUBLISHER_H

#include "sg_printf.h"

#include "iec_def.h"
#include "iec_goose_node.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

#include "goose_publisher.h"
#include "hal_thread.h"
#include "mms_value.h"

namespace iec61850
{
class cGoosePNode : public cNodeGoose
{
  private:
  public:
    /* Enumeration of sending states */
    typedef enum { Normal, First, Second, Third } SendStates;

    bool ChangedFlag = false;
    bool Sent = false;
    SendStates SendState;
    uint32_t OldTime = 0;
    uint32_t BaseIntervall = 0;
    uint32_t ChangedIntervall = 0;
    uint8_t IntervallMultiplier = 1;

    std::vector<std::string> stReadVect;
    uint16_t AppID;
    uint16_t VLanID;
    uint8_t VLanPriority;

    uint64_t MacAddr;

    std::vector<uint8_t> DataIdx;

    std::string Interface;
    std::string EthLabel;
    int8_t *DataIn = NULL;
    uint32_t DataType;
    uint8_t NumVariables = 0;
    uint16_t DataTypeBytes = 0;
    uint16_t DataLength = 0;

    CommParameters gooseCommParameters;
    GoosePublisher publisher = NULL;
    LinkedList DataSetValues = NULL;
    std::vector<MmsValue *> Values;
    std::vector<MmsValue *> OldValues;

    void log(Severity l, const char *m, ...);

    int32_t process();
    int32_t start();
    int32_t terminate();
    int32_t init(uint32_t DataType, uint16_t nouse, uint8_t NumVariables, uint64_t MacAddr,
                 std::string Interface, std::string EthLabel, std::vector<std::string> stReadVect,
                 uint16_t AppID, uint16_t VLanID, uint8_t VLanPriority, uint32_t BaseIntervall);
    uint32_t getTime(void);
    void updateValues(void);

    cGoosePNode(uint16_t ID) : cNodeGoose(ID) {};
    ~cGoosePNode();
};

} // namespace iec61850

#endif

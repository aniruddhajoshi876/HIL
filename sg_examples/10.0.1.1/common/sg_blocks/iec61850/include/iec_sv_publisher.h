#ifndef __IEC_SV_PUBLISHER_H
#define __IEC_SV_PUBLISHER_H

#include "sg_printf.h"

#include "iec_def.h"
#include "iec_sv_node.h"
#include "sv_publisher.h"
#include <cstdarg>
#include <ctime>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

#include "hal_thread.h"
#include "mms_value.h"
#include "sv_publisher.h"

namespace iec61850
{
class cSVPNode : public cNodeSV
{
  private:
  public:
    bool EnaTimeStamp = false;

    std::vector<uint8_t> DataIdx;
    uint8_t TimeIndex;
    uint64_t PollingInterval = 0;
    uint64_t OldTime = 0;
    std::string Interface;
    std::string ASDU_Name;
    std::string EthLabel;
    int8_t *DataIn = NULL;
    uint32_t DataType = 0;
    uint8_t NumVariables = 0;
    uint16_t DataTypeBytes = 0;
    uint16_t DataLength = 0;
    uint16_t AppID;
    uint16_t VLanID;
    uint8_t VLanPriority;
    uint64_t MacAddr;

    CommParameters svCommParameters;
    SVPublisher svPublisher;
    SVPublisher_ASDU ASDU1;

    void log(Severity l, const char *m, ...);

    int32_t process();
    int32_t start();
    int32_t terminate();
    int32_t init(uint32_t PollingInterval, uint32_t DataType, uint8_t EnaTimeStamp, uint16_t nouse,
                 uint8_t NumVariables, uint64_t MacAddr, std::string Interface,
                 std::string ASDU_Name, std::string EthLabel, uint16_t AppID, uint16_t VLanID,
                 uint8_t VLanPriority);
    uint64_t getTime(void);
    void publish(void);

    cSVPNode(uint16_t ID)
        : cNodeSV(ID) {}; 
    ~cSVPNode();
};

} // namespace iec61850

#endif

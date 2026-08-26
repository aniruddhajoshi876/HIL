#ifndef __IEC_CLIENT_TRANSCEIVER_H
#define __IEC_CLIENT_TRANSCEIVER_H

#include "sg_printf.h"
#include "hal_thread.h"
#include "iec.h"
#include "iec61850_client.h"
#include "iec_block.h"
#include "iec_def.h"
#include "iec_node.h"
#include "stdint.h"
#include <list>
#include <map>
#include <vector>

#define MMS_DATAITEM_TYPE_UNKNOWN 0
#define MMS_DATAITEM_TYPE_CONTROL 1
#define MMS_DATAITEM_TYPE_READ    2
#define MMS_DATAITEM_TYPE_WRITE   3

#define MMS_DATAITEM_STATE_ERROR    -1
#define MMS_DATAITEM_STATE_UNKNOWN  0
#define MMS_DATAITEM_STATE_INIT     1
#define MMS_DATAITEM_STATE_INITDONE 2
#define MMS_DATAITEM_STATE_READY    3

namespace iec61850
{
struct TransceiverDataItem {
    uint32_t DevFlags;
    uint32_t HostFlags;
    uint8_t Type;
    int8_t State;
    uint32_t Index;
    uint32_t DataType;
    uint32_t DataLength;
    int32_t Fc;
    void *ValRef;
    void *VarSpec;
    void *Data;

    void *ObjRef;
    std::string ObjPath;

    /* Struct constructor */
    TransceiverDataItem(uint8_t t, uint32_t idx, uint32_t dt, uint32_t len, int32_t fc, void *data,
                        std::string objpath)
        : DevFlags(0), HostFlags(0), Type(t), State(MMS_DATAITEM_STATE_UNKNOWN), Index(idx),
          DataType(dt), DataLength(len), Fc(fc), ValRef(NULL), VarSpec(NULL), Data(data),
          ObjRef(NULL), ObjPath(objpath)
    {
    }
};

class cClientTransceiver
{
  private:
  public:
    bool IsFaulty = false;
    uint32_t State = 0;

    bool CtrlMode = false;
    bool CtrlTest = false;

    int32_t DataType = 0;
    uint16_t TransceiverID;
    uint64_t PollingInterval = 0;
    uint64_t Timer = 0;
    uint16_t ReadDim = 0;
    uint16_t WriteDim = 0;
    uint16_t ControlDim = 0;

    void *Connection;

    void log(Severity l, const char *m, ...);
    int32_t init(uint32_t PollingInterval, uint16_t ReadDim, uint16_t WriteDim, uint16_t ControlDim,
                 bool CtrlMode, bool CtrlTest, int type);
    int32_t start();
    int32_t process();
    int32_t reset();
    int32_t operate();
    int32_t prepare();
    int32_t read();
    int32_t write();
    int32_t terminate();
    int32_t addDataItem(uint8_t Type, uint32_t Index, uint32_t DataType, uint32_t DataLength,
                        std::string ObjPath);

    void updateControlItem(uint32_t Index, bool Operate, void *Data);
    void updateReadItem(uint32_t Index, bool Read, void *Data);
    void updateWriteItem(uint32_t Index, bool Write, void *Data);
    bool areDataItemsReady();

    std::vector<TransceiverDataItem *> ControlItems;
    std::vector<TransceiverDataItem *> ReadItems;
    std::vector<TransceiverDataItem *> WriteItems;

    cClientTransceiver(uint16_t ID);
    virtual ~cClientTransceiver();

};
} // namespace iec61850

#endif

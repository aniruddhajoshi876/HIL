#ifndef __TRDP_TRANSCEIVER_H
#define __TRDP_TRANSCEIVER_H

#include "sg_printf.h"

#include "trdp_base.h"
#include "trdp_def.h"

namespace ns_sg_trdp
{
class cTransceiver : public cBase
{
    private:
    public:
    uint8_t Type = TRDP_BLOCK_TYPE_UNDEF;
    uint8_t *InputBuffer = NULL;
    uint8_t *OutputBuffer = NULL;
    uint32_t MaxInDataLen = 0;
    uint32_t MaxOutDataLen = 0;
    uint32_t InDataLen = 0;
    uint32_t OutDataLen = 0;
    uint32_t ComID = 0;
    uint32_t DestIpAddr;
    uint32_t SrcIpAddr;
    uint32_t NumReplies;
    uint32_t Timeout;
    uint32_t WaitingForReply = 0;
    uint8_t TransportLayer;
    bool ReplyRequired = false;
    bool TimoutEnabled = false;
    bool Pull = false;
    void *uid = NULL;

    uint32_t HostFlagsTx = 0;
    uint32_t HostFlagsRx = 0;
    uint32_t DevFlagsTx = 0;
    uint32_t DevFlagsRx = 0;

    uint32_t HostFlagsTx2 = 0;
    uint32_t DevFlagsTx2 = 0;

    void *Handle;
    void *RxHandle;
    void *Station;

    void log(Severity l, const char *m, ...);
    int32_t init(uint8_t Type, uint32_t ComID, uint32_t Timeout, uint32_t DestIpAddr, uint32_t SrcIpAddr,
                 uint8_t *Buffer, uint32_t MaxDataLen, bool Pull);
    int32_t init(uint8_t Type, uint32_t ComID, uint32_t Timeout, uint32_t DestIpAddr,
                 uint8_t *InputBuffer, uint8_t *OutputBuffer, uint32_t MaxInDataLen, uint32_t MaxOutDataLen, bool ReplyRequired, uint32_t NumReplies, uint8_t TransportLayer);
    int32_t start();
    int32_t process();
    int32_t terminate();

    cTransceiver(uint32_t ID);
    virtual ~cTransceiver();
};
} // namespace ns_sg_trdp

#endif

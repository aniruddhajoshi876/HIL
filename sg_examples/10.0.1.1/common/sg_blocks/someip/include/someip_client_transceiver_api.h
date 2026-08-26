#ifndef __SOMIEIP_CLIENT_TRANSCEIVER_API_H
#define __SOMIEIP_CLIENT_TRANSCEIVER_API_H

#include <someip_def.h>
#include <list>
#include <stdint.h>
#include <wchar.h>

namespace sg_ns_someip
{
class cClientTransceiverApi
{
  private:
  public:
    void *Impl = NULL;

    int32_t init(uint16_t ServiceID, uint16_t InstanceID, uint16_t MethodID, uint16_t EventID,
                 uint16_t EventGroupID, bool OutPortConnected, uint32_t OutDataLength,
                 bool InPortConnected, uint32_t InDataLength);

    void processOutport(void *Port);
    void processInport(void *Port);

    cClientTransceiverApi() {};
    ~cClientTransceiverApi() {};
};
} // namespace sg_ns_someip

#endif

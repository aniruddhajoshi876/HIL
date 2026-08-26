#ifndef __SOMIEIP_CLIENT_STATION_API_H
#define __SOMIEIP_CLIENT_STATION_API_H

#include <someip_client_transceiver_api.h>
#include <stdint.h>

namespace sg_ns_someip
{
class cClientStationApi
{
  private:
  public:
    void *Impl = NULL;

    int32_t init(uint32_t IpAddr, uint16_t TcpPort);
    int32_t addTransceiver(cClientTransceiverApi **Api);

    cClientStationApi() {};
    ~cClientStationApi() {};
};

} // namespace sg_ns_someip

#endif

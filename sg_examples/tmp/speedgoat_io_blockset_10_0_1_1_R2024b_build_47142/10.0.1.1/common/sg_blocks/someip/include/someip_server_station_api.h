#ifndef __SOMIEIP_SERVER_STATION_API_H
#define __SOMIEIP_SERVER_STATION_API_H

#include <someip_server_service_api.h>
#include <stdint.h>

namespace sg_ns_someip
{

class cServerStationApi
{
  private:
  public:
    void *Impl = NULL;

    int32_t init(uint32_t IpAddr, uint16_t TcpPort);
    int32_t addService(cServerServiceApi **Api);

    cServerStationApi() {};
    ~cServerStationApi() {};
};

} // namespace sg_ns_someip

#endif

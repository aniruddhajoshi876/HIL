#ifndef __TRDP_STATION_H
#define __TRDP_STATION_H

#include "sg_printf.h"

#include "trdp_base.h"
#include "trdp_transceiver.h"

#include <vector>

namespace ns_sg_trdp
{
class cStation : public cBase
{
  private:
  public:

    uint32_t IpAddr = 0;
    uint16_t TcpPort = 0;

    void *Session;

    /* Vector of transceivers */
    std::vector<cTransceiver *> Transceivers;

    void log(Severity l, const char *m, ...);

    int32_t init(uint32_t IpAddr, uint16_t TcpPort);
    int32_t start();
    int32_t process();
    int32_t terminate();

    int32_t addTransceiver(cTransceiver **Transceiver);

    cStation(uint32_t ID);
    ~cStation();
};

} // namespace ns_sg_trdp

#endif

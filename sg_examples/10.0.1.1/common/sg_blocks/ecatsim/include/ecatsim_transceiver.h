#ifndef __ECATSIM_TRANSCEIVER_H
#define __ECATSIM_TRANSCEIVER_H

#include "sg_printf.h"

#include "ecatsim_base.h"
#include <ecatsim_transceiver.h>
#include <stdint.h>
#include <wchar.h>

namespace sg_ns_ecatsim
{
class cTransceiver : public cBase
{
  private:
  public:
    void log(Severity l, const char *m, ...);
    int32_t init();
    int32_t start();
    int32_t process();
    int32_t terminate();

    int32_t read(uint8_t *Destination, uint32_t TypeLength, uint32_t Width, uint32_t Offset, bool isBool);
    int32_t write(uint8_t *Source, uint32_t TypeLength, uint32_t Width, uint32_t Offset, bool isBool);


    uint8_t Type = 0;

    void *Network = NULL;

    uint32_t HostFlagsTx = 0;
    uint32_t HostFlagsRx = 0;
    uint32_t DevFlagsTx = 0;
    uint32_t DevFlagsRx = 0;

    cTransceiver(uint32_t ID);
    virtual ~cTransceiver();
};

} // namespace sg_ns_ecatsim

#endif

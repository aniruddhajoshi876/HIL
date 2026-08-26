#ifndef __ECATSIM_NETWORK_H
#define __ECATSIM_NETWORK_H

#include "sg_printf.h"

#include "ecatsim_base.h"
#include "ecatsim_transceiver.h"
#include "ecatsim_object.h"

#include <vector>

namespace sg_ns_ecatsim
{
class cNetwork : public cBase
{
  private:
  public:
    uint32_t InstanceID = 0;
    
    /* Vector of transceivers */
    std::vector<cTransceiver *> Transceivers;

    /* Vector of objects */
    std::vector<cObject *> Objects;

    void log(Severity l, const char *m, ...);
    int32_t init(int32_t FirstDevice);
    int32_t start();
    int32_t process();
    int32_t terminate();

    int32_t addTransceiver(cTransceiver **Transceiver);
    int32_t getTransceiver(uint32_t, cTransceiver **);

    int32_t addObject(cObject **Object);
    int32_t getObject(uint32_t, cObject **);

    int32_t executeJob();

    cNetwork(uint32_t ID);
    ~cNetwork();
};

} // namespace sg_ns_ecatsim

#endif

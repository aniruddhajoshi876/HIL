#ifndef __ECATSIM_ROOT_H
#define __ECATSIM_ROOT_H

#include "sg_printf.h"

#include "ecatsim_base.h"
#include "ecatsim_network.h"

#include <vector>

namespace sg_ns_ecatsim
{
class cRoot : public cBase
{
  private:

    /* Vector of networks */
    std::vector<cNetwork *> Networks;

    /* Background thread handle */
    void *MainThread = NULL;

  public:
    uint32_t NumSlaves = 0;
    uint32_t NumLic = 0;

    int32_t init();
    int32_t start();
    void run();
    int32_t process();
    void stop();
    int32_t terminate();

    void log(Severity l, const char *m, ...);
    int32_t addNetwork(uint32_t ID, cNetwork **Network);
    int32_t getNetwork(uint32_t, cNetwork **);

    cRoot() {};
    ~cRoot() {};
};
} // namespace sg_ns_ecatsim

#endif

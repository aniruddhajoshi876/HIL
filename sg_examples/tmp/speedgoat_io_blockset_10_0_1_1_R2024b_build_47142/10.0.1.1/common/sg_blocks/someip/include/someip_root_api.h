#ifndef __SOMIEIP_ROOT_API_H
#define __SOMIEIP_ROOT_API_H

#include "sg_common.h"

#include <cstdint>
#include <stdint.h>

namespace sg_ns_someip
{
class cRootApi
{
  private:
  public:
    void *Impl = NULL;

    /* Methods */
    int32_t init();
    void start();
    int32_t stop();
    int32_t addStation(uint32_t ID, uint8_t Type, void **Api);

    cRootApi() {};
    ~cRootApi() {};
};
} // namespace sg_ns_someip

#endif

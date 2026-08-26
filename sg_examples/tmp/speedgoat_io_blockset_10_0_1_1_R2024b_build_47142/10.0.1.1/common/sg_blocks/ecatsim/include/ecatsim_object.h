#ifndef __ECATSIM_OBJECT_H
#define __ECATSIM_OBJECT_H

#include "sg_printf.h"

#include "ecatsim_base.h"
#include <ecatsim_object.h>
#include <stdint.h>
#include <wchar.h>

namespace sg_ns_ecatsim
{
class cObject : public cBase
{
  private:
  public:
    void log(Severity l, const char *m, ...);
    int32_t init(uint32_t SlaveAddress, uint32_t Index, uint32_t SubIndex, uint32_t Length);
    int32_t start();
    int32_t process();
    int32_t terminate();
    int32_t update(void *DataInPort, bool *EnableInPort, uint32_t *LengthInPort,
                     void *DataOutPort, uint32_t *StatusOutPort, uint32_t *LengthOutPort);

    void *Network = NULL;

    uint32_t WriteCounter = 0;
    uint32_t SlaveAddress;
    uint32_t Index;
    uint32_t SubIndex;
    uint32_t Length;
    uint32_t MaxLength;

    void *Data;

    cObject(uint32_t ID);
    virtual ~cObject();
};

} // namespace sg_ns_ecatsim

#endif

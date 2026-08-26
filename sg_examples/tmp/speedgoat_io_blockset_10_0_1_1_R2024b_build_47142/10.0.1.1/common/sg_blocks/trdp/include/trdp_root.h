#ifndef __TRDP_ROOT_H
#define __TRDP_ROOT_H

#include "sg_printf.h"

#include "trdp_station.h"

#include <map>

namespace ns_sg_trdp
{
class cRoot : public cBase
{
  private:
    /* List of stations */
    std::map<uint32_t, cStation *> Stations;

    /* Background thread handle */
    void *MainThread = NULL;

  public:

    void log(Severity l, const char *m, ...);

    int32_t init();
    void launch();
    int32_t start();
    int32_t process();
    int32_t terminate();
    void stop();

    bool isStation(uint32_t ID);
    int32_t addStation(uint32_t ID, uint8_t Type, cStation **Station);
    int32_t getStation(uint32_t, cStation **);

    cRoot() {};
    ~cRoot() {};
};
} // namespace ns_sg_trdp

#endif

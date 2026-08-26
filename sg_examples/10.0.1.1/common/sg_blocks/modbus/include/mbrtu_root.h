#ifndef __MBRTU_ROOT_H
#define __MBRTU_ROOT_H

#include "mbrtu_client_interface.h"
#include "mbrtu_interface.h"
#include "mbrtu_server_interface.h"
#include <map>
#include <utility>

namespace modbusRTU
{

class cRoot
{
  private:
    /* List of remote station relations */
    std::map<uint16_t, cInterface *> Interfaces;

    void *MBRTU_MainThread;

    void log(Severity l, const char *m, ...);

  public:

    bool Stop = false;
    bool Start = false;
    bool Run = false;

    bool InitDone = false;
    uint32_t Timeout = 0; 

    bool isInterface(uint16_t ID);
    int32_t addInterface(uint16_t ID, bool IsClient, cInterface **Interface);
    int32_t getInterface(uint16_t ID, cInterface **Interface);
    int32_t init();
    void start();
    int32_t stop();
    int32_t terminate();
    int32_t process();

    cRoot();
    ~cRoot();
};

} // namespace modbusRTU

#endif

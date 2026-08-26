#ifndef __MBTCP_ROOT_H
#define __MBTCP_ROOT_H

#include "mbtcp_node.h"
#include "mbtcp_client_node.h"
#include "mbtcp_server_node.h"
#include <map>

namespace modbusTCP
{

class cRoot
{
  private:
    /* List of remote station relations */
    std::map<uint16_t, cNode *> Nodes;

    void *MB_MainThread;

  public:
    bool InitDone = false;
    bool Run = false;
    bool Stop = false;

    void log(Severity l, const char *m, ...);
    bool isNode(uint16_t ID);
    int32_t addNode(uint16_t ID, bool IsClient, cNode **Node);
    int32_t getNode(uint16_t ID, cNode **Node);
    int32_t init();
    int32_t terminate();
    int32_t process();

    cRoot();
    ~cRoot();
};

} // namespace modbusTCP

#endif

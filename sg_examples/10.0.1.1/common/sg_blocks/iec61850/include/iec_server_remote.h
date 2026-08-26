#ifndef __IEC_SERVER_REMOTE_H
#define __IEC_SERVER_REMOTE_H

#include "stdint.h"
//#include <map>
#include <list>
#include "iec_def.h"
#include "iec_node.h"
#include "iec_unit.h"

namespace iec61850
{
class cServerRemote
{
    private:

    public:
    
        uint32_t ResponseDelay = 0;

        uint16_t ID = 0;

        void *Node;

        std::list<IEC_SEND_FRAME_T> SendQueue;

        int32_t process();
        int32_t init(int RemoteSocket, bool Swap, uint32_t ResponseDelay);
        int32_t terminate();

        uint32_t getTime(void);

        cServerRemote(uint16_t ID);
        ~cServerRemote();
};

    
}

#endif

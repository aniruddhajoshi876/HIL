#ifndef __IEC_ROOT_H
#define __IEC_ROOT_H

#include "sg_printf.h"
#include <map>
#include "iec_node.h"

namespace iec61850
{

    class cRoot
    {
    private:

        /* List of remote station relations */
        std::map<uint16_t, cNode*> Nodes;

        void* MainThread;
        
    public:

        bool IsFaulty = false;
        uint32_t State = 0;

        void log(Severity l, const char *m, ...);

        bool isNode(uint16_t ID);
        int32_t addNode(uint16_t ID, bool IsClient, cNode **Node);
        int32_t getNode(uint16_t ID, cNode** Node);
        int32_t init();
        int32_t terminate();
        void launch();
        int32_t start();
        void stop();
        int32_t process();

        cRoot();
        ~cRoot();

    };

}

#endif

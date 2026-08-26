#ifndef __IEC_GOOSE_ROOT_H
#define __IEC_GOOSE_ROOT_H

#include "sg_printf.h"

#include <map>
#include "iec_goose_publisher.h"
#include "iec_goose_subscriber.h"
#include "iec_goose_node.h"

namespace iec61850
{
class cGooseRoot
{
    private:

    public:

		/* List of remote station relations */
		std::map<uint16_t, cNodeGoose*> Nodes;

            bool IsFaulty = false;
        uint32_t State = 0;

		void* IEC_GOOSEThread;
		uint16_t NodeIDs=0;

        const char* interface = "wm1";

                        void log(Severity l, const char *m, ...);

        bool isNode(uint16_t ID);
        int32_t addNode(uint16_t ID, bool IsPublisher, cNodeGoose **Node);
        int32_t getNode(uint16_t ID, cNodeGoose** Node);
        int32_t init();
        void launch();
        int32_t start();
        void stop();
        int32_t terminate();
        int32_t process();

        cGooseRoot();
        ~cGooseRoot();
};

    
}

#endif

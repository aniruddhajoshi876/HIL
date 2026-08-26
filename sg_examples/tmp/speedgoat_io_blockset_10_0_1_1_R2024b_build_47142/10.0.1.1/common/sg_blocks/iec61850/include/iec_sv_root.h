#ifndef __IEC_SV_ROOT_H
#define __IEC_SV_ROOT_H

#include "sg_printf.h"

#include <map>
#include "iec_sv_publisher.h"
#include "iec_sv_subscriber.h"
#include "iec_sv_node.h"

namespace iec61850
{
class cSVRoot
{
    private:

    public:

		/* List of remote station relations */
		std::map<uint16_t, cNodeSV*> Nodes;

            bool IsFaulty = false;
        uint32_t State = 0;

		void* IEC_SVThread;
		uint16_t NodeIDs=0;


        const char* interface = "wm1";

                        void log(Severity l, const char *m, ...);

        bool isNode(uint16_t ID);
        int32_t addNode(uint16_t ID, bool IsPublisher, cNodeSV **Node);
        int32_t getNode(uint16_t ID, cNodeSV** Node);
        int32_t init();
        void launch();
        int32_t start();
        void stop();
        int32_t terminate();
        int32_t process();
        char* findSVEthernetLabel(const char* EthTranslateFile, const char* EthLabel);

        cSVRoot();
        ~cSVRoot();
};

    
}

#endif

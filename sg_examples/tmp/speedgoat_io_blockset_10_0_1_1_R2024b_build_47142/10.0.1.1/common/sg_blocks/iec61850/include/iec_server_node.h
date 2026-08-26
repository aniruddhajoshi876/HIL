#ifndef __IEC_SERVER_NODE_H
#define __IEC_SERVER_NODE_H

#include "stdint.h"
#include "iec_def.h"
#include "iec_node.h"
#include "iec_server_readwrite.h"
#include "sg_printf.h"


#include "iec61850_server.h"
#include "hal_thread.h"
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <array>

namespace iec61850
{
class cServerNode : public cNode
{
    private:

    public:

		/***/
		unsigned int memory = 99;
		/***/
    
        bool IsFaulty = false;
        uint32_t State = 0;

        uint32_t IpAddr = 0;
        uint16_t TcpPort = 102;
        uint32_t KeepAlive = 0;
        uint16_t ReadWriteIDs = 1;
        uint32_t NumReadWrites = 0;
        std::array<int, 19> AccessPolicyArray = {1};
        bool WantAuthentication = false;
        char* Enabler;

        int ServerSocket = -1;

        bool IsCom = false;
        uint32_t ResponseDelay = 0;

        std::map <uint16_t, cServerReadWrite*> ReadWrites;
        std::vector<DataAttribute> DAList;

        void saveDataModel(char pathRef[254], IedModel *DataModel, const char *FC_old);

        int32_t addReadWrite(cServerReadWrite **ReadWrite);
        int32_t getReadWrite(uint16_t ID, cServerReadWrite** ReadWrite);
        int32_t getFirstReadWrite(cServerReadWrite** ReadWrite);
        bool isReadWrite(uint8_t ID);

        int32_t copyFromIedModelToBlock(cServerReadWrite *ServerBlock);
        int32_t copyFromBlockToIedModel(cServerReadWrite *ServerBlock);

        void log(Severity l, const char *m, ...);
        int32_t process();
        int32_t init(uint32_t LocalIpAddr, uint16_t LocalTcpPort, uint32_t KeepAlive, bool WantAuthentication, const char* Enabler, std::array<int, 19> AccessPolicyArray);
        int32_t start();

        void setFcWriteAccess(std::array<int, 19> AccessPolicyArray);

        IedModel* IedCfgModel;
        IedModel iecModel;
        IedServer iedServer;

        int32_t terminate(void);
        cServerNode(uint16_t ID) : cNode(ID) {};
        ~cServerNode();
        uint32_t  fillDataAttributeVector(cServerReadWrite *ReadWrite);
        MmsValue* transformMMSVal(std::vector<cdiggins::any>::iterator iter, std::vector<DataAttribute>::iterator itDA, bool RW, MmsValue* readVal = NULL);
};

}

#endif

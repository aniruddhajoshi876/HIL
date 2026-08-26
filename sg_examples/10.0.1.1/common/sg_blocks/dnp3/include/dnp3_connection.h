#ifndef __DNP3_REMOTESTATION_H
#define __DNP3_REMOTESTATION_H

#include "stdint.h"
#include <map>
#include "Master.h"
#include "ConnectionTCP.h"
#include "IMasterCallback.h"
#include "dnp3_api.h"
#include "dnp3_clientblock.h"

namespace dnp3
{
    class cConnection
    {
        private:

            /* Class containing receive callbacks */
            class cCallback : public IMasterCallback
            {
            public:
                cConnection* Parent;

                cCallback(cConnection*);
                ~cCallback();

            private:
                virtual void handle(const CObjHdr* p_header, int16u index, CCountPoint& point) override;
                virtual void handle(const CObjHdr* p_header, int16u index, CStatsPoint& point) override;
                virtual void handle(const CObjHdr* p_header, int16u index, CFrozenCountPoint& point) override;
                virtual void handle(const CObjHdr* p_header, int16u index, CCTOPoint& point) override;
                virtual void handle(const CObjHdr* p_header, int16u index, CEvent<CCountPoint>& event, boolean_t bUnsol = false) override;
                virtual void handle(const CObjHdr* p_header, int16u index, CBinPoint& point) override;
                virtual void handle(const CObjHdr* p_header, int16u index, CDBinPoint& point) override;
                virtual void handle(const CObjHdr* p_header, int16u index, CTimePoint& point) override;
                virtual void handle(const CObjHdr* p_header, int16u index, CDelayPoint& point) override;
                virtual void handle(const CObjHdr* p_header, int16u index, CEvent<CDBinPoint>& event, boolean_t bUnsol = false) override;
                virtual void handle(const CObjHdr* p_header, int16u index, CAnalogPoint& point) override;
                virtual void handle(const CObjHdr* p_header, int16u index, CFrozenAnalogPoint& point) override;
                virtual void handle(const CObjHdr* p_header, int16u index, CEvent<CBinPoint>& event, boolean_t bUnsol = false) override;
                virtual void handle(const CObjHdr* p_header, int16u index, CEvent<CAnalogPoint>& event, boolean_t bUnsol = false) override;
                virtual void operateStatusCROB(const CObjHdr* p_header, int8u status, boolean_t matchReq, boolean_t isSelect) override;
                virtual void operateStatusAOB(const CObjHdr* p_header, int8u status, boolean_t matchReq, boolean_t isSelect) override;
                virtual void notify(DNP3_NOTIF_t errCode, const char* ps_msg);
            };
            
            uint32_t NumBlocks = 0;
            CLIENT_BLOCK_T* Blocks[DNP3_MAX_NUM_BLOCKS];

            /* DNP3 stack object instances */
            DNPClientConfig CommunicationConfig;
            CConnectionTCP *ConnectionObject;
            
            /* Receive callbacks */
            cCallback* CommunicationCallback;

            /* Send function*/
            int32_t readRange(CLIENT_BLOCK_T*);
            int32_t sendCommand1201(CLIENT_BLOCK_T*);
            int32_t sendCommand4100(CLIENT_BLOCK_T*);
            int32_t sendFreeze(CLIENT_BLOCK_T* Block);

        public:
            CMaster* CommunicationObject;

            uint16_t ClientID;
            uint16_t ID;
            uint32_t LocalIpAddr;
            uint16_t LocalTcpPort;
            uint32_t RemoteIpAddr;
            uint16_t RemoteTcpPort;
            uint32_t KeepAlive;
            uint32_t RxTimeout;

            bool IsCom = false;
            void* Parent;

            bool IsFaulty = false;
            uint32_t State = 0;

            void log(Severity l, const char* m, ...);

            int32_t addBlock(CLIENT_BLOCK_T**);
            int32_t assignClass(CLIENT_BLOCK_T* Block);
            int32_t enableUnsolicited(CLIENT_BLOCK_T* Block);
            int32_t poll(CLIENT_BLOCK_T* Block);
            boolean_t isConnected();

            int32_t init(uint32_t LocalIpAddr, uint16_t LocalTcpPort, uint32_t RemoteIpAddr, uint16_t RemoteTcpPort);
            int32_t start();
            int32_t process();
            int32_t terminate();

            cConnection(uint16_t,uint16_t);
            ~cConnection();  // Destructor is called when application is unloaded from target.

    };
    
}

#endif
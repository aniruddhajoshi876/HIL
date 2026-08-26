#ifndef __MBTCP_SERVER_FI_RULE_H
#define __MBTCP_SERVER_FI_RULE_H

#include "stdint.h"
#include "mb_def.h"

namespace modbusTCP
{
    class cServerFiRule
    {
        private:

        public:

        uint32_t ID;
        void *Fi;

        bool Trigger = 0;
        bool Enabled = true;
        uint32_t State;

        uint32_t Action;
        double FirstIpAddr;
        double LastIpAddr;
        double FirstPort;
        double LastPort;

        double FirstUnit;
        double LastUnit;
        double FirstFc;
        double LastFc;
        double FirstIndex;
        double LastIndex;
        double Modifier;

        void log(Severity l, const char *m, ...);
        int32_t init(uint32_t Action,
                     double FirstIpAddr, double LastIpAddr,
                     double FirstPort, double LastPort);
        int32_t init(uint32_t Action, double FirstUnit, double LastUnit, double FirstFc, double LastFc, double FirstIndex, double LastIndex, double Modifier);
        int32_t apply(uint32_t IpAddr, uint32_t Port, bool *Accepted);
        int32_t apply(MB_REQUEST_T *RequestADU, MB_SEND_FRAME_T *TxFrame, bool *DoSend);
        int32_t update(bool *Enabled, double *Modifier);

        cServerFiRule(uint32_t ID);
        ~cServerFiRule();
    };
} //namespace modbusTCP

#endif

#ifndef __MBTCP_SERVER_FI_H
#define __MBTCP_SERVER_FI_H

#include "stdint.h"
#include "mb_def.h"
#include "mbtcp_server_fi_rule.h"

namespace modbusTCP
{
class cServerFi
{
    private:

    public:
    
        uint32_t ID;
        uint32_t Mode;
        bool ShowEnablePort;
        bool ShowModifierPort;
        void *Station;

        /* Vector of fault insertion blocks */
        std::vector<cServerFiRule *> Rules;

        void log(Severity l, const char *m, ...);
        int32_t init(uint32_t Mode, bool ShowEnablePort, bool ShowModifierPort);
        int32_t addRule(cServerFiRule **Rule);
        int32_t applyRules(uint32_t IpAddr, uint32_t Port, bool *Accepted);
        int32_t applyRules(MB_REQUEST_T *RequestADU, MB_SEND_FRAME_T *TxFrame, bool *DoSend);

        cServerFi(uint32_t ID);
        ~cServerFi();
};
} //namespace modbusTCP

#endif

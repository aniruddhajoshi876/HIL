#ifndef __OPCUA_CLIENT_TRANSCEIVER_H
#define __OPCUA_CLIENT_TRANSCEIVER_H

#include <opcua_block.h>
#include <opcua_def.h>
#include <opcua_client_item.h>
#include <stdint.h>
#include <wchar.h>
#include <list>

namespace opcua
{
	class cClientTransceiver : public cBlock
	{
		private:
		public:

			bool ResponsePending = false;
			void *Data = NULL;
			void *NodeId = NULL;
			OPCUA_TRANSCEIVER_PROPS_T *Props = NULL;
			uint8_t Type = OPCUA_BLOCK_TYPE_UNDEF;
			uint32_t SubscriptionId = 0;
			uint32_t MsgStatus = 0;
			uint64_t TimeStamp = 0;

			std::list<cClientItem*> Items;

			int32_t init(uint8_t Type, OPCUA_TRANSCEIVER_PROPS_T *Props);
			int32_t start();
			int32_t process();
			int32_t terminate();

			int32_t addItem(cClientItem **Item);

			cClientTransceiver() {};
			~cClientTransceiver() {};
	};
}


#endif

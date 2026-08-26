#ifndef __OPCUA_CLIENT_ITEM_H
#define __OPCUA_CLIENT_ITEM_H

#include <opcua_block.h>
#include <opcua_def.h>
#include <opcua_client_transceiver.h>
#include <stdint.h>
#include <wchar.h>

namespace opcua
{
	class cClientItem : public cBlock
	{
		private:
		public:

			bool ResponsePending = false;
			void *Data = NULL;
			void *NodeId = NULL;
			OPCUA_NODE_PROPS_T *Props = NULL;
			uint8_t Type = OPCUA_BLOCK_TYPE_UNDEF;
			uint32_t MsgStatus = 0;
			uint64_t TimeStamp = 0;
			void *MonitoredItem;
			void *Transceiver;

			int32_t init(uint8_t Type, OPCUA_NODE_PROPS_T *Props);
			int32_t start();
			int32_t process();
			int32_t terminate();

			cClientItem() {};
			~cClientItem() {};
	};
}


#endif

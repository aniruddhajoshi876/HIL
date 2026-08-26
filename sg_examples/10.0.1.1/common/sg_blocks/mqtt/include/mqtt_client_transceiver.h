#ifndef __MQTT_CLIENT_TRANSCEIVER_H
#define __MQTT_CLIENT_TRANSCEIVER_H

#include <mqtt_def.h>
#include <mqtt_transceiver.h>
#include <stdint.h>
#include <wchar.h>

namespace mqtt
{
	class cClientTransceiver : public cTransceiver
	{
		private:
		public:


			void *Data = NULL;
			void *NodeId = NULL;
			MQTT_NODE_PROPS_T *Props = NULL;
			uint8_t Type = MQTT_BLOCK_TYPE_UNDEF;
			uint32_t MsgStatus = 0;
			uint64_t TimeStamp = 0;
			uint8_t *Buffer = NULL;
			uint32_t MaxDataLen = 0;
			uint32_t DataLen = 0;
			char Topic[USHRT_MAX + 1] = {0};
			uint32_t TopicLen = 0;
			int QoS = 0;
			int Retain = 0;

			int32_t init(uint8_t Type, char *Topic, int QoS, int Retain, uint8_t *Buffer, uint32_t MaxDataLen);
			int32_t start();
			int32_t subscribe();
			int32_t handleMessage(char* topicName, int topicLen, void *m);
			int32_t process();
			int32_t terminate();

			cClientTransceiver() {};
			~cClientTransceiver() {};
	};
}


#endif

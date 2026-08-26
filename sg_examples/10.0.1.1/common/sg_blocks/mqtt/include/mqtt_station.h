#ifndef __MQTT_STATION_H
#define __MQTT_STATION_H

#include <mqtt_base.h>
#include <stdint.h>

namespace mqtt
{
	class cStation : public cBase
	{
		private:

		public:

			uint16_t ID = 0;
			uint8_t Type = 0;

			cStation() {};
			virtual ~cStation() {};
	};
}

#endif


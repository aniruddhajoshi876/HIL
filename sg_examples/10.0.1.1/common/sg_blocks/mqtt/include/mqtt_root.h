#ifndef __MQTT_ROOT_H
#define __MQTT_ROOT_H

#include <mqtt_station.h>
#include <wchar.h>
#include <cstdint>
#include <map>

namespace mqtt
{
    class cRoot : public cBase
    {
		private:

			/* List of client and server stations */
			std::map<uint16_t, cStation*> Stations;

			/* Background thread handle */
			void* MainThread = NULL;

		public:

			bool Run = false;
			bool Stop = false;

			int32_t init();
			int32_t start();
			int32_t process();
			int32_t terminate();
			int32_t stop();

			bool isStation(uint16_t ID);
			int32_t addStation(uint16_t ID, uint8_t Type, cStation** Station);
			int32_t getStation(uint16_t, cStation**);

			cRoot() {};
			~cRoot() {};
    };
}

#endif

#ifndef __MQTT_BASE_H
#define __MQTT_BASE_H

#include <stdint.h>

namespace mqtt
{
    class cBase
    {
		private:
		public:

			bool InitDone = false;
			bool StartDone = false;

			int32_t init() {return 0;};
			virtual int32_t start() = 0;
			virtual int32_t process() = 0;
			virtual int32_t terminate() = 0;

			cBase() {};
			virtual ~cBase() {};
    };
}

#endif

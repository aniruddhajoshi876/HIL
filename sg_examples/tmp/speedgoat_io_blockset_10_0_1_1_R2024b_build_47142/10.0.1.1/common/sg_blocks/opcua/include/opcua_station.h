#ifndef __OPCUA_STATION_H
#define __OPCUA_STATION_H

#include <opcua_base.h>
#include <stdint.h>

namespace opcua
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


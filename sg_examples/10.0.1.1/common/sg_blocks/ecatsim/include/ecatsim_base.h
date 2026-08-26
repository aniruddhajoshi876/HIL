#ifndef __ECATSIM_BASE_H
#define __ECATSIM_BASE_H

#include <stdint.h>

namespace sg_ns_ecatsim
{
    class cBase
    {
		private:
		public:

			uint32_t ID = 0;
			int16_t State = 0;
			bool IsFaulty = false;

			int32_t init() {return 0;};
			virtual int32_t start() = 0;
			virtual int32_t process() = 0;
			virtual int32_t terminate() = 0;

			cBase() {};
			virtual ~cBase() {};
    };
}

#endif

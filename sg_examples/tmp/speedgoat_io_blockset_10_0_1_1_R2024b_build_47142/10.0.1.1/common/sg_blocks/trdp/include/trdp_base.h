#ifndef __TRDP_BASE_H
#define __TRDP_BASE_H

#include <stdint.h>

namespace ns_sg_trdp
{
    class cBase
    {
		private:
		public:

			bool IsFaulty = false;

			uint32_t ID = 0;

			uint32_t State = 0;

			int32_t init() {return 0;};
			virtual int32_t start() = 0;
			virtual int32_t process() = 0;
			virtual int32_t terminate() = 0;

			cBase() {};
			virtual ~cBase() {};
    };
}

#endif

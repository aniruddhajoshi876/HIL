#ifndef __OPCUA_SERVER_NODE_H
#define __OPCUA_SERVER_NODE_H

#include <opcua_base.h>
#include <opcua_def.h>
#include <stdint.h>
#include <wchar.h>
#include <list>

namespace opcua
{
	class cServerNode : public cBase
	{
		private:
		public:

			OPCUA_NODE_PROPS_T *Props = NULL;

			void *Data = NULL;
			void *ParentNode = NULL;
			void *NodeId = NULL;
			void *Station = NULL;

			int32_t init(OPCUA_NODE_PROPS_T *Props);
			int32_t start();
			int32_t process();
			int32_t terminate();

			cServerNode();
			~cServerNode();
	};
}

#endif

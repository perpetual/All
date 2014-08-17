#ifndef HANDLE_BASE_OBJECT_H
#define HANDLE_BASE_OBJECT_H

#include <cstdlib>

namespace Handle
{
	class CBaseObject
	{
	public:
		virtual ~CBaseObject(void) = 0;
		virtual CBaseObject* Copy(void) const { return NULL;}		//如果用于代理则需要实现该方法
	};
}

#endif
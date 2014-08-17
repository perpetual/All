#ifndef HANDLE_OBJECT_SURROGATE_H
#define HANDLE_OBJECT_SURROGATE_H

#include <cstdlib>
#include "BaseObject.h"

namespace Handle
{
	class CSurrogate
	{
	protected:
		CSurrogate(const CBaseObject&);
		CSurrogate(const CSurrogate&);
		CSurrogate& operator =(const CSurrogate&);
		operator bool(void) const {return NULL != this->m_pBaseObject;}
		virtual ~CSurrogate(void) = 0;

		CBaseObject* m_pBaseObject;
	};
}

#endif
#include "Handle/Surrogate.h"

namespace Handle
{
	//带参数的构造函数需要在派生类中有对应的定义
	CSurrogate::CSurrogate(const CBaseObject& obj) : m_pBaseObject(obj.Copy()) {}

	CSurrogate::~CSurrogate(void) {delete this->m_pBaseObject;}

	CSurrogate::CSurrogate(const CSurrogate& obj) : m_pBaseObject(NULL != obj.m_pBaseObject ? obj.m_pBaseObject->Copy() : NULL) {}

	CSurrogate& CSurrogate::operator =(const CSurrogate& obj)
	{
		if (&obj != this)
		{
			delete this->m_pBaseObject;
			this->m_pBaseObject = (NULL != obj.m_pBaseObject ? obj.m_pBaseObject->Copy() : NULL);
		}

		return *this;
	}
}

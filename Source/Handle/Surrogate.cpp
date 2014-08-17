#include "Handle/Surrogate.h"

namespace Handle
{
	//�������Ĺ��캯����Ҫ�����������ж�Ӧ�Ķ���
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

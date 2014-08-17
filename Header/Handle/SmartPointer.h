#ifndef HANDLE_SMART_POINTER_H
#define HANDLE_SMART_POINTER_H

#include "VersionControl.h"
#include "Handle/Handle.h"

namespace Handle
{
	using std::ostream;
	using Utility::exceptionx;

	template <typename T, bool b = false>
	class CSmartPointer : public Handle::CHandle<T, b>
	{
	public:
		//参数只能指向堆地址
		explicit CSmartPointer(T* p = NULL)
		{
			this->m_pBase = p;
		}

		T* operator ->(void) const
		{
			return this->m_pBase;
		}

		T& operator *(void) const
		{
			return *this->m_pBase;
		}

		operator bool(void) const
		{
			return NULL != this->m_pBase;
		}

		unsigned int GetRefCount(void) const
		{
			return this->m_oUseCount;
		}

		bool operator ==(const CSmartPointer& sp) const
		{
			return this->m_pBase == sp.m_pBase;
		}

		bool operator !=(const CSmartPointer& sp) const
		{
			return this->m_pBase != sp.m_pBase;
		}
	};

	//template <typename T, bool b>
	//CSmartPointer<T, b> CSmartPointer<T, b>::NUL = 0;
}

#endif
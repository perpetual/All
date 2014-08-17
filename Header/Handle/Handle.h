#ifndef HANDLE_HANDLE_H
#define HANDLE_HANDLE_H

#include "BaseObject.h"

#ifdef __OS_VERSION_WINDOWS__
#pragma warning(disable:4127)
#elif defined (__OS_VERSION_LINUX__)
#endif

namespace Handle
{
	//派生类负责为基类指针分配空间且不需要在派生类的析构函数中释放
	//模板的第二个参数表示是否指向对象数组
	template <typename T, bool>
	class CHandle
	{
		//判断引用计数时要使用指针，不能直接用对象复制，否则会改变引用计数
		class CUseCount
		{
		public:
			CUseCount(void) : m_puiCount(new unsigned int(1)) {}
			CUseCount(const CUseCount& obj) : m_puiCount(obj.m_puiCount) {++*this->m_puiCount;}
			CUseCount& operator =(const CUseCount& obj);
			~CUseCount(void)
			{
				if (0 == --*this->m_puiCount)
				{
					delete this->m_puiCount;
				}
			}
			bool IsOnly(void) const {return 1 == *this->m_puiCount;}
			bool MakeOnly(void)
			{
				if (1 == *this->m_puiCount)
				{
					return false;
				}
				else
				{
					--*this->m_puiCount;
					this->m_puiCount = new unsigned int(1);
					return true;
				}
			}

			bool Reattach(const CUseCount& oUseCount)
			{
				++*oUseCount.m_puiCount;
				if (0 == --*this->m_puiCount)
				{
					delete this->m_puiCount;
					this->m_puiCount = oUseCount.m_puiCount;
					return true;
				}
				else
				{
					this->m_puiCount = oUseCount.m_puiCount;
					return false;
				}
			}

			CUseCount& operator ++(void) {++*this->m_puiCount; return *this;}

			CUseCount& operator --(void) {--*this->m_puiCount; return *this;}

			operator unsigned int(void) const {return *this->m_puiCount;}

		private:
			unsigned int* m_puiCount;	//采用指针也是为了保证复制多个对象共用一个计数器
		};
	protected:
		CHandle(void);
		CHandle(const CHandle&);
		CHandle& operator =(const CHandle&);
		virtual ~CHandle(void) = 0;

		T* m_pBase;
		CUseCount m_oUseCount;
	};

	template <typename T, bool b>
	CHandle<T, b>::CHandle(void) : m_pBase(NULL) {}

	template <typename T, bool b>
	CHandle<T, b>::CHandle(const CHandle& h) : m_pBase(h.m_pBase), m_oUseCount(h.m_oUseCount) {}

	template <typename T, bool b>
	CHandle<T, b>& CHandle<T, b>::operator =(const CHandle<T, b>& h)
	{
		T* pTemp = this->m_pBase;
		this->m_pBase = h.m_pBase;

		if (this->m_oUseCount.Reattach(h.m_oUseCount))
		{
			delete pTemp;
		}
		return *this;
	}

	template <typename T, bool b>
	CHandle<T, b>::~CHandle(void)
	{
		if (this->m_oUseCount.IsOnly())
		{
			if (b)
			{
				delete[] this->m_pBase;
			}
			else
			{
				delete this->m_pBase;
			}
			this->m_pBase = NULL;
		}
	}

}

#endif
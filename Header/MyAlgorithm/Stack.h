#ifndef MYALGORITHM_STACK_H
#define MYALGORITHM_STACK_H

#include <cassert>
#include "Nodes.h"

namespace MyAlgorithm
{
	//Êý×é¶ÑÕ»
	template <typename T, size_t sz>
	class CArrayStack
	{
	public:
		CArrayStack(void) :
		  m_uiCount(0)
		  {}
		void Push(const T&);
		void Pop(void);
		T Top(void) const;
		bool IsEmpty(void) const;
		bool IsFull(void) const;
		void Clear(void);

	private:
		unsigned int m_uiCount;
		T m_tArray[sz];
	};

	template <typename T, size_t sz>
	void CArrayStack<T, sz>::Push(const T& t)
	{
		assert(!this->IsFull());
		this->m_tArray[this->m_uiCount++] = t;
	}

	template <typename T, size_t sz>
	void CArrayStack<T, sz>::Pop(void)
	{
		assert(!this->IsEmpty());
		--this->m_uiCount;
	}

	template <typename T, size_t sz>
	T CArrayStack<T, sz>::Top(void) const
	{
		assert(!this->IsEmpty());
		return this->m_tArray[this->m_uiCount - 1];
	}

	template <typename T, size_t sz>
	bool CArrayStack<T, sz>::IsEmpty(void) const
	{
		return 0 == this->m_uiCount;
	}

	template <typename T, size_t sz>
	bool CArrayStack<T, sz>::IsFull(void) const
	{
		return sz == this->m_uiCount;
	}

	template <typename T, size_t sz>
	void CArrayStack<T, sz>::Clear(void)
	{
		while (!this->IsEmpty())
		{
			this->Pop();
		}
	}
}

namespace MyAlgorithm
{
	template <typename T>
	class CLinkStack
	{
	public:
		CLinkStack(void);
		~CLinkStack(void);

		void Push(const T&);
		T Pop(void);
		T Top(void) const;
		bool IsEmpty(void) const;
		bool IsFull(void) const
		{
			return false;
		}
		void Clear(void);

	private:
		CSmartPointer<CSLLNode<T> > m_pRoot;
	};

	template <typename T>
	CLinkStack<T>::CLinkStack(void) :
		m_pRoot(NULL)
	{}

	template <typename T>
	CLinkStack<T>::~CLinkStack(void)
	{
		while (!this->IsEmpty())
		{
			this->Pop();
		}
	}

	template <typename T>
	void CLinkStack<T>::Push(const T& t)
	{
		CSmartPointer<CSLLNode<T> > pNew(new CSLLNode<T>(t));

		pNew->m_spNext = this->m_pRoot;
		this->m_pRoot = pNew;
	}

	template <typename T>
	T CLinkStack<T>::Pop(void)
	{
		assert(this->m_pRoot);
		CSmartPointer<CSLLNode<T> > pTemp = this->m_pRoot;
		this->m_pRoot = this->m_pRoot->m_spNext;
		return *pTemp;
	}

	template <typename T>
	T CLinkStack<T>::Top(void) const
	{
		assert(!this->IsEmpty());
		return *this->m_pRoot;
	}

	template <typename T>
	bool CLinkStack<T>::IsEmpty(void) const
	{
		return !this->m_pRoot;
	}

	template <typename T>
	void CLinkStack<T>::Clear(void)
	{
		while (!this->IsEmpty())
		{
			this->Pop();
		}
	}
}

#endif
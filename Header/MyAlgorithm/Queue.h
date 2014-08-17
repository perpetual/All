#ifndef MYALGORITHM_QUEUE_H
#define MYALGORITHM_QUEUE_H

#include <cassert>
#include "Handle/SmartPointer.h"

namespace MyAlgorithm
{
	using Handle::CSmartPointer;

	//数组队列
	template <typename T, size_t sz>
	class CArrayQueue
	{
	public:
		CArrayQueue(void) :
		  m_szFront(1),
		  m_szRear(0)
		{}
		bool IsEmpty(void) const;
		bool IsFull(void) const;
		void Push(const T&);
		void Pop(void);
		T Front(void) const;
		size_t GetSize(void) const;
	private:
		T m_array[sz + 1];
		size_t m_szFront;
		size_t m_szRear;
	};

	template <typename T, size_t sz>
	bool CArrayQueue<T, sz>::IsEmpty(void) const
	{
		return (this->m_szRear + 1) % (sz + 1) == this->m_szFront;
	}

	template <typename T, size_t sz>
	bool CArrayQueue<T, sz>::IsFull(void) const
	{
		return (this->m_szRear + 2) % (sz + 1) == this->m_szFront;
	}


	template <typename T, size_t sz>
	void CArrayQueue<T, sz>::Push(const T& t)
	{
		assert(!this->IsFull());
		this->m_szRear = ++this->m_szRear % (sz + 1);
		this->m_array[this->m_szRear] = t;
	}

	template <typename T, size_t sz>
	void CArrayQueue<T, sz>::Pop(void)
	{
		assert(!this->IsEmpty());
		this->m_szFront = ++this->m_szFront % (sz + 1);
	}

	template <typename T, size_t sz>
	T CArrayQueue<T, sz>::Front(void) const
	{
		assert(!this->IsEmpty());
		return this->m_array[this->m_szFront];
	}

	template<typename T, size_t sz>
	size_t CArrayQueue<T, sz>::GetSize(void) const
	{
		return (this->m_szRear - this->m_szFront + sz + 2) % (sz + 1);
	}
}

namespace MyAlgorithm
{
	//链式队列
	template <typename T>
	class CLinkedQueue
	{
	public:
		CLinkedQueue(void);
		~CLinkedQueue(void);

		bool IsEmpty(void) const;
		void Push(const T&);
		void Pop(void);
		T Front(void) const;
	private:
		CSmartPointer<CSLLNode<T> > m_pFront;
		CSmartPointer<CSLLNode<T> > m_pRear;
	};

	template <typename T>
	CLinkedQueue<T>::CLinkedQueue(void) :
		m_pFront(NULL),
		m_pRear(NULL)
	{}

	template <typename T>
	CLinkedQueue<T>::~CLinkedQueue(void)
	{
		while (!this->IsEmpty())
		{
			this->Pop();
		}
	}

	template <typename T>
	bool CLinkedQueue<T>::IsEmpty(void) const
	{
		return NULL == this->m_pFront && NULL == this->m_pRear;
	}

	template<typename T>
	void CLinkedQueue<T>::Push(const T& t)
	{
		CSmartPointer<CSLLNode<T> > pNew(new CSLLNode<T>(t));

		//*pNew = t;
		if (NULL == this->m_pRear)
		{
			this->m_pRear = pNew;
		}
		else
		{
			this->m_pRear->m_spNext = pNew;
			this->m_pRear = pNew;
		}

		if (NULL == this->m_pFront)
		{
			this->m_pFront = pNew;
		}
	}

	template <typename T>
	void CLinkedQueue<T>::Pop(void)
	{
		assert(!this->IsEmpty());

		CSmartPointer<CSLLNode<T> > pTemp(this->m_pFront);		//重新绑定，超出生命周期后析构
		this->m_pFront = this->m_pFront->m_spNext;
		if (NULL == this->m_pFront)
		{
			this->m_pRear = CSmartPointer<CSLLNode<T> >(NULL);
		}
	}

	template <typename T>
	T CLinkedQueue<T>::Front(void) const
	{
		assert(!this->IsEmpty());
		return *this->m_pFront;
	}
}

#endif
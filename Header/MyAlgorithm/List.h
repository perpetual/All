#ifndef MYALGORITHM_LIST_H
#define MYALGORITHM_LIST_H

#include "Nodes.h"

namespace MyAlgorithm
{
	using Handle::CSmartPointer;

	//双向链表
	template <typename T>
	class CDLList
	{
	public:
		CDLList(void);
		~CDLList(void);

		//参数标记是否为逆向打印
		void Display(bool = false) const;

		//插入节点
		bool InsertAt(int, const T&);

		//获取链表长度
		size_t GetLength(void) const;

		//删除节点
		void Remove(const T&);

	private:
		CSmartPointer<CDLLNode<T> > m_spRoot;			//根节点
	};

	template <typename T>
	CDLList<T>::CDLList(void) :
	m_spRoot(NULL)
	{}

	template <typename T>
	CDLList<T>::~CDLList(void)
	{
		CSmartPointer<CDLLNode<T> >* psp = &this->m_spRoot;
		while (*psp)
		{
			(*psp)->m_pPrev = CSmartPointer<CDLLNode<T> >(NULL);
			psp = &(*psp)->m_pNext;
		}
	}

	template <typename T>
	void CDLList<T>::Display(bool bConverse) const
	{
		CSmartPointer<CDLLNode<T> > p = this->m_spRoot;
		while (bConverse && p && p->m_pNext)
		{
			p = p->m_pNext;
		}

		while (p)
		{
			cout << (*p) << ends;
			!bConverse ? p = p->m_pNext : p = p->m_pPrev;
		}
		cout << endl;
	}

	template <typename T>
	bool CDLList<T>::InsertAt(int iIndex, const T& t)
	{
		CSmartPointer<CDLLNode<T> >* pspCur = &this->m_spRoot;
		CSmartPointer<CDLLNode<T> > spPrev;

		while (*pspCur && iIndex-- > 0)
		{
			spPrev = *pspCur;
			pspCur = &(*pspCur)->m_pNext;
		}

		if (iIndex <= 0)
		{
			CSmartPointer<CDLLNode<T> > spNew(new CDLLNode<T>(t));

			spNew->m_pNext = (*pspCur);
			if (!*pspCur)		//如果在尾部插入
			{
				spNew->m_pPrev = spPrev;
			}
			else
			{
				if (this->m_spRoot != *pspCur)		//如果不在表头插入
				{
					spNew->m_pPrev = (*pspCur)->m_pPrev;
				}
			}
			if (*pspCur)
			{
				(*pspCur)->m_pPrev = spNew;
			}
			(*pspCur) = spNew;

			return true;
		}
		else
		{
			return false;
		}
	}

	template <typename T>
	size_t CDLList<T>::GetLength(void) const
	{
		size_t sz = 0;
		CSmartPointer<CDLLNode<T> > sp = this->m_spRoot;
		while (sp)
		{
			++sz;
			sp = sp->m_pNext;
		}
		return sz;
	}

	template <typename T>
	void CDLList<T>::Remove(const T& t)
	{
		CSmartPointer<CDLLNode<T> > sp = this->m_spRoot;

		while (sp && *sp != t)
		{
			sp = sp->m_pNext;
		}

		if (sp)
		{
			sp->m_pPrev->m_pNext = sp->m_pNext;
			sp->m_pNext->m_pPrev = sp->m_pPrev;
			this->Remove(t);
		}
	}
}

namespace MyAlgorithm
{
	//双向循环链表
	template <typename T>
	class CDLLList
	{
	public:
		CDLLList(void);
		~CDLLList(void);

		//参数标记是否为逆向打印
		void Display(bool = false) const;

		//插入节点
		bool Insert(const T&);

		//删除节点
		void Remove(const T&);

	private:
		CSmartPointer<CDLLNode<T> > m_pRoot;			//根节点
	};

	template <typename T>
	CDLLList<T>::CDLLList(void) :
	m_pRoot(NULL)
	{}

	template <typename T>
	CDLLList<T>::~CDLLList(void)
	{
		CSmartPointer<CDLLNode<T> > spNull;
		if (this->m_pRoot)
		{
			//先改造成双向非循环链表
			this->m_pRoot->m_pPrev->m_pNext = spNull;
			this->m_pRoot->m_pPrev = spNull;

			CSmartPointer<CDLLNode<T> > spTemp = this->m_pRoot;

			//转换为单向链表
			while (spTemp->m_pNext != spNull)
			{
				spTemp->m_pNext->m_pPrev = spNull;
				spTemp = spTemp->m_pNext;
			}
		}
	}

	template <typename T>
	void CDLLList<T>::Display(bool bConverse) const
	{
		CSmartPointer<CDLLNode<T> > p = !bConverse ? this->m_pRoot : this->m_pRoot ? this->m_pRoot->m_pPrev : this->m_pRoot;

		if (p)
		{
			do
			{
				cout << (*p) << ends;
				!bConverse ? p = p->m_pNext : p = p->m_pPrev;
			}while (!bConverse ? this->m_pRoot != p : this->m_pRoot->m_pPrev != p);
		}
		cout << endl;
	}

	template <typename T>
	bool CDLLList<T>::Insert(const T& t)
	{
		CSmartPointer<CDLLNode<T> >* pPointer = &this->m_pRoot;

		//查找正确的插入位置
		if (*pPointer)
		{
			do
			{
				pPointer = &(*pPointer)->m_pNext;
			}while (&(**pPointer) != &(*this->m_pRoot)/* && **pPointer <= t*/);
		}

		CSmartPointer<CDLLNode<T> > pNew(new CDLLNode<T>(t));
		if (NULL == pNew)
		{
			return false;
		}
		else
		{
			if (!*pPointer)		//如果是根节点
			{
				this->m_pRoot = pNew;
				this->m_pRoot->m_pNext = this->m_pRoot;
				this->m_pRoot->m_pPrev = this->m_pRoot;
			}
			else
			{
				pNew->m_pNext = *pPointer;
				pNew->m_pPrev = (*pPointer)->m_pPrev;
				(*pPointer)->m_pPrev = pNew;
				*pPointer = pNew;
			}
		}

		return true;
	}

	template <typename T>
	void CDLLList<T>::Remove(const T& t)
	{
		if (this->m_pRoot == this->m_pRoot->m_pNext)		//如果只有一个节点
		{
			if (t == *this->m_pRoot)
			{
				this->m_pRoot->m_pNext = CSmartPointer<CDLLNode<T> >(NULL);
				this->m_pRoot->m_pPrev = CSmartPointer<CDLLNode<T> >(NULL);
				this->m_pRoot = CSmartPointer<CDLLNode<T> >(NULL);
			}
		}
		else		//否则，有多个节点
		{
			CSmartPointer<CDLLNode<T> > spPointer = this->m_pRoot->m_pNext;

			//查找指定的点
			if (spPointer)
			{
				while (this->m_pRoot != spPointer && *spPointer != t)
				{
					spPointer = spPointer->m_pNext;
				}

				if (this->m_pRoot == spPointer)		//如果是第一个节点
				{
					if (*spPointer == t)
					{
						this->m_pRoot = this->m_pRoot->m_pNext;
					}
					else
					{
						return;
					}
				}
				spPointer->m_pNext->m_pPrev = spPointer->m_pPrev;
				spPointer->m_pPrev->m_pNext = spPointer->m_pNext;
				this->Remove(t);
			}
		}
	}
}

namespace MyAlgorithm
{
	//单链表
	template <typename T>
	class CSLList
	{
	public:
		CSLList(void);

		//在链表的头部添加节点
		virtual bool AddHead(const T&);

		//在链表的尾部添加节点
		virtual bool AddTail(const T&);

		//获取表头元素
		T GetHead(void) const;

		//查找某个节点
		T* Find(const T&);

		//在制定位置添加节点
		virtual bool InsertAt(int, const T&);

		//将单链表反序
		virtual void Reverse(void);

		//根据值删除所有匹配节点
		bool Remove(const T&);

		//判断链表是否为空
		operator bool(void) const;

		//打印链表
		virtual void Display(void) const;
	protected:
		CSmartPointer<CSLLNode<T> > m_pRoot;			//根指针
	};

	template<typename T>
	CSLList<T>::CSLList(void) :
	m_pRoot(NULL)
	{}

	template <typename T>
	bool CSLList<T>::AddHead(const T& t)
	{
		CSmartPointer<CSLLNode<T> > spNew(new CSLLNode<T>(t));
		if (spNew)
		{
			spNew->m_spNext = this->m_pRoot;
			this->m_pRoot = spNew;
			return true;
		}
		else
		{
			return false;
		}
	}

	template <typename T>
	bool CSLList<T>::AddTail(const T& t)
	{
		CSmartPointer<CSLLNode<T> >* spPointer = &this->m_pRoot;		//指向某个节点指针的指针，作用相当于指向某个节点指针的引用

		//将指针移动到末尾
		while (NULL != *spPointer)
		{
			spPointer = &(*spPointer)->m_spNext;
		}

		CSmartPointer<CSLLNode<T> > spNew(new CSLLNode<T>(t));
		if (NULL != spNew)
		{
			spNew->m_spNext = *spPointer;
			*spPointer = spNew;
			return true;
		}
		else
		{
			return false;
		}
	}

	template <typename T>
	T CSLList<T>::GetHead() const
	{
		if (this->m_pRoot)
		{
			return *this->m_pRoot;
		}
		else
		{
			throw exceptionx("Out of bounds");
		}
	}

	template <typename T>
	T* CSLList<T>::Find(const T& t)
	{
		CSmartPointer<CSLLNode<T> > sp = this->m_pRoot;

		while (sp && t != *sp)
		{
			sp = sp->m_spNext;
		}

		return sp ? &static_cast<T&>(*sp) : NULL;
	}

	template <typename T>
	bool CSLList<T>::InsertAt(int iIndex, const T& t)
	{
		CSmartPointer<CSLLNode<T> >* spPointer = &this->m_pRoot;

		while (NULL != *spPointer && iIndex-- > 0)
		{
			spPointer = &(*spPointer)->m_spNext;
		}

		if (iIndex <= 0)
		{
			CSmartPointer<CSLLNode<T> > spNew(new CSLLNode<T>(t));
			spNew->m_spNext = (*spPointer);
			(*spPointer) = spNew;
			return true;
		}
		else
		{
			return false;
		}
	}

	template <typename T>
	void CSLList<T>::Reverse()
	{
		CSmartPointer<CSLLNode<T> > pCur = this->m_pRoot;
		CSmartPointer<CSLLNode<T> > pPre;
		CSmartPointer<CSLLNode<T> > pNext;

		while (NULL != pCur)
		{
			pNext = pCur->m_spNext;
			pCur->m_spNext = pPre;
			pPre = pCur;
			pCur = pNext;
		}
		this->m_pRoot = pPre;
	}

	template <typename T>
	bool CSLList<T>::Remove(const T& t)
	{
		CSmartPointer<CSLLNode<T> >* ppCur = &this->m_pRoot;

		//找到对应的点
		while (NULL != *ppCur && (t != **ppCur))
		{
			ppCur = &(*ppCur)->m_spNext;
		}

		if (NULL != *ppCur)
		{
			*ppCur = (*ppCur)->m_spNext;
			this->Remove(t);

			return true;
		}
		else
		{
			return false;
		}
	}

	template <typename T>
	CSLList<T>::operator bool(void) const
	{
		return this->m_pRoot;
	}

	template <typename T>
	void CSLList<T>::Display(void) const
	{
		CSmartPointer<CSLLNode<T> > p = this->m_pRoot;

		while (NULL != p)
		{
			cout << (*p) << ends;
			p = p->m_spNext;
		}
		cout << endl;
	}
}

namespace MyAlgorithm
{
	//有序的单链表
	template <typename T>
	class CSortSLList : public CSLList<T>
	{
	public:
		//优化的有序单链表插入操作
		bool Insert(const T&);
	};

	template <typename T>
	bool CSortSLList<T>::Insert(const T& t)
	{
		CSmartPointer<CSLLNode<T> >* pPointer = &this->m_pRoot;		//指向某个节点指针的指针，作用相当于指向某个节点指针的引用

		while (NULL != *pPointer && **pPointer < t)
		{
			pPointer = &(*pPointer)->m_spNext;
		}

		CSmartPointer<CSLLNode<T> > pNew(new CSLLNode<T>(t));
		if (NULL == pNew)
		{
			return false;
		}
		else
		{
			pNew->m_spNext = *pPointer;
			*pPointer = pNew;
			return true;
		}
	}
}

#endif
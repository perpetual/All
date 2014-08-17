#ifndef MYALGORITHM_LIST_H
#define MYALGORITHM_LIST_H

#include "Nodes.h"

namespace MyAlgorithm
{
	using Handle::CSmartPointer;

	//˫������
	template <typename T>
	class CDLList
	{
	public:
		CDLList(void);
		~CDLList(void);

		//��������Ƿ�Ϊ�����ӡ
		void Display(bool = false) const;

		//����ڵ�
		bool InsertAt(int, const T&);

		//��ȡ������
		size_t GetLength(void) const;

		//ɾ���ڵ�
		void Remove(const T&);

	private:
		CSmartPointer<CDLLNode<T> > m_spRoot;			//���ڵ�
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
			if (!*pspCur)		//�����β������
			{
				spNew->m_pPrev = spPrev;
			}
			else
			{
				if (this->m_spRoot != *pspCur)		//������ڱ�ͷ����
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
	//˫��ѭ������
	template <typename T>
	class CDLLList
	{
	public:
		CDLLList(void);
		~CDLLList(void);

		//��������Ƿ�Ϊ�����ӡ
		void Display(bool = false) const;

		//����ڵ�
		bool Insert(const T&);

		//ɾ���ڵ�
		void Remove(const T&);

	private:
		CSmartPointer<CDLLNode<T> > m_pRoot;			//���ڵ�
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
			//�ȸ����˫���ѭ������
			this->m_pRoot->m_pPrev->m_pNext = spNull;
			this->m_pRoot->m_pPrev = spNull;

			CSmartPointer<CDLLNode<T> > spTemp = this->m_pRoot;

			//ת��Ϊ��������
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

		//������ȷ�Ĳ���λ��
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
			if (!*pPointer)		//����Ǹ��ڵ�
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
		if (this->m_pRoot == this->m_pRoot->m_pNext)		//���ֻ��һ���ڵ�
		{
			if (t == *this->m_pRoot)
			{
				this->m_pRoot->m_pNext = CSmartPointer<CDLLNode<T> >(NULL);
				this->m_pRoot->m_pPrev = CSmartPointer<CDLLNode<T> >(NULL);
				this->m_pRoot = CSmartPointer<CDLLNode<T> >(NULL);
			}
		}
		else		//�����ж���ڵ�
		{
			CSmartPointer<CDLLNode<T> > spPointer = this->m_pRoot->m_pNext;

			//����ָ���ĵ�
			if (spPointer)
			{
				while (this->m_pRoot != spPointer && *spPointer != t)
				{
					spPointer = spPointer->m_pNext;
				}

				if (this->m_pRoot == spPointer)		//����ǵ�һ���ڵ�
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
	//������
	template <typename T>
	class CSLList
	{
	public:
		CSLList(void);

		//�������ͷ����ӽڵ�
		virtual bool AddHead(const T&);

		//�������β����ӽڵ�
		virtual bool AddTail(const T&);

		//��ȡ��ͷԪ��
		T GetHead(void) const;

		//����ĳ���ڵ�
		T* Find(const T&);

		//���ƶ�λ����ӽڵ�
		virtual bool InsertAt(int, const T&);

		//����������
		virtual void Reverse(void);

		//����ֵɾ������ƥ��ڵ�
		bool Remove(const T&);

		//�ж������Ƿ�Ϊ��
		operator bool(void) const;

		//��ӡ����
		virtual void Display(void) const;
	protected:
		CSmartPointer<CSLLNode<T> > m_pRoot;			//��ָ��
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
		CSmartPointer<CSLLNode<T> >* spPointer = &this->m_pRoot;		//ָ��ĳ���ڵ�ָ���ָ�룬�����൱��ָ��ĳ���ڵ�ָ�������

		//��ָ���ƶ���ĩβ
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

		//�ҵ���Ӧ�ĵ�
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
	//����ĵ�����
	template <typename T>
	class CSortSLList : public CSLList<T>
	{
	public:
		//�Ż�����������������
		bool Insert(const T&);
	};

	template <typename T>
	bool CSortSLList<T>::Insert(const T& t)
	{
		CSmartPointer<CSLLNode<T> >* pPointer = &this->m_pRoot;		//ָ��ĳ���ڵ�ָ���ָ�룬�����൱��ָ��ĳ���ڵ�ָ�������

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
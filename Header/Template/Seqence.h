#ifndef TEMPLATE_SEQUENCE_H
#define TEMPLATE_SEQUENCE_H

#include "MyAlgorithm/SLList.h"
#include "Handle/SmartPointer.h"

namespace Template
{
	using MyAlgorithm::CSLList;
	using MyAlgorithm::CSLLNode;
	using Handle::CSmartPointer;
	using Utility::exceptionx;

	template <typename T>
	class CSeqence : public CSLList<T>
	{
	public:
		CSeqence(void) {}
		//���Ѿ��е����������ͷ��
		CSeqence(const T&, CSeqence&);

		void Test(void)
		{
			CSmartPointer<CSLLNode<T> >* sp = &this->m_pRoot;
			cout << '[';
			while (*sp)
			{
				cout << (*sp).GetRefCount() << ends;
				sp = &(*sp)->m_spNext;
			}
			cout << ']' << endl;
		}

		//��ȡ��β
		CSeqence<T> GetTail(void) const;

		//��ȡ��ĳ���
		size_t GetLength(void) const;

		//��ת����
		void Reverse(void);

	private:
		CSeqence(CSmartPointer<CSLLNode<T> >&);
	};

	template <typename T>
	CSeqence<T>::CSeqence(const T& t, CSeqence& oSeq)
	{
		this->m_pRoot = oSeq.m_pRoot;
		this->AddHead(t);
	}

	template <typename T>
	CSeqence<T>::CSeqence(CSmartPointer<CSLLNode<T> >& oSLLNode)
	{
		this->m_pRoot = oSLLNode;
	}

	template <typename T>
	CSeqence<T> CSeqence<T>::GetTail(void) const
	{
		if (this->m_pRoot)
		{
			return CSeqence(this->m_pRoot->m_spNext);
		}
		else
		{
			return CSeqence();
		}
	}

	template <typename T>
	size_t CSeqence<T>::GetLength(void) const
	{
		CSeqence<T> oSeq(*this);
		size_t szLen = 0;
		while (oSeq)
		{
			++szLen;
			oSeq = oSeq.GetTail();
		}
		return szLen;
	}

	template <typename T>
	void CSeqence<T>::Reverse(void)
	{
		CSmartPointer<CSLLNode<T> >* psp = &this->m_pRoot;
		while (*psp && 1 == (*psp).GetRefCount())		//�ҵ���һ�����ü�����Ϊ1�Ľڵ�
		{
			psp = &(*psp)->m_spNext;
		}

		if (*psp)
		{
			CSmartPointer<CSLLNode<T> > pspOld = (*psp);
			(*psp) = CSmartPointer<CSLLNode<T> >(NULL);		//�Ͽ����ü�����Ϊ1�Ľڵ�֮���β��
			while (pspOld)		//�����µ�β��
			{
				this->AddTail(*pspOld);
				pspOld = pspOld->m_spNext;
			}
		}
		CSLList::Reverse();
	}
}

#endif
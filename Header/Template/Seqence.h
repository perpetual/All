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
		//在已经有的序列上添加头部
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

		//获取表尾
		CSeqence<T> GetTail(void) const;

		//获取表的长度
		size_t GetLength(void) const;

		//反转链表
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
		while (*psp && 1 == (*psp).GetRefCount())		//找到第一个引用计数不为1的节点
		{
			psp = &(*psp)->m_spNext;
		}

		if (*psp)
		{
			CSmartPointer<CSLLNode<T> > pspOld = (*psp);
			(*psp) = CSmartPointer<CSLLNode<T> >(NULL);		//断开引用计数不为1的节点之后的尾链
			while (pspOld)		//构造新的尾链
			{
				this->AddTail(*pspOld);
				pspOld = pspOld->m_spNext;
			}
		}
		CSLList::Reverse();
	}
}

#endif
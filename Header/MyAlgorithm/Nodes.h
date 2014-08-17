#ifndef MYALGORITHM_NODES_H
#define MYALGORITHM_NODES_H

#include "VersionControl.h"
#include <iostream>
#include <vector>
#include "Handle/Handle.h"
#include "Handle/SmartPointer.h"

namespace MyAlgorithm
{
	using std::ostream;
	using std::vector;
	using Handle::CHandle;
	using Handle::CSmartPointer;
	using Utility::exceptionx;

	//�������TΪ�ṹ�壬Ӧ�����ع�ϵ�����
	//����Ľڵ�
	template <typename T>
	class CNode : public CHandle<T, false>
	{
	public:
		CNode(const T& t)
		{
			if (NULL == (this->m_pBase = new T(t)))
			{
				throw exceptionx("Allocate new node failed");
			}
		}

		operator T&(void) const
		{
			return *this->m_pBase;
		}
	};

	//��������Ľڵ�
	template<typename T>
	class CSLLNode : public CNode<T>
	{
	public:
		CSLLNode(const T& t) :
			CNode<T>(t)
		{}

		CSmartPointer<CSLLNode<T> > m_spNext;
	};

	//˫������Ľڵ�
	template <typename T>
	class CDLLNode : public CNode<T>
	{
	public:
		CDLLNode(const T& t) :
			CNode<T>(t)
		{}

		CSmartPointer<CDLLNode<T> > m_spNext;
		CSmartPointer<CDLLNode<T> > m_spPrev;
	};

	/////////////////////////////ƽ��������Ľڵ�/////////////////////////////////////////////
	template <typename T>
	class CBSTreeNode : public CNode<T>
	{
	public:
		CBSTreeNode(const T& t) :
			CNode<T>(t),
			m_iBF(0)
		{}

		CSmartPointer<CBSTreeNode<T> > m_spLeft;
		CSmartPointer<CBSTreeNode<T> > m_spRight;
		int m_iBF;			//ƽ������
	};

	////////////////////////////B-���Ľڵ�/////////////////////////////////
	template <typename T>
	class CBMinusTreeNode;

	template <typename T>
	class CPair
	{
	public:
		CPair(const T& t) :
		  m_t(t)
		{}

		bool operator <(const CPair& pr) const
		{
			return this->m_t < pr.m_t;
		}

		bool operator ==(const CPair& pr) const
		{
			return this->m_t == pr.m_t;
		}

		T m_t;
		CSmartPointer<CBMinusTreeNode<T> > m_sp;
	};

	template <typename T>
	class CBMinusTreeNode
	{
	public:
	    vector<CPair<T> > m_vec;
	};

	//////////////////////////////////////////////////////////////////////////
	template<typename T>
	ostream& operator <<(ostream& o, const CNode<T>& oNode)
	{
		return o << static_cast<T>(oNode);
	}
}


#endif
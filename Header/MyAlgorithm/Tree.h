#ifndef MYALGORITHM_TREE_H
#define MYALGORITHM_TREE_H

#include <vector>
#include <queue>
#include <cstring>
#include "Nodes.h"
#include "Queue.h"
#include "Handle/SmartPointer.h"

namespace MyAlgorithm
{
	template <typename T>
	class CBTree
	{
	public:
		//前序遍历
		virtual vector<T> PreOrder(void) const = 0;

		//中序遍历
		virtual vector<T> InOrder(void) const = 0;
		//反中序遍历
		virtual vector<T> ReInOrder(void) const = 0;

		//后序遍历
		virtual vector<T> PostOrder(void) const = 0;

		//层次遍历
		virtual vector<T> BreadthFirst(void) const = 0;

		//插入节点，返回值表示是否插入成功
		virtual bool Insert(const T&) = 0;

		//查找节点
		virtual T* FindNode(const T&) = 0;

		//删除节点
		virtual bool Remove(const T&) = 0;
	};
}

namespace MyAlgorithm
{
	using std::vector;
	using std::queue;
	using MyAlgorithm::CBSTreeNode;
	using Handle::CSmartPointer;

	//二叉树搜索树
	template<typename	T>
	class CLinkedBSTree : public CBTree<T>
	{
	public:
		CLinkedBSTree(void) {}
		//前序遍历
		vector<T> PreOrder(void) const;

		//中序遍历
		vector<T> InOrder(void) const;
		//反中序遍历
		vector<T> ReInOrder(void) const;

		//后序遍历
		vector<T> PostOrder(void) const;

		//层次遍历
		vector<T> BreadthFirst(void) const;

		//插入节点，返回值表示是否插入成功
		bool Insert(const T&);

		//查找节点
		T* FindNode(const T&);

		//删除节点
		bool Remove(const T&);

	protected:
		CSmartPointer<CBSTreeNode<T> > m_pRoot;					//根节点

	private:
		//前序遍历
		void PreOrder(const CSmartPointer<CBSTreeNode<T> >& spNode, vector<T>&) const;

		//中序遍历
		void InOrder(const CSmartPointer<CBSTreeNode<T> >& spNode, vector<T>&) const;
		//反中序遍历
		void ReInOrder(const CSmartPointer<CBSTreeNode<T> >& spNode, vector<T>&) const;

		//后序遍历
		void PostOrder(const CSmartPointer<CBSTreeNode<T> >& spNode, vector<T>&) const;

		//递归插入节点
		bool Insert(CSmartPointer<CBSTreeNode<T> >&, const T&);

		//查找节点
		//返回指向该节点指针的引用
		CSmartPointer<CBSTreeNode<T> >& FindNode(CSmartPointer<CBSTreeNode<T> >& spNode, const T&) const;

		//禁止复制和赋值
		CLinkedBSTree(const CLinkedBSTree&);
		CLinkedBSTree& operator=(const CLinkedBSTree&);

	};

	template <typename T>
	bool CLinkedBSTree<T>::Insert(const T& t)
	{
		return this->Insert(this->m_pRoot, t);
	}

	template<typename T>
	vector<T> CLinkedBSTree<T>::PreOrder(void) const
	{
		vector<T> vec;
		this->PreOrder(this->m_pRoot, vec);
		return vec;
	}

	template<typename T>
	vector<T> CLinkedBSTree<T>::InOrder(void) const
	{
		vector<T> vec;
		this->InOrder(this->m_pRoot, vec);
		return vec;
	}

	template<typename T>
	vector<T> CLinkedBSTree<T>::ReInOrder(void) const
	{
		vector<T> vec;
		this->ReInOrder(this->m_pRoot, vec);
		return vec;
	}

	template<typename T>
	vector<T> CLinkedBSTree<T>::PostOrder(void) const
	{
		vector<T> vec;
		this->PostOrder(this->m_pRoot, vec);
		return vec;
	}

	template<typename T>
	vector<T> CLinkedBSTree<T>::BreadthFirst(void) const
	{
		//queue<const CBSTreeNode<T>*> q;
		CLinkedQueue<const CSmartPointer<CBSTreeNode<T> > > q;
		//CArrayQueue<const CBSTreeNode<T>*, 10> q;
		vector<T> vec;

		if (NULL != this->m_pRoot)
		{
			q.Push(this->m_pRoot);
			while (!q.IsEmpty())
			{
				CSmartPointer<CBSTreeNode<T> > spNode = q.Front();

				vec.push_back(*spNode);
				if (NULL != spNode->m_spLeft)
				{
					q.Push(spNode->m_spLeft);
				}
				if (NULL != spNode->m_spRight)
				{
					q.Push(spNode->m_spRight);
				}
				q.Pop();
			}
		}
		return vec;
	}

	template <typename T>
	T* CLinkedBSTree<T>::FindNode(const T& t)
	{
		CSmartPointer<CBSTreeNode<T> > sp = this->FindNode(this->m_pRoot, t);
		if (sp)
		{
			return &(static_cast<T&>(*sp));
		}
		else
		{
			return NULL;
		}
	}

	template <typename T>
	bool CLinkedBSTree<T>::Remove(const T& t)
	{
		CSmartPointer<CBSTreeNode<T> >& spNode = this->FindNode(this->m_pRoot, t);

		if (NULL == spNode)
		{
			return false;
		}
		else
		{
			if (NULL == spNode->m_spLeft && NULL == spNode->m_spRight)		//如果删除的是叶子节点
			{
				spNode = CSmartPointer<CBSTreeNode<T> >(NULL);
			}
			else
			{
				if (NULL != spNode->m_spLeft && NULL == spNode->m_spRight)		//如果右孩子为空
				{
					spNode = spNode->m_spLeft;
				}
				else
				{
					if (NULL == spNode->m_spLeft && NULL != spNode->m_spRight)		//如果左孩子为空
					{
						spNode = spNode->m_spRight;
					}
					else		//左右孩子都不空
					{
						//获取其左子树中最大的节点
						vector<T> vec;
						this->InOrder(spNode->m_spLeft, vec);
						this->Remove(vec.back());
						static_cast<T&>(*spNode) = vec.back();
					}
				}
			}
			return true;
		}
	}

	template<typename T>
	void CLinkedBSTree<T>::PreOrder(const CSmartPointer<CBSTreeNode<T> >& spNode, vector<T>& vec) const
	{
		if (NULL != spNode)
		{
			vec.push_back(*spNode);
			this->PreOrder(spNode->m_spLeft, vec);
			this->PreOrder(spNode->m_spRight, vec);
		}
	}

	template<typename T>
	void CLinkedBSTree<T>::InOrder(const CSmartPointer<CBSTreeNode<T> >& spNode, vector<T>& vec) const
	{
		if (NULL != spNode)
		{
			this->InOrder(spNode->m_spLeft, vec);
			vec.push_back(*spNode);
			this->InOrder(spNode->m_spRight, vec);
		}
	}

	template<typename T>
	void CLinkedBSTree<T>::ReInOrder(const CSmartPointer<CBSTreeNode<T> >& spNode, vector<T>& vec) const
	{
		if (NULL != spNode)
		{
			this->ReInOrder(spNode->m_spRight, vec);
			vec.push_back(*spNode);
			this->ReInOrder(spNode->m_spLeft, vec);
		}
	}

	template<typename T>
	void CLinkedBSTree<T>::PostOrder(const CSmartPointer<CBSTreeNode<T> >& spNode, vector<T>& vec) const
	{
		if (NULL != spNode)
		{
			this->PostOrder(spNode->m_spLeft, vec);
			this->PostOrder(spNode->m_spRight, vec);
			vec.push_back(*spNode);
		}
	}

	template <typename T>
	bool CLinkedBSTree<T>::Insert(CSmartPointer<CBSTreeNode<T> >& spNode, const T& t)
	{
		if (NULL == spNode)
		{
			spNode = CSmartPointer<CBSTreeNode<T> >(new CBSTreeNode<T>(t));
			if (NULL == spNode)
			{
				return false;
			}
			else
			{
				return true;
			}
		}
		else
		{
			if (t < *spNode)
			{
				return this->Insert(spNode->m_spLeft, t);
			}
			else
			{
				if (t == *spNode)
				{
					return true;
				}
				else
				{
					return this->Insert(spNode->m_spRight, t);
				}
			}
		}
	}

	template <typename T>
	CSmartPointer<CBSTreeNode<T> >& CLinkedBSTree<T>::FindNode(CSmartPointer<CBSTreeNode<T> >& spNode, const T& t) const
	{
		if (NULL != spNode)
		{
			if (t == *spNode)
			{
				return spNode;
			}
			else
			{
				if (t < *spNode)
				{
					return this->FindNode(spNode->m_spLeft, t);
				}
				else
				{
					return this->FindNode(spNode->m_spRight, t);
				}
			}
		}
		else
		{
			return spNode;
		}
	}
}

namespace MyAlgorithm
{
	//平衡二叉树
	template <typename T>
	class CBBTree : public CLinkedBSTree<T>
	{
	public:
		bool Insert(const T&);
	private:
		//以平衡二叉树的方式递归插入节点
		//最后一个参数表示插入操作是否
		//返回-1表示存在相同节点，未进行插入，0表示插入成功，1表示插入使树长高
		int Insert(CSmartPointer<CBSTreeNode<T> >&, const T&);
		//对平衡二叉树进行左旋操作
		void LRotate(CSmartPointer<CBSTreeNode<T> >&);

		//对平衡二叉树进行右旋操作
		void RRotate(CSmartPointer<CBSTreeNode<T> >&);

		//左子树平衡处理
		void LeftBalance(CSmartPointer<CBSTreeNode<T> >&);

		//右子树平衡处理
		void RightBalance(CSmartPointer<CBSTreeNode<T> >&);
	};

	template <typename T>
	bool CBBTree<T>::Insert(const T& t)
	{
		return this->Insert(this->m_pRoot, t) >= 0;
	}

	template <typename T>
	void CBBTree<T>::LRotate(CSmartPointer<CBSTreeNode<T> >& spNode)
	{
		CSmartPointer<CBSTreeNode<T> > pTemp = spNode->m_spRight;

		spNode->m_spRight = pTemp->m_spLeft;
		pTemp->m_spLeft = spNode;
		spNode = pTemp;
	}

	template <typename T>
	void CBBTree<T>::RRotate(CSmartPointer<CBSTreeNode<T> >& spNode)
	{
		CSmartPointer<CBSTreeNode<T> > pTemp = spNode->m_spLeft;

		spNode->m_spLeft = pTemp->m_spRight;
		pTemp->m_spRight = spNode;
		spNode = pTemp;
	}

	template <typename T>
	void CBBTree<T>::LeftBalance(CSmartPointer<CBSTreeNode<T> >& spNode)
	{
		CSmartPointer<CBSTreeNode<T> > spTemp1 = spNode->m_spLeft;
		CSmartPointer<CBSTreeNode<T> > spTemp2 = spTemp1->m_spRight;

		switch (spTemp1->m_iBF)		//检查左子树的平衡度
		{
		case -1:
			switch (spTemp2->m_iBF)
			{
			case -1:
				spTemp1->m_iBF = 1;
				spNode->m_iBF = 0;
				break;
			case 0:
				spTemp1->m_iBF = spNode->m_iBF = 0;
				break;
			case 1:
				spTemp1->m_iBF = 0;
				spNode->m_iBF = -1;
				break;
			default:
				break;
			}
			spTemp2->m_iBF = 0;
			this->LRotate(spNode->m_spLeft);
			this->RRotate(spNode);
			break;
		case 1:
			spNode->m_iBF = spTemp1->m_iBF = 0;
			this->RRotate(spNode);
			break;
		default:
			break;
		}
	}

	template <typename T>
	void CBBTree<T>::RightBalance(CSmartPointer<CBSTreeNode<T> >& spNode)
	{
		CSmartPointer<CBSTreeNode<T> > spTemp1 = spNode->m_spRight;
		CSmartPointer<CBSTreeNode<T> > spTemp2 = spTemp1->m_spLeft;

		switch (spTemp1->m_iBF)		//检查右子树的平衡度
		{
		case -1:
			spNode->m_iBF = spTemp1->m_iBF = 0;
			this->LRotate(spNode);
			break;
		case 1:
			switch (spTemp2->m_iBF)
			{
			case -1:
				spTemp1->m_iBF = 1;
				spNode->m_iBF = 0;
				break;
			case 0:
				spTemp1->m_iBF = spNode->m_iBF = 0;
				break;
			case 1:
				spTemp1->m_iBF = -1;
				spNode->m_iBF = 0;
				break;
			default:
				break;
			}
			spTemp2->m_iBF = 0;
			this->RRotate(spNode->m_spRight);
			this->LRotate(spNode);
			break;
		default:
			break;
		}
	}

	template <typename T>
	int CBBTree<T>::Insert(CSmartPointer<CBSTreeNode<T> >& spNode, const T& t)
	{
		int iRet = -1;

		if (!spNode)
		{
			spNode = CSmartPointer<CBSTreeNode<T> >(new CBSTreeNode<T>(t));
			iRet = 1;
		}
		else
		{
			if (t == *spNode)
			{
				iRet = -1;
			}
			else
			{
				if (t < *spNode)		//在左子树插入
				{
					switch (this->Insert(spNode->m_spLeft, t))
					{
					case -1:		//没有插入
						iRet = -1;
						break;
					case 0:
						iRet = 0;
						break;
					case 1:			//插入使树升高
						switch (spNode->m_iBF)
						{
						case -1:
							spNode->m_iBF = 0;
							iRet = 0;
							break;
						case 0:
							spNode->m_iBF = 1;
							iRet = 1;
							break;
						case 1:
							this->LeftBalance(spNode);
							iRet = 0;
							break;
						}
						break;
					default:
						break;
					}
				}
				else		//在右子树插入
				{
					switch (this->Insert(spNode->m_spRight, t))
					{
					case -1:		//没有插入
						iRet = -1;
						break;
					case 0:
						iRet = 0;
						break;
					case 1:			//插入成功并且使树升高
						switch (spNode->m_iBF)
						{
						case -1:
							this->RightBalance(spNode);
							iRet = 0;
							break;
						case 0:
							spNode->m_iBF = -1;
							iRet = 1;
							break;
						case 1:
							spNode->m_iBF = 0;
							iRet = 0;
							break;
						default:
							break;
						}
						break;
					default:
						break;
					}
				}
			}
		}

		return iRet;
	}
}

namespace MyAlgorithm
{
	template <typename T>
	class CArrayBSTree : public CBTree<T>
	{
	public:
		struct TTreeNode
		{
			TTreeNode(void) :
				m_bValid(false),
				m_tValue(NULL)
			{}
			bool m_bValid;			//标记节点是否为有效节点
			T m_tValue;
		};

		CArrayBSTree(void) :
			m_szArrayLen(0),
			m_pRoot(NULL)
		{}

		~CArrayBSTree(void)
		{
			delete[] this->m_pRoot;
		}

		//插入
		bool Insert(const T&);

		//查找
		T* FindNode(const T&);

		//前序遍历
		vector<T> PreOrder(void) const;

		//中序遍历
		vector<T> InOrder(void) const;
		//反中序遍历
		vector<T> ReInOrder(void) const;

		//后序遍历
		vector<T> PostOrder(void) const;

		//层次遍历
		vector<T> BreadthFirst(void) const;

		//删除节点
		bool Remove(const T&);
	private:
		//禁止复制和赋值
		CArrayBSTree(const CArrayBSTree&);
		CArrayBSTree& operator =(const CArrayBSTree&);

		//获取左孩子
		size_t GetLeftChildIndex(size_t) const;

		//获取右孩子
		size_t GetRightChildIndex(size_t) const;

		//插入节点
		bool Insert(size_t, const T&);

		//查找节点
		TTreeNode* FindNode(size_t, const T&);

		//前序遍历
		void PreOrder(size_t, vector<T>&) const;

		//中序遍历
		void InOrder(size_t, vector<T>&) const;
		//反中序遍历（先）
		void ReInOrder(size_t, vector<T>&) const;

		//中序遍历
		void PostOrder(size_t, vector<T>&) const;

		//提升指定节
		//第一个参数是需要提升的节点的序号
		//下一个参数是新的序号
		void Promote(size_t, size_t) const;

		size_t m_szArrayLen;				//数组的长度
		TTreeNode* m_pRoot;				//根节点
	};

	template <typename T>
	bool CArrayBSTree<T>::Insert(const T& t)
	{
		return this->Insert(0, t);
	}

	template <typename T>
	T* CArrayBSTree<T>::FindNode(const T& t)
	{
		TTreeNode* p = this->FindNode(0, t);

		if (NULL != p)
		{
			return &p->m_tValue;
		}
		else
		{
			return NULL;
		}
	}

	template <typename T>
	vector<T> CArrayBSTree<T>::PreOrder(void) const
	{
		vector<T> vec;
		this->PreOrder(0, vec);
		return vec;
	}

	template <typename T>
	vector<T> CArrayBSTree<T>::InOrder(void) const
	{
		vector<T> vec;
		this->InOrder(0, vec);
		return vec;
	}

	template <typename T>
	vector<T> CArrayBSTree<T>::ReInOrder(void) const
	{
		vector<T> vec;
		this->ReInOrder(0, vec);
		return vec;
	}

	template <typename T>
	vector<T> CArrayBSTree<T>::PostOrder(void) const
	{
		vector<T> vec;
		this->PostOrder(0, vec);
		return vec;
	}

	template <typename T>
	size_t CArrayBSTree<T>::GetLeftChildIndex(size_t szIndex) const
	{
		return 2 * szIndex + 1;
	}

	template <typename T>
	size_t CArrayBSTree<T>::GetRightChildIndex(size_t szIndex) const
	{
		return 2 * szIndex + 2;
	}

	template <typename T>
	bool CArrayBSTree<T>::Insert(size_t szIndex, const T& t)
	{
		if (szIndex < this->m_szArrayLen)
		{
			if (this->m_pRoot[szIndex].m_bValid)
			{
				if (t < this->m_pRoot[szIndex].m_tValue)
				{
					return this->Insert(this->GetLeftChildIndex(szIndex), t);
				}
				else
				{
					if (t == this->m_pRoot[szIndex].m_tValue)
					{
						return true;
					}
					else
					{
						return this->Insert(this->GetRightChildIndex(szIndex), t);
					}
				}
			}
			else
			{
				this->m_pRoot[szIndex].m_tValue = t;
				return this->m_pRoot[szIndex].m_bValid = true;
			}
		}
		else
		{
			TTreeNode* pTemp = new TTreeNode[szIndex + 1];
			memcpy(pTemp, this->m_pRoot, sizeof(TTreeNode) * this->m_szArrayLen);
			delete[] this->m_pRoot;
			this->m_pRoot = pTemp;
			this->m_szArrayLen = szIndex + 1;
			return this->Insert(szIndex, t);
		}
	}

	template <typename T>
	typename CArrayBSTree<T>::TTreeNode* CArrayBSTree<T>::FindNode(size_t szIndex, const T& t)
	{
		if (szIndex < this->m_szArrayLen && this->m_pRoot[szIndex].m_bValid)
		{
			const T& tTemp = this->m_pRoot[szIndex].m_tValue;

			if (t < tTemp)
			{
				return this->FindNode(this->GetLeftChildIndex(szIndex), t);
			}
			else
			{
				if (t == tTemp)
				{
					return &this->m_pRoot[szIndex];
				}
				else
				{
					return this->FindNode(this->GetRightChildIndex(szIndex), t);
				}
			}
		}
		else
		{
			return NULL;
		}
	}

	template <typename T>
	void CArrayBSTree<T>::PreOrder(size_t szIndex, vector<T>& vec) const
	{
		if (szIndex < this->m_szArrayLen && this->m_pRoot[szIndex].m_bValid)
		{
			vec.push_back(this->m_pRoot[szIndex].m_tValue);
			this->PreOrder(this->GetLeftChildIndex(szIndex), vec);
			this->PreOrder(this->GetRightChildIndex(szIndex), vec);
		}
	}

	template <typename T>
	void CArrayBSTree<T>::InOrder(size_t szIndex, vector<T>& vec) const
	{
		if (szIndex < this->m_szArrayLen && this->m_pRoot[szIndex].m_bValid)
		{
			this->InOrder(this->GetLeftChildIndex(szIndex), vec);
			vec.push_back(this->m_pRoot[szIndex].m_tValue);
			this->InOrder(this->GetRightChildIndex(szIndex), vec);
		}
	}

	template <typename T>
	void CArrayBSTree<T>::ReInOrder(size_t szIndex, vector<T>& vec) const
	{
		if (szIndex < this->m_szArrayLen && this->m_pRoot[szIndex].m_bValid)
		{
			this->ReInOrder(this->GetRightChildIndex(szIndex), vec);
			vec.push_back(this->m_pRoot[szIndex].m_tValue);
			this->ReInOrder(this->GetLeftChildIndex(szIndex), vec);
		}
	}

	template <typename T>
	void CArrayBSTree<T>::PostOrder(size_t szIndex, vector<T>& vec) const
	{
		if (szIndex < this->m_szArrayLen && this->m_pRoot[szIndex].m_bValid)
		{
			this->PostOrder(this->GetLeftChildIndex(szIndex), vec);
			this->PostOrder(this->GetRightChildIndex(szIndex), vec);
			vec.push_back(this->m_pRoot[szIndex].m_tValue);
		}
	}

	template <typename T>
	vector<T> CArrayBSTree<T>::BreadthFirst(void) const
	{
		vector<T> vec;
		for (size_t sz = 0; sz < this->m_szArrayLen; ++sz)
		{
			this->m_pRoot[sz].m_bValid ? vec.push_back(this->m_pRoot[sz].m_tValue): void(NULL);
		}
		return vec;
	}

	template <typename T>
	void CArrayBSTree<T>::Promote(size_t szOldIndex, size_t szNewIndex) const
	{
		queue<pair<size_t, size_t> > q;			//<旧位置索引，新位置索引>

		q.push(make_pair(szOldIndex, szNewIndex));
		while (!q.empty())
		{
			if (q.front().first < this->m_szArrayLen && this->m_pRoot[q.front().first].m_bValid && q.front().second < this->m_szArrayLen)
			{
				this->m_pRoot[q.front().second] = this->m_pRoot[q.front().first];
				this->m_pRoot[q.front().first].m_bValid = false;
				q.push(make_pair(this->GetLeftChildIndex(q.front().first), this->GetLeftChildIndex(q.front().second)));
				q.push(make_pair(this->GetRightChildIndex(q.front().first), this->GetRightChildIndex(q.front().second)));
			}
			q.pop();
		}
	}

	template <typename T>
	bool CArrayBSTree<T>::Remove(const T& t)
	{
		TTreeNode* pNode = this->FindNode(0, t);

		if (NULL == pNode)
		{
			return false;
		}
		else
		{
			size_t szIndex = pNode - this->m_pRoot;
			size_t szLeftChildIndex = this->GetLeftChildIndex(szIndex);
			size_t szRightChildIndex = this->GetRightChildIndex(szIndex);

			if ((szLeftChildIndex < this->m_szArrayLen && this->m_pRoot[szLeftChildIndex].m_bValid)
				|| (szRightChildIndex < this->m_szArrayLen && this->m_pRoot[szRightChildIndex].m_bValid))			//如果不是叶子节点
			{
				if (!this->m_pRoot[this->GetRightChildIndex(szIndex)].m_bValid)			//如果右孩子为空
				{
					this->m_pRoot[szIndex].m_bValid = false;
					//this->PromoteLeftChild(szLeftChildIndex);
					this->Promote(szLeftChildIndex, (szLeftChildIndex + 1) / 2 - 1);
					return true;
				}
				else
				{
					if (!this->m_pRoot[this->GetLeftChildIndex(szIndex)].m_bValid)		//如果左孩子为空
					{
						this->m_pRoot[szIndex].m_bValid = false;
						//this->PromoteRightChild(szRightChildIndex);
						this->Promote(szRightChildIndex, (szRightChildIndex + 1) / 2 - 1);
						return true;
					}
					else
					{
						vector<T> vec;
						this->InOrder(this->GetLeftChildIndex(szIndex), vec);
						TTreeNode* pNode = this->FindNode(0, vec.back());

						this->m_pRoot[szIndex].m_tValue = pNode->m_tValue;
						pNode->m_bValid = false;
						return true;
					}
				}
			}
			else
			{
				this->m_pRoot[szIndex].m_bValid = false;
				return true;
			}
		}
	}
}

namespace MyAlgorithm
{
	template <typename T>
	class CBMinusTree : public CBTree<T>
	{
	public:
		CBMinusTree(size_t szOrder) :
		  m_szOrder(szOrder)
		{}

		bool Insert(const T&);

		vector<T> PreOrder(void) const;

		vector<T> InOrder(void) const;
		vector<T> ReInOrder(void) const;

		vector<T> PostOrder(void) const;

		vector<T> BreadthFirst(void) const;

		T* FindNode(const T&);

		bool Remove(const T&);

	private:
		//禁止赋值与复制
		CBMinusTree(const CBMinusTree&);
		CBMinusTree& operator =(const CBMinusTree&);

		bool Insert(CSmartPointer<CBMinusTreeNode<T> >&, const T&);

		void PreOrder(const CSmartPointer<CBMinusTreeNode<T> >&, vector<T>&) const;

		const size_t m_szOrder;			//阶数
		CSmartPointer<CBMinusTreeNode<T> > m_spRoot;
	};

	template <typename T>
	bool CBMinusTree<T>::Insert(const T& t)
	{
		return this->Insert(this->m_spRoot, t);
	}

	template <typename T>
	void CBMinusTree<T>::PreOrder(const CSmartPointer<CBMinusTreeNode<T> >& sp, vector<T>& vec) const
	{
		if (sp)
		{			
			for (vector<CPair<T> >::const_iterator cit = sp->m_vec.begin() + 1; cit != sp->m_vec.end(); ++cit)
			{
				vec.push_back(cit->m_t);
			}
		}
	}

	template <typename T>
	vector<T> CBMinusTree<T>::PreOrder(void) const
	{
		vector<T> vec;
		this->PreOrder(this->m_spRoot, vec);
		return vec;
	}

	template <typename T>
	vector<T> CBMinusTree<T>::InOrder(void) const
	{
		vector<T> vec;
		return vec;
	}

	template <typename T>
	vector<T> CBMinusTree<T>::ReInOrder(void) const
	{
		vector<T> vec;
		return vec;
	}

	template <typename T>
	vector<T> CBMinusTree<T>::PostOrder(void) const
	{
		vector<T> vec;
		return vec;
	}

	template <typename T>
	vector<T> CBMinusTree<T>::BreadthFirst(void) const
	{
		vector<T> vec;
		return vec;
	}

	template <typename T>
	T* CBMinusTree<T>::FindNode(const T&)
	{
		return NULL;
	}

	template <typename T>
	bool CBMinusTree<T>::Remove(const T&)
	{
		return false;
	}

	template <typename T>
	bool CBMinusTree<T>::Insert(CSmartPointer<CBMinusTreeNode<T> >& sp, const T& t)
	{
		if (!sp)
		{
			sp = CSmartPointer<CBMinusTreeNode<T> >(new CBMinusTreeNode<T>);
			sp->m_vec.push_back(t);		//之用其中的指针，忽略其键值
			sp->m_vec.push_back(t);
		}
		else
		{
			vector<CPair<T> >::const_iterator cit;

			for (cit = sp->m_vec.begin() + 1; cit != sp->m_vec.end();)
			{
				if (*cit < t)
				{
					++cit;
				}
				else
				{
					if (CPair<T>(t) == *cit)
					{
						return false;
					}
					else
					{
						break;
					}
				}
			}

			if (sp->m_vec.size() < this->m_szOrder)
			{
				sp->m_vec.insert(cit, t);
			}
			else		//分裂节点
			{
				exit(0);
			}
		}
		return true;
	}
}

namespace MyAlgorithm
{
	template <typename T>
	class CRBTree : public CBTree<T>
	{
	public:
		//前序遍历
		vector<T> PreOrder(void) const;

		//中序遍历
		vector<T> InOrder(void) const;
		//反中序遍历
		vector<T> ReInOrder(void) const;

		//后序遍历
		vector<T> PostOrder(void) const;

		//层次遍历
		vector<T> BreadthFirst(void) const;

		//插入节点，返回值表示是否插入成功
		bool Insert(const T&);

		//查找节点
		T* FindNode(const T&);

		//删除节点
		bool Remove(const T&);
	};

	template <typename T>
	vector<T> CRBTree<T>::PreOrder(void) const
	{
		vector<T> vec;
		return vec;
	}

	template <typename T>
	vector<T> CRBTree<T>::InOrder(void) const
	{
		vector<T> vec;
		return vec;
	}

	template <typename T>
	vector<T> CRBTree<T>::ReInOrder(void) const
	{
		vector<T> vec;
		return vec;
	}

	template <typename T>
	vector<T> CRBTree<T>::PostOrder(void) const
	{
		vector<T> vec;
		return vec;
	}

	template <typename T>
	vector<T> CRBTree<T>::BreadthFirst(void) const
	{
		vector<T> vec;
		return vec;
	}

	template <typename T>
	bool CRBTree<T>::Insert(const T&)
	{
		return false;
	}

	template <typename T>
	T* CRBTree<T>::FindNode(const T&)
	{
		return NULL;
	}

	template <typename T>
	bool CRBTree<T>::Remove(const T&)
	{
		return false;
	}
}

#endif
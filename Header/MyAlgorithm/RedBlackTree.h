#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include <cstdlib>

namespace MyAlgorithm
{
	template<typename T>
	class CRedBlackTree
	{
	public:
		class CNode
		{
		public:
			enum EColor{RED, BLACK};
			CNode(T val = NULL) :
				m_pParentNode(NULL),
				m_pLeftChildNode(NULL),
				m_pRightChildNode(NULL),
				m_eColor(BLACK),
				m_val(val)
			{
			}

			//设置颜色
			void SetColor(const EColor& eColor)
			{
				this->m_eColor = eColor;
			}

			//获取颜色
			EColor GetColor(void) const
			{
				return this->m_eColor;
			}

			//设置值
			void SetValue(const T& val)
			{
				this->m_val = val;
			}

			//获取值
			T GetValue(void) const
			{
				return this->m_val;
			}

			//获取祖父节点
			CNode* GetGParent(void) const
			{
				return NULL == this->m_pParentNode ? NULL : this->m_pParentNode->GetParent();
			}

			//获取父节点
			CNode* GetParent(void) const
			{
				return this->m_pParentNode;
			}

			//获取左子节点
			CNode* GetLeftChild(void) const
			{
				return this->m_pLeftChildNode;
			}

			//获取右子节点
			CNode* GetRightChild(void) const
			{
				return this->m_pRightChildNode;
			}

			//获取叔父节点
			CNode* GetUncle(void) const
			{
				return NULL == this->GetGParent() ? NULL : (this->m_pParentNode == this->GetGParent()->GetLeftChild() ? this->GetGParent()->GetRightChild() : this->GetGParent()->GetLeftChild());
			}

		private:
			CNode* m_pParentNode;				//父节点
			CNode* m_pLeftChildNode;			//左子节点
			CNode* m_pRightChildNode;			//右子节点
			EColor m_eColor;					//颜色
			T m_val;								//值
		};

                using CNode::BLACK;
                using CNode::RED;

		CRedBlackTree(void) :
			m_pRootNode(NULL)
		{
		}

		//获取树的根节点
		CRedBlackTree* GetRootNode(void) const
		{
			return this->m_pRootNode;
		}

		//插入节点
		void InsertNode(const CNode&);

	private:
		//新节点N没有父节点P
		void InsertNode1(const CNode&);

		//新节点N的父节点P是黑色的
		void InsertNode2(const CNode&);

		//父节点P和叔父U节点都为红色
		void InsertNode3(const CNode&);

		//父节点P是红色，叔父节点U是黑色的或空
		//本节点N是其父节点P的右孩子，其父节点P又是其父节点G的左孩子
		void InsertNode4(const CNode&);

		//父节点P是红色，叔父节点U是黑色的或空
		//本节点N是其父节点P的左孩子，其父节点P又是其父节点G的左孩子
		void InsertNode5(const CNode&);

		CNode* m_pRootNode;					//根节点
	};
}
#endif
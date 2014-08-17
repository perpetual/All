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

			//������ɫ
			void SetColor(const EColor& eColor)
			{
				this->m_eColor = eColor;
			}

			//��ȡ��ɫ
			EColor GetColor(void) const
			{
				return this->m_eColor;
			}

			//����ֵ
			void SetValue(const T& val)
			{
				this->m_val = val;
			}

			//��ȡֵ
			T GetValue(void) const
			{
				return this->m_val;
			}

			//��ȡ�游�ڵ�
			CNode* GetGParent(void) const
			{
				return NULL == this->m_pParentNode ? NULL : this->m_pParentNode->GetParent();
			}

			//��ȡ���ڵ�
			CNode* GetParent(void) const
			{
				return this->m_pParentNode;
			}

			//��ȡ���ӽڵ�
			CNode* GetLeftChild(void) const
			{
				return this->m_pLeftChildNode;
			}

			//��ȡ���ӽڵ�
			CNode* GetRightChild(void) const
			{
				return this->m_pRightChildNode;
			}

			//��ȡ�常�ڵ�
			CNode* GetUncle(void) const
			{
				return NULL == this->GetGParent() ? NULL : (this->m_pParentNode == this->GetGParent()->GetLeftChild() ? this->GetGParent()->GetRightChild() : this->GetGParent()->GetLeftChild());
			}

		private:
			CNode* m_pParentNode;				//���ڵ�
			CNode* m_pLeftChildNode;			//���ӽڵ�
			CNode* m_pRightChildNode;			//���ӽڵ�
			EColor m_eColor;					//��ɫ
			T m_val;								//ֵ
		};

                using CNode::BLACK;
                using CNode::RED;

		CRedBlackTree(void) :
			m_pRootNode(NULL)
		{
		}

		//��ȡ���ĸ��ڵ�
		CRedBlackTree* GetRootNode(void) const
		{
			return this->m_pRootNode;
		}

		//����ڵ�
		void InsertNode(const CNode&);

	private:
		//�½ڵ�Nû�и��ڵ�P
		void InsertNode1(const CNode&);

		//�½ڵ�N�ĸ��ڵ�P�Ǻ�ɫ��
		void InsertNode2(const CNode&);

		//���ڵ�P���常U�ڵ㶼Ϊ��ɫ
		void InsertNode3(const CNode&);

		//���ڵ�P�Ǻ�ɫ���常�ڵ�U�Ǻ�ɫ�Ļ��
		//���ڵ�N���丸�ڵ�P���Һ��ӣ��丸�ڵ�P�����丸�ڵ�G������
		void InsertNode4(const CNode&);

		//���ڵ�P�Ǻ�ɫ���常�ڵ�U�Ǻ�ɫ�Ļ��
		//���ڵ�N���丸�ڵ�P�����ӣ��丸�ڵ�P�����丸�ڵ�G������
		void InsertNode5(const CNode&);

		CNode* m_pRootNode;					//���ڵ�
	};
}
#endif
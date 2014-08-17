#include "MyAlgorithm/RedBlackTree.h"

namespace MyAlgorithm
{
	///////////////////////////嵌套类成员函数定义////////////////////////////

	//////////////////////////红黑树类成员函数定义/////////////////////////
	template<typename T>
	void CRedBlackTree<T>::InsertNode(const CNode& oNode)
	{
	}

	template<typename T>
	void CRedBlackTree<T>::InsertNode1(const CNode& oNode)
	{
		NULL == oNode.GetParent() ? oNode.SetColor(BLACK) : this->InsertNode2(oNode);
	}

	template<typename T>
	void CRedBlackTree<T>::InsertNode2(const CNode& oNode)
	{
		if (NULL != oNode.GetParent() && BLACK == oNode.GetParent())
		{
			return;
		}
		else
		{
			this->InsertNode3(oNode);
		}
	}

	template<typename T>
	void CRedBlackTree<T>::InsertNode3(const CNode& oNode)
	{
		if (NULL != oNode.GetParent() && RED == oNode.GetParent()->GetColor()
			&& NULL != oNode.GetUncle() && RED == oNode.GetUncle()->GetColor())
		{
			oNode.GetParent()->SetColor(BLACK);
			oNode.GetUncle()->SetColor(BLACK);
			oNode.GetGParent()->SetColor(RED);
			this->InsertNode1(*oNode.GetGParent());
		}
		else
		{
			this->InsertNode4(oNode);
		}
	}

	template<typename T>
	void CRedBlackTree<T>::InsertNode4(const CNode& oNode)
	{
		if (NULL != oNode.GetParent() && &oNode == oNode.GetParent()->GetRightChild()
			&& NULL != oNode.GetGParent() && oNode.GetParent() == oNode.GetGParent()->GetLeftChild())
		{
		}
		else
		{
			if (NULL != oNode.GetParent() && &oNode == oNode.GetParent()->GetLeftChild()
				&& NULL != oNode.GetGParent() && oNode.GetParent() == oNode.GetGParent()->GetRightChild())
			{
			}
		}
		this->InsertNode5(oNode);
	}

	template<typename T>
	void CRedBlackTree<T>::InsertNode5(const CNode& oNode)
	{
	}
}
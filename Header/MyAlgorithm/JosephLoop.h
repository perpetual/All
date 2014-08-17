#ifndef MYALGORITHM_JOSEPH_LOOP_H
#define MYALGORITHM_JOSEPH_LOOP_H

#include <vector>
#include "Nodes.h"

//约瑟夫环
namespace MyAlgorithm
{
	using std::vector;

	template <typename T>
	class CJosephLoop
	{
	public:
		//第一个参数为约瑟夫环中元素的个数
		//下一个参数是报数的最大值
		CJosephLoop(unsigned short = 3, unsigned short = 3);
		//打印环
		vector<T> GetResult(void);
	private:
		//禁止复制和赋值
		CJosephLoop(const CJosephLoop&);
		CJosephLoop& operator =(const CJosephLoop&);

		const unsigned short m_usCount;
		const unsigned short m_usNO;				//报数最大值
		CSLLNode<T>* m_pCur;
		CSLLNode<T>* m_pPre;
		vector<T> m_vecResult;
	};

	template <typename T>
	CJosephLoop<T>::CJosephLoop(unsigned short usCount, unsigned short usNO) :
		m_usCount(usCount),
		m_usNO(usNO),
		m_pCur(NULL),
		m_pPre(NULL)
	{
		if (0 == usCount || 0 == usNO || usCount < usNO)
		{
			throw exception("参数错误");
		}
		this->m_pCur = new CSLLNode<T>(1);
		CSLLNode<T>* pHead = this->m_pCur;
		for (unsigned short us = 2; us <= usCount; ++us)
		{
			m_pCur->m_spNext = new CSLLNode<T>(us);
			m_pCur->m_spNext->m_pNext = NULL;
			m_pCur = m_pCur->m_spNext;
		}
		this->m_pCur->m_spNext = pHead;
		this->m_pPre = this->m_pCur;
		this->m_pCur = this->m_pCur->m_spNext;

		while (NULL != this->m_pCur)
		{
			for (unsigned short us = 0; us < this->m_usNO - 1; ++us)
			{
				this->m_pCur = this->m_pCur->m_spNext;
				this->m_pPre = this->m_pPre->m_spNext;
			}
			CSLLNode<T>* pTemp = this->m_pCur;
			this->m_vecResult.push_back(*this->m_pCur);
			if (this->m_pCur->m_spNext == this->m_pCur)			//如果是最后一个节点
			{
				this->m_pCur = NULL;
			}
			else
			{
				this->m_pPre->m_spNext = this->m_pCur->m_spNext;
				this->m_pCur = this->m_pCur->m_spNext;
			}
			delete pTemp;
		}
	}

	template <typename T>
	vector<T> CJosephLoop<T>::GetResult(void)
	{
		return this->m_vecResult;
	}
}

#endif
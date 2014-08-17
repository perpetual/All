#ifndef MYALGORITHM_SHUFFLE_H
#define MYALGORITHM_SHUFFLE_H

#include "MyAlgorithm/Random.h"
#include <vector>

namespace MyAlgorithm
{
	using std::vector;
	using Random::CRandom;

	//���������ϴ��
	class CShuffle
	{
	public:
		//����Ϊ�Ƶĸ���
		CShuffle(unsigned short = 16);

		//ϴ��
		void Shuffle(void);
	private:
		//��ֹ���ƺ͸�ֵ
		CShuffle(const CShuffle&);
		CShuffle& operator =(const CShuffle&);
		vector<int> m_vecCards;
		CRandom m_oRand;
		const unsigned short m_usCardCount;
	};
}
#endif
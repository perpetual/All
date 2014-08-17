#ifndef MYALGORITHM_SHUFFLE_H
#define MYALGORITHM_SHUFFLE_H

#include "MyAlgorithm/Random.h"
#include <vector>

namespace MyAlgorithm
{
	using std::vector;
	using Random::CRandom;

	//利用随机数洗牌
	class CShuffle
	{
	public:
		//参数为牌的个数
		CShuffle(unsigned short = 16);

		//洗牌
		void Shuffle(void);
	private:
		//禁止复制和赋值
		CShuffle(const CShuffle&);
		CShuffle& operator =(const CShuffle&);
		vector<int> m_vecCards;
		CRandom m_oRand;
		const unsigned short m_usCardCount;
	};
}
#endif
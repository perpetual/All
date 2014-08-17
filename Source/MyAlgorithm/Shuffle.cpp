#include "MyAlgorithm/Shuffle.h"
#include <algorithm>
#include <iostream>
#include <iterator>

namespace MyAlgorithm
{
	using std::cout;
	using std::endl;
	using std::ends;
	using std::swap;
	using std::ostream_iterator;

	CShuffle::CShuffle(unsigned short usCardCount) :
		m_usCardCount(usCardCount)
	{
		for (int i = 1; i <= this->m_usCardCount; ++i)
		{
			this->m_vecCards.push_back(i);
			cout << i << ends;
		}
		cout << endl;
	}

	void CShuffle::Shuffle(void)
	{
		for (vector<int>::size_type count = this->m_usCardCount - 1; count > 0; --count)
		{
			vector<int>::size_type pos = this->m_oRand.Get() % count;
			swap(this->m_vecCards[count], this->m_vecCards[pos]);
		}
		copy(this->m_vecCards.begin(), this->m_vecCards.end(), ostream_iterator<int>(cout, " "));
		cout << endl;
	}
}
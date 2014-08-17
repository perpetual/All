#include <iostream>
#include <complex>
#include "MyAlgorithm/EightQueens.h"

namespace MyAlgorithm
{
	using std::cout;
	using std::endl;
        using std::abs;

	CEightQueens::CEightQueens(unsigned short usDimension) : m_usDimension(usDimension), m_uiCount(0)
	{
		this->PutChess(0);
	}

	bool CEightQueens::Attack(unsigned short usRow)
	{
		for (map<unsigned short, unsigned short>::const_iterator citLocation = m_mapQueens.begin(); citLocation != m_mapQueens.end() && citLocation->first < usRow; ++citLocation)
		{
			unsigned short usColumn = this->m_mapQueens[usRow];
			if (usRow == citLocation->first
				|| usColumn == citLocation->second
				|| abs(static_cast<double>(citLocation->first - usRow)) == abs(static_cast<double>(citLocation->second - usColumn)))
			{
				return true;
			}
		}
		return false;
	}

	void CEightQueens::Display(void)
	{
		cout << "@@@@@(" << ++this->m_uiCount << ")@@@@@@" << endl;
		for (unsigned short usX = 0; usX < this->m_usDimension; ++usX)
		{
			for (unsigned short usY = 0; usY < this->m_usDimension; ++usY)
			{
				map<unsigned short, unsigned short>::const_iterator cit = this->m_mapQueens.find(usX);
				if (cit != this->m_mapQueens.end() && cit->second == usY)
				{
					cout << "1 ";
				}
				else
				{
					cout << "0 ";
				}
			}
			cout << endl;
		}
	}

	void CEightQueens::PutChess(unsigned short usRow)
	{
		if (usRow < this->m_usDimension)
		{
			for (unsigned short usColumn = 0; usColumn < this->m_usDimension; ++usColumn)
			{
				this->m_mapQueens[usRow] = usColumn;
				if (!Attack(usRow))
				{
					if (this->m_usDimension - 1 == usRow)
					{
						this->Display();
					}
					else
					{
						this->PutChess(usRow + 1);
					}
				}
			}
		}
	}
}
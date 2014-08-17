#ifndef MYALGORITHM_EIGHT_QUEENS_H
#define MYALGORITHM_EIGHT_QUEENS_H

#include <map>

namespace MyAlgorithm
{
	using std::map;

	class CEightQueens
	{
	public:
		CEightQueens(unsigned short usDimension = 8);
	private:
		//禁止复制和赋值
		CEightQueens(const CEightQueens&);
		CEightQueens& operator =(const CEightQueens&);

		bool Attack(unsigned short);									//判断某行的皇后是否能够攻击其之前行中的皇后
		void Display(void);												//显示棋盘
		void PutChess(unsigned short usRow);					//在某行放置棋子
		map<unsigned short, unsigned short> m_mapQueens;		//存在皇后的位置<行，列>
		const unsigned short m_usDimension;						//维数
		unsigned int m_uiCount;										//计数器
	};
}

#endif
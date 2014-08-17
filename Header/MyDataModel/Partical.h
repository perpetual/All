#ifndef MYDATAMODEL_PARTICAL_H
#define MYDATAMODEL_PARTICAL_H

namespace MyDataStructure
{
	//点类
	template <typename T>
	class CPartical
	{
	public:
		CPartical(T tX = 0, T tY = 0, size_t szWeight = 0) :
		  m_tX(tX),
		  m_tY(tY),
		  m_szWeight(szWeight)
		  {}

		T m_tX;			//横坐标
		T m_tY;			//纵坐标
		size_t m_szWeight;			//权重
	};
}

#endif
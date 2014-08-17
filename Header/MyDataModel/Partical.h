#ifndef MYDATAMODEL_PARTICAL_H
#define MYDATAMODEL_PARTICAL_H

namespace MyDataStructure
{
	//����
	template <typename T>
	class CPartical
	{
	public:
		CPartical(T tX = 0, T tY = 0, size_t szWeight = 0) :
		  m_tX(tX),
		  m_tY(tY),
		  m_szWeight(szWeight)
		  {}

		T m_tX;			//������
		T m_tY;			//������
		size_t m_szWeight;			//Ȩ��
	};
}

#endif
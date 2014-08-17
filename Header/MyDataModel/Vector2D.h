#ifndef MYDATAMODEL_VECTOR_2D_H
#define MYDATAMODEL_VECTOR_2D_H

#include <utility>
#include "Segment.h"

namespace MyDataStructure
{
	using std::pair;
	using std::make_pair;

	//二维向量
	class CVector2D : public CSegment
	{
	public:
		//第一个参数是向量的起点
		//下一个参数是向量的终点
		CVector2D(void);

		//第一个参数是向量的起点
		//下一个参数是向量的终点
		template <typename T>
		CVector2D(const CPartical<T>&, const CPartical<T>&);

		//第一个参数是向量的横坐标
		//下一个参数是向量的纵坐标
		template <typename T>
		CVector2D(const T&, const T&);

		CVector2D operator +(const CVector2D&) const;
	};

	template <typename T>
	CVector2D::CVector2D(const CPartical<T>& ptStart, const CPartical<T>& ptEnd) :
		CSegment(CPartical<T>(0, 0, ptStart.m_szWeight), CPartical<T>(ptEnd.m_tX - ptStart.m_tX, ptEnd.m_tY - ptStart.m_tY, ptEnd.m_szWeight))
	{}

	template <typename T>
	CVector2D::CVector2D(const T& tX, const T& tY) :
		CSegment(CPartical<T>(0, 0), CPartical<T>(tX, tY))
	{}
}

#endif
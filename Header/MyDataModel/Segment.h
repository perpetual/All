#ifndef MYDATAMODEL_SEGMENT_H
#define MYDATAMODEL_SEGMENT_H

#include "Partical.h"
#include <complex>

namespace MyDataStructure
{
	using std::sqrt;

	extern double dMinDiff;

	//线段类
	class CSegment
	{
	public:
		template <typename T>
		CSegment(const CPartical<T>&, const CPartical<T>&);

		//获取起点
		template <typename T>
		CPartical<T> GetStart(void) const;

		//获取终点
		template <typename T>
		CPartical<T> GetEnd(void) const;

		//线段长度
		template <typename T>
		static double GetLength(const T&, const T&, const T&, const T&);
		template <typename T>
		static double GetLength(const CPartical<T>&, const CPartical<T>&);
		double GetLength(void) const;

		//点到线段的距离
		template <typename T>
		double GetDistance(const CPartical<T>&) const;

		//判断点是否在线段上
		template <typename T>
		bool IsInSegment(const CPartical<T>&) const;

		//获取中点
		template <typename T>
		CPartical<double> GetMid(void) const;

		//获取斜率
		double GetSlope(void) const;

		//获取偏转角
		double GetAngle(void) const;

		CPartical<double> m_ptStart;
		CPartical<double> m_ptEnd;
	};

	template <typename T>
	CSegment::CSegment(const CPartical<T>& ptStart, const CPartical<T>& ptEnd) :
		m_ptStart(ptStart.m_tX, ptStart.m_tY, ptStart.m_szWeight),
		m_ptEnd(ptEnd.m_tX, ptEnd.m_tY, ptEnd.m_szWeight)
	{}

	template <typename T>
	double CSegment::GetLength(const T& tX1, const T& tY1, const T& tX2, const T& tY2)
	{		
		return sqrt(pow(static_cast<double>(tX1 > tX2 ? tX1 - tX2 : tX2 - tX1), 2)
							+ pow(static_cast<double>(tY1 > tY2 ? tY1 - tY2 : tY2 - tY1), 2));
	}

	template <typename T>
	double CSegment::GetLength(const CPartical<T>& ptStart, const CPartical<T>& ptEnd)
	{
		return GetLength(ptStart.m_tX, ptStart.m_tY, ptEnd.m_tX, ptEnd.m_tY);
	}

	template <typename T>
	double CSegment::GetDistance(const CPartical<T>& pt) const
	{
		//利用海伦公式求组成的三角形面积
		double dSide1 = this->GetLength(pt, this->m_ptStart);
		double dSide2 = this->GetLength(pt, this->m_ptEnd);
		double dSide3 = this->GetLength();
		double dHelen = (dSide1 + dSide2 + dSide3) / 2.0;
		double dArea = sqrt(dHelen * (dHelen - dSide1) * (dHelen - dSide2) * (dHelen - dSide3));
		return dSide3 > 0 ? (2 * dArea) / dSide3 : this->GetLength(pt, this->m_ptStart);
	}

	template <typename T>
	bool CSegment::IsInSegment(const CPartical<T>& pt) const
	{
		if (0 == this->GetDistance(pt))
		{
			return (this->m_ptStart.m_tX < this->m_ptEnd.m_tX) ? (pt.m_tX >= this->m_ptStart.m_tX && pt.m_tX <= this->m_ptEnd.m_tX) : (pt.m_tX <= this->m_ptStart.m_tX && pt.m_tX >= this->m_ptEnd.m_tX);
		}
		else
		{
			return false;
		}
	}

	template <typename T>
	CPartical<double> CSegment::GetMid(void) const
	{
		return CPartical<double>((this->m_ptStart.m_tX + this->m_ptEnd.m_tX) / 2.0, (this->m_ptStart.m_tY + this->m_ptEnd.m_tY) / 2.0);
	}
}

#endif
#include "MyDataModel/Vector2D.h"

namespace MyDataStructure
{
	CVector2D::CVector2D(void) :
		CSegment(CPartical<double>(0, 0), CPartical<double>(0, 0))
	{}

	CVector2D CVector2D::operator +(const CVector2D& vec2D) const
	{
		return CVector2D(this->m_ptEnd.m_tX + vec2D.m_ptEnd.m_tX, this->m_ptEnd.m_tY + vec2D.m_ptEnd.m_tY);
	}
}
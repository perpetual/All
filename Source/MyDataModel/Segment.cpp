#include "MyDataModel/Segment.h"
#include "MyTools/MyTools.h"

namespace MyDataStructure
{
	using MyTools::PI;

	double dMinDiff = 0.001;

	double CSegment::GetLength(void) const
	{
		return GetLength(this->m_ptStart, this->m_ptEnd);
	}

	double CSegment::GetSlope(void) const
	{
		double tDiffY = this->m_ptEnd.m_tY - this->m_ptStart.m_tY;
		double tDiffX = this->m_ptEnd.m_tX - this->m_ptStart.m_tX;

		if (tDiffX < dMinDiff && tDiffX > -dMinDiff)
		{
			return tDiffY * (HUGE_VAL);
		}
		else
		{
			return tDiffY / tDiffX;
		}
	}

	double CSegment::GetAngle(void) const
	{
		return this->m_ptEnd.m_tY < this->m_ptStart.m_tY ? atan(this->GetSlope()) + PI : atan(this->GetSlope());
	}
}
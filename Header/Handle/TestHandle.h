#ifndef HANDLE_TEST_HANDLE_H
#define HANDLE_TEST_HANDLE_H

#include "BaseObject.h"
#include "Handle.h"

namespace Handle
{
	class CPoint : public CBaseObject
	{
	public:
		CPoint(void) : m_iX(0), m_iY(0) {}
		CPoint(int x, int y) : m_iX(x), m_iY(y) {}
		int X(void) const {return this->m_iX;}
		int Y(void) const {return this->m_iY;}
		CPoint& X(int x) {this->m_iX = x; return *this;}
		CPoint& Y(int y) {this->m_iY = y; return *this;}

	private:
		int m_iX;
		int m_iY;
	};

	class CPointHandle : public CHandle<CPoint>
	{
	public:
		CPointHandle(void) {m_pBase = new CPoint;}
		CPointHandle(int iX, int iY) {this->m_pBase = new CPoint(iX, iY);}
		CPointHandle(const CPoint& obj) {this->m_pBase = new CPoint(obj);}

		int X(void) const {return this->m_pBase->X();}
		CPointHandle& X(int iX)
		{
			if (this->m_oUseCount.MakeOnly())
			{
				this->m_pBase = new CPoint(*this->m_pBase);
			}
			this->m_pBase->X(iX);
			return *this;
		}
		int Y(void) const {return this->m_pBase->Y();}
		CPointHandle& Y(int iY) {this->m_pBase->Y(iY); return *this;}
	};
}

#endif
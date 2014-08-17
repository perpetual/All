#include <cstring>
#include "Picture/Picture.h"
#include "MyTools/MyUtilityTools.h"

namespace Picture
{
	CPicture::CPicture(unsigned int uiHeight, unsigned int uiWidth) : m_uiHeight(uiHeight), m_uiWidth(uiWidth), m_pData(new char[uiHeight * uiWidth]) {this->Clear();}

	CPicture::CPicture(const char* const* ppArray, unsigned int uiRow)
	{
		unsigned int uiMax = 0;

		for (unsigned int ui = 0; ui < uiRow; ++ui)
		{
			uiMax = MyTools::Max(uiMax, strlen(ppArray[ui]));
		}

		this->m_uiHeight = uiRow;
		this->m_uiWidth = uiMax;
		this->m_pData = new char[this->m_uiHeight * this->m_uiWidth];

		for (unsigned int ui = 0; ui < uiRow; ++ui)
		{
			unsigned int uiCount = 0;

			while (uiCount < strlen(ppArray[ui]))
			{
				this->Position(ui, uiCount) = ppArray[ui][uiCount];
				++uiCount;
			}
			while (uiCount < this->m_uiWidth)
			{
				this->Position(ui, uiCount++) = ' ';
			}
		}
	}

	CPicture::CPicture(const CPicture& pic) : m_uiHeight(pic.m_uiHeight), m_uiWidth(pic.m_uiWidth), m_pData(new char[pic.m_uiHeight * pic.m_uiWidth])
	{
		this->CopyBlock(0, 0, pic);
	}

	CPicture::~CPicture(void) {delete[] this->m_pData;}

	CPicture& CPicture::operator =(const CPicture& pic)
	{
		if (&pic != this)
		{
			delete[] this->m_pData;
			this->m_uiHeight = pic.m_uiHeight;
			this->m_uiWidth = pic.m_uiWidth;
			this->m_pData = new char[this->m_uiHeight * this->m_uiWidth];
			this->CopyBlock(0, 0, pic);
		}
		return *this;
	}

	void CPicture::CopyBlock(unsigned int uiHeight, unsigned int uiWidth, const CPicture& pic)
	{
		for (unsigned int uiI = 0; uiI < pic.m_uiHeight; ++uiI)
		{
			for (unsigned int uiJ = 0; uiJ < pic.m_uiWidth; ++uiJ)
			{
				this->Position(uiHeight + uiI, uiWidth + uiJ) = pic.Position(uiI, uiJ);
			}
		}
	}

	void CPicture::Clear(void)
	{
		for (unsigned int uiI = 0; uiI < this->m_uiHeight; ++uiI)
		{
			for (unsigned int uiJ = 0; uiJ < this->m_uiWidth; ++uiJ)
			{
				this->Position(uiI, uiJ) = ' ';
			}
		}
	}

	ostream& operator <<(ostream& oStream, const CPicture& pic)
	{
		for (unsigned int uiI = 0; uiI < pic.m_uiHeight; ++uiI)
		{
			for (unsigned int uiJ = 0; uiJ < pic.m_uiWidth; ++uiJ)
			{
				oStream << pic.Position(uiI, uiJ);
			}
			oStream << endl;
		}
		return oStream;
	}

	CPicture Frame(const CPicture& pic)
	{
		CPicture picDst(pic.m_uiHeight + 2, pic.m_uiWidth + 2);

		for (unsigned int uiI = 1; uiI < picDst.m_uiHeight - 1; ++uiI)
		{
			picDst.Position(uiI, 0) = '|';
			picDst.Position(uiI, picDst.m_uiWidth - 1) = '|';
		}

		for (unsigned int uiI = 1; uiI < picDst.m_uiWidth - 1; ++uiI)
		{
			picDst.Position(0, uiI) = '-';
			picDst.Position(picDst.m_uiHeight - 1, uiI) = '-';
		}

		picDst.Position(0, 0) = '+';
		picDst.Position(0, picDst.m_uiWidth - 1) = '+';
		picDst.Position(picDst.m_uiHeight - 1, 0) = '+';
		picDst.Position(picDst.m_uiHeight - 1, picDst.m_uiWidth - 1) = '+';

		picDst.CopyBlock(1, 1, pic);
		return picDst;
	}

	CPicture operator &(const CPicture& picUp, const CPicture& picDown)
	{
		CPicture picDst(picUp.m_uiHeight + picDown.m_uiHeight, MyTools::Max(picUp.m_uiWidth, picDown.m_uiWidth));

		picDst.CopyBlock(0, 0, picUp);
		picDst.CopyBlock(picUp.m_uiHeight, 0, picDown);
		return picDst;
	}

	CPicture operator |(const CPicture& picLeft, const CPicture& picRight)
	{
		CPicture picDst(MyTools::Max(picLeft.m_uiHeight, picRight.m_uiHeight), picLeft.m_uiWidth + picRight.m_uiWidth);

		picDst.CopyBlock(0, 0, picLeft);
		picDst.CopyBlock(0, picLeft.m_uiWidth, picRight);

		return picDst;
	}
}
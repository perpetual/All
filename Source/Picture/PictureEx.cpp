#include <cstring>
#include "Picture/PictureEx.h"

namespace Picture
{
	void DisplayPad(ostream& oStream, unsigned int uiX, unsigned int uiY)
	{
		for (unsigned int ui = uiX; ui < uiY; ++ui)
		{
			oStream << ' ';
		}
	}

	///////////////////////////////CPictureEx的实现/////////////////////////////////////////
	CPictureEx::CPictureEx(const char* const* ppArray, unsigned int uiHeight)
	{
		this->m_pBase = new CStringPicture(ppArray, uiHeight);
	}

	CPictureEx Frame(const CPictureEx& pic)
	{
		return new CFramePicture(pic);
	}

	CPictureEx Reframe(const CPictureEx& pic, char c, char s, char t)
	{
		return pic.m_pBase->Reframe(c, s, t);
	}

	CPictureEx::CPictureEx(CBasePictureEx* pBaseObject)
	{
		this->m_pBase = pBaseObject;
	}

	ostream& operator <<(ostream& oStream, const CPictureEx& pic)
	{
		unsigned int uiHeight = pic.Height();

		for (unsigned int ui = 0; ui < uiHeight; ++ui)
		{
			pic.Display(oStream, ui, pic.Width());
			oStream << endl;
		}
		return oStream;
	}

	///////////////////////////////CStringPicture的实现///////////////////////////////////////////
	CStringPicture::CStringPicture(const char* const* pArray, unsigned int uiHeight) : m_size(uiHeight)
	{
		for (unsigned int uiRow = 0; uiRow < uiHeight; ++uiRow)
		{
			this->m_pBase.push_back(pArray[uiRow]);
		}
	}

	unsigned int CStringPicture::Width(void) const
	{
		unsigned int uiMax = 0;

		for (unsigned int ui = 0; ui < this->m_size; ++ui)
		{
			uiMax = MyTools::Max(uiMax, this->m_pBase[ui].length());
		}
		return uiMax;
	}

	void CStringPicture::Display(ostream& oStream, unsigned int uiRow, unsigned int uiWidth) const
	{
		unsigned int uiStart = 0;

		if (uiRow >= 0 && uiRow < this->Height())
		{
			oStream << this->m_pBase[uiRow];
			uiStart = this->m_pBase[uiRow].length();
		}
		DisplayPad(oStream, uiStart, uiWidth);
	}

	//////////////////////////////CFramePicture的实现////////////////////////////////////////////
	CFramePicture::CFramePicture(const CPictureEx& pic, char c, char s, char t) : m_pic(pic), m_cCorner(c), m_cSideBorder(s), m_cTopBorder(t) {}

	void CFramePicture::Display(ostream& oStream, unsigned int uiRow, unsigned int uiWidth) const
	{
		if (uiRow >= this->Height())		//越界
		{
			DisplayPad(oStream, 0, uiWidth);
		}
		else
		{
			if (0 == uiRow || this->Height() - 1 == uiRow)		//顶框和底框
			{
				oStream << this->m_cCorner;
				for (unsigned int ui = 0; ui < this->m_pic.Width(); ++ui)
				{
					oStream << this->m_cTopBorder;
				}
				oStream << this->m_cCorner;
			}
			else		//内部行
			{
				oStream << this->m_cSideBorder;
				this->m_pic.Display(oStream, uiRow - 1, this->m_pic.Width());
				oStream << this->m_cSideBorder;
			}
			DisplayPad(oStream, this->Width(), uiWidth);
		}
	}

	CPictureEx CFramePicture::Reframe(char c, char s, char t)
	{
		return new CFramePicture(this->m_pic, c, s, t);
	}

	//////////////////////////////CVCatPicture的实现////////////////////////////////////////////
	void CVCatPicture::Display(ostream& oStream, unsigned int uiRow, unsigned int uiWidth) const
	{
		if (uiRow >=0 && uiRow < this->m_picTop.Height())
		{
			this->m_picTop.Display(oStream, uiRow, uiWidth);
		}else if (uiRow < this->m_picTop.Height() + this->m_picBottom.Height())
		{
			this->m_picBottom.Display(oStream, uiRow - this->m_picTop.Height(), uiWidth);
		}
		else
		{
			DisplayPad(oStream, 0, uiWidth);
		}
	}

	CPictureEx CVCatPicture::Reframe(char c, char s, char t)
	{
		return new CVCatPicture(Picture::Reframe(this->m_picTop, c, s, t), Picture::Reframe(this->m_picBottom, c, s, t));
	}

	CPictureEx operator &(const CPictureEx& picTop, const CPictureEx& picBottom)
	{
		return new CVCatPicture(picTop, picBottom);
	}

	///////////////////////////////CHCatPicture的实现///////////////////////////////////////////
	void CHCatPicture::Display(ostream& oStream, unsigned int uiRow, unsigned int uiWidth) const
	{
		this->m_picLeft.Display(oStream, uiRow, this->m_picLeft.Width());
		this->m_picRight.Display(oStream, uiRow, this->m_picRight.Width());
		DisplayPad(oStream, this->Width(), uiWidth);
	}

	CPictureEx CHCatPicture::Reframe(char c, char s, char t)
	{
		return new CHCatPicture(Picture::Reframe(this->m_picLeft, c, s, t), Picture::Reframe(this->m_picRight, c, s, t));
	}

	CPictureEx operator |(const CPictureEx& picLeft, const CPictureEx& picRight)
	{
		return new CHCatPicture(picLeft, picRight);
	}
}
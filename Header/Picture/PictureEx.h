#ifndef PICTURE_PICTUREEX_H
#define PICTURE_PICTUREEX_H

#include <iostream>
#include <vector>
#include <string>
#include "Handle/Handle.h"
#include "MyTools/MyUtilityTools.h"

namespace Picture
{
	using std::ostream;
	using MyTools::Max;

	class CPictureEx;

	class CBasePictureEx : public Handle::CBaseObject
	{
		friend class CPictureEx;
		friend CPictureEx Reframe(const CPictureEx&, char, char, char);
	protected:
		virtual unsigned int Height(void) const = 0;
		virtual unsigned int Width(void) const = 0;
		//第二、三个参数分别是图像的行序号和该行的宽度
		virtual void Display(ostream&, unsigned int, unsigned int) const = 0;
		//第一个参数表示拐角的符号
		//第二个参数表示纵向的符号
		//第三个参数表示横向的符号
		virtual CPictureEx Reframe(char = '+', char = '|', char = '-') = 0;
	};

	//向流中输出第三个参数-第二个参数个空格
	void DisplayPad(ostream&, unsigned int, unsigned int);

	class CPictureEx : public Handle::CHandle<CBasePictureEx, false>
	{
		friend ostream& operator <<(ostream&, const CPictureEx&);
		friend CPictureEx Frame(const CPictureEx&);
		friend CPictureEx Reframe(const CPictureEx&, char, char, char);
		friend CPictureEx operator &(const CPictureEx&, const CPictureEx&);
		friend CPictureEx operator |(const CPictureEx&, const CPictureEx&);

		friend class CStringPicture;
		friend class CFramePicture;
		friend class CHCatPicture;
		friend class CVCatPicture;
	public:
		CPictureEx(void) {this->m_pBase = NULL;}
		//第二个参数是字符数组的行数
		CPictureEx(const char* const*, unsigned int);

	private:
		CPictureEx(CBasePictureEx*);
		unsigned int Height(void) const {return this->m_pBase->Height();}
		unsigned int Width(void) const {return this->m_pBase->Width();}
		void Display(ostream& oStream, unsigned int uiRow, unsigned int uiWidth) const {this->m_pBase->Display(oStream, uiRow, uiWidth);}
	};

	class CStringPicture : public CBasePictureEx
	{
		friend class CPictureEx;

		CStringPicture(const char* const*, unsigned int);

		unsigned int Height(void) const {return this->m_size;}
		unsigned int Width(void) const;
		void Display(ostream&, unsigned int, unsigned int) const;
		CPictureEx Reframe(char, char, char) {return new CStringPicture(*this);}

		std::vector<std::string> m_pBase;
		size_t m_size;
	};

	class CFramePicture : public CBasePictureEx
	{
		friend CPictureEx Frame(const CPictureEx&);

		CFramePicture(const CPictureEx& pic, char = '+', char = '|', char = '-');

		unsigned int Height(void) const {return this->m_pic.Height() + 2;};
		unsigned int Width(void) const {return this->m_pic.Width() + 2;};
		void Display(ostream&, unsigned int, unsigned int) const;
		CPictureEx Reframe(char, char, char);

		CPictureEx m_pic;
		char m_cCorner;
		char m_cSideBorder;
		char m_cTopBorder;
	};

	CPictureEx Frame(const CPictureEx&);
	CPictureEx Reframe(const CPictureEx&, char = '+', char = '|', char = '-');

	class CVCatPicture : public CBasePictureEx
	{
		friend CPictureEx operator &(const CPictureEx&, const CPictureEx&);

		CVCatPicture(const CPictureEx& picTop, const CPictureEx& picBottom) : m_picTop(picTop), m_picBottom(picBottom) {}

		unsigned int Height(void) const {return this->m_picTop.Height() + this->m_picBottom.Height();}
		unsigned int Width(void) const {return MyTools::Max(this->m_picTop.Width(), this->m_picBottom.Width());}
		void Display(ostream&, unsigned int, unsigned int) const;
		CPictureEx Reframe(char, char, char);

		CPictureEx m_picTop, m_picBottom;
	};

	CPictureEx operator &(const CPictureEx& picTop, const CPictureEx& picBottom);

	class CHCatPicture : public CBasePictureEx
	{
		friend CPictureEx operator |(const CPictureEx&, const CPictureEx&);

		CHCatPicture(const CPictureEx& picLeft, const CPictureEx& picRight) : m_picLeft(picLeft), m_picRight(picRight) {}

		unsigned int Height(void) const {return MyTools::Max(this->m_picLeft.Height(), this->m_picRight.Height());}
		unsigned int Width(void) const {return this->m_picLeft.Width() + this->m_picRight.Width();}
		void Display(ostream&, unsigned int, unsigned int) const;
		CPictureEx Reframe(char, char, char);

		CPictureEx m_picLeft, m_picRight;
	};

	CPictureEx operator |(const CPictureEx& picLeft, const CPictureEx& picRight);

	ostream& operator <<(ostream&, const CPictureEx&);
}

#endif
#ifndef PICTURE_PICTURE_H
#define PICTURE_PICTURE_H

#include <iostream>

namespace Picture
{
	using std::ostream;

	class CPicture
	{
		friend ostream& operator <<(ostream&, const CPicture&);
		friend CPicture Frame(const CPicture&);
		friend CPicture operator &(const CPicture&, const CPicture&);
		friend CPicture operator |(const CPicture&, const CPicture&);
	public:
		//第一个参数是图像的高度
		//下一个参数是图像的宽度
		CPicture(unsigned int = 0, unsigned int = 0);
		//第二个参数是字符数组的行数
		CPicture(const char* const*, unsigned int);
		CPicture(const CPicture&);
		~CPicture(void);

		CPicture& operator =(const CPicture&);

	private:
		char& Position(unsigned int row, unsigned int col) {return this->m_pData[row * this->m_uiWidth + col];}
		char Position(unsigned int row, unsigned int col) const {return this->m_pData[row * this->m_uiWidth + col];}
		//将源图像拷贝至目标图像的指定位置
		void CopyBlock(unsigned int, unsigned int, const CPicture&);
		//清空图像
		void Clear(void);

		unsigned int m_uiHeight, m_uiWidth;
		char* m_pData;
	};

	ostream& operator <<(ostream&, const CPicture&);

	//为字符画加边框
	CPicture Frame(const CPicture&);
	CPicture operator &(const CPicture&, const CPicture&);
	CPicture operator |(const CPicture&, const CPicture&);
}

#endif
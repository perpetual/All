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
		//��һ��������ͼ��ĸ߶�
		//��һ��������ͼ��Ŀ��
		CPicture(unsigned int = 0, unsigned int = 0);
		//�ڶ����������ַ����������
		CPicture(const char* const*, unsigned int);
		CPicture(const CPicture&);
		~CPicture(void);

		CPicture& operator =(const CPicture&);

	private:
		char& Position(unsigned int row, unsigned int col) {return this->m_pData[row * this->m_uiWidth + col];}
		char Position(unsigned int row, unsigned int col) const {return this->m_pData[row * this->m_uiWidth + col];}
		//��Դͼ�񿽱���Ŀ��ͼ���ָ��λ��
		void CopyBlock(unsigned int, unsigned int, const CPicture&);
		//���ͼ��
		void Clear(void);

		unsigned int m_uiHeight, m_uiWidth;
		char* m_pData;
	};

	ostream& operator <<(ostream&, const CPicture&);

	//Ϊ�ַ����ӱ߿�
	CPicture Frame(const CPicture&);
	CPicture operator &(const CPicture&, const CPicture&);
	CPicture operator |(const CPicture&, const CPicture&);
}

#endif
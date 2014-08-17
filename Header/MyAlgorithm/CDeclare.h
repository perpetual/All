#ifndef MYALGORITHM_C_DECLARE_H
#define MYALGORITHM__DECLARE_H

#include <string>
#include <iostream>
#include <sstream>
#include "Stack.h"

namespace MyAlgorithm
{
    using std::string;
	using std::ostream;

    //��C������������Ϊ��Ȼ����
    class CCDeclare
	{
		friend ostream& operator <<(ostream&, const CCDeclare&);
		//���
		struct TToken
		{
			char m_cType;
			string m_str;
		};

		//�������
		enum ETypeTag
		{
			IDENTIFIER,
			QUALIFIER,
			TYPE
		};
	public:
		CCDeclare(const string&);

	private:
		//������з������̵Ĵ����
		void ReadFirstIdentifer(void);

		//������������
		void DealDeclarator(void);

		//��ֹ���ƺ͸�ֵ
		CCDeclare(const CCDeclare&);
		CCDeclare& operator =(const CCDeclare&);

		//�ƶϱ�ʶ��������
		enum ETypeTag ClassifyString(void);

		//��ȡ��һ�����
		void GetToken(void);

		//��������
		void DealArray(void);

		//����������
		void DealFunctionArgs(void);

		//����ָ��
		void DealPointers(void);

		TToken m_tCur;	//��ǰ
		CLinkStack<TToken> m_stk;
		std::istringstream m_inStream;
		string m_strResult;
	};

	ostream& operator <<(ostream&, const CCDeclare&);
}

#endif
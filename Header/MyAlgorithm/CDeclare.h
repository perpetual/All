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

    //将C语言声明解释为自然语言
    class CCDeclare
	{
		friend ostream& operator <<(ostream&, const CCDeclare&);
		//标记
		struct TToken
		{
			char m_cType;
			string m_str;
		};

		//标记类型
		enum ETypeTag
		{
			IDENTIFIER,
			QUALIFIER,
			TYPE
		};
	public:
		CCDeclare(const string&);

	private:
		//理解所有分析过程的代码段
		void ReadFirstIdentifer(void);

		//处理整个声明
		void DealDeclarator(void);

		//禁止复制和赋值
		CCDeclare(const CCDeclare&);
		CCDeclare& operator =(const CCDeclare&);

		//推断标识符的类型
		enum ETypeTag ClassifyString(void);

		//读取下一个标记
		void GetToken(void);

		//处理数组
		void DealArray(void);

		//处理函数参数
		void DealFunctionArgs(void);

		//处理指针
		void DealPointers(void);

		TToken m_tCur;	//当前
		CLinkStack<TToken> m_stk;
		std::istringstream m_inStream;
		string m_strResult;
	};

	ostream& operator <<(ostream&, const CCDeclare&);
}

#endif
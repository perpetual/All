#include <cctype>
#include "MyAlgorithm/CDeclare.h"
#include "MyTools/MyUtilityTools.h"

namespace MyAlgorithm
{
	using std::cin;
	using std::cout;
	using MyTools::StringToUInt;
	using std::ends;

	CCDeclare::CCDeclare(const string& str) :
		m_inStream(str)
	{
		this->m_strResult.clear();
		this->ReadFirstIdentifer();
		this->DealDeclarator();
	}

	void CCDeclare::DealDeclarator(void)
	{
		switch (this->m_tCur.m_cType)
		{
		case '[':
			this->DealArray();
			break;
		case '(':
			this->DealFunctionArgs();
			break;
		}

		this->DealPointers();

		//处理栈中的标记
		while (!this->m_stk.IsEmpty())
		{
			if ('(' == this->m_stk.Top().m_cType)
			{
				this->m_stk.Pop();
				this->GetToken();
				this->DealDeclarator();
			}
			else
			{
				this->m_strResult += this->m_stk.Top().m_str + ' ';
				this->m_stk.Pop();
			}
		}
	}

	CCDeclare::ETypeTag CCDeclare::ClassifyString(void)
	{
		if ("const" == this->m_tCur.m_str)
		{
			this->m_tCur.m_str = " read_only ";
			return QUALIFIER;
		} else if ("volatile" == this->m_tCur.m_str)
		{
			return QUALIFIER;
		}else if ("void" == this->m_tCur.m_str
					|| "char" == this->m_tCur.m_str
					|| "signed" == this->m_tCur.m_str
					|| "unsigned" == this->m_tCur.m_str
					|| "short" == this->m_tCur.m_str
					|| "int" == this->m_tCur.m_str
					|| "long" == this->m_tCur.m_str
					|| "float" == this->m_tCur.m_str
					|| "double" == this->m_tCur.m_str
					|| "struct" == this->m_tCur.m_str
					|| "union" == this->m_tCur.m_str
					|| "enum" == this->m_tCur.m_str)
		{
			return TYPE;
		}else
		{
			return IDENTIFIER;
		}
	}

	void CCDeclare::GetToken(void)
	{
		char ch = '\0';

		//跳过空白
		while (this->m_inStream.get(ch), ' ' == ch);

		if (isalnum(ch))
		{
			this->m_tCur.m_str.clear();
			//读入以字母或数字开头的标识符
			while (this->m_tCur.m_str += ch, this->m_inStream.get(ch), isalnum(ch));
			this->m_inStream.putback(ch);
			this->m_tCur.m_cType = static_cast<char>(this->ClassifyString());
		}else if ('*' == ch)
		{
			this->m_tCur.m_str = "pointer to ";
			this->m_tCur.m_cType = '*';
		}else
		{
			this->m_tCur.m_str.resize(1);
			this->m_tCur.m_cType = ch;
		}
	}

	void CCDeclare::ReadFirstIdentifer(void)
	{
		this->GetToken();
		while (IDENTIFIER != this->m_tCur.m_cType)
		{
			this->m_stk.Push(this->m_tCur);
			this->GetToken();
		}
		this->m_strResult += this->m_tCur.m_str + " is ";
		this->GetToken();
	}

	void CCDeclare::DealArray(void)
	{
		while ('[' == this->m_tCur.m_cType)
		{
			this->m_strResult += " array ";
			this->GetToken();
			if (isdigit(this->m_tCur.m_str[0]))
			{
				this->m_strResult += " 0... " + StringToUInt(this->m_tCur.m_str) + ' ';
				this->GetToken();
			}
			this->GetToken();
			this->m_strResult += " of ";
		}
	}

	void CCDeclare::DealFunctionArgs(void)
	{
		while (')' != this->m_tCur.m_cType)
		{
			this->GetToken();
		}
		this->GetToken();
		this->m_strResult == " function returning " + ' ';
	}

	void CCDeclare::DealPointers(void)
	{
		while ('*' == this->m_stk.Top().m_cType)
		{
			this->m_strResult += this->m_stk.Top().m_str + ' ';
			this->m_stk.Pop();
		}
	}

	ostream& operator <<(ostream& o, const CCDeclare& obj)
	{
		return o << obj.m_strResult;
	}
}

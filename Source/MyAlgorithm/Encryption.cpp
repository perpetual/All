#include <iostream>
#include <algorithm>
#include "MyAlgorithm/Encryption.h"
#include "MyTools/MyUtilityTools.h"
#include "MyTools/MyFunctional.h"

namespace MyAlgorithm
{
	using std::unique;
	using MyTools::Unique;
	using MyTools::CToUpper;

	class CConversion
	{
	public:
		CConversion(const map<char, char>& mapCodeBook) :
		  m_mapConversionBook(mapCodeBook)
		  {}

		  void operator () (char& c) const
		  {
			  map<char, char>::const_iterator cit = this->m_mapConversionBook.find(c);

			  if (this->m_mapConversionBook.end() != cit)
			  {
				  c = cit->second;
			  }
		  }

	private:
		//禁止赋值
		CConversion& operator =(const CConversion&);
		const map<char, char>& m_mapConversionBook;
	};

	CEncryption::CEncryption(const string& str, const string& strCipher) :
		m_str(str)
	{
		string strNewCipher(strCipher);
		char ch = 'A';

		for_each(strNewCipher.begin(), strNewCipher.end(), CToUpper());
		strNewCipher = Unique(strNewCipher);
		if (str.length() < strNewCipher.length())
		{
			strNewCipher = strNewCipher.substr(0, str.length());
		}

		//构造密码本
		for (string::const_iterator citChar = strNewCipher.begin(); citChar != strNewCipher.end(); ++citChar)
		{
			if (isalpha(*citChar))
			{
				this->m_mapCodeBook[ch] = *citChar;
				this->m_mapRCodeBook[*citChar] = ch;
				++ch;
			}
		}

		for (char chr = 'A'; chr <= 'Z'; ++chr)
		{
			if (string::npos == strNewCipher.find(chr))
			{
				this->m_mapCodeBook[ch] = chr;
				this->m_mapRCodeBook[chr] = ch;
				++ch;
			}
		}
	}

	string CEncryption::Encrypt(void)
	{
		for_each(this->m_str.begin(), this->m_str.end(), CConversion(this->m_mapCodeBook));
		return this->m_str;
	}

	string CEncryption::Decrypt(void)
	{
		for_each(this->m_str.begin(), this->m_str.end(), CConversion(this->m_mapRCodeBook));
		return this->m_str;		
	}
}
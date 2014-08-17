#include "RegularExpression/RegularExpression.h"

namespace RegEx
{
	using std::string;
	using boost::cmatch;
	using boost::regex_match;

	CRegEx::CRegEx(const string& strRegEx, boost::regbase::flag_type_ eType) :
		m_regex(strRegEx, eType)
	{}

	vector<string> CRegEx::Parse(const string& str)
	{
		vector<string> vecRet;
		cmatch what;

		if (regex_match(str.data(), what, this->m_regex))
		{
			for (unsigned int ui = 0; ui < what.size(); ++ui)
			{
				vecRet.push_back(what[ui]);
			}
		}

		return vecRet;
	}
}
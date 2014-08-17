#ifndef REGEX_REGEX_H
#define REGEX_REGEX_H

#include "VersionControl.h"
#include <string>
#include <vector>
#include "Boost/boost/regex.hpp"
#include "Boost/boost/regex/v4/regbase.hpp"

namespace RegEx
{
	using std::string;
	using std::vector;
	using boost::regex;

	class CRegEx
	{
	public:
		//参数为正则表达式，默认采用per语法
		CRegEx(const string&, boost::regbase::flag_type_ = boost::regex::perl);

		//解析
		vector<string> Parse(const string&);
	private:
		regex m_regex;
	};
}

#endif
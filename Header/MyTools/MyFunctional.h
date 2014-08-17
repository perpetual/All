#ifndef MYTOOLS_FUNCTIONAL_H
#define MYTOOLS_FUNCTIONAL_H

#include <iostream>
#include <string>
#include <utility>

namespace MyTools
{
	using std::string;
	using std::pair;
	using std::cout;
	using std::endl;

	//将字母转换为大写
	class CToUpper
	{
	public:
		void operator ()(char& c);
	};

	//将字母转换为小写
	class CToLower
	{
	public:
		void operator ()(char& c);
	};

	//打印函数类
	class CDisplay
	{
	public:
		//参数为分隔符
		CDisplay(const string& strSeperator = " ") : m_strSeperator(strSeperator) {}
		template <typename T>
		void operator ()(const T t) const
		{
			cout << t << this->m_strSeperator;
		}
		template <typename T1, typename T2>
		void operator ()(const pair<T1, T2>& p) const
		{
			cout << '(' << p.first << ',' << p.second << ')' << this->m_strSeperator;
		}
	private:
		string m_strSeperator;
	};
}

#endif
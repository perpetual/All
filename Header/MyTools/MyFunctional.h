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

	//����ĸת��Ϊ��д
	class CToUpper
	{
	public:
		void operator ()(char& c);
	};

	//����ĸת��ΪСд
	class CToLower
	{
	public:
		void operator ()(char& c);
	};

	//��ӡ������
	class CDisplay
	{
	public:
		//����Ϊ�ָ���
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
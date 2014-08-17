#ifndef MY_UTILITY_TOOLS_H
#define MY_UTILITY_TOOLS_H

#include <VersionControl.h>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <sstream>
#include <utility>
#include <iomanip>
#include <typeinfo>
#include <iterator>

#ifdef __OS_VERSION_WINDOWS__
#include <conio.h>
#endif

namespace MyTools
{
	using std::string;
	using std::wstring;
	using std::ostringstream;
	using std::vector;
	using std::pair;
	using std::set;
	using std::hex;
	using std::oct;
	using std::uppercase;
	using std::ostream_iterator;
	using std::cout;
	using std::endl;
	using std::ends;

	//初始化各种环境
#ifdef __OS_VERSION_WINDOWS__
	//初始化COM库
	class CInitCom
	{
	protected:
		CInitCom(void);
		virtual ~CInitCom(void);
	};
#endif

	//清除字符串两端的空白字符
	string Trim(const char* const);
	wstring Trim(const wchar_t* const);
	string Trim(string str);
	wstring Trim(wstring str);

	//清除字符串中所有多余的空白字符
	string TrimAll(const char* const);
	wstring TrimAll(const wchar_t* const);
	string TrimAll(string str);
	wstring TrimAll(wstring str);

	//窄字符串转宽字符串
	wstring StrToWStr(const string&);

	//宽字符串转换为窄字符串
	string WStrToStr(const wstring&);

	//将数字转换为八进制字符串
	template<typename T>
	string NumberToOctString(T tVal)
	{
		ostringstream ostrstr;
		if (typeid(T) == typeid(char) || typeid(T) == typeid(unsigned char))
		{
			ostrstr << oct << static_cast<short>(tVal);
		}
		else
		{
			ostrstr << oct << tVal;
		}
		return ostrstr.str();
	}

	//将数字转换为十进制字符串
	template<typename T>
	string NumberToDecString(T tVal)
	{
		ostringstream ostrstr;
		if (typeid(T) == typeid(char) || typeid(T) == typeid(unsigned char))
		{
			ostrstr << static_cast<short>(tVal);
		}
		else
		{
			ostrstr << tVal;
		}
		return ostrstr.str();
	}

	//将数字转换为十六进制字符串
	template<typename T>
	string NumberToHexString(T tVal, bool bUppercase = false)
	{
		ostringstream ostrstr;

		bUppercase ? (ostrstr << uppercase, NULL) : NULL;
		if (typeid(T) == typeid(char) || typeid(T) == typeid(unsigned char))
		{
			ostrstr << hex << static_cast<short>(tVal);
		}
		else
		{
			ostrstr << hex << tVal;
		}
		return ostrstr.str();
	}

	//将字符串转换为数字
	typedef char byte;
	typedef unsigned char ubyte;

	char StringToChar(const string&);
	unsigned char StringToUChar(const string&);
	byte StringToByte(const string&);
	ubyte StringToUByte(const string&);
	short StringToShort(const string&);
	unsigned short StringToUShort(const string&);
	int StringToInt(const string&);
	unsigned int StringToUInt(const string&);
	long StringToLong(const string&);
	unsigned long StringToULong(const string&);
	long long StringToLongLong(const string&);
	unsigned long long StringToULongLong(const string&);
	float StringToFloat(const string&);
	double StringToDouble(const string&);
	long double StringToLDouble(const string&);

	//将字符串转换为数字

	//判断文件是否是正常文件
	bool IsFile(const string&);

	//判断是否是目录
	bool IsDirectory(const string&);

	//读取文件的全部内容
	string ReadWholeFile(const string&);

	//将字符写入文件
	//第一个参数是文件名
	//下一个参数是文件内容
	bool WriteWholeFile(const string&, const string&);

	//获取随机不重复的名字
	string GetRandomName(void);

	//删除指定的文件
	bool RemoveFile(const string&);

	//修改文件名
	//第一个参数是旧文件名
	//下一个参数是新文件名
	bool RenameFile(const string&, const string&);

	//阻塞线程
	void WaitForever(void);

	//用指定分隔符提取字符串
	//第一个参数是被提取的字符串
	//第二个是分隔符
	vector<string> SplitString(const string& str, const string& = " \t\f\r\v\n");

	//清除容器中重复的元素
	template <typename T>
	T Unique(T t)
	{
		T tRet;
		set<typename T::value_type> setVal;

		for (typename T::const_iterator cit = t.begin(); cit != t.end(); ++cit)
		{
			if (0 == setVal.count(*cit))
			{
				fill_n(back_inserter(tRet), 1, *cit);
				setVal.insert(*cit);
			}
		}

		return tRet;
	}

	//设置Windows时间
	bool SetSystemTime(time_t);

	//向string中添加二进制数据
	//下一个参数是需要添加数据的首地址
	//下一个参数是添加的长度
	string& AppendString(string&, const void*, unsigned int);

	//添加若干个字符
	string& AppendString(string&, char, unsigned int);

	//将一段内存内容以二进制的形式打印出来
	//第一个参数是内存首址
	//下一个参数是内存长度
	string PrintMemory(const void*, unsigned int);

	//获取指定目录下的所有文件名
	//第一个参数表示目录路径
	//下个参数表示是否读取目录
	//下一个参数表示是否递归获取
	//下一个参数表示是否获取隐藏文件
#ifdef __OS_VERSION_WINDOWS__
	//可以使用通配符
	vector<string> GetAllFileName(const string& = ".\\*", bool = false, bool = true, bool = false);
#elif defined (__OS_VERSION_LINUX__)
	vector<string> GetAllFileName(const string& = "./", bool = false, bool = true, bool = false);
#endif

	//打印容器中的元素
	//第一个参数是容器的引用
	//第二个参数是分隔符
	template <typename T>
	void PrintContainer(const T& t, char ch = ' ')
	{
		copy(t.begin(), t.end(), ostream_iterator<typename T::value_type>(cout, string(1, ch).c_str()));
		cout << endl;
	}

	//字符编码转换
	//第一个参数是需要转换文件的名称
	//下一个参数是源编码类型
	//下一个参数是目标编码类型
	//下一个参数是目标文件名称
	bool TransCode(const string&, const string&, const string&, const string&);

#ifdef __OS_VERSION_LINUX__
	int getch(void);
	int kbhit(void);
#endif

	//获取当前路径
	string GetCurrentPath(void);

	//获取最大值
	template <typename T>
	T Max(const T t1, const T t2) {return t1 > t2 ? t1 : t2;}

	//计时
	//参数表示是否进行初始化
	float Clock(bool = false);
}
#endif

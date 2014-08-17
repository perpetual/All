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

	//��ʼ�����ֻ���
#ifdef __OS_VERSION_WINDOWS__
	//��ʼ��COM��
	class CInitCom
	{
	protected:
		CInitCom(void);
		virtual ~CInitCom(void);
	};
#endif

	//����ַ������˵Ŀհ��ַ�
	string Trim(const char* const);
	wstring Trim(const wchar_t* const);
	string Trim(string str);
	wstring Trim(wstring str);

	//����ַ��������ж���Ŀհ��ַ�
	string TrimAll(const char* const);
	wstring TrimAll(const wchar_t* const);
	string TrimAll(string str);
	wstring TrimAll(wstring str);

	//խ�ַ���ת���ַ���
	wstring StrToWStr(const string&);

	//���ַ���ת��Ϊխ�ַ���
	string WStrToStr(const wstring&);

	//������ת��Ϊ�˽����ַ���
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

	//������ת��Ϊʮ�����ַ���
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

	//������ת��Ϊʮ�������ַ���
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

	//���ַ���ת��Ϊ����
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

	//���ַ���ת��Ϊ����

	//�ж��ļ��Ƿ��������ļ�
	bool IsFile(const string&);

	//�ж��Ƿ���Ŀ¼
	bool IsDirectory(const string&);

	//��ȡ�ļ���ȫ������
	string ReadWholeFile(const string&);

	//���ַ�д���ļ�
	//��һ���������ļ���
	//��һ���������ļ�����
	bool WriteWholeFile(const string&, const string&);

	//��ȡ������ظ�������
	string GetRandomName(void);

	//ɾ��ָ�����ļ�
	bool RemoveFile(const string&);

	//�޸��ļ���
	//��һ�������Ǿ��ļ���
	//��һ�����������ļ���
	bool RenameFile(const string&, const string&);

	//�����߳�
	void WaitForever(void);

	//��ָ���ָ�����ȡ�ַ���
	//��һ�������Ǳ���ȡ���ַ���
	//�ڶ����Ƿָ���
	vector<string> SplitString(const string& str, const string& = " \t\f\r\v\n");

	//����������ظ���Ԫ��
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

	//����Windowsʱ��
	bool SetSystemTime(time_t);

	//��string����Ӷ���������
	//��һ����������Ҫ������ݵ��׵�ַ
	//��һ����������ӵĳ���
	string& AppendString(string&, const void*, unsigned int);

	//������ɸ��ַ�
	string& AppendString(string&, char, unsigned int);

	//��һ���ڴ������Զ����Ƶ���ʽ��ӡ����
	//��һ���������ڴ���ַ
	//��һ���������ڴ泤��
	string PrintMemory(const void*, unsigned int);

	//��ȡָ��Ŀ¼�µ������ļ���
	//��һ��������ʾĿ¼·��
	//�¸�������ʾ�Ƿ��ȡĿ¼
	//��һ��������ʾ�Ƿ�ݹ��ȡ
	//��һ��������ʾ�Ƿ��ȡ�����ļ�
#ifdef __OS_VERSION_WINDOWS__
	//����ʹ��ͨ���
	vector<string> GetAllFileName(const string& = ".\\*", bool = false, bool = true, bool = false);
#elif defined (__OS_VERSION_LINUX__)
	vector<string> GetAllFileName(const string& = "./", bool = false, bool = true, bool = false);
#endif

	//��ӡ�����е�Ԫ��
	//��һ������������������
	//�ڶ��������Ƿָ���
	template <typename T>
	void PrintContainer(const T& t, char ch = ' ')
	{
		copy(t.begin(), t.end(), ostream_iterator<typename T::value_type>(cout, string(1, ch).c_str()));
		cout << endl;
	}

	//�ַ�����ת��
	//��һ����������Ҫת���ļ�������
	//��һ��������Դ��������
	//��һ��������Ŀ���������
	//��һ��������Ŀ���ļ�����
	bool TransCode(const string&, const string&, const string&, const string&);

#ifdef __OS_VERSION_LINUX__
	int getch(void);
	int kbhit(void);
#endif

	//��ȡ��ǰ·��
	string GetCurrentPath(void);

	//��ȡ���ֵ
	template <typename T>
	T Max(const T t1, const T t2) {return t1 > t2 ? t1 : t2;}

	//��ʱ
	//������ʾ�Ƿ���г�ʼ��
	float Clock(bool = false);
}
#endif

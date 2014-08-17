#ifndef DATA_TYPE_H
#define DATA_TYPE_H

#include <string>
#include <vector>
#include <map>
#include <utility>
#include <sstream>
#include <iostream>

namespace DataType
{
	using std::string;

	extern const char* const STRING_CHAR;
	extern const char* const STRING_UCHAR;
	extern const char* const STRING_SHORT;
	extern const char* const STRING_USHORT;
	extern const char* const STRING_INT;
	extern const char* const STRING_UINT;
	extern const char* const STRING_LONGLONG;
	extern const char* const STRING_ULONGLONG;
	extern const char* const STRING_SINGLE;
	extern const char* const STRING_DOUBLE;
	extern const char* const STRING_STRING;
	extern const char* TYPE_STRINGS[];

	enum EType
	{
		ID_CHAR,
		ID_UCHAR,
		ID_SHORT,
		ID_USHOR,
		ID_INT,
		ID_UINT,
		ID_LONGLONG,
		ID_ULONGLONG,
		ID_SINGLE,
		ID_DOUBLE,
		ID_STRING
	};

	//根据类型名获取类型值
	EType WhichType(const string&);

	using std::string;
	using std::vector;
	using std::map;
	using std::pair;
	using std::make_pair;
	using std::istringstream;
	using std::ostringstream;
	using std::stringstream;
	using std::ios;
	using std::ostream;
	using std::cout;

	class CSimpleData
	{
		friend class CComplexData;
	public:
		//第一个参数是值
		//第二个参数表示数据名称
		CSimpleData(char, const string& = "");
		CSimpleData(unsigned char, const string& = "");
		CSimpleData(short, const string& = "");
		CSimpleData(unsigned short, const string& = "");
		CSimpleData(int = int(0), const string& = "");				//充当默认构造函数
		CSimpleData(unsigned int, const string& = "");
		CSimpleData(long long, const string& = "");
		CSimpleData(unsigned long long, const string& = "");
		//第三个参数是精度，正值表示有效数字，负值代表小数精度
		CSimpleData(float, const string& = "", char = -4);
		CSimpleData(double, const string& = "", char = -4);
		CSimpleData(const string&, const string& = "");

		//第一个参数是类型标识
		//第二个参数是值的字符串形式
		//第三个参数是数据名称
		//第四个参数是精度
		CSimpleData(string, string,  const string&, char = -4);
		CSimpleData(string, const char* const &, const string&, char = -4);

		//第一个参数是类型标识
		//第二个参数是值的内存首地址，且必须是空指针
		//第三个参数是数据名称
		//第四个参数是浮点数精度
		CSimpleData(string, const void*, const string&, char = -4);

		//拷贝构造函数
		CSimpleData(const CSimpleData&);

		//重载赋值操作符
		CSimpleData& operator =(const CSimpleData&);

		//转换操作符
		operator bool(void) const;
		operator char(void) const;
		operator unsigned char(void) const;
		operator short(void) const;
		operator unsigned short(void) const;
		operator int(void) const;
		operator unsigned int(void) const;
		operator long long(void) const;
		operator unsigned long long(void) const;
		operator float(void) const;
		operator double(void) const;
		operator const char*(void) const;
		operator string(void) const;

//		const void* operator &(void)
//		{
//			return this->m_strRawValue.c_str();
//		}

		//判断转换是否成功
		bool IsSuccessful(void) const
		{
			return this->m_bIsSuccessful;
		}

		//获取数据名称
		string GetDataName(void) const
		{
			return this->m_strDataName;
		}

		//获取类型大小
		unsigned int GetSize(void) const
		{
			return this->m_strRawValue.length();
		}

		//获取该数据类型的名称
		string GetTypeName(void) const
		{
			return this->m_strTypeName;
		}

		//获取实际内存值
		const void* GetRawValue(void) const
		{
			return this->m_strRawValue.c_str();
		}

		//获取格式化后的值
		string GetFormatedValue(void) const
		{
			return this->m_strFormatedValue;
		}

		const CSimpleData& Display(bool = false) const;

		//重载算术运算符
		friend CSimpleData operator +(const CSimpleData&, const CSimpleData&);
		friend CSimpleData operator -(const CSimpleData&, const CSimpleData&);
		friend CSimpleData operator *(const CSimpleData&, const CSimpleData&);
		friend CSimpleData operator /(const CSimpleData&, const CSimpleData&);
		friend CSimpleData operator %(const CSimpleData&, const CSimpleData&);

		//重载逻辑操作符
		friend bool operator <(const CSimpleData&, const CSimpleData&);
		friend bool operator <=(const CSimpleData&, const CSimpleData&);
		friend bool operator ==(const CSimpleData&, const CSimpleData&);
		friend bool operator !=(const CSimpleData&, const CSimpleData&);
		friend bool operator >(const CSimpleData&, const CSimpleData&);
		friend bool operator >=(const CSimpleData&, const CSimpleData&);

	private:
		//根据类型标识获取其原始值
		template <typename T>
		T OriginalValue(T) const
		{
			if (STRING_CHAR == this->m_strTypeName)
			{
				return static_cast <T> (*reinterpret_cast <const char*> (this->m_strRawValue.c_str()));
			}else if (STRING_UCHAR == this->m_strTypeName)
			{
				return static_cast <T> (*reinterpret_cast <const unsigned char*> (this->m_strRawValue.c_str()));
			}else if (STRING_SHORT == this->m_strTypeName)
			{
				return static_cast <T> (*reinterpret_cast <const short*> (this->m_strRawValue.c_str()));
			}else if (STRING_USHORT == this->m_strTypeName)
			{
				return static_cast <T> (*reinterpret_cast <const unsigned short*> (this->m_strRawValue.c_str()));
			}else if(STRING_INT == this->m_strTypeName)
			{
				return static_cast <T> (*reinterpret_cast <const int*> (this->m_strRawValue.c_str()));
			}else if (STRING_UINT == this->m_strTypeName)
			{
				return static_cast <T> (*reinterpret_cast <const unsigned int*> (this->m_strRawValue.c_str()));
			}else if (STRING_LONGLONG == this->m_strTypeName)
			{
				return static_cast <T> (*reinterpret_cast <const long long*> (this->m_strRawValue.c_str()));
			}else if (STRING_ULONGLONG == this->m_strTypeName)
			{
				return static_cast <T> (*reinterpret_cast <const unsigned long long*> (this->m_strRawValue.c_str()));
			}else if (STRING_SINGLE == this->m_strTypeName)
			{
				return static_cast <T> (*reinterpret_cast <const float*> (this->m_strRawValue.c_str()));
			}else if (STRING_DOUBLE== this->m_strTypeName)
			{
				return static_cast <T> (*reinterpret_cast <const double*> (this->m_strRawValue.c_str()));
			}
			else
			{
				return 0;
			}
		}

		const string m_strDataName;			//数据名称
		const string m_strTypeName;			//类型名称
		const char m_i8Precision;					//精度
		string m_strRawValue;						//原始值，内存形态
		string m_strFormatedValue;				//格式化后的值，字面形态
		bool m_bIsSuccessful;						//是否成功
	};

	ostream& operator<<(ostream&, const CSimpleData&);
}

#endif
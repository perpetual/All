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

	//������������ȡ����ֵ
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
		//��һ��������ֵ
		//�ڶ���������ʾ��������
		CSimpleData(char, const string& = "");
		CSimpleData(unsigned char, const string& = "");
		CSimpleData(short, const string& = "");
		CSimpleData(unsigned short, const string& = "");
		CSimpleData(int = int(0), const string& = "");				//�䵱Ĭ�Ϲ��캯��
		CSimpleData(unsigned int, const string& = "");
		CSimpleData(long long, const string& = "");
		CSimpleData(unsigned long long, const string& = "");
		//�����������Ǿ��ȣ���ֵ��ʾ��Ч���֣���ֵ����С������
		CSimpleData(float, const string& = "", char = -4);
		CSimpleData(double, const string& = "", char = -4);
		CSimpleData(const string&, const string& = "");

		//��һ�����������ͱ�ʶ
		//�ڶ���������ֵ���ַ�����ʽ
		//��������������������
		//���ĸ������Ǿ���
		CSimpleData(string, string,  const string&, char = -4);
		CSimpleData(string, const char* const &, const string&, char = -4);

		//��һ�����������ͱ�ʶ
		//�ڶ���������ֵ���ڴ��׵�ַ���ұ����ǿ�ָ��
		//��������������������
		//���ĸ������Ǹ���������
		CSimpleData(string, const void*, const string&, char = -4);

		//�������캯��
		CSimpleData(const CSimpleData&);

		//���ظ�ֵ������
		CSimpleData& operator =(const CSimpleData&);

		//ת��������
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

		//�ж�ת���Ƿ�ɹ�
		bool IsSuccessful(void) const
		{
			return this->m_bIsSuccessful;
		}

		//��ȡ��������
		string GetDataName(void) const
		{
			return this->m_strDataName;
		}

		//��ȡ���ʹ�С
		unsigned int GetSize(void) const
		{
			return this->m_strRawValue.length();
		}

		//��ȡ���������͵�����
		string GetTypeName(void) const
		{
			return this->m_strTypeName;
		}

		//��ȡʵ���ڴ�ֵ
		const void* GetRawValue(void) const
		{
			return this->m_strRawValue.c_str();
		}

		//��ȡ��ʽ�����ֵ
		string GetFormatedValue(void) const
		{
			return this->m_strFormatedValue;
		}

		const CSimpleData& Display(bool = false) const;

		//�������������
		friend CSimpleData operator +(const CSimpleData&, const CSimpleData&);
		friend CSimpleData operator -(const CSimpleData&, const CSimpleData&);
		friend CSimpleData operator *(const CSimpleData&, const CSimpleData&);
		friend CSimpleData operator /(const CSimpleData&, const CSimpleData&);
		friend CSimpleData operator %(const CSimpleData&, const CSimpleData&);

		//�����߼�������
		friend bool operator <(const CSimpleData&, const CSimpleData&);
		friend bool operator <=(const CSimpleData&, const CSimpleData&);
		friend bool operator ==(const CSimpleData&, const CSimpleData&);
		friend bool operator !=(const CSimpleData&, const CSimpleData&);
		friend bool operator >(const CSimpleData&, const CSimpleData&);
		friend bool operator >=(const CSimpleData&, const CSimpleData&);

	private:
		//�������ͱ�ʶ��ȡ��ԭʼֵ
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

		const string m_strDataName;			//��������
		const string m_strTypeName;			//��������
		const char m_i8Precision;					//����
		string m_strRawValue;						//ԭʼֵ���ڴ���̬
		string m_strFormatedValue;				//��ʽ�����ֵ��������̬
		bool m_bIsSuccessful;						//�Ƿ�ɹ�
	};

	ostream& operator<<(ostream&, const CSimpleData&);
}

#endif
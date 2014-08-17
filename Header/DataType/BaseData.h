#ifndef DATATYPE_BASE_DATA_H
#define DATATYPE_BASE_DATA_H

#include "VersionControl.h"
#include <iostream>
#include <string>
#include <typeinfo>
#include "Handle/BaseObject.h"
#include "Handle/Handle.h"

#define FRIEND_CLASS	friend class CChar; friend class CUChar;\
	friend class CShort; friend class CUShort;\
	friend class CInt; friend class CUInt;\
	friend class CLong; friend class CULong;\
	friend class CLongLong; friend class CULongLong;\
	friend class CFloat; friend class CDouble;friend class CLongDouble;

namespace DataType
{
	using std::ostream;
	using std::string;
	using Utility::exceptionx;

	class CBaseData;

	class CCommonBase : public Handle::CBaseObject
	{
		friend class CBaseData;
		friend ostream& operator <<(ostream&, const CBaseData&);
	protected:
		virtual ostream& Print(ostream& oStream) const = 0;
		virtual CBaseData operator +(void) const = 0;
		virtual CBaseData operator -(void) const = 0;
		virtual CBaseData operator +(const CBaseData&) const = 0;
		virtual CBaseData operator -(const CBaseData&) const = 0;
		virtual CBaseData operator *(const CBaseData&) const = 0;
		virtual CBaseData operator /(const CBaseData&) const = 0;
		virtual CBaseData operator %(const CBaseData&) const = 0;

		virtual bool operator <(const CBaseData&) const = 0;
		virtual bool operator >(const CBaseData&) const = 0;
		virtual bool operator ==(const CBaseData&) const = 0;
		virtual bool operator !=(const CBaseData&) const = 0;
		virtual bool operator <=(const CBaseData&) const = 0;
		virtual bool operator >=(const CBaseData&) const = 0;

		virtual operator char(void) const = 0;
		virtual operator unsigned char(void) const = 0;
		virtual operator short(void) const = 0;
		virtual operator unsigned short(void) const = 0;
		virtual operator int(void) const = 0;
		virtual operator unsigned int(void) const = 0;
		virtual operator long(void) const = 0;
		virtual operator unsigned long(void) const = 0;
		virtual operator long long(void) const = 0;
		virtual operator unsigned long long(void) const = 0;
		virtual operator float(void) const = 0;
		virtual operator double(void) const = 0;
		virtual operator long double(void) const = 0;
		virtual operator string(void) const = 0;

		virtual size_t GetSize(void) const = 0;
		string Name(void);
		string Name(const string&);

		string m_strName;		//名称标识
	};

	class CChar : public CCommonBase
	{
		FRIEND_CLASS
	public:
		CChar(char c = 0, const string& strName = "") : m_data(c) {this->m_strName = strName;}
		ostream& Print(ostream& oStream) const {return oStream << this->m_data;}
		CBaseData operator +(void) const;
		CBaseData operator -(void) const;
		CBaseData operator +(const CBaseData&) const;
		CBaseData operator -(const CBaseData&) const;
		CBaseData operator *(const CBaseData&) const;
		CBaseData operator /(const CBaseData&) const;
		CBaseData operator %(const CBaseData&) const;

		bool operator <(const CBaseData&) const;
		bool operator >(const CBaseData&) const;
		bool operator ==(const CBaseData&) const;
		bool operator !=(const CBaseData&) const;
		bool operator <=(const CBaseData&) const;
		bool operator >=(const CBaseData&) const;

		operator char(void) const;
		operator unsigned char(void) const;
		operator short(void) const;
		operator unsigned short(void) const;
		operator int(void) const;
		operator unsigned int(void) const;
		operator long(void) const;
		operator unsigned long(void) const;
		operator long long(void) const;
		operator unsigned long long(void) const;
		operator float(void) const;
		operator double(void) const;
		operator long double(void) const;
		operator string(void) const;

		size_t GetSize(void) const;
	private:
		char m_data;
	};

	class CUChar : public CCommonBase
	{
		FRIEND_CLASS
	public:
		CUChar(unsigned char uc = 0, const string& strName = "") : m_data(uc) {this->m_strName = strName;}
		ostream& Print(ostream& oStream) const {return oStream << this->m_data;}
		CBaseData operator +(void) const;
		CBaseData operator -(void) const;
		CBaseData operator +(const CBaseData&) const;
		CBaseData operator -(const CBaseData&) const;
		CBaseData operator *(const CBaseData&) const;
		CBaseData operator /(const CBaseData&) const;
		CBaseData operator %(const CBaseData&) const;

		bool operator <(const CBaseData&) const;
		bool operator >(const CBaseData&) const;
		bool operator ==(const CBaseData&) const;
		bool operator !=(const CBaseData&) const;
		bool operator <=(const CBaseData&) const;
		bool operator >=(const CBaseData&) const;

		operator char(void) const;
		operator unsigned char(void) const;
		operator short(void) const;
		operator unsigned short(void) const;
		operator int(void) const;
		operator unsigned int(void) const;
		operator long(void) const;
		operator unsigned long(void) const;
		operator long long(void) const;
		operator unsigned long long(void) const;
		operator float(void) const;
		operator double(void) const;
		operator long double(void) const;
		operator string(void) const;

		size_t GetSize(void) const;
	private:
		unsigned char m_data;
	};

	class CShort : public CCommonBase
	{
		FRIEND_CLASS
	public:
		CShort(short s = 0, const string& strName = "") : m_data(s) {this->m_strName = strName;}
		ostream& Print(ostream& oStream) const {return oStream << this->m_data;}
		CBaseData operator +(void) const;
		CBaseData operator -(void) const;
		CBaseData operator +(const CBaseData&) const;
		CBaseData operator -(const CBaseData&) const;
		CBaseData operator *(const CBaseData&) const;
		CBaseData operator /(const CBaseData&) const;
		CBaseData operator %(const CBaseData&) const;
		bool operator <(const CBaseData&) const;
		bool operator >(const CBaseData&) const;
		bool operator ==(const CBaseData&) const;
		bool operator !=(const CBaseData&) const;
		bool operator <=(const CBaseData&) const;
		bool operator >=(const CBaseData&) const;

		operator char(void) const;
		operator unsigned char(void) const;
		operator short(void) const;
		operator unsigned short(void) const;
		operator int(void) const;
		operator unsigned int(void) const;
		operator long(void) const;
		operator unsigned long(void) const;
		operator long long(void) const;
		operator unsigned long long(void) const;
		operator float(void) const;
		operator double(void) const;
		operator long double(void) const;
		operator string(void) const;

		size_t GetSize(void) const;
	private:
		short m_data;
	};

	class CUShort : public CCommonBase
	{
		FRIEND_CLASS
	public:
		CUShort(unsigned short us = 0, const string& strName = "") : m_data(us) {this->m_strName = strName;}
		ostream& Print(ostream& oStream) const {return oStream << this->m_data;}
		CBaseData operator +(void) const;
		CBaseData operator -(void) const;
		CBaseData operator +(const CBaseData&) const;
		CBaseData operator -(const CBaseData&) const;
		CBaseData operator *(const CBaseData&) const;
		CBaseData operator /(const CBaseData&) const;
		CBaseData operator %(const CBaseData&) const;
		bool operator <(const CBaseData&) const;
		bool operator >(const CBaseData&) const;
		bool operator ==(const CBaseData&) const;
		bool operator !=(const CBaseData&) const;
		bool operator <=(const CBaseData&) const;
		bool operator >=(const CBaseData&) const;

		operator char(void) const;
		operator unsigned char(void) const;
		operator short(void) const;
		operator unsigned short(void) const;
		operator int(void) const;
		operator unsigned int(void) const;
		operator long(void) const;
		operator unsigned long(void) const;
		operator long long(void) const;
		operator unsigned long long(void) const;
		operator float(void) const;
		operator double(void) const;
		operator long double(void) const;
		operator string(void) const;

		size_t GetSize(void) const;
	private:
		unsigned short m_data;
	};

	class CInt : public CCommonBase
	{
		FRIEND_CLASS
	public:
		CInt(int i = 0, const string& strName = "") : m_data(i) {this->m_strName = strName;}
		ostream& Print(ostream& oStream) const {return oStream << this->m_data;}
		CBaseData operator +(void) const;
		CBaseData operator -(void) const;
		CBaseData operator +(const CBaseData&) const;
		CBaseData operator -(const CBaseData&) const;
		CBaseData operator *(const CBaseData&) const;
		CBaseData operator /(const CBaseData&) const;
		CBaseData operator %(const CBaseData&) const;
		bool operator <(const CBaseData&) const;
		bool operator >(const CBaseData&) const;
		bool operator ==(const CBaseData&) const;
		bool operator !=(const CBaseData&) const;
		bool operator <=(const CBaseData&) const;
		bool operator >=(const CBaseData&) const;

		operator char(void) const;
		operator unsigned char(void) const;
		operator short(void) const;
		operator unsigned short(void) const;
		operator int(void) const;
		operator unsigned int(void) const;
		operator long(void) const;
		operator unsigned long(void) const;
		operator long long(void) const;
		operator unsigned long long(void) const;
		operator float(void) const;
		operator double(void) const;
		operator long double(void) const;
		operator string(void) const;

		size_t GetSize(void) const;
	private:
		int m_data;
	};

	class CUInt : public CCommonBase
	{
		FRIEND_CLASS
	public:
		CUInt(unsigned int ui = 0, const string& strName = "") : m_data(ui) {this->m_strName = strName;}
		ostream& Print(ostream& oStream) const {return oStream << this->m_data;}
		CBaseData operator +(void) const;
		CBaseData operator -(void) const;
		CBaseData operator +(const CBaseData&) const;
		CBaseData operator -(const CBaseData&) const;
		CBaseData operator *(const CBaseData&) const;
		CBaseData operator /(const CBaseData&) const;
		CBaseData operator %(const CBaseData&) const;
		bool operator <(const CBaseData&) const;
		bool operator >(const CBaseData&) const;
		bool operator ==(const CBaseData&) const;
		bool operator !=(const CBaseData&) const;
		bool operator <=(const CBaseData&) const;
		bool operator >=(const CBaseData&) const;

		operator char(void) const;
		operator unsigned char(void) const;
		operator short(void) const;
		operator unsigned short(void) const;
		operator int(void) const;
		operator unsigned int(void) const;
		operator long(void) const;
		operator unsigned long(void) const;
		operator long long(void) const;
		operator unsigned long long(void) const;
		operator float(void) const;
		operator double(void) const;
		operator long double(void) const;
		operator string(void) const;

		size_t GetSize(void) const;
	private:
		unsigned int m_data;
	};

	class CLong : public CCommonBase
	{
		FRIEND_CLASS
	public:
		CLong(long l = 0, const string& strName = "") : m_data(l) {this->m_strName = strName;}
		ostream& Print(ostream& oStream) const {return oStream << this->m_data;}
		CBaseData operator +(void) const;
		CBaseData operator -(void) const;
		CBaseData operator +(const CBaseData&) const;
		CBaseData operator -(const CBaseData&) const;
		CBaseData operator *(const CBaseData&) const;
		CBaseData operator /(const CBaseData&) const;
		CBaseData operator %(const CBaseData&) const;
		bool operator <(const CBaseData&) const;
		bool operator >(const CBaseData&) const;
		bool operator ==(const CBaseData&) const;
		bool operator !=(const CBaseData&) const;
		bool operator <=(const CBaseData&) const;
		bool operator >=(const CBaseData&) const;

		operator char(void) const;
		operator unsigned char(void) const;
		operator short(void) const;
		operator unsigned short(void) const;
		operator int(void) const;
		operator unsigned int(void) const;
		operator long(void) const;
		operator unsigned long(void) const;
		operator long long(void) const;
		operator unsigned long long(void) const;
		operator float(void) const;
		operator double(void) const;
		operator long double(void) const;
		operator string(void) const;

		size_t GetSize(void) const;
	private:
		long m_data;
	};

	class CULong : public CCommonBase
	{
		FRIEND_CLASS
	public:
		CULong(unsigned long ul = 0, const string& strName = "") : m_data(ul) {this->m_strName = strName;}
		ostream& Print(ostream& oStream) const {return oStream << this->m_data;}
		CBaseData operator +(void) const;
		CBaseData operator -(void) const;
		CBaseData operator +(const CBaseData&) const;
		CBaseData operator -(const CBaseData&) const;
		CBaseData operator *(const CBaseData&) const;
		CBaseData operator /(const CBaseData&) const;
		CBaseData operator %(const CBaseData&) const;
		bool operator <(const CBaseData&) const;
		bool operator >(const CBaseData&) const;
		bool operator ==(const CBaseData&) const;
		bool operator !=(const CBaseData&) const;
		bool operator <=(const CBaseData&) const;
		bool operator >=(const CBaseData&) const;

		operator char(void) const;
		operator unsigned char(void) const;
		operator short(void) const;
		operator unsigned short(void) const;
		operator int(void) const;
		operator unsigned int(void) const;
		operator long(void) const;
		operator unsigned long(void) const;
		operator long long(void) const;
		operator unsigned long long(void) const;
		operator float(void) const;
		operator double(void) const;
		operator long double(void) const;
		operator string(void) const;

		size_t GetSize(void) const;
	private:
		unsigned long m_data;
	};

	class CLongLong : public CCommonBase
	{
		FRIEND_CLASS
	public:
		CLongLong(long long ll = 0, const string& strName = "") : m_data(ll) {this->m_strName = strName;}
		ostream& Print(ostream& oStream) const {return oStream << this->m_data;}
		CBaseData operator +(void) const;
		CBaseData operator -(void) const;
		CBaseData operator +(const CBaseData&) const;
		CBaseData operator -(const CBaseData&) const;
		CBaseData operator *(const CBaseData&) const;
		CBaseData operator /(const CBaseData&) const;
		CBaseData operator %(const CBaseData&) const;
		bool operator <(const CBaseData&) const;
		bool operator >(const CBaseData&) const;
		bool operator ==(const CBaseData&) const;
		bool operator !=(const CBaseData&) const;
		bool operator <=(const CBaseData&) const;
		bool operator >=(const CBaseData&) const;

		operator char(void) const;
		operator unsigned char(void) const;
		operator short(void) const;
		operator unsigned short(void) const;
		operator int(void) const;
		operator unsigned int(void) const;
		operator long(void) const;
		operator unsigned long(void) const;
		operator long long(void) const;
		operator unsigned long long(void) const;
		operator float(void) const;
		operator double(void) const;
		operator long double(void) const;
		operator string(void) const;

		size_t GetSize(void) const;
	private:
		long long m_data;
	};

	class CULongLong : public CCommonBase
	{
		FRIEND_CLASS
	public:
		CULongLong(unsigned long long ull = 0, const string& strName = "") : m_data(ull) {this->m_strName = strName;}
		ostream& Print(ostream& oStream) const {return oStream << this->m_data;}
		CBaseData operator +(void) const;
		CBaseData operator -(void) const;
		CBaseData operator +(const CBaseData&) const;
		CBaseData operator -(const CBaseData&) const;
		CBaseData operator *(const CBaseData&) const;
		CBaseData operator /(const CBaseData&) const;
		CBaseData operator %(const CBaseData&) const;
		bool operator <(const CBaseData&) const;
		bool operator >(const CBaseData&) const;
		bool operator ==(const CBaseData&) const;
		bool operator !=(const CBaseData&) const;
		bool operator <=(const CBaseData&) const;
		bool operator >=(const CBaseData&) const;

		operator char(void) const;
		operator unsigned char(void) const;
		operator short(void) const;
		operator unsigned short(void) const;
		operator int(void) const;
		operator unsigned int(void) const;
		operator long(void) const;
		operator unsigned long(void) const;
		operator long long(void) const;
		operator unsigned long long(void) const;
		operator float(void) const;
		operator double(void) const;
		operator long double(void) const;
		operator string(void) const;

		size_t GetSize(void) const;
	private:
		unsigned long long m_data;
	};

	class CFloat : public CCommonBase
	{
		FRIEND_CLASS
	public:
		CFloat(float f = 0.0f, const string& strName = "") : m_data(f) {this->m_strName = strName;}
		ostream& Print(ostream& oStream) const {return oStream << this->m_data;}
		CBaseData operator +(void) const;
		CBaseData operator -(void) const;
		CBaseData operator +(const CBaseData&) const;
		CBaseData operator -(const CBaseData&) const;
		CBaseData operator *(const CBaseData&) const;
		CBaseData operator /(const CBaseData&) const;
		CBaseData operator %(const CBaseData&) const;
		bool operator <(const CBaseData&) const;
		bool operator >(const CBaseData&) const;
		bool operator ==(const CBaseData&) const;
		bool operator !=(const CBaseData&) const;
		bool operator <=(const CBaseData&) const;
		bool operator >=(const CBaseData&) const;

		operator char(void) const;
		operator unsigned char(void) const;
		operator short(void) const;
		operator unsigned short(void) const;
		operator int(void) const;
		operator unsigned int(void) const;
		operator long(void) const;
		operator unsigned long(void) const;
		operator long long(void) const;
		operator unsigned long long(void) const;
		operator float(void) const;
		operator double(void) const;
		operator long double(void) const;
		operator string(void) const;

		size_t GetSize(void) const;
	private:
		float m_data;
	};

	class CDouble : public CCommonBase
	{
		FRIEND_CLASS
	public:
		CDouble(double d = 0.0, const string& strName = "") : m_data(d) {this->m_strName = strName;}
		ostream& Print(ostream& oStream) const {return oStream << this->m_data;}
		CBaseData operator +(void) const;
		CBaseData operator -(void) const;
		CBaseData operator +(const CBaseData&) const;
		CBaseData operator -(const CBaseData&) const;
		CBaseData operator *(const CBaseData&) const;
		CBaseData operator /(const CBaseData&) const;
		CBaseData operator %(const CBaseData&) const;
		bool operator <(const CBaseData&) const;
		bool operator >(const CBaseData&) const;
		bool operator ==(const CBaseData&) const;
		bool operator !=(const CBaseData&) const;
		bool operator <=(const CBaseData&) const;
		bool operator >=(const CBaseData&) const;

		operator char(void) const;
		operator unsigned char(void) const;
		operator short(void) const;
		operator unsigned short(void) const;
		operator int(void) const;
		operator unsigned int(void) const;
		operator long(void) const;
		operator unsigned long(void) const;
		operator long long(void) const;
		operator unsigned long long(void) const;
		operator float(void) const;
		operator double(void) const;
		operator long double(void) const;
		operator string(void) const;

		size_t GetSize(void) const;
	private:
		double m_data;
	};

	class CLongDouble : public CCommonBase
	{
		FRIEND_CLASS
	public:
		CLongDouble(long double ld = 0.0, const string& strName = "") : m_data(ld) {this->m_strName = strName;}
		ostream& Print(ostream& oStream) const {return oStream << this->m_data;}
		CBaseData operator +(void) const;
		CBaseData operator -(void) const;
		CBaseData operator +(const CBaseData&) const;
		CBaseData operator -(const CBaseData&) const;
		CBaseData operator *(const CBaseData&) const;
		CBaseData operator /(const CBaseData&) const;
		CBaseData operator %(const CBaseData&) const;
		bool operator <(const CBaseData&) const;
		bool operator >(const CBaseData&) const;
		bool operator ==(const CBaseData&) const;
		bool operator !=(const CBaseData&) const;
		bool operator <=(const CBaseData&) const;
		bool operator >=(const CBaseData&) const;

		operator char(void) const;
		operator unsigned char(void) const;
		operator short(void) const;
		operator unsigned short(void) const;
		operator int(void) const;
		operator unsigned int(void) const;
		operator long(void) const;
		operator unsigned long(void) const;
		operator long long(void) const;
		operator unsigned long long(void) const;
		operator float(void) const;
		operator double(void) const;
		operator long double(void) const;
		operator string(void) const;

		size_t GetSize(void) const;
	private:
		long double m_data;
	};

	class CBaseData : public Handle::CHandle<CCommonBase, false>
	{
		FRIEND_CLASS
		friend ostream& operator <<(ostream&, const CBaseData&);
	public:
		enum EDataType
		{
#ifdef CHAR
#undef CHAR
#endif
			CHAR,
#ifdef UCHAR
#undef UCHAR
#endif
			UCHAR,
#ifdef BYTE
#undef BYTE
#endif
			BYTE,
#ifdef UBYTE
#undef UBYTE
#endif
			UBYTE,
#ifdef SHORT
#undef SHORT
#endif
			SHORT,
#ifdef USHORT
#undef USHORT
#endif
			USHORT,
#ifdef INT
#undef INT
#endif
			INT,
#ifdef UINT
#undef UINT
#endif
			UINT,
#ifdef LONG
#undef LONG
#endif
			LONG,
#ifdef ULONG
#undef ULONG
#endif
			ULONG,
#ifdef LONGLONG
#undef LONGLONG
#endif
			LONGLONG,
#ifdef ULONGLONG
#undef ULONGLONG
#endif
			ULONGLONG,
#ifdef FLOAT
#undef FLOAT
#endif
			FLOAT,
#ifdef DOUBLE
#undef DOUBLE
#endif
			DOUBLE,
#ifdef LONGDOUBLE
#undef LONGDOUBLE
#endif
			LONGDOUBLE
		};

		CBaseData(void);

		template <typename T>
		CBaseData(T t, const string& = "");

		//通过数字字符串进行构造
		CBaseData(const string&, EDataType, const string& = "");

		//通过内存结构进行构造
		CBaseData(const void*, EDataType, const string& = "");

		CBaseData operator +(void) const;
		CBaseData operator -(void) const;
		CBaseData operator +(const CBaseData&) const;
		CBaseData operator -(const CBaseData&) const;
		CBaseData operator *(const CBaseData&) const;
		CBaseData operator /(const CBaseData&) const;
		CBaseData operator %(const CBaseData&) const;
		bool operator <(const CBaseData&) const;
		bool operator >(const CBaseData&) const;
		bool operator ==(const CBaseData&) const;
		bool operator !=(const CBaseData&) const;
		bool operator <=(const CBaseData&) const;
		bool operator >=(const CBaseData&) const;

		operator char(void) const;
		operator unsigned char(void) const;
		operator short(void) const;
		operator unsigned short(void) const;
		operator int(void) const;
		operator unsigned int(void) const;
		operator long(void) const;
		operator unsigned long(void) const;
		operator long long(void) const;
		operator unsigned long long(void) const;
		operator float(void) const;
		operator double(void) const;
		operator long double(void) const;
		operator string(void) const;

		//获取数据的实际类型
		string GetActualType(void) const {return typeid(*this->m_pBase).name();}

		//获取数据内容长度
		size_t GetSize(void) const;

		//获取数据名称
		string Name(void) const {return this->m_pBase->Name();}
		string Name(const string& strName) const {return this->m_pBase->Name(strName);}
	};

	template <typename T>
	CBaseData::CBaseData(T t, const string& strName)
	{
		if (typeid(T) == typeid(char))
		{
			this->m_pBase = new CChar(static_cast<char>(t), strName);
		}else if (typeid(T) == typeid(unsigned char))
		{
			this->m_pBase = new CUChar(static_cast<unsigned char>(t), strName);
		}else if (typeid(T) == typeid(short))
		{
			this->m_pBase = new CShort(static_cast<short>(t), strName);
		}else if (typeid(T) == typeid(unsigned short))
		{
			this->m_pBase = new CUShort(static_cast<unsigned short>(t), strName);
		}else if (typeid(T) == typeid(int))
		{
			this->m_pBase = new CInt(static_cast<int>(t), strName);
		}else if (typeid(T) == typeid(unsigned int))
		{
			this->m_pBase = new CUInt(static_cast<unsigned int>(t), strName);
		}else if (typeid(T) == typeid(long))
		{
			this->m_pBase = new CLong(static_cast<long>(t), strName);
		}else if (typeid(T) == typeid(unsigned long))
		{
			this->m_pBase = new CULong(static_cast<unsigned long>(t), strName);
		}else if (typeid(T) == typeid(long long))
		{
			this->m_pBase = new CLongLong(static_cast<long long>(t), strName);
		}else if (typeid(T) == typeid(unsigned long long))
		{
			this->m_pBase = new CULongLong(static_cast<long long>(t), strName);
		}else if (typeid(T) == typeid(float))
		{
			this->m_pBase = new CFloat(static_cast<float>(t), strName);
		}else if (typeid(T) == typeid(double))
		{
			this->m_pBase = new CDouble(static_cast<double>(t), strName);
		}else if (typeid(T) == typeid(long double))
		{
			this->m_pBase = new CLongDouble(static_cast<long double>(t), strName);
		}
		else
		{
			throw exceptionx("Unknown Type");
		}
	}

	ostream& operator <<(ostream& oStream, const CBaseData& oBaseData);
}

#endif

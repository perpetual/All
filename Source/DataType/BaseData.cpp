#include <sstream>
#include "DataType/BaseData.h"

#ifdef __OS_VERSION_WINDOWS__
#pragma warning(disable:4018)
#pragma warning(disable:4389)
#pragma warning(disable:4244)
#pragma warning(disable:4146)
#elif defined (__OS_VERSION_LINUX__)
#endif

#define DYNAMIC_CAST(ClassName, ObjectName) dynamic_cast<ClassName*>(ObjectName.m_pBase)

#define DYNAMIC_SUM(ObjectName) \
	if (DYNAMIC_CAST(CChar, ObjectName))\
	{return this->m_data + DYNAMIC_CAST(CChar, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CUChar, ObjectName))\
	{return this->m_data + DYNAMIC_CAST(CUChar, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CShort, ObjectName))\
	{return this->m_data + DYNAMIC_CAST(CShort, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CUShort, ObjectName))\
	{return this->m_data + DYNAMIC_CAST(CUShort, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CInt, ObjectName))\
	{return this->m_data + DYNAMIC_CAST(CInt, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CUInt, ObjectName))\
	{return this->m_data + DYNAMIC_CAST(CUInt, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CLong, ObjectName))\
	{return this->m_data + DYNAMIC_CAST(CLong, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CULong, ObjectName))\
	{return this->m_data + DYNAMIC_CAST(CULong, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CLongLong, ObjectName))\
	{return this->m_data + DYNAMIC_CAST(CLongLong, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CULongLong, ObjectName))\
	{return this->m_data + DYNAMIC_CAST(CULongLong, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CFloat, ObjectName))\
	{return this->m_data + DYNAMIC_CAST(CFloat, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CDouble, ObjectName))\
	{return this->m_data + DYNAMIC_CAST(CDouble, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CLongDouble, ObjectName))\
	{return this->m_data + DYNAMIC_CAST(CLongDouble, ObjectName)->m_data;\
	}else\
	{throw exceptionx("Dynamic Sum Error");}

#define DYNAMIC_SUB(ObjectName) \
	if (DYNAMIC_CAST(CChar, ObjectName))\
	{return this->m_data - DYNAMIC_CAST(CChar, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CUChar, ObjectName))\
	{return this->m_data - DYNAMIC_CAST(CUChar, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CShort, ObjectName))\
	{return this->m_data - DYNAMIC_CAST(CShort, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CUShort, ObjectName))\
	{return this->m_data - DYNAMIC_CAST(CUShort, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CInt, ObjectName))\
	{return this->m_data - DYNAMIC_CAST(CInt, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CUInt, ObjectName))\
	{return this->m_data - DYNAMIC_CAST(CUInt, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CLong, ObjectName))\
	{return this->m_data - DYNAMIC_CAST(CLong, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CULong, ObjectName))\
	{return this->m_data - DYNAMIC_CAST(CULong, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CLongLong, ObjectName))\
	{return this->m_data - DYNAMIC_CAST(CLongLong, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CULongLong, ObjectName))\
	{return this->m_data - DYNAMIC_CAST(CULongLong, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CFloat, ObjectName))\
	{return this->m_data - DYNAMIC_CAST(CFloat, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CDouble, ObjectName))\
	{return this->m_data - DYNAMIC_CAST(CDouble, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CLongDouble, ObjectName))\
	{return this->m_data - DYNAMIC_CAST(CLongDouble, ObjectName)->m_data;\
	}\
	{throw exceptionx("Dynamic Sub Error");}

#define DYNAMIC_MUL(ObjectName) \
	if (DYNAMIC_CAST(CChar, ObjectName))\
	{return this->m_data * DYNAMIC_CAST(CChar, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CUChar, ObjectName))\
	{return this->m_data * DYNAMIC_CAST(CUChar, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CShort, ObjectName))\
	{return this->m_data * DYNAMIC_CAST(CShort, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CUShort, ObjectName))\
	{return this->m_data * DYNAMIC_CAST(CUShort, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CInt, ObjectName))\
	{return this->m_data * DYNAMIC_CAST(CInt, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CUInt, ObjectName))\
	{return this->m_data * DYNAMIC_CAST(CUInt, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CLong, ObjectName))\
	{return this->m_data * DYNAMIC_CAST(CLong, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CULong, ObjectName))\
	{return this->m_data * DYNAMIC_CAST(CULong, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CLongLong, ObjectName))\
	{return this->m_data * DYNAMIC_CAST(CLongLong, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CULongLong, ObjectName))\
	{return this->m_data * DYNAMIC_CAST(CULongLong, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CFloat, ObjectName))\
	{return this->m_data * DYNAMIC_CAST(CFloat, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CDouble, ObjectName))\
	{return this->m_data * DYNAMIC_CAST(CDouble, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CLongDouble, ObjectName))\
	{return this->m_data * DYNAMIC_CAST(CLongDouble, ObjectName)->m_data;\
	}else\
	{throw exceptionx("Dynamic Mul Error");}

#define DYNAMIC_DIV(ObjectName) \
	if (DYNAMIC_CAST(CChar, ObjectName))\
	{return this->m_data / DYNAMIC_CAST(CChar, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CUChar, ObjectName))\
	{return this->m_data / DYNAMIC_CAST(CUChar, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CShort, ObjectName))\
	{return this->m_data / DYNAMIC_CAST(CShort, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CUShort, ObjectName))\
	{return this->m_data / DYNAMIC_CAST(CUShort, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CInt, ObjectName))\
	{return this->m_data / DYNAMIC_CAST(CInt, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CUInt, ObjectName))\
	{return this->m_data / DYNAMIC_CAST(CUInt, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CLong, ObjectName))\
	{return this->m_data / DYNAMIC_CAST(CLong, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CULong, ObjectName))\
	{return this->m_data / DYNAMIC_CAST(CULong, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CLongLong, ObjectName))\
	{return this->m_data / DYNAMIC_CAST(CLongLong, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CULongLong, ObjectName))\
	{return this->m_data / DYNAMIC_CAST(CULongLong, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CFloat, ObjectName))\
	{return this->m_data / DYNAMIC_CAST(CFloat, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CDouble, ObjectName))\
	{return this->m_data / DYNAMIC_CAST(CDouble, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CLongDouble, ObjectName))\
	{return this->m_data / DYNAMIC_CAST(CLongDouble, ObjectName)->m_data;\
	}else\
	{throw exceptionx("Dynamic Div Error");}

#define DYNAMIC_LESS(ObjectName) \
	if (DYNAMIC_CAST(CChar, ObjectName))\
	{return this->m_data < DYNAMIC_CAST(CChar, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CUChar, ObjectName))\
	{return this->m_data < DYNAMIC_CAST(CUChar, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CShort, ObjectName))\
	{return this->m_data < DYNAMIC_CAST(CShort, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CUShort, ObjectName))\
	{return this->m_data < DYNAMIC_CAST(CUShort, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CInt, ObjectName))\
	{return this->m_data < DYNAMIC_CAST(CInt, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CUInt, ObjectName))\
	{return this->m_data < DYNAMIC_CAST(CUInt, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CLong, ObjectName))\
	{return this->m_data < DYNAMIC_CAST(CLong, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CULong, ObjectName))\
	{return this->m_data < DYNAMIC_CAST(CULong, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CLongLong, ObjectName))\
	{return this->m_data < DYNAMIC_CAST(CLongLong, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CULongLong, ObjectName))\
	{return this->m_data < DYNAMIC_CAST(CULongLong, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CFloat, ObjectName))\
	{return this->m_data < DYNAMIC_CAST(CFloat, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CDouble, ObjectName))\
	{return this->m_data < DYNAMIC_CAST(CDouble, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CLongDouble, ObjectName))\
	{return this->m_data < DYNAMIC_CAST(CLongDouble, ObjectName)->m_data;\
	}else\
	{throw exceptionx("Dynamic Less Error");}

#define DYNAMIC_MORE(ObjectName) \
	if (DYNAMIC_CAST(CChar, ObjectName))\
	{return this->m_data > DYNAMIC_CAST(CChar, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CUChar, ObjectName))\
	{return this->m_data > DYNAMIC_CAST(CUChar, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CShort, ObjectName))\
	{return this->m_data > DYNAMIC_CAST(CShort, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CUShort, ObjectName))\
	{return this->m_data > DYNAMIC_CAST(CUShort, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CInt, ObjectName))\
	{return this->m_data > DYNAMIC_CAST(CInt, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CUInt, ObjectName))\
	{return this->m_data > DYNAMIC_CAST(CUInt, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CLong, ObjectName))\
	{return this->m_data > DYNAMIC_CAST(CLong, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CULong, ObjectName))\
	{return this->m_data > DYNAMIC_CAST(CULong, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CLongLong, ObjectName))\
	{return this->m_data > DYNAMIC_CAST(CLongLong, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CULongLong, ObjectName))\
	{return this->m_data > DYNAMIC_CAST(CULongLong, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CFloat, ObjectName))\
	{return this->m_data > DYNAMIC_CAST(CFloat, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CDouble, ObjectName))\
	{return this->m_data > DYNAMIC_CAST(CDouble, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CLongDouble, ObjectName))\
	{return this->m_data > DYNAMIC_CAST(CLongDouble, ObjectName)->m_data;\
	}else\
	{throw exceptionx("Dynamic More Error");}

#define DYNAMIC_EQUAL(ObjectName) \
	if (DYNAMIC_CAST(CChar, ObjectName))\
	{return this->m_data == DYNAMIC_CAST(CChar, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CUChar, ObjectName))\
	{return this->m_data == DYNAMIC_CAST(CUChar, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CShort, ObjectName))\
	{return this->m_data == DYNAMIC_CAST(CShort, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CUShort, ObjectName))\
	{return this->m_data == DYNAMIC_CAST(CUShort, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CInt, ObjectName))\
	{return this->m_data == DYNAMIC_CAST(CInt, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CUInt, ObjectName))\
	{return this->m_data == DYNAMIC_CAST(CUInt, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CLong, ObjectName))\
	{return this->m_data == DYNAMIC_CAST(CLong, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CULong, ObjectName))\
	{return this->m_data == DYNAMIC_CAST(CULong, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CLongLong, ObjectName))\
	{return this->m_data == DYNAMIC_CAST(CLongLong, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CULongLong, ObjectName))\
	{return this->m_data == DYNAMIC_CAST(CULongLong, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CFloat, ObjectName))\
	{return this->m_data == DYNAMIC_CAST(CFloat, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CDouble, ObjectName))\
	{return this->m_data == DYNAMIC_CAST(CDouble, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CLongDouble, ObjectName))\
	{return this->m_data == DYNAMIC_CAST(CLongDouble, ObjectName)->m_data;\
	}else\
	{throw exceptionx("Dynamic Equal Error");}

#define DYNAMIC_NOT_EQUAL(ObjectName) \
	if (DYNAMIC_CAST(CChar, ObjectName))\
	{return this->m_data != DYNAMIC_CAST(CChar, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CUChar, ObjectName))\
	{return this->m_data != DYNAMIC_CAST(CUChar, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CShort, ObjectName))\
	{return this->m_data != DYNAMIC_CAST(CShort, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CUShort, ObjectName))\
	{return this->m_data != DYNAMIC_CAST(CUShort, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CInt, ObjectName))\
	{return this->m_data != DYNAMIC_CAST(CInt, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CUInt, ObjectName))\
	{return this->m_data != DYNAMIC_CAST(CUInt, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CLong, ObjectName))\
	{return this->m_data != DYNAMIC_CAST(CLong, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CULong, ObjectName))\
	{return this->m_data != DYNAMIC_CAST(CULong, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CLongLong, ObjectName))\
	{return this->m_data != DYNAMIC_CAST(CLongLong, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CULongLong, ObjectName))\
	{return this->m_data != DYNAMIC_CAST(CULongLong, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CFloat, ObjectName))\
	{return this->m_data != DYNAMIC_CAST(CFloat, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CDouble, ObjectName))\
	{return this->m_data != DYNAMIC_CAST(CDouble, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CLongDouble, ObjectName))\
	{return this->m_data != DYNAMIC_CAST(CLongDouble, ObjectName)->m_data;\
	}else\
	{throw exceptionx("Dynamic Equal Error");}

#define DYNAMIC_LESS_EQUAL(ObjectName) \
	if (DYNAMIC_CAST(CChar, ObjectName))\
	{return this->m_data <= DYNAMIC_CAST(CChar, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CUChar, ObjectName))\
	{return this->m_data <= DYNAMIC_CAST(CUChar, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CShort, ObjectName))\
	{return this->m_data <= DYNAMIC_CAST(CShort, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CUShort, ObjectName))\
	{return this->m_data <= DYNAMIC_CAST(CUShort, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CInt, ObjectName))\
	{return this->m_data <= DYNAMIC_CAST(CInt, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CUInt, ObjectName))\
	{return this->m_data <= DYNAMIC_CAST(CUInt, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CLong, ObjectName))\
	{return this->m_data <= DYNAMIC_CAST(CLong, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CULong, ObjectName))\
	{return this->m_data <= DYNAMIC_CAST(CULong, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CLongLong, ObjectName))\
	{return this->m_data <= DYNAMIC_CAST(CLongLong, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CULongLong, ObjectName))\
	{return this->m_data <= DYNAMIC_CAST(CULongLong, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CFloat, ObjectName))\
	{return this->m_data <= DYNAMIC_CAST(CFloat, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CDouble, ObjectName))\
	{return this->m_data <= DYNAMIC_CAST(CDouble, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CLongDouble, ObjectName))\
	{return this->m_data <= DYNAMIC_CAST(CLongDouble, ObjectName)->m_data;\
	}else\
	{throw exceptionx("Dynamic Less-Equal Error");}

#define DYNAMIC_MORE_EQUAL(ObjectName) \
	if (DYNAMIC_CAST(CChar, ObjectName))\
	{return this->m_data >= DYNAMIC_CAST(CChar, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CUChar, ObjectName))\
	{return this->m_data >= DYNAMIC_CAST(CUChar, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CShort, ObjectName))\
	{return this->m_data >= DYNAMIC_CAST(CShort, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CUShort, ObjectName))\
	{return this->m_data >= DYNAMIC_CAST(CUShort, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CInt, ObjectName))\
	{return this->m_data >= DYNAMIC_CAST(CInt, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CUInt, ObjectName))\
	{return this->m_data >= DYNAMIC_CAST(CUInt, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CLong, ObjectName))\
	{return this->m_data >= DYNAMIC_CAST(CLong, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CULong, ObjectName))\
	{return this->m_data >= DYNAMIC_CAST(CULong, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CLongLong, ObjectName))\
	{return this->m_data >= DYNAMIC_CAST(CLongLong, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CULongLong, ObjectName))\
	{return this->m_data >= DYNAMIC_CAST(CULongLong, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CFloat, ObjectName))\
	{return this->m_data >= DYNAMIC_CAST(CFloat, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CDouble, ObjectName))\
	{return this->m_data >= DYNAMIC_CAST(CDouble, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CLongDouble, ObjectName))\
	{return this->m_data >= DYNAMIC_CAST(CLongDouble, ObjectName)->m_data;\
	}else\
	{throw exceptionx("Dynamic More-Equal Error");}

#define DYNAMIC_MOD(ObjectName) \
	if (DYNAMIC_CAST(CChar, ObjectName))\
	{return this->m_data % DYNAMIC_CAST(CChar, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CUChar, ObjectName))\
	{return this->m_data % DYNAMIC_CAST(CUChar, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CShort, ObjectName))\
	{return this->m_data % DYNAMIC_CAST(CShort, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CUShort, ObjectName))\
	{return this->m_data % DYNAMIC_CAST(CUShort, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CInt, ObjectName))\
	{return this->m_data % DYNAMIC_CAST(CInt, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CUInt, ObjectName))\
	{return this->m_data % DYNAMIC_CAST(CUInt, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CLong, ObjectName))\
	{return this->m_data % DYNAMIC_CAST(CLong, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CULong, ObjectName))\
	{return this->m_data % DYNAMIC_CAST(CULong, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CLongLong, ObjectName))\
	{return this->m_data % DYNAMIC_CAST(CLongLong, ObjectName)->m_data;\
	}else if (DYNAMIC_CAST(CULongLong, ObjectName))\
	{return this->m_data % DYNAMIC_CAST(CULongLong, ObjectName)->m_data;\
	}else\
	{throw exceptionx("Dynamic Mod Error");}

namespace DataType
{
	using std::ostringstream;

	/////////////////////////CCommonBase的实现/////////////////////////////////////////////////
	string CCommonBase::Name(void) {return this->m_strName;}
	string CCommonBase::Name(const string& strName) {return this->m_strName = strName;}

	////////////////////////CChar的实现//////////////////////////////////////////////////
	CBaseData CChar::operator +(void) const {return this->m_data;}
	CBaseData CChar::operator -(void) const {return -this->m_data;}
	CBaseData CChar::operator +(const CBaseData& o) const {	DYNAMIC_SUM(o)}
	CBaseData CChar::operator -(const CBaseData& o) const {DYNAMIC_SUB(o)}
	CBaseData CChar::operator *(const CBaseData& o) const {	DYNAMIC_MUL(o)}
	CBaseData CChar::operator /(const CBaseData& o) const {DYNAMIC_DIV(o)}
	CBaseData CChar::operator %(const CBaseData& o) const {DYNAMIC_MOD(o)}
	bool CChar::operator <(const CBaseData& o) const {DYNAMIC_LESS(o)}
	bool CChar::operator >(const CBaseData& o) const {DYNAMIC_MORE(o)}
	bool CChar::operator ==(const CBaseData& o) const {DYNAMIC_EQUAL(o)}
	bool CChar::operator !=(const CBaseData& o) const {DYNAMIC_NOT_EQUAL(o)}
	bool CChar::operator <=(const CBaseData& o) const {DYNAMIC_LESS_EQUAL(o)}
	bool CChar::operator >=(const CBaseData& o) const {DYNAMIC_MORE_EQUAL(o)}
	CChar::operator char(void) const {return this->m_data;}
	CChar::operator unsigned char(void) const {return this->m_data;}
	CChar::operator short(void) const {return this->m_data;}
	CChar::operator unsigned short(void) const {return this->m_data;}
	CChar::operator int(void) const {return this->m_data;}
	CChar::operator unsigned int(void) const {return this->m_data;}
	CChar::operator long(void) const {return this->m_data;}
	CChar::operator unsigned long(void) const {return this->m_data;}
	CChar::operator long long(void) const {return this->m_data;}
	CChar::operator unsigned long long(void) const {return this->m_data;}
	CChar::operator float(void) const {return this->m_data;}
	CChar::operator double(void) const {return this->m_data;}
	CChar::operator long double(void) const {return this->m_data;}
	CChar::operator string(void) const {ostringstream oss; oss << this->m_data; return oss.str();}
	size_t CChar::GetSize() const {return sizeof (this->m_data);}

	////////////////////////CUChar的实现//////////////////////////////////////////////////
	CBaseData CUChar::operator +(void) const {return this->m_data;}
	CBaseData CUChar::operator -(void) const {return -this->m_data;}
	CBaseData CUChar::operator +(const CBaseData& o) const {DYNAMIC_SUM(o)}
	CBaseData CUChar::operator -(const CBaseData& o) const {DYNAMIC_SUB(o)}
	CBaseData CUChar::operator *(const CBaseData& o) const {DYNAMIC_MUL(o)}
	CBaseData CUChar::operator /(const CBaseData& o) const {DYNAMIC_DIV(o)}
	CBaseData CUChar::operator %(const CBaseData& o) const {DYNAMIC_MOD(o)}
	bool CUChar::operator <(const CBaseData& o) const {	DYNAMIC_LESS(o)}
	bool CUChar::operator >(const CBaseData& o) const {DYNAMIC_MORE(o)}
	bool CUChar::operator ==(const CBaseData& o) const {DYNAMIC_EQUAL(o)}
	bool CUChar::operator !=(const CBaseData& o) const {DYNAMIC_NOT_EQUAL(o)}
	bool CUChar::operator <=(const CBaseData& o) const {DYNAMIC_LESS_EQUAL(o)}
	bool CUChar::operator >=(const CBaseData& o) const {DYNAMIC_MORE_EQUAL(o)}
	CUChar::operator char(void) const {return this->m_data;}
	CUChar::operator unsigned char(void) const {return this->m_data;}
	CUChar::operator short(void) const {return this->m_data;}
	CUChar::operator unsigned short(void) const {return this->m_data;}
	CUChar::operator int(void) const {return this->m_data;}
	CUChar::operator unsigned int(void) const {return this->m_data;}
	CUChar::operator long(void) const {return this->m_data;}
	CUChar::operator unsigned long(void) const {return this->m_data;}
	CUChar::operator long long(void) const {return this->m_data;}
	CUChar::operator unsigned long long(void) const {return this->m_data;}
	CUChar::operator float(void) const {return this->m_data;}
	CUChar::operator double(void) const {return this->m_data;}
	CUChar::operator long double(void) const {return this->m_data;}
	CUChar::operator string(void) const {ostringstream oss; oss << this->m_data; return oss.str();}
	size_t CUChar::GetSize() const {return sizeof (this->m_data);}

	////////////////////////CShort的实现//////////////////////////////////////////////////
	CBaseData CShort::operator +(void) const {return this->m_data;}
	CBaseData CShort::operator -(void) const {return -this->m_data;}
	CBaseData CShort::operator +(const CBaseData& o) const {DYNAMIC_SUM(o)}
	CBaseData CShort::operator -(const CBaseData& o) const {DYNAMIC_SUB(o)}
	CBaseData CShort::operator *(const CBaseData& o) const {DYNAMIC_MUL(o)}
	CBaseData CShort::operator /(const CBaseData& o) const {DYNAMIC_DIV(o)}
	CBaseData CShort::operator %(const CBaseData& o) const {DYNAMIC_MOD(o)}
	bool CShort::operator <(const CBaseData& o) const {	DYNAMIC_LESS(o)}
	bool CShort::operator >(const CBaseData& o) const {DYNAMIC_MORE(o)}
	bool CShort::operator ==(const CBaseData& o) const {DYNAMIC_EQUAL(o)}
	bool CShort::operator !=(const CBaseData& o) const {DYNAMIC_NOT_EQUAL(o)}
	bool CShort::operator <=(const CBaseData& o) const {DYNAMIC_LESS_EQUAL(o)}
	bool CShort::operator >=(const CBaseData& o) const {DYNAMIC_MORE_EQUAL(o)}
	CShort::operator char(void) const {return this->m_data;}
	CShort::operator unsigned char(void) const {return this->m_data;}
	CShort::operator short(void) const {return this->m_data;}
	CShort::operator unsigned short(void) const {return this->m_data;}
	CShort::operator int(void) const {return this->m_data;}
	CShort::operator unsigned int(void) const {return this->m_data;}
	CShort::operator long(void) const {return this->m_data;}
	CShort::operator unsigned long(void) const {return this->m_data;}
	CShort::operator long long(void) const {return this->m_data;}
	CShort::operator unsigned long long(void) const {return this->m_data;}
	CShort::operator float(void) const {return this->m_data;}
	CShort::operator double(void) const {return this->m_data;}
	CShort::operator long double(void) const {return this->m_data;}
	CShort::operator string(void) const {ostringstream oss; oss << this->m_data; return oss.str();}
	size_t CShort::GetSize() const {return sizeof (this->m_data);}

	////////////////////////CUShort的实现//////////////////////////////////////////////////
	CBaseData CUShort::operator +(void) const {return this->m_data;}
	CBaseData CUShort::operator -(void) const {return -this->m_data;}
	CBaseData CUShort::operator +(const CBaseData& o) const {DYNAMIC_SUM(o)}
	CBaseData CUShort::operator -(const CBaseData& o) const {DYNAMIC_SUB(o)}
	CBaseData CUShort::operator *(const CBaseData& o) const {DYNAMIC_MUL(o)}
	CBaseData CUShort::operator /(const CBaseData& o) const {DYNAMIC_DIV(o)}
	CBaseData CUShort::operator %(const CBaseData& o) const {DYNAMIC_MOD(o)}
	bool CUShort::operator <(const CBaseData& o) const {	DYNAMIC_LESS(o)}
	bool CUShort::operator >(const CBaseData& o) const {DYNAMIC_MORE(o)}
	bool CUShort::operator ==(const CBaseData& o) const {DYNAMIC_EQUAL(o)}
	bool CUShort::operator !=(const CBaseData& o) const {DYNAMIC_NOT_EQUAL(o)}
	bool CUShort::operator <=(const CBaseData& o) const {DYNAMIC_LESS_EQUAL(o)}
	bool CUShort::operator >=(const CBaseData& o) const {DYNAMIC_MORE_EQUAL(o)}
	CUShort::operator char(void) const {return this->m_data;}
	CUShort::operator unsigned char(void) const {return this->m_data;}
	CUShort::operator short(void) const {return this->m_data;}
	CUShort::operator unsigned short(void) const {return this->m_data;}
	CUShort::operator int(void) const {return this->m_data;}
	CUShort::operator unsigned int(void) const {return this->m_data;}
	CUShort::operator long(void) const {return this->m_data;}
	CUShort::operator unsigned long(void) const {return this->m_data;}
	CUShort::operator long long(void) const {return this->m_data;}
	CUShort::operator unsigned long long(void) const {return this->m_data;}
	CUShort::operator float(void) const {return this->m_data;}
	CUShort::operator double(void) const {return this->m_data;}
	CUShort::operator long double(void) const {return this->m_data;}
	CUShort::operator string(void) const {ostringstream oss; oss << this->m_data; return oss.str();}
	size_t CUShort::GetSize() const {return sizeof (this->m_data);}

	////////////////////////CInt的实现//////////////////////////////////////////////////
	CBaseData CInt::operator +(void) const {return this->m_data;}
	CBaseData CInt::operator -(void) const {return -this->m_data;}
	CBaseData CInt::operator +(const CBaseData& o) const {DYNAMIC_SUM(o)}
	CBaseData CInt::operator -(const CBaseData& o) const {	DYNAMIC_SUB(o)}
	CBaseData CInt::operator *(const CBaseData& o) const {DYNAMIC_MUL(o)}
	CBaseData CInt::operator /(const CBaseData& o) const {	DYNAMIC_DIV(o)}
	CBaseData CInt::operator %(const CBaseData& o) const {DYNAMIC_MOD(o)}
	bool CInt::operator <(const CBaseData& o) const {	DYNAMIC_LESS(o)}
	bool CInt::operator >(const CBaseData& o) const {DYNAMIC_MORE(o)}
	bool CInt::operator ==(const CBaseData& o) const {DYNAMIC_EQUAL(o)}
	bool CInt::operator !=(const CBaseData& o) const {DYNAMIC_NOT_EQUAL(o)}
	bool CInt::operator <=(const CBaseData& o) const {DYNAMIC_LESS_EQUAL(o)}
	bool CInt::operator >=(const CBaseData& o) const {DYNAMIC_MORE_EQUAL(o)}
	CInt::operator char(void) const {return this->m_data;}
	CInt::operator unsigned char(void) const {return this->m_data;}
	CInt::operator short(void) const {return this->m_data;}
	CInt::operator unsigned short(void) const {return this->m_data;}
	CInt::operator int(void) const {return this->m_data;}
	CInt::operator unsigned int(void) const {return this->m_data;}
	CInt::operator long(void) const {return this->m_data;}
	CInt::operator unsigned long(void) const {return this->m_data;}
	CInt::operator long long(void) const {return this->m_data;}
	CInt::operator unsigned long long(void) const {return this->m_data;}
	CInt::operator float(void) const {return this->m_data;}
	CInt::operator double(void) const {return this->m_data;}
	CInt::operator long double(void) const {return this->m_data;}
	CInt::operator string(void) const {ostringstream oss; oss << this->m_data; return oss.str();}
	size_t CInt::GetSize() const {return sizeof (this->m_data);}

	////////////////////////CUInt的实现//////////////////////////////////////////////////
	CBaseData CUInt::operator +(void) const {return this->m_data;}
	CBaseData CUInt::operator -(void) const {return -this->m_data;}
	CBaseData CUInt::operator +(const CBaseData& o) const {DYNAMIC_SUM(o)}
	CBaseData CUInt::operator -(const CBaseData& o) const {DYNAMIC_SUB(o)}
	CBaseData CUInt::operator *(const CBaseData& o) const {DYNAMIC_MUL(o)}
	CBaseData CUInt::operator /(const CBaseData& o) const {DYNAMIC_DIV(o)}
	CBaseData CUInt::operator %(const CBaseData& o) const {DYNAMIC_MOD(o)}
	bool CUInt::operator <(const CBaseData& o) const {	DYNAMIC_LESS(o)}
	bool CUInt::operator >(const CBaseData& o) const {DYNAMIC_MORE(o)}
	bool CUInt::operator ==(const CBaseData& o) const {DYNAMIC_EQUAL(o)}
	bool CUInt::operator !=(const CBaseData& o) const {DYNAMIC_NOT_EQUAL(o)}
	bool CUInt::operator <=(const CBaseData& o) const {DYNAMIC_LESS_EQUAL(o)}
	bool CUInt::operator >=(const CBaseData& o) const {DYNAMIC_MORE_EQUAL(o)}
	CUInt::operator char(void) const {return this->m_data;}
	CUInt::operator unsigned char(void) const {return this->m_data;}
	CUInt::operator short(void) const {return this->m_data;}
	CUInt::operator unsigned short(void) const {return this->m_data;}
	CUInt::operator int(void) const {return this->m_data;}
	CUInt::operator unsigned int(void) const {return this->m_data;}
	CUInt::operator long(void) const {return this->m_data;}
	CUInt::operator unsigned long(void) const {return this->m_data;}
	CUInt::operator long long(void) const {return this->m_data;}
	CUInt::operator unsigned long long(void) const {return this->m_data;}
	CUInt::operator float(void) const {return this->m_data;}
	CUInt::operator double(void) const {return this->m_data;}
	CUInt::operator long double(void) const {return this->m_data;}
	CUInt::operator string(void) const {ostringstream oss; oss << this->m_data; return oss.str();}
	size_t CUInt::GetSize() const {return sizeof (this->m_data);}

	////////////////////////CLong的实现//////////////////////////////////////////////////
	CBaseData CLong::operator +(void) const {return this->m_data;}
	CBaseData CLong::operator -(void) const {return -this->m_data;}
	CBaseData CLong::operator +(const CBaseData& o) const {DYNAMIC_SUM(o)}
	CBaseData CLong::operator -(const CBaseData& o) const {DYNAMIC_SUB(o)}
	CBaseData CLong::operator *(const CBaseData& o) const {DYNAMIC_MUL(o)}
	CBaseData CLong::operator /(const CBaseData& o) const {DYNAMIC_DIV(o)}
	CBaseData CLong::operator %(const CBaseData& o) const {DYNAMIC_MOD(o)}
	bool CLong::operator <(const CBaseData& o) const {	DYNAMIC_LESS(o)}
	bool CLong::operator >(const CBaseData& o) const {DYNAMIC_MORE(o)}
	bool CLong::operator ==(const CBaseData& o) const {DYNAMIC_EQUAL(o)}
	bool CLong::operator !=(const CBaseData& o) const {DYNAMIC_NOT_EQUAL(o)}
	bool CLong::operator <=(const CBaseData& o) const {DYNAMIC_LESS_EQUAL(o)}
	bool CLong::operator >=(const CBaseData& o) const {DYNAMIC_MORE_EQUAL(o)}
	CLong::operator char(void) const {return this->m_data;}
	CLong::operator unsigned char(void) const {return this->m_data;}
	CLong::operator short(void) const {return this->m_data;}
	CLong::operator unsigned short(void) const {return this->m_data;}
	CLong::operator int(void) const {return this->m_data;}
	CLong::operator unsigned int(void) const {return this->m_data;}
	CLong::operator long(void) const {return this->m_data;}
	CLong::operator unsigned long(void) const {return this->m_data;}
	CLong::operator long long(void) const {return this->m_data;}
	CLong::operator unsigned long long(void) const {return this->m_data;}
	CLong::operator float(void) const {return this->m_data;}
	CLong::operator double(void) const {return this->m_data;}
	CLong::operator long double(void) const {return this->m_data;}
	CLong::operator string(void) const {ostringstream oss; oss << this->m_data; return oss.str();}
	size_t CLong::GetSize() const {return sizeof (this->m_data);}

	////////////////////////CULong的实现//////////////////////////////////////////////////
	CBaseData CULong::operator +(void) const {return this->m_data;}
	CBaseData CULong::operator -(void) const {return -this->m_data;}
	CBaseData CULong::operator +(const CBaseData& o) const {DYNAMIC_SUM(o)}
	CBaseData CULong::operator -(const CBaseData& o) const {DYNAMIC_SUB(o)}
	CBaseData CULong::operator *(const CBaseData& o) const {DYNAMIC_MUL(o)}
	CBaseData CULong::operator /(const CBaseData& o) const {DYNAMIC_DIV(o)}
	CBaseData CULong::operator %(const CBaseData& o) const {DYNAMIC_MOD(o)}
	bool CULong::operator <(const CBaseData& o) const {	DYNAMIC_LESS(o)}
	bool CULong::operator >(const CBaseData& o) const {DYNAMIC_MORE(o)}
	bool CULong::operator ==(const CBaseData& o) const {DYNAMIC_EQUAL(o)}
	bool CULong::operator !=(const CBaseData& o) const {DYNAMIC_NOT_EQUAL(o)}
	bool CULong::operator <=(const CBaseData& o) const {DYNAMIC_LESS_EQUAL(o)}
	bool CULong::operator >=(const CBaseData& o) const {DYNAMIC_MORE_EQUAL(o)}
	CULong::operator char(void) const {return this->m_data;}
	CULong::operator unsigned char(void) const {return this->m_data;}
	CULong::operator short(void) const {return this->m_data;}
	CULong::operator unsigned short(void) const {return this->m_data;}
	CULong::operator int(void) const {return this->m_data;}
	CULong::operator unsigned int(void) const {return this->m_data;}
	CULong::operator long(void) const {return this->m_data;}
	CULong::operator unsigned long(void) const {return this->m_data;}
	CULong::operator long long(void) const {return this->m_data;}
	CULong::operator unsigned long long(void) const {return this->m_data;}
	CULong::operator float(void) const {return this->m_data;}
	CULong::operator double(void) const {return this->m_data;}
	CULong::operator long double(void) const {return this->m_data;}
	CULong::operator string(void) const {ostringstream oss; oss << this->m_data; return oss.str();}
	size_t CULong::GetSize() const {return sizeof (this->m_data);}

	////////////////////////CLongLong的实现//////////////////////////////////////////////////
	CBaseData CLongLong::operator +(void) const {return this->m_data;}
	CBaseData CLongLong::operator -(void) const {return -this->m_data;}
	CBaseData CLongLong::operator +(const CBaseData& o) const {DYNAMIC_SUM(o)}
	CBaseData CLongLong::operator -(const CBaseData& o) const {DYNAMIC_SUB(o)}
	CBaseData CLongLong::operator *(const CBaseData& o) const {DYNAMIC_MUL(o)}
	CBaseData CLongLong::operator /(const CBaseData& o) const {DYNAMIC_DIV(o)}
	CBaseData CLongLong::operator %(const CBaseData& o) const {DYNAMIC_MOD(o)}
	bool CLongLong::operator <(const CBaseData& o) const {	DYNAMIC_LESS(o)}
	bool CLongLong::operator >(const CBaseData& o) const {DYNAMIC_MORE(o)}
	bool CLongLong::operator ==(const CBaseData& o) const {DYNAMIC_EQUAL(o)}
	bool CLongLong::operator !=(const CBaseData& o) const {DYNAMIC_NOT_EQUAL(o)}
	bool CLongLong::operator <=(const CBaseData& o) const {DYNAMIC_LESS_EQUAL(o)}
	bool CLongLong::operator >=(const CBaseData& o) const {DYNAMIC_MORE_EQUAL(o)}
	CLongLong::operator char(void) const {return this->m_data;}
	CLongLong::operator unsigned char(void) const {return this->m_data;}
	CLongLong::operator short(void) const {return this->m_data;}
	CLongLong::operator unsigned short(void) const {return this->m_data;}
	CLongLong::operator int(void) const {return this->m_data;}
	CLongLong::operator unsigned int(void) const {return this->m_data;}
	CLongLong::operator long(void) const {return this->m_data;}
	CLongLong::operator unsigned long(void) const {return this->m_data;}
	CLongLong::operator long long(void) const {return this->m_data;}
	CLongLong::operator unsigned long long(void) const {return this->m_data;}
	CLongLong::operator float(void) const {return this->m_data;}
	CLongLong::operator double(void) const {return this->m_data;}
	CLongLong::operator long double(void) const {return this->m_data;}
	CLongLong::operator string(void) const {ostringstream oss; oss << this->m_data; return oss.str();}
	size_t CLongLong::GetSize() const {return sizeof (this->m_data);}

	////////////////////////CULongLong的实现//////////////////////////////////////////////////
	CBaseData CULongLong::operator +(void) const {return this->m_data;}
	CBaseData CULongLong::operator -(void) const {return -this->m_data;}
	CBaseData CULongLong::operator +(const CBaseData& o) const {DYNAMIC_SUM(o)}
	CBaseData CULongLong::operator -(const CBaseData& o) const {DYNAMIC_SUB(o)}
	CBaseData CULongLong::operator *(const CBaseData& o) const {DYNAMIC_MUL(o)}
	CBaseData CULongLong::operator /(const CBaseData& o) const {DYNAMIC_DIV(o)}
	CBaseData CULongLong::operator %(const CBaseData& o) const {DYNAMIC_MOD(o)}
	bool CULongLong::operator <(const CBaseData& o) const {	DYNAMIC_LESS(o)}
	bool CULongLong::operator >(const CBaseData& o) const {DYNAMIC_MORE(o)}
	bool CULongLong::operator ==(const CBaseData& o) const {DYNAMIC_EQUAL(o)}
	bool CULongLong::operator !=(const CBaseData& o) const {DYNAMIC_NOT_EQUAL(o)}
	bool CULongLong::operator <=(const CBaseData& o) const {DYNAMIC_LESS_EQUAL(o)}
	bool CULongLong::operator >=(const CBaseData& o) const {DYNAMIC_MORE_EQUAL(o)}
	CULongLong::operator char(void) const {return this->m_data;}
	CULongLong::operator unsigned char(void) const {return this->m_data;}
	CULongLong::operator short(void) const {return this->m_data;}
	CULongLong::operator unsigned short(void) const {return this->m_data;}
	CULongLong::operator int(void) const {return this->m_data;}
	CULongLong::operator unsigned int(void) const {return this->m_data;}
	CULongLong::operator long(void) const {return this->m_data;}
	CULongLong::operator unsigned long(void) const {return this->m_data;}
	CULongLong::operator long long(void) const {return this->m_data;}
	CULongLong::operator unsigned long long(void) const {return this->m_data;}
	CULongLong::operator float(void) const {return this->m_data;}
	CULongLong::operator double(void) const {return this->m_data;}
	CULongLong::operator long double(void) const {return this->m_data;}
	CULongLong::operator string(void) const {ostringstream oss; oss << this->m_data; return oss.str();}
	size_t CULongLong::GetSize() const {return sizeof (this->m_data);}

	////////////////////////CFloat的实现//////////////////////////////////////////////////
	CBaseData CFloat::operator +(void) const {return this->m_data;}
	CBaseData CFloat::operator -(void) const {return -this->m_data;}
	CBaseData CFloat::operator +(const CBaseData& o) const {DYNAMIC_SUM(o)}
	CBaseData CFloat::operator -(const CBaseData& o) const {DYNAMIC_SUB(o);	}
	CBaseData CFloat::operator *(const CBaseData& o) const {DYNAMIC_MUL(o)}
	CBaseData CFloat::operator /(const CBaseData& o) const {DYNAMIC_DIV(o);}
	CBaseData CFloat::operator %(const CBaseData&) const {throw exceptionx("Invalid Operation");}
	bool CFloat::operator <(const CBaseData& o) const {	DYNAMIC_LESS(o)}
	bool CFloat::operator >(const CBaseData& o) const {DYNAMIC_MORE(o)}
	bool CFloat::operator ==(const CBaseData& o) const {DYNAMIC_EQUAL(o)}
	bool CFloat::operator !=(const CBaseData& o) const {DYNAMIC_NOT_EQUAL(o)}
	bool CFloat::operator <=(const CBaseData& o) const {DYNAMIC_LESS_EQUAL(o)}
	bool CFloat::operator >=(const CBaseData& o) const {DYNAMIC_MORE_EQUAL(o)}
	CFloat::operator char(void) const {return this->m_data;}
	CFloat::operator unsigned char(void) const {return this->m_data;}
	CFloat::operator short(void) const {return this->m_data;}
	CFloat::operator unsigned short(void) const {return this->m_data;}
	CFloat::operator int(void) const {return this->m_data;}
	CFloat::operator unsigned int(void) const {return this->m_data;}
	CFloat::operator long(void) const {return this->m_data;}
	CFloat::operator unsigned long(void) const {return this->m_data;}
	CFloat::operator long long(void) const {return this->m_data;}
	CFloat::operator unsigned long long(void) const {return this->m_data;}
	CFloat::operator float(void) const {return this->m_data;}
	CFloat::operator double(void) const {return this->m_data;}
	CFloat::operator long double(void) const {return this->m_data;}
	CFloat::operator string(void) const {ostringstream oss; oss << this->m_data; return oss.str();}
	size_t CFloat::GetSize() const {return sizeof (this->m_data);}

	////////////////////////CDouble的实现//////////////////////////////////////////////////
	CBaseData CDouble::operator +(void) const {return this->m_data;}
	CBaseData CDouble::operator -(void) const {return -this->m_data;}
	CBaseData CDouble::operator +(const CBaseData& o) const {DYNAMIC_SUM(o)}
	CBaseData CDouble::operator -(const CBaseData& o) const 	{DYNAMIC_SUB(o)}
	CBaseData CDouble::operator *(const CBaseData& o) const {DYNAMIC_MUL(o)}
	CBaseData CDouble::operator /(const CBaseData& o) const 	{DYNAMIC_DIV(o)}
	CBaseData CDouble::operator %(const CBaseData&) const {throw exceptionx("Invalid Operation");}
	bool CDouble::operator <(const CBaseData& o) const {DYNAMIC_LESS(o)}
	bool CDouble::operator >(const CBaseData& o) const {DYNAMIC_MORE(o)}
	bool CDouble::operator ==(const CBaseData& o) const {DYNAMIC_EQUAL(o)}
	bool CDouble::operator !=(const CBaseData& o) const {DYNAMIC_NOT_EQUAL(o)}
	bool CDouble::operator <=(const CBaseData& o) const {DYNAMIC_LESS_EQUAL(o)}
	bool CDouble::operator >=(const CBaseData& o) const {DYNAMIC_MORE_EQUAL(o)}
	CDouble::operator char(void) const {return this->m_data;}
	CDouble::operator unsigned char(void) const {return this->m_data;}
	CDouble::operator short(void) const {return this->m_data;}
	CDouble::operator unsigned short(void) const {return this->m_data;}
	CDouble::operator int(void) const {return this->m_data;}
	CDouble::operator unsigned int(void) const {return this->m_data;}
	CDouble::operator long(void) const {return this->m_data;}
	CDouble::operator unsigned long(void) const {return this->m_data;}
	CDouble::operator long long(void) const {return this->m_data;}
	CDouble::operator unsigned long long(void) const {return this->m_data;}
	CDouble::operator float(void) const {return this->m_data;}
	CDouble::operator double(void) const {return this->m_data;}
	CDouble::operator long double(void) const {return this->m_data;}
	CDouble::operator string(void) const {ostringstream oss; oss << this->m_data; return oss.str();}
	size_t CDouble::GetSize() const {return sizeof (this->m_data);}

	////////////////////////CDouble的实现//////////////////////////////////////////////////
	CBaseData CLongDouble::operator +(void) const {return this->m_data;}
	CBaseData CLongDouble::operator -(void) const {return -this->m_data;}
	CBaseData CLongDouble::operator +(const CBaseData& o) const {DYNAMIC_SUM(o)}
	CBaseData CLongDouble::operator -(const CBaseData& o) const 	{DYNAMIC_SUB(o)}
	CBaseData CLongDouble::operator *(const CBaseData& o) const {DYNAMIC_MUL(o)}
	CBaseData CLongDouble::operator /(const CBaseData& o) const 	{DYNAMIC_DIV(o)}
	CBaseData CLongDouble::operator %(const CBaseData&) const {throw exceptionx("Invalid Operation");}
	bool CLongDouble::operator <(const CBaseData& o) const {DYNAMIC_LESS(o)}
	bool CLongDouble::operator >(const CBaseData& o) const {DYNAMIC_MORE(o)}
	bool CLongDouble::operator ==(const CBaseData& o) const {DYNAMIC_EQUAL(o)}
	bool CLongDouble::operator !=(const CBaseData& o) const {DYNAMIC_NOT_EQUAL(o)}
	bool CLongDouble::operator <=(const CBaseData& o) const {DYNAMIC_LESS_EQUAL(o)}
	bool CLongDouble::operator >=(const CBaseData& o) const {DYNAMIC_MORE_EQUAL(o)}
	CLongDouble::operator char(void) const {return this->m_data;}
	CLongDouble::operator unsigned char(void) const {return this->m_data;}
	CLongDouble::operator short(void) const {return this->m_data;}
	CLongDouble::operator unsigned short(void) const {return this->m_data;}
	CLongDouble::operator int(void) const {return this->m_data;}
	CLongDouble::operator unsigned int(void) const {return this->m_data;}
	CLongDouble::operator long(void) const {return this->m_data;}
	CLongDouble::operator unsigned long(void) const {return this->m_data;}
	CLongDouble::operator long long(void) const {return this->m_data;}
	CLongDouble::operator unsigned long long(void) const {return this->m_data;}
	CLongDouble::operator float(void) const {return this->m_data;}
	CLongDouble::operator double(void) const {return this->m_data;}
	CLongDouble::operator long double(void) const {return this->m_data;}
	CLongDouble::operator string(void) const {ostringstream oss; oss << this->m_data; return oss.str();}
	size_t CLongDouble::GetSize() const {return sizeof (this->m_data);}

	/////////////////////////CBaseData的实现/////////////////////////////////////////////////
	CBaseData::CBaseData(void) {this->m_pBase = new CInt;}

#define MULTIPLE_CONSTRUCTOR(TypeName, ClassName) \
	{\
		TypeName data;\
		bError = (NULL == iss >> data);\
		if (!bError)\
		{\
			this->m_pBase = new ClassName(data, strName);\
		}\
	}

	CBaseData::CBaseData(const string& strNumber, EDataType eType, const string& strName)
	{
		std::istringstream iss(strNumber);
		bool bError = false;

		switch (eType)
		{
		case CHAR:
			MULTIPLE_CONSTRUCTOR(char, CChar)
			break;
		case UCHAR:
			MULTIPLE_CONSTRUCTOR(unsigned char, CUChar)
			break;
		case BYTE:
		case UBYTE:
			{
				short s;
				bError = (NULL == iss >> s);
				if (!bError)
				{
					BYTE == eType ? this->m_pBase = new CChar(s, strName) : this->m_pBase = new CUChar(s, strName);
				}
			}
			break;
		case SHORT:
			MULTIPLE_CONSTRUCTOR(short, CShort)
			break;
		case USHORT:
			MULTIPLE_CONSTRUCTOR(unsigned short, CUShort)
			break;
		case INT:
			MULTIPLE_CONSTRUCTOR(int, CInt)
			break;
		case UINT:
			MULTIPLE_CONSTRUCTOR(unsigned int, CUInt)
			break;
		case LONG:
			MULTIPLE_CONSTRUCTOR(long, CLong)
			break;
		case ULONG:
			MULTIPLE_CONSTRUCTOR(unsigned long, CULong)
			break;
		case LONGLONG:
			MULTIPLE_CONSTRUCTOR(long long, CLongLong)
			break;
		case ULONGLONG:
			MULTIPLE_CONSTRUCTOR(unsigned long long, CULongLong)
			break;
		case FLOAT:
			MULTIPLE_CONSTRUCTOR(float, CFloat)
			break;
		case DOUBLE:
			MULTIPLE_CONSTRUCTOR(double, CDouble)
			break;
		case LONGDOUBLE:
			MULTIPLE_CONSTRUCTOR(long double, CLongDouble)
			break;
		default:
			throw exceptionx("Unknow Type");
			break;
		}

		if (bError)
		{
			delete this->m_pBase;
			throw exceptionx("Invalid Number");
		}
	}

	CBaseData::CBaseData(const void* pBinary, EDataType eType, const string& strName)
	{
		switch (eType)
		{
		case CHAR:
		case BYTE:
			this->m_pBase = new CChar(*reinterpret_cast<const char*>(pBinary), strName);
			break;
		case UCHAR:
		case UBYTE:
			this->m_pBase = new CUChar(*reinterpret_cast<const unsigned char*>(pBinary), strName);
			break;
		case SHORT:
			this->m_pBase = new CShort(*reinterpret_cast<const short*>(pBinary), strName);
			break;
		case USHORT:
			this->m_pBase = new CUShort(*reinterpret_cast<const unsigned short*>(pBinary), strName);
			break;
		case INT:
			this->m_pBase = new CInt(*reinterpret_cast<const int*>(pBinary), strName);
			break;
		case UINT:
			this->m_pBase = new CUInt(*reinterpret_cast<const unsigned int*>(pBinary), strName);
			break;
		case LONG:
			this->m_pBase = new CLong(*reinterpret_cast<const long*>(pBinary), strName);
			break;
		case ULONG:
			this->m_pBase = new CULong(*reinterpret_cast<const unsigned long*>(pBinary), strName);
			break;
		case LONGLONG:
			this->m_pBase = new CLongLong(*reinterpret_cast<const long long*>(pBinary), strName);
			break;
		case ULONGLONG:
			this->m_pBase = new CULongLong(*reinterpret_cast<const unsigned long long*>(pBinary), strName);
			break;
		case FLOAT:
			this->m_pBase = new CFloat(*reinterpret_cast<const float*>(pBinary), strName);
			break;
		case DOUBLE:
			this->m_pBase = new CDouble(*reinterpret_cast<const double*>(pBinary), strName);
			break;
		case LONGDOUBLE:
			this->m_pBase = new CLongDouble(*reinterpret_cast<const long double*>(pBinary), strName);
			break;
		default:
			throw exceptionx("Unknow Type");
			break;
		}
	}

	CBaseData CBaseData::operator +(void) const {return this->m_pBase->operator +();}
	CBaseData CBaseData::operator -(void) const {return this->m_pBase->operator -();}
	CBaseData CBaseData::operator +(const CBaseData& o) const {return this->m_pBase->operator +(o);}
	CBaseData CBaseData::operator -(const CBaseData& o) const {return this->m_pBase->operator -(o);}
	CBaseData CBaseData::operator *(const CBaseData& o) const {return this->m_pBase->operator *(o);}
	CBaseData CBaseData::operator /(const CBaseData& o) const 	{return this->m_pBase->operator /(o);}
	CBaseData CBaseData::operator %(const CBaseData& o) const {return this->m_pBase->operator %(o);}
	bool CBaseData::operator <(const CBaseData& o) const {return this->m_pBase->operator <(o);}
	bool CBaseData::operator >(const CBaseData& o) const {return this->m_pBase->operator >(o);}
	bool CBaseData::operator ==(const CBaseData& o) const {return this->m_pBase->operator ==(o);}
	bool CBaseData::operator !=(const CBaseData& o) const {return this->m_pBase->operator !=(o);}
	bool CBaseData::operator <=(const CBaseData& o) const {return this->m_pBase->operator <=(o);}
	bool CBaseData::operator >=(const CBaseData& o) const {return this->m_pBase->operator >=(o);}
	CBaseData::operator char(void) const {return this->m_pBase->operator char();}
	CBaseData::operator unsigned char(void) const {return this->m_pBase->operator unsigned char();}
	CBaseData::operator short(void) const {return this->m_pBase->operator short();}
	CBaseData::operator unsigned short(void) const {return this->m_pBase->operator unsigned short();}
	CBaseData::operator int(void) const {return this->m_pBase->operator int();}
	CBaseData::operator unsigned int(void) const {return this->m_pBase->operator unsigned int();}
	CBaseData::operator long(void) const {return this->m_pBase->operator long();}
	CBaseData::operator unsigned long(void) const {return this->m_pBase->operator unsigned long();}
	CBaseData::operator long long(void) const {return this->m_pBase->operator long long();}
	CBaseData::operator unsigned long long(void) const {return this->m_pBase->operator unsigned long long();}
	CBaseData::operator float(void) const {return this->m_pBase->operator float();}
	CBaseData::operator double(void) const {return this->m_pBase->operator double();}
	CBaseData::operator long double(void) const {return this->m_pBase->operator long double();}
	CBaseData::operator string(void) const {return this->m_pBase->operator string();}
	size_t CBaseData::GetSize() const {return this->m_pBase->GetSize();}

	///////////////////////全局函数///////////////////////////////////////////////////
	ostream& operator <<(ostream& oStream, const CBaseData& oBaseData) {return oBaseData.m_pBase->Print(oStream);}
}
#include "VersionControl.h"
#include "DataType/SimpleData.h"
#include "MyTools/MyUtilityTools.h"

namespace DataType
{
	using MyTools::Trim;

	const char* const STRING_CHAR =  "char";
	const char* const STRING_UCHAR = "unsigned char";
	const char* const STRING_SHORT = "short";
	const char* const STRING_USHORT = "unsigned short";
	const char* const STRING_INT = "int";
	const char* const STRING_UINT = "unsigned int";
	const char* const STRING_LONGLONG = "long long";
	const char* const STRING_ULONGLONG = "unsigned long long";
	const char* const STRING_SINGLE = "single";
	const char* const STRING_DOUBLE = "double";
	const char* const STRING_STRING = "string";
	const char* TYPE_STRINGS[] = {STRING_CHAR, STRING_UCHAR, STRING_SHORT, STRING_USHORT, STRING_INT, STRING_UINT, STRING_LONGLONG, STRING_ULONGLONG, STRING_SINGLE, STRING_DOUBLE, STRING_STRING};

	EType WhichType(const string& strTypeName)
	{
		if (!strTypeName.compare(STRING_CHAR))
		{
			return ID_CHAR;
		}else if (!strTypeName.compare(STRING_UCHAR))
		{
			return ID_UCHAR;
		}else if (!strTypeName.compare(STRING_SHORT))
		{
			return ID_SHORT;
		}else if (!strTypeName.compare(STRING_USHORT))
		{
			return ID_USHOR;
		}else if (!strTypeName.compare(STRING_INT))
		{
			return ID_INT;
		}else if (!strTypeName.compare(STRING_UINT))
		{
			return ID_UINT;
		}else if (!strTypeName.compare(STRING_LONGLONG))
		{
			return ID_LONGLONG;
		}else if (!strTypeName.compare(STRING_ULONGLONG))
		{
			return ID_ULONGLONG;
		}else if (!strTypeName.compare(STRING_SINGLE))
		{
			return ID_SINGLE;
		}else if (!strTypeName.compare(STRING_DOUBLE))
		{
			return ID_DOUBLE;
		}
		else
		{
			return ID_STRING;
		}
	}

	CSimpleData::CSimpleData(char data, const string& strDataName) : m_strTypeName(STRING_CHAR), m_strDataName(strDataName), m_i8Precision(0), m_bIsSuccessful(true)
	{
		stringstream strstr;

		this->m_strRawValue.assign(reinterpret_cast<const char*> (&data), sizeof (char));
		strstr << static_cast<short>(data);
		strstr >> this->m_strFormatedValue;
	}

	CSimpleData::CSimpleData(unsigned char data, const string& strDataName) : m_strTypeName(STRING_UCHAR), m_strDataName(strDataName), m_i8Precision(0), m_bIsSuccessful(true)
	{
		stringstream strstr;

		this->m_strRawValue.assign(reinterpret_cast<const char*> (&data), sizeof (unsigned char));
		strstr << static_cast<unsigned short>(data);
		strstr >> this->m_strFormatedValue;
	}

	CSimpleData::CSimpleData(short data, const string& strDataName) : m_strTypeName(STRING_SHORT), m_strDataName(strDataName), m_i8Precision(0), m_bIsSuccessful(true)
	{
		stringstream strstr;

		this->m_strRawValue.assign(reinterpret_cast<const char*> (&data), sizeof (short));
		strstr << data;
		strstr >> this->m_strFormatedValue;
	}

	CSimpleData::CSimpleData(unsigned short data, const string& strDataName) : m_strTypeName(STRING_USHORT), m_strDataName(strDataName), m_i8Precision(0), m_bIsSuccessful(true)
	{
		stringstream strstr;

		this->m_strRawValue.assign(reinterpret_cast<const char*> (&data), sizeof (unsigned short));
		strstr << data;
		strstr >> this->m_strFormatedValue;
	}

	CSimpleData::CSimpleData(int data, const string& strDataName) : m_strTypeName(STRING_INT), m_strDataName(strDataName), m_i8Precision(0), m_bIsSuccessful(true)
	{
		stringstream strstr;

		this->m_strRawValue.assign(reinterpret_cast<const char*> (&data), sizeof (int));
		strstr << data;
		strstr >> this->m_strFormatedValue;
	}

	CSimpleData::CSimpleData(unsigned int data, const string& strDataName) : m_strTypeName(STRING_UINT), m_strDataName(strDataName), m_i8Precision(0), m_bIsSuccessful(true)
	{
		stringstream strstr;

		this->m_strRawValue.assign(reinterpret_cast<const char*> (&data), sizeof (unsigned int));
		strstr << data;
		strstr >> this->m_strFormatedValue;
	}

	CSimpleData::CSimpleData(long long data, const string& strDataName) : m_strTypeName(STRING_LONGLONG), m_strDataName(strDataName), m_i8Precision(0), m_bIsSuccessful(true)
	{
		stringstream strstr;

		this->m_strRawValue.assign(reinterpret_cast<const char*> (&data), sizeof (long long));
		strstr << data;
		strstr >> this->m_strFormatedValue;
	}

	CSimpleData::CSimpleData(unsigned long long data, const string& strDataName) : m_strTypeName(STRING_ULONGLONG), m_strDataName(strDataName), m_i8Precision(0), m_bIsSuccessful(true)
	{
		stringstream strstr;

		this->m_strRawValue.assign(reinterpret_cast<const char*> (&data), sizeof (unsigned long long));
		strstr << data;
		strstr >> this->m_strFormatedValue;
	}

	CSimpleData::CSimpleData(float data, const string& strDataName, char i8Precision) : m_strTypeName(STRING_SINGLE), m_strDataName(strDataName), m_i8Precision(i8Precision), m_bIsSuccessful(true)
	{
		stringstream strstr;

		if (this->m_i8Precision < 0)
		{
			strstr.setf(ios::fixed, ios::floatfield);
			strstr.precision(-this->m_i8Precision);
		}
		else
		{
			strstr.precision(this->m_i8Precision);
		}

		this->m_strRawValue.assign(reinterpret_cast<const char*> (&data), sizeof (float));
		strstr << data;
		strstr >> this->m_strFormatedValue;
	}

	CSimpleData::CSimpleData(double data, const string& strDataName, char i8Precision) : m_strTypeName(STRING_DOUBLE), m_strDataName(strDataName), m_i8Precision(i8Precision), m_bIsSuccessful(true)
	{
		stringstream strstr;

		if (this->m_i8Precision < 0)
		{
			strstr.setf(ios::fixed, ios::floatfield);
			strstr.precision(-this->m_i8Precision);
		}
		else
		{
			strstr.precision(this->m_i8Precision);
		}

		this->m_strRawValue.assign(reinterpret_cast<const char*> (&data), sizeof (double));
		strstr << data;
		strstr >> this->m_strFormatedValue;
	}

	CSimpleData::CSimpleData(const string& str, const string& strDataName) : m_strTypeName(STRING_STRING), m_strDataName(strDataName), m_i8Precision(0), m_bIsSuccessful(true)
	{
		this->m_strRawValue = this->m_strFormatedValue = str;
	}

	CSimpleData::CSimpleData(string strType, string strValue, const string& strDataName, char i8Precision) : m_strTypeName(Trim(strType)), m_strDataName(strDataName), m_i8Precision(i8Precision), m_bIsSuccessful(true)
	{
		string oldStr(strValue);

		istringstream istrstr(Trim(strValue));
		ostringstream ostrstr;

		if (i8Precision < 0)
		{
			ostrstr.setf(ios::fixed, ios::floatfield);
			ostrstr.precision(-this->m_i8Precision);
		}
		else
		{
			ostrstr.precision(this->m_i8Precision);
		}

		if (STRING_CHAR == this->m_strTypeName )
		{
			char temp;
			istrstr >> temp;
			this->m_bIsSuccessful = istrstr.eof();
			this->m_strRawValue.assign(reinterpret_cast <char*> (&temp), sizeof (temp));
			ostrstr << temp;
			this->m_strFormatedValue = ostrstr.str();
		} else if (STRING_UCHAR == this->m_strTypeName)
		{
			unsigned char temp;
			istrstr >> temp;
			this->m_bIsSuccessful = istrstr.eof();
			this->m_strRawValue.assign(reinterpret_cast <char*> (&temp), sizeof (temp));
			ostrstr <<  temp;
			this->m_strFormatedValue = ostrstr.str();
		} else if (STRING_SHORT == this->m_strTypeName)
		{
			short temp;
			istrstr >> temp;
			this->m_bIsSuccessful = istrstr.eof();
			this->m_strRawValue.assign(reinterpret_cast <char*> (&temp), sizeof (temp));
			ostrstr << temp;
			this->m_strFormatedValue = ostrstr.str();
		} else if (STRING_USHORT == this->m_strTypeName)
		{
			unsigned short temp;
			istrstr >> temp;
			this->m_bIsSuccessful = istrstr.eof();
			this->m_strRawValue.assign(reinterpret_cast <char*> (&temp), sizeof (temp));
			ostrstr << temp;
			this->m_strFormatedValue = ostrstr.str();
		} else if (STRING_INT == this->m_strTypeName)
		{
			int temp;
			istrstr >> temp;
			this->m_bIsSuccessful = istrstr.eof();
			this->m_strRawValue.assign(reinterpret_cast <char*> (&temp), sizeof (temp));
			ostrstr << temp;
			this->m_strFormatedValue = ostrstr.str();
		} else if (STRING_UINT == this->m_strTypeName)
		{
			unsigned int temp;
			istrstr >> temp;
			this->m_bIsSuccessful = istrstr.eof();
			this->m_strRawValue.assign(reinterpret_cast <char*> (&temp), sizeof (temp));
			ostrstr << temp;
			this->m_strFormatedValue = ostrstr.str();
		} else if (STRING_LONGLONG == this->m_strTypeName)
		{
			long long temp;
			istrstr >> temp;
			this->m_bIsSuccessful = istrstr.eof();
			this->m_strRawValue.assign(reinterpret_cast <char*> (&temp), sizeof (temp));
			ostrstr << temp;
			this->m_strFormatedValue = ostrstr.str();
		} else if (STRING_ULONGLONG == this->m_strTypeName)
		{
			unsigned long long temp;
			istrstr >> temp;
			this->m_bIsSuccessful = istrstr.eof();
			this->m_strRawValue.assign(reinterpret_cast <char*> (&temp), sizeof (temp));
			ostrstr << temp;
			this->m_strFormatedValue = ostrstr.str();
		} else if (STRING_SINGLE == this->m_strTypeName)
		{
			float temp;
			istrstr >> temp;
			this->m_bIsSuccessful = istrstr.eof();
			this->m_strRawValue.assign(reinterpret_cast <char*> (&temp), sizeof (temp));
			ostrstr << temp;
			this->m_strFormatedValue = ostrstr.str();
		} else if (STRING_DOUBLE == this->m_strTypeName)
		{
			double temp;
			istrstr >> temp;
			this->m_bIsSuccessful = istrstr.eof();
			this->m_strRawValue.assign(reinterpret_cast <char*> (&temp), sizeof (temp));
			ostrstr << temp;
			this->m_strFormatedValue = ostrstr.str();
		} else if (STRING_STRING == this->m_strTypeName)
		{
			this->m_strRawValue = this->m_strFormatedValue = oldStr;
		}
		else
		{
			this->m_bIsSuccessful = false;
		}
	}

	CSimpleData::CSimpleData(string strType, const char* const& pstrValue, const string& strDataName, char i8Precision) : m_strTypeName(Trim(strType)), m_strDataName(strDataName), m_i8Precision(i8Precision), m_bIsSuccessful(true)
	{
		string strOld(pstrValue);
		string strValue(pstrValue);

		istringstream istrstr(Trim(strValue));
		ostringstream ostrstr;

		if (i8Precision < 0)
		{
			ostrstr.setf(ios::fixed, ios::floatfield);
			ostrstr.precision(-this->m_i8Precision);
		}
		else
		{
			ostrstr.precision(this->m_i8Precision);
		}

		if (STRING_CHAR == this->m_strTypeName )
		{
			char temp;
			istrstr >> temp;
			this->m_bIsSuccessful = istrstr.eof();
			this->m_strRawValue.assign(reinterpret_cast <char*> (&temp), sizeof (temp));
			ostrstr << temp;
			this->m_strFormatedValue = ostrstr.str();
		} else if (STRING_UCHAR == this->m_strTypeName)
		{
			unsigned char temp;
			istrstr >> temp;
			this->m_bIsSuccessful = istrstr.eof();
			this->m_strRawValue.assign(reinterpret_cast <char*> (&temp), sizeof (temp));
			ostrstr << temp;
			this->m_strFormatedValue = ostrstr.str();
		} else if (STRING_SHORT == this->m_strTypeName)
		{
			short temp;
			istrstr >> temp;
			this->m_bIsSuccessful = istrstr.eof();
			this->m_strRawValue.assign(reinterpret_cast <char*> (&temp), sizeof (temp));
			ostrstr << temp;
			this->m_strFormatedValue = ostrstr.str();
		} else if (STRING_USHORT == this->m_strTypeName)
		{
			unsigned short temp;
			istrstr >> temp;
			this->m_bIsSuccessful = istrstr.eof();
			this->m_strRawValue.assign(reinterpret_cast <char*> (&temp), sizeof (temp));
			ostrstr << temp;
			this->m_strFormatedValue = ostrstr.str();
		} else if (STRING_INT == this->m_strTypeName)
		{
			int temp;
			istrstr >> temp;
			this->m_bIsSuccessful = istrstr.eof();
			this->m_strRawValue.assign(reinterpret_cast <char*> (&temp), sizeof (temp));
			ostrstr << temp;
			this->m_strFormatedValue = ostrstr.str();
		} else if (STRING_UINT == this->m_strTypeName)
		{
			unsigned int temp;
			istrstr >> temp;
			this->m_bIsSuccessful = istrstr.eof();
			this->m_strRawValue.assign(reinterpret_cast <char*> (&temp), sizeof (temp));
			ostrstr << temp;
			this->m_strFormatedValue = ostrstr.str();
		} else if (STRING_LONGLONG == this->m_strTypeName)
		{
			long long temp;
			istrstr >> temp;
			this->m_bIsSuccessful = istrstr.eof();
			this->m_strRawValue.assign(reinterpret_cast <char*> (&temp), sizeof (temp));
			ostrstr << temp;
			this->m_strFormatedValue = ostrstr.str();
		} else if (STRING_ULONGLONG == this->m_strTypeName)
		{
			unsigned long long temp;
			istrstr >> temp;
			this->m_bIsSuccessful = istrstr.eof();
			this->m_strRawValue.assign(reinterpret_cast <char*> (&temp), sizeof (temp));
			ostrstr << temp;
			this->m_strFormatedValue = ostrstr.str();
		} else if (STRING_SINGLE == this->m_strTypeName)
		{
			float temp;
			istrstr >> temp;
			this->m_bIsSuccessful = istrstr.eof();
			this->m_strRawValue.assign(reinterpret_cast <char*> (&temp), sizeof (temp));
			ostrstr << temp;
			this->m_strFormatedValue = ostrstr.str();
		} else if (STRING_DOUBLE == this->m_strTypeName)
		{
			double temp;
			istrstr >> temp;
			this->m_bIsSuccessful = istrstr.eof();
			this->m_strRawValue.assign(reinterpret_cast <char*> (&temp), sizeof (temp));
			ostrstr << temp;
			this->m_strFormatedValue = ostrstr.str();
		} else if (STRING_STRING == this->m_strTypeName)
		{
			this->m_strRawValue = this->m_strFormatedValue = strOld;
		}
		else
		{
			this->m_bIsSuccessful = false;
		}
	}

	CSimpleData::CSimpleData(string strType, const void* pValue, const string& strDataName, char i8Precision) : m_strTypeName(Trim(strType)), m_strDataName(strDataName), m_i8Precision(i8Precision), m_bIsSuccessful(true)
	{
		ostringstream ostrstr;
		const char* p = reinterpret_cast <const char*> (pValue);

		if (this->m_i8Precision < 0)
		{
			ostrstr.setf(ios::fixed, ios::floatfield);
			ostrstr.precision(-this->m_i8Precision);
		}
		else
		{
			ostrstr.precision(this->m_i8Precision);
		}

		if (STRING_CHAR == this->m_strTypeName)
		{
			this->m_strRawValue.assign(p, sizeof (char));
			char temp = *reinterpret_cast <const char*> (pValue);
			ostrstr << temp;
			this->m_strFormatedValue = ostrstr.str();
		} else if (STRING_UCHAR == this->m_strTypeName)
		{
			this->m_strRawValue.assign(p, sizeof (unsigned char));
			unsigned char temp = *reinterpret_cast <const unsigned char*> (pValue);
			ostrstr << temp;
			this->m_strFormatedValue = ostrstr.str();
		} else if (STRING_SHORT == this->m_strTypeName)
		{
			this->m_strRawValue.assign(p, sizeof (short));
			ostrstr << *reinterpret_cast <const short*> (pValue);
			this->m_strFormatedValue = ostrstr.str();
		} else if (STRING_USHORT == this->m_strTypeName)
		{
			this->m_strRawValue.assign(p, sizeof (unsigned short));
			ostrstr << *reinterpret_cast <const unsigned short*> (pValue);
			this->m_strFormatedValue = ostrstr.str();
		} else if (STRING_INT == this->m_strTypeName)
		{
			this->m_strRawValue.assign(p, sizeof (int));
			ostrstr << *reinterpret_cast <const int*> (pValue);
			this->m_strFormatedValue = ostrstr.str();
		} else if (STRING_UINT == this->m_strTypeName)
		{
			this->m_strRawValue.assign(p, sizeof (unsigned int));
			ostrstr << *reinterpret_cast <const unsigned int*> (pValue);
			this->m_strFormatedValue = ostrstr.str();
		} else if (STRING_LONGLONG == this->m_strTypeName)
		{
			this->m_strRawValue.assign(p, sizeof (long long));
			ostrstr << *reinterpret_cast <const long long*> (pValue);
			this->m_strFormatedValue = ostrstr.str();
		} else if (STRING_ULONGLONG == this->m_strTypeName)
		{
			this->m_strRawValue.assign(p, sizeof (unsigned long long));
			ostrstr << *reinterpret_cast <const unsigned long long*> (pValue);
			this->m_strFormatedValue = ostrstr.str();
		} else if (STRING_SINGLE == this->m_strTypeName)
		{
			this->m_strRawValue.assign(p, sizeof (float));
			ostrstr << *reinterpret_cast <const float*> (pValue);
			this->m_strFormatedValue = ostrstr.str();
		} else if (STRING_DOUBLE == this->m_strTypeName)
		{
			this->m_strRawValue.assign(p, sizeof (double));
			ostrstr << *reinterpret_cast <const double*> (pValue);
			this->m_strFormatedValue = ostrstr.str();
		} else
		{
			this->m_strFormatedValue = this->m_strRawValue = reinterpret_cast <const char*> (pValue);
		}
	}

	CSimpleData::CSimpleData(const CSimpleData& data) : m_strTypeName(data.m_strTypeName), m_strDataName(data.m_strDataName), m_i8Precision(data.m_i8Precision)
	{
		this->m_strRawValue = data.m_strRawValue;
		this->m_strFormatedValue = data.m_strFormatedValue;
		this->m_bIsSuccessful = data.m_bIsSuccessful;
	}

	CSimpleData& CSimpleData::operator =(const CSimpleData& data)
	{
		if (this != &data)
		{
			CSimpleData oData(this->GetTypeName(), data.GetFormatedValue(), data.GetDataName());

			this->m_strRawValue = oData.m_strRawValue;
			this->m_strFormatedValue = oData.m_strFormatedValue;
			this->m_bIsSuccessful = data.m_bIsSuccessful;
		}
		return *this;
	}

	CSimpleData::operator bool(void) const
	{
		return this->m_bIsSuccessful;
	}

	CSimpleData::operator char(void) const
	{
		return this->OriginalValue(char(0));
	}

	CSimpleData::operator unsigned char(void) const
	{
		return this->OriginalValue((unsigned char)(0));
	}

	CSimpleData::operator short(void) const
	{
		return this->OriginalValue(short(0));
	}

	CSimpleData::operator unsigned short(void) const
	{
		return this->OriginalValue((unsigned short)(0));
	}

	CSimpleData::operator int(void) const
	{
		return this->OriginalValue(int(0));
	}

	CSimpleData::operator unsigned int(void) const
	{
		return this->OriginalValue((unsigned int)(0));
	}

	CSimpleData::operator long long(void) const
	{
		return this->OriginalValue((long long)(0));
	}

	CSimpleData::operator unsigned long long(void) const
	{
		return this->OriginalValue((unsigned long long)(0));
	}

	CSimpleData::operator float(void) const
	{
		return this->OriginalValue(float(0));
	}

	CSimpleData::operator double(void) const
	{
		return this->OriginalValue(double(0));
	}

	CSimpleData::operator const char*(void) const
	{
		return this->m_strRawValue.c_str();
	}

	CSimpleData::operator string(void) const
	{
		return this->m_strFormatedValue;
	}

	const CSimpleData& CSimpleData::Display(bool bNewLine) const
	{
		if (STRING_CHAR == this->m_strTypeName)
		{
			cout << this->OriginalValue(char(0));
		}else if (STRING_UCHAR == this->m_strTypeName)
		{
			cout << this->OriginalValue((unsigned char)(0));
		}else if (STRING_SHORT == this->m_strTypeName)
		{
			cout << short(this->OriginalValue(short(0)));
		}else if (STRING_USHORT == this->GetTypeName())
		{
			cout << this->OriginalValue((unsigned short)(0));
		}else if (STRING_INT == this->m_strTypeName)
		{
			cout << this->OriginalValue(int(0));
		}else if (STRING_UINT == this->m_strTypeName)
		{
			cout << this->OriginalValue((unsigned int)(0));
		}else if (STRING_LONGLONG == this->m_strTypeName)
		{
			cout << this->OriginalValue((long long)(0));
		}else if (STRING_ULONGLONG == this->m_strTypeName)
		{
			cout << this->OriginalValue((unsigned long long)(0));
		}else if (STRING_SINGLE == this->m_strTypeName)
		{
			cout << this->OriginalValue(float(0));
		}else if (STRING_DOUBLE == this->m_strTypeName)
		{
			cout << this->OriginalValue(double(0));
		}
		else
		{
			cout << this->m_strFormatedValue;
		}

		bNewLine ? cout << '\n' : cout << "";
		return *this;
	}

	CSimpleData operator +(const CSimpleData& oData1, const CSimpleData& oData2)
	{
		if (STRING_STRING == oData1.GetTypeName() && STRING_STRING == oData2.GetTypeName())
		{
			return oData1.GetFormatedValue() + oData2.GetFormatedValue();
		}
		else if (STRING_DOUBLE == oData1.GetTypeName() || STRING_DOUBLE == oData2.GetTypeName())
		{
			return CSimpleData(oData1.OriginalValue(double(0)) + oData2.OriginalValue(double(0)));
		}
		else if (STRING_ULONGLONG == oData1.GetTypeName() || STRING_ULONGLONG == oData2.GetTypeName())
		{
			return CSimpleData(oData1.OriginalValue((unsigned long long)(0)) + oData2.OriginalValue((unsigned long long)(0)));
		}
		else if (STRING_LONGLONG == oData1.GetTypeName() || STRING_LONGLONG == oData2.GetTypeName())
		{
			return CSimpleData(oData1.OriginalValue((long long)(0)) + oData2.OriginalValue((long long)(0)));
		}
		else if (STRING_SINGLE == oData1.GetTypeName() || STRING_SINGLE == oData2.GetTypeName())
		{
			return CSimpleData(oData1.OriginalValue(float(0)) + oData2.OriginalValue(float(0)));
		}
		else if (STRING_UINT == oData1.GetTypeName() || STRING_UINT == oData2.GetTypeName())
		{
			return CSimpleData(oData1.OriginalValue((unsigned int)(0)) + oData2.OriginalValue((unsigned int)(0)));
		}
		else
		{
			return CSimpleData(oData1.OriginalValue(int(0)) + oData2.OriginalValue(int(0)));
		}
	}

	CSimpleData operator -(const CSimpleData& oData1, const CSimpleData& oData2)
	{
		if (STRING_DOUBLE == oData1.GetTypeName() || STRING_DOUBLE == oData2.GetTypeName())
		{
			return CSimpleData(oData1.OriginalValue(double(0)) - oData2.OriginalValue(double(0)));
		}
		else if (STRING_ULONGLONG == oData1.GetTypeName() || STRING_ULONGLONG == oData2.GetTypeName())
		{
			return CSimpleData(oData1.OriginalValue((unsigned long long)(0)) - oData2.OriginalValue((unsigned long long)(0)));
		}
		else if (STRING_LONGLONG == oData1.GetTypeName() || STRING_LONGLONG == oData2.GetTypeName())
		{
			return CSimpleData(oData1.OriginalValue((long long)(0)) - oData2.OriginalValue((long long)(0)));
		}
		else if (STRING_SINGLE == oData1.GetTypeName() || STRING_SINGLE == oData2.GetTypeName())
		{
			return CSimpleData(oData1.OriginalValue(float(0)) - oData2.OriginalValue(float(0)));
		}
		else if (STRING_UINT == oData1.GetTypeName() || STRING_UINT == oData2.GetTypeName())
		{
			return CSimpleData(oData1.OriginalValue((unsigned int)(0)) - oData2.OriginalValue((unsigned int)(0)));
		}
		else
		{
			return CSimpleData(oData1.OriginalValue(int(0)) - oData2.OriginalValue(int(0)));
		}
	}

	CSimpleData operator *(const CSimpleData& oData1, const CSimpleData& oData2)
	{
		if (STRING_DOUBLE == oData1.GetTypeName() || STRING_DOUBLE == oData2.GetTypeName())
		{
			return CSimpleData(oData1.OriginalValue(double(0)) * oData2.OriginalValue(double(0)));
		}
		else if (STRING_ULONGLONG == oData1.GetTypeName() || STRING_ULONGLONG == oData2.GetTypeName())
		{
			return CSimpleData(oData1.OriginalValue((unsigned long long)(0)) * oData2.OriginalValue((unsigned long long)(0)));
		}
		else if (STRING_LONGLONG == oData1.GetTypeName() || STRING_LONGLONG == oData2.GetTypeName())
		{
			return CSimpleData(oData1.OriginalValue((long long)(0)) * oData2.OriginalValue((long long)(0)));
		}
		else if (STRING_SINGLE == oData1.GetTypeName() || STRING_SINGLE == oData2.GetTypeName())
		{
			return CSimpleData(oData1.OriginalValue(float(0)) * oData2.OriginalValue(float(0)));
		}
		else if (STRING_UINT == oData1.GetTypeName() || STRING_UINT == oData2.GetTypeName())
		{
			return CSimpleData(oData1.OriginalValue((unsigned int)(0)) * oData2.OriginalValue((unsigned int)(0)));
		}
		else
		{
			return CSimpleData(oData1.OriginalValue(int(0)) * oData2.OriginalValue(int(0)));
		}
	}

	CSimpleData operator /(const CSimpleData& oData1, const CSimpleData& oData2)
	{
		if (STRING_DOUBLE == oData1.GetTypeName() || STRING_DOUBLE == oData2.GetTypeName())
		{
			return CSimpleData(oData1.OriginalValue(double(0)) / oData2.OriginalValue(double(0)));
		}
		else if (STRING_ULONGLONG == oData1.GetTypeName() || STRING_ULONGLONG == oData2.GetTypeName())
		{
			return CSimpleData(oData1.OriginalValue((unsigned long long)(0)) / oData2.OriginalValue((unsigned long long)(0)));
		}
		else if (STRING_LONGLONG == oData1.GetTypeName() || STRING_LONGLONG == oData2.GetTypeName())
		{
			return CSimpleData(oData1.OriginalValue((long long)(0)) / oData2.OriginalValue((long long)(0)));
		}
		else if (STRING_SINGLE == oData1.GetTypeName() || STRING_SINGLE == oData2.GetTypeName())
		{
			return CSimpleData(oData1.OriginalValue(float(0)) / oData2.OriginalValue(float(0)));
		}
		else if (STRING_UINT == oData1.GetTypeName() || STRING_UINT == oData2.GetTypeName())
		{
			return CSimpleData(oData1.OriginalValue((unsigned int)(0)) / oData2.OriginalValue((unsigned int)(0)));
		}
		else
		{
			return CSimpleData(oData1.OriginalValue(int(0)) / oData2.OriginalValue(int(0)));
		}
	}

	CSimpleData operator %(const CSimpleData& oData1, const CSimpleData& oData2)
	{
		if (STRING_ULONGLONG == oData1.GetTypeName() || STRING_ULONGLONG == oData2.GetTypeName())
		{
			return CSimpleData(oData1.OriginalValue((unsigned long long)(0)) % oData2.OriginalValue((unsigned long long)(0)));
		}
		else if (STRING_LONGLONG == oData1.GetTypeName() || STRING_LONGLONG == oData2.GetTypeName())
		{
			return CSimpleData(oData1.OriginalValue((long long)(0)) % oData2.OriginalValue((long long)(0)));
		}
		else if (STRING_UINT == oData1.GetTypeName() || STRING_UINT == oData2.GetTypeName())
		{
			return CSimpleData(oData1.OriginalValue((unsigned int)(0)) % oData2.OriginalValue((unsigned int)(0)));
		}
		else
		{
			return CSimpleData(oData1.OriginalValue(int(0)) % oData2.OriginalValue(int(0)));
		}
	}

	bool operator <(const CSimpleData& oData1, const CSimpleData& oData2)
	{
		if (STRING_ULONGLONG == oData1.GetTypeName() || STRING_ULONGLONG == oData2.GetTypeName())
		{
			return oData1.OriginalValue((unsigned long long)(0)) < oData2.OriginalValue((unsigned long long)(0));
		}
		else if (STRING_LONGLONG == oData1.GetTypeName() || STRING_LONGLONG == oData2.GetTypeName())
		{
			return oData1.OriginalValue((long long)(0)) < oData2.OriginalValue((long long)(0));
		}
		else if (STRING_DOUBLE == oData1.GetTypeName() || STRING_DOUBLE == oData2.GetTypeName())
		{
			return oData1.OriginalValue(double(0.0)) < oData2.OriginalValue(double(0.0));
		}
		else if (STRING_SINGLE == oData1.GetTypeName() || STRING_SINGLE == oData2.GetTypeName())
		{
			return oData1.OriginalValue(float(0.0)) < oData2.OriginalValue(float(0.0));
		}
		else if (STRING_UINT == oData1.GetTypeName() || STRING_UINT == oData2.GetTypeName())
		{
			return oData1.OriginalValue((unsigned int)(0)) < oData2.OriginalValue((unsigned int)(0));
		}
		else if (STRING_INT == oData1.GetTypeName() || STRING_INT == oData2.GetTypeName())
		{
			return oData1.OriginalValue(int(0)) < oData2.OriginalValue(int(0));
		}
		else if (STRING_USHORT == oData1.GetTypeName() || STRING_USHORT == oData2.GetTypeName())
		{
			return oData1.OriginalValue((unsigned short)(0)) < oData2.OriginalValue((unsigned short)(0));
		}
		else if (STRING_SHORT == oData1.GetTypeName() || STRING_SHORT == oData2.GetTypeName())
		{
			return oData1.OriginalValue(short(0)) < oData2.OriginalValue(short(0));
		}
		else if (STRING_UCHAR == oData1.GetTypeName() || STRING_UCHAR == oData2.GetTypeName())
		{
			return oData1.OriginalValue((unsigned char)(0)) < oData2.OriginalValue((unsigned char)(0));
		}
		else
		{
			return oData1.OriginalValue(char(0)) < oData2.OriginalValue(char(0));
		}
	}

	bool operator ==(const CSimpleData& oData1, const CSimpleData& oData2)
	{
		if (STRING_ULONGLONG == oData1.GetTypeName() || STRING_ULONGLONG == oData2.GetTypeName())
		{
			return oData1.OriginalValue((unsigned long long)(0)) == oData2.OriginalValue((unsigned long long)(0));
		}
		else if (STRING_LONGLONG == oData1.GetTypeName() || STRING_LONGLONG == oData2.GetTypeName())
		{
			return oData1.OriginalValue((long long)(0)) == oData2.OriginalValue((long long)(0));
		}
		else if (STRING_DOUBLE == oData1.GetTypeName() || STRING_DOUBLE == oData2.GetTypeName())
		{
			return oData1.OriginalValue(double(0.0)) == oData2.OriginalValue(double(0.0));
		}
		else if (STRING_SINGLE == oData1.GetTypeName() || STRING_SINGLE == oData2.GetTypeName())
		{
			return oData1.OriginalValue(float(0.0)) == oData2.OriginalValue(float(0.0));
		}
		else if (STRING_UINT == oData1.GetTypeName() || STRING_UINT == oData2.GetTypeName())
		{
			return oData1.OriginalValue((unsigned int)(0)) == oData2.OriginalValue((unsigned int)(0));
		}
		else if (STRING_INT == oData1.GetTypeName() || STRING_INT == oData2.GetTypeName())
		{
			return oData1.OriginalValue(int(0)) == oData2.OriginalValue(int(0));
		}
		else if (STRING_USHORT == oData1.GetTypeName() || STRING_USHORT == oData2.GetTypeName())
		{
			return oData1.OriginalValue((unsigned short)(0)) == oData2.OriginalValue((unsigned short)(0));
		}
		else if (STRING_SHORT == oData1.GetTypeName() || STRING_SHORT == oData2.GetTypeName())
		{
			return oData1.OriginalValue(short(0)) == oData2.OriginalValue(short(0));
		}
		else if (STRING_UCHAR == oData1.GetTypeName() || STRING_UCHAR == oData2.GetTypeName())
		{
			return oData1.OriginalValue((unsigned char)(0)) == oData2.OriginalValue((unsigned char)(0));
		}
		else
		{
			return oData1.OriginalValue(char(0)) == oData2.OriginalValue(char(0));
		}
	}

	bool operator !=(const CSimpleData& oData1, const CSimpleData& oData2)
	{
		return !(oData1 == oData2);
	}

	bool operator <=(const CSimpleData& oData1, const CSimpleData& oData2)
	{
		return (oData1 < oData2) || (oData1 == oData2);
	}

	bool operator >=(const CSimpleData& oData1, const CSimpleData& oData2)
	{
		return !(oData1 < oData2);
	}

	bool operator >(const CSimpleData& oData1, const CSimpleData& oData2)
	{
		return !(oData1 <= oData2);
	}

	ostream& operator<<(ostream& outStream, const CSimpleData& oSimpData)
	{
		return (outStream << oSimpData.GetFormatedValue());
	}
}
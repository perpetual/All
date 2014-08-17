#include "VersionControl.h"
#include <cstring>
#include "DataType/ComplexData.h"

namespace DataType
{
	unsigned int CComplexData::AddField(const CSimpleData& oDataType)
	{
		this->m_vecFields.push_back(oDataType);
		this->m_u32DataSize += oDataType.GetSize();

		return oDataType.GetSize();
	}

	unsigned int CComplexData::GetOffset(unsigned int uiIndex) const
	{
		unsigned int uiOffset = 0;

		for (unsigned u = 0; u < uiIndex; ++u)
		{
			uiOffset += this->m_vecFields[u].GetSize();
		}

		return uiOffset;
	}

	string CComplexData::Serialize(void) const
	{
		char* pBuf = new char[this->GetSize()];

		for (unsigned u = 0; u < this->GetCount(); ++u)
		{
			memcpy(pBuf +this->GetOffset(u), this->m_vecFields[u].GetRawValue(), this->m_vecFields[u].GetSize());
		}

		string strRet(pBuf, this->GetSize());

		delete[] pBuf;

		return strRet;
	}

	CComplexData CComplexData::UnSerialize(const string& strSerialized)
	{
		for (unsigned u = 0; u < this->GetCount(); ++u)
		{
			this->m_vecFields[u] = CSimpleData(this->m_vecFields[u].GetTypeName(), static_cast<const void*>(strSerialized.c_str() + this->GetOffset(u)), "");
		}

		return *this;
	}

	string CComplexData::SerializeEx(void) const
	{
		unsigned int uiSize = this->GetSize() + sizeof (unsigned int) * this->GetCount();		//在每一个具体数值前加一个标记位
		char* pStart = new char[uiSize];
		char* pBuf = pStart;
		unsigned int uiTemp = 0;
		string strRet;

		for (vector<CSimpleData>::const_iterator ci = this->m_vecFields.begin(); ci != this->m_vecFields.end(); ++ci)
		{
			if (STRING_STRING == ci->GetTypeName())
			{
				uiTemp = ID_STRING + ci->GetSize();					//字符串的标记位为字符串标识符值+字符串的长度
			}
			else
			{
				uiTemp = WhichType(ci->GetTypeName());
			}
			memcpy(pBuf, &uiTemp, sizeof (uiTemp));
			pBuf += sizeof (uiTemp);
			memcpy(pBuf, ci->GetRawValue(), ci->GetSize());
			pBuf += ci->GetSize();
		}

		strRet = string(pStart, pBuf - pStart);
		delete[] pStart;
		return string(strRet);
	}

	CComplexData CComplexData::UnSerializeEx(const string& strSerializedEx)
	{
		unsigned int uiTemp = 0;
		const char* pStart = strSerializedEx.c_str();
		const char* pEnd = strSerializedEx.c_str() + strSerializedEx.length();

		this->Clear();
		for (const char* p = pStart; p < pEnd;)
		{
			uiTemp = *reinterpret_cast<const unsigned int*>(p);
			p += sizeof (uiTemp);
			if (uiTemp >= ID_STRING)			//如果是字符串
			{
				this->AddField(CSimpleData(string(p, uiTemp - ID_STRING)));
			}
			else
			{
				this->AddField(CSimpleData(TYPE_STRINGS[uiTemp], static_cast<const void*>(p), ""));
			}
			p += this->GetLastField().GetSize();
		}

		return *this;
	}

	void CComplexData::Display(void) const
	{
		for (vector<CSimpleData>::const_iterator ci = this->m_vecFields.begin(); ci != this->m_vecFields.end(); ++ci)
		{
			cout << ci->GetFormatedValue() << ' ';
		}
		cout << std::endl;
	}
}
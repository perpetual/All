#ifndef SCHEMA_H
#define SCHEMA_H

#include <vector>
#include <string>
#include <cassert>
#include "SimpleData.h"

namespace DataType
{
	using std::vector;
	using std::string;

	class CComplexData
	{
	public:
		CComplexData(void) : m_u32DataSize(0)
		{}

		//����ֶ�
		//�����ֶεĳ���
		unsigned int AddField(const CSimpleData&);

		//�������
		void Clear(void)
		{
			this->m_vecFields.clear();
			this->m_u32DataSize = 0;
		}

		//��ȡ�ֶθ���
		unsigned int GetCount(void) const
		{
			return this->m_vecFields.size();
		}

		//��ȡ���������������͵Ĵ�С
		unsigned int GetSize(void) const
		{
			return this->m_u32DataSize;
		}

		//��ȡָ������ֶε�ƫ����
		unsigned int GetOffset(unsigned int) const;

		CSimpleData GetFirstField(void) const
		{
			assert(0 != this->m_vecFields.size());
			return this->m_vecFields.front();
		}

		CSimpleData GetLastField(void) const
		{
			assert(0 != this->m_vecFields.size());
			return this->m_vecFields.back();
		}

		//��ȡָ�����ƻ���ŵ��ֶ�
		CSimpleData GetField(unsigned int u32Index) const
		{
			return this->m_vecFields[u32Index];
		}

		//����ָ���ֶε�ֵ
		void SetField(unsigned int u32Index, const CSimpleData& oSimpData)
		{
			this->m_vecFields[u32Index] = oSimpData;
		}

		//��һ�ֽڶ������л�
		string Serialize(void) const;

		//�����л�
		CComplexData UnSerialize(const string&);

		//��һ�ֽڶ������л����Խ�����
		string SerializeEx(void) const;

		//�����л�(�Խ���)
		CComplexData UnSerializeEx(const string&);

		//��ʾ����
		void Display(void) const;

	private:
		vector<CSimpleData> m_vecFields;		//������Ÿ����ֶ�
		unsigned int m_u32DataSize;			//�����ܴ�С�����ֽ�Ϊ��λ
	};
}

#endif
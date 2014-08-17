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

		//添加字段
		//返回字段的长度
		unsigned int AddField(const CSimpleData&);

		//清空数据
		void Clear(void)
		{
			this->m_vecFields.clear();
			this->m_u32DataSize = 0;
		}

		//获取字段个数
		unsigned int GetCount(void) const
		{
			return this->m_vecFields.size();
		}

		//获取整个复杂数据类型的大小
		unsigned int GetSize(void) const
		{
			return this->m_u32DataSize;
		}

		//获取指定序号字段的偏移量
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

		//获取指定名称或序号的字段
		CSimpleData GetField(unsigned int u32Index) const
		{
			return this->m_vecFields[u32Index];
		}

		//设置指定字段的值
		void SetField(unsigned int u32Index, const CSimpleData& oSimpData)
		{
			this->m_vecFields[u32Index] = oSimpData;
		}

		//按一字节对齐序列化
		string Serialize(void) const;

		//反序列化
		CComplexData UnSerialize(const string&);

		//按一字节对齐序列化（自解析）
		string SerializeEx(void) const;

		//反序列化(自解析)
		CComplexData UnSerializeEx(const string&);

		//显示数据
		void Display(void) const;

	private:
		vector<CSimpleData> m_vecFields;		//用来存放各个字段
		unsigned int m_u32DataSize;			//数据总大小，以字节为单位
	};
}

#endif
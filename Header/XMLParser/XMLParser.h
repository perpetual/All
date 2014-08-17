#ifndef XML_PARSER_H
#define XML_PARSER_H

#include <iostream>
#include <string>
#include <vector>
#include "xercesc/parsers/XercesDOMParser.hpp"
#include "xercesc/dom/DOMDocument.hpp"
#include "MyTools/MyUtilityTools.h"

namespace XMLObject
{
	using std::string;
	using std::wstring;
	using std::vector;
	using xercesc::DOMElement;
	using xercesc::XercesDOMParser;

	//初始化xercesc环境
	class CInitXercesc
	{
	protected:
		CInitXercesc(void);
		virtual ~CInitXercesc(void);
	private:
		static unsigned int m_uiXercersInitCount;		//Xerces初始化计数器
	};

	class CXMLObjectBase : public CInitXercesc
	{
	protected:
		CXMLObjectBase(void);
		~CXMLObjectBase(void);

		XercesDOMParser* m_pParse;
	};

	class CXMLObject : public CXMLObjectBase
	{
	public:
		class CElementObject
		{
			friend class CXMLObject;
		public:
			//构造函数
			CElementObject(const DOMElement* = NULL);

			//获取第一个子元素
			CElementObject GetFirstChildElement(void) const;

			//获取最后一个子元素
			CElementObject GetLastChildElement(void) const;

			//获取所有子元素
			vector<CElementObject> GetChildElements(const string&) const;

			//获取元素名称
			string GetElementName(void) const;

			//获取元素值，一般是文本节点的值
			string GetElementValue(void) const;

			//获取元素属性
			//参数是元素属性名称
			string GetAttribute(const string&) const;

			operator bool(void) const
			{
				return NULL != this->m_pElement;
			}

		private:
			const DOMElement* m_pElement;
		};
		//构造函数
		//参数是XML文件名或XML字符串
		explicit CXMLObject(const string&);

		//判断解析器是否初始化成功
		operator bool(void) const
		{
			return this->m_bIsSuccessful;
		}

		//获取根元素
		CElementObject GetRootElement(void) const
		{
			return CElementObject(this->m_pRoot);
		}

		//获取元素对象
		//第一个参数是元素名称
		vector<CElementObject> GetElements(const string&) const;

		//获取指定元素名称的第一个元素对象
		CElementObject GetFirstElement(const string&) const;

		//获取文件内容
		string GetContent(void) const;

	private:
		//禁止复制和赋值
		CXMLObject(const CXMLObject&);
                CXMLObject& operator =(const CXMLObject&);

		bool m_bIsSuccessful;
		xercesc::DOMDocument* m_pDoc;				//XML文档
		DOMElement* m_pRoot;				//根元素
		string m_strContent;						//文件内容
	};
}

#endif
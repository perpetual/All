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

	//��ʼ��xercesc����
	class CInitXercesc
	{
	protected:
		CInitXercesc(void);
		virtual ~CInitXercesc(void);
	private:
		static unsigned int m_uiXercersInitCount;		//Xerces��ʼ��������
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
			//���캯��
			CElementObject(const DOMElement* = NULL);

			//��ȡ��һ����Ԫ��
			CElementObject GetFirstChildElement(void) const;

			//��ȡ���һ����Ԫ��
			CElementObject GetLastChildElement(void) const;

			//��ȡ������Ԫ��
			vector<CElementObject> GetChildElements(const string&) const;

			//��ȡԪ������
			string GetElementName(void) const;

			//��ȡԪ��ֵ��һ�����ı��ڵ��ֵ
			string GetElementValue(void) const;

			//��ȡԪ������
			//������Ԫ����������
			string GetAttribute(const string&) const;

			operator bool(void) const
			{
				return NULL != this->m_pElement;
			}

		private:
			const DOMElement* m_pElement;
		};
		//���캯��
		//������XML�ļ�����XML�ַ���
		explicit CXMLObject(const string&);

		//�жϽ������Ƿ��ʼ���ɹ�
		operator bool(void) const
		{
			return this->m_bIsSuccessful;
		}

		//��ȡ��Ԫ��
		CElementObject GetRootElement(void) const
		{
			return CElementObject(this->m_pRoot);
		}

		//��ȡԪ�ض���
		//��һ��������Ԫ������
		vector<CElementObject> GetElements(const string&) const;

		//��ȡָ��Ԫ�����Ƶĵ�һ��Ԫ�ض���
		CElementObject GetFirstElement(const string&) const;

		//��ȡ�ļ�����
		string GetContent(void) const;

	private:
		//��ֹ���ƺ͸�ֵ
		CXMLObject(const CXMLObject&);
                CXMLObject& operator =(const CXMLObject&);

		bool m_bIsSuccessful;
		xercesc::DOMDocument* m_pDoc;				//XML�ĵ�
		DOMElement* m_pRoot;				//��Ԫ��
		string m_strContent;						//�ļ�����
	};
}

#endif
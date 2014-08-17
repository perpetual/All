#include "VersionControl.h"
#include <sstream>
#include <string>
#include "xercesc/util/XMLString.hpp"
#include "xercesc/dom/DOMElement.hpp"
#include "xercesc/dom/DOMNodeList.hpp"
#include "MyTools/MyUtilityTools.h"
#include "XMLParser/XMLParser.h"
#include "LogFile/LogFile.h"

namespace XMLObject
{
	using std::stringstream;
	using std::wstringstream;
	using std::string;
	using xercesc::XMLString;
	using xercesc::DOMNodeList;
	using xercesc::XMLPlatformUtils;
	using MyTools::Trim;
	using MyTools::StrToWStr;
	using MyTools::WStrToStr;
	using MyTools::IsFile;
	using MyTools::GetRandomName;
	using MyTools::WriteWholeFile;
	using MyTools::ReadWholeFile;
	using MyTools::RemoveFile;

	unsigned int CInitXercesc::m_uiXercersInitCount = 0;

	CInitXercesc::CInitXercesc(void)
	{
		if (0 == this->m_uiXercersInitCount++)
		{
			xercesc::XMLPlatformUtils::Initialize();
		}
	}

	CInitXercesc::~CInitXercesc(void)
	{
		if (this->m_uiXercersInitCount > 0 && 0 == --this->m_uiXercersInitCount)
		{
			xercesc::XMLPlatformUtils::Terminate();
		}
	}

	/************************************************************************/
	//Tools
	/************************************************************************/
	CXMLObjectBase::CXMLObjectBase(void) try :
		m_pParse(new XercesDOMParser)
	{}
	catch (...)
	{
		throw;
	}

	CXMLObjectBase::~CXMLObjectBase(void)
	{
		delete this->m_pParse;
	}

        class StrToXMLCh
        {
        public:
            StrToXMLCh(const string& str) : m_pXMLCh(NULL)
            {
                this->m_pXMLCh = new XMLCh[str.length() + 1];
                XMLString::transcode(str.c_str(), this->m_pXMLCh, str.length());
            }
            ~StrToXMLCh(void)
            {
                delete[] this->m_pXMLCh;
            }
            operator const XMLCh*(void)
            {
                return this->m_pXMLCh;
            }
        private:
            XMLCh* m_pXMLCh;
        };

        class XMLChToStr
        {
        public:
            XMLChToStr(const XMLCh* strXML)
            {
                if (NULL != strXML)
                {
                    char* p = NULL;

                    this->m_str = (p = XMLString::transcode(strXML));
                    XMLString::release(&p);
                }
            }
            operator string(void) const
            {
                return this->m_str;
            }
        private:
            string m_str;
        };

	/************************************************************************/
	/* CElementObject                                                                     */
	/************************************************************************/
	CXMLObject::CElementObject::CElementObject(const DOMElement* pElement) : m_pElement(pElement)
	{}

	CXMLObject::CElementObject CXMLObject::CElementObject::GetFirstChildElement(void) const
	{
		if (NULL == this->m_pElement)
		{
			return CElementObject(NULL);
		}
		return CElementObject(reinterpret_cast <DOMElement*> (this->m_pElement->getFirstChild()));
	}

	CXMLObject::CElementObject CXMLObject::CElementObject::GetLastChildElement(void) const
	{
		if (NULL == this->m_pElement)
		{
			return CElementObject(NULL);
		}
		return CElementObject(reinterpret_cast <DOMElement*> (this->m_pElement->getLastChild()));
	}

	vector<CXMLObject::CElementObject> CXMLObject::CElementObject::GetChildElements(const string& strTagName) const
	{
		if (NULL == this->m_pElement)
		{
			return vector<CXMLObject::CElementObject>();
		}

		const DOMNodeList* pNodeList = this->m_pElement->getElementsByTagName(StrToXMLCh(strTagName));
		vector<CXMLObject::CElementObject> v;

		unsigned int u32ListLen = pNodeList->getLength();
		for (unsigned int u = 0; u < u32ListLen; ++u)
		{
			v.push_back(CElementObject(reinterpret_cast <const DOMElement*>(pNodeList->item(u))));
		}
		return v;
	}

	string CXMLObject::CElementObject::GetElementName(void) const
	{
		if (NULL == this->m_pElement)
		{
			return string();
		}
                return XMLChToStr(this->m_pElement->getNodeName());
	}

	string CXMLObject::CElementObject::GetElementValue(void) const
	{
		if (NULL == this->m_pElement)
		{
			return string();
		}
                return XMLChToStr(this->m_pElement->getNodeValue());
	}

	string CXMLObject::CElementObject::GetAttribute(const string& strAttrName) const
	{
		if (NULL == this->m_pElement)
		{
			return string();
		}

                return XMLChToStr(this->m_pElement->getAttribute(StrToXMLCh(strAttrName)));
	}

	/************************************************************************/
	/* CXMLObject                                                                     */
	/************************************************************************/
	CXMLObject::CXMLObject(const string& strXMLFile) :
		m_pDoc(NULL),
		m_pRoot(NULL),
		m_bIsSuccessful(false)
	{
		if (NULL != this->m_pParse)
		{
			string str = Trim(strXMLFile);

			if (IsFile(Trim(strXMLFile)))
			{
				this->m_strContent = ReadWholeFile(str);
				this->m_pParse->parse(str.c_str());
			}
			else
			{
				string strTempFileName;
				strTempFileName = GetRandomName();
				this->m_strContent = strXMLFile;
				WriteWholeFile(strTempFileName, this->m_strContent);
				this->m_pParse->parse(strTempFileName.c_str());
				RemoveFile(strTempFileName);
			}
			this->m_pDoc = this->m_pParse->getDocument();
			if (NULL != this->m_pDoc)
			{
				this->m_pRoot = this->m_pDoc->getDocumentElement();
				if (NULL != this->m_pRoot)
				{
					this->m_bIsSuccessful = true;
				}
				else
				{
					this->m_pParse = NULL;
					this->m_pDoc = NULL;
					this->m_pRoot = NULL;
				}
			}
		}
	}

	vector<CXMLObject::CElementObject> CXMLObject::GetElements(const string& strTagName) const
	{
		vector<CElementObject> v;

		if (NULL != this->m_pRoot)
		{
			DOMNodeList* pNodeList = this->m_pRoot->getElementsByTagName(StrToXMLCh(strTagName));
			unsigned int u32ListLen = pNodeList->getLength();

			for (unsigned int u = 0; u < u32ListLen; ++u)
			{
				v.push_back(CElementObject(reinterpret_cast <const DOMElement*>(pNodeList->item(u))));
			}
		}
		return v;
	}

	CXMLObject::CElementObject CXMLObject::GetFirstElement(const string& strTagName) const
	{
		vector<CElementObject> v = this->GetElements(strTagName);

		if (v.empty())
		{
			return CElementObject(NULL);
		}
		else
		{
			return v[0];
		}
	}

	string CXMLObject::GetContent(void) const
	{
		return this->m_strContent;
	}
}
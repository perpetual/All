#include "NetAdapter/NetAdapter.h"
#include <exception>
#include "MyTools/MyUtilityTools.h"
#include "MyTools/MyNetTools.h"

namespace NetAdapter
{
	using std::exception;
	using MyTools::NumberToHexString;

	CNetAdapter::CNetAdapter(void) :
		m_pAdapterInfo(NULL),
		m_ulAdapterInfoSize(0)
	{
		::GetAdaptersInfo(this->m_pAdapterInfo, &this->m_ulAdapterInfoSize);

		this->m_pAdapterInfo = reinterpret_cast<PIP_ADAPTER_INFO>(new char[this->m_ulAdapterInfoSize]);
		if (NULL == this->m_pAdapterInfo)
		{
			throw exception("为适配器数据结构分配空间失败");
		}
		else
		{
			if (ERROR_SUCCESS != ::GetAdaptersInfo(this->m_pAdapterInfo, &this->m_ulAdapterInfoSize))
			{
				delete[] this->m_pAdapterInfo;
				this->m_pAdapterInfo = NULL;
				throw exception("获取适配器信息失败");
			}
			else
			{
				PIP_ADAPTER_INFO p = this->m_pAdapterInfo;
				while (NULL != p)
				{
					TNetAdapterInfo tNetAdapterInfo;
					tNetAdapterInfo.m_uiIndex = p->Index;
					tNetAdapterInfo.m_strNetAdapterName = p->AdapterName;
					tNetAdapterInfo.m_strNetAdapterDescription = p->Description;
					tNetAdapterInfo.m_ullMACAddress = (*reinterpret_cast<unsigned long long*>(p->Address));
					for (unsigned int u = 0; u < p->AddressLength; ++u)
					{
						string str = NumberToHexString(p->Address[u], true);
						tNetAdapterInfo.m_strMACAddress += (str.length() < 2 ? (string("0") + str) : str) + '-';
					}
					tNetAdapterInfo.m_strMACAddress.resize(tNetAdapterInfo.m_strMACAddress.length() - 1);
					tNetAdapterInfo.m_strIPAddress = p->IpAddressList.IpAddress.String;
					tNetAdapterInfo.m_strGatewayAddress = p->GatewayList.IpAddress.String;
					tNetAdapterInfo.m_strMask = p->IpAddressList.IpMask.String;
					this->m_vecNetAdapters.push_back(tNetAdapterInfo);
					p = p->Next;
				}
			}
		}
	}

	CNetAdapter::~CNetAdapter(void)
	{
		delete[] this->m_pAdapterInfo;
	}

	unsigned int CNetAdapter::GetCount(void) const
	{
		return this->m_vecNetAdapters.size();
	}

	unsigned int CNetAdapter::GetIndex(unsigned int uiIndex) const
	{
		unsigned int uiRet = 0;
		if (uiIndex < this->m_vecNetAdapters.size())
		{
			uiRet = this->m_vecNetAdapters[uiIndex].m_uiIndex;
		}
		return uiRet;
	}

	string CNetAdapter::GetName(unsigned int uiIndex) const
	{
		string strRet;
		if (uiIndex < this->m_vecNetAdapters.size())
		{
			strRet = this->m_vecNetAdapters[uiIndex].m_strNetAdapterName;
		}
		return strRet;
	}

	string CNetAdapter::GetDescription(unsigned int uiIndex) const
	{
		string strRet;
		if (uiIndex < this->m_vecNetAdapters.size())
		{
			strRet = this->m_vecNetAdapters[uiIndex].m_strNetAdapterDescription;
		}
		return strRet;
	}

	unsigned long long CNetAdapter::GetMACAddress1(unsigned int uiIndex) const
	{
		unsigned long long ullRet = 0;
		if (uiIndex < this->m_vecNetAdapters.size())
		{
			ullRet = this->m_vecNetAdapters[uiIndex].m_ullMACAddress;
		}
		return ullRet;
	}

	string CNetAdapter::GetMACAddress2(unsigned int uiIndex) const
	{
		string strRet;
		if (uiIndex < this->m_vecNetAdapters.size())
		{
			strRet = this->m_vecNetAdapters[uiIndex].m_strMACAddress;
		}
		return strRet;
	}

	string CNetAdapter::GetIPAddress(unsigned int uiIndex) const
	{
		string strRet;
		if (uiIndex < this->m_vecNetAdapters.size())
		{
			strRet = this->m_vecNetAdapters[uiIndex].m_strIPAddress;
		}
		return strRet;
	}

	string CNetAdapter::GetGatewayAddress(unsigned int uiIndex) const
	{
		string strRet;
		if (uiIndex < this->m_vecNetAdapters.size())
		{
			strRet = this->m_vecNetAdapters[uiIndex].m_strGatewayAddress;
		}
		return strRet;
	}

	string CNetAdapter::GetMask(unsigned int uiIndex) const
	{
		string strRet;
		if (uiIndex < this->m_vecNetAdapters.size())
		{
			strRet = this->m_vecNetAdapters[uiIndex].m_strMask;
		}
		return strRet;
	}
}
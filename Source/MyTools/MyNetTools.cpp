#include <VersionControl.h>
#include <exception>
#include <cstring>
#include "MyTools/MyUtilityTools.h"
#include "MyTools/MyNetTools.h"

namespace MyTools
{
	using std::exception;

	unsigned int CInitSocketLibrary::m_uiSocketLibraryInitCount = 0;			//套接字库的初始化次数

	CInitSocketLibrary::CInitSocketLibrary(unsigned short usHigh, unsigned short usLow)
	{
#ifdef __OS_VERSION_WINDOWS__
		if (0 == this->m_uiSocketLibraryInitCount++)
		{
			WSAData oWSAData;

			if (0 != ::WSAStartup(MAKEWORD(usHigh, usLow), &oWSAData))
			{
				throw exception("加载套接字库失败");
			}
		}
#endif
	}

	CInitSocketLibrary::~CInitSocketLibrary(void)
	{
#ifdef __OS_VERSION_WINDOWS__
		if (this->m_uiSocketLibraryInitCount > 0 && 0 == --this->m_uiSocketLibraryInitCount)
		{
			WSACleanup();
		}
#endif
	}

	bool CheckIP(const string& strIP)
	{
		return (static_cast<unsigned int>(-1) != inet_addr(Trim(strIP).c_str()) || "255.255.255.255" == Trim(strIP));
	}

	string NetUIntToStringIP(unsigned int uiIP, bool bConversion)
	{
		if (bConversion)
		{
			uiIP = htonl(uiIP);
		}
		return ::inet_ntoa(*reinterpret_cast<const in_addr*>(&uiIP));
	}

	unsigned int StringIPToNetUInt(const string& strIP)
	{
		return ::inet_addr(Trim(strIP).c_str());
	}

	string GetHostName(void)
	{
		CInitSocketLibrary o;

		char buf[1024];

		memset(buf, '\0', 1024);
		::gethostname(buf, 1024);
		return buf;
	}

	vector<string> GetHostAddress(const string& strHostName)
	{
		vector<string> vecIPAddressRet;
#ifdef __OS_VERSION_WINDOWS__
		CInitSocketLibrary o;
		struct hostent* p = gethostbyname(Trim(strHostName).c_str());

		if (NULL != p)
		{
			unsigned int u = 0;
			while (NULL != p->h_addr_list[u])
			{
				vecIPAddressRet.push_back(inet_ntoa(*reinterpret_cast<const in_addr*>(reinterpret_cast<unsigned long*>(p->h_addr_list[u++]))));
			}
		}
#elif defined (__OS_VERSION_LINUX__)
		int sock = ::socket(PF_INET, SOCK_STREAM, 0);
		struct ifconf conf;
		int iCount = 1;

		bzero(&conf, sizeof (conf));
		if (Trim(strHostName).empty())
		{
			int sock = ::socket(AF_INET, SOCK_STREAM, 0);
			if (-1 != sock)
			{
				if (-1 != ::ioctl(sock, SIOCGIFCONF, &conf))
				{
					conf.ifc_ifcu.ifcu_buf = new char[conf.ifc_len];		//分配缓冲区
					iCount = conf.ifc_len / sizeof (ifreq);
					if (-1 == ::ioctl(sock, SIOCGIFCONF, &conf))
					{
						::close(sock);
						delete[] conf.ifc_ifcu.ifcu_buf;
						return vector<string>();
					}
				}
			}
		}

		sockaddr_in* pHost = NULL;

		if (NULL == conf.ifc_ifcu.ifcu_buf)
		{
			conf.ifc_ifcu.ifcu_buf = new char[sizeof (ifreq)];
			bzero(conf.ifc_ifcu.ifcu_buf, sizeof (ifreq));
			strncpy(conf.ifc_ifcu.ifcu_req->ifr_ifrn.ifrn_name, strHostName.c_str(), strHostName.length());
		}

		for (int i = 0; i < iCount; ++i)
		{
			if (-1 != ::ioctl(sock, SIOCGIFADDR, &conf.ifc_ifcu.ifcu_req[i]))
			{
				pHost = reinterpret_cast<sockaddr_in*>(&conf.ifc_ifcu.ifcu_req[i].ifr_ifru.ifru_addr);
				if (NULL != pHost)
				{
					vecIPAddressRet.push_back(inet_ntoa(pHost->sin_addr));
				}
			}
		}
		delete[] conf.ifc_ifcu.ifcu_buf;
#endif
		return vecIPAddressRet;
	}

	vector<string> GetHostAddressAd(const string& strHostName)
	{
		addrinfo* pAddrInfo = NULL;
		vector<string> vecAddressRet;

		CInitSocketLibrary o;

		if (0 != getaddrinfo(Trim(strHostName).c_str(), "0", NULL, &pAddrInfo))
		{
			return vecAddressRet;
		}
		else
		{
			while (NULL != pAddrInfo)
			{
				vecAddressRet.push_back(inet_ntoa(reinterpret_cast<sockaddr_in*>(pAddrInfo->ai_addr)->sin_addr));
				pAddrInfo = pAddrInfo->ai_next;
			}
			return vecAddressRet;
		}
	}

	string GetIPAddress(const string& str)
	{
		string s = Trim(str);

		if (!CheckIP(s))
		{
			s = GetHostAddress(s).front();
		}

		return s;
	}

	sockaddr_in FillSockAddr(const string& strIP, unsigned short usPort)
	{
		sockaddr_in addrSock;

		addrSock.sin_family = AF_INET;

#ifdef __OS_VERSION_WINDOWS__
		addrSock.sin_addr.S_un.S_addr = StringIPToNetUInt(strIP);
#elif defined(__OS_VERSION_LINUX__)
		addrSock.sin_addr.s_addr = StringIPToNetUInt(strIP);
#endif
		addrSock.sin_port = htons(usPort);

		return addrSock;
	}

	vector<unsigned short> GetMACAddress(const string& strIP)
	{
		vector<unsigned short> vecMACAddr;
		unsigned char ucDstMACAddr[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
		unsigned long ulMACAddrLen = 6;
#ifdef __OS_VERSION_WINDOWS__
		if (NO_ERROR == ::SendARP(StringIPToNetUInt(strIP), 0, ucDstMACAddr, &ulMACAddrLen))
		{
			for (unsigned int u = 0; u < ulMACAddrLen; ++u)
			{
				vecMACAddr.push_back(ucDstMACAddr[u]);
			}
		}
#endif
		return vecMACAddr;
	}
}
#include "Sniffer.h"
#include "MyTools/MyNetTools.h"
#include "MyTools/MySocketTools.h"
#include "NetProtocol/NetProtocol.h"
#include <exception>
#include <cstdio>
#include <cstring>
#ifdef __OS_VERSION_LINUX__
#include <linux/if_ether.h>
#include <netpacket/packet.h>
#endif

namespace Sniffer
{
	using MyTools::StringIPToNetUInt;
	using MyTools::GetHostAddress;
	using MyTools::SetRawSocketReceiveAll;
	using std::exception;
	using namespace NetProtocol;
	using MyTools::CheckIP;
	using Utility::exceptionx;

#ifdef __OS_VERSION_WINDOWS__
	CSniffer::CSniffer(bool bPromiscuous, unsigned int uiBufLen) :
#elif defined (__OS_VERSION_LINUX__)
	CSniffer::CSniffer(const string& strName, bool bPromiscuous, unsigned int uiBufLen) :
#endif
		m_uiBufLen(uiBufLen)
	{
		if (NULL == (this->m_pBuf = new char[this->m_uiBufLen]))
		{
			throw exceptionx("缓冲区分配失败");
		}
		else
		{
#ifdef __OS_VERSION_WINDOWS__
			this->m_sock = ::socket(AF_INET, SOCK_RAW, IPPROTO_IP);
#elif defined (__OS_VERSION_LINUX__)
			this->m_sock = ::socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
#endif
			if (INVALID_SOCKET == this->m_sock)
			{
				throw exceptionx("创建原始套接字失败");
			}
			else
			{
#ifdef __OS_VERSION_WINDOWS__
				SOCKADDR_IN addrBind;

				addrBind.sin_family = AF_INET;
				addrBind.sin_port = htons(0);
				addrBind.sin_addr.S_un.S_addr = StringIPToNetUInt(GetHostAddress().front());			//绑定到明确的本地IP地址
#elif defined (__OS_VERSION_LINUX__)
				struct ifreq ifr;
				sockaddr_ll addrBind;

				memset(&addrBind, 0, sizeof (addrBind));
				strncpy(ifr.ifr_ifrn.ifrn_name, strName.c_str(), strName.length() + 1);
				if (0 != ::ioctl(this->m_sock, SIOCGIFINDEX, &ifr))
				{
					perror("");
					throw exceptionx("设置套接字序号失败");
				}
				addrBind.sll_family = AF_PACKET;
				addrBind.sll_ifindex = ifr.ifr_ifru.ifru_ivalue;
				addrBind.sll_protocol = htons(ETH_P_ALL);

#endif
				if (SOCKET_ERROR == ::bind(this->m_sock, reinterpret_cast<SOCKADDR*>(&addrBind), sizeof (addrBind)))
				{
					::closesocket(this->m_sock);
					perror("");
					throw exceptionx("套接字绑定失败");
				}
				else
				{
#ifdef __OS_VERSION_WINDOWS__
					if (bPromiscuous && !SetRawSocketReceiveAll(this->m_sock))
#elif defined (__OS_VERSION_LINUX__)
					if (bPromiscuous && !SetRawSocketReceiveAll(this->m_sock, "eth2"))
#endif
					{
						::closesocket(this->m_sock);
						throw exceptionx("设置混杂模式失败");
					}
				}
			}
		}
	}

	CSniffer::~CSniffer(void)
	{
		::closesocket(this->m_sock);
	}

	void CSniffer::Start(void) const
	{
		socklen_t len = sizeof (SOCKADDR);
		SOCKADDR addrTemp;

		while (true)
		{
			int iRecvLen = ::recvfrom(this->m_sock, this->m_pBuf, this->m_uiBufLen, 0, &addrTemp, &len);

			if (SOCKET_ERROR == iRecvLen)
			{
				::closesocket(this->m_sock);
				iRecvLen = 0;
				break;
			}
			else
			{
				char* pBuf = this->m_pBuf;
#ifdef __OS_VERSION_LINUX__
				const TEtherHeader* pEtherHeader = reinterpret_cast<const TEtherHeader*>(pBuf);
				pEtherHeader->Display();
				pBuf += sizeof (TEtherHeader);
#endif
				const TIPHeader* pIPHeader = reinterpret_cast<const TIPHeader*>(pBuf);
				if ((this->m_setSrcIP.empty() || this->m_setSrcIP.count(pIPHeader->m_uiSrcIP) > 0)
					&& (this->m_setDstIP.empty() || this->m_setDstIP.count(pIPHeader->m_uiDstIP) > 0)
					&& (this->m_setProtocol.empty() || this->m_setProtocol.count(pIPHeader->m_ucProtocol) > 0))
				{
					switch (pIPHeader->m_ucProtocol)
					{
					case IPPROTO_UDP:
						{
							const TUDPHeader* pUDPHeader = reinterpret_cast<const TUDPHeader*>(this->m_pBuf + sizeof (TIPHeader));
							if (this->HasPort(::ntohs(pUDPHeader->m_usSrcPort), ::ntohs(pUDPHeader->m_usDstPort)))
							{
								pIPHeader->Display();
								pUDPHeader->Display();
							}
						}
						break;
					case IPPROTO_TCP:
						{
							const TTCPHeader* pTCPHeader = reinterpret_cast<const TTCPHeader*>(this->m_pBuf + sizeof (TIPHeader));
							if (this->HasPort(::ntohs(pTCPHeader->m_usSrcPort), ::ntohs(pTCPHeader->m_usDstPort)))
							{
								pIPHeader->Display();
								pTCPHeader->Display();
							}
						}
						break;
					case IPPROTO_ICMP:
						{
							const TICMPHeader* pICMPHeader = reinterpret_cast<const TICMPHeader*>(this->m_pBuf + sizeof (TIPHeader));
							if (this->m_setSrcPort.empty() && this->m_setDstPort.empty())
							{
								pIPHeader->Display();
								pICMPHeader->Display();
							}
						}
						break;
					}
				}
			}
		}
	}

	void CSniffer::AddSourceIP(const string& strSrcIP)
	{
		if (CheckIP(strSrcIP))
		{
			this->m_setSrcIP.insert(StringIPToNetUInt(strSrcIP));
		}
	}

	void CSniffer::RemoveSourceIP(const string& strSrcIP)
	{
		if (CheckIP(strSrcIP))
		{
			this->m_setSrcIP.erase(StringIPToNetUInt(strSrcIP));
		}
	}

	void CSniffer::AddDestinationIP(const string& strDstIP)
	{
		if (CheckIP(strDstIP))
		{
			this->m_setDstIP.insert(StringIPToNetUInt(strDstIP));
		}
	}

	void CSniffer::RemoveDestinationIP(const string& strDstIP)
	{
		if (CheckIP(strDstIP))
		{
			this->m_setDstIP.erase(StringIPToNetUInt(strDstIP));
		}
	}

	void CSniffer::AddSourcePort(unsigned short usSrcPort)
	{
		this->m_setSrcPort.insert(usSrcPort);
	}

	void CSniffer::RemoveSourcePort(unsigned short usSrcPort)
	{
		this->m_setSrcPort.erase(usSrcPort);
	}

	void CSniffer::AddDestinationPort(unsigned short usDstPort)
	{
		this->m_setDstPort.insert(usDstPort);
	}

	void CSniffer::RemoveDestinationPort(unsigned short usDstPort)
	{
		this->m_setDstPort.erase(usDstPort);
	}

	void CSniffer::AddProtocol(unsigned char ucProtocol)
	{
		this->m_setProtocol.insert(ucProtocol);
	}

	void CSniffer::RemoveProtocol(unsigned char ucProtocol)
	{
		this->m_setProtocol.erase(ucProtocol);
	}

	bool CSniffer::HasPort(unsigned short usSrcPort, unsigned short usDstPort) const
	{
		return ((this->m_setSrcPort.empty() || this->m_setSrcPort.count(usSrcPort) > 0)
					&& (this->m_setDstPort.empty() || this->m_setDstPort.count(usDstPort) > 0));
	}
}
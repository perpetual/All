#include "VersionControl.h"
#include "DataPath/RawUDPClient.h"
#include <exception>
#include "MyTools/MySocketTools.h"
#include "MyTools/MyNetTools.h"

namespace DataPath
{
	using Utility::exceptionx;
	using MyTools::SetRawSocketIPHeader;
	using NetProtocol::CheckSum;
	using NetProtocol::UDPCheckSum;
	using MyTools::SetSocketNonBlock;
	using MyTools::GetHostAddress;
	using MyTools::StringIPToNetUInt;

	CRawUDPClient::CRawUDPClient(const string& strDstIP, unsigned short usDstPort, unsigned short usSrcPort) :
		m_usID(0)
	{
		if (usDstPort == usSrcPort)
		{
			throw exceptionx("源端口与目标端口相同");
		}
		else
		{
			if (SOCKET_ERROR == (this->m_sock = ::socket(AF_INET, SOCK_RAW, IPPROTO_UDP)))
			{
				throw exceptionx("创建原始套接字失败");
			}
			else
			{
				if (!SetRawSocketIPHeader(this->m_sock))			//允许包含IP头
				{
					::closesocket(this->m_sock);
					throw exceptionx("允许设置IP头失败");
				}
				else
				{
					//IP头
					this->m_tIPHeader.m_ucVersion = 4;
					this->m_tIPHeader.m_ucHeaderLen = sizeof (TIPHeader) / sizeof (unsigned int);
					this->m_tIPHeader.m_ucTTL = 128;
					this->m_tIPHeader.m_ucProtocol = IPPROTO_UDP;
					this->m_tIPHeader.m_uiSrcIP = StringIPToNetUInt(GetHostAddress().front());
					this->m_tIPHeader.m_uiDstIP = StringIPToNetUInt(strDstIP);

					//UDP头
					this->m_tUDPHeader.m_usSrcPort = ::htons(usSrcPort);
					this->m_tUDPHeader.m_usDstPort = ::htons(usDstPort);
					this->m_tUDPHeader.m_usChkSum = 0;

					this->m_addrSock.sin_family = AF_INET;
#ifdef __OS_VERSION_WINDOWS__
					this->m_addrSock.sin_addr.S_un.S_addr = this->m_tIPHeader.m_uiDstIP;
#elif defined (__OS_VERSION_LINUX__)
					this->m_addrSock.sin_addr.s_addr = this->m_tIPHeader.m_uiDstIP;
#endif
					this->m_addrSock.sin_port = this->m_tUDPHeader.m_usDstPort;
				}
			}
		}
	}

	CRawUDPClient::~CRawUDPClient(void)
	{
		::closesocket(this->m_sock);
	}

	bool CRawUDPClient::Send(const string& str)
	{
		this->m_tIPHeader.m_usTotalSize = ::htons(static_cast<unsigned short>(sizeof (TIPHeader) + sizeof (TUDPHeader) + str.length()));
		this->m_tIPHeader.m_usID = ::htons(++this->m_usID);
		this->m_tIPHeader.m_usChkSum = CheckSum(reinterpret_cast<unsigned short*>(&this->m_tIPHeader), sizeof (TIPHeader));
		this->m_tUDPHeader.m_usLen = ::htons(static_cast<unsigned short>(sizeof (TUDPHeader) + str.length()));
		this->m_tUDPHeader.m_usChkSum = UDPCheckSum(this->m_tIPHeader, this->m_tUDPHeader, str);

		string s(reinterpret_cast<char*>(&this->m_tIPHeader), sizeof (TIPHeader));
		s.append(reinterpret_cast<char*>(&this->m_tUDPHeader), sizeof (TUDPHeader));
		s += str;
		return !(SOCKET_ERROR == ::sendto(this->m_sock, s.data(), s.length(), 0, reinterpret_cast<sockaddr*>(&this->m_addrSock), sizeof (sockaddr)));
	}
}
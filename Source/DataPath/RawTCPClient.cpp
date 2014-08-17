#include "VersionControl.h"
#include <cstdio>
#include <cstdlib>
#include <cerrno>
#include "DataPath/RawTCPClient.h"
#include "MyTools/MySocketTools.h"
#include "MyTools/MyNetTools.h"
#include "MyTools/MyUtilityTools.h"

namespace DataPath
{
	using Utility::exceptionx;
	using MyTools::SetRawSocketIPHeader;
	using NetProtocol::CheckSum;
	using NetProtocol::UDPCheckSum;
	using NetProtocol::TTCPOption1;
	using MyTools::SetSocketNonBlock;
	using MyTools::GetHostAddress;
	using MyTools::StringIPToNetUInt;
	using MyTools::AppendString;
	using NetProtocol::TTCPOption1;

	CRawTCPClient::CRawTCPClient(const string& strDstIP, unsigned short usDstPort, unsigned short usSrcPort) :
	m_usID(0),
		m_uiSeq(0)
	{
		if (usDstPort == usSrcPort)
		{
			throw exceptionx("源端口与目标端口相同");
		}
		else
		{
			if (SOCKET_ERROR == (this->m_sock = ::socket(AF_INET, SOCK_RAW, IPPROTO_TCP)))
			{
				perror("");
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
					this->m_tIPHeader.m_ucProtocol = IPPROTO_TCP;
					this->m_tIPHeader.m_uiSrcIP = StringIPToNetUInt(GetHostAddress().front());
					this->m_tIPHeader.m_uiDstIP = StringIPToNetUInt(strDstIP);
					this->m_tIPHeader.m_usID = ::htons(++this->m_usID);
					this->m_tIPHeader.m_ucFlag = 0x0;
					this->m_tIPHeader.m_usOffset = 0;
					*reinterpret_cast<unsigned short*>(&this->m_usID + 1) = ::htons(*reinterpret_cast<unsigned short*>(&this->m_usID + 1));		//改变字节序
					this->m_tIPHeader.m_usChkSum = CheckSum(reinterpret_cast<unsigned short*>(&this->m_tIPHeader), sizeof (TIPHeader));

					//三次握手
					TTCPHeader tTCPHeader;
					TTCPOption1 tOption1;			//三次握手第一步所需的TCP选项

					tTCPHeader.m_usSrcPort = ::htons(usSrcPort);
					tTCPHeader.m_usDstPort = ::htons(usDstPort);
					tTCPHeader.m_uiSeqNO = ::htonl(++this->m_uiSeq);
					tTCPHeader.m_ucOffset = (sizeof (TTCPHeader) + sizeof (TTCPOption1)) / sizeof (unsigned int);
					tTCPHeader.m_ucFlag = 0x2;			//SYN置1
					//tTCPHeader.m_ucFlag = 0x1;			//FIN置1
					//tTCPHeader.m_ucFlag = 0x4;			//SYN置1
					tTCPHeader.m_usWindowSize = ::htons(64240);
					*reinterpret_cast<unsigned short*>(&tTCPHeader.m_uiAckNO + 1) = ::htons(*reinterpret_cast<unsigned short*>(&tTCPHeader.m_uiAckNO + 1));

					tOption1.m_uiMSS = ::htonl(0x020405b4);
					tOption1.m_ui16Sack = ::htons(0x0402);
					tOption1.m_ui8NOP1 = 1;
					tOption1.m_ui8NOP2 = 1;

					tTCPHeader.m_usChkSum = TCPCheckSum(this->m_tIPHeader, tTCPHeader, string(reinterpret_cast<char*>(&tOption1), sizeof (tOption1)));

					this->m_addrSock.sin_family = AF_INET;
#ifdef __OS_VERSION_WINDOWS__
					this->m_addrSock.sin_addr.S_un.S_addr = this->m_tIPHeader.m_uiDstIP;
#elif __OS_VERSION_LINUX__
					this->m_addrSock.sin_addr.s_addr = this->m_tIPHeader.m_uiDstIP;
#endif
					this->m_addrSock.sin_port = ::htons(usDstPort);

					string str;

					this->m_tIPHeader.m_usTotalSize = ::htons(sizeof (this->m_tIPHeader) + sizeof (tTCPHeader) + sizeof (tOption1));
					this->m_tIPHeader.m_usChkSum = CheckSum(reinterpret_cast<unsigned short*>(&this->m_tIPHeader), sizeof (this->m_tIPHeader));
					AppendString(str, &this->m_tIPHeader, sizeof (this->m_tIPHeader));
					AppendString(str, &tTCPHeader, sizeof (tTCPHeader));
					AppendString(str, &tOption1, sizeof (tOption1));

					int iSend = ::sendto(this->m_sock, str.data(), str.length(), 0, reinterpret_cast<sockaddr*>(&this->m_addrSock), sizeof (this->m_addrSock));		//第一次握手
					printf("%d\n", iSend);
#ifdef __OS_VERSION_WINDOWS__
					printf("%d\n", ::WSAGetLastError());
#elif defined (__OS_VERSION_LINUX__)
					perror("");
#endif
				}
			}
		}
	}

	CRawTCPClient::~CRawTCPClient(void)
	{
		::closesocket(this->m_sock);
	}
}
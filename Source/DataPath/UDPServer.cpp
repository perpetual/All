#include "VersionControl.h"
#include "DataPath/UDPServer.h"
#include <exception>
#include "MyTools/MySocketTools.h"

namespace DataPath
{
	using MyTools::NetUIntToStringIP;
	using MyTools::StringIPToNetUInt;
	using MyTools::SetRawSocketReceiveAll;
	using Utility::exceptionx;

	CUDPServer::CUDPServer(unsigned short usPort, const string& strIP, unsigned int uiRecvBufLen) :
		m_uiRecvBufSize(uiRecvBufLen),
		m_pRecvBuf(new char[uiRecvBufLen])
	{
		this->m_sock = ::socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
#ifdef __OS_VERSION_WINDOWS__
		this->m_addrClient.sin_addr.S_un.S_addr = 0;
#elif defined (__OS_VERSION_LINUX__)
		this->m_addrClient.sin_addr.s_addr = 0;
#endif
		this->m_addrClient.sin_port = 0;

		if (INVALID_SOCKET == this->m_sock)
		{
			throw exceptionx("创建数据报套接字失败");
		}
		else
		{
			sockaddr_in addrBind;

			addrBind.sin_family = AF_INET;
#ifdef __OS_VERSION_WINDOWS__
			addrBind.sin_addr.S_un.S_addr = StringIPToNetUInt(strIP);
#elif defined (__OS_VERSION_LINUX__)
			addrBind.sin_addr.s_addr = StringIPToNetUInt(strIP);
#endif
			addrBind.sin_port = ::htons(usPort);
			if (SOCKET_ERROR == ::bind(this->m_sock, reinterpret_cast<sockaddr*>(&addrBind), sizeof (sockaddr)))
			{
				::closesocket(this->m_sock);
				throw exceptionx("绑定套接字失败");
			}
			//mytools::SetSocketMulticast(this->m_sock, "234.5.6.7", "192.168.1.2");
		}
	}

	CUDPServer::~CUDPServer(void)
	{
		::closesocket(this->m_sock);
		delete[] this->m_pRecvBuf;
	}

	string CUDPServer::Receive(void)
	{
#ifdef __OS_VERSION_WINDOWS__
		int len = sizeof (sockaddr);
#elif defined (__OS_VERSION_LINUX__)
		socklen_t len = sizeof (sockaddr);
#endif
		int iRecvLen = ::recvfrom(this->m_sock, this->m_pRecvBuf, this->m_uiRecvBufSize, 0, reinterpret_cast<sockaddr*>(&this->m_addrClient), &len);

		if (SOCKET_ERROR == iRecvLen)
		{
			::closesocket(this->m_sock);
			iRecvLen = 0;
		}

		return string(this->m_pRecvBuf, iRecvLen);
	}

	string CUDPServer::GetClientAddress(void) const
	{
#ifdef __OS_VERSION_WINDOWS__
		return NetUIntToStringIP(this->m_addrClient.sin_addr.S_un.S_addr);
#elif defined (__OS_VERSION_LINUX__)
		return NetUIntToStringIP(this->m_addrClient.sin_addr.s_addr);
#endif
	}

	unsigned short CUDPServer::GetClientPort(void) const
	{
		return ntohs(this->m_addrClient.sin_port);
	}
}
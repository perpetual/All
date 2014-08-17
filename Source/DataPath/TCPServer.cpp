#include "VersionControl.h"
#include <iostream>
#include <cerrno>
#include "DataPath/TCPServer.h"
#include "MyTools/MyUtilityTools.h"
#include "MyTools/MyNetTools.h"

namespace DataPath
{
	using MyTools::NetUIntToStringIP;
	using MyTools::StringIPToNetUInt;
	using MyTools::FillSockAddr;
	using MyTools::Trim;
	using Utility::exceptionx;

	CTCPServer::CTCPServer(unsigned short usPort, const string& strIP, unsigned int uiRecvBufLen) :
		m_uiRecvBufSize(uiRecvBufLen),
		m_bInit(false)
	{
		if (0 == this->m_uiRecvBufSize)
		{
			throw exceptionx("接收缓冲区长度非法");
		}

		this->m_sock = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (INVALID_SOCKET == this->m_sock)
		{
			throw exceptionx("创建流式套接字失败");
		}
		else
		{
#ifdef __OS_VERSION_WINDOWS__
			int i = 0;
			int j = sizeof (int);
#elif defined (__OS_VERSION_LINUX__)
			socklen_t i = 0;
			socklen_t j = sizeof (socklen_t);
#endif
			getsockopt(this->m_sock, IPPROTO_IP, IP_TTL, reinterpret_cast<char*>(&i), &j);
			m_addrListen.sin_family = AF_INET;
#ifdef __OS_VERSION_WINDOWS__
			m_addrListen.sin_addr.S_un.S_addr = StringIPToNetUInt(Trim(strIP));
#elif defined (__OS_VERSION_LINUX__)
			m_addrListen.sin_addr.s_addr = StringIPToNetUInt(Trim(strIP));
#endif
			m_addrListen.sin_port = htons(usPort);
		}
	}

	CTCPServer::~CTCPServer(void)
	{
		::closesocket(this->m_sock);
		this->m_sock = INVALID_SOCKET;
		this->m_bInit = false;
	}

	CTCPServer::CTCPClientSocket::CTCPClientSocket(void) :
		m_sockClient(INVALID_SOCKET),
		m_pRecvBuf(NULL),
		m_uiRecvBufSize(0)
	{
		this->m_addrClient = FillSockAddr();
	}

	CTCPServer::CTCPClientSocket::~CTCPClientSocket(void)
	{
		this->CloseSocket();
		this->m_sockClient = INVALID_SOCKET;
		delete[] this->m_pRecvBuf;
		this->m_pRecvBuf = NULL;
	}

	CTCPServer::CTCPClientSocket::operator bool(void) const
	{
		return INVALID_SOCKET != this->m_sockClient;
	}

	string CTCPServer::CTCPClientSocket::GetClientAddress(void) const
	{
#ifdef __OS_VERSION_WINDOWS__
		return NetUIntToStringIP(this->m_addrClient.sin_addr.S_un.S_addr);
#elif defined (__OS_VERSION_LINUX__)
		return NetUIntToStringIP(this->m_addrClient.sin_addr.s_addr);
#endif
	}

	unsigned short CTCPServer::CTCPClientSocket::GetClientPort(void) const
	{
		return ntohs(this->m_addrClient.sin_port);
	}

	void CTCPServer::CTCPClientSocket::CloseSocket(void)
	{
		::closesocket(this->m_sockClient);
		this->m_sockClient = INVALID_SOCKET;
	}

	bool CTCPServer::Accept(CTCPClientSocket& oTCPClientSocket)
	{
#ifdef __OS_VERSION_WINDOWS__
		int len = sizeof (sockaddr);
#elif defined (__OS_VERSION_LINUX__)
		socklen_t len = sizeof (sockaddr);
#endif
		sockaddr_in addrClient = FillSockAddr();

		if (!this->m_bInit)
		{
			if (SOCKET_ERROR == ::bind(this->m_sock, reinterpret_cast<sockaddr*>(&m_addrListen), sizeof (sockaddr)))
			{
				::closesocket(this->m_sock);
				throw exceptionx("套接字绑定失败");
			}
			else
			{
				if (SOCKET_ERROR == ::listen(this->m_sock, SOMAXCONN))
				{
					::closesocket(this->m_sock);
					throw exceptionx("套接字监听失败");
				}
			}
			this->m_bInit = true;
		}

		oTCPClientSocket.m_sockClient = ::accept(this->m_sock, reinterpret_cast<sockaddr*>(&addrClient), &len);

		if (oTCPClientSocket)
		{
			oTCPClientSocket.m_addrClient = addrClient;
			oTCPClientSocket.m_uiRecvBufSize = this->m_uiRecvBufSize;
			oTCPClientSocket.m_pRecvBuf = new char[oTCPClientSocket.m_uiRecvBufSize];
		}

		return oTCPClientSocket;
	}

	pair<string, int> CTCPServer::Receive(CTCPClientSocket& oTCPClientSocket)
	{
		int iRecvLen = ::recv(oTCPClientSocket.m_sockClient, oTCPClientSocket.m_pRecvBuf, oTCPClientSocket.m_uiRecvBufSize, 0);

		if (SOCKET_ERROR == iRecvLen)
		{
			iRecvLen = 0;
			oTCPClientSocket.CloseSocket();
		}

		return make_pair(string(oTCPClientSocket.m_pRecvBuf, iRecvLen), errno);
	}

	bool CTCPServer::Send(CTCPClientSocket& oTCPClientSocket, const string& strBuf)
	{
		bool bRet = false;

		if (SOCKET_ERROR == ::send(oTCPClientSocket.m_sockClient, strBuf.c_str(), strBuf.length(), 0))
		{
			oTCPClientSocket.CloseSocket();
		}
		else
		{
			bRet = true;
		}
		return bRet;
	}
}
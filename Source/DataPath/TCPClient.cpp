#include "VersionControl.h"
#include <cerrno>
#include "DataPath/TCPClient.h"
#include "MyTools/MyNetTools.h"

namespace DataPath
{
	using MyTools::StringIPToNetUInt;
	using Utility::exceptionx;

	CTCPClient::CTCPClient(const string& strIP, unsigned short usPort, unsigned int uiBufSize) :
		m_pBuf(NULL),
		m_uiBufSize(uiBufSize)
	{
		this->m_sock = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (INVALID_SOCKET == this->m_sock)
		{
			throw exceptionx("创建流式套接字失败");
		}
		else
		{
			this->m_addrServer.sin_family = AF_INET;
#ifdef __OS_VERSION_WINDOWS__
			this->m_addrServer.sin_addr.S_un.S_addr = StringIPToNetUInt(strIP);
#elif __OS_VERSION_LINUX__
			this->m_addrServer.sin_addr.s_addr = StringIPToNetUInt(strIP);
#endif
			this->m_addrServer.sin_port = htons(usPort);

			if (NULL == (this->m_pBuf = new char[this->m_uiBufSize]))
			{
				throw exceptionx("开辟缓冲区失败");
			}
		}
	}

	CTCPClient::~CTCPClient(void)
	{
		::closesocket(this->m_sock);
		delete[] this->m_pBuf;
	}

	bool CTCPClient::Connect(void)
	{
		if (SOCKET_ERROR == ::connect(this->m_sock, reinterpret_cast<sockaddr*>(&this->m_addrServer), sizeof (sockaddr)))
		{
			::closesocket(this->m_sock);
			return false;
		}
		else
		{
			return true;
		}
	}

	bool CTCPClient::Send(const string& str)
	{
		if (SOCKET_ERROR == ::send(this->m_sock, str.c_str(), str.length(), 0))
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	pair<string, int> CTCPClient::Receive(void)
	{
		int iRecvLen = ::recv(this->m_sock, this->m_pBuf, this->m_uiBufSize, 0);

		if (SOCKET_ERROR == iRecvLen)
		{
			iRecvLen = 0;
			::closesocket(this->m_sock);
		}

		return make_pair(string(this->m_pBuf, iRecvLen), errno);
	}
}
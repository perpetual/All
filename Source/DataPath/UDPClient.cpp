#include "VersionControl.h"
#include "DataPath/UDPClient.h"
#include "MyTools/MyTools.h"
#include <iostream>

namespace DataPath
{
	using MyTools::StringIPToNetUInt;
	using std::cerr;
	using std::endl;
	using Utility::exceptionx;

	const unsigned int MAX_UDP_BUFFER_SIZE = 63 * 1024;

	CUDPClient::CUDPClient(const string& strDstIP, unsigned short usPort)
	{
		this->m_sock = ::socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		if (INVALID_SOCKET == this->m_sock)
		{
			throw exceptionx("�������ݱ��׽���ʧ��");
		}
		else
		{
			this->m_addrServer.sin_family = AF_INET;
#ifdef __OS_VERSION_WINDOWS__
			this->m_addrServer.sin_addr.S_un.S_addr = StringIPToNetUInt(strDstIP);
#elif defined (__OS_VERSION_LINUX__)
			this->m_addrServer.sin_addr.s_addr = StringIPToNetUInt(strDstIP);
#endif
			this->m_addrServer.sin_port = htons(usPort);
		}
	}

	CUDPClient::~CUDPClient(void)
	{
		::closesocket(this->m_sock);
	}

	bool CUDPClient::Send(const string& str)
	{
		if (str.length() > MAX_UDP_BUFFER_SIZE)
		{
			cerr << "�������ݹ���" << endl;
			return false;
		}

		return SOCKET_ERROR != ::sendto(this->m_sock, str.c_str(), str.length(), 0, reinterpret_cast<sockaddr*>(&this->m_addrServer), sizeof (sockaddr));
	}
}
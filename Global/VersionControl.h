//控制版本的预编译头

#if (!defined(__OS_VERSION_WINDOWS__) && !defined(__OS_VERSION_LINUX__)) || (defined(__OS_VERSION_WINDOWS__) && defined(__OS_VERSION_LINUX__))
#error "UNKNOWN OS"
#endif

#ifndef __OS_VERSION__
#define __OS_VERSION__

#include <iostream>

using std::cout;
using std::endl;
using std::ends;

#ifdef __OS_VERSION_WINDOWS__
#include <WinSock2.h>
#include <Windows.h>
#include <WS2tcpip.h>
#include <IPHlpApi.h>
#include <sddl.h>
#include <io.h>
#include <MSTcpIP.h>
#include <winternl.h>

#ifdef _USRDLL
#define MY_DLL __declspec(dllexport)
#else
#define MY_DLL __declspec(dllimport)
#endif

#elif defined(__OS_VERSION_LINUX__)
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <net/if_arp.h>

#define SOCKET_ERROR (-1)
#define INVALID_SOCKET (-1)
#define closesocket close
#define SOCKADDR_IN sockaddr_in
#define SOCKADDR sockaddr

typedef int SOCKET;
typedef int BOOL;
#endif


#ifndef __UTILITY__
#define __UTILITY__

#include <exception>
#include <string>

namespace Utility
{
	using std::string;

	class exceptionx : public std::exception
	{
	public:
		exceptionx(const string& str) throw() : m_str(str)
		{}
		virtual const char* what() const throw()
		{
			return this->m_str.c_str();
		}
		~exceptionx(void) throw() {}
	private:
		string m_str;
	};
}
#endif

#endif
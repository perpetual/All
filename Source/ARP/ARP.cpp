#include "ARP/ARP.h"
#include "MyTools/MyNetTools.h"

namespace ARP
{
	sockaddr_in FillSockAddr(const string& strIP, unsigned short usPort)
	{
		sockaddr_in addrSock;

		addrSock.sin_family = AF_INET;

#ifdef __OS_VERSION_WINDOWS__
		addrSock.sin_addr.S_un.S_addr = MyTools::StringIPToNetUInt(strIP);
#elif defined(__OS_VERSION_LINUX__)
		addrSock.sin_addr.s_addr = StringIPToNetUInt(strIP);
#endif
		addrSock.sin_port = htons(usPort);

		return addrSock;
	}
}
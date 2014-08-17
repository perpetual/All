#include "VersionControl.h"
#include <cstring>
#include <cstdio>
#include <MyTools/MySocketTools.h>
#include <MyTools/MyNetTools.h>


namespace MyTools
{
	bool SetSocketOutTime(SOCKET sock, unsigned int uiOutTime)
	{
		return 0 == ::setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<char*> (&uiOutTime), sizeof (unsigned int));
	}

	bool SetSocketTTL(SOCKET sock, unsigned int uiTTL)
	{
		return 0 == ::setsockopt(sock, IPPROTO_IP, IP_TTL, reinterpret_cast<char*> (&uiTTL), sizeof (int));
	}

	bool SetMulticastSocketTTL(SOCKET sock, unsigned int uiTTL)
	{
		return 0 == ::setsockopt(sock, IPPROTO_IP, IP_MULTICAST_TTL, reinterpret_cast<char*> (&uiTTL), sizeof (int));
	}

	pair<string, unsigned short> GetSocketInfo(SOCKET sock)
	{
		sockaddr_in sockAddr;
		pair<string, unsigned short> pairRet;
#ifdef __OS_VERSION_WINDOWS__
		int len = sizeof (sockaddr);
#elif defined(__OS_VERSION_LINUX__)
                socklen_t len = sizeof (sockaddr);
#endif

		if (SOCKET_ERROR != ::getsockname(sock, reinterpret_cast<sockaddr*>(&sockAddr), &len))
		{
#ifdef __OS_VERSION_WINDOWS__
			pairRet.first = NetUIntToStringIP(sockAddr.sin_addr.S_un.S_addr);
#elif defined(__OS_VERSION_LINUX__)
			pairRet.first = NetUIntToStringIP(sockAddr.sin_addr.s_addr);
#endif
			pairRet.second = ntohs(sockAddr.sin_port);
		}
		return pairRet;
	}

	bool SetSocketNonBlock(SOCKET sock, BOOL b)
	{
		unsigned long ul = b;
#ifdef __OS_VERSION_WINDOWS__
		return 0 == ::ioctlsocket(sock, FIONBIO, &ul);
#elif defined(__OS_VERSION_LINUX__)
                return 0 == ::ioctl(sock, FIONBIO, &ul);
#endif
	}

	bool SetSocketBroadcast(SOCKET sock, BOOL b)
	{
		return 0 == ::setsockopt(sock, SOL_SOCKET, SO_BROADCAST, reinterpret_cast<char*>(&b), sizeof (BOOL));
	}

	bool SetSocketReuse(SOCKET sock, BOOL b)
	{
		return 0 == ::setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<char*>(&b), sizeof (BOOL));
	}

	bool SetSocketMulticast(SOCKET sock, const string& strMultiAddr, const string& strInterface, BOOL b)
	{
		ip_mreq mcast;

#ifdef __OS_VERSION_WINDOWS__
		mcast.imr_multiaddr.S_un.S_addr = StringIPToNetUInt(strMultiAddr);
		mcast.imr_interface.S_un.S_addr = StringIPToNetUInt(strInterface);
#elif __OS_VERSION_LINUX__
		mcast.imr_multiaddr.s_addr = StringIPToNetUInt(strMultiAddr);
		mcast.imr_interface.s_addr = StringIPToNetUInt(strInterface);
#endif
		if (b)
		{
			return 0 == ::setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, reinterpret_cast<char*>(&mcast), sizeof (ip_mreq));
		}
		else
		{
			return 0 == ::setsockopt(sock, IPPROTO_IP, IP_DROP_MEMBERSHIP, reinterpret_cast<char*>(&mcast), sizeof (ip_mreq));
		}
	}

	bool SetRawSocketIPHeader(SOCKET sock, BOOL b)
	{
		return 0 == ::setsockopt(sock, IPPROTO_IP, IP_HDRINCL, reinterpret_cast<char*>(&b), sizeof (BOOL));
	}

#ifdef __OS_VERSION_WINDOWS__
	bool SetRawSocketReceiveAll(SOCKET sock, BOOL b)
#elif defined(__OS_VERSION_LINUX__)
	bool SetRawSocketReceiveAll(SOCKET sock, const string& strName, BOOL b)
#endif
	{
#ifdef __OS_VERSION_WINDOWS__
		unsigned long ul = b;
		return 0 == ::ioctlsocket(sock, SIO_RCVALL, &ul);
#elif defined(__OS_VERSION_LINUX__)
		ifreq ifr;
		strncpy(ifr.ifr_ifrn.ifrn_name, strName.c_str(), strName.length() + 1);
		if (b)
		{
			ifr.ifr_ifru.ifru_flags |= IFF_PROMISC;
		}
		else
		{
			ifr.ifr_ifru.ifru_flags &= ~IFF_PROMISC;
		}
        return 0 == ::ioctl(sock, SIOCGIFFLAGS, &ifr);
#endif
	}
}
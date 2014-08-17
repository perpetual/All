#ifndef DATAPATH_UDP_CLIENT_H
#define DATAPATH_UDP_CLIENT_H

#include "DataPath/DataPath.h"
#include <string>

namespace DataPath
{
	using std::string;

	class CUDPClient : public CDataPath
	{
	public:
		//第一个参数是目标IP地址
		//下一个参数是目标端口
		CUDPClient(const string&, unsigned short);
		~CUDPClient(void);

		bool Send(const string&);

	private:
		sockaddr_in m_addrServer;
	};
}

#endif
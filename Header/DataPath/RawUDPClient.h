#ifndef DATAPATH_RAW_UDP_CLIENT_H
#define DATAPATH_RAW_UDP_CLIENT_H

#include "DataPath.h"
#include "NetWorkProtocol/NetWorkProtocol.h"

namespace DataPath
{
	using NetProtocol::TIPHeader;
	using NetProtocol::TUDPHeader;

	class CRawUDPClient : public CDataPath
	{
	public:
		//第一个参数为目标IP地址
		//下一个参数为目的端口号
		//下一个参数为源端口号
		CRawUDPClient(const string&, unsigned short, unsigned short = 55667);
		~CRawUDPClient(void);

		//发送数据
		bool Send(const string&);
	private:
		TIPHeader m_tIPHeader;
		TUDPHeader m_tUDPHeader;
		sockaddr_in m_addrSock;
		unsigned short m_usID;
	};
}

#endif
#ifndef DATAPATH_RAW_TCP_CLIENT_H
#define DATAPATH_RAW_TCP_CLIENT_H

#include "VersionControl.h"
#include "DataPath.h"
#include "NetworkProtocol/NetworkProtocol.h"

namespace DataPath
{
	using NetProtocol::TIPHeader;
	using NetProtocol::TTCPHeader;

	class CRawTCPClient : public CDataPath
	{
	public:
		//第一个参数为目标IP地址
		//下一个参数为目的端口号
		//下一个参数为源端口号
		CRawTCPClient(const string&, unsigned short, unsigned short = 55667);
		~CRawTCPClient(void);

		//发送数据
		bool Send(const string&);
	private:
		TIPHeader m_tIPHeader;
		TTCPHeader m_tUDPHeader;
		sockaddr_in m_addrSock;
		unsigned short m_usID;
		unsigned int m_uiSeq;
	};
}

#endif
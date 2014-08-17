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
		//��һ������ΪĿ��IP��ַ
		//��һ������ΪĿ�Ķ˿ں�
		//��һ������ΪԴ�˿ں�
		CRawUDPClient(const string&, unsigned short, unsigned short = 55667);
		~CRawUDPClient(void);

		//��������
		bool Send(const string&);
	private:
		TIPHeader m_tIPHeader;
		TUDPHeader m_tUDPHeader;
		sockaddr_in m_addrSock;
		unsigned short m_usID;
	};
}

#endif
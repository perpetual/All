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
		//��һ������ΪĿ��IP��ַ
		//��һ������ΪĿ�Ķ˿ں�
		//��һ������ΪԴ�˿ں�
		CRawTCPClient(const string&, unsigned short, unsigned short = 55667);
		~CRawTCPClient(void);

		//��������
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
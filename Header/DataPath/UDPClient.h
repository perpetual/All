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
		//��һ��������Ŀ��IP��ַ
		//��һ��������Ŀ��˿�
		CUDPClient(const string&, unsigned short);
		~CUDPClient(void);

		bool Send(const string&);

	private:
		sockaddr_in m_addrServer;
	};
}

#endif
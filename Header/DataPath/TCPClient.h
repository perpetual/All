#ifndef DATAPATH_TCP_CLIENT_H
#define DATAPATH_TCP_CLIENT_H

#include "DataPath.h"
#include <string>
#include <utility>

namespace DataPath
{
	using std::string;
	using std::pair;
	using std::make_pair;

	class CTCPClient : public CDataPath
	{
	public:
		//��һ��������Ŀ��IP��ַ
		//��һ��������Ŀ��˿�
		//�����������ǻ������Ĵ�С
		CTCPClient(const string&, unsigned short, unsigned int = 1024);
		~CTCPClient(void);

		//����
		bool Connect(void);

		bool Send(const string&);

		//����ֵ��secondΪ������
		pair<string, int> Receive(void);
	private:
		char* m_pBuf;
		unsigned int m_uiBufSize;
		sockaddr_in m_addrServer;
	};
}
#endif
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
		//第一个参数是目标IP地址
		//下一个参数是目标端口
		//第三个参数是缓冲区的大小
		CTCPClient(const string&, unsigned short, unsigned int = 1024);
		~CTCPClient(void);

		//连接
		bool Connect(void);

		bool Send(const string&);

		//返回值的second为错误码
		pair<string, int> Receive(void);
	private:
		char* m_pBuf;
		unsigned int m_uiBufSize;
		sockaddr_in m_addrServer;
	};
}
#endif
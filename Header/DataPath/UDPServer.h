#ifndef DATAPATH_UDP_SERVER_H
#define DATAPATH_UDP_SERVER_H

#include "DataPath.h"
#include <string>

namespace DataPath
{
	using std::string;

	class CUDPServer : public CDataPath
	{
	public:
		//第一个参数是主机监听的端口号
		//下一个参数是绑定的IP地址
		//下一个参数是接收缓冲区的长度
		CUDPServer(unsigned short, const string& = "0.0.0.0", unsigned int = 1024);
		~CUDPServer(void);

		//返回值表示接收到的字符串
		string Receive(void);

		//获取客户端IP地址
		string GetClientAddress(void) const;

		//获取客户端口
		unsigned short GetClientPort(void) const;

	private:
		char* m_pRecvBuf;							//接收缓冲区
		const unsigned int m_uiRecvBufSize;	//缓冲区长度
		sockaddr_in m_addrClient;			//客户端的地址
	};
}

#endif
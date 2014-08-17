#ifndef MYTOOLS_SELECT_TCP_SERVER_H
#define MYTOOLS_SELECT_TCP_SERVER_H

#include "VersionControl.h"
#include "DataPath.h"
#include <string>

namespace DataPath
{
	using std::string;
	using DataPath::CDataPath;

	class CSelectTCPServer : public CDataPath
	{
	public:
		//第一个参数是主机监听的端口号
		//下一个参数是监听地址
		//下一个参数是接收缓冲区的长度
		CSelectTCPServer(unsigned short, const string& = "0.0.0.0", unsigned int = 1024);
		~CSelectTCPServer(void);

	private:
		char* m_pRecvBuf;
		unsigned int m_uiRecvBufSize;
	};
}

#endif
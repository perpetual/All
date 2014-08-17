#ifndef DATAPATH_TCP_SERVER_H
#define DATAPATH_TCP_SERVER_H

#include "DataPath.h"
#include "MyTools/MySocketTools.h"
#include <utility>
#include <map>
#include <string>

namespace DataPath
{
	using std::pair;
	using std::make_pair;
	using std::map;
	using std::string;
	using MyTools::GetSocketInfo;

	class CTCPServer : public CDataPath
	{
	public:
		//用于与客户端通信的套接字
		class CTCPClientSocket
		{
			friend class CTCPServer;
		public:
			CTCPClientSocket(void);
			~CTCPClientSocket(void);

			operator bool(void) const;

			//获取客户端IP地址
			string GetClientAddress(void) const;

			//获取客户端口
			unsigned short GetClientPort(void) const;

			//关闭套接字
			void CloseSocket(void);

		private:
			//禁止复制和赋值
			CTCPClientSocket(CTCPClientSocket&);
			CTCPClientSocket& operator =(CTCPClientSocket&);
			SOCKET m_sockClient;
			sockaddr_in m_addrClient;
			char* m_pRecvBuf;			//接收缓冲区
			unsigned int m_uiRecvBufSize;		//接收缓冲区的长度
		};
		//第一个参数是主机监听的端口号
		//下一个参数是监听地址
		//下一个参数是接收缓冲区的长度
		CTCPServer(unsigned short, const string& = "0.0.0.0", unsigned int = 1024);
		~CTCPServer(void);

		//获取监听套接字绑定的地址
		string GetBindAddress(void) const
		{
			return GetSocketInfo(this->m_sock).first;
		}

		//获取监听套接字绑定的端口
		unsigned short GetBindPort(void) const
		{
			return GetSocketInfo(this->m_sock).second;
		}

		//接收客户端连接
		bool Accept(CTCPClientSocket& oTCPClientSocket);

		//接收数据
		//返回值的first是接收到的字符串
		static pair<string, int> Receive(CTCPClientSocket&);

		//发送数据
		//第一个参数是套接字对象
		//第二个参数是需要发送的数据
		bool Send(CTCPClientSocket&, const string&);

	private:
		sockaddr_in m_addrListen;
		const unsigned int m_uiRecvBufSize;	//缓冲区长度
		bool m_bInit;									//是否初始化
	};
}

#endif
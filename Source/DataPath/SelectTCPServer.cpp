#include "VersionControl.h"
#include "DataPath/SelectTCPServer.h"
#include "MyTools/MyUtilityTools.h"
#include "MyTools/MySocketTools.h"
#include <iostream>

namespace DataPath
{
	using MyTools::StringIPToNetUInt;
	using MyTools::Trim;
	using MyTools::GetSocketInfo;
	using std::cout;
	using std::endl;
	using std::cerr;
	using Utility::exceptionx;

	CSelectTCPServer::CSelectTCPServer(unsigned short usPort, const string& strIP, unsigned int uiRecvBufSize) :
		m_pRecvBuf(NULL),
		m_uiRecvBufSize(uiRecvBufSize)
	{
		if (0 == this->m_uiRecvBufSize)
		{
			throw exceptionx("接收缓冲区长度非法");
		}

		this->m_sock = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (INVALID_SOCKET == this->m_sock)
		{
			throw exceptionx("创建流式套接字失败");
		}
		else
		{
			sockaddr_in addrListen;
			addrListen.sin_family = AF_INET;
#ifdef __OS_VERSION_WINDOWS__
			addrListen.sin_addr.S_un.S_addr = StringIPToNetUInt(Trim(strIP));
#elif defined (__OS_VERSION_LINUX__)
			addrListen.sin_addr.s_addr = StringIPToNetUInt(Trim(strIP));
#endif
			addrListen.sin_port = htons(usPort);
			if (SOCKET_ERROR == ::bind(this->m_sock, reinterpret_cast<sockaddr*>(&addrListen), sizeof (sockaddr)))
			{
				::closesocket(this->m_sock);
				throw exceptionx("套接字绑定失败");
			}
			else
			{
				if (SOCKET_ERROR == ::listen(this->m_sock, SOMAXCONN))
				{
					::closesocket(this->m_sock);
					throw exceptionx("套接字监听失败");
				}
				else
				{
					fd_set fdSockets;			//可用套接字集合
					FD_ZERO(&fdSockets);
					FD_SET(this->m_sock, &fdSockets);		//将监听套接字放入集合

					this->m_pRecvBuf = new char[this->m_uiRecvBufSize];
#ifdef __OS_VERSION_WINDOWS__
					while (true)
					{
						fd_set fdRead = fdSockets;
						int iRet = ::select(0, &fdRead, NULL, NULL, NULL);
						if (iRet > 0)
						{
							//检查集合中是否有可读套接字
							for (unsigned int u = 0; u < fdSockets.fd_count; ++u)
							{
								if (FD_ISSET(fdSockets.fd_array[u], &fdRead))			//如果有可读套接字
								{
									if (fdSockets.fd_array[u] == this->m_sock)			//如果是监听套接字可读
									{
										SOCKADDR_IN addrSock;
										int iLen = sizeof (SOCKADDR);
										SOCKET sockNew = ::accept(this->m_sock, reinterpret_cast<SOCKADDR*>(&addrSock), &iLen);
										if (SOCKET_ERROR == sockNew)
										{
											cerr << "接受新的连接错误" << endl;
										}
										else
										{
											FD_SET(sockNew, &fdSockets);			//将新连接的套接字添加到集合
											cout << "接受来自" << GetSocketInfo(sockNew).first << "的连接" << endl;
										}
									}
									else
									{
										int iRecvLen = ::recv(fdSockets.fd_array[u], this->m_pRecvBuf, this->m_uiRecvBufSize, 0);
										if (SOCKET_ERROR == iRecvLen || 0 == iRecvLen)
										{
											if (SOCKET_ERROR == iRecvLen)
											{
												cout << "接收来自" << GetSocketInfo(fdSockets.fd_array[u]).first << "的数据失败" << ::WSAGetLastError() << endl;
											}
											::closesocket(fdSockets.fd_array[u]);
											FD_CLR(fdSockets.fd_array[u], &fdSockets);
										}
										else
										{
											cout << "接收来自" << GetSocketInfo(fdSockets.fd_array[u]).first << "的数据：" << string(this->m_pRecvBuf, iRecvLen) << endl;
										}
									}
								}
							}
						}
						else if (0 == iRet)
						{
							cout << "超时" << endl;
						}
						else
						{
							cerr << "select出错" << endl;
							break;
						}
					}
#endif
				}
			}
		}
	}

	CSelectTCPServer::~CSelectTCPServer(void)
	{
		delete this->m_pRecvBuf;
		::closesocket(this->m_sock);
		this->m_sock = INVALID_SOCKET;
	}
}
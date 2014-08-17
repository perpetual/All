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
			throw exceptionx("���ջ��������ȷǷ�");
		}

		this->m_sock = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (INVALID_SOCKET == this->m_sock)
		{
			throw exceptionx("������ʽ�׽���ʧ��");
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
				throw exceptionx("�׽��ְ�ʧ��");
			}
			else
			{
				if (SOCKET_ERROR == ::listen(this->m_sock, SOMAXCONN))
				{
					::closesocket(this->m_sock);
					throw exceptionx("�׽��ּ���ʧ��");
				}
				else
				{
					fd_set fdSockets;			//�����׽��ּ���
					FD_ZERO(&fdSockets);
					FD_SET(this->m_sock, &fdSockets);		//�������׽��ַ��뼯��

					this->m_pRecvBuf = new char[this->m_uiRecvBufSize];
#ifdef __OS_VERSION_WINDOWS__
					while (true)
					{
						fd_set fdRead = fdSockets;
						int iRet = ::select(0, &fdRead, NULL, NULL, NULL);
						if (iRet > 0)
						{
							//��鼯�����Ƿ��пɶ��׽���
							for (unsigned int u = 0; u < fdSockets.fd_count; ++u)
							{
								if (FD_ISSET(fdSockets.fd_array[u], &fdRead))			//����пɶ��׽���
								{
									if (fdSockets.fd_array[u] == this->m_sock)			//����Ǽ����׽��ֿɶ�
									{
										SOCKADDR_IN addrSock;
										int iLen = sizeof (SOCKADDR);
										SOCKET sockNew = ::accept(this->m_sock, reinterpret_cast<SOCKADDR*>(&addrSock), &iLen);
										if (SOCKET_ERROR == sockNew)
										{
											cerr << "�����µ����Ӵ���" << endl;
										}
										else
										{
											FD_SET(sockNew, &fdSockets);			//�������ӵ��׽�����ӵ�����
											cout << "��������" << GetSocketInfo(sockNew).first << "������" << endl;
										}
									}
									else
									{
										int iRecvLen = ::recv(fdSockets.fd_array[u], this->m_pRecvBuf, this->m_uiRecvBufSize, 0);
										if (SOCKET_ERROR == iRecvLen || 0 == iRecvLen)
										{
											if (SOCKET_ERROR == iRecvLen)
											{
												cout << "��������" << GetSocketInfo(fdSockets.fd_array[u]).first << "������ʧ��" << ::WSAGetLastError() << endl;
											}
											::closesocket(fdSockets.fd_array[u]);
											FD_CLR(fdSockets.fd_array[u], &fdSockets);
										}
										else
										{
											cout << "��������" << GetSocketInfo(fdSockets.fd_array[u]).first << "�����ݣ�" << string(this->m_pRecvBuf, iRecvLen) << endl;
										}
									}
								}
							}
						}
						else if (0 == iRet)
						{
							cout << "��ʱ" << endl;
						}
						else
						{
							cerr << "select����" << endl;
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
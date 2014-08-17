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
		//��һ�����������������Ķ˿ں�
		//��һ�������ǰ󶨵�IP��ַ
		//��һ�������ǽ��ջ������ĳ���
		CUDPServer(unsigned short, const string& = "0.0.0.0", unsigned int = 1024);
		~CUDPServer(void);

		//����ֵ��ʾ���յ����ַ���
		string Receive(void);

		//��ȡ�ͻ���IP��ַ
		string GetClientAddress(void) const;

		//��ȡ�ͻ��˿�
		unsigned short GetClientPort(void) const;

	private:
		char* m_pRecvBuf;							//���ջ�����
		const unsigned int m_uiRecvBufSize;	//����������
		sockaddr_in m_addrClient;			//�ͻ��˵ĵ�ַ
	};
}

#endif
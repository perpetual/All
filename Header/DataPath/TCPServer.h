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
		//������ͻ���ͨ�ŵ��׽���
		class CTCPClientSocket
		{
			friend class CTCPServer;
		public:
			CTCPClientSocket(void);
			~CTCPClientSocket(void);

			operator bool(void) const;

			//��ȡ�ͻ���IP��ַ
			string GetClientAddress(void) const;

			//��ȡ�ͻ��˿�
			unsigned short GetClientPort(void) const;

			//�ر��׽���
			void CloseSocket(void);

		private:
			//��ֹ���ƺ͸�ֵ
			CTCPClientSocket(CTCPClientSocket&);
			CTCPClientSocket& operator =(CTCPClientSocket&);
			SOCKET m_sockClient;
			sockaddr_in m_addrClient;
			char* m_pRecvBuf;			//���ջ�����
			unsigned int m_uiRecvBufSize;		//���ջ������ĳ���
		};
		//��һ�����������������Ķ˿ں�
		//��һ�������Ǽ�����ַ
		//��һ�������ǽ��ջ������ĳ���
		CTCPServer(unsigned short, const string& = "0.0.0.0", unsigned int = 1024);
		~CTCPServer(void);

		//��ȡ�����׽��ְ󶨵ĵ�ַ
		string GetBindAddress(void) const
		{
			return GetSocketInfo(this->m_sock).first;
		}

		//��ȡ�����׽��ְ󶨵Ķ˿�
		unsigned short GetBindPort(void) const
		{
			return GetSocketInfo(this->m_sock).second;
		}

		//���տͻ�������
		bool Accept(CTCPClientSocket& oTCPClientSocket);

		//��������
		//����ֵ��first�ǽ��յ����ַ���
		static pair<string, int> Receive(CTCPClientSocket&);

		//��������
		//��һ���������׽��ֶ���
		//�ڶ�����������Ҫ���͵�����
		bool Send(CTCPClientSocket&, const string&);

	private:
		sockaddr_in m_addrListen;
		const unsigned int m_uiRecvBufSize;	//����������
		bool m_bInit;									//�Ƿ��ʼ��
	};
}

#endif
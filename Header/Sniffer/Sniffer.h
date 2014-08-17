#ifndef SNIFFER_SNIFFER_H
#define SNIFFER_SNIFFER_H

#include "VersionControl.h"
#include <string>
#include <set>
#include "MyTools/MyNetTools.h"

namespace Sniffer
{
	using std::string;
	using std::set;
	using MyTools::CInitSocketLibrary;

	//������̽��
	class CSniffer : public CInitSocketLibrary
	{
	public:
		//��һ��������ʾ�Ƿ�����Ϊ����ģʽ
		//��һ������Ϊ����������
#ifdef __OS_VERSION_WINDOWS__
		CSniffer(bool = true, unsigned int = 65536);
#elif defined (__OS_VERSION_LINUX__)
		//��һ������Ϊ����������
		CSniffer(const string& = "eth0", bool = true, unsigned int = 65536);
#endif
		~CSniffer(void);

		//��������
		void Start(void) const;

		//���ԴIP��ַ
		void AddSourceIP(const string&);

		//ɾ��ԴIP��ַ
		void RemoveSourceIP(const string&);

		//���Ŀ��IP��ַ
		void AddDestinationIP(const string&);

		//ɾ��ԴIP��ַ
		void RemoveDestinationIP(const string&);

		//���Դ�˿�
		void AddSourcePort(unsigned short);

		//ɾ��Դ�˿�
		void RemoveSourcePort(unsigned short);

		//���Ŀ�Ķ˿�
		void AddDestinationPort(unsigned short);

		//ɾ��Ŀ�Ķ˿�
		void RemoveDestinationPort(unsigned short);

		//���Э��
		void AddProtocol(unsigned char);

		//ɾ��Э��
		void RemoveProtocol(unsigned char);

	private:
		//��ֹ���ƺ͸�ֵ
		CSniffer(const CSniffer&);
		CSniffer& operator =(const CSniffer&);

		//�ж�Դ��Ŀ�Ķ˿��Ƿ���Ҫ����
		//��һ��������Դ�˿�
		//�ڶ���������Ŀ�Ķ˿�
		bool HasPort(unsigned short, unsigned short) const;

		SOCKET m_sock;
		char* m_pBuf;					//������ָ��
		const unsigned int m_uiBufLen;			//����������

		set<unsigned int> m_setSrcIP;			//Դip��ַ
		set<unsigned int> m_setDstIP;			//Ŀ��ip��ַ
		set<unsigned short> m_setSrcPort;	//Դ�˿�
		set<unsigned short> m_setDstPort;	//Ŀ�Ķ˿�
		set<unsigned char> m_setProtocol;	//Э��
	};
}

#endif
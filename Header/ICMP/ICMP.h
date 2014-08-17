#ifndef ICMP_ICMP_H
#define ICMP_ICMP_H

#include "VersionControl.h"
#include <iostream> 
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <utility>
#include "NetworkProtocol/NetworkProtocol.h"
#include "MyTools/MyNetTools.h"

namespace ICMP
{
	using std::string;
	using std::vector;
	using std::pair;
	using NetProtocol::TICMPHeader;
	using NetProtocol::TIPHeader;
	using MyTools::CInitSocketLibrary;

	//��ʾICMPͷ����
	void DisplayICMPHeader(const TICMPHeader&);

	//��ʾIPͷ����
	void DisplayIPHeader(const TIPHeader&);

	class CICMP : public CInitSocketLibrary
	{
	public:
		enum EEchoType
		{
			ECHO_ERROR,		//����
			ECHO_UNREACHABLE,	//���ɴ�
			ECHO_FINISH		//����
		};

	protected:
		//����Ϊ��ʱʱ��
		CICMP(unsigned int uiOutTime);
		~CICMP(void);

		//����̽���
		//��һ������Ŀ��IP��ַ����������
		//�ڶ���������TTLֵ��0��ʾʹ��Ĭ��TTLֵ
		//����IP��ַ���ձ�ʾ̽��ʧ��
		string Probe(const string&, unsigned int = 0);

		//��׽̽����Ӧ��
		//�����ǳ�ʱʱ�䣨ms����0��ʾ����ʱ
		//�����Ǵ�������
		//����ֵ��ʾ����ֵ����
		EEchoType Catch(TIPHeader&, TICMPHeader&) ;

		unsigned int m_uiSeq;				//���
		unsigned int m_uiOutTime;		//��ʱʱ�䣨ms��

	private:
		//��ֹ�����븳ֵ
		CICMP(const CICMP&);
		CICMP& operator =(const CICMP&);

		SOCKET m_sockSend;				//�����׽���
		SOCKET m_sockRecv;				//�����׽���
	};
}

#endif
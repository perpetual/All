#ifndef PING_H
#define PING_H

#include <string>
#include "ICMP.h"

namespace ICMP
{
	using std::string;
	using NetProtocol::TIPHeader;
	using NetProtocol::TICMPHeader;
	using ICMP::CICMP;

	extern const unsigned int BUF_LEN;
	extern const unsigned int DEFAULT_OUTTIME;

	typedef struct
	{
		unsigned char Ttl;								//TTL
		unsigned char Tos;							//��������
		unsigned char Flags;							//IPͷ���
		unsigned char OptionsSize;				//��ѡ���ݴ�С
		unsigned char *OptionsData;				//ָ���ѡ���ݵ�ָ��
	} IP_OPTION_INFORMATION, * PIP_OPTION_INFORMATION;

	typedef struct
	{
		DWORD Address;										// Ӧ���ַ
		unsigned long  Status;								 //Ӧ��״̬
		unsigned long  RoundTripTime;					//����ʱ��
		unsigned short DataSize;							//Ӧ�����ݴ�С
		unsigned short Reserved;							//����λ
		void *Data;												//ָ��Ӧ�����ݵ�ָ��
		IP_OPTION_INFORMATION Options;			//Ӧ��ѡ��
	} IP_ECHO_REPLY, * PIP_ECHO_REPLY;

	// ������������ָ������
	typedef HANDLE (WINAPI* pfnHV)(VOID);
	typedef BOOL (WINAPI* pfnBH)(HANDLE);
	typedef DWORD (WINAPI* pfnDHDPWPipPDD)(HANDLE, DWORD, LPVOID, WORD, PIP_OPTION_INFORMATION, LPVOID, DWORD, DWORD);

	class CPing : public CICMP
	{
	public:
		//����Ϊ��ʱʱ��
		CPing(unsigned int = 5000);

		//����Ping��
		//��һ��������Ŀ��IP��ַ��������
		//�ڶ�������ΪTTLֵ��0��ʾ������TTLֵ
		CICMP::EEchoType Ping(const string&, unsigned int = 0);
		CICMP::EEchoType PingEx(const string&, unsigned int = 0);

		//���ó�ʱʱ�䣨ms��
		void SetSocketOutTime(unsigned int uiOutTime)
		{
			this->m_uiOutTime = uiOutTime;
		}

		//��ȡ���
		unsigned int GetSeqNO(void)
		{
			return this->m_tICMPHeader.m_usICMPSeq;
		}

		//��ȡԴIP
		string GetSourceIP(void) const
		{
			return inet_ntoa(*reinterpret_cast<const in_addr*>(&this->m_tIPHeader.m_uiDstIP));
		}

		//��ȡĿ��IP
		string GetDestIP(void) const
		{
			return inet_ntoa(*reinterpret_cast<const in_addr*>(&this->m_tIPHeader.m_uiSrcIP));
		}

		//��ȡTTL
		unsigned short GetTTL(void) const
		{
			return this->m_tIPHeader.m_ucTTL;
		}

		//��ȡʱ���
		unsigned int GetTimestamp(void) const
		{
			return this->m_tICMPHeader.m_uiICMPTimestamp;
		}

		//��ȡ�ӳ�(����)
		unsigned short GetDelay(void) const
		{
			return this->m_usDelay;
		}

	private:
		TIPHeader m_tIPHeader;					//IPͷ
		TICMPHeader m_tICMPHeader;			//ICMPͷ
		unsigned short m_usDelay;						//�ӳ٣�ms��
		HINSTANCE m_hICMP;						//ICMP��̬����
		PIP_ECHO_REPLY m_pEchoBuf;			//Ӧ�𻺳���ָ��

		//��������ָ�뺯��
		pfnHV m_pIcmpCreateFile;
		pfnBH m_pIcmpCloseHandle;
		pfnDHDPWPipPDD m_pIcmpSendEcho;
		HANDLE m_hPing;									//Ping����
	};
}

#endif
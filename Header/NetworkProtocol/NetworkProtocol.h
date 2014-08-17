#ifndef NETPROTOCOL_NET_PROTOCOL_H
#define NETPROTOCOL_NET_PROTOCOL_H

#include "VersionControl.h"
#include <string>
#include <cstring>

//�������л�ȡ�ĸ���ͷҪת���ֽ��������ȷ��ʾ
namespace NetProtocol
{
	using std::string;

	//��̫֡ͷ
	struct TEtherHeader
	{
		TEtherHeader(void)
		{
			memset(this->m_ucDst, 0, sizeof (this->m_ucDst));
			memset(this->m_ucSrc, 0, sizeof (this->m_ucSrc));
			this->m_usType = 0;
		}

		void Display(void) const;
		unsigned char m_ucDst[6];
		unsigned char m_ucSrc[6];
		unsigned short m_usType;
	};

	//IPͷ
	struct TIPHeader
	{
		TIPHeader() :
			m_ucVersion(0),
			m_ucHeaderLen(0),
			m_ucService(0),
			m_usTotalSize(0),
			m_usID(0),
			m_usOffset(0),
			m_ucFlag(0),
			m_ucTTL(0),
			m_ucProtocol(0),
			m_usChkSum(0),
			m_uiSrcIP(0),
			m_uiDstIP(0)
		{}

		//��ʾIPͷ������
		void Display(void) const;

		unsigned short m_ucHeaderLen : 4;		//IPͷ����
		unsigned short m_ucVersion : 4;			//IP�汾
		unsigned short m_ucService : 8;			//���ַ���һ������¶���ʹ�ø��ֶ�
		unsigned short m_usTotalSize;				//������ܴ�С��������IP���Ĵ�С
		unsigned short m_usID;							//�����ʶ��Ψһ��ʶ���͵�ÿһ�����ݱ�
		unsigned short m_usOffset : 13;			//Ƭƫ��
		unsigned short m_ucFlag : 3;				//���
		unsigned short m_ucTTL : 8;					//����ʱ��
		unsigned short m_ucProtocol : 8;			//Э�����ͣ�������TCP��UDP��ICMP��
		unsigned short m_usChkSum;				//У���
		unsigned int m_uiSrcIP;							//ԴIP
		unsigned int m_uiDstIP;							//Ŀ��IP
	};

	//ICMPͷ
	struct TICMPHeader
	{
		TICMPHeader() :
			m_ucICMPType(0),
			m_ucICMPCode(0),
			m_usICMPChkSum(0),
			m_usICMPID(0),
			m_usICMPSeq(0),
			m_uiICMPTimestamp(0)
		{}

		void Display(void) const;

		unsigned short m_ucICMPType : 8;				//��Ϣ����
		unsigned short m_ucICMPCode : 8;				//����
		unsigned short m_usICMPChkSum;			//У���

		//����ͷ
		unsigned short m_usICMPID;					//����Ψһ��ʶ�������ID�ţ�ͨ������Ϊ����ID
		unsigned short m_usICMPSeq;				//���к�
		unsigned int m_uiICMPTimestamp;			//ʱ���
	};

	//����ICMPͷУ���
	//��һ�������ǻ�����ָ��
	//�ڶ��������ǻ���������
	unsigned short CheckSum(const unsigned short*, int);

	//UDPͷ
	struct TUDPHeader
	{
		TUDPHeader(void) :
			m_usSrcPort(0),
			m_usDstPort(0),
			m_usLen(0),
			m_usChkSum(0)
		{}

		//��ʾUDPͷ������
		void Display(void) const;

		unsigned short m_usSrcPort;				//Դ�˿ں�
		unsigned short m_usDstPort;				//Ŀ�Ķ˿ں�
		unsigned short m_usLen;					//�������
		unsigned short m_usChkSum;			//У���
	};

	//UDPͷ��У���
	//��һ��������IPͷָ��
	//�ڶ���������UDPͷָ��
	//�����������Ǿ��غ�
	unsigned short UDPCheckSum(const TIPHeader&, const TUDPHeader&, const string&);

	//TCPͷ
	struct TTCPHeader
	{
		TTCPHeader(void) :
			m_usSrcPort(0),
			m_usDstPort(0),
			m_uiSeqNO(0),
			m_uiAckNO(0),
			m_ucOffset(0),
			m_ucReserved(0),
			m_ucFlag(0),
			m_usWindowSize(0),
			m_usChkSum(0),
			m_usUrgPtr(0)
		{}

		void Display(void) const;

		unsigned short m_usSrcPort;				//Դ�˿ں�
		unsigned short m_usDstPort;				//Ŀ�Ķ˿ں�
		unsigned int m_uiSeqNO;					//���к�
		unsigned int m_uiAckNO;					//ȷ�Ϻ�
		//unsigned char m_ucOffset;				//��λ�ײ����Ⱥ�
		//unsigned char m_ucFlag;				//6λ���λ
		unsigned short m_ucFlag : 6;			//���λ
		unsigned short m_ucReserved : 6;		//������
		unsigned short m_ucOffset : 4;			//����ƫ��
		unsigned short m_usWindowSize;		//���ڴ�С
		unsigned short m_usChkSum;			//У���
		unsigned short m_usUrgPtr;				//����ָ��
	};

	//�������ֵ�һ�����ֵ�ѡ��
	struct TTCPOption1
	{
		TTCPOption1(void) :
	m_uiMSS(0),
		m_ui16Sack(0),
		m_ui8NOP1(0),
		m_ui8NOP2(0)
	{}
	unsigned int m_uiMSS;
	unsigned int m_ui8NOP1 : 8;
	unsigned int m_ui8NOP2 : 8;
	unsigned int m_ui16Sack : 16;
	};

	//����TCPУ���
	//��һ��������IPͷ
	//��һ��������TCPͷ
	//��һ���������غɣ�Ҳ����TCPѡ���
	unsigned short TCPCheckSum(const TIPHeader&, const TTCPHeader&, const string&);

	//ARPЭ��ͷ
	enum
	{
		ARP_REQUEST,			//ARP����
		ARP_REPLY				//ARP��Ӧ
	};

#ifdef __OS_VERSION_WINDOWS__
	extern unsigned short ARPHRD_ETHER;
#endif

	struct TARPHeader
	{
		TARPHeader(void) :
			m_usHardAddr(ARPHRD_ETHER),
			m_usType(0),
			m_ucMACLen(6),
			m_ucIPLen(4)
		{}
		unsigned short m_usHardAddr;				//Ӳ����ַ�ռ�
		unsigned short m_usType;						//��̫������
		unsigned char m_ucMACLen;					//MAC��ַ�ĳ���
		unsigned char m_ucIPLen;						//IP��ַ�ĳ���
		unsigned short m_usOpCode;				//������
		unsigned char m_ucSrcMAC[6];				//ԴMAC��ַ
		unsigned char m_ucSrcIP[4];					//ԴIP��ַ
		unsigned char m_ucDstMAC[6];				//Ŀ��MAC��ַ
		unsigned char m_ucDstIP[4];					//Ŀ��IP��ַ
	};
}
#endif
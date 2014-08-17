#include "NetworkProtocol/NetworkProtocol.h"
#include <iostream>
#include <string>
#include <cstring>
#include <iomanip>
#include "MyTools/MyUtilityTools.h"
#include "MyTools/MyNetTools.h"

namespace NetProtocol
{
	using std::cout;
	using std::endl;
	using std::string;
	using std::hex;
	using std::dec;
	using MyTools::NetUIntToStringIP;
	using MyTools::NumberToHexString;
	using MyTools::NumberToDecString;
	using MyTools::AppendString;

#ifdef __OS_VERSION_WINDOWS__
	unsigned short ARPHRD_ETHER = 1;
#endif

	//�ָ���
	inline string SEPERATOR(const string& str = "")
	{
		return string("----------") + str + string("----------");
	}

	template<typename T>
	inline string NumberDisplay(T t)
	{
		return NumberToDecString(t) + "(0x" + NumberToHexString(t) + ")";
	}

	void TEtherHeader::Display(void) const
	{
		cout << endl << SEPERATOR("��̫֡ͷ") << endl;
		string strMacDst;
		string strMacSrc;
		for (int i = 0; i < 6; ++i)
		{
			string strTemp = NumberToHexString(this->m_ucDst[i]);
			if (strTemp.length() < 2)
			{
				strTemp = string("0") + strTemp;
			}
			strMacDst += strTemp + ':';

			strTemp = NumberToHexString(this->m_ucSrc[i]);
			if (strTemp.length() < 2)
			{
				strTemp = string("0") + strTemp;
			}
			strMacSrc += strTemp + ':';
		}
		cout << "Ŀ�������ַ��" << strMacDst.substr(0, strMacDst.length() - 1) << endl;
		cout << "Դ�����ַ��" << strMacSrc.substr(0, strMacSrc.length() - 1) << endl;
		cout << "Э�����ͣ�" << NumberDisplay(::htons(this->m_usType)) << endl;
		cout << SEPERATOR() << endl;
	}

	void TIPHeader::Display(void) const
	{
		cout << endl << SEPERATOR("IPͷ") << endl;
		cout << "�汾�ţ�" << this->m_ucVersion << endl;
		cout << "IPͷ���ȣ�" << this->m_ucHeaderLen * 4 << endl;
		cout << "�������ͣ�" << this->m_ucService << endl;
		cout << "�ܴ�С��" << ::ntohs(this->m_usTotalSize) << endl;
		cout << "��ʶ��" << NumberDisplay(::ntohs(this->m_usID)) << endl;
		TIPHeader tIPHeader;
		*reinterpret_cast<unsigned short*>(&tIPHeader.m_usID + 1) = ::ntohs(*reinterpret_cast<const unsigned short*>(&this->m_usID + 1));
		cout << "��ǣ�" << NumberDisplay(tIPHeader.m_ucFlag) << endl;
		cout << "Ƭƫ�ƣ�" << NumberDisplay(tIPHeader.m_usOffset) << endl;
		cout << "����ʱ�䣺" << this->m_ucTTL << endl;
		cout << "Э�����ͣ�" << this->m_ucProtocol << endl;
		cout << "У��ͣ�" << NumberDisplay(::ntohs(this->m_usChkSum)) << endl;
		cout << "ԴIP��ַ��" << NetUIntToStringIP(this->m_uiSrcIP) << endl;
		cout << "Ŀ��IP��ַ��" << NetUIntToStringIP(this->m_uiDstIP) << endl;
		cout << SEPERATOR() << endl;
	}

	void TICMPHeader::Display(void) const
	{
		cout << endl << SEPERATOR("ICMPͷ") << endl;
		cout << "��Ϣ���ͣ�" << this->m_ucICMPType << endl;
		cout << "��Ϣ����" << this->m_ucICMPCode << endl;
		cout << "У��ͣ�" << NumberDisplay(::ntohs(this->m_usICMPChkSum)) << endl;
		//cout << "��ʶ��" << ::ntohs(this->m_usICMPID) << endl;
		//cout << "���кţ�" << NumberDisplay(::ntohs(this->m_usICMPSeq)) << endl;
		//cout << "ʱ�����" << ::ntohl(this->m_uiICMPTimestamp) << endl;
		cout << SEPERATOR() << endl;
	}

	void TUDPHeader::Display(void) const
	{
		cout << endl << SEPERATOR("UDPͷ") << endl;
		cout << "Դ�˿ںţ�" << ::ntohs(this->m_usSrcPort) << endl;
		cout << "Ŀ�Ķ˿ںţ�" << ::ntohs(this->m_usDstPort) << endl;
		cout << "���ȣ�" << ::ntohs(this->m_usLen) << endl;
		cout << "У��ͣ�" << NumberDisplay(::ntohs(this->m_usChkSum)) << endl;
		cout << SEPERATOR() << endl;
	}

	void TTCPHeader::Display(void) const
	{
		cout << endl << SEPERATOR("TCPͷ") << endl;
		cout << "Դ�˿ںţ�" << ::ntohs(this->m_usSrcPort) << endl;
		cout << "Ŀ�Ķ˿ںţ�" << ::ntohs(this->m_usDstPort) << endl;
		cout << "���кţ�" << NumberDisplay(::ntohl(this->m_uiSeqNO)) << endl;
		cout << "ȷ�Ϻţ�" << NumberDisplay(::ntohl(this->m_uiAckNO)) << endl;
		TTCPHeader tTCPHeader;
		(*reinterpret_cast<unsigned short*>(&tTCPHeader.m_uiAckNO + 1)) = ::ntohs(*reinterpret_cast<const unsigned short*>(&this->m_uiAckNO + 1));
		cout << "���λ��" << NumberDisplay(tTCPHeader.m_ucFlag) << endl;
		cout << "�����֣�" << NumberDisplay(tTCPHeader.m_ucReserved) << endl;
		cout << "ƫ������" << NumberDisplay(tTCPHeader.m_ucOffset) << endl;
		cout << "���ڴ�С��" << ::ntohs(this->m_usWindowSize) << endl;
		cout << "У��ͣ�" << NumberDisplay(::ntohs(this->m_usChkSum)) << endl;
		cout << "����ָ�룺" << ::ntohs(this->m_usUrgPtr) << endl;
		cout << SEPERATOR() << endl;
	}

	unsigned short CheckSum(const unsigned short* buf, int iLen)
	{
		unsigned long ulChkSum = 0;

		//����������Ϊ��λ�ۼӵ�˫����
		while (iLen > 1)
		{
			ulChkSum += *buf++;
			iLen -= sizeof (unsigned short);
		}

		//���Ϊ�����������һ���ֽ���չ��˫�ֲ��ۼ�
		if (0 != iLen)
		{
			ulChkSum += *reinterpret_cast<const unsigned char*>(buf);
		}

		//��˫�ֵĸ�16λ�͵�16λ��ӣ�ȡ����õ�У���
		ulChkSum = (ulChkSum >> 16) + (ulChkSum & 0xffff);
		ulChkSum += (ulChkSum >> 16);

		return static_cast<unsigned short>(~ulChkSum);
	}

	unsigned short UDPCheckSum(const TIPHeader& tIPHeader, const TUDPHeader& tUDPHeader, const string& str)
	{
		char* p = new char[str.length() + 64];
		char* pStart = p;
		unsigned int uiCheckSumLen = 0;

		//����ԴIP��Ŀ��IP��ַ
		memcpy(p, &tIPHeader.m_uiSrcIP, sizeof (tIPHeader.m_uiSrcIP));
		p +=sizeof (tIPHeader.m_uiSrcIP);
		uiCheckSumLen += sizeof (tIPHeader.m_uiSrcIP);
		memcpy(p, &tIPHeader.m_uiDstIP, sizeof (tIPHeader.m_uiDstIP));
		p += sizeof (tIPHeader.m_uiDstIP);
		uiCheckSumLen += sizeof (tIPHeader.m_uiDstIP);

		//����8λ0
		memset(p, '\0', 1);
		p += 1;
		uiCheckSumLen += 1;

		//Э��
		unsigned char ucProtocol = tIPHeader.m_ucProtocol;
		memcpy(p, &ucProtocol, sizeof (ucProtocol));
		p += sizeof (ucProtocol);
		uiCheckSumLen += sizeof (ucProtocol);

		//UDP����
		memcpy(p, &tUDPHeader.m_usLen, sizeof (tUDPHeader.m_usLen));
		p += sizeof (tUDPHeader.m_usLen);
		uiCheckSumLen += sizeof (tUDPHeader.m_usLen);

		//UDPԴ�˿ں�
		memcpy(p, &tUDPHeader.m_usSrcPort, sizeof (tUDPHeader.m_usSrcPort));
		p += sizeof (tUDPHeader.m_usSrcPort);
		uiCheckSumLen += sizeof(tUDPHeader.m_usSrcPort);

		//UDPĿ�Ķ˿ں�
		memcpy(p, &tUDPHeader.m_usDstPort, sizeof (tUDPHeader.m_usDstPort));
		p += sizeof (tUDPHeader.m_usDstPort);
		uiCheckSumLen += sizeof (tUDPHeader.m_usDstPort);

		//����UDP����
		memcpy(p, &tUDPHeader.m_usLen, sizeof (tUDPHeader.m_usLen));
		p += sizeof (tUDPHeader.m_usLen);
		uiCheckSumLen += sizeof (tUDPHeader.m_usLen);

		//16λ��UDPУ��ͣ���Ϊ0
		memset(p, '\0', 2);
		p += 2;
		uiCheckSumLen += 2;

		//����
		memcpy(p, str.data(), str.length());
		p += str.length();
		uiCheckSumLen += str.length();

		//�����ֽڶ���
		if (1 == str.length() % 2)
		{
			memset(p, '\0', 1);
			p += 1;
			uiCheckSumLen += 1;
		}

		unsigned short usCheckSum = CheckSum(reinterpret_cast<unsigned short*>(pStart), uiCheckSumLen);

		delete[] pStart;

		return usCheckSum;
	}

	unsigned short TCPCheckSum(const TIPHeader& tIPHeader, const TTCPHeader& tTCPHeader, const string& strLoad)
	{
		string str;

		//���αTCPͷ
		AppendString(str, &tIPHeader.m_uiSrcIP, sizeof (tIPHeader.m_uiSrcIP));
		AppendString(str, &tIPHeader.m_uiDstIP, sizeof (tIPHeader.m_uiDstIP));
		AppendString(str, '\0', 1);
		unsigned char ucProtocol = tIPHeader.m_ucProtocol;
		AppendString(str, &ucProtocol, sizeof (ucProtocol));
		unsigned short usSize = ::htons(sizeof (tTCPHeader) + sizeof (TTCPOption1));
		AppendString(str, &usSize, sizeof (usSize));

		//�����ʵTCPͷ
		AppendString(str, &tTCPHeader, sizeof (tTCPHeader));
		//���TCPѡ���
		str += strLoad;

		if (0 != str.length() % 2)		//���������2�ֽڶ���
		{
			AppendString(str, '\0', 1);
		}

		return CheckSum(reinterpret_cast<const unsigned short*>(str.data()), str.length());
	}
}
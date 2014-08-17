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

	//分割线
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
		cout << endl << SEPERATOR("以太帧头") << endl;
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
		cout << "目的物理地址：" << strMacDst.substr(0, strMacDst.length() - 1) << endl;
		cout << "源物理地址：" << strMacSrc.substr(0, strMacSrc.length() - 1) << endl;
		cout << "协议类型：" << NumberDisplay(::htons(this->m_usType)) << endl;
		cout << SEPERATOR() << endl;
	}

	void TIPHeader::Display(void) const
	{
		cout << endl << SEPERATOR("IP头") << endl;
		cout << "版本号：" << this->m_ucVersion << endl;
		cout << "IP头长度：" << this->m_ucHeaderLen * 4 << endl;
		cout << "服务类型：" << this->m_ucService << endl;
		cout << "总大小：" << ::ntohs(this->m_usTotalSize) << endl;
		cout << "标识：" << NumberDisplay(::ntohs(this->m_usID)) << endl;
		TIPHeader tIPHeader;
		*reinterpret_cast<unsigned short*>(&tIPHeader.m_usID + 1) = ::ntohs(*reinterpret_cast<const unsigned short*>(&this->m_usID + 1));
		cout << "标记：" << NumberDisplay(tIPHeader.m_ucFlag) << endl;
		cout << "片偏移：" << NumberDisplay(tIPHeader.m_usOffset) << endl;
		cout << "生存时间：" << this->m_ucTTL << endl;
		cout << "协议类型：" << this->m_ucProtocol << endl;
		cout << "校验和：" << NumberDisplay(::ntohs(this->m_usChkSum)) << endl;
		cout << "源IP地址：" << NetUIntToStringIP(this->m_uiSrcIP) << endl;
		cout << "目的IP地址：" << NetUIntToStringIP(this->m_uiDstIP) << endl;
		cout << SEPERATOR() << endl;
	}

	void TICMPHeader::Display(void) const
	{
		cout << endl << SEPERATOR("ICMP头") << endl;
		cout << "消息类型：" << this->m_ucICMPType << endl;
		cout << "消息代码" << this->m_ucICMPCode << endl;
		cout << "校验和：" << NumberDisplay(::ntohs(this->m_usICMPChkSum)) << endl;
		//cout << "标识：" << ::ntohs(this->m_usICMPID) << endl;
		//cout << "序列号：" << NumberDisplay(::ntohs(this->m_usICMPSeq)) << endl;
		//cout << "时间戳：" << ::ntohl(this->m_uiICMPTimestamp) << endl;
		cout << SEPERATOR() << endl;
	}

	void TUDPHeader::Display(void) const
	{
		cout << endl << SEPERATOR("UDP头") << endl;
		cout << "源端口号：" << ::ntohs(this->m_usSrcPort) << endl;
		cout << "目的端口号：" << ::ntohs(this->m_usDstPort) << endl;
		cout << "长度：" << ::ntohs(this->m_usLen) << endl;
		cout << "校验和：" << NumberDisplay(::ntohs(this->m_usChkSum)) << endl;
		cout << SEPERATOR() << endl;
	}

	void TTCPHeader::Display(void) const
	{
		cout << endl << SEPERATOR("TCP头") << endl;
		cout << "源端口号：" << ::ntohs(this->m_usSrcPort) << endl;
		cout << "目的端口号：" << ::ntohs(this->m_usDstPort) << endl;
		cout << "序列号：" << NumberDisplay(::ntohl(this->m_uiSeqNO)) << endl;
		cout << "确认号：" << NumberDisplay(::ntohl(this->m_uiAckNO)) << endl;
		TTCPHeader tTCPHeader;
		(*reinterpret_cast<unsigned short*>(&tTCPHeader.m_uiAckNO + 1)) = ::ntohs(*reinterpret_cast<const unsigned short*>(&this->m_uiAckNO + 1));
		cout << "标记位：" << NumberDisplay(tTCPHeader.m_ucFlag) << endl;
		cout << "保留字：" << NumberDisplay(tTCPHeader.m_ucReserved) << endl;
		cout << "偏移量：" << NumberDisplay(tTCPHeader.m_ucOffset) << endl;
		cout << "窗口大小：" << ::ntohs(this->m_usWindowSize) << endl;
		cout << "校验和：" << NumberDisplay(::ntohs(this->m_usChkSum)) << endl;
		cout << "紧急指针：" << ::ntohs(this->m_usUrgPtr) << endl;
		cout << SEPERATOR() << endl;
	}

	unsigned short CheckSum(const unsigned short* buf, int iLen)
	{
		unsigned long ulChkSum = 0;

		//将数据以字为单位累加到双字中
		while (iLen > 1)
		{
			ulChkSum += *buf++;
			iLen -= sizeof (unsigned short);
		}

		//如果为奇数，将最后一个字节扩展到双字并累加
		if (0 != iLen)
		{
			ulChkSum += *reinterpret_cast<const unsigned char*>(buf);
		}

		//将双字的高16位和低16位相加，取反后得到校验和
		ulChkSum = (ulChkSum >> 16) + (ulChkSum & 0xffff);
		ulChkSum += (ulChkSum >> 16);

		return static_cast<unsigned short>(~ulChkSum);
	}

	unsigned short UDPCheckSum(const TIPHeader& tIPHeader, const TUDPHeader& tUDPHeader, const string& str)
	{
		char* p = new char[str.length() + 64];
		char* pStart = p;
		unsigned int uiCheckSumLen = 0;

		//包含源IP和目的IP地址
		memcpy(p, &tIPHeader.m_uiSrcIP, sizeof (tIPHeader.m_uiSrcIP));
		p +=sizeof (tIPHeader.m_uiSrcIP);
		uiCheckSumLen += sizeof (tIPHeader.m_uiSrcIP);
		memcpy(p, &tIPHeader.m_uiDstIP, sizeof (tIPHeader.m_uiDstIP));
		p += sizeof (tIPHeader.m_uiDstIP);
		uiCheckSumLen += sizeof (tIPHeader.m_uiDstIP);

		//包含8位0
		memset(p, '\0', 1);
		p += 1;
		uiCheckSumLen += 1;

		//协议
		unsigned char ucProtocol = tIPHeader.m_ucProtocol;
		memcpy(p, &ucProtocol, sizeof (ucProtocol));
		p += sizeof (ucProtocol);
		uiCheckSumLen += sizeof (ucProtocol);

		//UDP长度
		memcpy(p, &tUDPHeader.m_usLen, sizeof (tUDPHeader.m_usLen));
		p += sizeof (tUDPHeader.m_usLen);
		uiCheckSumLen += sizeof (tUDPHeader.m_usLen);

		//UDP源端口号
		memcpy(p, &tUDPHeader.m_usSrcPort, sizeof (tUDPHeader.m_usSrcPort));
		p += sizeof (tUDPHeader.m_usSrcPort);
		uiCheckSumLen += sizeof(tUDPHeader.m_usSrcPort);

		//UDP目的端口号
		memcpy(p, &tUDPHeader.m_usDstPort, sizeof (tUDPHeader.m_usDstPort));
		p += sizeof (tUDPHeader.m_usDstPort);
		uiCheckSumLen += sizeof (tUDPHeader.m_usDstPort);

		//又是UDP长度
		memcpy(p, &tUDPHeader.m_usLen, sizeof (tUDPHeader.m_usLen));
		p += sizeof (tUDPHeader.m_usLen);
		uiCheckSumLen += sizeof (tUDPHeader.m_usLen);

		//16位的UDP校验和，置为0
		memset(p, '\0', 2);
		p += 2;
		uiCheckSumLen += 2;

		//净荷
		memcpy(p, str.data(), str.length());
		p += str.length();
		uiCheckSumLen += str.length();

		//以两字节对齐
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

		//添加伪TCP头
		AppendString(str, &tIPHeader.m_uiSrcIP, sizeof (tIPHeader.m_uiSrcIP));
		AppendString(str, &tIPHeader.m_uiDstIP, sizeof (tIPHeader.m_uiDstIP));
		AppendString(str, '\0', 1);
		unsigned char ucProtocol = tIPHeader.m_ucProtocol;
		AppendString(str, &ucProtocol, sizeof (ucProtocol));
		unsigned short usSize = ::htons(sizeof (tTCPHeader) + sizeof (TTCPOption1));
		AppendString(str, &usSize, sizeof (usSize));

		//添加真实TCP头
		AppendString(str, &tTCPHeader, sizeof (tTCPHeader));
		//添加TCP选项部分
		str += strLoad;

		if (0 != str.length() % 2)		//如果不是以2字节对齐
		{
			AppendString(str, '\0', 1);
		}

		return CheckSum(reinterpret_cast<const unsigned short*>(str.data()), str.length());
	}
}
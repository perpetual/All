#ifndef NETPROTOCOL_NET_PROTOCOL_H
#define NETPROTOCOL_NET_PROTOCOL_H

#include "VersionControl.h"
#include <string>
#include <cstring>

//从网络中获取的各种头要转换字节序才能正确显示
namespace NetProtocol
{
	using std::string;

	//以太帧头
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

	//IP头
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

		//显示IP头的内容
		void Display(void) const;

		unsigned short m_ucHeaderLen : 4;		//IP头长度
		unsigned short m_ucVersion : 4;			//IP版本
		unsigned short m_ucService : 8;			//区分服务，一般情况下都不使用该字段
		unsigned short m_usTotalSize;				//封包的总大小，即整个IP报的大小
		unsigned short m_usID;							//封包标识，唯一标识发送的每一个数据报
		unsigned short m_usOffset : 13;			//片偏移
		unsigned short m_ucFlag : 3;				//标记
		unsigned short m_ucTTL : 8;					//生存时间
		unsigned short m_ucProtocol : 8;			//协议类型，可能是TCP，UDP，ICMP等
		unsigned short m_usChkSum;				//校验和
		unsigned int m_uiSrcIP;							//源IP
		unsigned int m_uiDstIP;							//目的IP
	};

	//ICMP头
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

		unsigned short m_ucICMPType : 8;				//消息类型
		unsigned short m_ucICMPCode : 8;				//代码
		unsigned short m_usICMPChkSum;			//校验和

		//回显头
		unsigned short m_usICMPID;					//用来唯一标识此请求的ID号，通常设置为进程ID
		unsigned short m_usICMPSeq;				//序列号
		unsigned int m_uiICMPTimestamp;			//时间戳
	};

	//计算ICMP头校验和
	//第一个参数是缓冲区指针
	//第二个参数是缓冲区长度
	unsigned short CheckSum(const unsigned short*, int);

	//UDP头
	struct TUDPHeader
	{
		TUDPHeader(void) :
			m_usSrcPort(0),
			m_usDstPort(0),
			m_usLen(0),
			m_usChkSum(0)
		{}

		//显示UDP头的内容
		void Display(void) const;

		unsigned short m_usSrcPort;				//源端口号
		unsigned short m_usDstPort;				//目的端口号
		unsigned short m_usLen;					//封包长度
		unsigned short m_usChkSum;			//校验和
	};

	//UDP头的校验和
	//第一个参数是IP头指针
	//第二个参数是UDP头指针
	//第三个参数是净载荷
	unsigned short UDPCheckSum(const TIPHeader&, const TUDPHeader&, const string&);

	//TCP头
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

		unsigned short m_usSrcPort;				//源端口号
		unsigned short m_usDstPort;				//目的端口号
		unsigned int m_uiSeqNO;					//序列号
		unsigned int m_uiAckNO;					//确认号
		//unsigned char m_ucOffset;				//四位首部长度和
		//unsigned char m_ucFlag;				//6位标记位
		unsigned short m_ucFlag : 6;			//标记位
		unsigned short m_ucReserved : 6;		//保留字
		unsigned short m_ucOffset : 4;			//数据偏移
		unsigned short m_usWindowSize;		//窗口大小
		unsigned short m_usChkSum;			//校验和
		unsigned short m_usUrgPtr;				//紧急指针
	};

	//三次握手第一次握手的选项
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

	//计算TCP校验和
	//第一个参数是IP头
	//下一个参数是TCP头
	//下一个参数是载荷，也包括TCP选项部分
	unsigned short TCPCheckSum(const TIPHeader&, const TTCPHeader&, const string&);

	//ARP协议头
	enum
	{
		ARP_REQUEST,			//ARP请求
		ARP_REPLY				//ARP响应
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
		unsigned short m_usHardAddr;				//硬件地址空间
		unsigned short m_usType;						//以太网类型
		unsigned char m_ucMACLen;					//MAC地址的长度
		unsigned char m_ucIPLen;						//IP地址的长度
		unsigned short m_usOpCode;				//操作码
		unsigned char m_ucSrcMAC[6];				//源MAC地址
		unsigned char m_ucSrcIP[4];					//源IP地址
		unsigned char m_ucDstMAC[6];				//目的MAC地址
		unsigned char m_ucDstIP[4];					//目的IP地址
	};
}
#endif
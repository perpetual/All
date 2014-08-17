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
		unsigned char Tos;							//服务类型
		unsigned char Flags;							//IP头标记
		unsigned char OptionsSize;				//可选数据大小
		unsigned char *OptionsData;				//指向可选数据的指针
	} IP_OPTION_INFORMATION, * PIP_OPTION_INFORMATION;

	typedef struct
	{
		DWORD Address;										// 应答地址
		unsigned long  Status;								 //应答状态
		unsigned long  RoundTripTime;					//返回时间
		unsigned short DataSize;							//应答数据大小
		unsigned short Reserved;							//保留位
		void *Data;												//指向应答数据的指针
		IP_OPTION_INFORMATION Options;			//应答选项
	} IP_ECHO_REPLY, * PIP_ECHO_REPLY;

	// 定义三个函数指针类型
	typedef HANDLE (WINAPI* pfnHV)(VOID);
	typedef BOOL (WINAPI* pfnBH)(HANDLE);
	typedef DWORD (WINAPI* pfnDHDPWPipPDD)(HANDLE, DWORD, LPVOID, WORD, PIP_OPTION_INFORMATION, LPVOID, DWORD, DWORD);

	class CPing : public CICMP
	{
	public:
		//参数为超时时间
		CPing(unsigned int = 5000);

		//发出Ping包
		//第一个参数是目标IP地址或主机名
		//第二个参数为TTL值，0表示不设置TTL值
		CICMP::EEchoType Ping(const string&, unsigned int = 0);
		CICMP::EEchoType PingEx(const string&, unsigned int = 0);

		//设置超时时间（ms）
		void SetSocketOutTime(unsigned int uiOutTime)
		{
			this->m_uiOutTime = uiOutTime;
		}

		//获取序号
		unsigned int GetSeqNO(void)
		{
			return this->m_tICMPHeader.m_usICMPSeq;
		}

		//获取源IP
		string GetSourceIP(void) const
		{
			return inet_ntoa(*reinterpret_cast<const in_addr*>(&this->m_tIPHeader.m_uiDstIP));
		}

		//获取目标IP
		string GetDestIP(void) const
		{
			return inet_ntoa(*reinterpret_cast<const in_addr*>(&this->m_tIPHeader.m_uiSrcIP));
		}

		//获取TTL
		unsigned short GetTTL(void) const
		{
			return this->m_tIPHeader.m_ucTTL;
		}

		//获取时间戳
		unsigned int GetTimestamp(void) const
		{
			return this->m_tICMPHeader.m_uiICMPTimestamp;
		}

		//获取延迟(毫秒)
		unsigned short GetDelay(void) const
		{
			return this->m_usDelay;
		}

	private:
		TIPHeader m_tIPHeader;					//IP头
		TICMPHeader m_tICMPHeader;			//ICMP头
		unsigned short m_usDelay;						//延迟（ms）
		HINSTANCE m_hICMP;						//ICMP动态库句柄
		PIP_ECHO_REPLY m_pEchoBuf;			//应答缓冲区指针

		//定义三个指针函数
		pfnHV m_pIcmpCreateFile;
		pfnBH m_pIcmpCloseHandle;
		pfnDHDPWPipPDD m_pIcmpSendEcho;
		HANDLE m_hPing;									//Ping服务
	};
}

#endif
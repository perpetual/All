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

	//显示ICMP头内容
	void DisplayICMPHeader(const TICMPHeader&);

	//显示IP头内容
	void DisplayIPHeader(const TIPHeader&);

	class CICMP : public CInitSocketLibrary
	{
	public:
		enum EEchoType
		{
			ECHO_ERROR,		//错误
			ECHO_UNREACHABLE,	//不可达
			ECHO_FINISH		//正常
		};

	protected:
		//参数为超时时间
		CICMP(unsigned int uiOutTime);
		~CICMP(void);

		//发送探测包
		//第一个参数目标IP地址或主机名称
		//第二个参数是TTL值，0表示使用默认TTL值
		//返回IP地址，空表示探测失败
		string Probe(const string&, unsigned int = 0);

		//捕捉探测响应包
		//参数是超时时间（ms），0表示不超时
		//参数是传出参数
		//返回值表示返回值类型
		EEchoType Catch(TIPHeader&, TICMPHeader&) ;

		unsigned int m_uiSeq;				//序号
		unsigned int m_uiOutTime;		//超时时间（ms）

	private:
		//禁止复制与赋值
		CICMP(const CICMP&);
		CICMP& operator =(const CICMP&);

		SOCKET m_sockSend;				//发送套接字
		SOCKET m_sockRecv;				//接收套接字
	};
}

#endif
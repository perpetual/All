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

	//网络嗅探器
	class CSniffer : public CInitSocketLibrary
	{
	public:
		//第一个参数表示是否设置为混杂模式
		//下一个参数为缓冲区长度
#ifdef __OS_VERSION_WINDOWS__
		CSniffer(bool = true, unsigned int = 65536);
#elif defined (__OS_VERSION_LINUX__)
		//第一个参数为网卡的名字
		CSniffer(const string& = "eth0", bool = true, unsigned int = 65536);
#endif
		~CSniffer(void);

		//接收数据
		void Start(void) const;

		//添加源IP地址
		void AddSourceIP(const string&);

		//删除源IP地址
		void RemoveSourceIP(const string&);

		//添加目标IP地址
		void AddDestinationIP(const string&);

		//删除源IP地址
		void RemoveDestinationIP(const string&);

		//添加源端口
		void AddSourcePort(unsigned short);

		//删除源端口
		void RemoveSourcePort(unsigned short);

		//添加目的端口
		void AddDestinationPort(unsigned short);

		//删除目的端口
		void RemoveDestinationPort(unsigned short);

		//添加协议
		void AddProtocol(unsigned char);

		//删除协议
		void RemoveProtocol(unsigned char);

	private:
		//禁止复制和赋值
		CSniffer(const CSniffer&);
		CSniffer& operator =(const CSniffer&);

		//判断源、目的端口是否需要过滤
		//第一个参数是源端口
		//第二个参数是目的端口
		bool HasPort(unsigned short, unsigned short) const;

		SOCKET m_sock;
		char* m_pBuf;					//缓冲区指针
		const unsigned int m_uiBufLen;			//缓冲区长度

		set<unsigned int> m_setSrcIP;			//源ip地址
		set<unsigned int> m_setDstIP;			//目的ip地址
		set<unsigned short> m_setSrcPort;	//源端口
		set<unsigned short> m_setDstPort;	//目的端口
		set<unsigned char> m_setProtocol;	//协议
	};
}

#endif
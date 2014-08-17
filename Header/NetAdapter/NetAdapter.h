#ifndef NETADAPTER_NET_ADAPTER_H
#define NETADAPTER_NET_ADAPTER_H

#include "VersionControl.h"
#include <vector>
#include <string>
#include "MyTools/MyNetTools.h"

namespace NetAdapter
{
	using std::vector;
	using std::string;
	using MyTools::CInitSocketLibrary;

	//获取本机网络适配器（网卡）的信息
	class CNetAdapter : public CInitSocketLibrary
	{
	public:
		struct TNetAdapterInfo
		{
			unsigned int m_uiIndex;							//适配器索引
			string m_strNetAdapterName;				//适配器名称
			string m_strNetAdapterDescription;		//适配器描述
			unsigned long long m_ullMACAddress;	//MAC地址的数值形式
			string m_strMACAddress;						//适配器MAC地址的字符串形式
			string m_strIPAddress;							//与适配器相关联的IP地址
			string m_strGatewayAddress;				//适配器网关地址
			string m_strMask;									//子网掩码
		};

		CNetAdapter(void);
		~CNetAdapter(void);
		//获取网卡数量
		unsigned int GetCount(void) const;

		//获取指定网络适配器序号
		unsigned int GetIndex(unsigned int) const;

		//获取网络适配器名称
		string GetName(unsigned int) const;

		//获取网络适配器描述
		string GetDescription(unsigned int) const;

		//获取网络适配器的数值形式
		unsigned long long GetMACAddress1(unsigned int) const;

		//获取网络适配器的字符串形式
		string GetMACAddress2(unsigned int) const;

		//获取IP地址
		string GetIPAddress(unsigned int) const;

		//获取网关地址
		string GetGatewayAddress(unsigned int) const;

		//获取掩码
		string GetMask(unsigned int) const;

	private:
		//禁止复制和赋值
		CNetAdapter(const CNetAdapter&);
		CNetAdapter& operator =(const CNetAdapter&);

		vector <TNetAdapterInfo> m_vecNetAdapters;		//适配器信息
		PIP_ADAPTER_INFO m_pAdapterInfo;					//适配器结构体指针
		unsigned long m_ulAdapterInfoSize;						//适配器结构体大小
	};
}

#endif
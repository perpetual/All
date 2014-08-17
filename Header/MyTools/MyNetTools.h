#ifndef MY_NET_TOOLS_H
#define MY_NET_TOOLS_H

#include "VersionControl.h"
#include <string>
#include <vector>
#include <utility>

namespace MyTools
{
	using std::string;
	using std::vector;
	using std::pair;

	//初始化套接字库
	class CInitSocketLibrary
	{
	public:
		//参数是高位和低位版本号
		CInitSocketLibrary(unsigned short = 2, unsigned short = 2);
		~CInitSocketLibrary(void);
	private:
		static unsigned int m_uiSocketLibraryInitCount;
	};

	//释放套接字库
	void ReleaseSocketLibrary(void);

	//检测是否是IP地址的点分十进制形式
	bool CheckIP(const string&);

	//网络字节序的无符号整形转换为IP字符串
	//第二个参数表示是否转换字节序
	string NetUIntToStringIP(unsigned int, bool = false);

	//字符串IP地址转换为网络字节序无符号整型
	unsigned int StringIPToNetUInt(const string&);

	//获取主机名称
	string GetHostName(void);

	//获取指定主机所有的IP地址
	//Windows下的参数为主机名称
	//Linux下氏网卡接口名称
	vector<string> GetHostAddress(const string& = "");
	vector<string> GetHostAddressAd(const string& = "");


	//将主机名称和域名统一转换为IP地址字符串，IP地址不转换
	string GetIPAddress(const string&);

	//填写地址结构体
	//第一个参数是IP地址
	//下一个参数是主机字节序的端口号
	sockaddr_in FillSockAddr(const string& = "", unsigned short = 0);

	//获取指定IP地址对应的MAC地址
	//参数是IP地址
	vector<unsigned short> GetMACAddress(const string&);
}

#endif
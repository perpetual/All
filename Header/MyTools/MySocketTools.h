#ifndef MYTOOLS_MY_SOCKET_TOOLS_H
#define MYTOOLS_MY_SOCKET_TOOLS_H

#include "VersionControl.h"
#include <utility>
#include <string>

namespace MyTools
{
	using std::pair;
	using std::string;

	//设置接收超时时间（毫秒）
	bool SetSocketOutTime(SOCKET, unsigned int);

	//设置发送UDP包的TTL值
	bool SetSocketTTL(SOCKET, unsigned int);

	//设置多播的TTL值
	bool SetMulticastSocketTTL(SOCKET, unsigned int);

	//获取获取与套接字绑定的地址和端口
	pair<string, unsigned short> GetSocketInfo(SOCKET);

	//将套接字设置为非阻塞或阻塞
	//第二个参数true表示设置为非阻塞，false表示设置为阻塞
	bool SetSocketNonBlock(SOCKET, BOOL = true);

	//设置套接字是否允许广播
	bool SetSocketBroadcast(SOCKET, BOOL = true);

	//设置套接字可以重用端口
	//在Linux下，每个复用的套接字都要进行设置
	bool SetSocketReuse(SOCKET, BOOL = true);

	//加入多播组
	//第二个参数是多播组的本地地址
	//下一个参数是接口地址
	bool SetSocketMulticast(SOCKET, const string&, const string& = "0.0.0.0", BOOL = true);

	//使用原始套接字发送IP头
	bool SetRawSocketIPHeader(SOCKET, BOOL = true);

	//将网卡设置为混杂模式，以以接收网络上所有的封包
#ifdef __OS_VERSION_WINDOWS__
	bool SetRawSocketReceiveAll(SOCKET, BOOL = true);
#elif defined (__OS_VERSION_LINUX__)
	//下一个参数是网卡的名称
	bool SetRawSocketReceiveAll(SOCKET, const string& = "eth0", BOOL = true);
#endif
}
#endif
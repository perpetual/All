#ifndef MYTOOLS_MY_SOCKET_TOOLS_H
#define MYTOOLS_MY_SOCKET_TOOLS_H

#include "VersionControl.h"
#include <utility>
#include <string>

namespace MyTools
{
	using std::pair;
	using std::string;

	//���ý��ճ�ʱʱ�䣨���룩
	bool SetSocketOutTime(SOCKET, unsigned int);

	//���÷���UDP����TTLֵ
	bool SetSocketTTL(SOCKET, unsigned int);

	//���öಥ��TTLֵ
	bool SetMulticastSocketTTL(SOCKET, unsigned int);

	//��ȡ��ȡ���׽��ְ󶨵ĵ�ַ�Ͷ˿�
	pair<string, unsigned short> GetSocketInfo(SOCKET);

	//���׽�������Ϊ������������
	//�ڶ�������true��ʾ����Ϊ��������false��ʾ����Ϊ����
	bool SetSocketNonBlock(SOCKET, BOOL = true);

	//�����׽����Ƿ�����㲥
	bool SetSocketBroadcast(SOCKET, BOOL = true);

	//�����׽��ֿ������ö˿�
	//��Linux�£�ÿ�����õ��׽��ֶ�Ҫ��������
	bool SetSocketReuse(SOCKET, BOOL = true);

	//����ಥ��
	//�ڶ��������Ƕಥ��ı��ص�ַ
	//��һ�������ǽӿڵ�ַ
	bool SetSocketMulticast(SOCKET, const string&, const string& = "0.0.0.0", BOOL = true);

	//ʹ��ԭʼ�׽��ַ���IPͷ
	bool SetRawSocketIPHeader(SOCKET, BOOL = true);

	//����������Ϊ����ģʽ�����Խ������������еķ��
#ifdef __OS_VERSION_WINDOWS__
	bool SetRawSocketReceiveAll(SOCKET, BOOL = true);
#elif defined (__OS_VERSION_LINUX__)
	//��һ������������������
	bool SetRawSocketReceiveAll(SOCKET, const string& = "eth0", BOOL = true);
#endif
}
#endif
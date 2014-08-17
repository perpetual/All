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

	//��ʼ���׽��ֿ�
	class CInitSocketLibrary
	{
	public:
		//�����Ǹ�λ�͵�λ�汾��
		CInitSocketLibrary(unsigned short = 2, unsigned short = 2);
		~CInitSocketLibrary(void);
	private:
		static unsigned int m_uiSocketLibraryInitCount;
	};

	//�ͷ��׽��ֿ�
	void ReleaseSocketLibrary(void);

	//����Ƿ���IP��ַ�ĵ��ʮ������ʽ
	bool CheckIP(const string&);

	//�����ֽ�����޷�������ת��ΪIP�ַ���
	//�ڶ���������ʾ�Ƿ�ת���ֽ���
	string NetUIntToStringIP(unsigned int, bool = false);

	//�ַ���IP��ַת��Ϊ�����ֽ����޷�������
	unsigned int StringIPToNetUInt(const string&);

	//��ȡ��������
	string GetHostName(void);

	//��ȡָ���������е�IP��ַ
	//Windows�µĲ���Ϊ��������
	//Linux���������ӿ�����
	vector<string> GetHostAddress(const string& = "");
	vector<string> GetHostAddressAd(const string& = "");


	//���������ƺ�����ͳһת��ΪIP��ַ�ַ�����IP��ַ��ת��
	string GetIPAddress(const string&);

	//��д��ַ�ṹ��
	//��һ��������IP��ַ
	//��һ�������������ֽ���Ķ˿ں�
	sockaddr_in FillSockAddr(const string& = "", unsigned short = 0);

	//��ȡָ��IP��ַ��Ӧ��MAC��ַ
	//������IP��ַ
	vector<unsigned short> GetMACAddress(const string&);
}

#endif
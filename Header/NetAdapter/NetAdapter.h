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

	//��ȡ��������������������������Ϣ
	class CNetAdapter : public CInitSocketLibrary
	{
	public:
		struct TNetAdapterInfo
		{
			unsigned int m_uiIndex;							//����������
			string m_strNetAdapterName;				//����������
			string m_strNetAdapterDescription;		//����������
			unsigned long long m_ullMACAddress;	//MAC��ַ����ֵ��ʽ
			string m_strMACAddress;						//������MAC��ַ���ַ�����ʽ
			string m_strIPAddress;							//���������������IP��ַ
			string m_strGatewayAddress;				//���������ص�ַ
			string m_strMask;									//��������
		};

		CNetAdapter(void);
		~CNetAdapter(void);
		//��ȡ��������
		unsigned int GetCount(void) const;

		//��ȡָ���������������
		unsigned int GetIndex(unsigned int) const;

		//��ȡ��������������
		string GetName(unsigned int) const;

		//��ȡ��������������
		string GetDescription(unsigned int) const;

		//��ȡ��������������ֵ��ʽ
		unsigned long long GetMACAddress1(unsigned int) const;

		//��ȡ�������������ַ�����ʽ
		string GetMACAddress2(unsigned int) const;

		//��ȡIP��ַ
		string GetIPAddress(unsigned int) const;

		//��ȡ���ص�ַ
		string GetGatewayAddress(unsigned int) const;

		//��ȡ����
		string GetMask(unsigned int) const;

	private:
		//��ֹ���ƺ͸�ֵ
		CNetAdapter(const CNetAdapter&);
		CNetAdapter& operator =(const CNetAdapter&);

		vector <TNetAdapterInfo> m_vecNetAdapters;		//��������Ϣ
		PIP_ADAPTER_INFO m_pAdapterInfo;					//�������ṹ��ָ��
		unsigned long m_ulAdapterInfoSize;						//�������ṹ���С
	};
}

#endif
#ifndef TRACE_H
#define TRACE_H

#include <string>
#include <vector>
#include <utility>
#include "ICMP.h"
#include "Ping.h"

namespace ICMP
{
	using ICMP::CICMP;
	using ICMP::CPing;
	using std::string;
	using std::vector;
	using std::pair;

	class CTrace : public CICMP
	{
	public:
		//��һ��������ʾ��ʱʱ��
		//��һ��������ʾ���TTLֵ
		//��һ��������ʾ̽���������
		CTrace(unsigned int = 10000, unsigned short = 30, unsigned char = 3);

		//����·��
		//��һ��������Ŀ��IP��ַ��������
		//�ڶ����������������
		//������������ʾ�Ƿ���ʾ������Ϣ
		bool Trace(const string&, bool = false);
		bool TraceEx(const string&, bool = false);

		//����·�ɵĳ�ʱʱ�䣨ms��
		void SetSocketOutTime(unsigned int uiOutTime)
		{
			this->m_oPing.SetSocketOutTime(uiOutTime);
		}

		//����·�ɵ��������
		void SetMaxTTL(unsigned short uiMaxTTL)
		{
			this->m_uiMaxTTL = uiMaxTTL;
		}

		//����ʧ�ܳ��Դ���
		void SetTryCount(unsigned char ucTryCount)
		{
			this->m_ucTryCount = ucTryCount;
		}

		//��ȡǰһ��·����Ϣ
		vector<pair<string, unsigned short>> GetLastRoute(void) const
		{
			return this->m_vecLastResult;
		}

		//��ȡ����·����Ϣ
		vector<pair<string, unsigned short>> GetNewRoute(void) const
		{
			return this->m_vecSuccessfulResult;
		}

		//ֹͣ̽��
		void Stop(void)
		{
			this->m_bProbing = false;
		}

	private:
		vector<pair<string, unsigned short>> m_vecLastResult;						//��һ�γɹ���·��<IP���ӳ٣�ms��>
		vector<pair<string, unsigned short>> m_vecSuccessfulResult;		//��·��<IP���ӳ٣�ms��>
		vector<pair<string, unsigned short>> m_vecFailureResult;
		CPing m_oPing;												//����̽��·��
		unsigned short m_uiMaxTTL;							//�����������
		unsigned char m_ucTryCount;						//̽�����
		bool m_bSuccessful;										//��Ǳ���̽���Ƿ�ɹ�
		bool m_bProbing;											//�Ƿ���Ҫ����̽��
	};
}


#endif
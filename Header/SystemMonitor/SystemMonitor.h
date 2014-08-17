/*
 * File:   SystemMonitor.h
 * Author: zy
 *
 * Created on 2011��6��30��, ����9:40
 */

#ifndef SYSTEMMONITOR_SYSTEM_MONITOR_H
#define	SYSTEMMONITOR_SYSTEM_MONITOR_H

#include <string>
#include <vector>
#include <ostream>
#ifdef __OS_VERSION_WINDOWS__
#include <Windows.h>
#include <winternl.h>
#endif

namespace SystemMonitor
{
    using std::string;
    using std::vector;
    using std::ostream;

    class CSystemMonitor
	{
#ifdef __OS_VERSION_WINDOWS__
		typedef struct
		{
			LARGE_INTEGER liKeBootTime;
			LARGE_INTEGER liKeSystemTime;
			LARGE_INTEGER liExpTimeZoneBias;
			ULONG         uCurrentTimeZoneId;
			DWORD         dwReserved;
		} SYSTEM_TIME_OF_DAY_INFORMATION;
#elif defined (__OS_VERSION_LINUX__)
		struct TCPUStat
		{
			unsigned long long m_ullUsr;     //��ϵͳ������ʼ�ۼƵ���ǰʱ�̣��û�̬��CPUʱ�䣨��λ��jiffies�� �������� niceֵΪ������
			unsigned long long m_ullNice;    //��ϵͳ������ʼ�ۼƵ���ǰʱ�̣�niceֵΪ���Ľ�����ռ�õ�CPUʱ�䣨��λ��jiffies��
			unsigned long long m_ullSystem;  //��ϵͳ������ʼ�ۼƵ���ǰʱ�̣�����ʱ�䣨��λ��jiffies��
			unsigned long long m_ullIdle;    //��ϵͳ������ʼ�ۼƵ���ǰʱ�̣���Ӳ��IO�ȴ�ʱ�����������ȴ�ʱ�䣨��λ��jiffies��
			unsigned long long m_ullIOWait;  //��ϵͳ������ʼ�ۼƵ���ǰʱ�̣�Ӳ��IO�ȴ�ʱ�䣨��λ��jiffies��
			unsigned long long m_ullIRQ;     //��ϵͳ������ʼ�ۼƵ���ǰʱ�̣�Ӳ�ж�ʱ�䣨��λ��jiffies��
			unsigned long long m_ullSoftIRQ; //softirq (5346) ��ϵͳ������ʼ�ۼƵ���ǰʱ�̣����ж�ʱ�䣨��λ��jiffies��

		};
#endif
    public:
        CSystemMonitor(void);
		~CSystemMonitor(void);

        //��ȡ��ǰCPU����
        short GetCPUCount(void);

        //��ȡCPU��ǰʹ����
        float GetCPUUsage(unsigned short = 0);
    private:
        //��ֹ���ƺ͸�ֵ
        CSystemMonitor(const CSystemMonitor&);
        CSystemMonitor& operator =(const CSystemMonitor&);

        //��ȡ״̬��Ϣ
        //����ΪCPU�ı�ţ�0��ʾ����CPU
        //����CPU����
        short GetStat(void);

        unsigned short m_usCPUCount;
		bool m_bFirst;				//����Ƿ��ǵ�һ������

#ifdef __OS_VERSION_WINDOWS__
		LARGE_INTEGER m_liLastIdleTime;
		LARGE_INTEGER m_liLastSystemTime;

		SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION* m_pIdleTimeBuf;		//��ȡCPU����ʱ��
#elif defined (__OS_VERSION_LINUX__)
		unsigned long long m_ullLastTotalCPUTime;
		unsigned long long m_ullLastIdleTime;
        vector<TCPUStat> m_vecCPUStats;
#endif
    };
}

#endif	/* SYSTEMMONITOR_H */


/*
 * File:   SystemMonitor.h
 * Author: zy
 *
 * Created on 2011年6月30日, 下午9:40
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
			unsigned long long m_ullUsr;     //从系统启动开始累计到当前时刻，用户态的CPU时间（单位：jiffies） ，不包含 nice值为负进程
			unsigned long long m_ullNice;    //从系统启动开始累计到当前时刻，nice值为负的进程所占用的CPU时间（单位：jiffies）
			unsigned long long m_ullSystem;  //从系统启动开始累计到当前时刻，核心时间（单位：jiffies）
			unsigned long long m_ullIdle;    //从系统启动开始累计到当前时刻，除硬盘IO等待时间以外其它等待时间（单位：jiffies）
			unsigned long long m_ullIOWait;  //从系统启动开始累计到当前时刻，硬盘IO等待时间（单位：jiffies）
			unsigned long long m_ullIRQ;     //从系统启动开始累计到当前时刻，硬中断时间（单位：jiffies）
			unsigned long long m_ullSoftIRQ; //softirq (5346) 从系统启动开始累计到当前时刻，软中断时间（单位：jiffies）

		};
#endif
    public:
        CSystemMonitor(void);
		~CSystemMonitor(void);

        //获取当前CPU个数
        short GetCPUCount(void);

        //获取CPU当前使用率
        float GetCPUUsage(unsigned short = 0);
    private:
        //禁止复制和赋值
        CSystemMonitor(const CSystemMonitor&);
        CSystemMonitor& operator =(const CSystemMonitor&);

        //获取状态信息
        //参数为CPU的编号，0表示所有CPU
        //返回CPU个数
        short GetStat(void);

        unsigned short m_usCPUCount;
		bool m_bFirst;				//标记是否是第一次运行

#ifdef __OS_VERSION_WINDOWS__
		LARGE_INTEGER m_liLastIdleTime;
		LARGE_INTEGER m_liLastSystemTime;

		SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION* m_pIdleTimeBuf;		//获取CPU空闲时间
#elif defined (__OS_VERSION_LINUX__)
		unsigned long long m_ullLastTotalCPUTime;
		unsigned long long m_ullLastIdleTime;
        vector<TCPUStat> m_vecCPUStats;
#endif
    };
}

#endif	/* SYSTEMMONITOR_H */


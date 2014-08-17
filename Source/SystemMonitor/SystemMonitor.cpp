#include "VersionControl.h"
#include <exception>
#include <sstream>
#include <iostream>
#include "SystemMonitor\SystemMonitor.h"
#include "MyTools/MyUtilityTools.h"

namespace SystemMonitor
{
    using Utility::exceptionx;
    using std::istringstream;
    using MyTools::ReadWholeFile;
    using MyTools::SplitString;
    using MyTools::Trim;
    using MyTools::StringToULongLong;
    using MyTools::StringToUInt;

    namespace
    {
#ifdef __OS_VERSION_WINDOWS__
		typedef NTSTATUS (WINAPI *NQSIFunc)(SYSTEM_INFORMATION_CLASS, PVOID, ULONG, PULONG);		//导出函数类型声明
		NQSIFunc   NtQuerySystemInformation = NULL;		//函数指针
#elif defined (__OS_VERSION_LINUX__)
        const string CPU("cpu");
		const string PROCESSES("processes");
#endif
	}

	CSystemMonitor::CSystemMonitor() :
		m_bFirst(true)
	{
#ifdef __OS_VERSION_WINDOWS__
		this->m_liLastIdleTime.QuadPart = 0;
		this->m_liLastSystemTime.QuadPart = 0;

		NtQuerySystemInformation = reinterpret_cast<NQSIFunc>(GetProcAddress(GetModuleHandle(L"ntdll.dll"), "NtQuerySystemInformation"));
		if (NULL == NtQuerySystemInformation)
		{
			throw exceptionx("NtQuerySystemInformation函数提取失败");
		}

		SYSTEM_BASIC_INFORMATION buf;
		if (NO_ERROR == NtQuerySystemInformation(SystemBasicInformation, &buf, sizeof (buf), NULL))
		{
			this->m_pIdleTimeBuf = new SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION[this->m_usCPUCount = buf.NumberOfProcessors];
		}
#elif defined (__OS_VERSION_LINUX__)
		this->m_ullLastTotalCPUTime = 0;
		this->m_ullLastIdleTime = 0;
		this->m_usCPUCount = this->GetStat();
#endif
    }

	CSystemMonitor::~CSystemMonitor(void)
	{
#ifdef __OS_VERSION_WINDOWS__
		delete[] this->m_pIdleTimeBuf;
#endif
	}

    short CSystemMonitor::GetCPUCount()
    {
        return this->m_usCPUCount;
    }

    float CSystemMonitor::GetCPUUsage(unsigned short usCPUSeq)
	{
		float fCPUUsage = 0.0f;
#ifdef __OS_VERSION_WINDOWS__
		//获取CPU的空闲时间
		if (usCPUSeq <= this->m_usCPUCount)
		{
			LARGE_INTEGER liCurIdleTime = {0};

			NTSTATUS ret = NtQuerySystemInformation(SystemProcessorPerformanceInformation, this->m_pIdleTimeBuf, this->m_usCPUCount * sizeof (SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION), NULL);
			if (NO_ERROR == ret)
			{
				if (0 == usCPUSeq)
				{
					for (int i = 0; i < this->m_usCPUCount; ++i)
					{
						liCurIdleTime.QuadPart += this->m_pIdleTimeBuf[i].IdleTime.QuadPart;
					}
				}
				else
				{
					if (usCPUSeq <= 2)
					{
						liCurIdleTime.QuadPart += this->m_pIdleTimeBuf[usCPUSeq - 1].IdleTime.QuadPart;
					}
				}
			}

			SYSTEM_TIME_OF_DAY_INFORMATION SystemTimeBuf;

			if (NO_ERROR == NtQuerySystemInformation(SystemTimeOfDayInformation, &SystemTimeBuf, sizeof (SystemTimeBuf), NULL))
			{
				fCPUUsage = static_cast<float>(liCurIdleTime.QuadPart - this->m_liLastIdleTime.QuadPart) / (0 == usCPUSeq ? this->m_usCPUCount : 1)
										/ (SystemTimeBuf.liKeSystemTime.QuadPart - this->m_liLastSystemTime.QuadPart);

				this->m_liLastIdleTime = liCurIdleTime;
				this->m_liLastSystemTime.QuadPart = SystemTimeBuf.liKeSystemTime.QuadPart;
				fCPUUsage = (1 - fCPUUsage) * 100;
			}
		}
#elif defined (__OS_VERSION_LINUX__)
		TCPUStat tCPUStat = {0};
		unsigned long long ullCurTotalCPUTime = 0;

		if (usCPUSeq <= this->m_usCPUCount)
		{
			this->GetStat();
			tCPUStat = this->m_vecCPUStats[usCPUSeq];
			ullCurTotalCPUTime = tCPUStat.m_ullUsr + tCPUStat.m_ullNice + tCPUStat.m_ullSystem + tCPUStat.m_ullIdle + tCPUStat.m_ullIOWait + tCPUStat.m_ullIRQ + tCPUStat.m_ullSoftIRQ;
			fCPUUsage = 100.0 - 100.0 * (tCPUStat.m_ullIdle - this->m_ullLastIdleTime) / (ullCurTotalCPUTime - this->m_ullLastTotalCPUTime);
			this->m_ullLastIdleTime = tCPUStat.m_ullIdle;
			this->m_ullLastTotalCPUTime = ullCurTotalCPUTime;
		}
#endif
		return this->m_bFirst ? (this->m_bFirst = false, 0) : fCPUUsage;
    }

    short CSystemMonitor::GetStat(void)
    {
#ifdef __OS_VERSION_WINDOWS__
		return this->m_usCPUCount;
#elif defined (__OS_VERSION_LINUX__)
        string strStat = ReadWholeFile("/proc/stat");

        if (strStat.empty())
        {
            throw exceptionx("状态信息读取失败");
        }
        else
        {
            string strLine;
            istringstream iss(strStat);

            this->m_vecCPUStats.clear();
            while (getline(iss, strLine))
            {
                strLine = Trim(strLine);
                if (0 == strLine.compare(0, CPU.length(), CPU))
                {
                    vector<string> vecStats = SplitString(strLine);
                    TCPUStat tCPUStat;

                    for (int i = 1; i < vecStats.size(); ++i)
                    {
                        unsigned long long ullTemp = StringToULongLong(vecStats[i]);
//                        std::cout << ullTemp << ' ';
                        switch (i - 1)
                        {
                        case 0:
                            tCPUStat.m_ullUsr = ullTemp;
                            break;
                        case 1:
                            tCPUStat.m_ullNice = ullTemp;
                            break;
                        case 2:
                            tCPUStat.m_ullSystem = ullTemp;
                            break;
                        case 3:
                            tCPUStat.m_ullIdle = ullTemp;
                            break;
                        case 4:
                            tCPUStat.m_ullIOWait = ullTemp;
                            break;
                        case 5:
                            tCPUStat.m_ullIRQ = ullTemp;
                            break;
                        case 6:
                            tCPUStat.m_ullSoftIRQ = ullTemp;
                            break;
                        }
                    }
//                    std::cout << std::endl;
                    this->m_vecCPUStats.push_back(tCPUStat);
                }
            }
		}
		return this->m_vecCPUStats.size() - 1;
#endif
	}
}

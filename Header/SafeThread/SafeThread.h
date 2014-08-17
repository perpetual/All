#ifndef WORK_THREAD_H
#define WORK_THREAD_H

#include "VersionControl.h"
#include <iostream>

namespace SafeThread
{
	//传递给线程的参数最好是在堆上分配，并且由线程负责释放
	class CSafeThread
	{
		enum EThreadStat{RUN, SUSPEND, PAUSE, STOP};		//线程状态
	protected:
		CSafeThread(void);
		//派生类的析构函数首先要停止线程，然后等待线程的退出并在线程停止后负责资源的回收
		virtual ~CSafeThread(void) = 0;

	public:
		//启动线程
		void Start(void) const;

		//停止线程
		virtual void Stop(void) {}

		//获取线程是否正在运行
		EThreadStat GetStat(void) const
		{
			return this->m_eStat;
		}

		//挂起线程
		void Suspend(void);

		//恢复线程运行
		void Resume(void);

		//等待线程的退出
		void WaitForWorkThread(void);

	protected:
		//工作函数
		virtual void WorkProcess(void);

		//释放资源
		virtual void Release(void) = 0;

	private:
		//禁止复制和赋值
		CSafeThread(const CSafeThread&);
		CSafeThread& operator =(const CSafeThread&);

		//线程函数
		static DWORD WINAPI ThreadProcess(LPVOID);

		HANDLE m_hWorkThread;			//线程句柄
		HANDLE m_hResource;				//资源信号量，用于控制线程的启动
		HANDLE m_hFnish;					//资源信号量，用于等待工作是否结束
		EThreadStat m_eStat;				//线程状态
		EThreadStat m_eLastStat;			//挂起前的状态
		SECURITY_ATTRIBUTES m_tSA;			//安全对象
		SECURITY_DESCRIPTOR m_tSD;		//安全描述符
	};

	class CDemoThread : public CSafeThread
	{
	public:
		CDemoThread(void) : m_bRunning(true) {}
		~CDemoThread(void) {this->WaitForWorkThread();}
		virtual void WaitForWorkThread(void)
		{
			this->m_bRunning = false;
		}

		virtual void WorkProcess(void)
		{
			while (this->m_bRunning)
			{
				std::cout << "示例\n";
				Sleep(100);
			}
		}

		bool m_bRunning;
	};
}

#endif
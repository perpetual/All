#include <iostream>
#include "VersionControl.h"
#include <exception>
#include "SafeThread/SafeThread.h"

namespace SafeThread
{
	using std::cout;
	using std::endl;
	using std::exception;

	CSafeThread::CSafeThread(void) :
		m_hWorkThread(NULL),
		m_hResource(NULL),
		m_hFnish(NULL),
		m_eStat(PAUSE),
		m_eLastStat(PAUSE)
	{
		this->m_hResource = ::CreateSemaphore(NULL, 0, 1, NULL);
		if (NULL == this->m_hResource)
		{
			throw exception("创建线程工作开始资源信号量失败！\n");
		}
		else
		{
			this->m_hFnish = ::CreateSemaphore(NULL, 0, 1, NULL);
			if (NULL == this->m_hFnish)
			{
				CloseHandle(this->m_hResource);
				throw exception("创建线程工作完成资源信号量失败！\n");
			}
			else
			{
				/*::InitializeSecurityDescriptor(&this->m_tSD, SECURITY_DESCRIPTOR_REVISION);
				::SetSecurityDescriptorDacl(&this->m_tSD, true, NULL, FALSE);
				this->m_tSA.nLength = sizeof (SECURITY_ATTRIBUTES);
				this->m_tSA.bInheritHandle = true;
				this->m_tSA.lpSecurityDescriptor = &this->m_tSD;*/

				//TCHAR * szSD = TEXT("D:")       // Discretionary ACL
					//TEXT("(D;OICI;GA;;;BG)")     // Deny access to 
					// built-in guests
					//TEXT("(D;OICI;GA;;;AN)")     // Deny access to 
					// anonymous logon
					//TEXT("(A;OICI;GRGWGX;;;AU)") // Allow 
					// read/write/execute 
					// to authenticated 
					// users
					//TEXT("(A;OICI;GA;;;BA)");    // Allow full control 
				// to administrators
				//this->m_tSA.bInheritHandle = false;
				//this->m_tSA.nLength = sizeof (SECURITY_ATTRIBUTES);
				/*bool b = ConvertStringSecurityDescriptorToSecurityDescriptor(
					szSD,
					SDDL_REVISION_1,
					&this->m_tSA.lpSecurityDescriptor,
					NULL);*/

				this->m_hWorkThread = ::CreateThread(NULL, 0, ThreadProcess, this, 0, NULL);
				if (NULL == this->m_hWorkThread)
				{
					CloseHandle(m_hFnish);
					throw exception("工作线程创建失败！\n");
				}
			}
		}
	}

	CSafeThread::~CSafeThread(void)
	{
		this->m_eLastStat = this->m_eStat;
		this->m_eStat = STOP;
		switch (this->m_eLastStat)
		{
		case RUN:
			break;
		case SUSPEND:
			::ResumeThread(this->m_hWorkThread);
			break;
		case PAUSE:
			::ReleaseSemaphore(this->m_hResource, 1, NULL);
			break;
		default:
			break;
		}
		::WaitForSingleObject(this->m_hFnish, INFINITE);
		::WaitForSingleObject(this->m_hWorkThread, INFINITE);
		CloseHandle(this->m_hResource);
		CloseHandle(this->m_hFnish);
		CloseHandle(this->m_hWorkThread);
	}

	void CSafeThread::Start(void) const
	{
		if (PAUSE == this->m_eStat)
		{
			::ReleaseSemaphore(m_hResource, 1, NULL);
		}
	}

	void CSafeThread::Suspend(void)
	{
		if (RUN == this->m_eStat || PAUSE == this->m_eStat)
		{
			this->m_eLastStat = this->m_eStat;
			::SuspendThread(this->m_hWorkThread);
			this->m_eStat = SUSPEND;
		}
	}

	void CSafeThread::Resume(void)
	{
		if (SUSPEND == this->m_eStat)
		{
			::ResumeThread(m_hWorkThread);
			this->m_eStat = this->m_eLastStat;
		}
	}

	void CSafeThread::WorkProcess(void)
	{
		cout <<  "工作开始\n";
	}

	void CSafeThread::WaitForWorkThread(void)
	{
		::WaitForSingleObject(this->m_hWorkThread, INFINITE);
		this->m_hWorkThread = NULL;
	}

	DWORD CSafeThread::ThreadProcess(LPVOID pParam)
	{
		CSafeThread* pThreadObj = reinterpret_cast<CSafeThread*>(pParam);

		//while (STOP != pThreadObj->m_eStat)
		{
			pThreadObj->m_eStat = PAUSE;
			::WaitForSingleObject(pThreadObj->m_hResource, INFINITE);
			if (STOP != pThreadObj->m_eStat)
			{
				pThreadObj->m_eStat = RUN;
				pThreadObj->WorkProcess();
				pThreadObj->Release();
			}
			::ReleaseSemaphore(pThreadObj->m_hFnish, 1, NULL);
		}
		return 0;
	}

}
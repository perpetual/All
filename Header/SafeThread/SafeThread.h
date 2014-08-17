#ifndef WORK_THREAD_H
#define WORK_THREAD_H

#include "VersionControl.h"
#include <iostream>

namespace SafeThread
{
	//���ݸ��̵߳Ĳ���������ڶ��Ϸ��䣬�������̸߳����ͷ�
	class CSafeThread
	{
		enum EThreadStat{RUN, SUSPEND, PAUSE, STOP};		//�߳�״̬
	protected:
		CSafeThread(void);
		//�������������������Ҫֹͣ�̣߳�Ȼ��ȴ��̵߳��˳������߳�ֹͣ������Դ�Ļ���
		virtual ~CSafeThread(void) = 0;

	public:
		//�����߳�
		void Start(void) const;

		//ֹͣ�߳�
		virtual void Stop(void) {}

		//��ȡ�߳��Ƿ���������
		EThreadStat GetStat(void) const
		{
			return this->m_eStat;
		}

		//�����߳�
		void Suspend(void);

		//�ָ��߳�����
		void Resume(void);

		//�ȴ��̵߳��˳�
		void WaitForWorkThread(void);

	protected:
		//��������
		virtual void WorkProcess(void);

		//�ͷ���Դ
		virtual void Release(void) = 0;

	private:
		//��ֹ���ƺ͸�ֵ
		CSafeThread(const CSafeThread&);
		CSafeThread& operator =(const CSafeThread&);

		//�̺߳���
		static DWORD WINAPI ThreadProcess(LPVOID);

		HANDLE m_hWorkThread;			//�߳̾��
		HANDLE m_hResource;				//��Դ�ź��������ڿ����̵߳�����
		HANDLE m_hFnish;					//��Դ�ź��������ڵȴ������Ƿ����
		EThreadStat m_eStat;				//�߳�״̬
		EThreadStat m_eLastStat;			//����ǰ��״̬
		SECURITY_ATTRIBUTES m_tSA;			//��ȫ����
		SECURITY_DESCRIPTOR m_tSD;		//��ȫ������
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
				std::cout << "ʾ��\n";
				Sleep(100);
			}
		}

		bool m_bRunning;
	};
}

#endif
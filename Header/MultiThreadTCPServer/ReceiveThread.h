#ifndef RECEIVETHREAD_RECEIVE_THREAD_H
#define  RECEIVETHREAD_RECEIVE_THREAD_H

#include "SafeThread/SafeThread.h"
#include "DataPath/TCPServer.h"

namespace MultiThreadTCPServer
{
	using SafeThread::CSafeThread;
	using DataPath::CTCPServer;

	class CReceiveThead : public CSafeThread
	{
	public:
		CReceiveThead(CTCPServer::CTCPClientSocket*);
		~CReceiveThead(void);
		virtual void WorkProcess(void);
		virtual void WaitForWorkThread(void);
		virtual void Release(void);
	private:
		CTCPServer::CTCPClientSocket* m_pTCPClientSocket;
	};
}


#endif
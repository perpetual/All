#include "MultiThreadTCPServer/MultiThreadTCPServer.h"
#include "DataPath/TCPServer.h"
#include "MultiThreadTCPServer/ReceiveThread.h"

namespace MultiThreadTCPServer
{
	using DataPath::CTCPServer;

	CMultiThreadTCPServer::CMultiThreadTCPServer(void)
	{
		CTCPServer o(4321);
		CTCPServer::CTCPClientSocket* pTCPClientSocket;
		CReceiveThead* pThread = NULL;

		if (o.Accept(*(pTCPClientSocket = new CTCPServer::CTCPClientSocket)))
		{
			pThread = new CReceiveThead(pTCPClientSocket);
			pThread->Start();
		}
		else
		{
			delete pTCPClientSocket;
		}
		Sleep(5000);
		delete pThread;
	}
}
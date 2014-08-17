#include "MultiThreadTCPServer/ReceiveThread.h"
#include <exception>
#include <string>
#include <iostream>
#include "MyTools/MyUtilityTools.h"

namespace MultiThreadTCPServer
{
	using std::exception;
	using std::string;
	using std::cout;
	using MyTools::NumberToDecString;

	CReceiveThead::CReceiveThead(CTCPServer::CTCPClientSocket* pTCPClientSocket) :
		m_pTCPClientSocket(pTCPClientSocket)
	{
		if (NULL == pTCPClientSocket || !*pTCPClientSocket)
		{
			throw exception("²ÎÊý´íÎó");
		}
	}

	CReceiveThead::~CReceiveThead(void)
	{
		this->WaitForWorkThread();
	}

	void CReceiveThead::WorkProcess(void)
	{
		string str;
		
		while (!(str = CTCPServer::Receive(*this->m_pTCPClientSocket).first).empty())
		{
			str += ' ' + this->m_pTCPClientSocket->GetClientAddress() + ' ' + NumberToDecString(this->m_pTCPClientSocket->GetClientPort()) + '\n';
			cout <<  str;
		}
	}

	void CReceiveThead::WaitForWorkThread(void)
	{
		this->m_pTCPClientSocket->CloseSocket();
		CSafeThread::WaitForWorkThread();
	}

	void CReceiveThead::Release(void)
	{
		delete this->m_pTCPClientSocket;
		this->m_pTCPClientSocket = NULL;
	}
}
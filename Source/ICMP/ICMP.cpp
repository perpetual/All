#include <iostream>
#include <exception>
#include "ICMP/ICMP.h"
#include "DataType/SimpleData.h"
#include "MyTools/MySocketTools.h"
#include "MyTools/MyNetTools.h"
#include "MyTools/MyUtilityTools.h"

namespace ICMP
{
	using std::cerr;
	using std::cout;
	using std::endl;
	using std::exception;
	using MyTools::Trim;
	using MyTools::SetSocketOutTime;
	using MyTools::SetSocketTTL;
	using MyTools::CheckIP;
	using MyTools::GetHostAddress;
	using NetProtocol::CheckSum;

	CICMP::CICMP(unsigned int uiOutTime = 5000) :
		m_uiSeq(0),
		m_uiOutTime(uiOutTime)
	{
		this->m_sockSend = ::socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
		this->m_sockRecv = ::socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);

		if (SOCKET_ERROR == this->m_sockSend || SOCKET_ERROR == this->m_sockRecv)
		{
			//throw exception("创建套接字失败");
		}
		else
		{
			SOCKADDR_IN addrRecv;

			addrRecv.sin_family = AF_INET;
			addrRecv.sin_addr.S_un.S_addr = INADDR_ANY;
			addrRecv.sin_port = htons(9);
			if (SOCKET_ERROR == ::bind(this->m_sockRecv, reinterpret_cast<SOCKADDR*>(&addrRecv), sizeof (SOCKADDR)))
			{
				throw exception("套接字绑定失败");
			}
		}
	}

	CICMP::~CICMP(void)
	{
		closesocket(this->m_sockSend);
		closesocket(this->m_sockRecv);
	}

	void DisplayICMPHeader(const TICMPHeader& tICMPHeader)
	{
		cout << "-----------------ICMP头部-------------" << endl;
		cout << "类型：" << static_cast<unsigned short>(tICMPHeader.m_ucICMPType)<< endl;
		cout << "代码：" << static_cast<unsigned short>(tICMPHeader.m_ucICMPCode) << endl;
		cout << "校验和：" << tICMPHeader.m_usICMPChkSum << endl;
		cout << "标识：" << tICMPHeader.m_usICMPID << endl;
		cout << "序号：" << tICMPHeader.m_usICMPSeq << endl;
		cout << "时间戳：" << tICMPHeader.m_uiICMPTimestamp << endl;
		cout << "----------------------------------------" << endl;
	}

	void DisplayIPHeader(const TIPHeader& ipHeader)
	{
		cout << "------------------IP头部---------------" << endl;
		cout << "IP版本号：" << static_cast<unsigned short>(ipHeader.m_ucVersion) << endl;
		cout << "服务类型：" << static_cast<unsigned short>(ipHeader.m_ucService) << endl;
		cout << "封包总长度：" << ipHeader.m_usTotalSize << endl;
		cout << "封包标识：" << ipHeader.m_usID << endl;
		cout << "标识：" << ipHeader.m_ucFlag << endl;
		cout << "生存时间：" << static_cast<unsigned short>(ipHeader.m_ucTTL) << endl;
		cout << "协议：" << static_cast<unsigned short>(ipHeader.m_ucProtocol) << endl;
		cout << "校验和：" << ipHeader.m_usChkSum << endl;
		cout << "源IP：" << inet_ntoa(*reinterpret_cast<const in_addr*>(&ipHeader.m_uiSrcIP)) << endl;
		cout << "目的IP：" << inet_ntoa(*reinterpret_cast<const in_addr*>(&ipHeader.m_uiDstIP)) << endl;
		cout << "----------------------------------------" << endl;
	}

	string CICMP::Probe(const string& strDest, unsigned int uiTTL)
	{
		string strIP = CheckIP(strDest) ? Trim(strDest) : GetHostAddress(strDest).front().c_str();
		string strRetIP;

		if (!strIP.empty())
		{
			//发送ICMP包
			SOCKADDR_IN addrTo;

			addrTo.sin_family = AF_INET;
			addrTo.sin_addr.S_un.S_addr = inet_addr(strIP.c_str());
			addrTo.sin_port = htons(9);

			char pSendBuf[sizeof (TICMPHeader) + 32];
			TICMPHeader* pICMPHdr = reinterpret_cast<TICMPHeader*>(pSendBuf);

			pICMPHdr->m_ucICMPType = 8;				//询问请求
			pICMPHdr->m_ucICMPCode = 0;
			pICMPHdr->m_usICMPID = static_cast<unsigned short>(::GetCurrentProcessId());
			pICMPHdr->m_usICMPSeq = static_cast<unsigned short>(this->m_uiSeq++);
			pICMPHdr->m_uiICMPTimestamp = 0;
			pICMPHdr->m_usICMPChkSum = 0;

			if (0 != uiTTL && !SetSocketTTL(this->m_sockSend, uiTTL))
			{
				//设置TTL失败
			}
			else
			{
				pICMPHdr->m_usICMPChkSum = 0;
				pICMPHdr->m_uiICMPTimestamp = ::GetTickCount();
				++pICMPHdr->m_usICMPSeq;
				pICMPHdr->m_usICMPChkSum = CheckSum(reinterpret_cast<unsigned short*>(pSendBuf), sizeof (TICMPHeader) + 32);

				if (SOCKET_ERROR != ::sendto(this->m_sockSend, pSendBuf, sizeof (TICMPHeader) + 32, 0, reinterpret_cast<SOCKADDR*>(&addrTo), sizeof (SOCKADDR)))
				{
					strRetIP = string(inet_ntoa(addrTo.sin_addr));
				}
			}
		}

		return strRetIP;
	}

	CICMP::EEchoType CICMP::Catch(TIPHeader& tIPHeader, TICMPHeader& tICMPHeader)
	{
		int iLen = sizeof (SOCKADDR);
		char pRecvBuf[1024];
		SOCKADDR_IN addrFrom;
		EEchoType eRet = ECHO_ERROR;

		if (0 != this->m_uiOutTime && !SetSocketOutTime(this->m_sockRecv, this->m_uiOutTime))
		{
			//设置超时时间失败
		}
		else
		{
			while (true)
			{
				int iRecvLen = ::recvfrom(this->m_sockRecv, pRecvBuf, 1024, 0, reinterpret_cast<SOCKADDR*>(&addrFrom), &iLen);

				if (SOCKET_ERROR == iRecvLen)
				{
					break;
				}
				else
				{
					tIPHeader = *reinterpret_cast<TIPHeader*>(pRecvBuf);
					tICMPHeader = *reinterpret_cast<TICMPHeader*>(pRecvBuf + sizeof (TIPHeader));

					if (11 == tICMPHeader.m_ucICMPType)
					{
						eRet = ECHO_UNREACHABLE;
					}
					else
					{
						if (0 == tICMPHeader.m_ucICMPType && tICMPHeader.m_usICMPID == ::GetCurrentProcessId())		//探测结束
						{
							eRet = ECHO_FINISH;
						}
						else
						{
							continue;
						}
					}
					break;
				}
			}
		}

		return eRet;
	}
}

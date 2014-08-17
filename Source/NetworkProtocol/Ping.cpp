#include <utility>
#include <exception>
#include "NetworkProtocol/Ping.h"
#include "MyTools/MyUtilityTools.h"
#include "MyTools/MyNetTools.h"

namespace ICMP
{
	using std::make_pair;
	using std::pair;
	using std::exception;
	using MyTools::Trim;
	using MyTools::GetHostAddress;
	using MyTools::CheckIP;

	const unsigned int BUF_LEN = 64;

	CPing::CPing(unsigned int uiOutTime) try :
		m_usDelay(0),
		m_hICMP(NULL),
		m_pEchoBuf(NULL),
		m_pIcmpCreateFile(NULL),
		m_pIcmpCloseHandle(NULL),
		m_pIcmpSendEcho(NULL),
		m_hPing(NULL),
		CICMP(uiOutTime)
	{
		ZeroMemory(&this->m_tIPHeader, sizeof (TIPHeader));
		ZeroMemory(&this->m_tICMPHeader, sizeof (TICMPHeader));
		
		this->m_hICMP = ::LoadLibrary(L"ICMP.dll");
		if (NULL == this->m_hICMP)
		{
			throw exception("加载动态链接库失败");
		}
		else
		{
			this->m_pEchoBuf = static_cast<PIP_ECHO_REPLY>(GlobalAlloc( GMEM_FIXED | GMEM_ZEROINIT, sizeof(IP_ECHO_REPLY) + BUF_LEN));
			if (NULL == this->m_pEchoBuf)
			{
				throw exception("内存分配失败");
			}
			else
			{
				//从ICMP.DLL中得到函数入口地址
				this->m_pIcmpCreateFile = (pfnHV)GetProcAddress(this->m_hICMP,  "IcmpCreateFile");
				this->m_pIcmpCloseHandle = (pfnBH)GetProcAddress(this->m_hICMP, "IcmpCloseHandle");
				this->m_pIcmpSendEcho = (pfnDHDPWPipPDD)GetProcAddress(this->m_hICMP, "IcmpSendEcho");

				if ((NULL == this->m_pIcmpCreateFile) || (NULL == this->m_pIcmpCloseHandle) || (NULL == this->m_pIcmpSendEcho))
				{
					throw exception("导出函数失败");
				}
				else
				{
					this->m_hPing = this->m_pIcmpCreateFile();					//打开Ping服务

					if (INVALID_HANDLE_VALUE == this->m_hPing)
					{
						throw exception("打开Ping服务失败");
					}
				}
			}
		}
	}
	catch (exception&)
	{
		throw;
	}

	CICMP::EEchoType CPing::Ping(const string& strDest, unsigned int uiTTL)
	{
		EEchoType eRet = ECHO_ERROR;
		string strIP = CheckIP(strDest) ? Trim(strDest) : GetHostAddress(strDest).front();

		this->m_usDelay = static_cast<unsigned short>(::GetTickCount());
		ZeroMemory(&this->m_tIPHeader, sizeof (TIPHeader));
		ZeroMemory(&this->m_tICMPHeader, sizeof (TICMPHeader));
		if (!this->Probe(strDest, uiTTL).empty() && ECHO_ERROR != (eRet = this->Catch(this->m_tIPHeader, this->m_tICMPHeader)))
		{
			this->m_usDelay = static_cast<unsigned short>(::GetTickCount() - this->m_usDelay) + 1;
		}
		else
		{
			this->m_tIPHeader.m_ucTTL = 0;
			this->m_usDelay = 0;
		}
		this->m_tICMPHeader.m_usICMPSeq = static_cast<unsigned short>(this->m_uiSeq);
		this->m_tIPHeader.m_uiDstIP = inet_addr(GetHostAddress("").front().c_str());
		this->m_tICMPHeader.m_uiICMPTimestamp = static_cast<unsigned int>(time(NULL));

		return eRet;
	}

	CICMP::EEchoType CPing::PingEx(const string& strDest, unsigned int uiTTL)
	{
		EEchoType eRet = ECHO_ERROR;
		string strDestIP;

		if (!strDest.empty() && !(strDestIP = CheckIP(strDest) ? Trim(strDest) : GetHostAddress(strDest).front()).empty())
		{
			IP_OPTION_INFORMATION tIPOptionInfo;

			ZeroMemory(&tIPOptionInfo, sizeof (IP_OPTION_INFORMATION));
			ZeroMemory(&this->m_tIPHeader, sizeof (TIPHeader));
			ZeroMemory(&this->m_tICMPHeader, sizeof (TICMPHeader));

			// 构造ping数据包
			char strPingBuffer[BUF_LEN];

			memset(strPingBuffer, '\xAA', sizeof(strPingBuffer));
			this->m_pEchoBuf->Data = strPingBuffer;
			this->m_pEchoBuf->DataSize = sizeof(strPingBuffer);

			tIPOptionInfo.Ttl = (0 == uiTTL ? this->m_pEchoBuf->Options.Ttl : static_cast<unsigned char>(uiTTL));

			// 发送ping数据包
			if (0 != this->m_pIcmpSendEcho(this->m_hPing, inet_addr(strDestIP.c_str()), strPingBuffer, sizeof(strPingBuffer), 0 == uiTTL ? NULL : &tIPOptionInfo, this->m_pEchoBuf, sizeof(IP_ECHO_REPLY) + sizeof(strPingBuffer), this->m_uiOutTime))
			{
				this->m_tIPHeader.m_ucTTL = this->m_pEchoBuf->Options.Ttl;
				this->m_usDelay = static_cast<unsigned short>(this->m_pEchoBuf->RoundTripTime);
				this->m_tIPHeader.m_uiSrcIP = this->m_pEchoBuf->Address;
				if (inet_addr(strDestIP.c_str()) == this->m_pEchoBuf->Address)
				{
					eRet = ECHO_FINISH;
				}
				else
				{
					eRet = ECHO_UNREACHABLE;
				}
			}
			else		//失败
			{
				this->m_tIPHeader.m_uiSrcIP = 0;
				this->m_tIPHeader.m_ucTTL = static_cast<unsigned char>(-1);
				this->m_usDelay = static_cast<unsigned short>(-1);
			}
			this->m_tIPHeader.m_uiDstIP = inet_addr(GetHostAddress("").front().c_str());
			this->m_tICMPHeader.m_usICMPSeq = static_cast<unsigned short>(++this->m_uiSeq);
			this->m_tICMPHeader.m_uiICMPTimestamp = static_cast<unsigned int>(time(NULL));
		}

		return eRet;
	}
}
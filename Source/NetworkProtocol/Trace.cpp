#include <iostream>
#include <string>
#include "NetworkProtocol/Trace.h"
#include "MyTools/MyUtilityTools.h"
#include "MyTools/MyNetTools.h"

namespace ICMP
{
	using std::cout;
	using std::endl;
	using ICMP::TIPHeader;
	using std::make_pair;
	using std::string;
	using MyTools::Trim;
	using MyTools::GetHostAddress;
	using MyTools::CheckIP;
	using MyTools::NumberToDecString;
	using MyTools::NetUIntToStringIP;

	//第一个参数表示超时时间
	//第二个参数表示最大TTL值
	CTrace::CTrace(unsigned int uiOutTime, unsigned short uiMaxTTL, unsigned char uiTryCount) try :
		CICMP(uiOutTime),
		m_oPing(uiOutTime),
		m_uiMaxTTL(uiMaxTTL),
		m_ucTryCount(uiTryCount),
		m_bSuccessful(false),
		m_bProbing(true)
	{}
	catch (...)
	{
		throw;
	}

	bool CTrace::Trace(const string& strDest, bool bDebug)
	{
		unsigned int uiTTL = 0;
		unsigned long ulDelay = 0;
		bool bFinish = false;
		TIPHeader tIPHeader;
		TICMPHeader tICMPHeader;
		EEchoType bRet = ECHO_ERROR;

		this->m_vecSuccessfulResult.clear();
		while (!bFinish && uiTTL++ < this->m_uiMaxTTL)
		{
			this->m_vecSuccessfulResult.push_back(make_pair(string(), 0));

			for (int i = 0; i < 3; ++i)			//对每个节点最多进行3次探测
			{
				ulDelay = ::GetTickCount();

				if (!this->Probe(strDest, uiTTL).empty() && ECHO_ERROR != (bRet = this->Catch(tIPHeader, tICMPHeader)))
				{
					ulDelay = ::GetTickCount() - ulDelay;

					this->m_vecSuccessfulResult.back().first = NetUIntToStringIP(tIPHeader.m_uiSrcIP);

					if (ECHO_FINISH == bRet)
					{
						bFinish = true;
					}
					break;
				}
			}

			if (bDebug)
			{
				std::cout << this->m_vecSuccessfulResult.back().first << std::endl;
			}
		}

		return bFinish;
	}

	bool CTrace::TraceEx(const string& strDest, bool bDebug)
	{
		unsigned int uiTTL = 0;
		CICMP::EEchoType eEcho = CICMP::ECHO_UNREACHABLE;
		string strDestIP = CheckIP(strDest) ? Trim(strDest) : GetHostAddress(strDest).front();
		vector<pair<string, unsigned short>> vecResult;

		vecResult.push_back(make_pair(ICMP::GetHostAddress("").front(), 0));			//添加源地址
		while (this->m_bProbing && !strDestIP.empty() && uiTTL++ < this->m_uiMaxTTL && CICMP::ECHO_FINISH != eEcho)
		{
			unsigned u = this->m_ucTryCount;				//失败次数

			do
			{
				eEcho = this->m_oPing.PingEx(strDestIP, uiTTL);
				if (CICMP::ECHO_ERROR != eEcho)
				{
					break;
				}
			} while (this->m_bProbing && --u > 0 && CICMP::ECHO_ERROR == eEcho);
			vecResult.push_back(make_pair(this->m_oPing.GetDestIP(), this->m_oPing.GetDelay()));
			if (bDebug)
			{
				cout << NumberToDecString(uiTTL) + '\t' + this->m_oPing.GetSourceIP() + '\t' + this->m_oPing.GetDestIP() + '\t' + NumberToDecString(this->m_oPing.GetDelay()) + '\n';
			}
		}

		this->m_bSuccessful = (eEcho == CICMP::ECHO_FINISH);
		if (this->m_bSuccessful)
		{
			if (this->m_vecLastResult.empty())
			{
				this->m_vecLastResult = vecResult;
			}
			else
			{
				this->m_vecLastResult = this->m_vecSuccessfulResult;
			}
			this->m_vecFailureResult.clear();
			this->m_vecSuccessfulResult = vecResult;
		}
		else
		{
			this->m_vecSuccessfulResult.clear();
			this->m_vecFailureResult = vecResult;
		}

		if (!this->m_bProbing)
		{
			this->m_bProbing = true;
			this->m_bSuccessful = false;
		}

		return this->m_bSuccessful;
	}
}
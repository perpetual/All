#ifndef TRACE_H
#define TRACE_H

#include <string>
#include <vector>
#include <utility>
#include "ICMP.h"
#include "Ping.h"

namespace ICMP
{
	using ICMP::CICMP;
	using ICMP::CPing;
	using std::string;
	using std::vector;
	using std::pair;

	class CTrace : public CICMP
	{
	public:
		//第一个参数表示超时时间
		//下一个参数表示最大TTL值
		//下一个参数表示探测的最大次数
		CTrace(unsigned int = 10000, unsigned short = 30, unsigned char = 3);

		//跟踪路由
		//第一个参数是目标IP地址或主机名
		//第二个参数是最大跳数
		//第三个参数表示是否显示调试信息
		bool Trace(const string&, bool = false);
		bool TraceEx(const string&, bool = false);

		//设置路由的超时时间（ms）
		void SetSocketOutTime(unsigned int uiOutTime)
		{
			this->m_oPing.SetSocketOutTime(uiOutTime);
		}

		//设置路由的最大跳数
		void SetMaxTTL(unsigned short uiMaxTTL)
		{
			this->m_uiMaxTTL = uiMaxTTL;
		}

		//设置失败尝试次数
		void SetTryCount(unsigned char ucTryCount)
		{
			this->m_ucTryCount = ucTryCount;
		}

		//获取前一次路由信息
		vector<pair<string, unsigned short>> GetLastRoute(void) const
		{
			return this->m_vecLastResult;
		}

		//获取最新路由信息
		vector<pair<string, unsigned short>> GetNewRoute(void) const
		{
			return this->m_vecSuccessfulResult;
		}

		//停止探测
		void Stop(void)
		{
			this->m_bProbing = false;
		}

	private:
		vector<pair<string, unsigned short>> m_vecLastResult;						//上一次成功的路由<IP，延迟（ms）>
		vector<pair<string, unsigned short>> m_vecSuccessfulResult;		//新路由<IP，延迟（ms）>
		vector<pair<string, unsigned short>> m_vecFailureResult;
		CPing m_oPing;												//用于探测路由
		unsigned short m_uiMaxTTL;							//最大生存周期
		unsigned char m_ucTryCount;						//探测次数
		bool m_bSuccessful;										//标记本次探测是否成功
		bool m_bProbing;											//是否需要继续探测
	};
}


#endif
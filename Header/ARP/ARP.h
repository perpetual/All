#ifndef ARP_ARP_H
#define ARP_ARP_H

#include "VersionControl.h"
#include <vector>
#include <string>

namespace ARP
{
	using std::vector;
	using std::string;

	class CARP
	{
	public:
		//获取指定IP地址对应的MAC地址
		//参数是IP地址
		static vector<unsigned short> GetMACAddress(const string&);
	};
}

#endif
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
		//��ȡָ��IP��ַ��Ӧ��MAC��ַ
		//������IP��ַ
		static vector<unsigned short> GetMACAddress(const string&);
	};
}

#endif
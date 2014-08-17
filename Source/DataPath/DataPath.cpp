#include "DataPath/DataPath.h"
#include "MyTools/MyNetTools.h"
#include "MyTools/MySocketTools.h"

namespace DataPath
{
	CDataPath::CDataPath(void) :
		m_sock(NULL)
	{}

	CDataPath::~CDataPath(void) {}

	bool CDataPath::SetNonBlock(bool b) const
	{
		return MyTools::SetSocketNonBlock(this->m_sock, b);
	}

	bool CDataPath::SetBroadcast(bool b) const
	{
		return MyTools::SetSocketBroadcast(this->m_sock, b);
	}

	bool CDataPath::SetReuse(bool b) const
	{
		return MyTools::SetSocketReuse(this->m_sock, b);
	}
}

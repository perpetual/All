#include "VersionControl.h"
#include "LogFile/LogFile.h"

namespace LogFile
{
	CLogFile::CLogFile(const string& strFileName, ios_base::openmode  flag, bool bOn) : m_ofLog(strFileName.c_str(), flag), m_bOn(bOn)
	{}

	CLogFile::operator bool(void) const
	{
		return this->m_ofLog.is_open();
	}

	CLogFile& CLogFile::operator <<( basic_ostream<char, char_traits<char> >& (*_Pfn)(basic_ostream<char, char_traits<char> >&))
	{
		if (this->m_bOn)
		{
			_Pfn(this->m_ofLog);
		}

		return *this;
	}

	void CLogFile::Switch(bool bOn)
	{
		this->m_bOn = bOn;
	}
}
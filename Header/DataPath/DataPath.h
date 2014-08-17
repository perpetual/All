#ifndef DATAPATH_DATA_PATH_H
#define DATAPATH_DATA_PATH_H

#include "VersionControl.h"
#include <string>
#include <exception>
#include "MyTools/MyNetTools.h"

namespace DataPath
{
	using std::string;
	using std::exception;
	using MyTools::CInitSocketLibrary;

	class CDataPath : public CInitSocketLibrary
	{
	public:
		CDataPath(void);
		virtual ~CDataPath(void) = 0;

		//�����׽���Ϊ�������׽���
		bool SetNonBlock(bool = true) const;

		//���öಥ����
		bool SetBroadcast(bool = true) const;

		//���õ�ַ����
		bool SetReuse(bool = true) const;

		SOCKET m_sock;
	private:
		CDataPath(const CDataPath&);
		CDataPath& operator =(const CDataPath&);
	};
}
#endif
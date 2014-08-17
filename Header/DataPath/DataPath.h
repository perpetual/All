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

		//设置套接字为非阻塞套接字
		bool SetNonBlock(bool = true) const;

		//设置多播属性
		bool SetBroadcast(bool = true) const;

		//设置地址复用
		bool SetReuse(bool = true) const;

		SOCKET m_sock;
	private:
		CDataPath(const CDataPath&);
		CDataPath& operator =(const CDataPath&);
	};
}
#endif
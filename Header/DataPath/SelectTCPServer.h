#ifndef MYTOOLS_SELECT_TCP_SERVER_H
#define MYTOOLS_SELECT_TCP_SERVER_H

#include "VersionControl.h"
#include "DataPath.h"
#include <string>

namespace DataPath
{
	using std::string;
	using DataPath::CDataPath;

	class CSelectTCPServer : public CDataPath
	{
	public:
		//��һ�����������������Ķ˿ں�
		//��һ�������Ǽ�����ַ
		//��һ�������ǽ��ջ������ĳ���
		CSelectTCPServer(unsigned short, const string& = "0.0.0.0", unsigned int = 1024);
		~CSelectTCPServer(void);

	private:
		char* m_pRecvBuf;
		unsigned int m_uiRecvBufSize;
	};
}

#endif
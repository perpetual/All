#include "CommonTest.h"
#include <string>

#include "DataPath/TCPServer.h"
using namespace DataPath;

#pragma comment (lib, "DataPath.lib")

int main(void)
{
	try
	{
		while (true)
		{
			CTCPServer o(2831);
			CTCPServer::CTCPClientSocket sock;
			cout << o.Accept(sock) << endl;
			cout << o.Receive(sock).first << endl;
		}
	}
	catch (exception& e)
	{
		cout << e.what() << endl;
	}
#ifdef __OS_VERSION_WINDOWS__
	system("pause");
#endif
	return 0;
}
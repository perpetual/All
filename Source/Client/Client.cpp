//#include "CommonTest.h"

#define DEBUG 0

#if 0 == DEBUG
#include <iostream>
#include "MyTools/MyUtilityTools.h"

#pragma comment (lib, "MyTools.lib")

using std::cout;
using std::endl;
using std::cerr;
using std::wcout;

#elif 1 == DEBUG
#include "NetStatDetector/NetStatDetector.h"
#pragma comment(lib, "NetStatDetector.lib")
#pragma comment(lib, "SafeThread.lib")
#pragma comment(lib, "XMLObject.lib")
#pragma comment(lib, "DataType.lib")
#pragma comment(lib, "ICMP.lib")
#pragma comment(lib, "MiniNGISTools.lib")
#pragma comment(lib, "NetProtocol.lib")
#pragma comment(lib, "iceutild.lib")
#pragma comment(lib, "iced.lib")
#ifdef _DEBUG
#pragma comment (lib, "xerces-c_2D.lib")
#pragma comment (lib, "xerces-c_3D.lib")
#pragma comment (lib, "xerces-depdom_2D.lib")
#else
#pragma comment (lib, "xerces-c_2.lib")
#pragma comment (lib, "xerces-c_3.lib")
#pragma comment (lib, "xerces-depdom_2.lib")
#endif
#elif 2 == DEBUG
#include "ICMPProbe/ICMPProbe.h"
#pragma comment(lib, "ICMPProbe.lib")
using namespace ICMPProbe;
void __stdcall Test(const char* pStr, int i)
{
	cout << pStr << ends << i << endl;
}

void __stdcall Finish(const void*, int len)
{
	cout << len << endl;
}

void __stdcall Finish(const void*, int len)
{
	cout << len << endl;
}
#endif

//int main(int argc, char* argv[], char* env[])
int main(void)
{
	try
	{
#if 0 == DEBUG
		wcout << MyTools::StrToWStr("Hello") << endl;
#elif 1 == DEBUG
		NetStatDetector::CNetStatDetector oDetctor;
		if (oDetctor)
		{
			MyTools::WaitForever();
		}
#elif 2 == DEBUG
		InitCallback(Test, Finish);
		AddTarget("121.48.164.1");
		AddTarget("121.195.178.238");
		//AddTarget("119.75.217.109");
		Start();
		Sleep(1000);
		Stop();
		cout << endl << "Hello World" << endl;
#endif
	}
	catch (std::exception& e)
	{
		cerr << e.what() << endl;
	}
	catch (...)
	{
		cerr << "δ֪�쳣" << endl;
	}
#ifdef __OS_VERSION_WINDOWS__
	system("pause");
#endif
	return EXIT_SUCCESS;
}

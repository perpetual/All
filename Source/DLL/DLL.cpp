#include <iostream>
#include "DLL/DLL.h"
//#include "LogFile/LogFile.h"

//#pragma comment (lib, "LogFile.lib")

namespace DLL
{
	using std::cout;
	using std::endl;

	void Test1(void)
	{
		cout << "Hello World1" << endl;
	}

	void Test2(void)
	{
		cout << "Hello World22222" << endl;
	}

	CDLL::CDLL(void)
	{
		cout << "Hello World11" << endl;
	}

	void CDLL::Test(void)
	{
		cout << "Hello World22" << endl;
	}

	//����
	HHOOK g_hKeyboard;
	HINSTANCE g_hInst = NULL;
	//�½�һ����
#pragma data_seg ("MySec")
	HWND g_hWnd = NULL;
#pragma data_seg ()

	//���������
#pragma comment (linker, "/section:MySec,RWS")

	LRESULT CALLBACK KeyboardProc(int iCode, WPARAM wParam, LPARAM lParam)
	{
		if (VK_F4 == wParam)
		{
			//::SendMessage(g_hWnd, WM_CLOSE, 0, 0);
			SendMessage(::GetActiveWindow(), WM_CLOSE, 0, 0);
			return ::CallNextHookEx(g_hKeyboard, iCode, wParam, lParam);
		}
		else
		{
			return 1;
		}
	}

	void SetHook(HWND hWnd)
	{
		g_hWnd = hWnd;

		//���μ�����Ϣ
		if (NULL == (g_hKeyboard = ::SetWindowsHookEx(WH_KEYBOARD, KeyboardProc, g_hInst, 0)))
		{
			exit(0);
		}
	}
}

//LogFile::CLogFile o("G:\\VS2008\\ALL\\Bin\\1.txt");

//��һ�������Ƕ�̬���ӿ�ģ����
BOOL WINAPI DllMain(HINSTANCE hDllHandle, DWORD nReason, LPVOID)
{
	using namespace DLL;

	if (DLL_PROCESS_ATTACH == nReason)		//ֻ�ڽ��̵�һ�μ���ʱ����
	{
		//cout << "���ض�̬��" << endl;
	}
	g_hInst = hDllHandle;

	//o << ::GetCurrentProcessId() << endl;

	if (DLL_PROCESS_DETACH == nReason)
	{
		::UnhookWindowsHookEx(g_hKeyboard);
		//cout << "ж�ض�̬��" << endl;
	}
	return TRUE;
}

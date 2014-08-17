#include "MyMFCTools/stdafx.h"
#include "MyMFCTools/MyMFCTools.h"

namespace MyMFCTools
{
	void RemoveMessage(HWND hWnd, unsigned int uiMinMsg, unsigned int uiMaxMsg)
	{
		MSG msg;

		while (::PeekMessage(&msg, hWnd, uiMinMsg, uiMaxMsg, PM_REMOVE))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
	}
}
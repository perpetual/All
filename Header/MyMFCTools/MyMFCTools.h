#ifndef MYMFCTOOLS_MY_MFC_TOOLS_H
#define MYMFCTOOLS_MY_MFC_TOOLS_H

namespace MyMFCTools
{
	//清空消息队列
	//第一个参数是消息队列所属的窗口，NULL表示清除本线程的所有消息
	//下两个参数本别表示消息的最大值和最小值
	void RemoveMessage(HWND, unsigned int = 0, unsigned int = 0);

#ifndef WARNING
#define WARNING(str) MessageBox(str, _T("警告"), MB_ICONWARNING)
#endif

#ifndef INFORMATION
#define INFOMATION(str) MessageBox(str, _T("消息"), MB_ICONINFORMATION)
#endif
}

#endif
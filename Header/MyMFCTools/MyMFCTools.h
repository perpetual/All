#ifndef MYMFCTOOLS_MY_MFC_TOOLS_H
#define MYMFCTOOLS_MY_MFC_TOOLS_H

namespace MyMFCTools
{
	//�����Ϣ����
	//��һ����������Ϣ���������Ĵ��ڣ�NULL��ʾ������̵߳�������Ϣ
	//���������������ʾ��Ϣ�����ֵ����Сֵ
	void RemoveMessage(HWND, unsigned int = 0, unsigned int = 0);

#ifndef WARNING
#define WARNING(str) MessageBox(str, _T("����"), MB_ICONWARNING)
#endif

#ifndef INFORMATION
#define INFOMATION(str) MessageBox(str, _T("��Ϣ"), MB_ICONINFORMATION)
#endif
}

#endif
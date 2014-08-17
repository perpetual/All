#ifndef DLL_DLL_H
#define DLL_DLL_H

#include "VersionControl.h"
#include <Windows.h>

namespace DLL
{
	extern "C" MY_DLL void Test1(void);
	MY_DLL void Test2(void);

	class CDLL
	{
	public:
		MY_DLL CDLL(void);
		void Test(void);
	protected:
	private:
	};

	//¹³×Ó
	MY_DLL void SetHook(HWND);

}

#endif
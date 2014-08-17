#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "MyCLib/MyCLib.h"
#include "MyCLib/MyString.h"

long AToL(char *pStr)
{
	long r = 0;
	int neg = 0;
	switch (*pStr)
	{
	case '-':
		neg = 1;
	case '+':
		++pStr;
		break;
	}

	while (isdigit(*pStr))
	{
		int n = *pStr++ - '0';

		if (0 != neg)			//如果是负数
		{
			n = -n;
		}
		r = 10 * r + n;
	}
	return r;
}

static void Process(long l, char* pBuf)
{
	long q = 0, r = 0;

	l = l >= 0 ? l : -l;
	q = l / 10;
	r = l % 10;

	if (q > 0)
	{
		Process(q, pBuf + 1);	//每次把低位放在pBuf+1的位置上
	}
	else
	{
		*(pBuf + 1) = '\0';
	}
	*pBuf = ("0123456789"[r]);
}

char* LToA(long l, char* pBuf)
{
	Process(l, pBuf);
	if (l < 0)
	{
		memcpy(pBuf + strlen(pBuf), "-\0", 2);
	}

	return ReverseStr(pBuf);
}

void VariableArg(int iCount, ...)
{
	va_list ap;
	int i = 0;

	va_start(ap, iCount);
	for (i = 0; i < iCount; ++i)
	{
#ifdef __OS_VERSION_WINDOWS__
		printf("%c ", va_arg(ap, char));
		puts("windows");
#elif defined(__OS_VERSION_LINUX__)
		printf("%d ", va_arg(ap, int));
		puts("linux");
#else
#error "UNKNOWN OS"
#endif
	}
	va_end(ap);
}

int MyPrintf(const char* pFormat, ...)
{
	va_list ap;
	int iRet = 0;

	va_start(ap, pFormat);
	iRet = vprintf(pFormat, ap);
	va_end(ap);
	return iRet;
}

//组合数
//最后一个参数用于存放结果，pBuf[0]用于存放组合数的位数
static void __Comb(int n, int r, char pBuf[])
{
	int i = 0;
	int j = 0;

	for (i = n; i >= r; --i)
	{
		//pBuf[r] = 4 - i + '0' + 1;
		pBuf[r] = (char)i + '0';
		if (r > 1)
		{
			__Comb(i - 1, r - 1, pBuf);
		}
		else
		{
			for (j = pBuf[0]; j > 0; --j)
			{
				putchar(pBuf[j]);
			}
			putchar('\n');
		}
	}
}

void Comb(int iN, int iR)
{
	char* pBuf = (char*)calloc(1, iR + 2);
	pBuf[0] = (char)iR;		//存放组合位数
	__Comb(iN, iR, pBuf);
	free(pBuf);
}

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "MyCLib/MyString.h"

char* MyStrRStr(char* pStr, const char*  pStrGroup)
{
	register char* pLast = NULL;
	register char* pCur = NULL;

	if (NULL == pStr || NULL == pStrGroup)
	{
		return NULL;
	}

	if ('\0' != *pStrGroup)
	{
		pCur = strstr(pStr, pStrGroup);
	}

	while (NULL != pCur)
	{
		pLast = pCur;
		pCur = strstr(pLast + 1, pStrGroup);
	}
	return pLast;
}

char* MyStrRChr(char* pStr, const char  chr)
{
	register char* pLast = NULL;
	register char* pCur = NULL;

	if (NULL == pStr)
	{
		return NULL;
	}


	if ('\0' != *pStr)
	{
		pCur = strchr(pStr, chr);
	}

	while (NULL != pCur)
	{
		pLast = pCur;
		pCur = strchr(pLast + 1, chr);
	}
	return pLast;
}

size_t MyStrLen(const char* pStr, size_t size)
{
	register size_t sz = 0;

	if (NULL == pStr)
	{
		return 0;
	}

	while (sz < size && '\0' != *pStr++)
	{
		++sz;
	}

	return sz;
}

char* MyStrCpy(char* pStrDst, const char* pStrSrc, size_t size)
{
	register size_t sz = 0;
	register char* pRet = pStrDst;

	if (NULL == pStrDst || NULL == pStrSrc)
	{
		return NULL;
	}

	while (sz < size && '\0' != (*pRet++ = *pStrSrc++))
	{
		sz++;
	}

	return pStrDst;
}

char* MyStrNCat(char* pStrDst, const char* pStrSrc, size_t size)
{
	size_t uDstLen = strlen(pStrDst);

	if (NULL == pStrDst || NULL == pStrSrc)
	{
		return NULL;
	}

	MyStrCpy(pStrDst + uDstLen, pStrSrc, size > uDstLen ? size - uDstLen : 0);
	return pStrDst;
}

char* MyStrCpyEnd(char* pStrDst, const char* pStrSrc)
{
	if (NULL == pStrDst || NULL == pStrSrc)
	{
		return NULL;
	}

	while ('\0' != (*pStrDst++ = *pStrSrc++));

	return pStrDst - 1;
}

char* MyStrNChr(char * pStr, int ch, int which)
{
	register char* pLast = NULL;
	register char* pCur = NULL;

	if (NULL == pStr)
	{
		return NULL;
	}

	if ('\0' != *pStr)
	{
		pCur = strchr(pStr, ch);
	}

	while (--which > 0 && NULL != pCur)
	{
		pLast = pCur;
		pCur = strchr(pLast + 1, ch);
	}

	return pCur;
}

int CountChr(const char* str, const char* chars)
{
	int iCount = 0;
	const char* p = NULL;

	if (NULL == str || NULL == chars)
	{
		return 0;
	}

	for (p = str; '\0' != *p; ++p)
	{
		if (NULL != strchr(chars, *p))
		{
			++iCount;
		}
	}

	return iCount;
}

char* ReverseStr(char* pBuf)
{
	char* pLow = pBuf;
	char* pHigh = pBuf + strlen(pBuf);
	char chTemp = '\0';

	if (pLow != pHigh)			//Èç¹û×Ö·û´®·Ç¿Õ
	{
		--pHigh;
		while (pLow <= pHigh)
		{
			chTemp = *pLow;
			*pLow = *pHigh;
			*pHigh = chTemp;
			++pLow;
			--pHigh;
		}
	}

	return pBuf;
}

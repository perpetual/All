#include <string.h>
#include <stdlib.h>
#include "Search.h"

static void KMPNext(const char* str, int iNexts[])
{
	int iLen = strlen(str);
	int i = 0;
	int j = -1;

	iNexts[0] = -1;
	while (i < iLen - 1)
	{
		if (-1 == j || str[i] == str[j])
		{
			++i;
			++j;
			//iNexts[i] = j;		//对模式中存在大量重复子串的时候，比如aaaab, abababc效率比较低
			if (str[i] != str[j])
			{
				iNexts[i] = j;
			}
			else
			{
				iNexts[i] = iNexts[j];
			}
		}
		else
		{
			j = iNexts[j];
		}
	}
}

int KMP(const char* pStr, const char* pPattern, int iPos)
{
	int iLenStr = strlen(pStr);
	int iLenPattern = strlen(pPattern);
	int j = 0;
	int* piNext = (int*)malloc(iLenPattern * sizeof (int));

	KMPNext(pPattern, piNext);

	while (iPos < iLenStr && j < iLenPattern)
	{
		if (-1 == j || pStr[iPos] == pPattern[j])
		{
			++iPos;
			++j;
		}
		else
		{
			j = piNext[j];
		}
	}

	free(piNext);
	if (j >= iLenPattern)
	{
		return iPos - iLenPattern;
	}
	else
	{
		return -1;
	}
}
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "MyCLib/Sorting.h"

void InsertSort(int a[], int iLen)
{
	if (NULL != a && iLen > 1)
	{
		int iTemp = 0;
		int i = 0;
		int j = 0;

		for (i = 1; i < iLen; ++i)
		{
			if (a[i] < a[i - 1])
			{
				iTemp = a[i];
				j = 0;
				for (j = i - 1; a[j] > iTemp; --j)
				{
					a[j + 1] = a[j];
				}
				a[j + 1] = iTemp;
			}
		}
	}
}

void BInsertSort(int a[], int iLen)
{
	if (NULL != a && iLen > 1)
	{
		int iTemp = 0;
		int iLow = 0, iHigh = 0, iMid = 0;
		int i = 0;
		int j = 0;

		for (i = 1; i < iLen; ++i)
		{
			if (a[i] < a[i - 1])
			{
				iTemp = a[i];
				iLow = 0;
				iHigh = i - 1;
				while (iLow <= iHigh)			//����ʱiLow��Ҫ�����λ��
				{
					iMid = (iLow + iHigh) / 2;
					if (iTemp < a[iMid])
					{
						iHigh = iMid - 1;
					}
					else
					{
						iLow = iMid + 1;
					}
				}
				j = 0;
				for (j = i - 1; j >= iLow; --j)
				{
					a[j + 1] = a[j];
				}
				a[iLow] = iTemp;
			}
		}
	}
}

//С������ð
void BubbleSort(int a[], int iLen)
{
	if (NULL != a && iLen > 1)
	{
		int iTemp = 0;
		int iFlag = 1;
		int i = 0;
		int j = 0;

		//�����Ҫ����n-1������
		for (i = 0; 0 != iFlag && i < iLen - 1; ++i)
		{
			iFlag = 0;
			for (j = iLen - 1; j > i; --j)		//������a[j]��a[j - 1]��ȣ���˿�����>i��Ϊ��������
			{
				if (a[j] < a[j - 1])
				{
					iTemp = a[j - 1];
					a[j - 1] = a[j];
					a[j] = iTemp;
					iFlag = 1;
				}
			}
		}
	}
}

void SelectSort(int a[], int iLen)
{
	if (NULL != a && iLen > 1)
	{
		int iMinPos = 0;
		int j = 0;
		int iTemp = 0;
		int i = 0;

		for (i = 0; i < iLen - 1; ++i)
		{
			iMinPos = i;
			for (j = i + 1; j < iLen; ++j)
			{
				if (a[j] < a[iMinPos])
				{
					iMinPos = j;
				}
			}

			if (i != j)
			{
				iTemp = a[i];
				a[i] = a[iMinPos];
				a[iMinPos] = iTemp;
			}
		}
	}
}

int Partition(int a[], int iLow, int iHigh)
{
	int iPivot = a[iLow];

	while (iLow < iHigh)
	{
		while (iLow < iHigh && a[iHigh] >= iPivot)
		{
			--iHigh;
		}
		if (iLow < iHigh)
		{
			a[iLow++] = a[iHigh];
		}
		while (iLow < iHigh && a[iLow] <= iPivot)
		{
			++iLow;
		}
		if (iLow < iHigh)
		{
			a[iHigh--] = a[iLow];
		}
	}
	a[iLow] = iPivot;
	return iLow;
}

void QSort(int a[], int iLow, int iHigh)
{
	if (iLow < iHigh)
	{
		int iPartition = Partition(a, iLow, iHigh);
		QSort(a, iLow, iPartition - 1);
		QSort(a, iPartition + 1, iHigh);
	}
}

void QuickSort(int a[], int iLen)
{
	if (iLen > 1)
	{
		QSort(a, 0, iLen - 1);
	}
}

//����Ϊһ���󶥶�
void HeapAdjust(int a[], int l, int h)
{
	if (NULL != a && l >=0 && h > l)
	{
		int temp = a[l];
		int i = 0;

		for (i = l * 2 + 1; i <= h; i *= 2 )		//���Žϴ����֦���в��ң�i���ڱ���l���ӽڵ㣬l��ʾ�ϴ�Ľڵ�
		{
			if (i < h && a[i] < a[i + 1])
			{
				++i;
			}

			if (temp >= a[i])
			{
				break;
			}
			else
			{
				a[l] = a[i];
				l = i;
			}
		}
		a[l] = temp;		//���ʼ�ĶѶ�Ԫ�ط�����ȷ��λ��
	}
}

void HeapSort(int a[], int iLen)
{
	int i = 0;
	int temp = 0;

	if (NULL != a && iLen > 0)
	{
		for (i = iLen / 2 - 1; i >= 0; --i)		//�ӵ�һ����Ҷ�ӽڵ㿪ʼɸѡ�Խ�����ʼ�ѣ��Ӻ���ǰɸѡ��
		{
			HeapAdjust(a, i, iLen - 1);		//�Ӻ�벿����ǰ�벿����չ
		}

		for (i = iLen - 1; i > 0; --i)		//ɸѡ�����Ѷ�Ԫ�����βԪ�ؽ���
		{
			temp = a[0];
			a[0] = a[i];
			a[i] = temp;
			HeapAdjust(a, 0, i - 1);		//����ǰ�벿��
		}
	}
}

//�������a[iLow...iMid]��a[iMid + 1...iHigh]�鲢Ϊ�����b[iLow...iHigh]
static void Merge(int a[], int b[], int iLow, int iMid, int iHigh)
{
	int iB = iLow,  i1 = iLow, i2 = iMid + 1;

	for (; i1 <= iMid && i2 <= iHigh; ++iB)
	{
		if (a[i1] <= a[i2])
		{
			b[iB] = a[i1++];
		}
		else
		{
			b[iB] = a[i2++];
		}
	}

	while (i1 <= iMid)
	{
		b[iB++] = a[i1++];
	}
	while (i2 <= iHigh)
	{
		b[iB++] = a[i2++];
	}
}

//��һ������ΪԴ����
//��һ��������Ŀ������
//��һ����������ʱ����
static void MSort(int a[], int b[], int iLow, int iHigh)
{
	int iMid = 0;
	int* c = NULL;
	if (iLow == iHigh)
	{
		b[iLow] = a[iLow];
	}
	else
	{
		iMid = (iLow + iHigh) / 2;
		c = (int*)malloc((iHigh + 1) * sizeof (int));
		MSort(a, c, iLow, iMid);
		MSort(a, c, iMid + 1, iHigh);
		Merge(c, b, iLow, iMid, iHigh);
		free(c);
	}
}

void MergeSort(int a[], int iLen)
{
	if (NULL != a && iLen > 1)
	{
		MSort(a, a, 0, iLen - 1);
	}
}

static const size_t MAX_KEYS = 10;		//����ֵ
static const int RADIX = 10;				//����

struct TCell
{
	char cKeys[10];
	unsigned int uiValue;
	struct TCell* pNext;
};

//����
static void Distribute(struct TCell* pCell, int iIndex, struct TCell* pFront[], struct TCell* pRear[])
{
	char cKey = 0;

	while (NULL != pCell)
	{
		cKey = pCell->cKeys[iIndex];
		if (NULL == pFront[cKey])
		{
			pFront[cKey] = pCell;
		}
		else
		{
			pRear[cKey]->pNext = pCell;
		}
		pRear[cKey] = pCell;
		pCell = pCell->pNext;
	}
}

//�ռ�
static void Collect(struct TCell** ppCell, struct TCell* pFront[], struct TCell* pRear[])
{
	struct  TCell* pRearTemp = NULL;
	int i = 0;

	//�ҵ���һ���ǿն���
	for (i = 0; i < RADIX; ++i)
	{
		if (NULL != (*ppCell = pFront[i]))
		{
			pRearTemp = pRear[i];
			break;
		}
	}

	for (++i; i < RADIX; ++i)
	{
		if (NULL != pFront[i])
		{
			pRearTemp->pNext = pFront[i];
			pRearTemp = pRear[i];
			pRearTemp->pNext = NULL;
		}
	}
}

float RadixSort(int a[], int iLen)
{
	struct TCell* pCellTemp = NULL;
	struct TCell* pCell = NULL;
	int i = 0;
	int j = 0;
	size_t sz = 0;
	struct TCell** pFront = NULL;
	struct TCell** pRear = NULL;
	float fTime = 0.0f;
	clock_t clk = 0;
	struct TCell* pTemp = NULL;

	for (i = iLen - 1; i >= 0; --i)
	{
		pCellTemp = (struct TCell*)malloc(sizeof (struct TCell));
		memset(pCellTemp, '\0', sizeof (struct TCell));
		pCellTemp->uiValue = a[i];
		pCellTemp->pNext = NULL;
		for (j = MAX_KEYS - 1; j >= 0; --j)
		{
			pCellTemp->cKeys[j] = a[i] % 10;
			a[i] /= 10;
		}
		pCellTemp->pNext = pCell;
		pCell = pCellTemp;
	}

	sz = sizeof (struct TCell*) * RADIX;
	pFront = (struct TCell**)malloc(sz);
	pRear = (struct TCell**)malloc(sz);
	fTime = 0.0f;
	clk = clock();
	for (i = MAX_KEYS - 1; i >= 0; --i)
	{
		memset(pFront, '\0', sz);
		memset(pRear, '\0', sz);
		Distribute(pCell, i, pFront, pRear);
		Collect(&pCell, pFront, pRear);
	}
	fTime = (float)(clock() - clk) / CLOCKS_PER_SEC;
	free(pFront);
	free(pRear);

	pTemp = NULL;
	while (NULL != pCell)
	{
		*a++ = pCell->uiValue;
		pTemp = pCell;
		pCell = pCell->pNext;
		free(pTemp);
	}
	return fTime;
}

void ShellInsert(int a[], int iLenA, int iInc)
{
	int iTemp = 0;
	int i = 0;
	int j = 0;

	for (i = iInc; i < iLenA; ++i)
	{
		iTemp = a[i];
		for (j = i - iInc; j >= 0 && iTemp < a[j]; j -= iInc)
		{
			a[j + iInc] = a[j];
		}
		a[j + iInc] = iTemp;
	}
}

void ShellSort(int a[], int iLen)
{
	//int b[] = {9, 5, 3, 2, 1};
	int b[] = {40, 13, 4, 1};
	const int sz = sizeof (b) / sizeof (int);
	int i = 0;

	for (i = 0; i < sz; ++i)
	{
		ShellInsert(a, iLen, b[i]);
	}
}

void Rearrange(int a[], int addr[], int iLen)
{
	int iValue = 0;
	int iIndex = 0;
	int iTemp = 0;
	int i = 0;

	if (NULL != a && NULL != addr && iLen > 1)
	{
		for (i = 0; i < iLen - 1; ++i)
		{
			iIndex = i; iValue = a[i];		//��¼��һ��Ҫ�����λ�ú�ֵ
			if (addr[i] != i)
			{
				while (addr[iIndex] != i)
				{
					iTemp = addr[iIndex];		//ȡֵλ��
					a[iIndex] = a[iTemp];		//�ƶ�ֵ
					addr[iIndex] = iIndex;		//��ǰλ�����ƶ�
					iIndex = iTemp;					//��һ��Ҫ�����λ��
				}
				a[iIndex] = iValue;
				addr[iIndex] = iIndex;
			}
		}
	}
}

static int MAX_KEY = 0x7FFFFFFF;

//�ش�Ҷ�ӽڵ�a[s]�����ڵ�a[0]��·������������
//��һ��������˳��洢�İ�����
//��һ�������ǰ�������Ҷ�ӽڵ�
//��һ��������Ҷ�ӽڵ�����
//��һ�������ǹ鲢��·��
static void Adjust(int a[], int pTree[], int iS, const int ciK)
{
	int iT = (iS + ciK) / 2;		//a[t]��b[iS]��˫�׽ڵ�
	int iTemp = 0;

	while (iT > 0)
	{
		if (ciK != iS && (ciK == pTree[iT] || a[iS] > a[pTree[iT]]))
		{
			iTemp = iS;
			iS = pTree[iT];
			pTree[iT] = iTemp;
		}
		iT /= 2;
	}
	pTree[0] = iS;
}

//��������������ȫ��������
static void CreateLoserTree(int a[], int pTree[], const int ciK)
{
	int i = 0;

	for (i = 0; i < ciK; ++i)
	{
		pTree[i] = ciK;
	}

	for (i = ciK - 1; i >= 0; --i)
	{
		Adjust(a, pTree, i, ciK);
	}
}

//k·�鲢
void KMergeSort(int a[], const int ciK)
{
	int i = 0;
	int iTemp = 0;
	int* pTree = (int*)malloc(sizeof (int) * ciK);
	int* pBuf = (int*)malloc(sizeof (int) * ciK);

	CreateLoserTree(a, pTree, ciK);
	for (i = 0; i < ciK; ++i)
	{
		iTemp = pTree[0];
		pBuf[i] = a[iTemp];
		a[iTemp] = MAX_KEY;
		Adjust(a, pTree, iTemp, ciK);
	}

	memcpy(a, pBuf, sizeof (int) * ciK);
	free(pTree);
	free(pBuf);
}
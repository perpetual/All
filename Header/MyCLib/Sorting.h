#ifndef MYCLIB_SORTING_H
#define MYCLIB_SORTING_H

#ifdef __cplusplus
extern "C"
{
#endif

//��������
void InsertSort(int [], int);

//�۰��������
void BInsertSort(int [], int);

//ð������
void BubbleSort(int [], int);

//ѡ������
void SelectSort(int [], int);

//��������
void QuickSort(int [], int);

//������
void HeapSort(int [], int);

//�鲢����
void MergeSort(int [], int);

//K·�鲢����
void KMergeSort(int [], const int iK);

//��������
//�������������ʱ��
float RadixSort(int [], int);

//ϣ������
void ShellSort(int [], int);

//�����㷨
void Rearrange(int [], int [], int);

#ifdef __cplusplus
}
#endif

#endif
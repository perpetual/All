#ifndef MYCLIB_SORTING_H
#define MYCLIB_SORTING_H

#ifdef __cplusplus
extern "C"
{
#endif

//插入排序
void InsertSort(int [], int);

//折半插入排序
void BInsertSort(int [], int);

//冒泡排序
void BubbleSort(int [], int);

//选择排序
void SelectSort(int [], int);

//快速排序
void QuickSort(int [], int);

//堆排序
void HeapSort(int [], int);

//归并排序
void MergeSort(int [], int);

//K路归并排序
void KMergeSort(int [], const int iK);

//基数排序
//返回排序所需的时间
float RadixSort(int [], int);

//希尔排序
void ShellSort(int [], int);

//重排算法
void Rearrange(int [], int [], int);

#ifdef __cplusplus
}
#endif

#endif
#ifndef SORTING_SORTING_H
#define SORTING_SORTING_H

#include <vector>
#include <deque>
#include <algorithm>
#include "MyTools/MyTools.h"

namespace MyAlgorithm
{
	using std::vector;
	using std::deque;

	//插入排序
	template <typename T>
	class CInsertSort
	{
	public:
		CInsertSort(vector<T>& vec)
		{
			if (!vec.empty())
			{
				deque<T> deq(vec.begin(), vec.end());
				deq.push_front(0);
				for (typename vector<T>::size_type i = 2; i < deq.size(); ++i)
				{
					if (deq[i] < deq[i - 1])
					{
						deq[0] = deq[i];			//第一个位置充当哨兵
						typename vector<T>::size_type j = 0;
						for (j = i - 1; deq[j] > deq[0]; --j)
						{
							deq[j + 1] = deq[j];
						}
						deq[j + 1] = deq[0];
					}
				}
				deq.pop_front();
				vec.assign(deq.begin(), deq.end());
			}
		}
	};

	//折半插入排序
	//在已排序序列中用折半查找插入位置
	template <typename T>
	class CBInsertSort
	{
	public:
		CBInsertSort(vector<T>& vec)
		{
			if (!vec.empty())
			{
				deque<T> deq(vec.begin(), vec.end());

				deq.push_front(0);		//加入哨兵位
				for (typename vector<T>::size_type i = 2; i < deq.size(); ++i)
				{
					deq[0] = deq[i];		//令待插入数据作为哨兵（待插入数据）
					typename vector<T>::size_type low = 1, high = i - 1;
					while (low <= high)			//在待插入数据之前的位置寻找插入点（如果不在low，high相等时再比较一次，则不能确定插入该位置之前还是之后，该位置由low指示）
					{
						typename vector<T>::size_type m = (low + high) / 2;
						if (deq[0] < deq[m])
						{
							high = m - 1;
						}
						else
						{
							low = m + 1;
						}
					}

					for (typename vector<T>::size_type j = i - 1; j >= low; --j)		//移动待插入数据所在位置i之前的元素
					{
						deq[j + 1] = deq[j];
					}
					deq[low] = deq[0];
				}
				deq.pop_front();
				vec.assign(deq.begin(), deq.end());
			}
		}
	};

	//冒泡排序
	template <typename T>
	class CBubbleSort
	{
	public:
		CBubbleSort(vector<T>& vec)
		{
			if (!vec.empty())
			{
				bool b = true;		//是否有交换
				for (typename vector<T>::size_type i = 0; b && i < vec.size(); ++i)
				{
					b = false;
					for (typename vector<T>::size_type j = vec.size() - 1; j > i; --j)
					{
						if (vec[j] < vec[j - 1])
						{
							std::swap(vec[j], vec[j - 1]);
							b = true;
						}
					}
				}
			}
		}
	};

	//快速排序
	template <typename T>
	class CQuickSort
	{
	public:
		CQuickSort(vector<T>& vec)
		{
			if (!vec.empty())
			{
				QuickSort(vec, 0, vec.size() - 1);
			}
		}
	private:
		//划分数组
		//参数代表数组的上下标
		T Partition(vector<T>& vec, typename vector<T>::size_type begin, typename vector<T>::size_type end)
		{
			T tPivot = vec[begin];		//每个子序列的第一个元素为枢轴

			while (begin < end)
			{
				while (begin < end && vec[end] >= tPivot)		//先移动尾指针
				{
					--end;
				}
				if (begin < end)
				{
					vec[begin++] = vec[end];
				}
				while (begin < end && vec[begin] <= tPivot)
				{
					++begin;
				}
				if (begin < end)
				{
					vec[end--] = vec[begin];
				}
			}//while
			vec[begin] = tPivot;

			return begin;
		}

		//快速排序
		//参数代表数组的上下标
		void QuickSort(vector<T>& vec, typename vector<T>::size_type tBegin, typename vector<T>::size_type tEnd)
		{
			T tPivot = NULL;

			if (tBegin < tEnd)
			{
				tPivot = this->Partition(vec, tBegin, tEnd);
				QuickSort(vec, tBegin, tPivot - 1);
				QuickSort(vec, tPivot + 1, tEnd);
			}
		}
	};

	//选择排序
	template <typename T>
	class CSelectSort
	{
	public:
		CSelectSort(vector<T>& vec)
		{
			if (!vec.empty())
			{
				for (typename vector<T>::size_type i = 0; i < vec.size() - 1; ++i)
				{
					typename vector<T>::size_type szCurMinPos = i;
					//寻找最小值的位置
					typename vector<T>::size_type j = i + 1;
					for (; j < vec.size(); ++j)
					{
						if (vec[j] < vec[szCurMinPos])
						{
							szCurMinPos = j;
						}
					}
					if (i != j)
					{
						std::swap(vec[szCurMinPos], vec[i]);
					}
				}
			}
		}
	};

	//归并排序
	//把一个序列分割为两个序列
	template <typename T>
	class CMergeSort
	{
	public:
		CMergeSort(vector<T>& vec)
		{
			if (!vec.empty())
			{
				this->MSort(vec, vec, 0, vec.size() - 1);
			}
		}
	private:
		void MSort(const vector<T>& vecSrc, vector<T>& vecDst1, typename vector<T>::size_type begin, typename vector<T>::size_type end)
		{
			if (begin == end)
			{
				vecDst1[begin] = vecSrc[end];
			}
			else
			{
				typename vector<T>::size_type mid = (begin + end) / 2;
				vector<T> vecDst2(vecSrc.size());

				this->MSort(vecSrc, vecDst2, begin, mid);
				this->MSort(vecSrc, vecDst2, mid + 1, end);
				this->Merge(vecDst2, vecDst1, begin, mid, end);
			}
		}

		void Merge(const vector<T>& vecSrc, vector<T>& vecDst, typename vector<T>::size_type low, typename vector<T>::size_type mid, typename vector<T>::size_type high)
		{
			typename vector<T>::size_type first = low;
			typename vector<T>::size_type dstIndex = 0;
			typename vector<T>::size_type second = 0;

			for (dstIndex = first, second = mid + 1; first <= mid && second <= high; ++dstIndex)
			{
				if (vecSrc[first] <= vecSrc[second])
				{
					vecDst[dstIndex] = vecSrc[first++];
				}
				else
				{
					vecDst[dstIndex] = vecSrc[second++];
				}
			}

			if (first <= mid)
			{
				for (typename vector<T>::size_type i = first; i <= mid; ++i)
				{
					vecDst[dstIndex++] = vecSrc[i];
				}
			}
			else if (second <= high)
			{
				for (typename vector<T>::size_type i = second; i <= high; ++i)
				{
					vecDst[dstIndex++] = vecSrc[i];
				}
			}
		}
	};

	//堆排序
	template <typename T>
	class CHeapSort
	{
	public:
		CHeapSort(vector<T>& vec)
		{
			this->HeapSort(vec);
		}

	private:
		//调整成为一个大顶堆
		void HeapAdjust(vector<T>& vec, typename vector<T>::size_type szS, typename vector<T>::size_type szE)
		{
			T temp = vec[szS];			//保存堆的第一个节点

			for (typename vector<T>::size_type sz = 2 * szS + 1; sz <= szE; sz *= 2)		//沿着较大的树枝进行
			{
				if (sz < szE && vec[sz] < vec[sz  + 1])		//寻找二叉树两个节点值较大的那个索引
				{
					++sz;
				}

				if (temp >= vec[sz])		//如果父节点的值不小于其两个子节点，则结束循环
				{
					break;
				}
				else
				{
					vec[szS] = vec[sz];
					szS = sz;
				}
			}
			vec[szS] = temp;		//把原来的堆顶元素放在合适的位置上
		}

		void HeapSort(vector<T>& vec)
		{
			for (typename vector<T>::size_type sz = vec.size() / 2 - 1; sz >= 0; --sz)			//从第一个非叶子节点开始进行处理，调整为一个大顶堆
			{
				this->HeapAdjust(vec, sz, vec.size() - 1);
				if (0 == sz)
				{
					break;
				}
			}

			for (typename vector<T>::size_type sz = vec.size() - 1; sz > 0; --sz)
			{
				std::swap(vec[0], vec[sz]);		//把大顶堆的第一个元素与最后一个元素交换，即把最大值放在最后一个位置
				this->HeapAdjust(vec, 0, sz - 1);		//把剩下的n-1个节点重新调整为一个堆
			}
		}
	};
}

#endif

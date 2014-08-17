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

	//��������
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
						deq[0] = deq[i];			//��һ��λ�ó䵱�ڱ�
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

	//�۰��������
	//�����������������۰���Ҳ���λ��
	template <typename T>
	class CBInsertSort
	{
	public:
		CBInsertSort(vector<T>& vec)
		{
			if (!vec.empty())
			{
				deque<T> deq(vec.begin(), vec.end());

				deq.push_front(0);		//�����ڱ�λ
				for (typename vector<T>::size_type i = 2; i < deq.size(); ++i)
				{
					deq[0] = deq[i];		//�������������Ϊ�ڱ������������ݣ�
					typename vector<T>::size_type low = 1, high = i - 1;
					while (low <= high)			//�ڴ���������֮ǰ��λ��Ѱ�Ҳ���㣨�������low��high���ʱ�ٱȽ�һ�Σ�����ȷ�������λ��֮ǰ����֮�󣬸�λ����lowָʾ��
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

					for (typename vector<T>::size_type j = i - 1; j >= low; --j)		//�ƶ���������������λ��i֮ǰ��Ԫ��
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

	//ð������
	template <typename T>
	class CBubbleSort
	{
	public:
		CBubbleSort(vector<T>& vec)
		{
			if (!vec.empty())
			{
				bool b = true;		//�Ƿ��н���
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

	//��������
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
		//��������
		//����������������±�
		T Partition(vector<T>& vec, typename vector<T>::size_type begin, typename vector<T>::size_type end)
		{
			T tPivot = vec[begin];		//ÿ�������еĵ�һ��Ԫ��Ϊ����

			while (begin < end)
			{
				while (begin < end && vec[end] >= tPivot)		//���ƶ�βָ��
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

		//��������
		//����������������±�
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

	//ѡ������
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
					//Ѱ����Сֵ��λ��
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

	//�鲢����
	//��һ�����зָ�Ϊ��������
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

	//������
	template <typename T>
	class CHeapSort
	{
	public:
		CHeapSort(vector<T>& vec)
		{
			this->HeapSort(vec);
		}

	private:
		//������Ϊһ���󶥶�
		void HeapAdjust(vector<T>& vec, typename vector<T>::size_type szS, typename vector<T>::size_type szE)
		{
			T temp = vec[szS];			//����ѵĵ�һ���ڵ�

			for (typename vector<T>::size_type sz = 2 * szS + 1; sz <= szE; sz *= 2)		//���Žϴ����֦����
			{
				if (sz < szE && vec[sz] < vec[sz  + 1])		//Ѱ�Ҷ����������ڵ�ֵ�ϴ���Ǹ�����
				{
					++sz;
				}

				if (temp >= vec[sz])		//������ڵ��ֵ��С���������ӽڵ㣬�����ѭ��
				{
					break;
				}
				else
				{
					vec[szS] = vec[sz];
					szS = sz;
				}
			}
			vec[szS] = temp;		//��ԭ���ĶѶ�Ԫ�ط��ں��ʵ�λ����
		}

		void HeapSort(vector<T>& vec)
		{
			for (typename vector<T>::size_type sz = vec.size() / 2 - 1; sz >= 0; --sz)			//�ӵ�һ����Ҷ�ӽڵ㿪ʼ���д�������Ϊһ���󶥶�
			{
				this->HeapAdjust(vec, sz, vec.size() - 1);
				if (0 == sz)
				{
					break;
				}
			}

			for (typename vector<T>::size_type sz = vec.size() - 1; sz > 0; --sz)
			{
				std::swap(vec[0], vec[sz]);		//�Ѵ󶥶ѵĵ�һ��Ԫ�������һ��Ԫ�ؽ������������ֵ�������һ��λ��
				this->HeapAdjust(vec, 0, sz - 1);		//��ʣ�µ�n-1���ڵ����µ���Ϊһ����
			}
		}
	};
}

#endif

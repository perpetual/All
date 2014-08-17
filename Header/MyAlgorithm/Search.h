#ifndef MYALGORITHM_SEARCH_H
#define MYALGORITHM_SEARCH_H

namespace MyAlgorithm
{
	//���ֲ���
	template <typename T>
	bool BinarySearch(const vector<T>& vec, T tVal)
	{
		if (vec.size() > 0)
		{
			vector<T> vecTemp(vec);
			sort(vecTemp.begin(), vecTemp.end());
			vecTemp = vector<T>(vecTemp.begin(), unique(vecTemp.begin(), vecTemp.end()));
			typename vector<T>::size_type begin = 0;
			typename vector<T>::size_type end = vecTemp.size() - 1;
			typename vector<T>::size_type mid = 0;

			//while (begin <= end && end < vec.size())
			while (begin < end && end < vec.size())			//��ò��÷ǶԳƱ߽磬�Ա㷽��ظ���Ϊ��ָ����ʽ
			{
				mid = (begin + end) / 2;
				if (tVal == vecTemp[mid])
				{
					return true;
				}
				else
				{
					if (tVal < vecTemp[mid])
					{
						//end = mid - 1;
						end = mid;
					}
					else
					{
						begin = mid + 1;
					}
				}
			}
		}

		return false;
	}

	//��ϣ����
	
}

#endif
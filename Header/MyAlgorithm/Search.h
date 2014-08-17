#ifndef MYALGORITHM_SEARCH_H
#define MYALGORITHM_SEARCH_H

namespace MyAlgorithm
{
	//二分查找
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
			while (begin < end && end < vec.size())			//最好采用非对称边界，以便方便地改造为纯指针形式
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

	//哈希查找
	
}

#endif
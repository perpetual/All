#ifndef MYALGORITHM_HASH_TABLE_H
#define MYALGORITHM_HASH_TABLE_H

#include "Handle/SmartPointer.h"
#include "List.h"

namespace MyAlgorithm
{
	using Handle::CSmartPointer;

	template <typename T, size_t szTabLen = 13>
	class CHashTable
	{
	public:
		void Insert(const T&);
		T* Find(const T&);
		void Display(void);
	private:
		CSortSLList<T> m_tab[szTabLen];
	};

	template <typename T, size_t szTabLen>
	void CHashTable<T, szTabLen>::Insert(const T &t)
	{
		this->m_tab[t % szTabLen].Insert(t);
	}

	template <typename T, size_t szTabLen>
	T* CHashTable<T, szTabLen>::Find(const T& t)
	{
		return this->m_tab[t % szTabLen].Find(t);
	}

	template <typename T, size_t szTabLen>
	void CHashTable<T, szTabLen>::Display(void)
	{
		for (int i = 0; i < szTabLen; ++i)
		{
			this->m_tab[i].Display();
		}
	}
}

#endif
#ifndef TEMPLATE_ITERATOR_H
#define TEMPLATE_ITERATOR_H

#include <iostream>
#include "MyTools/MyTools.h"

namespace Template
{
	using std::istream;
	using std::ostream;

	//抽象基类
	template <typename T>
	class CIterator
	{
	public:
		virtual bool Valid(void) const = 0;
		virtual T Next(void) = 0;
		virtual ~CIterator(void) = 0 {}
	};

	//数组迭代器
	template <typename T>
	class CArrayIterator : public CIterator<T>
	{
	public:
		CArrayIterator(T*, size_t);
		bool Valid(void) const;
		T Next(void);
	private:
		T* m_pData;
		size_t m_szLen;
	};

	template <typename T>
	CArrayIterator<T>::CArrayIterator(T* p, size_t sz) :
		m_pData(p),
		m_szLen(sz)
	{}

	template <typename T>
	bool CArrayIterator<T>::Valid(void) const
	{
		return this->m_szLen > 0;
	}

	template <typename T>
	T CArrayIterator<T>::Next(void)
	{
		--this->m_szLen;
		return *this->m_pData++;
	}

	//输入流迭代器
	template <typename T>
	class CIStreamIterator : public CIterator<T>
	{
	public:
		CIStreamIterator(istream&);
		bool Valid(void) const;
		T Next(void);
	private:
		CIStreamIterator(const CIStreamIterator&);
		CIStreamIterator& operator =(const CIStreamIterator&);
		istream& m_istr;
		T m_tData;
	};

	template <typename T>
	CIStreamIterator<T>::CIStreamIterator(istream& istr) :
		m_istr(istr),
		m_tData(0)
	{
		this->m_istr >> this->m_tData;
	}

	template <typename T>
	bool CIStreamIterator<T>::Valid(void) const
	{
		return this->m_istr.good();
	}

	template <typename T>
	T CIStreamIterator<T>::Next(void)
	{
		T tResult = this->m_tData;
		this->m_istr >> this->m_tData;
		return tResult;
	}

	//求和函数
	template <typename T>
	T Sum(CIterator<T>& it)
	{
		T tRet = 0;

 		while (it.Valid())
		{
			tRet += it.Next();
		}
		return tRet;
	}
}

#endif
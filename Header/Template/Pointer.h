#ifndef TEMPLATE_POINTER_H
#define TEMPLATE_POINTER_H

#include "VersionControl.h"
#include "Handle/Handle.h"

namespace Template
{
	using Utility::exceptionx;

	template <typename T> class CPointer;
	template <typename T> class CConstPointer;
	template <typename T> class CArray;

	template <typename T>
	class CArrayData : public Handle::CHandle<T, true>
	{
		friend class CPointer<T>;
		friend class CConstPointer<T>;
		friend class CArray<T>;
	public:
		CArrayData(size_t sz = 0) : m_size(sz)
		{
			this->m_pBase = new T[this->m_size];
		}

		const T& operator [](size_t szIndex) const
		{
			if (szIndex < this->m_size && NULL != this->m_pBase)
			{
				return this->m_pBase[szIndex];
			}
			else
			{
				throw exceptionx("Error Index");
			}
		}
		T& operator [](size_t szIndex)
		{
			if (szIndex < this->m_size && NULL != this->m_pBase)
			{
				return this->m_pBase[szIndex];
			}
			else
			{
				throw exceptionx("Error Index");
			}
		}

		void Resize(size_t szSize)
		{
			if (this->m_size != szSize)
			{
				T* pOldData = this->m_pBase;

				this->m_pBase = new T[szSize];
				this->Copy(pOldData, szSize > this->m_size ? this->m_size : szSize);
				delete[] pOldData;
				this->m_size = szSize;
			}
		}

		void Reserve(size_t szNewSize)
		{
			size_t szSize = this->m_size;

			if (0 == szSize)
			{
				szSize = 1;
			}

			while (szSize <= szNewSize)
			{
				szSize *= 1.5;
			}
			this->Resize(szSize);
		}
	private:
		//禁止复制和赋值
		CArrayData(const CArrayData&);
		CArrayData& operator =(const CArrayData&);
		void Copy(T* pT, size_t szSize)
		{
			for (size_t sz = 0; sz < szSize; ++sz)
			{
				this->m_pBase[sz] = pT[sz];
			}
		}

		void Clone(const CArrayData<T>& a)
		{
			delete[] this->m_pBase;
			this->m_pBase = new T[this->m_size = a.m_size];
			this->Copy(a.m_pBase, this->m_size);
		}


		//获取引用计数器的值
		unsigned int Count(void) {return this->m_oUseCount;}
		//引用计数增1
		void Inc(void) {++this->m_oUseCount;}
		//引用计数减1
		void Dec(void) {--this->m_oUseCount;}

		size_t m_size;
	};

	template <typename T>
	class CArray
	{
		friend class CPointer<T>;
		friend class CConstPointer<T>;
	public:
		CArray(size_t sz = 0) :
		  m_data(new CArrayData<T>(sz))
		{}

		~CArray(void)
		{
			if (1 == this->m_data->Count())
			{
				delete this->m_data;
			}
			else
			{
				this->m_data->Dec();
			}
		}

		void Resize(size_t szSize)
		{
			this->m_data->Resize(szSize);
		}

		void Reserve(size_t szSize)
		{
			if (szSize >= this->m_data->m_size)
			{
				this->m_data->Resize(szSize);
			}
		}

		const T& operator [](size_t szIndex) const
		{
			return (*this->m_data)[szIndex];
		}

		T& operator [](size_t szIndex)
		{
			return (*this->m_data)[szIndex];
		}

		CArray(const CArray& a) :
			m_data(new CArrayData<T>(a.m_data->m_size))
		{
			this->m_data->Copy(a.m_data->m_pBase, a.m_data->m_size);
		}

		CArray& operator =(const CArray& a)
		{
			if (this != &a)
			{
				this->m_data->Clone(*a.m_data);
			}
			return *this;
		}
	private:
		CArrayData<T>* m_data;
	};

	template <typename T>
	class CConstPointer
	{
		template <typename TP>
		friend int operator -(const CConstPointer<TP>&, const CConstPointer<TP>&);
		template <typename TP>
		friend bool operator ==(const CConstPointer<TP>&, const CConstPointer<TP>&);
		template <typename TP>
		friend bool operator <(const CConstPointer<TP>&, const CConstPointer<TP>&);
	public:
		CConstPointer(const CArray<T>& a, size_t szIndex) :
		  m_data(a.m_data),
		  m_szIndex(szIndex)
		{
			this->m_data->Inc();
		}
		CConstPointer(const CConstPointer& cp) :
			m_data(cp.m_data),
			m_szIndex(cp.m_szIndex)
		{
			cp.m_data->Inc();
		}
		~CConstPointer(void)
		{
			if (1 == this->m_data->Count())
			{
				delete this->m_data;
			}
			else
			{
				this->m_data->Dec();
			}
		}

		CConstPointer& operator =(const CConstPointer& cp)
		{
			cp.m_data->Inc();
			if (1 == this->m_data->Count())
			{
				delete this->m_data;
			}
			else
			{
				this->m_data->Dec();
			}
			this->m_data = cp.m_data;
			this->m_szIndex = cp.m_szIndex;
			return *this;
		}

		const CConstPointer& operator*(void) const
		{
			return (*this->m_data)[this->m_szIndex];
		}
	protected:
		CArrayData<T>* m_data;
		size_t m_szIndex;
	};

	template <typename T>
	class CPointer
	{
	public:
		CPointer(CArray<T> & a, size_t szIndex) :
		  m_data(a.m_data),
		  m_szIndex(szIndex)
		{
			this->m_data->Inc();
		}

		CPointer(const CPointer<T>& p) :
			m_data(p.m_data),
			m_szIndex(p.m_szIndex)
		{
			this->m_data->Inc();
		}

		~CPointer(void)
		{
			if (NULL != this->m_data && 1 == this->m_data->Count())
			{
				delete this->m_data;
			}
			else
			{
				this->m_data->Dec();
			}
		}

		CPointer& operator =(const CPointer<T> p)
		{
			if (NULL != p.m_data)
			{
				p.m_data->Inc();
			}

			if (NULL != this->m_data && 1 == this->m_data->Count())
			{
				delete this->m_data;
			}
			else
			{
				this->m_data->Dec();
			}
			this->m_data = p.m_data;
			this->m_szIndex = p.m_szIndex;
			return *this;
		}

		T& operator *() const
		{
			return (*this->m_data)[this->m_szIndex];
		}
	private:
		CArrayData<T>* m_data;
		size_t m_szIndex;
	};

	template <typename T>
	class CNewPointer : public CConstPointer<T>
	{
	public:
		CNewPointer(CArray<T>& a, size_t szIndex) :
		  CConstPointer<T>(a, szIndex)
		{}

		T& operator *(void)
		{
 			return (*this->m_data)[this->m_szIndex];
		}

		CNewPointer& operator ++(void)
		{
			++this->m_szIndex;
			return *this;
		}

		CNewPointer& operator --(void)
		{
			--this->m_szIndex;
			return *this;
		}

		CNewPointer operator ++(int)
		{
			CNewPointer ret(*this);
			++this->m_szIndex;
			return ret;
		}

		CNewPointer operator --(int)
		{
			CNewPointer ret(*this);
			--this->m_szIndex;
			return ret;
		}

		CNewPointer& operator +=(int n)
		{
			this->m_szIndex += n;
			return *this;
		}

		CNewPointer& operator -=(int n)
		{
			this->m_szIndex -= n;
			return *this;
		}
	};

	template <typename T>
	int operator -(const CConstPointer<T>& p1, const CConstPointer<T>& p2)
	{
		return static_cast<int>(p1.m_szIndex) - static_cast<int>(p2.m_szIndex);
	}

	template <typename T>
	CNewPointer<T> operator +(const CNewPointer<T>& p, int n)
	{
		CNewPointer<T> ret(p);
		ret += n;
		return ret;
	}

	template <typename T>
	CNewPointer<T> operator +(int n, const CNewPointer<T>& p)
	{
		CNewPointer<T> ret(p);
		ret += n;
		return ret;
	}

	template <typename T>
	bool operator ==(const CConstPointer<T>& p1, const CConstPointer<T>& p2)
	{
		if (p1.m_data != p2.m_data)
		{
			return false;
		}
		return p1.m_szIndex == p2.m_szIndex;
	}

	template <typename T>
	bool operator <(const CConstPointer<T>& p1, const CConstPointer<T>& p2)
	{
		if (p1.m_data != p2.m_data)
		{
			throw exceptionx("Invalid Compare");
		}
		return p1.m_szIndex < p2.m_szIndex;
	}
}

#endif
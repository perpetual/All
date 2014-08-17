#ifndef MYALGORITHM_MATRIX_H
#define MYALGORITHM_MATRIX_H

#include <iostream>
#include <exception>

namespace MyAlgorithm
{
	using std::ostream;
	using std::exception;
	using std::endl;

	template <typename T, unsigned short usRow, unsigned short usColumn>
	class CMatrix
	{
	public:
		//参数为一个二维数组
		CMatrix(T (&)[usRow][usColumn]);
		const T* operator [](unsigned short usRowIndex) const;
		CMatrix& operator =(const CMatrix&);
	private:
		T m_tMatrix[usRow][usColumn];
	};

	template <typename T, unsigned short usRow, unsigned short usColumn>
	CMatrix<T, usRow, usColumn>::CMatrix(T (&matrix)[usRow][usColumn])
	{
		if (0 == usRow || 0 == usColumn)
		{
			throw exception("数组维数错误");
		}

		for (unsigned short us1 = 0; us1 < usRow; ++us1)
		{
			for (unsigned short us2 = 0; us2 < usColumn; ++us2)
			{
				this->m_tMatrix[us1][us2] = matrix[us1][us2];
			}
		}
	}

	template <typename T, unsigned short usRow, unsigned short usColumn>
	const T* CMatrix<T, usRow, usColumn>::operator [](unsigned short usRowIndex) const
	{
		if (usRowIndex >= usRow)
		{
			throw exception("数组下标越界");
		}
		return &this->m_tMatrix[usRowIndex][0];
	}

	template <typename T, unsigned short usRow, unsigned short usColumn>
	CMatrix<T, usRow, usColumn>& CMatrix<T, usRow, usColumn>::operator =(const CMatrix<T, usRow, usColumn>& oMatrix)
	{
		for (unsigned short us1 = 0; us1 < usRow; ++us1)
		{
			for (unsigned short us2 = 0; us2 < usColumn; ++us2)
			{
				this->m_tMatrix[us1][us2] = oMatrix.m_tMatrix[us1][us2];
			}
		}
		return *this;
	}

	template <typename T, unsigned short usRow, unsigned short usColumnRow, unsigned short usColumn>
	CMatrix<T, usRow, usColumn> operator *(const CMatrix<T, usRow, usColumnRow>& oMatrix1, const CMatrix<T, usColumnRow, usColumn>& oMatrix2)
	{
		T a[usRow][usColumn] = {{}};

		for (unsigned short us1 = 0; us1 < usRow; ++us1)
		{
			for (unsigned short us2 = 0; us2 < usColumn; ++us2)
			{
				for (unsigned short us3 = 0; us3 < usColumnRow; ++us3)
				{
					a[us1][us2] += oMatrix1[us1][us3] * oMatrix2[us3][us2];
				}
			}
		}
		return CMatrix<T, usRow, usColumn>(a);
	}

	template <typename T, unsigned short usRow, unsigned short usColumn>
	ostream& operator <<(ostream& oOutStream, const CMatrix<T, usRow, usColumn>& oMatrix)
	{
		for (unsigned short us1 = 0; us1 < usRow; ++us1)
		{
			for (unsigned short us2 = 0; us2 < usColumn; ++us2)
			{
				oOutStream << '\t' << oMatrix[us1][us2];
			}
			oOutStream << endl;
		}
		return oOutStream;
	}
}

#endif
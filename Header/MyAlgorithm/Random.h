#ifndef RANDOM_H
#define RANDOM_H

#include <complex>
#include <typeinfo>
#include "DataType/SimpleData.h"

namespace Random
{
	using DataType::CSimpleData;

	//随机数类，可产生64位随机数
	class CRandom
	{
	public:
		CRandom(void);

		//生成范围[low, high]的随机数
		template <typename T>
		T Get(const T& low, const T& high) const
		{
			unsigned long long temp = static_cast <unsigned long long> (pow(10.0, 6));

			if (low <= high)
			{
				if (typeid(T).name() == typeid(float).name() || typeid (T).name() == typeid (double).name() || typeid (T).name() == typeid (long double).name())
				{
					return static_cast <T> (((Rand64() % static_cast <unsigned long long>(1ull + (high - low) * temp)) + low * temp) / temp);
				}
				else
				{
					return static_cast <T> (Rand64() % static_cast <unsigned long long> (1ull + high - low) + low);
				}
			}
			else
			{
				return 0;
			}
		}

		CSimpleData Get(const CSimpleData& oLow, const CSimpleData& oHigh) const
		{
			CSimpleData oTemp(static_cast <unsigned long long> (pow(10.0, 6)));

			if (oLow.GetTypeName() == oHigh.GetTypeName() && oLow <= oHigh)
			{
				if (DataType::STRING_SINGLE == oLow.GetTypeName() || DataType::STRING_DOUBLE == oLow.GetTypeName())
				{
					return CSimpleData(oLow.GetTypeName(), (((CSimpleData(Rand64()) % (CSimpleData(1ll) + (oHigh - oLow) * oTemp)) + oLow * oTemp) / oTemp).GetFormatedValue(), "");
				}
				else
				{
					return CSimpleData(oLow.GetTypeName(), (CSimpleData(Rand64()) % (CSimpleData(1ull) + oHigh - oLow) + oLow).GetFormatedValue(), "");
				}
			}
			else
			{
				return 0;
			}
		}

		int Get(void)
		{
			return this->Get(int (0), int (0x7FFFFFFF));
		}

	private:
		//生成64位随机无符号整数
		unsigned long long Rand64(void) const;
	};
}

#endif
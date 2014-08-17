#ifndef HANDLE_TEST_SURROGATE_H
#define HANDLE_TEST_SURROGATE_H

#include "BaseObject.h"
#include "Surrogate.h"

namespace Handle
{
	class CVehicel : public CBaseObject
	{
	public:
		virtual void Test(void) const = 0;
	};

	//模板类型为自定义基类类型
	template<typename T>
	class CSurrogateTester : public CSurrogate
	{
	public:
		CSurrogateTester(const CBaseObject& obj) : CSurrogate(obj) {}
		//CSurrogateTester(const CSurrogateTester& obj) : CObjectSurrogate(obj) {}
		virtual void Test(void) const
		{
			dynamic_cast<T*>(this->m_pBaseObject)->Test();
		}
	};

	class Car : public CVehicel
	{
	public:
		CVehicel* Copy(void) const {return new Car(*this);}

		void Test(void) const
		{
			puts("汽车");
		}
	};

	class Plan : public CVehicel
	{
	public:
		CVehicel* Copy(void) const {return new Plan(*this);}

		void Test(void) const
		{
			puts("飞机");
		}
	};

	class Ship : public CVehicel
	{
	public:
		CVehicel* Copy(void) const {return new Ship(*this);}

		void Test(void) const
		{
			puts("轮船");
		}
	};
}

#endif
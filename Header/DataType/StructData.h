#ifndef DATATYPE_STRUCT_DATA_H
#define DATATYPE_STRUCT_DATA_H

#include <vector>
#include "BaseData.h"

namespace DataType
{
	class CStructData
	{
	private:
		std::vector<CBaseData> m_vecData;
	};
}

#endif
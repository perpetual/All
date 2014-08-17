#include "VersionControl.h"
#include "Random/Random.h"
#include <cstdlib>
#include <ctime>

namespace Random
{
	bool g_bHasInit = false;

	CRandom::CRandom(void)
	{
		!g_bHasInit ? srand(static_cast <unsigned int> (time(NULL))), g_bHasInit = true : NULL;
	}

	unsigned long long CRandom::Rand64(void) const
	{
		return static_cast <unsigned long long> (rand())
			| (static_cast <unsigned long long> (rand())) << 15
			| (static_cast <unsigned long long> (rand())) << 30
			| (static_cast <unsigned long long> (rand())) << 45
			| (static_cast <unsigned long long> (rand())) << 60;
	}

}


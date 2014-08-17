#include "VersionControl.h"
#include "MyTools/MyFunctional.h"
#include <cctype>


namespace MyTools
{
	void CToUpper::operator ()(char& c)
	{
		c = static_cast<char>(toupper(c));
	}

	void CToLower::operator ()(char& c)
	{
		c = static_cast<char>(tolower(c));
	}
}
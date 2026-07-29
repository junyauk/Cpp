#include "pch.h"
#include "TypeTraits_Basic.h"
#include <iostream>

namespace TypeTraits_Basic
{
	void TypeTraits_Basic::demoIntegralCheck()
	{
		check_integral<int>();
		check_integral<double>();
		check_integral<char>();
	}
}


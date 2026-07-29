//#include "pch.h"
//#include "Legacy.h"
module Legacy;
import <string>;

namespace moduleexample::legacy
{
	// Simple function
	int legacy_add(int a, int b)
	{
		return a + b;
	}

	int LegacyCalculator::multiply(int a, int b)
	{
		return a * b;
	}

	std::string LegacyCalculator::info()
	{
		return "LegacyCalculator";
	}
}

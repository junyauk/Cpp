import ModuleB;
import Legacy;

import <string>;
using namespace moduleexample::legacy;

namespace moduleexample::moduleb
{
	int Calculator::multiply(int a, int b)
	{
		return a * b * 10;
	}
	std::string Calculator::info()
	{
		return "ModuleB::Calculator";
	}

	int Calculator::legacy_multiply(int a, int b)
	{
		LegacyCalculator lc;
		return lc.multiply(a, b) * 2;
	}
	std::string Calculator::legacy_info()
	{
		return LegacyCalculator::info() + " info via ModuleB";
	}

}


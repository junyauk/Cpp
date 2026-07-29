import ModuleA;
import Legacy;

import <string>;
using namespace moduleexample::legacy;

namespace moduleexample::modulea
{
	int Calculator::multiply(int a, int b)
	{
		return a * b;
	}
	std::string Calculator::info()
	{
		return "ModuleA::Calculator";
	}

	int Calculator::legacy_multiply(int a, int b)
	{
		LegacyCalculator lc;
		return lc.multiply(a, b);
	}
	std::string Calculator::legacy_info()
	{
		return LegacyCalculator::info() + " info via ModuleA";
	}

}

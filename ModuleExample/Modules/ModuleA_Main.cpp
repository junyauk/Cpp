import ModuleA;
import Legacy;

import <string>;

using namespace moduleexample::legacy;

namespace moduleexample::modulea
{
	int add(int a, int b)
	{
		return (a + b) * 10;
	}
	std::string concat(const std::string& a, const std::string& b)
	{
		return "[" + a + "|" + b + "]";
	}
	int compute_value(int x)
	{
		return (x + 1) * 100;
	}
	std::string message()
	{
		return "ModuleA says hi!";
	}

	int legacy_add_viaModuleA(int a, int b)
	{
		return legacy_add(a, b);
	}

}

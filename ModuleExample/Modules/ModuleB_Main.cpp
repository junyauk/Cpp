import ModuleB;
import Legacy;

import <string>;

using namespace moduleexample::legacy;

namespace moduleexample::moduleb
{
	int add(int a, int b)
	{
		return (a + b) * 100;
	}
	std::string concat(const std::string& a, const std::string& b)
	{
		return "<" + a + "," + b + ">";
	}
	int compute_value(int x)
	{
		return (x + 1) * 1000;
	}
	std::string message()
	{
		return "ModuleB says hello!";
	}

	int legacy_add_viaModuleB(int a, int b)
	{
		return legacy_add(a, b) + 1;
	}

}


export module ModuleA;
import Legacy;
import <string>;

using namespace moduleexample::legacy;

export namespace moduleexample::modulea
{
	// Example of constants
	export constexpr int kModuleAValue = 100;

	// Example of funcs
	export int add(int a, int b);
	export std::string concat(const std::string& a, const std::string& b);
	export int compute_value(int x);
	export std::string message();

	// Example of classes
	export class Calculator
	{
	public:
		Calculator() = default;
		int multiply(int a, int b);
		static std::string info();

		// These use Legacy's methods
		int legacy_multiply(int a, int b);
		static std::string legacy_info();

	};

	// This use Legacy's function
	export int legacy_add_viaModuleA(int a, int b);

	// This combine with Legacy's constant
	export constexpr int kModuleACombinedValue = kModuleAValue + kLegacyValue;
}

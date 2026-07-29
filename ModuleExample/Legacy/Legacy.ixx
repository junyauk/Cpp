export module Legacy;

import <string>;

namespace moduleexample::legacy
{
	// Simple function
	export int legacy_add(int a, int b);

	// Constant
	export constexpr int kLegacyValue = 500;

	// Class
	export class LegacyCalculator
	{
	public:
		LegacyCalculator() = default;
		int multiply(int a, int b);
		static std::string info();
	};
}

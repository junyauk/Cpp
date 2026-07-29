#pragma once
#include <string>

namespace moduleexample::legacy
{
	// Simple function
	int legacy_add(int a, int b);

	// Constant
	constexpr int kLegacyValue = 500;

	// Class
	class LegacyCalculator
	{
	public:
		LegacyCalculator() = default;
		int multiply(int a, int b);
		static std::string info();
	};
}

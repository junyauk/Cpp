#pragma once
#include <string>

namespace LanguageFeatures
{
	// It would cause a warning error if the return value is ignored
	[[nodiscard]] int ComputeValue(int x)
	{
		return x * 2;
	}

	// it can be applied for struct
	struct [[nodiscard]] Result
	{
		int value;
		std::string description;
	};
}

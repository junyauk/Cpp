#include "pch.h"
#include <sstream>
#include "04_InlineVariable.h"

namespace LanguageFeatures
{
	void incrementA()
	{
		staticCounter++;
		inlineCounter++;
		Config::sharedValue++;
	}

	std::vector<int> getCountersA()
	{
		return { staticCounter, inlineCounter, Config::sharedValue };
	}
}

#include "pch.h"
#include <sstream>
#include "04_InlineVariable.h"

namespace LanguageFeatures
{
	void incrementB()
	{
		staticCounter++;
		inlineCounter++;
		Config::sharedValue++;
	}

	std::vector<int> getCountersB()
	{
		return { staticCounter, inlineCounter, Config::sharedValue };
	}
}

#include "pch.h"
#include "04_InlineVariable.h"
#include <sstream>
#include <string>

namespace LanguageFeatures
{
	void incrementC()
	{
		staticCounter++;
		inlineCounter++;
		Config::sharedValue++;
	}

	std::vector<int> getCountersC()
	{
		return { staticCounter, inlineCounter, Config::sharedValue };
	}
}

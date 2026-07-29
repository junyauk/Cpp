#include "pch.h"
#include <sstream>
#include "04_InlineVariable.h"

namespace LanguageFeatures
{
	std::string reportValues()
	{
		std::ostringstream oss;
		oss << "staticCounter=" << staticCounter
			<< ", inlineCounter=" << inlineCounter
			<< ", Config::sharedValue=" << Config::sharedValue;
		return oss.str();
	}
}


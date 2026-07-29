#pragma once
#include <optional>
#include <vector>
#include <string>
#include <map>

namespace SwitchInitSample
{
	std::string classifyByModulo(int value);
	bool isVowel(char ch);
	enum class Color
	{
		Red,
		Green,
		Blue,
		Unknown
	};
	Color toColor(const std::string& name);
	Color toColorOrUnknown(const std::optional<std::string>& name);
}

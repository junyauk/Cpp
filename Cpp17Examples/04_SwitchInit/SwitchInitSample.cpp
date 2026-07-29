#include "pch.h"
#include "framework.h"
#include "SwitchInitSample.h"

namespace SwitchInitSample
{
	std::string classifyByModulo(int value)
	{
		switch (auto v = value % 3; v)
		{
		case 0: return "divisible by 3";
		case 1: return "remainder 1";
		case 2: return "remainder 2";
		default: return "unexpected";
		}
	}
	bool isVowel(char ch)
	{
		switch (auto code = static_cast<int>(ch); code)
		{
		case 'A': case 'E': case 'I': case 'O': case 'U':
		case 'a': case 'e': case 'i': case 'o': case 'u':
			return true;
		default:
			return false;
		}
	}
	Color toColor(const std::string& name)
	{
		static const std::map<std::string, Color> table
		{
			{"red", Color::Red},
			{"green", Color::Green},
			{"blue", Color::Blue},
		};

		if (auto it = table.find(name); it != table.end())
		{
			return it->second;
		}
		return Color::Unknown;

	}
	Color toColorOrUnknown(const std::optional<std::string>& name)
	{
		switch (auto c = name ? toColor(name.value()) : Color::Unknown; c)
		{
		case Color::Red: case Color::Green: case Color::Blue:
			return c;
		default:
			return Color::Unknown;
		}
	}
}

#include "pch.h"
#include "framework.h"
#include "VariantExamples.h"
#include <sstream>

namespace VariantExamples
{
	std::string toString(const IntOrString& v)
	{
		return std::visit(
			[](auto&& arg)
			{
				using T = std::decay_t<decltype(arg)>;
				if constexpr (std::is_same_v<T, int>)
				{
					return std::to_string(arg);
				}
				else if (std::is_same_v<T, std::string>)
				{
					return arg;
				}
			}, v);
	}

	std::string settingToString(const SettingValue& v)
	{
		return std::visit(
			[](auto&& arg) -> std::string
			{
				using T = std::decay_t<decltype(arg)>;
				if constexpr (std::is_same_v<T, int>)
				{
					return "int:" + std::to_string(arg);
				}
				else if constexpr (std::is_same_v<T, double>)
				{
					return "double:" + std::to_string(arg);
				}
				else if constexpr (std::is_same_v<T, std::string>)
				{
					return "string:" + arg;
				}
				else if constexpr (std::is_same_v<T, Color>)
				{
					switch (arg)
					{
					case Color::Red: return "Color:Red";
					case Color::Green: return "Color:Green";
					case Color::Blue: return "Color::Blue";
					}

				}
				return "Unknown";
			}, v);
	}
}

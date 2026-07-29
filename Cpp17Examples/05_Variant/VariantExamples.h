#pragma once
#include <optional>
#include <vector>
#include <string>
#include <variant>
#include <map>

namespace VariantExamples
{
	using IntOrString = std::variant<int, std::string>;

	std::string toString(const IntOrString& v);

	enum class Color { Red, Green, Blue };
	using SettingValue = std::variant<int, double, std::string, Color>;

	std::string settingToString(const SettingValue& v);
}

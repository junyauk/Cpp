#pragma once
#include <string_view>

namespace StringViewExamples
{
	int CompareStrings(std::string_view lhs, std::string_view rhs);
	bool Equals(std::string_view lhs, std::string_view rhs);
	bool LessThan(std::string_view lhs, std::string_view rhs);
}

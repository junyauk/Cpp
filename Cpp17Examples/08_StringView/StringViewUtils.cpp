#include "pch.h"
#include "StringViewUtils.h"

namespace StringViewExamples
{
	int CompareStrings(std::string_view lhs, std::string_view rhs)
	{
		return lhs.compare(rhs);
	}
	bool Equals(std::string_view lhs, std::string_view rhs)
	{
		return lhs == rhs;
	}
	bool LessThan(std::string_view lhs, std::string_view rhs)
	{
		return lhs < rhs;
	}
}

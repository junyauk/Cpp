#pragma once
#include <string_view>
#include <vector>

namespace StringViewExamples
{
	std::string_view GetSubstr(std::string_view text, size_t pos, size_t count);

	bool Contains(std::string_view text, std::string_view pattern);

	std::vector<std::string_view> SplitWords(std::string_view text);
}



#pragma once
#include <string_view>
#include <map>
#include <unordered_map>
#include <string>

namespace StringViewExamples
{
	std::map<std::string_view, int> CountWordsOrdered(const std::vector<std::string>& words);

	std::unordered_map<std::string_view, int> CountWordsUnordered(const std::vector<std::string>& words);
}


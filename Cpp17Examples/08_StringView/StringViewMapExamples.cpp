#include "pch.h"
#include "StringViewMapExamples.h"

namespace StringViewExamples
{
	std::map<std::string_view, int> CountWordsOrdered(const std::vector<std::string>& words)
	{
		std::map<std::string_view, int> counts;
		for (const auto& word : words)
		{
			counts[word]++;
		}
		return counts;
	}

	std::unordered_map<std::string_view, int> CountWordsUnordered(const std::vector<std::string>& words)
	{
		std::unordered_map<std::string_view, int> counts;
		for (const auto& word : words)
		{
			counts[word]++;
		}
		return counts;
	}
}

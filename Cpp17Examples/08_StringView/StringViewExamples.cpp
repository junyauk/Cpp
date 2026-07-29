#include "pch.h"
#include <sstream>
#include "StringViewExamples.h"

namespace StringViewExamples
{
	std::string_view GetSubstr(std::string_view text, size_t pos, size_t count)
	{
		return text.substr(pos, count);
	}

	bool Contains(std::string_view text, std::string_view pattern)
	{
		return text.find(pattern) != std::string_view::npos;
	}

	std::vector<std::string_view> SplitWords(std::string_view text)
	{
		std::vector<std::string_view> words;
		size_t start = 0;
		while (start < text.size())
		{
			size_t end = text.find(' ', start);
			if (end == std::string_view::npos)
			{
				end = text.size();
			}
			if (end > start)
			{
				words.push_back(text.substr(start, end - start));
			}
			start = end + 1;
		}
		return words;
	}
}


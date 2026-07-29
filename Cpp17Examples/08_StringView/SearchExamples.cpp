#include "pch.h"
#include "searchExamples.h"

namespace StringViewExamples
{
	bool containsWorld(std::string_view sv)
	{
		return sv.find("World") != std::string_view::npos;
	}
	bool startsWithHello(std::string_view sv)
	{
		return sv.rfind("Hello", 0) == 0;
	}
    bool endsWithExclamation(std::string_view sv)
    {
	    return !sv.empty() && sv.back() == '!';
    }

	std::vector<std::string_view> splitWords(std::string_view sv)
	{
		std::vector<std::string_view> words;
		size_t pos = 0;
		while (pos < sv.size())
		{
			size_t space = sv.find(' ', pos);
			if (space == std::string_view::npos)
			{
				words.push_back(sv.substr(pos));
				break;
			}
			words.push_back(sv.substr(pos, space - pos));
			pos = space + 1;
		}
		return words;
	}
}

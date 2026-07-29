#pragma once
#include <string_view>
#include <string>
#include <vector>

namespace StringViewExamples
{
	bool containsWorld(std::string_view sv);
	bool startsWithHello(std::string_view sv);
	bool endsWithExclamation(std::string_view sv);

	std::vector<std::string_view> splitWords(std::string_view sv);
}

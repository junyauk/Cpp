#pragma once
#include <string_view>
#include <string>

namespace StringViewExamples
{
	std::string_view getTempStringView();
	std::string_view getStaticStringView();
	std::string_view getViewFromString(const std::string& str);
}
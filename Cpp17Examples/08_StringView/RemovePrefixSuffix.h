#pragma once
#include <string_view>
#include <string>

namespace StringViewExamples
{
	std::string_view getFileName(std::string_view path);
	std::string_view getExtension(std::string_view path);
}
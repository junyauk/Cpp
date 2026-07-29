#include "pch.h"
#include "LifeTimeTrap.h"

namespace StringViewExamples
{
	std::string_view getTempStringView()
	{
		return std::string_view("Temporary String"); // this string_view 
	}
	std::string_view getStaticStringView()
	{
		static std::string str = "Static storage";
		return str;
	}
	std::string_view getViewFromString(const std::string& str)
	{
		return str;
	}
}

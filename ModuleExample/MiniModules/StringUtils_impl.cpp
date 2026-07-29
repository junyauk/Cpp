module;
// #include should be listed after "module" directive
#include <algorithm>
#include <cctype>

// Implementation of stringutils module
module stringutils;

std::string to_upper(const std::string& str)
{
	std::string ret = str;
	std::transform(ret.begin(), ret.end(), ret.begin(),
		[](unsigned char c) { return std::toupper(c); });
	return ret;
}
std::string to_lower(const std::string& str)
{
	std::string ret = str;
	std::transform(ret.begin(), ret.end(), ret.begin(), 
		[](unsigned char c) { return std::tolower(c); });
	return ret;
}

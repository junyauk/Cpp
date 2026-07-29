#pragma once
#include <map>
#include <string>
#include <optional>
#include <vector>

namespace IfInitSample
{
	std::optional<std::string> findValue(const std::map<int, std::string>& m, int key);
	std::string classifyString(const std::string& input);

	std::optional<int> findEven(const std::vector<int>& numbers);
	std::string checkPassword(const std::string& pwd);
}


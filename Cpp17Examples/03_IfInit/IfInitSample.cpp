#include "pch.h"
#include "framework.h"
#include "IfInitSample.h"

namespace IfInitSample
{
	std::optional<std::string> findValue(const std::map<int, std::string>& m, int key)
	{
		if (auto it = m.find(key); it != m.end())
		{
			return it->second;
		}
		return std::nullopt;
	}
	std::string classifyString(const std::string& input)
	{
		switch (auto len = input.size(); len)
		{
		case 0: return "empty";
		case 1: return "short";
		case 2: return "tiny";
		default: return "long";
		}
	}

	std::optional<int> findEven(const std::vector<int>& numbers)
	{
		for (auto i = 0; i < numbers.size(); ++i)
		{
			if (auto n = numbers[i]; n % 2 == 0)
			{
				return n;
			}
		}
		return std::nullopt;
	}
	std::string checkPassword(const std::string& pwd)
	{
		if (auto len = pwd.size(); len < 6)
		{
			return "too short";
		}
		else if (len > 12)
		{
			return "too long";
		}
		else if (pwd == "password")
		{
			return "too weak";
		}
		return "ok";
	}
}

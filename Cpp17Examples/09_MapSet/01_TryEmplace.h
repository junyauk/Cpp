#pragma once
#include <map>
#include <unordered_map>
#include <string>
#include <sstream>

namespace MapSetExamples
{
	inline std::string TestTryEmplaceMap()
	{
		std::map<int, std::string> m;

		m.try_emplace(1, "Hello");
		m.try_emplace(2, "World");

		m.try_emplace(1, "Ignored");

		std::ostringstream oss;
		for (auto& [k, v] : m)
		{
			oss << k << ":" << v << "; ";
		}
		return oss.str();
	}

	inline std::string TestTryEmplaceUnorderedMap()
	{
		std::unordered_map<int, std::string> m;

		m.try_emplace(1, "Hello");
		m.try_emplace(2, "World");

		m.try_emplace(1, "Ignored");

		std::ostringstream oss;
		for (auto& [k, v] : m)
		{
			oss << k << ":" << v << "; ";
		}
		return oss.str();
	}
}


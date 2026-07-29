#pragma once
#include <map>
#include <unordered_map>
#include <string>
#include <sstream>

namespace MapSetExamples
{
	inline std::string TestInsertOrAssignMap()
	{
		std::map<int, std::string> m;
		m.insert_or_assign(1, "Hello");
		m.insert_or_assign(2, "World");

		m.insert_or_assign(1, "Overwritten");

		std::ostringstream oss;
		for (auto& [n, s] : m)
		{
			oss << n << ":" << s << "; ";
		}
		return oss.str();
	}

	inline std::string TestInsertOrAssignUnordered()
	{
		std::unordered_map<int, std::string> m;
		m.insert_or_assign(1, "Hello");
		m.insert_or_assign(2, "World");

		m.insert_or_assign(1, "Overwritten");

		std::ostringstream oss;
		for (auto& [n, s] : m)
		{
			oss << n << ":" << s << "; ";
		}
		return oss.str();
	}
}


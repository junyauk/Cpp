#include "pch.h"
#include <map>
#include <unordered_map>
#include <vector>
#include <string>
#include <optional>

#include "MapBasics.h"

namespace MapSetExamples
{
	std::map<std::string, int> MapBasics::insertExamples()
	{
		std::map<std::string, int> m;

		// insert
		m.insert({ "apple", 1 });
		// [] operator
		m["banana"] = 2;
		// emplace
		m.emplace("cherry", 3);

		return m;
	}

	std::optional<int> MapBasics::findExample(const std::map<std::string, int>& m, std::string& key)
	{
		auto it = m.find(key);
		if (it != m.end())
		{
			return it->second;
		}
		return std::nullopt;
	}

	std::optional<int> MapBasics::atExample(const std::map<std::string, int>& m, std::string& key)
	{
		try
		{
			return m.at(key);
		}
		catch (...)
		{
			return std::nullopt;
		}
	}

	std::map<std::string, int> MapBasics::eraseExamples()
	{
		std::map<std::string, int> m = insertExamples();

		m.erase("banana");
			
		auto it = m.find("apple");
		if (it != m.end())
		{
			m.erase(it);
		}
		return m;
	}

	std::map<std::string, int> MapBasics::updateExamples()
	{
		std::map<std::string, int> m = insertExamples();

		m["banana"] = 20;

		m.try_emplace("banana", 100);
		m.try_emplace("date", 40);

		return m;
	}

	int MapBasics::sumValues(const std::map<std::string, int>& m)
	{
		int sum = 0;
		for (const auto& [k, v] : m)
		{
			sum += v;
		}
		return sum;
	}

	bool MapBasics::capacityExamples()
	{
		std::map<std::string, int> m = insertExamples();
		bool before = m.empty();
		m.clear();
		bool after = m.empty();
		return (!before && after);
	}

	std::vector<std::string> MapBasics::orderedKeys()
	{
		std::map<std::string, int> m = insertExamples();
		std::vector<std::string> keys;
		for (const auto& [k, v] : m)
		{
			keys.push_back(k);
		}
		return keys;
	}

	std::vector<std::string> MapBasics::unorderedKeys()
	{
		std::unordered_map<std::string, int> um = { {"apple", 1}, {"banana", 2}, {"cherry", 3} };
		std::vector<std::string> keys;
		for (const auto& [k, v] : um)
		{
			keys.push_back(k);
		}
		return keys;
	}
}


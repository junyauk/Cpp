#pragma once
#include <map>
#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

// map/set are red & black tree
// 
// lower_bound(v) => returns the first itelator of the first value >= v
// upper_bound(v) => returns the first itelator of the first value > v
// equal_range(v) => returns a std::pair{ lower_bound(v), upper_bound(v) }
//
// they are O(log n)

// unordered_map/set are hash table that contains buckets

namespace MapSetExamples
{
	void ExampleOfLowerAndUpper()
	{
		std::map<int, std::string> m
		{
			{0,"0"}, 
			{1,"1"},
			{50,"50"},
			{99,"99"},
			{100,"100"},
			{101,"101"}
		};
		auto it_l = m.lower_bound(0); // it_l will be 0 (the 1st value >= 0)
		auto it_h = m.upper_bound(100); // it_h will be 101 (the 1st value > 100))
		for (auto it = it_l; it != it_h; ++it)
		{
			// it_l(0) <= it <= it_h(100)
		}

		// Elements can be erased at once, better than processing erase(key) individually
		m.erase(it_l, it_h);
	}

	std::vector<std::string> ExampleOfEqualRangeOfMultiMap()
	{
		std::vector<std::string> ret;

		std::multimap<int, std::string> m;
		m.emplace(1, "a");
		m.emplace(0, "b");
		m.emplace(1, "c");
		m.emplace(1, "d");
		m.emplace(5, "e");
		m.emplace(2, "f");
		m.emplace(9, "g");
		m.emplace(11, "h");

		{
			std::stringstream ss;
			ss << "range(1):";
			auto range = m.equal_range(1); // should be pair( (1, "a"), (2, "f") )
			for (auto it = range.first; it != range.second; ++it)
			{
				ss << " " << it->second;
			}
			ret.push_back(ss.str()); // range(1): a c d
		}

		{
			std::stringstream ss;
			ss << "range(2):";
			auto range = m.equal_range(2); // should be pair( (2, "f"), (5, "e") )
			for (auto it = range.first; it != range.second; ++it)
			{
				ss << " " << it->second;
			}
			ret.push_back(ss.str()); // range(2): f
		}

		{
			std::stringstream ss;
			ss << "range(3):";
			auto range = m.equal_range(3);  // should be pair( (5, "e"), (5, "e") )
			for (auto it = range.first; it != range.second; ++it)
			{
				ss << " " << it->second;
			}
			ret.push_back(ss.str()); // range(3):
		}

		{
			std::stringstream ss;
			ss << "range(11):";
			auto range = m.equal_range(11); // should be pair( (11, "h"), end )
			for (auto it = range.first; it != range.second; ++it)
			{
				ss << " " << it->second;
			}
			ret.push_back(ss.str()); // range(11): h
		}
		return ret;
	}

	std::vector<std::string> ExampleOfEqualRangeOfUnorderedMultiMap()
	{
		std::vector<std::string> ret;

		std::unordered_multimap<int, std::string> m;
		m.emplace(1, "a");
		m.emplace(0, "b");
		m.emplace(1, "c");
		m.emplace(1, "d");
		m.emplace(5, "e");
		m.emplace(2, "f");
		m.emplace(9, "g");
		m.emplace(11, "h");

		{
			std::stringstream ss;
			ss << "range(1):";
			auto range = m.equal_range(1); // should be pair( (1, "a"), (2, "f") )
			for (auto it = range.first; it != range.second; ++it)
			{
				ss << " " << it->second;
			}
			ret.push_back(ss.str()); // range(1): a c d
		}

		{
			std::stringstream ss;
			ss << "range(2):";
			auto range = m.equal_range(2); // should be pair( (2, "f"), (5, "e") )
			for (auto it = range.first; it != range.second; ++it)
			{
				ss << " " << it->second;
			}
			ret.push_back(ss.str()); // range(2): f
		}

		{
			std::stringstream ss;
			ss << "range(3):";
			auto range = m.equal_range(3);  // should be pair( (5, "e"), (5, "e") )
			for (auto it = range.first; it != range.second; ++it)
			{
				ss << " " << it->second;
			}
			ret.push_back(ss.str()); // range(3):
		}

		{
			std::stringstream ss;
			ss << "range(11):";
			auto range = m.equal_range(11); // should be pair( (11, "h"), end )
			for (auto it = range.first; it != range.second; ++it)
			{
				ss << " " << it->second;
			}
			ret.push_back(ss.str()); // range(11): h
		}
		return ret;
	}

	using EmployeeMap = std::map<int, std::string>;

	inline std::vector<std::pair<int, std::string>> getEmployeesFromId(const EmployeeMap& m, int minId)
	{
		std::vector<std::pair<int, std::string>> result;
		for (auto& it = m.lower_bound(minId); it != m.end();++it)
		{
			result.push_back(*it);
		}
		return result;
	}

	inline std::vector<std::pair<int, std::string>> getEmployeesInRange(const EmployeeMap& m, int low, int high)
	{
		std::vector<std::pair<int, std::string>> result;
		auto range = m.equal_range(low);
		for (auto it = range.first; it != m.upper_bound(high - 1); ++it)
		{
			result.push_back(*it);
		}
		return result;
	}
}


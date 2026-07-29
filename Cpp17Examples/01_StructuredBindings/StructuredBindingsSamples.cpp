#include "pch.h"
#define WIN32_LEAN_AND_MEAN
#include "StructuredBindingsSamples.h"

namespace StructuredBindingsExamples
{
	Point make_point(int x, int y)
	{
		return { x, y };
	}

	std::tuple<int, std::string> make_tuple_example(int num, const std::string& text)
	{
		return { num, text };
	}

	std::pair<std::map<std::string, int>::iterator, bool> insert_score(std::map<std::string, int>& scores, const std::string& name, int score)
	{
		auto [it, inserted] = scores.insert({name, score});
		return { it, inserted };
	}

	std::map<std::string, int>::iterator find_score(std::map<std::string, int>& scores, const std::string& name)
	{
		auto it = scores.find(name);
		return it;
	}

	std::pair<std::vector<std::string>, std::vector<int>> map_loop_example(std::unordered_map<std::string, int> data)
	{
		std::vector<std::string> strings;
		std::vector<int> values;
		for (auto& [str, val] : data)
		{
			strings.push_back(str);
			values.push_back(val);
		}
		return { std::move(strings), std::move(values) };
	}

	Employee make_employee(int id, std::string name, double salary)
	{
		return { id, name, salary };
	}

}

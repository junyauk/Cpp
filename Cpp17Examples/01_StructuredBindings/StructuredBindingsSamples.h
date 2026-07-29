#pragma once

#include <tuple>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <iterator>

namespace StructuredBindingsExamples
{
	struct Point
	{
		int x;
		int y;
		bool operator<(const Point& other) const
		{
			return std::tie(x, y) < std::tie(other.x, other.y);
		}
	};

	Point make_point(int x, int y);

	std::tuple<int, std::string> make_tuple_example(int num, const std::string& text);

	std::pair<std::map<std::string, int>::iterator, bool> insert_score(std::map<std::string, int>& scores, const std::string& name, int score);
	std::map<std::string, int>::iterator find_score(std::map<std::string, int>& scores, const std::string& name);
	std::pair<std::vector<std::string>, std::vector<int>> map_loop_example(std::unordered_map<std::string, int> data);

	struct Employee
	{
		int id;
		std::string name;
		double salary;
	};

	Employee make_employee(int id, std::string name, double salary);

}

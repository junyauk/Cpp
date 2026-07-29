#pragma once
#include <compare>
#include <string>


namespace ThreeWayComparisonSamples
{
	struct Person
	{
		std::string name;
		int age;

		auto operator<=>(const Person& other) const -> std::strong_ordering = default;
	};

	struct Point
	{
		int x;
		int y;

		auto operator<=>(const Point& other) const -> std::strong_ordering
		{
			if (auto cmp = x <=> other.x; cmp != 0)
			{
				return cmp;
			}
			return y <=> other.y;
		}

		bool operator==(const Point& other) const = default;
	};

	int CompareAges(const Person& p1, const Person& p2);

	std::string CompareInts(int a, int b);
	std::string CompareDoubles(double a, double b);
}


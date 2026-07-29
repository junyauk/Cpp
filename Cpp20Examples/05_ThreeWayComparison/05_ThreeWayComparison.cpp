#include "pch.h"
#include "framework.h"
#include "05_ThreeWayComparison.h"
#include <sstream>

namespace ThreeWayComparisonSamples
{

	int CompareAges(const Person& p1, const Person& p2)
	{
		std::strong_ordering result = p1.age <=> p2.age;

		if (result < 0) return -1;	// std::strong_ordering::less
		if (result > 0) return 1;	// std::strong_ordering::greater
		return 0;					// std::strong_ordering::equal
	}

	std::string CompareInts(int a, int b)
	{
		std::ostringstream oss;
		std::strong_ordering result = (a <=> b);

		if (result == std::strong_ordering::less)
		{
			oss << a << " < " << b;
		}
		else if (result == std::strong_ordering::equal)
		{
			oss << a << " == " << b;
		}
		else if (result == std::strong_ordering::greater)
		{
			oss << a << " > " << b;
		}
		return oss.str();
	}
	std::string CompareDoubles(double a, double b)
	{
		std::ostringstream oss;
		std::partial_ordering result = (a <=> b);

		if (result == std::partial_ordering::less)
		{
			oss << a << " < " << b;
		}
		else if (result == std::partial_ordering::equivalent)
		{
			oss << a << " == " << b;
		}
		else if (result == std::partial_ordering::greater)
		{
			oss << a << " > " << b;
		}
		return oss.str();
	}
}


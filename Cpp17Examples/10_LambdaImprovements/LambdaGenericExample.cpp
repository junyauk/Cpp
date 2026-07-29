#include "pch.h"
#include "LambdaGenericExample.h"

namespace LambdaImprovements
{
	std::string LambdaGenericExample::fixedLambdaExample()
	{
		std::ostringstream oss;

		auto squareInt = [](int x) { return x * x; };

		int result = squareInt(5);
		oss << "squareInt(5) = " << result << std::endl;
		oss << "Type of parameter: int (fixed)\n";
		return oss.str();
	}

	std::string LambdaGenericExample::genericLambdaExample()
	{
		std::ostringstream oss;

		auto square = [](auto x) { return x * x; };

		int i = 4;
		double d = 3.14;

		oss << "square(4) = " << square(i) << std::endl;
		oss << "square(3.14) = " << square(d) << std::endl;

		if constexpr (std::is_same_v<decltype(square(i)), int>)
		{
			oss << "Return type for int: int\n";
		}
		if constexpr (std::is_same_v<decltype(square(d)), double>)
		{
			oss << "Return type for double: double\n";
		}

		return oss.str();
	}
}


#include "pch.h"
#include "BindPitfallsExample.h"
#include <iostream>
#include <string>
#include <sstream>

namespace LambdaImprovements
{
	int add(int a, int b) { return a + b; }

	std::function<int(int, int)> BindPitfallsExample::wrongOrderBind()
	{
		// Note:
		// the order of the placeholders should be...
		// std::bind(&add, std::placeholders::_1, std::placeholders::_2);
		// The order will never be static cheked.
		return std::bind(&add, std::placeholders::_2, std::placeholders::_1); // NG order of std:placholders
	}

	std::function<int(int, int)> BindPitfallsExample::correctOrderLambda()
	{
		// Lambda can expricitly use the parameter name safely
		return [](int a, int b) { return add(a, b); };
	}

	std::function<void()> BindPitfallsExample::danglingReferenceBind()
	{
		int local = 42;
		// std::bind() can not only copy value, but also ref value, it's not safe.
		return std::bind([](int& ref) { ref = 999; }, std::ref(local));
		// Note:
		// When the returned bind function was used, the local wouldn't be available.
	}

	std::function<void()> BindPitfallsExample::safeLambda()
	{
		int local = 42;
		// Lambda can chose copy or safe ref.
		return [value = local]() mutable // this is copying
			{
				value = 999;
			};
	}
}

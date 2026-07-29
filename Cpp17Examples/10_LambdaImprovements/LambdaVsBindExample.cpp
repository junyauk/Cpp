#include "pch.h"
#include "LambdaVsBindExample.h"

namespace LambdaImprovements
{
	int LambdaVsBindExample::multiply(int a, int b)
	{
		return a * b;
	}
	std::function<int(int)> LambdaVsBindExample::createBindMultiplier(int factor)
	{
		// std::bind partially applies a function pointer of the multiply()
		return std::bind(&LambdaVsBindExample::multiply, factor, std::placeholders::_1);
	}

	std::function<int(int)> LambdaVsBindExample::createLambdaMultiplier(int factor)
	{
		// lambda copies the factor by closure[]
		return [factor](int value) {return factor * value; };
	}

	std::function<std::string()> LambdaVsBindExample::createBindStringAppender(std::string text)
	{
		auto func = [](std::string prefix, std::string suffix)
			{
				return prefix + " " + suffix;
			};
		// std::bind copies the parameter text and "bound"
		return std::bind(func, text, "bound");
	}
	std::function<std::string()> LambdaVsBindExample::createLambdaStringAppender(std::string text)
	{
		// lambda can specify the way (copy or ref)
		return [text]()
			{
				return text + " lambda";
			};
	}
}


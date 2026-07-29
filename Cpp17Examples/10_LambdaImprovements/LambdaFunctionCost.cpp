#include "pch.h"
#include "LambdaFunctionCost.h"

namespace LambdaImprovements
{
	double LambdaFunctionCost::measureStdFunctionCost(const std::function<void()>& func, int iterations)
	{
		auto start = Clock::now();
		for (int i = 0; i < iterations; ++i)
		{
			func();
		}
		auto end = Clock::now();
		std::chrono::duration<double, std::micro> diff = end - start;
		return diff.count();
	}
	double LambdaFunctionCost::measureEmptyLoop(int iterations)
	{
		auto start = Clock::now();
		for (int i = 0; i < iterations; ++i)
		{
			// empty, do nothing
		}
		auto end = Clock::now();
		std::chrono::duration<double, std::micro> diff = end - start;
		return diff.count();
	}
}


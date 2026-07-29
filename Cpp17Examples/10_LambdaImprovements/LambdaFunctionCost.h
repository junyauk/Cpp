#pragma once
#include <functional>
#include <string>
#include <chrono>

namespace LambdaImprovements
{
	class LambdaFunctionCost
	{
		using Clock = std::chrono::high_resolution_clock;

	public:
		template<typename F>
		static double measureLambdaCost(F&& func, int iterations)
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
		static double measureStdFunctionCost(const std::function<void()>& func, int iterations);
		static double measureEmptyLoop(int iterations);
	};
}


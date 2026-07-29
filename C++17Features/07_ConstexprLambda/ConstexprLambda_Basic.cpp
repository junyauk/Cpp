#include "pch.h"
#include "framework.h"
#include <array>
#include <numeric>
#include <string>
#include <type_traits>
#include "ConstexprLambda_Basic.h"

namespace CONSTEXPRLAMBDA_Basic
{
	// 1. Basic C++17 Constexpr Lambda
	int ConstexprLambda_Basic::calculateSquare(int x) const
	{
		// This lambda is implicitly constexpr because its body meets the requirements.
		auto square = [](int val) { return val * val; };
		// We can use it in a runtime context.
		return square(x);
	}


	// 3. Runtime usage of the implicitly constexpr lambda
	int ConstexprLambda_Basic::calculateRuntimeSum(int count) const
	{
		// An implicitly constexpr lambda
		auto sum_of_square = [](int n)
			{
				int sum = 0;
				// Loop is fine in a constexpr context if the bounds are known/deducible.
				// Here, it's used at runtime, which is always fine.
				for (int i = 1; i <= n; ++i)
				{
					sum += i * i;
				}
				return sum;
			};
		return sum_of_square(count);
	}
}

#pragma once
#include <array>
#include <numeric>
#include <string>
#include <type_traits>

namespace CONSTEXPRLAMBDA_Basic
{
	class ConstexprLambda_Basic
	{
	private:
		// Member to store a result from a compile-time calculation
		int m_fixedResult;
	public:
		ConstexprLambda_Basic() : m_fixedResult(0) {}
		void clear() { m_fixedResult = 0; }

		// 1. Basic C++17 Constexpr Lambda (implicitly constexpr)
		// Calculates the square of a number. Can be used at runtime or compile time.
		int calculateSquare(int x) const;

		// 2. Compile-Time Array Initialization
		// Uses a constexpr lambda to initialize an array at compile time.
		// The array is returned as a constant value.
		static constexpr size_t ARRAY_SIZE = 5;
		static constexpr std::array<int, ARRAY_SIZE> getCompileTimeArray()
		{
			// The lambda is immediately invoked (IIFE) and the result is used to initialize the array.
			// Since the lambda is implicitly constexpr and the initialization is a constant expression, 
			// the array is generated at compile time.
			constexpr auto generate_array = []()
				{
					std::array<int, ARRAY_SIZE> arr{};
					for (size_t i = 0; i < ARRAY_SIZE; ++i)
					{
						// We use a simple calculation, like (index + 1) * 10
						arr[i] = static_cast<int>((i + 1) * 10);
					}
					return arr;
				};
			// If 'generate_array()' is used in a constexpr context, the array is filled at compile time.
			// We ensure it's compile-time by marking the lambda usage with constexpr (though optional here).
			return generate_array();
		}

		// 3. Runtime usage of the implicitly constexpr lambda
		// Calculates the sum of a series using the lambda defined in calculateSquare, but called at runtime.
		int calculateRuntimeSum(int count) const;
	};
}

#pragma once
#include <array>
#include <string_view>

namespace ConstExprSamples
{

	constexpr unsigned long long factorial(int n)
	{
		return (n <= 1) ? 1 : (n * factorial(n - 1));
	}

	constexpr unsigned int gcd(unsigned int a, unsigned int b)
	{
		return (b == 0) ? a : gcd(b, a % b);
	}

	template <size_t N>
	constexpr int sum(const std::array<int, N>& arr)
	{
		int total = 0;
	#if 0 // for C++17 or earlier
		for (size_t i = 0; i < N; ++i)
		{
			total += arr[i];
		}
	#else // since C++20
		for (auto val : arr)
		{
			total += val;
		}
	#endif
		return total;
	}

	constexpr size_t str_len(const char* str)
	{
		size_t len = 0;
		while (*str++) ++len;
		return len;
	}
}

namespace ConstArrayUtils
{
	template<typename T, std::size_t N>
	consteval T sum(const std::array<T, N>& arr)
	{
		T total = 0;
		for (const auto& val : arr)
		{
			total += val;
		}
		return total;
	}

	template<typename T, std::size_t N>
	consteval T max(const std::array<T, N>& arr)
	{
		T maximum = arr[0];
		for (const auto& val : arr)
		{
			if (val > maximum)
			{
				maximum = val;
			}
		}
		return maximum;
	}
}
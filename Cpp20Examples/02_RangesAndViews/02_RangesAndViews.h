#pragma once
#include <optional>
#include <ranges>
#include <vector>
#include <iostream>
#include <string>
#include <numeric>

namespace rv = std::ranges::views;

inline auto filterEven(const std::vector<int>& input)
{
	return input | rv::filter([](int n) {return n % 2 == 0; });
}

inline auto squareAll(const std::vector<int>& input)
{
	return input | rv::transform([](int n) { return n * n; });
}

inline auto evenSquares(const std::vector<int>& input)
{
	return input 
		| rv::filter([](int n) {return n % 2 == 0; })
		| rv::transform([](int n) {return n * n; });
}

inline auto filterOddLessThanTen(const std::vector<int>& input)
{
	auto eliminated = input
		| rv::filter([](int n) { return n % 2 != 0; })   // odd
		| rv::filter([](int n) { return n < 10; })       // less than 10
		| rv::take(5);                                   // only the first 5 elements

	std::vector<int> result;
	result.reserve(input.size());
	for (auto n : eliminated)
	{
		result.emplace_back(n);
	}
	return result;
}

inline auto dropFirstThreeAndToString(const std::vector<int>& input)
{
	auto transformed =  input
					| rv::drop(3)
					| rv::transform([](int n) { return std::to_string(n); });
	return std::accumulate(std::next(transformed.begin()),transformed.end(),*transformed.begin(),
		[](const std::string& a, const std::string& b)
		{
			return a + " " + b;
		});
}

template<typename T>
auto enumerate(const std::vector<T>& input)
{
	auto indices = std::views::iota(0, static_cast<int>(input.size()));

	std::vector<std::pair<int, T>> result;
	result.reserve(input.size());

	for (auto i : indices)
	{
		result.emplace_back(i, input[i]);
	}
	return result;
}

template<std::ranges::input_range R>
	requires std::convertible_to<std::ranges::range_value_t<R>, int>
auto filterAndSquareOptional(const R& input)
{
	return input
		| rv::transform([](int n) -> std::optional<int>
			{
				if (n% 2 == 0)
				{
					return n * n;
				}
				return std::nullopt;
			})
		| rv::filter([](const std::optional<int>& opt) {return opt.has_value(); })
		| rv::transform([](const std::optional<int>& opt) {return *opt; });
}



template<typename R>
void printRange(const R& range)
{
	for (auto&& v : range)
	{
		std::cout << v << ' ';
	}
	std::cout << std::endl;
}

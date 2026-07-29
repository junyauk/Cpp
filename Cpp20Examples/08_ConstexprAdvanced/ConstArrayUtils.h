#pragma once

#include <array>
#include <cstddef>
#include <utility>

namespace ConstArrayUtils
{
    template <typename T, std::size_t N, std::size_t M = N>
    consteval auto filter(const std::array<T, N>& arr, auto predicate)
    {
        std::array<T, M> result{};
        std::size_t idx = 0;

        for (auto val : arr)
        {
            if (predicate(val))
            {
                result[idx++] = val;
            }
        }

        return std::pair{ result, idx };
    }

	template<typename T, typename Func, std::size_t N>
	constexpr auto map(const std::array<T, N>& arr, Func func) 
	{
		std::array<decltype(func(arr[0])), N> result{};
		for (size_t i = 0; i < N; ++i) 
		{
			result[i] = func(arr[i]);
		}
		return result;
	}

    template<typename T, std::size_t N>
    struct ConstArray
    {
        std::array<T, N> data;
        constexpr ConstArray(const std::array<T, N>& arr) : data(arr) {}
        constexpr T operator[](std::size_t i) const { return data[i]; }
        constexpr std::size_t size() const { return N; }

        template<typename Func>
        constexpr auto map(Func f) const
        {
            using ResultType = decltype(f(data[0]));
            std::array<ResultType, N> result{};
            for (std::size_t i = 0; i < N; ++i)
            {
                result[i] = f(data[i]);
            }
            return ConstArray<ResultType, N>(result);
        }

        template<typename Predicate>
        constexpr auto filter(Predicate pred) const
        {
            std::array<T, N> temp{};
            std::size_t count = 0;
            for (std::size_t i = 0; i < N; ++i)
            {
                if (pred(data[i]))
                {
                    temp[count++] = data[i];
                }
            }
            return std::pair<ConstArray<T, N>, std::size_t>{ ConstArray<T, N>(temp), count};
        }

        template<typename Func>
        constexpr auto reduce(Func f, T init) const
        {
            T result = init;
            for (auto val : data)
            {
                result = f(result, val);
			}
            return result;
        }
    };


}

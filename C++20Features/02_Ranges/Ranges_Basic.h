#pragma once
#include <vector>
#include <iostream>
#include <algorithm>
#include <ranges>
#include <numeric>
#include <sstream>

namespace Range_Basic
{
    /**
     * @brief Utility class to demonstrate C++20 Ranges and Views.
     */
    class RangeBasic
    {
    public:
        RangeBasic() = default;

        /**
         * @brief Demonstrates a Ranges pipeline:
         * 1. Filter for even numbers.
         * 2. Transform by multiplying by 2.
         * 3. Return the result as a space-separated string.
         * @param m_data The input vector of integers.
         * @return A string containing the processed elements (e.g., "4 8 12").
         */
        std::string processPipeline(const std::vector<int>& data) const
        {
            // C++20 Ranges View Pipeline
            auto processed_view = data
                // 1. Filter: Keep only even numbers (x % 2 == 0)
                | std::views::filter([](int x) { return x % 2 == 0; })
                // 2. Transform: Multiply each element by 2
                | std::views::transform([](int x) { return x * 2; });

            std::stringstream ss;
            // Iterate over the processed_view. 
            // The filtering and transformation happen lazily during this iteration.
            for (int val : processed_view)
            {
                ss << " " << val;
            }
            return ss.str().length() ? ss.str().substr(1) : "";
        }

        /**
         * @brief Demonstrates using a standard ranges algorithm.
         * @param m_data The input vector of integers.
         * @return The number of elements equal to 5.
         */
        int countTarget(const std::vector<int>& data) const
        {
            // std::ranges::count takes the entire range object, not begin/end iterators.
            return static_cast<int>(std::ranges::count(data, 5));
        }

        /**
         * @brief Demonstrates using std::views::take and a ranges algorithm on a subset.
         * @param m_data The input vector of integers.
         * @param n The number of elements to take from the start.
         * @return The sum of the first n elements.
         */
        int sumFirstN(const std::vector<int>& data, size_t n) const
        {
            // 1. Create a view containing only the first n elements (std::views::take)
            auto take_view = data | std::views::take(n);

            // 2. Use std::accumulate (or std::ranges::fold in C++23) on the view.
            // Since std::accumulate doesn't have a ranges version in C++20, 
            // we manually pass the begin/end iterators of the view.
            return std::accumulate(take_view.begin(), take_view.end(), 0);
        }
    };
}

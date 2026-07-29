#pragma once
#include <array>
#include <string_view>
#include <cstddef>
#include <algorithm>

namespace Constexpr_Basic
{
    /**
     * @brief Utility class to demonstrate C++20 constexpr capabilities, avoiding std::vector.
     */
    class ConstexprBasic
    {
    public:
        ConstexprBasic() = default;

        /**
         * @brief Converts a compile-time string to uppercase and returns the result as an array.
         * The entire operation runs at compile time, demonstrating complex C++20 constexpr logic.
         * @tparam N Size of the input string view.
         * @param str The input string view.
         * @return std::array<char, N> containing the uppercase result.
         */
        template<size_t N>
        static constexpr std::array<char, N> constexprToUpper(std::string_view str)
        {
            // C++20 allows complex state manipulation within local variables in constexpr.
            std::array<char, N> result{};
            if (str.length() != N)
            {
                // In a real application, this would ideally be diagnosed at compile time 
                // via a constexpr throw or static_assert, but for simplicity, we rely on the caller.
                return result;
            }

            for (auto i = 0; i < N; ++i)
            {
                char c = str[i];
                if ('a' <= c && c <= 'z')
                {
                    // Perform character transformation (an operation previously restricted or awkward)
                    result[i] = c - ('a' - 'A');    // Convert to uppercase
                }
                else
                {
                    result[i] = c;
                }
            }
            return result;
        }
 
        /**
         * @brief Defines the compile-time constant array by inlining the string transformation logic.
         * This ensures the compiler recognizes the constant expression required for global initialization.
         */
        static constexpr std::array<char, 12> getConstexprStringArray()
        {
            return constexprToUpper<12>("hello world!");
        }
    };
    // Demonstrate compile-time usage: the result is a hardcoded constant in the binary.
    constexpr std::array<char, 12> COMPILE_TIME_STRING_ARRAY = ConstexprBasic::getConstexprStringArray();

}
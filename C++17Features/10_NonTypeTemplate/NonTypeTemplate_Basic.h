#pragma once
#include <type_traits>
#include <string>

namespace NONTYPETEMPLATE_Basic
{
    // 1. Template using auto NTTP
    // N: The non-type template parameter whose type is deduced by 'auto'
    template<auto N>
    struct CompileTimeValue
    {
        // Use decltype(N) to get the actual type of N
        using ValueType = decltype(N);
        static constexpr ValueType value = N;

        // Return the value as a string for easy runtime testing
        static std::string toString()
        {
            if constexpr (std::is_same_v<ValueType, int>)
            {
                return std::to_string(N);
            }
            // Cannot use floating point types (double) as NTTP in C++17, so we only test int and bool.
            else if constexpr (std::is_same_v<ValueType, bool>)
            {
                return N ? "true" : "false";
            }
            else
            {
                return "Unsupported type for display";
            }
        }
    };

    // 2. Template using auto NTTP for a specific operation
    // Size: an NTTP (e.g., int)
    // Multiplier: an NTTP whose type is deduced (e.g., long, short)
    template<int Size, auto Multiplier>
    struct ArrayMultiplier
    {
        using ResultType = decltype(Multiplier);

        // Function to perform the multiplication, returning the result as a runtime value
        static ResultType getResult(ResultType baseValue)
        {
            return baseValue * Multiplier;
        }

        // Function to check the size used
        static constexpr int getSize() { return Size; }
    };

    class AutoNTTP_Basic
    {
    public:
        // Test 1: Int value deduction
        std::string testIntDeducation() const;
        // Test 2: Bool value deduction
        std::string testBoolDeducation() const;
        // Test 3: Operation with different NTTP types
        long testMultiplierOperation(long baseValue) const;
    };
}

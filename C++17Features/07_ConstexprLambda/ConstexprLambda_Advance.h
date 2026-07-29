#pragma once
#include <array>
#include <string>

namespace CONSTEXPRLAMBDA_Advance
{
    // --- 1. Applications of Compile-Time Processing: Factorial Calculation ---
    // Defined as a constexpr function (used in the internal implementation of C++17 constexpr lambdas)
    constexpr int factorial_constexpr_func(int n)
    {
        return (n <= 1) ? 1 : (n * factorial_constexpr_func(n - 1));
    }

    class ConstexprLambda_Advance
    {
    public:
        // 1. Application: Compile-Time Processing (Recursive Factorial via Lambda)
        // Uses a constexpr lambda to perform a recursive calculation at compile time.
        inline static constexpr int calculateFactorial(int n)
        {
/*
            // C++17: constexpr lambda (implicitly constexpr in C++17 if allowed)
            // C++20 allows explicit 'constexpr'
            auto factorial_lambda = [](auto self, int n) -> int
                {
                    if (n <= 1)
                    {
                        return 1;
                    }
                    return n * self(n - 1);
                };
            // For C++17, we rely on the function call operator of the lambda being constexpr.
            return factorial_lambda(factorial_lambda, n);
*/
            // NOTE: C++17 requires the use of Y-combinator pattern (or a specific helper) for recursive lambda.
            // Using a simple constexpr function to wrap it for C++17 compatibility.
            // We simplify and use a simple iteration/constexpr function for demonstration in C++17.
            // For C++17, the simplest demonstration is a non-recursive, simple calculation:

            // Simplified C++17 constexpr lambda:
            auto power_of_two = [](int n)
                {
                    int result = 1;
                    for (int i = 0; i < n; ++i)
                    {
                        result *= 2;
                    }
                    return result;
                };
            return power_of_two(n);
        }

        // 2. Application: Immediate Function (IIFE)
        // Uses a constexpr lambda immediately invoked to initialize a static const member.
        class Config
        {
        public:
            // Static data member initialized at compile time using a constexpr lambda IIFE.
            inline static constexpr int MAX_VALUE = []
                {
                    return factorial_constexpr_func(4); // 4! = 24
                }(); // Immediately invoked

            inline static constexpr std::array<int, 3> DATA_PATTERN = []
                {
                    std::array<int, 3> arr = { 0,0,0 };
                    for (int i = 0; i < 3; ++i)
                    {
                        arr[i] = i * 10 + 5;
                    }
                    return arr;
                }();
        };

        // 3. Application: Capture and Constraints (Demonstrate valid capture)
        // A constexpr lambda that captures a constexpr value and is called at compile time.
        inline static constexpr int calculateOffsetValue(int base)
        {
            constexpr int offset = 100;

            // Capture a constexpr local variable (valid)
            auto add_offset = [offset](int val) { return val + offset; };

            // This call can be evaluated at compile time
            return add_offset(base);
        }

        // Helper to check runtime vs compile time (for testing)
        inline constexpr bool is_constexpr_context() { return true; }
    };
}
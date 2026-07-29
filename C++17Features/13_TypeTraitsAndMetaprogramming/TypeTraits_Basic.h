#pragma once
#include <type_traits>
#include <iostream>

namespace TypeTraits_Basic
{
    // --- 1. Basic Type Trait Checks (Demonstration functions) ---

    // Function to check if a type T is an integral type (int, char, long, etc.)
    template<typename T>
    void check_integral()
    {
        // C++17 convenience variable: std::is_integral_v<T>
        if (std::is_integral_v<T>)
        {
            std::cout << "Type " << typeid(T).name() << " is an integral type.\n";
        }
        else
        {
            std::cout << "Type " << typeid(T).name() << " is NOT an integral type.\n";
        }
    }

    // Function to check if two types are the same
    template<typename T, typename U>
    void check_type_sameness()
    {
        // C++17 convenience variable: std::is_same_v<T, U>
        if (std::is_same_v<T, U>)
        {
            std::cout << "Types are the same.\n";
        }
        else
        {
            std::cout << "Types are different.\n";
        }
    }

    class TypeTraits_Basic
    {
    public:
        // --- 2. decltype Application ---
        // Uses decltype to deduce the return type of a lambda/expression.
        static constexpr auto createLambda()
        {
            // The return type is deduced as int (result of int * double is double, but we cast)
            return [](int a, double b) -> int
                {
                    return static_cast<int>(a * b);
                };
        }

        // Helper function to demonstrate integral check
        static void demoIntegralCheck();
    };

}

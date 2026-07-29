#pragma once
#include <iostream>
#include <string>
#include <type_traits>
#include <utility>

namespace TypeTraits_Advance
{
    // --- 1. Type Normalization and Decay (std::decay_t) ---
    template<typename T>
    void print_decayed_type_info(T&& value)
    {
        // A. True value type (removes reference, const, volatile, array-to-pointer, function-to-pointer)
        using decayedType = std::decay<T>;

        std::cout << "Original Type: " << typeid(T).name();
        std::cout << ", Decayed Type: " << typeid(decayedType).name();

        // B. Check if the original type was a reference (demonstrating std::is_lvalue_reference_v)
        if constexpr (std::is_lvalue_reference_v<decltype(value)>)
        {
            std::cout << " (Passed as L-value reference)";
        }
        else if constexpr (std::is_rvalue_reference_v<decltype(value)>)
        {
            std::cout << " (Passed as R-value reference)";
        }
        std::cout << std::endl;
    }

    // --- 2. Conditional Compilation (Constraining arithmetic types via std::enable_if_t) ---
    template<typename T>
    class Calculator
    {
    public:
        T value;
        Calculator(T val) : value(val) {}

        // This method is only available if T is an arithmetic type (int, float, etc.)
        template <typename U = T>
        std::enable_if_t<std::is_arithmetic_v<U>, T> add_and_double(U val_to_add) const
        {
            return (value + val_to_add) * 2;
        }

        // This method is only available if T is a pointer type
        template<typename U = T>
        std::enable_if_t<std::is_pointer_v<U>, U> increment_pointer() const
        {
            return value + 1;
        }
    };

    // --- 3. Perfect Forwarding Verification ---
    struct ForwardingTester
    {
        // Checks the type of the forwarded argument and prints the result
        template<typename T>
        static std::string forward_and_check(T&& arg)
        {
            // The type of the value *after* reference removal
            using ValueType = std::remove_reference_t<T>;

            // Check if T is an L-value reference (meaning the argument was an L-value)
            if (std::is_lvalue_reference_v<T>)
            {
                return "Forwarded L-value (" + std::string{ typeid(T).name()} + ")";
            }
            // If T is NOT a reference (meaning the argument was an R-value)
            else
            {
                return "Forwarded R-value (" + std::string{ typeid(T).name() } + ")";
            }
        }
    };
}


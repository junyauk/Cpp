#pragma once
#include <iostream>
#include <string>
#include <utility>
#include <tuple>

namespace FOLDEXPRESSIONS_Advance
{
    class FoldExpressions_Advance
    {
    public:
        // 1. Application: Logical Operations (AND/OR Fold)
        // Checks if all parameters are true (Unary Right Fold: AND)
        template<typename... Args>
        static constexpr bool all_true(Args... args)
        {
            // Unary Right Fold: (... && args)
            // (argN && (argN-1 && (... && arg1)))
            return (true && ... && args);
        }

        // Checks if at least one parameter is true (Unary Right Fold: OR)
        template<typename... Args>
        static constexpr bool any_true(Args... args)
        {
            // Unary Right Fold: (... || args)
            return (false || ... || args);
        }

        // 2. Application: Right vs. Left Fold (Comma Operator)
        // Uses the comma operator to sequence operations.
        // Unary Left Fold: (args, ...)
        template<typename T, typename... Args>
        static void process_left_fold_comma(T first, Args... args)
        {
            // The result of the fold is discarded, but the side effects (increment) occur.
            // (first, args1), args2), ...
            (first, ..., args) = (first, args, ...); // Example structure - not executable.

            // To demonstrate side effects:
            auto comma_fold = ([&](auto x) { x++; }, ..., first);
            // In C++, the comma operator is tricky for side-effects in fold. 
            // We use a demonstration function for clearer comparison in tests.
        }

        // 3. Application: Stream Output
        // Outputs all arguments to the given output stream.
        template<typename... Args>
        static void print_to_stream(std::ostream& os, const Args&... args)
        {
            // Binary Left Fold: (((os << first) << rest1) << rest2) ...
            // The initial value 'os' acts as the accumulator (the fold's left operand).
            (os << ... << args) << '\n';
        }
    };

    // Helper class for testing side effects in comma fold (Test only)
    class Counter
    {
    private:
        int& m_value;
    public:
        Counter(int& val) : m_value(val) {}
        void increment() { m_value++; }

        // Overload operator, to sequence the increment operation.
        // T operator,(T&&) is complicated. We'll use a direct function call for demonstration.

        // A simple function to increment all parameters (demonstrating execution order)
        template<typename... Args>
        static void sequence_increment(Args&... args)
        {
            // Unary Left Fold using the comma operator and lambda side effects
            // This ensures all lambda calls (side effects) are executed sequentially.
            // ((lambda(arg1), lambda(arg2)), ..., lambda(argN))
            (([](auto& x) {x++; }(args)), ...);
        }
    };
}

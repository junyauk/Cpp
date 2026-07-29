#pragma once
#include <variant>
#include <string>
#include <vector>
#include <functional>
#include <iostream>

namespace VARIANT_Advance
{
    // --- 2. Type definitions for type-safe error handling ---
    using SuccessType = double;
    struct ErrorInfo
    {
        int code;
        std::string message;
    };

    // ResultType holds either a successful value or an error structure.
    using ResultType = std::variant<SuccessType, ErrorInfo>;

    // --- 1. Type Definition for Visitor Pattern ---
    using TypeA = int;
    using TypeB = std::string;
    using VariantA = std::variant<TypeA, TypeB>;
    // Contains TypeA and a different type (double)
    using VariantB = std::variant<TypeA, SuccessType>;

    // --- 3. Type definitions including monostate applications ---
    using StatusVariant = std::variant<std::monostate, int, bool>;

    // Helper for C++17/20 overloads pattern (for std::visit)
    template<class... Ts> struct overload : Ts... { using Ts::operator()...; };
    template<class... Ts> overload(Ts...) -> overload<Ts...>;

    class Variant_Advance
    {
    public:
        // 1. Application: Multiple Visit (Poly-visitor)
        // Visits two variants simultaneously and combines their values based on their types.
        std::string processMultipleVariants(const VariantA& vA, const VariantB& vB) const;

        // 2. Application: Type-safe Error Handling
        // Returns a ResultType (SuccessType or ErrorInfo)
        ResultType calculateValue(double input) const;
        // 2b. Checks for ErrorInfo using std::get_if
        std::string checkResultForError(const ResultType& result) const;
        // 3. Application: std::monostate for explicit 'Empty' status
        // Demonstrates explicit monostate handling in a visitor.
        std::string checkStatus(const StatusVariant& status) const;
    };
}

#include "pch.h"
#include <sstream>
#include <stdexcept>
#include "Variant_Advance.h"

namespace VARIANT_Advance
{
    // 1. Application: Multiple Visit (Poly-visitor)
    std::string Variant_Advance::processMultipleVariants(const VariantA& vA, const VariantB& vB) const
    {
        std::stringstream ss;

        // Use std::visit with the overload pattern to handle all combinations
        std::visit(overload
            {
                // Case 1: Both are TypeA (int)
                [&ss](TypeA a1, TypeA a2)
                {
                    ss << "Both Int: " << a1 * a2;
                },
                // Case 2: VariantA is string, VariantB is double
                [&ss](const TypeB& s, double d)
                {
                    ss << "String (" << s << ") and Double (" << d << ")";
                },
                // Case 3: Other combinations (e.g., int and double)
                [&ss](auto&& arg1, auto&& arg2)
                {
                    ss << "Other Combination: Types differ or unexpected.";
                }

            }, vA, vB); // Pass both variants to std::visit
        return ss.str();
    }

    // 2. Application: Type-safe Error Handling
    ResultType Variant_Advance::calculateValue(double input) const
    {
        if (input < 0)
        {
            // Returns an error structure (ErrorInfo)
            return ErrorInfo{-1, "Input cannot be negative." };
        }
        else if (input == 0)
        {
            // Returns a successful value (SuccessType)
            return SuccessType{ 100.0 };
        }
        else
        {
            // Returns a calculated successful value
            return SuccessType{ input * 2.5 };
        }

    }

    // 2b. Checks for ErrorInfo using std::get_if
    std::string Variant_Advance::checkResultForError(const ResultType& result) const
    {
        // Use std::get_if for safe, non-throwing access
        if (const ErrorInfo* err = std::get_if<ErrorInfo>(&result))
        {
            // ErrorInfo is present
            return "ERROR: Code " + std::to_string(err->code) + ", Message: " + err->message;
        }
        else if (const SuccessType* val = std::get_if<SuccessType>(&result))
        {
            // SuccessType is present
            return "SUCCESS: Value is " + std::to_string(*val);
        }

        // Should not happen if ResultType only contains these two types
        return "UNKNOWN STATE";
    }

    // 3. Application: std::monostate for explicit 'Empty' status
    std::string Variant_Advance::checkStatus(const StatusVariant& status) const
    {
        // Explicitly handle std::monostate
        return std::visit(
            overload
            {
                [](std::monostate) {return std::string{"Status: Uninitialized/Empty"}; },
                [](int i) {return "Status: Int Value " + std::to_string(i); },
                [](bool b) { return std::string("Status: Bool Value ") + (b ? "True" : "False"); }
            }, status);
    }
}

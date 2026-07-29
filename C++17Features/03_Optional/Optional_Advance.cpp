#include "pch.h"
#include <sstream>
#include <stdexcept>
#include "Optional_Advance.h"

namespace OPTIONAL_Advance
{
    // Helper function for chaining: Takes an int, returns an optional string
    std::optional<std::string> stage2_transform(int input)
    {
        if (input % 2 == 0)
        {
            return std::nullopt;
        }
        return "Final Result: " + std::to_string(input * 3);
    }

    // 1. Application: Monadic Chaining (Non-C++23 version)
    std::optional<std::string> Optional_Advance::chainedProcessing(int initialValue) const
    {
        // Stage 1: Returns nullopt if initialValue < 10
        std::optional<int> stage1_result;
        if (initialValue > 10)
        {
            stage1_result = initialValue - 5;
        }

        // Manual Chaining (Simulating and_then):
        if (stage1_result.has_value())
        {
            // Stage 2: Only runs if Stage 1 was successful.
            // Passes the unwrapped value (*stage1_result) to stage2_transform.
            return stage2_transform(stage1_result.value());
        }
        return std::nullopt;    // Failure at Stage 1
    }

    // 2. Application: In-place construction and move semantics
    std::string Optional_Advance::checkMoveCost(std::optional<LargeData>&& optData) const
    {
        // When transferring LargeData *out* of an optional, 
        // using std::move ensures a move constructor is called, not a copy.
        if (optData.has_value())
        {
            // std::move(*optData) ensures the LargeData object is moved out of the optional.
            LargeData moved_data = std::move(*optData);
            optData.reset();
            return moved_data.name; // Name should include "_M" if move happened correctly
        }
        return "Empty";
    }

    // 3. Application: Exception Safety Check
    bool Optional_Advance::checkExceptionSafety(const std::optional<int>& opt) const
    {
        try
        {
            // If opt is empty, value() throws std::bad_optional_access
            int val = opt.value();
            // If successful
            return true;
        }
        catch (const std::bad_optional_access& e)
        {
            // Successfully caught the exception for an empty optional
            // std::cout << "Caught exception: " << e.what() << std::endl;
            return false;
        }
        catch (...)
        {
            return false;
        }
    }
}


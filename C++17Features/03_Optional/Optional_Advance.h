#pragma once
#include <optional>
#include <string>
#include <utility>
#include <memory>
#include <iostream>
#include <vector>

namespace OPTIONAL_Advance
{
    // --- 2. Large data structures used for managing copy/move costs ---
    struct LargeData
    {
        std::string name;
        std::vector<int> data;

        // Constructor to report activity
        LargeData(std::string n, size_t size) : name(std::move(n)), data(size, 1)
        {
            // std::cout << "LargeData::Constructed " << name << std::endl;
        }
        // Copy Constructor
        LargeData(const LargeData& other) : name(other.name + "_C"), data(other.data)
        {
            // std::cout << "LargeData::Copied " << name << std::endl;
        }
        // Move Constructor
        LargeData(LargeData&& other) noexcept : name(other.name + "_M"), data(std::move(other.data))
        {
            // std::cout << "LargeData::Moved " << name << std::endl;
        }
    };

    // --- 1. Helper functions for chained processing ---
    // Takes an int, processes it, and returns an optional string.
    std::optional<std::string> stage2_transform(int input);

    class Optional_Advance
    {
    public:
        // 1. Application: Monadic Chaining (Non-C++23 version)
        // Safely chains two processing stages and returns the final result.
        std::optional<std::string> chainedProcessing(int initialValue) const;

        // 2. Application: In-place construction and move semantics
        // Creates a LargeData optional using in_place and returns its name.
        std::string checkMoveCost(std::optional<LargeData>&& optData) const;

        // 3. Application: Exception Safety Check
        // Calls value() on a potentially empty optional and handles the exception.
        bool checkExceptionSafety(const std::optional<int>& opt) const;
    };
}


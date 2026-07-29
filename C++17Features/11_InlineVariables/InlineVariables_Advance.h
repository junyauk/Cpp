#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <string>

namespace INLINE_VARIABLES_Advance
{
    // --- 1. Static Data Member Initialization ---
    class Configuration
    {
    public:
        // C++17 inline variable: 
        // Allows definition and initialization in the header file.
        // The linker guarantees there is only one instance across all translation units.
        // This is non-const and initialized at runtime.
        inline static std::string APPLICATION_VERSION = "v1.1.0 - alpha";

        // C++17 inline variable for a complex, runtime-initialized object
        inline static std::map<int, std::string> ERROR_MAP =
        {
            {100, "ERR_INVALID_INPUT"},
            {200, "ERR_NOT_FOUND"}
        };

        // Constexpr variable (implicitly inline in C++17) - Comparison
        static constexpr int MAX_THREADS = 16;
    };

    // --- 2. Header-Only Library Design Example ---
    // A constant vector defined in the header for all users.
    // It's not constexpr, so it relies on 'inline' for ODR compliance.
    inline const std::vector<double> SHARED_CONSTANTS =
    {
        3.14159, 2.71828, 1.41421
    };

    class InlineVariables_Advance
    {
    public:
        // Helper function to demonstrate that the variable is shared (reference check)
        static const std::string& getVersionRef()
        {
            return Configuration::APPLICATION_VERSION;
        }
        // Helper function to modify the shared inline variable (if it's non-const)
        static void modifyVersion(const std::string& newVersion)
        {
            Configuration::APPLICATION_VERSION = newVersion;
        }
    };
}

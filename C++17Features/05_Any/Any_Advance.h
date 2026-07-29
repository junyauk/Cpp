#pragma once
#include <any>
#include <map>
#include <vector>
#include <string>
#include <utility>
#include <iostream>

namespace ANY_Advance
{
    // --- 3. Large data structures used for managing copy/move costs ---
    struct BigPayload
    {
        std::string label;
        std::vector<int> data;

        // Constructor to report activity
        BigPayload(std::string name, size_t size) : label(std::move(name)), data(size, 1) {}

        // Copy Constructor: Reports a copy operation
        BigPayload(const BigPayload& other) : label(other.label + "_C"), data(other.data)
        {
            // std::cout << "BigPayload::Copied " << label << std::endl;
        }

        // Move Constructor: Reports a move operation
        BigPayload(BigPayload&& other) noexcept : label(other.label + "_M"), data(std::move(other.data))
        {
            // std::cout << "BigPayload::Moved " << label << std::endl;
        }
    };

    class Any_Advance
    {
    private:
        // 1. Dynamic Configuration Map
        std::map<std::string, std::any> m_config;
    public:
        Any_Advance() = default;

        // 1. Application: Dynamic Configuration Map Management
        // Sets a configuration value using std::any.
        void setConfig(const std::string& key, std::any value);

        // 2. Application: Type Safety and Retrieval
        // Retrieves a value, checks the type, and returns a formatted string.
        std::string getConfigInfo(const std::string& key) const;

        // 3. Application: Copy vs. Move Cost
        // Stores and then moves a BigPayload object out of std::any.
        std::string processPayloadCost(const BigPayload& payload);
    };
}

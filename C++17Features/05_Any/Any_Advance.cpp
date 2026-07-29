#include "pch.h"
#include <sstream>
#include <stdexcept>
#include "Any_Advance.h"

namespace ANY_Advance
{
    // 1. Application: Dynamic Configuration Map Management
    void Any_Advance::setConfig(const std::string& key, std::any value)
    {
        // Simply store the std::any object in the map
        m_config[key] = value;
    }

    // 2. Application: Type Safety and Retrieval
    std::string Any_Advance::getConfigInfo(const std::string& key) const
    {
        auto it = m_config.find(key);
        if (it == m_config.end())
        {
            return "Key not found.";
        }

        const std::any& value = it->second;

        // Use typeid and type() for safe type identification
        if (value.type() == typeid(int))
        {
            // std::any_cast<T> for direct retrieval
            return "Type: int, Value: " + std::to_string(std::any_cast<int>(value));
        }
        else if (value.type() == typeid(double))
        {
            return "Type: double, Value: " + std::to_string(std::any_cast<double>(value));
        }
        else if (value.type() == typeid(std::string))
        {
            // Use pointer version (std::any_cast<T*>): does not throw, returns nullptr on failure
            if (const auto* pStr = std::any_cast<std::string>(&value))
            {
                return "Type: std::string, Value: " + *pStr;
            }
        }
        return "Type: Unknown (" + std::string{ value.type().name() } + ")";
    }

    // 3. Application: Copy vs. Move Cost
    std::string Any_Advance::processPayloadCost(const BigPayload& payload)
    {
        // 1. Copying the payload into std::any (Costly)
        std::any any_payload = payload;

        // 2. Moving the payload out of std::any (Cost is cheaper than copy)
        // Use std::any_cast<T&&>() to move the content out (C++17 behavior)
        try
        {
            BigPayload moved_payload = std::any_cast<BigPayload&&>(std::move(any_payload));
            return moved_payload.label;
        }
        catch (const std::bad_any_cast& e)
        {
            return "Cast error: " + std::string{ e.what() };
        }
    }
}

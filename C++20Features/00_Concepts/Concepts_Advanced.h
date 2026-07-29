#pragma once
#include <concepts>
#include <string>
#include <sstream>
#include <vector>
#include <format>

namespace Concepts_Advance
{
    // --- 1. Custom Concept Definitions ---

    /**
     * @brief Concept that requires a type T to have a const member function 'to_string()' returning std::string.
     */
    template<typename T>
    concept Printable = requires(const T & t)
    {
        { t.to_string() } -> std::same_as<std::string>;
    };

    /**
     * @brief Concept that requires a type T to have an accessible member 'id' convertible to int.
     */
    template<typename T>
    concept HasID = requires(T t)
    {
        { t.id } -> std::convertible_to<int>;
    };

    /**
     * @brief Composite Concept: Requires a type to be both Printable and HasID.
     */
    template<typename T>
    concept LoggableData = Printable<T> && HasID<T>;

    // --- 2. Data Structure Example ---

    struct UserProfile
    {
        int id;
        std::string username;

        std::string to_string() const
        {
            return std::format("[ID:{}] User: {}", id, username);
        }
    };

    // --- 3. Constrained Container Implementation ---

    /**
     * @brief A simple logger that only accepts and stores LoggableData types.
     * @tparam T The type of data to store, must satisfy LoggableData.
     */
    template<LoggableData T>
    class LogDataStore
    {
    private:
        std::vector<T> m_data;
    public:
        void addRecord(const T& record)
        {
            m_data.push_back(record);
        }

        std::string dump_log() const
        {
            std::string log;
            for (const auto& record : m_data)
            {
                // Guaranteed access to 'id' member and 'to_string' method
                log += std::format("LOG ENTRY (ID={}): ", record.id);
                log += record.to_string() + "\n";
            }
            return log;
        }

        size_t count() const { return m_data.size(); }
    };
}


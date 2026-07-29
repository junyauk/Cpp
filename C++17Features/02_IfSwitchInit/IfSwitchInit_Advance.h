#pragma once
#include <string>
#include <optional>
#include <memory>

namespace IFSWITCHINITIALIZER_Advance
{
    // 1. Mock lock class used in RAII resource management applications
    // Simulates a RAII lock object
    class SimpleLock
    {
    private:
        bool m_isLocked = false;
        std::string m_name;
    public:
        SimpleLock(std::string name) : m_name(name), m_isLocked(true) {}
        ~SimpleLock() { m_isLocked = false; }
        bool isLocked() const { return m_isLocked; }
        const std::string& getName() const { return m_name; }
    };

    // --- 2. Class used for managing the lifetime of temporary objects ---
    class ResourceProcessor
    {
    public:
        // Returns a resource only if the input is valid (simulates I/O or database access)
        std::optional<std::unique_ptr<int>> getResource(int id) const;
    };

    class Initializer_Advance
    {
    public:
        // 1. Application: RAII Lock Management
        // Uses the initializer to acquire a lock, ensuring it's held only within the if-block.
        std::string processWithLock(bool needsLocking) const;

        // 2. Application: Lifetime management for optional return values
        // Uses the initializer to check for a resource's existence and hold its unique_ptr.
        std::string checkAndProcessResource(int id) const;

        // 3. Application: Complex initialization in a switch statement
        // Initializes a status value and checks it against different cases.
        std::string checkStatusValue(int input) const;
    };
}

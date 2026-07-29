#include "pch.h"
#include "IfSwitchInit_Advance.h"

namespace IFSWITCHINITIALIZER_Advance
{
    // Returns a resource only if the input is valid (simulates I/O or database access)
    std::optional<std::unique_ptr<int>> ResourceProcessor::getResource(int id) const
    {
        if (id > 0)
        {
            // Returns a valid unique_ptr resource
            return std::make_optional(std::make_unique<int>(id * 10));
        }
        return std::nullopt;
    }

    // 1. Application: RAII Lock Management
    std::string Initializer_Advance::processWithLock(bool needsLocking) const
    {
        // C++17 Initializer: The SimpleLock object 'lock' is created and its lifetime 
        // is confined to the if/else block.
        if (SimpleLock lock("MyLock"); needsLocking)
        {
            if (lock.isLocked())
            {
                // Lock is guaranteed to be held here (RAII in action)
                return "Locked processing done by: " + lock.getName();
            }
        }
        else
        {
            // 'lock' is still in scope, even in the else block!
            return "Skipped locking. Lock name: " + lock.getName() + ", State: " + (lock.isLocked() ? "Locked" : "Unlocked (Error)");
        }
        return "No locking needed.";
    }

    // 2. Application: Lifetime management for optional return values
    std::string Initializer_Advance::checkAndProcessResource(int id) const
    {
        ResourceProcessor processor;

        // C++17 Initializer: result is initialized, and its lifetime extends across the if block.
        // The optional is checked for existence.
        if (auto result = processor.getResource(id); result.has_value())
        {
            // The unique_ptr is held by *result, ensuring the resource is valid here.
            int value = *result.value();
            return "Resource processed. Value: " + std::to_string(value);
        }
        else
        {
            // 'result' is still in scope here, allowing for logging/error checking
            return "Resource not found for ID: " + std::to_string(id);
        }
    }

    // 3. Application: Complex initialization in a switch statement
    std::string Initializer_Advance::checkStatusValue(int input) const
    {
        // C++17 Initializer: Initializes 'status' which is then checked in the switch
        switch (int status = input % 3; status)
        {
        case 0:
            // 'status' is in scope here
            return "Case Zero (Input % 3 = 0)";
        case 1:
            return "Case One (Input % 3 = 1)";
        default:
            // 'status' is in scope here
            return "Case Default (Input % 3 = 2)";
        }
    }
}

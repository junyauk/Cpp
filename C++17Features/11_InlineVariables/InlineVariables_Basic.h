#pragma once
#include <string>
#include <map>

namespace INLINEVARIABLES_Basic
{
    // 1. Global Inline Constant
    // This constant can be defined and initialized here, and safely included 
    // in multiple CPP files without ODR violation.
    inline const std::string VERSION_STRING = "C++17 Feature Set v1.0";

    // 2. Inline Static Member Variable (No longer needs CPP definition)
    class Counter
    {
    public:
        // C++17: inline static is used to define and initialize the static member 
        // within the class definition (in the header).
        inline static int instanceCount = 0;

        Counter() { instanceCount++; }
        ~Counter() { instanceCount--; }
    };

    // 3. Inline map for configuration (Complex type initialization in header)
    // This map is defined once, even if included in multiple files.
    inline const std::map<std::string, int> CONFIG_DEFAULT =
    {
        {"Timeout", 30},
        {"Retries", 3}
    };

    class InlineVariables_Basic
    {
    public:
        // Getter for the global constant
        std::string getVersion() const { return VERSION_STRING; }

        // Getter for a config value
        int getDefaultTimeout() const;

        // Function to create an instance of Counter and return the current count
        int getCurrentCountAndInstance() const;
    };

    int access_inline_counter();
    int get_inline_timeout();

}
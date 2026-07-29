#pragma once
#include <map>
#include <vector>
#include <string>
#include <tuple>
#include <array>

namespace STRUCTUREDBINDINGS_Advance
{
    // --- 3. Tuple-like Type Application (Conceptual) ---
    // Using std::array to demonstrate tuple-like behavior.

    // Class to demonstrate map operations
    class MapDemo
    {
    private:
        std::map<int, std::string> m_dataMap = { {1, "One"}, {2, "Two"} };
    public:
        MapDemo() = default;

        // 1. Reference binding and insertion result
        // Tries to update an existing key, modifying the value via the iterator reference.
        std::string updateExisting(int key, const std::string& newValue);

        // 2. Application in iteration
        // Iterates through the map and lists key-value pairs.
        std::vector<std::pair<int, std::string>> listMapContents() const;
    };

    // Class for testing advanced binding features
    class Bindings_Advance
    {
    public:
        // 3. Tuple-like Type: Reference binding on std::array
        // Binds the array elements by reference to modify the original array.
        void modifyArrayElements(std::array<int, 2>& arr, int newValue) const;
    };
}


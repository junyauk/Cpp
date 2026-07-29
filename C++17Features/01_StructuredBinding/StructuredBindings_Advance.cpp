#include "pch.h"
#include <sstream>
#include <iostream>
#include "StructuredBindings_Advance.h"

namespace STRUCTUREDBINDINGS_Advance
{
    // 1. Reference binding and insertion result (Advanced use)
    std::string MapDemo::updateExisting(int key, const std::string& newValue)
    {
        // map::insert returns std::pair<iterator, bool>.
        // Structured Binding: Decomposes the pair into 'it' and 'inserted'.
        auto [it, inserted] = m_dataMap.insert({ key, newValue });
        if (!inserted)
        {
            // If the key already exists, 'it' points to the existing element.
            // Modify the value via the iterator's second element.
            it->second = newValue;
            return "UPDATED: Key " + std::to_string(it->first) + " modified.";
        }
        else
        {
            return "INSERTED: New key " + std::to_string(it->first) + " added.";
        }
    }

    // 2. Application in iteration
    std::vector<std::pair<int, std::string>> MapDemo::listMapContents() const
    {
        std::vector<std::pair<int, std::string>> contents;

        // C++17 Structured Binding used in a range-based for loop.
        // const auto& [key, value] extracts elements as const references.
        for (auto [key, value] : m_dataMap)
        {
            contents.emplace_back(key, value);
        }
        return contents;
    }

    // 3. Tuple-like Type: Reference binding on std::array
    void Bindings_Advance::modifyArrayElements(std::array<int, 2>& arr, int newValue) const
    {
        // auto& [ref1, ref2] = arr; binds to the array elements by reference.
        auto& [ref1, ref2] = arr;
        // Change the original array element through the reference (ref2).
        ref2 = newValue;
    }
}

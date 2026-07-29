#pragma once
#include <iostream>
#include <string>
#include <array>
#include <utility>
#include <string_view>
#include <type_traits>

namespace NonTypeTemplate_Advance
{
    // --- 1. Compile-Time Hash Function (Updated to use const char* and size for C++17) ---
    // Uses FNV-1a algorithm to generate a hash at compile time.
    constexpr uint32_t fnvla_hash_32(const char* str, size_t size)
    {
        uint32_t hash = 2166136261u; // FNV offset basis
        for (auto i = 0; i < size; ++i)
        {
            hash ^= static_cast<uint32_t>(str[i]);
            hash *= 16777619u; // FNV prime
        }
        return hash;
    }

    // --- 1. Compile-Time Hashmap Key Wrapper (C++17 compatible) ---
    // Accepts a raw pointer and size as non-type template arguments to hash a string literal.
    template<const char* Str, size_t Size>   // C++17 supports const char* and integral types
    struct ConstexprHash
    {
        // Hash value is computed at compile time
        static constexpr uint32_t value = fnvla_hash_32(Str, Size);
    };

    // --- 3. Unifying Heterogeneous Data Structures ---
    // Class that accepts different integral types (e.g., int, char) using auto, 
    // but provides a unified interface.
    template<auto Start, auto End>
    class Range
    {
    public:
        // C++17: Get the deduced type using decltype(Start)
        using ValueType = decltype(Start);

        static_assert(std::is_integral_v<ValueType>, "Range must be integral type.");
        static_assert(Start <= End, "Start value must not exceed End value."); 

        ValueType size() const { return End - Start; }

        // Unified processing
        std::string getInfo() const
        {
            return "Range: [" + std::to_string(static_cast<long long>(Start)) +
                " to " + std::to_string(static_cast<long long>(End)) +
                "], Type: " + std::string(typeid(ValueType).name());
        }
    };

    class NonTypeTemplate_Advance
    {
    public:
        // 2. Application: std::array Type Deduction
        // Uses 'auto' to deduce the type of the non-type template argument N (usually size_t).
        template<auto N>
        static constexpr auto createSizeArray()
        {
            // N is used to determine the array size
            return std::array<int, N>{};
        }

        // 1. Application: Compile-Time Hashmap Key Verification (Runtime comparison helper)
        // Retrieves the hash value generated from a runtime std::string_view for comparison.
        static constexpr uint32_t getHashValue(std::string_view key)
        {
            // FNV-1a logic repeated here for runtime comparison
            uint32_t hash = 2166136261u;
            for (auto c : key)
            {
                hash ^= static_cast<uint32_t>(c);
                hash *= 16777619u;
            }
            return hash;
        }

        // 3. Application: Creates an instance of the Range class
        template<auto S, auto E>
        static Range<S, E> createRange()
        {
            return Range<S, E>{};
        }
    };
}


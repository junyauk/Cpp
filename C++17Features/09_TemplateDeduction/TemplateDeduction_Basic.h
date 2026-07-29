#pragma once
#include <vector>
#include <string>

namespace TEMPLATEDEDUCTION_Basic
{
    // 1. A custom container class template to test CTAD
    template<typename T>
    class SimpleWrapper
    {
    private:
        T m_value;
    public:
        // Constructor that takes a single value of type T
        SimpleWrapper(T val) : m_value(val) {}

        T getValue() const { return m_value; }
    };

    template<typename T>
    class CountedBuffer
    {
    private:
        size_t m_count;
        // T* m_data; // Not stored for simplicity, just demonstrating deduction

    public:
        // Constructor takes a pointer and a count
        CountedBuffer(T* data, size_t count) : m_count(count)
        {
            // Note: In a real scenario, we would manage the memory pointed to by 'data'.
        }

        size_t getCount() const { return m_count; }
        // T* getData() const { return m_data; }
    };

    // =========================================================================
    // DEDUCTION GUIDES (for C++17 CTAD)
    // =========================================================================

    // Deduction Guide for CountedBuffer: 
    // If the constructor is called with (T*, size_t), deduce T from the pointer type.
    template<typename T>
    CountedBuffer(T*, size_t) -> CountedBuffer<T>;

    // Utility class to demonstrate CTAD usage
    class CTAD_Basic
    {
    public:
        // Test 1: Implicit CTAD for SimpleWrapper
        // Creates a SimpleWrapper<int> using CTAD and returns the stored value.
        int testSimpleIntWrapper(int val) const;

        // Test 2: Implicit CTAD for SimpleWrapper with string (different type)
        // Creates a SimpleWrapper<std::string> using CTAD.
        std::string testSimpleStringWrapper(const std::string& val) const;

        // Test 3: Explicit Deduction Guide usage for CountedBuffer
        // Uses CTAD based on the manual deduction guide and returns the count.
        size_t testCountedBufferDeduction() const;
    };
}

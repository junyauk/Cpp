#include "pch.h"
#include "framework.h"
#include "TemplateDeduction_Basic.h"

namespace TEMPLATEDEDUCTION_Basic
{
    // Test 1: Implicit CTAD for SimpleWrapper<int>
    int CTAD_Basic::testSimpleIntWrapper(int val) const
    {
        // C++17: The compiler deduces SimpleWrapper<int> from the argument 'val'
        SimpleWrapper wrapper(val);
        return wrapper.getValue();
    }

    // Test 2: Implicit CTAD for SimpleWrapper<std::string>
    std::string CTAD_Basic::testSimpleStringWrapper(const std::string& val) const
    {
        // C++17: The compiler deduces SimpleWrapper<std::string>
        SimpleWrapper wrapper(val);
        return wrapper.getValue();
    }

    // Test 3: Explicit Deduction Guide usage for CountedBuffer
    size_t CTAD_Basic::testCountedBufferDeduction() const
    {
        int data[] = { 10,20,30 };

        // C++17: The compiler uses the Deduction Guide:
        // CountedBuffer(T*, size_t) -> CountedBuffer<T>
        // T is deduced to be 'int' from the first argument 'data' (which decays to int*).
        CountedBuffer buffer(data, 3);

        // The resulting type is CountedBuffer<int>
        return buffer.getCount();
    }
}


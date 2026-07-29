#include "pch.h"
#include "framework.h"
#include "NonTypeTemplate_Basic.h"

namespace NONTYPETEMPLATE_Basic
{

    // Test 1: Int value deduction
    std::string AutoNTTP_Basic::testIntDeducation() const
    {
        // The compiler deduces N=10 and ValueType=int
        return CompileTimeValue<10>::toString();
    }

    // Test 2: Bool value deduction
    std::string AutoNTTP_Basic::testBoolDeducation() const
    {
        // The compiler deduces N=true and ValueType=bool
        return CompileTimeValue<true>::toString();
    }

    // Test 3: Operation with different NTTP types
    long AutoNTTP_Basic::testMultiplierOperation(long baseValue) const
    {
        // The compiler deduces Size=5 (int) and Multiplier=20L (long)
        // Note: The 'L' suffix is crucial here to force 'Multiplier' to be 'long'
        return ArrayMultiplier<5, 20L>::getResult(baseValue);
    }
}

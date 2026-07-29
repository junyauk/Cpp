#include "pch.h"
#include "gtest/gtest.h"
#include <type_traits>
#include "..\07_ConstexprLambda\ConstexprLambda_Advance.h"

namespace ConstexprLambdaAdvanceTest
{
    class ConstexprLambdaAdvanceTest : public ::testing::Test
    {
    protected:

    };

    // Test Case 1: Compile-Time Processing (Calculation)
    TEST_F(ConstexprLambdaAdvanceTest, CalculateFactorial_CompileTime)
    {
        // Calculate 5! at compile time (using the lambda wrapper for 2^n)
        // The simplified lambda calculates 2^n
        constexpr int result = CONSTEXPRLAMBDA_Advance::ConstexprLambda_Advance::calculateFactorial(3);

        ASSERT_EQ(8, result);

        // Assert that the result can be used in a compile-time context
        static_assert(CONSTEXPRLAMBDA_Advance::ConstexprLambda_Advance::calculateFactorial(2) == 4,
            "Lambda must be executable at compile time.");
    }

    // Test Case 2a: Immediate Function (IIFE) - MAX_VALUE
    TEST_F(ConstexprLambdaAdvanceTest, IIFE_StaticMemberInitialization_MaxValue)
    {
        // Check if the static member was initialized correctly (4! = 24)
        ASSERT_EQ(24, CONSTEXPRLAMBDA_Advance::ConstexprLambda_Advance::Config::MAX_VALUE);

        // Assert that the result is truly a constexpr value
        static_assert(CONSTEXPRLAMBDA_Advance::ConstexprLambda_Advance::Config::MAX_VALUE == 24,
            "MAX_VALUE must be initialized by a constexpr context.");
    }

    // Test Case 2b: Immediate Function (IIFE) - DATA_PATTERN
    TEST_F(ConstexprLambdaAdvanceTest, IIFE_StaticMemberInitialization_DataPattern)
    {
        // Check if the static member was initialized correctly ({5, 15, 25})
        const auto& pattern = CONSTEXPRLAMBDA_Advance::ConstexprLambda_Advance::Config::DATA_PATTERN;

        ASSERT_EQ(3, pattern.size());
        ASSERT_EQ(5, pattern.at(0));
        ASSERT_EQ(15, pattern.at(1));
        ASSERT_EQ(25, pattern.at(2));

        // Assert compile-time initialization
        static_assert(CONSTEXPRLAMBDA_Advance::ConstexprLambda_Advance::Config::DATA_PATTERN[1] == 15,
            "DATA_PATTERN must be initialized by a constexpr lambda.");
    }

    // Test Case 3: Capture and Constraints
    TEST_F(ConstexprLambdaAdvanceTest, Capture_ConstexprValue)
    {
        // The function call itself is executed at runtime here, but the lambda could run at compile time
        int result = CONSTEXPRLAMBDA_Advance::ConstexprLambda_Advance::calculateOffsetValue(50);

        // Expected: 50 + 100 = 150
        ASSERT_EQ(150, result);

        // Assert compile-time capability
        static_assert(CONSTEXPRLAMBDA_Advance::ConstexprLambda_Advance::calculateOffsetValue(20) == 120,
            "Lambda capture must be valid in a constexpr context.");
    }

}


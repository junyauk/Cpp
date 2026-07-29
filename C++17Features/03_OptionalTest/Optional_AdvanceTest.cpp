#include "pch.h"
#include "gtest/gtest.h"
#include "..\03_Optional\Optional_Advance.h"

namespace OptionalAdvanceTest
{
    class OptionalAdvanceTest : public ::testing::Test
    {
    protected:
        OPTIONAL_Advance::Optional_Advance m_adv;
    };

    // Test Case 1a: Chaining Success (Stage 1 OK, Stage 2 OK)
    TEST_F(OptionalAdvanceTest, Chaining_Success)
    {
        // Input 11: Stage 1 result = 11 - 5 = 6 (Even) -> Stage 2 Fails.
        // Wait, the logic is: Fails if even. Let's use 13.
        // Input 13: Stage 1 result = 13 - 5 = 8 (Even) -> Stage 2 Fails.

        // Let's use 15: Stage 1 result = 15 - 5 = 10 (Even) -> Stage 2 Fails.

        // Let's use 16: Stage 1 result = 16 - 5 = 11 (Odd) -> Stage 2 OK (11 * 3 = 33)
        std::optional<std::string> result = m_adv.chainedProcessing(16);
        ASSERT_TRUE(result.has_value());
        ASSERT_EQ("Final Result: 33", result.value());
    }

    // Test Case 1b: Chaining Failure at Stage 1
    TEST_F(OptionalAdvanceTest, Chaining_FailureStage1)
    {
        // Input 8: Stage 1 fails (8 <= 10)
        std::optional<std::string> result = m_adv.chainedProcessing(8);
        ASSERT_FALSE(result.has_value());
    }

    // Test Case 1c: Chaining Failure at Stage 2
    TEST_F(OptionalAdvanceTest, Chaining_FailureStage2)
    {
        // Input 12: Stage 1 result = 12 - 5 = 7 (Odd) -> Stage 2 OK (7 * 3 = 21)
        // Wait, the logic is: Fails if even. Use 11.
        // Input 11: Stage 1 result = 11 - 5 = 6 (Even) -> Stage 2 Fails.
        std::optional<std::string> result = m_adv.chainedProcessing(11);
        ASSERT_FALSE(result.has_value());
    }

    // Test Case 2: In-place construction and move semantics
    TEST_F(OptionalAdvanceTest, CheckMoveCost_MoveSemantics)
    {
        // Create an optional directly using in_place
        std::optional<OPTIONAL_Advance::LargeData> opt{ std::in_place, "Original", 100000 };

        // Call checkMoveCost, which takes opt by r-value reference (&&) and moves the content out.
        std::string result = m_adv.checkMoveCost(std::move(opt));

        // The resulting name should contain "_M" from the move constructor of LargeData.
        ASSERT_NE(std::string::npos, result.find("Original_M"));

        // The original optional 'opt' should be empty after the move.
        ASSERT_FALSE(opt.has_value());
    }

    // Test Case 3a: Exception Safety (Success)
    TEST_F(OptionalAdvanceTest, ExceptionSafety_Success)
    {
        std::optional<int> opt = 42;
        // value() should succeed
        ASSERT_TRUE(m_adv.checkExceptionSafety(opt));
    }

    // Test Case 3b: Exception Safety (Failure/Exception)
    TEST_F(OptionalAdvanceTest, ExceptionSafety_Failure)
    {
        std::optional<int> opt = std::nullopt;
        // value() should throw std::bad_optional_access, caught by the method
        ASSERT_FALSE(m_adv.checkExceptionSafety(opt));
    }
}

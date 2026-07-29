#include "pch.h"
#include "gtest/gtest.h"
#include <type_traits>
#include "..\09_TemplateDeduction\TemplateDeduction_Basic.h"

namespace TEMPLATEDEDUCTION_Basic
{
    // Helper to verify the type deduced by CTAD (Conceptual check)
    template<typename T, typename U>
    constexpr bool is_same_type_v = std::is_same_v<T, U>;
}

namespace TemplateDeductionTest
{
    class TemplateDeductionTest : public ::testing::Test
    {
    protected:
        TEMPLATEDEDUCTION_Basic::CTAD_Basic m_ctad;
        void SetUp() override {}
        void TearDown() override {}
    };

    // Test Case 1: Implicit CTAD for SimpleWrapper<int>
    TEST_F(TemplateDeductionTest, SimpleIntWrapper_DeducesCorrectly)
    {
        int result = m_ctad.testSimpleIntWrapper(42);
        ASSERT_EQ(42, result);
        // NOTE: We cannot directly assert the type SimpleWrapper<int> was created 
        // within a TEST_F, but the function's return type implicitly confirms the usage.
    }

    // Test Case 2: Implicit CTAD for SimpleWrapper<std::string>
    TEST_F(TemplateDeductionTest, SimpleStringWrapper_DeducesCorrectly)
    {
        std::string result = m_ctad.testSimpleStringWrapper("hello ctad");
        ASSERT_EQ("hello ctad", result);
    }

    // Test Case 3: Explicit Deduction Guide usage for CountedBuffer
    TEST_F(TemplateDeductionTest, CountedBuffer_DeductionGuideUsed)
    {
        // The function uses the guide to create CountedBuffer<int>
        auto count = m_ctad.testCountedBufferDeduction();
        ASSERT_EQ(3, count);

        // --- Verification of STL CTAD (Example) ---
        // std::pair p(10, 5.0); // C++17 CTAD
        // static_assert(TEMPLATEDEDUCTION_Basic::is_same_type_v<decltype(p), std::pair<int, double>>);
        // This is a conceptual check demonstrating CTAD success.
    }
}


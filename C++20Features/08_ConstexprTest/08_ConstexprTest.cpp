#include "pch.h"
#include "../08_Constexpr/Constexpr_Basic.h"
#include <array>

using Constexpr_Basic::ConstexprBasic;
using Constexpr_Basic::COMPILE_TIME_STRING_ARRAY;

namespace Constexpr_Basic_Test
{
    class ConstexprTest : public ::testing::Test {};

    // Test case 1: Verify the compile-time string transformation result.
    TEST_F(ConstexprTest, GlobalConstant_StringToUpper)
    {
        std::string expected_str = "HELLO WORLD!";

        // Convert the compile-time array back to a string for comparison.
        std::string result_str(COMPILE_TIME_STRING_ARRAY.begin(), COMPILE_TIME_STRING_ARRAY.end());

        EXPECT_EQ(expected_str, result_str);
        EXPECT_EQ(12, COMPILE_TIME_STRING_ARRAY.size());
    }

    // Test case 2: Verify the function works when called explicitly at runtime.
    TEST_F(ConstexprTest, RuntimeCall)
    {
        // Calling the function at runtime should still yield the correct result.
        auto runtime_array = ConstexprBasic::constexprToUpper<5>("world");

        // Check the transformation
        std::string result_str(runtime_array.begin(), runtime_array.end());
        EXPECT_EQ("WORLD", result_str);
    }
} // namespace Constexpr_Basic_Test

#include "pch.h"
#include "gtest/gtest.h"
#include "..\08_ConstexprAdvanced\08_ConstexprAdvanced.h"

TEST(ConstexprAdvancedTest, FactorialAtCompileTime)
{
    using namespace ConstExprSamples;
    static_assert(factorial(5) == 120, "Compile-time check");
    EXPECT_EQ(factorial(5), 120);
}

TEST(ConstexprAdvancedTest, GcdCompileTime) {
    using namespace ConstExprSamples;
    static_assert(gcd(48, 18) == 6, "Compile-time check");
    EXPECT_EQ(gcd(48, 18), 6);
}

TEST(ConstexprAdvancedTest, SumOfArray)
{
    using namespace ConstExprSamples;
    constexpr std::array<int, 3> arr = { 1, 2, 3 };
    static_assert(sum(arr) == 6, "Compile-time check");
    EXPECT_EQ(sum(arr), 6);
}

TEST(ConstexprAdvancedTest, StringLength)
{
    using namespace ConstExprSamples;
    static_assert(str_len("Hello") == 5, "Compile-time check");
    EXPECT_EQ(str_len("Hello"), 5);
}

TEST(ConstArrayUtilsTest, SumOfArray)
{
    using namespace ConstArrayUtils;
    constexpr std::array<int, 5> arr = { 1, 2, 3, 4, 5 };
    static_assert(sum(arr) == 15, "Compile-time check");
    EXPECT_EQ(sum(arr), 15);
}

TEST(ConstArrayUtilsTest, MaxOfArray)
{
    using namespace ConstArrayUtils;
    constexpr std::array<int, 5> arr = { 1, 7, 3, 4, 5 };
    static_assert(max(arr) == 7, "Compile-time check");
    EXPECT_EQ(max(arr), 7);
}

TEST(ConstArrayUtilsTest, EmptyArray)
{
    using namespace ConstArrayUtils;
    constexpr std::array<int, 0> arr = {};
    // max on an empty array is undefined behavior; we skip that test
    static_assert(sum(arr) == 0, "Compile-time check");
	EXPECT_EQ(sum(arr), 0);
}

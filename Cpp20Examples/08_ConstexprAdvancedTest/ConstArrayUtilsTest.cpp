#include "pch.h"
#include "..\08_ConstexprAdvanced\ConstArrayUtils.h"
#include <gtest/gtest.h>
#include <array>

TEST(ConstArrayUtilsAdvancedTest, FilterEvenNumbers) {
    constexpr std::array<int, 5> arr = { 1, 2, 3, 4, 5 };

    constexpr auto result = ConstArrayUtils::filter(arr, [](int x) { return x % 2 == 0; });
	constexpr auto filtered = result.first;
	constexpr auto count = result.second;
    static_assert(count == 2, "Compile-time check");
    static_assert(filtered[0] == 2 && filtered[1] == 4, "Compile-time check");

    EXPECT_EQ(count, 2);
    EXPECT_EQ(filtered[0], 2);
    EXPECT_EQ(filtered[1], 4);
}


TEST(ConstArrayUtilsAdvancedTest, MapSquare) {
    constexpr std::array<int, 4> arr = { 1, 2, 3, 4 };
    constexpr auto squared = ConstArrayUtils::map(arr, [](int x) { return x * x; });

    static_assert(squared[0] == 1 && squared[3] == 16, "Compile-time check");
    EXPECT_EQ(squared[0], 1);
    EXPECT_EQ(squared[3], 16);
}

TEST(ConstArrayUtilsAdvancedTest, ConstArrayBasics)
{
	constexpr ConstArrayUtils::ConstArray<int, 3> arr({ 1, 2, 3 });
    constexpr auto doubled = arr.map([](int x) {return x * 2; });
    constexpr auto incremented = arr.map([](int x) {return x + 1; });
	static_assert(doubled[0] == 2 && doubled[2] == 6, "Compile-time check");
    EXPECT_EQ(doubled[0], 2);
    EXPECT_EQ(doubled[2], 6);
    EXPECT_EQ(incremented[0], 2);
	EXPECT_EQ(incremented[2], 4);
}

TEST(ConstArrayUtilsAdvancedTest, ConstArrayMixed)
{
	constexpr ConstArrayUtils::ConstArray<int, 5> arr({ 1, 2, 3, 4, 5 });
	constexpr auto doubled = arr.map([](int x) {return x * 2; });
    constexpr auto result = doubled.filter([](int x) { return x % 2 == 0; });
	constexpr auto evens = result.first;
    constexpr auto count = result.second;
    constexpr int sum = evens.reduce([](int a, int b) { return a + b; }, 0);
    static_assert(sum == 2 + 4 + 6 + 8 + 10, "Compile-time sum check");
}
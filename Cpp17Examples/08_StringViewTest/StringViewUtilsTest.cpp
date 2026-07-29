#include "pch.h"
#include "gtest/gtest.h"
#include "..\08_StringView\StringViewUtils.h"

using namespace StringViewExamples;

TEST(StringViewUtilsTest, CompareStrings_Basic)
{
	EXPECT_EQ(CompareStrings("apple", "apple"), 0);
	EXPECT_LT(CompareStrings("apple", "banana"), 0);
	EXPECT_GT(CompareStrings("banana", "apple"), 0);
}
TEST(StringViewUtilsTest, CompareStrings_LengthMatters)
{
	std::string_view a{ "apple" };
	std::string_view b{ "apple\0zzz", 9 };
	EXPECT_NE(a, b);
}
TEST(StringViewUtilsTest, Equals)
{
	EXPECT_TRUE(Equals("test", "test"));
	EXPECT_FALSE(Equals("test", "Test"));
	EXPECT_FALSE(Equals("test", "testing"));
}
TEST(StringViewUtilsTest, LessThan)
{
	EXPECT_TRUE(LessThan("apple", "banana"));
	EXPECT_FALSE(LessThan("banana", "apple"));
	EXPECT_FALSE(LessThan("apple", "apple"));

}

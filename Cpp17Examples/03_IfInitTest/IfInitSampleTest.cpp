#include "pch.h"
#include "..\03_IfInit\IfInitSample.h"

using namespace IfInitSample;

TEST(IfInitTests, FindValue_Found)
{
	std::map<int, std::string> m =
	{
		{1, "one"},
		{2, "two"}
	};
	auto result = findValue(m, 1);
	ASSERT_TRUE(result.has_value());
	EXPECT_EQ("one", result.value());
}
TEST(IfInitTests, FindValue_NotFound)
{
	std::map<int, std::string> m =
	{
		{1, "one"},
		{2, "two"}
	};
	auto result = findValue(m, 3);
	EXPECT_FALSE(result.has_value());
}
TEST(IfInitTests, ClassifyString_Empty)
{
	EXPECT_EQ("empty", classifyString(""));
}
TEST(IfInitTests, ClassifyString_Short)
{
	EXPECT_EQ("short", classifyString("A"));
}
TEST(IfInitTests, ClassifyString_Tiny)
{
	EXPECT_EQ("tiny", classifyString("AB"));
}
TEST(IfInitTests, ClassifyString_Long)
{
	EXPECT_EQ("long", classifyString("Hello"));
}

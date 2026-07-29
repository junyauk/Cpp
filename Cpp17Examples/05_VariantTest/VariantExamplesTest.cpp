#include "pch.h"
#include "..\05_Variant\VariantExamples.h"

using namespace VariantExamples;

TEST(VariantBasicTests, GetAndVisit)
{
	IntOrString v = 42;
	EXPECT_EQ(std::get<int>(v), 42);
	EXPECT_EQ(toString(v), "42");

	v = std::string("hello");
	EXPECT_EQ(std::get<std::string>(v), "hello");
	EXPECT_EQ(toString(v), "hello");
}

TEST(VariantBasicTests, HoldsAlternative)
{
	IntOrString v = 123;
	EXPECT_TRUE(std::holds_alternative<int>(v));
	EXPECT_FALSE(std::holds_alternative<std::string>(v));
}

TEST(VariantAdvancedTests, SettingValueToString)
{
	SettingValue v1 = 10;
	SettingValue v2 = 3.14;
	SettingValue v3 = std::string("sample");
	SettingValue v4 = Color::Blue;

	EXPECT_EQ(settingToString(v1), "int:10");
	EXPECT_EQ(settingToString(v2), "double:3.140000");
	EXPECT_EQ(settingToString(v3), "string:sample");
	EXPECT_EQ(settingToString(v4), "Color::Blue");
}


#include "pch.h"
#include "gtest/gtest.h"
#include "..\05_Variant\Config_Manager.h"

using namespace ConfigManagerUsingVisitExample;

TEST(ConfigManagerConverterTest, IntToString)
{
	ConfigValue v = 42;
	auto res = ConfigManager::convert<std::string>(v);
	ASSERT_TRUE(res.has_value());
	EXPECT_EQ(*res, "42");
}

TEST(ConfigManagerConverterTest, StringToBool)
{
	ConfigValue v = std::string("true");
	auto res = ConfigManager::convert<bool>(v);
	ASSERT_TRUE(res.has_value());
	EXPECT_TRUE(*res);
}

TEST(ConfigManagerConverterTest, InvalidStringToInt)
{
	ConfigValue v = std::string("abc");
	auto res = ConfigManager::convert<int>(v);
	EXPECT_FALSE(res.has_value());
}

TEST(ConfigManagerConverterTest, ConvertInt)
{
	EXPECT_EQ(ConfigManager::convert<int>(ConfigValue(42)), 42);
	EXPECT_EQ(ConfigManager::convert<int>(ConfigValue(3.14)), 3);
	EXPECT_EQ(ConfigManager::convert<int>(ConfigValue(true)), 1);
	EXPECT_EQ(ConfigManager::convert<int>(ConfigValue(false)), 0);
	EXPECT_EQ(ConfigManager::convert<int>(ConfigValue("123")), 123);
	EXPECT_FALSE(ConfigManager::convert<int>(ConfigValue("abc")).has_value());
}

TEST(ConfigManagerConverterTest, ConvertDouble)
{
	EXPECT_EQ(ConfigManager::convert<double>(ConfigValue(42)), 42.0);
	EXPECT_EQ(ConfigManager::convert<double>(ConfigValue(3.14)), 3.14);
	EXPECT_EQ(ConfigManager::convert<double>(ConfigValue(true)), 1.0);
	EXPECT_EQ(ConfigManager::convert<double>(ConfigValue(false)), 0.0);
	EXPECT_EQ(ConfigManager::convert<double>(ConfigValue("3.14")), 3.14);
	EXPECT_FALSE(ConfigManager::convert<double>(ConfigValue("abc")).has_value());
}

TEST(ConfigManagerConverterTest, ConvertBool)
{
	EXPECT_TRUE(ConfigManager::convert<bool>(ConfigValue(42)).value());
	EXPECT_FALSE(ConfigManager::convert<bool>(ConfigValue(0)).value());
	EXPECT_TRUE(ConfigManager::convert<bool>(ConfigValue("true")).value());
	EXPECT_FALSE(ConfigManager::convert<bool>(ConfigValue("false")).value());
	EXPECT_FALSE(ConfigManager::convert<bool>(ConfigValue("xyz")).has_value());
}

TEST(ConfigManagerConverterTest, ConvertString)
{
	EXPECT_EQ(ConfigManager::convert<std::string>(ConfigValue(42)).value(), "42");
	EXPECT_EQ(ConfigManager::convert<std::string>(ConfigValue(3.14)).value(), "3.140000");
	EXPECT_EQ(ConfigManager::convert<std::string>(ConfigValue(true)).value(), "true");
	EXPECT_EQ(ConfigManager::convert<std::string>(ConfigValue(false)).value(), "false");
	EXPECT_EQ(ConfigManager::convert<std::string>(ConfigValue("abc")).value(), "abc");
}

TEST(AdditionalTest, HoldAlternativeTest)
{
	sample_holds_alternative();
}

TEST(AdditionalTest, VisitOverloadTest)
{
	sample_visit_overloaded();
}

TEST(AdditionalTest, AnyTest)
{
	sample_any();
}

TEST(AdditionalTest, MoveOnlyTest)
{
	sample_moveonly_variant();
}
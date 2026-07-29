#include "pch.h"
#include "..\02_Optional\OptionalSample.h"

using namespace OptionalSamples;

TEST(OptionalTests, ToStringIfPositive_ReturnsValue)
{
	auto ret = toStringIfPositive(42);
	ASSERT_TRUE(ret.has_value());
	EXPECT_EQ("42", ret.value());
}
TEST(OptionalTests, ToStringIfPositive_ReturnsNulloptForNegative)
{
	auto ret = toStringIfPositive(-10);
	ASSERT_FALSE(ret.has_value());
}

TEST(OptionalTests, GetLengthIfHasValue_Works)
{
	std::optional<std::string> str = "Hello";
	auto len = getLengthIfHasValue(str);
	ASSERT_TRUE(len.has_value());
	EXPECT_EQ(5u, len.value());
}

TEST(OptionalTests, GetLengthIfHasValue_NoValue)
{
	std::optional<std::string> str = std::nullopt;
	auto len = getLengthIfHasValue(str);
	ASSERT_FALSE(len.has_value());
}

TEST(OptionalTests, GetValueOrDefault_ReturnsStoredValue)
{
	std::optional<std::string> str = "World";
	EXPECT_EQ("World", getValueOrDefault(str, "Default"));
}

TEST(OptionalTests, GetValueOrDefault_ReturnsDefaultIfEmpty)
{
	std::optional<std::string> str = std::nullopt;
	EXPECT_EQ("Default", getValueOrDefault(str, "Default"));
}

TEST(OptionalTests, MakeOptional_Works)
{
	auto opt = makeOptionalInt(123);
	ASSERT_TRUE(opt.has_value());
	EXPECT_EQ(123, *opt);
}

TEST(OptionalTests, Emplace_ReplacesValue)
{
	std::optional<std::string> opt = "Old";
	reEmplaceValue(opt, "New");
	ASSERT_TRUE(opt.has_value());
	EXPECT_EQ("New", opt.value());
}

TEST(OptionalTests, Reset_ClearsValue)
{
	std::optional<std::string> opt = "Hello";
	resetOptional(opt);
	ASSERT_FALSE(opt.has_value());
}

TEST(OptionalTests, OperatorArrow_AccessMembers)
{
	std::optional<std::string> opt = "ChatGPT";
	ASSERT_TRUE(opt.has_value());
	EXPECT_EQ(7u, opt->size());
}

TEST(OptionalTests, FindInVector_Found)
{
	std::vector<int> vec = { 1,2,3,4,5 };
	auto result = findInVector(vec, 3);
	ASSERT_TRUE(result.has_value());
	EXPECT_EQ(2u, result.value());
}

TEST(OptionalTests, FindInVector_NotFound)
{
	std::vector<int> vec = { 1,2,3,4,5 };
	auto result = findInVector(vec, 10);
	EXPECT_FALSE(result.has_value());
}


TEST(OptionalGeneralUsageTests, ParseInt_ValidInput)
{
	auto result = parseInt("123");
	ASSERT_TRUE(result.has_value());
	EXPECT_EQ(123, result.value());

}

TEST(OptionalGeneralUsageTests, ParseInput_InvalidInput)
{
	auto result = parseInt("abc");
	ASSERT_FALSE(result.has_value());
}

TEST(OptionalGeneralUsageTests, ValueOr_DefaultValue)
{
	Config cfg;
	int port = cfg.port.value_or(8000);
	EXPECT_EQ(8000, port);

	cfg.port = 443;
	EXPECT_EQ(443, cfg.port.value_or(8000));
}

TEST(OptionalGeneralUsageTests, IfWithOptional)
{
	std::vector<int> vec = { 10,20,30 };
	if (auto result = findInVector(vec, 20); result)
	{
		EXPECT_EQ(1u, *result);
	}
	else
	{
		FAIL() << "Value should be found.";
	}
}

TEST(OptionalGeneralUsageTests, OptinalBool_ThreeStateLogic)
{
	Settings settings;

	EXPECT_FALSE(settings.enableLogging.has_value());
	settings.enableLogging = true;
	EXPECT_TRUE(settings.enableLogging.value());
	settings.enableLogging = false;
	EXPECT_FALSE(settings.enableLogging.value());
}

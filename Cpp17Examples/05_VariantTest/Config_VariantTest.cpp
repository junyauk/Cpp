#include "pch.h"
#include "gtest/gtest.h"
#include "..\05_Variant\Config_Variant.h"

using namespace ConfigVariantExample;

TEST(ConfigVariantTests, StoreAndRetrieveInt)
{
	Config cfg;
	cfg.set("threads", 8);

	auto val = cfg.get<int>("threads");
	ASSERT_TRUE(val.has_value());
	EXPECT_EQ(*val, 8);
	EXPECT_EQ(val.value(), 8);
}

TEST(ConfigVariantTests, StoreAndRetrieveString)
{
	Config cfg;
	cfg.set("mode", std::string("debug"));

	auto val = cfg.get<std::string>("mode");
	ASSERT_TRUE(val.has_value());
	EXPECT_EQ(*val, "debug");
	EXPECT_EQ(val.value(), "debug");
}

TEST(ConfigVariantTests, WrontTypeReturnsNullopt)
{
	Config cfg;
	cfg.set("pi", 3.14);

	auto val = cfg.get<int>("pi");
	EXPECT_FALSE(val.has_value());
}


#include "pch.h"
#include "gtest/gtest.h"
#include "..\08_StringView\LifeTimeTrap.h"

using namespace StringViewExamples;

TEST(StringViewTest, LifeTimeTrap_Dangling)
{
	std::string_view sv = getTempStringView();

	std::cout << "Dangling string_view points to: [" << sv << "]" << std::endl;
}

TEST(StringViewTest, LifeTimeTrap_StaticSafe)
{
	auto sv = getStaticStringView();
	EXPECT_EQ(sv, "Static storage");
}

TEST(StringViewTest, LifeTimeTrap_FromCaller)
{
	std::string str = "Caller owns me";
	auto sv = getViewFromString(str);
	EXPECT_EQ(sv, "Caller owns me");
}


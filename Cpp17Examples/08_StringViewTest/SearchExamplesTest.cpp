#include "pch.h"
#include "gtest/gtest.h"
#include "..\08_StringView\SearchExamples.h"

using namespace StringViewExamples;

TEST(StringViewSearchTest, ContainsWord)
{
	EXPECT_TRUE(containsWorld("Hello, World!"));
	EXPECT_FALSE(containsWorld("Hello, everyone!"));
}

TEST(StringViewSearchTest, StartsWithHello)
{
	EXPECT_TRUE(startsWithHello("Hello, World!"));
	EXPECT_FALSE(startsWithHello("Hi, World!"));
}

TEST(StringViewSearchTest, EndsWithExclamation)
{
	EXPECT_TRUE(endsWithExclamation("Hello, World!"));
	EXPECT_FALSE(endsWithExclamation("Hello, World."));
}

TEST(StringViewSearchTest, SplitWords)
{
	auto words = splitWords("This is a test");
	ASSERT_EQ(words.size(), 4);
	EXPECT_EQ(words[0], "This");
	EXPECT_EQ(words[1], "is");
	EXPECT_EQ(words[2], "a");
	EXPECT_EQ(words[3], "test");
}

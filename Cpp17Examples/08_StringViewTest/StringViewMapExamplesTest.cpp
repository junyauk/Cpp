#include "pch.h"
#include "gtest/gtest.h"

#include "..\08_StringView\StringViewMapExamples.h"

using namespace StringViewExamples;

TEST(StringViewMapExamplesTest, CountWordsOrdered)
{
	std::vector<std::string> words =
	{
		"apple",
		"banana",
		"apple",
		"orange",
		"banana",
		"apple"
	};

	auto result = CountWordsOrdered(words);

	EXPECT_EQ(result["apple"], 3);
	EXPECT_EQ(result["banana"], 2);
	EXPECT_EQ(result["orange"], 1);

	auto it = result.begin();
	EXPECT_EQ(it->first, "apple");
	++it;
	EXPECT_EQ(it->first, "banana");
}
TEST(StringViewMapExamplesTest, CountWordsUnordered)
{
	std::vector<std::string> words =
	{
		"dog",
		"cat",
		"dog"
	};

	auto result = CountWordsUnordered(words);

	EXPECT_EQ(result["dog"], 2);
	EXPECT_EQ(result["cat"], 1);

}
#include "pch.h"
#include "..\02_RangesAndViews\02_RangesAndViews.h"
#include "..\TestUtilities\TestUtils.h"

#include <vector>
#include <string>

TEST(RangesAndViewsTest, FilterEven)
{
    std::vector<int> data{ 1,2,3,4,5,6 };
    auto evens = filterEven(data);

    std::vector<int> expected{ 2,4,6 };
    std::vector<int> result(evens.begin(), evens.end());

    EXPECT_EQ(result, expected);
}

TEST(RangesAndViewsTest, SquareAll)
{
	std::vector<int> data{ 1,2,3,4 };
	auto squares = squareAll(data);

	std::vector<int> expected{ 1,4,9,16 };
	std::vector<int> result(squares.begin(), squares.end());

	EXPECT_EQ(result, expected);
}

TEST(RangesAndViewsTest, EvenSquares)
{
	std::vector<int> data{ 1,2,3,4,5,6 };
	auto evenSquareViews = evenSquares(data);

	std::vector<int> expected{ 4, 16, 36 };
	std::vector<int> result(evenSquareViews.begin(), evenSquareViews.end());

	EXPECT_EQ(result, expected);
}

TEST(RangesAndViewsTest, FilterOddLessThanTen)
{
    std::vector<int> input = { 1, 2, 3, 4, 5, 10, 11, 13 };
    auto result = filterOddLessThanTen(input);

    std::vector<int> expected = { 1, 3, 5 };
    EXPECT_EQ(result, expected);
}

TEST(RangesAndViewsTest, DropFirstThreeAndToString)
{
    std::vector<int> input = { 10, 20, 30, 40, 50 };
    std::string result = dropFirstThreeAndToString(input);

    EXPECT_EQ(result, "40 50");
}

TEST(RangesAndViewsTest, Enumerate)
{
    std::vector<std::string> input = { "apple", "banana", "cherry" };
    auto result = enumerate(input);

    ASSERT_EQ(result.size(), 3);
    EXPECT_EQ(result[0].first, 0);
    EXPECT_EQ(result[0].second, "apple");
    EXPECT_EQ(result[1].first, 1);
    EXPECT_EQ(result[1].second, "banana");
    EXPECT_EQ(result[2].first, 2);
    EXPECT_EQ(result[2].second, "cherry");
}

TEST(RangesAndViewsTest, FilterAndSquareOptional)
{
    std::vector<int> input{ 1,2,3,4,5,6 };
    auto result = filterAndSquareOptional(input);

    std::vector<int> output(result.begin(), result.end());
    std::vector<int> expected{4,16,36};

    EXPECT_EQ(output, expected);
}


#include "pch.h"
#include "gtest/gtest.h"
#include "..\09_MapSet\MapSetLowerUpper.h"

using namespace MapSetExamples;

TEST(MapSetLowerUpperTest, GetEmployeesFromId)
{
	std::map<int, std::string> employees{ {100, "Alice"}, {200, "Bob"}, {300, "Charlie"} };
	auto result = getEmployeesFromId(employees, 200);
	ASSERT_EQ(result.size(), 2);
	EXPECT_EQ(result[0].second, "Bob");
	EXPECT_EQ(result[1].second, "Charlie");
}

TEST(MapSetLowerUpperTest, GetEmployeesInRange)
{
	std::map<int, std::string> employees
	{
		{100, "Alice"}, {200, "Bob"}, {300, "Charlie"}, {400, "Dave"}
	};
	auto result = getEmployeesInRange(employees, 200, 400);
	ASSERT_EQ(result.size(), 2);
	EXPECT_EQ(result[0].second, "Bob");
	EXPECT_EQ(result[1].second, "Charlie");

	result = getEmployeesInRange(employees, 100, 500);
	ASSERT_EQ(result.size(), 4);
	EXPECT_EQ(result[0].second, "Alice");
	EXPECT_EQ(result[1].second, "Bob");
	EXPECT_EQ(result[2].second, "Charlie");
	EXPECT_EQ(result[3].second, "Dave");
}


TEST(MapSetLowerUpperTest, EqualRangeOfMultiMap)
{
	std::vector<std::string> result;

	result = ExampleOfEqualRangeOfMultiMap();
	ASSERT_EQ(result.size(), 4);
	EXPECT_EQ(result[0], "range(1): a c d");
	EXPECT_EQ(result[1], "range(2): f");
	EXPECT_EQ(result[2], "range(3):");
	EXPECT_EQ(result[3], "range(11): h");
}

TEST(MapSetLowerUpperTest, EqualRangeOfUnorderedMultiMap)
{
	std::vector<std::string> result;

	result = ExampleOfEqualRangeOfUnorderedMultiMap();
	ASSERT_EQ(result.size(), 4);
	EXPECT_EQ(result[0], "range(1): a c d");
	EXPECT_EQ(result[1], "range(2): f");
	EXPECT_EQ(result[2], "range(3):");
	EXPECT_EQ(result[3], "range(11): h");
}


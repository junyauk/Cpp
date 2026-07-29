#include "pch.h"
#include "gtest/gtest.h"
#include "..\09_MapSet\MapSetAdvanced.h"

using namespace MapSetAdvanced;

TEST(MapSetAdvancedTest, OperatorSquareBracket)
{
	EmployeeMap m;

	setEmployeeName(m, 101, "Alice");
	setEmployeeName(m, 102, "Bob");

	EXPECT_EQ(m[101], "Alice");
	EXPECT_EQ(m[103], "");
}

TEST(MapSetAdvancedTest, AtFunction)
{
	EmployeeMap m;

	setEmployeeName(m, 201, "Charlie");

	EXPECT_EQ(getEmployeeNameAt(m, 201), "Charlie");

	EXPECT_THROW(getEmployeeNameAt(m, 999), std::out_of_range);
}

TEST(MapSetAdvancedTest, ExtractAndChangeKey)
{
	EmployeeMap m;

	setEmployeeName(m, 301, "Dave");
	setEmployeeName(m, 302, "Eve");

	changeEmployeeId(m, 301, 401);

	EXPECT_EQ(m.size(), 2);
	EXPECT_EQ(m.count(301), 0);
	EXPECT_EQ(m.count(401), 1);
	EXPECT_EQ(m[401], "Dave");

	EXPECT_EQ(m[302], "Eve");
}

TEST(MapSetAdvancedTest, ChangeIdWithExtract_Success)
{
	EmployeeMap m
	{
		{1001, "Alice"},
		{1002, "Bob"},
		{1003, "Charlie"}
	};

	bool result = changeEmployeeIdWithExtract(m, 1002, 2002);
	EXPECT_TRUE(result);
	EXPECT_EQ(m.count(1002), 0);
	EXPECT_EQ(m.at(2002), "Bob");
}

TEST(MapSetAdvancedTest, ChangeIdWithExtract_FailWhenOldIdNotFound)
{
	EmployeeMap m
	{
		{1001, "Alice"},
		{1003, "Charlie"}
	};

	bool result = changeEmployeeIdWithExtract(m, 9999, 2002);
	EXPECT_FALSE(result);
	EXPECT_EQ(m.size(), 2);
}

TEST(MapSetAdvancedTest, ChangeIdWithoutExtract_Success)
{
	EmployeeMap m
	{
		{1001, "Alice"},
		{1002, "Bob"},
		{1003, "Charlie"}
	};
	bool result = changeEmployeeIdWithoutExtract(m, 1002, 2002);
	EXPECT_TRUE(result);
	EXPECT_EQ(m.count(1002), 0);
	EXPECT_EQ(m.at(2002), "Bob");
}

TEST(MapSetAdvancedTest, ChangeIdWithoutExtract_FailWhenOldIdNotFound)
{
	EmployeeMap m
	{
		{1001, "Alice"},
		{1003, "Charlie"}
	};
	bool result = changeEmployeeIdWithoutExtract(m, 9999, 202);
	EXPECT_FALSE(result);
	EXPECT_EQ(m.size(), 2);
}

#include "pch.h"
#include <gtest/gtest.h>
#include "..\01_StructuredBindings\StructuredBindingsSamples.h"

using namespace StructuredBindingsExamples;

TEST(StructuredBindingsTest, PointDecompose)
{
	auto [x, y] = make_point(3, 7);
	EXPECT_EQ(x, 3);
	EXPECT_EQ(y, 7);
}


TEST(StructuredBindingsTest, TupleDecompose)
{
	auto [num, text] = make_tuple_example(42, "Hello C++17");
	EXPECT_EQ(num, 42);
	EXPECT_EQ(text, "Hello C++17");
}

TEST(StructuredBindingsTest, MapInsertDecompose)
{
	std::map<std::string, int> scores;
	auto [itr, inserted] = insert_score(scores, "Alice", 90);

	EXPECT_TRUE(inserted);
	EXPECT_EQ(itr->first, "Alice");
	EXPECT_EQ(itr->second, 90);

	auto [itr2, inserted2] = insert_score(scores, "Alice", 100);
	EXPECT_FALSE(inserted2);
	EXPECT_EQ(itr2->second, 90);
}

TEST(StructuredBindingsTest, MapFindWithIfInit)
{
	std::map<std::string, int> scores =
	{
		{"Alice", 90},
		{"Bob", 75}
	};

	if (auto it = find_score(scores, "Alice"); it != scores.end())
	{
		auto& [name, value] = *it;
		EXPECT_EQ(name, "Alice");
		EXPECT_EQ(value, 90);
	}
	else
	{
		FAIL() << "Alice should be found.\n";
	}
}

TEST(StructuredBindingsTest, EmployeeDecompose)
{
	auto [id, name, salary] = make_employee(101, "Alice", 50000.0);

	EXPECT_EQ(id, 101);
	EXPECT_EQ(name, "Alice");
	EXPECT_DOUBLE_EQ(salary, 50000.0);
}


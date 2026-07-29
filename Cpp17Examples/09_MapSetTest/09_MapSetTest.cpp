#include "pch.h"
#include <gtest/gtest.h>
#include "..\09_MapSet\01_TryEmplace.h"
#include "..\09_MapSet\02_InsertOrAssign.h"

using namespace MapSetExamples;

TEST(MapInsertVariants, InsertAndEmplace)
{
	std::map<std::string, int> m;

	auto [it1, inserted1] = m.insert({ "apple", 1 });
	EXPECT_TRUE(inserted1);
	EXPECT_EQ(m["apple"], 1);

	auto [it2, inserted2] = m.insert({ "apple", 99 });
	EXPECT_FALSE(inserted2);
	EXPECT_EQ(m["apple"], 1);

	auto [it3, inserted3] = m.emplace("banana", 2);
	EXPECT_TRUE(inserted3);
	EXPECT_EQ(m["banana"], 2);

	auto [it4, inserted4] = m.emplace("banana", 99);
	EXPECT_FALSE(inserted4);
	EXPECT_EQ(m["banana"], 2);

	// Never overwrite the existing element
	// - insert
	// - emplace (directly insert an object, and will never create a temp object)

	// Will overwrite the existing element
	// - insert_or_assign
}

TEST(MapSetExamplesTest, TryEmplace)
{
	auto result = TestTryEmplaceMap();
	EXPECT_EQ(result, "1:Hello; 2:World; ");

	result = TestTryEmplaceUnorderedMap();
	EXPECT_TRUE(result.find("1:Hello; ") != std::string::npos);
	EXPECT_TRUE(result.find("2:World; ") != std::string::npos);
	EXPECT_TRUE(result.find("Ignored") == std::string::npos);
}

TEST(MapSetExamplesTest, InsertOrAssign)
{
	auto result = TestInsertOrAssignMap();
	EXPECT_EQ(result, "1:Overwritten; 2:World; ");

	result = TestInsertOrAssignUnordered();
	EXPECT_TRUE(result.find("1:Hello; ") == std::string::npos);
	EXPECT_TRUE(result.find("1:Overwritten; ") != std::string::npos);
	EXPECT_TRUE(result.find("2:World; ") != std::string::npos);
}


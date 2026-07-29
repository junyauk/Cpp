#include "pch.h"
#include "gtest/gtest.h"
#include "..\09_MapSet\MapBasics.h"

using namespace MapSetExamples;

TEST(MapBasicExamplesTest, InsertExamples)
{
	auto m = MapBasics::insertExamples();

	EXPECT_EQ(m.at("apple"), 1);
	EXPECT_EQ(m.at("banana"), 2);
	EXPECT_EQ(m.at("cherry"), 3);
}

TEST(MapBasicExamplesTest, FindExamples)
{
	auto m = MapBasics::insertExamples();
	EXPECT_EQ(MapBasics::findExample(m, std::string{ "apple" }), 1);
	EXPECT_EQ(MapBasics::findExample(m, std::string{ "unknown" }), std::nullopt);
}

TEST(MapBasicExamplesTest, AtExamples)
{
	auto m = MapBasics::insertExamples();
	EXPECT_EQ(MapBasics::atExample(m, std::string{ "cherry" }), 3);
	EXPECT_EQ(MapBasics::atExample(m, std::string{ "none" }), std::nullopt);
}

TEST(MapBasicExamplesTest, EraseExamples)
{
	auto m = MapBasics::eraseExamples();
	EXPECT_EQ(m.count("apple"), 0);
	EXPECT_EQ(m.count("banana"), 0);
	EXPECT_EQ(m.count("cherry"), 1);
}

TEST(MapBasicExamplesTest, UpdateExamples)
{
	auto m = MapBasics::updateExamples();
	EXPECT_EQ(m.at("banana"), 20);
	EXPECT_EQ(m.at("date"), 40);
}

TEST(MapBasicExamplesTest, SumValues)
{
	auto m = MapBasics::insertExamples();
	EXPECT_EQ(MapBasics::sumValues(m), 6);
}

TEST(MapBasicExamplesTest, CapacityExamples)
{
	EXPECT_TRUE(MapBasics::capacityExamples());
}

TEST(MapBasicExamplesTest, OrderedVsUnordered)
{
	auto m = MapBasics::orderedKeys();
	auto um = MapBasics::unorderedKeys();

	std::vector<std::string> e{ "apple", "banana", "cherry" };
	EXPECT_EQ(m, e);
	EXPECT_EQ(um.size(), 3);
}


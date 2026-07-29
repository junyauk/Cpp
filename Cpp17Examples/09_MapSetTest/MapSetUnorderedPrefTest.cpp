#include "pch.h"
#include "gtest/gtest.h"
#include "..\09_MapSet\MapSetUnorderedPref.h"

using namespace MapSetExamples;

TEST(MapSetUnorderedPrefTest, LoadFactorWithoutReserve)
{
	float lf = getLoadFactor(1000, 0);
	EXPECT_GT(lf, 0.5);
}

TEST(MapSetUnorderedPrefTest, LoadFactorWithReserve)
{
	float lf = getLoadFactor(1000, 2000);
	EXPECT_LT(lf, 0.8);
}

TEST(MapSetUnorderedPrefTest, UnorderedMapBucketsAndLoadFactor)
{
	auto results = ExampleOfUnorderedMapBuckets();
	ASSERT_GE(results.size(), 4);

	EXPECT_TRUE(results[0].find("Initial size= 0") != std::string::npos);
	EXPECT_TRUE(results[1].find("After insert 20: size= 2") != std::string::npos);
	EXPECT_TRUE(results[2].find("After rehash(50):") != std::string::npos);
	EXPECT_TRUE(results[3].find("After reserve(200):") != std::string::npos);
}

#include "pch.h"
#include "gtest/gtest.h"
#include "..\09_MapSet\Warehouse.h"

using namespace MapSetExamples;

class WarehouseTest : public ::testing::Test
{
protected:
	Warehouse wh;
	void SetUp() override
	{
		wh.addProduct("apple", 10);
		wh.addProduct("banana", 20);
		wh.addProduct("orange", 15);
		wh.addProduct("grape", 5);
	}
};

TEST_F(WarehouseTest, AddAndGetStock)
{
	wh.addProduct("apple", 5);
	auto stock = wh.getStock("apple");
	ASSERT_TRUE(stock.has_value());
	EXPECT_EQ(stock.value(), 15);

	stock = wh.getStock("banana");
	ASSERT_TRUE(stock.has_value());
	EXPECT_EQ(stock.value(), 20);

}

TEST_F(WarehouseTest, GetStokNotFound)
{
	auto stock = wh.getStock("mango");
	ASSERT_FALSE(stock.has_value());
}

TEST_F(WarehouseTest, BucketCountPositive)
{
	EXPECT_GT(wh.bucketCount(), 0u);
}

TEST_F(WarehouseTest, BucketReturnsValidIndex)
{
	auto b = wh.bucket("apple");
	EXPECT_LT(b, wh.bucketCount());
}

TEST_F(WarehouseTest, BucketSizeMatchesInspect)
{
	for (size_t i = 0; i < wh.bucketCount(); ++i)
	{
		auto inspected = wh.inspectBucket(i);
		EXPECT_EQ(inspected.size(), wh.bucketSize(i));
	}
}

TEST_F(WarehouseTest, InspectBucketContainsKey)
{
	auto b = wh.bucket("banana");
	auto inspected = wh.inspectBucket(b);
	bool found = false;
	for (auto& kv : inspected)
	{
		if (kv.first == "banana")
		{
			found = true;
			break;
		}
	}
	EXPECT_TRUE(found);
}

TEST_F(WarehouseTest, LoadFactorIsNonNegative)
{
	EXPECT_GE(wh.getCurrentLoadFactor(), 0.0f);
}

TEST_F(WarehouseTest, BucketOperations)
{
	wh.addProduct("apple", 10);
	wh.addProduct("banana", 20);
	wh.addProduct("grape", 5);
	wh.addProduct("melon", 7);
	wh.addProduct("orange", 15);
	wh.addProduct("peach", 30);
	wh.addProduct("strawberry", 1);

	EXPECT_GT(wh.bucketCount(), 0u);

	bool foundNonEmptyBucket = false;

	for (size_t i = 0; i < wh.bucketCount(); ++i)
	{
		auto elements = wh.listBucket(i);
		if (!elements.empty())
		{
			foundNonEmptyBucket = true;
			for (const auto& e : elements)
			{
				EXPECT_NE(e.find(':'), std::string::npos);
			}
		}
	}

	EXPECT_TRUE(foundNonEmptyBucket);
}

TEST_F(WarehouseTest, ReserveIncreasesBucketCount)
{
	size_t before = wh.bucketCount();
	wh.reserve(100);
	size_t after = wh.bucketCount();

	EXPECT_GE(after, before);
}

TEST_F(WarehouseTest, RehashIncreasesBucketCount)
{
	size_t before = wh.bucketCount();
	wh.rehash(50);
	size_t after = wh.bucketCount();

	EXPECT_GE(after, 50);
	EXPECT_GE(after, before);
}

TEST_F(WarehouseTest, LoadFactorChek)
{
	float lf = wh.getCurrentLoadFactor();
	float maxLf = wh.getMaxLoadFactor();

	EXPECT_GE(lf, 0.0f);
	EXPECT_LE(lf, maxLf * 2.0f);
}

TEST(WarehouseLoadFactorTest, LoadFactorOperaitons)
{
	Warehouse wh;
	float initialMaxLf = wh.getMaxLoadFactor();
	float initialCurLf = wh.getCurrentLoadFactor();
	EXPECT_GT(initialMaxLf, 0.0f);
	EXPECT_EQ(initialCurLf, 0.0f);

	wh.addProduct("apple", 1);
	wh.addProduct("banana", 1);
	float curLf1 = wh.getCurrentLoadFactor();
	EXPECT_GT(curLf1, initialCurLf);

	wh.setMaxLoadFactor(0.75f);
	float maxLf1 = wh.getMaxLoadFactor();
	EXPECT_FLOAT_EQ(maxLf1, 0.75);

	wh.addProduct("orange", 1);
	EXPECT_FLOAT_EQ(wh.getMaxLoadFactor(), 0.75f);
	EXPECT_GT(wh.getCurrentLoadFactor(), curLf1);

	wh.setMaxLoadFactor(2.0f);
	EXPECT_FLOAT_EQ(wh.getMaxLoadFactor(), 2.0f);
}

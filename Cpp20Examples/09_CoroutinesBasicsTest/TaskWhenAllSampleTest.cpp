#include "pch.h"
#include "gtest/gtest.h"
#include "..\09_CoroutinesBasics\TaskWhenAllSample.h"

using namespace TaskWhenAllSample;

TEST(CoroutineTest, TaskWhenAllSample)
{
	auto all = parallelSquares();
	auto results = all.result();

	EXPECT_EQ(results.size(), 3);
	EXPECT_EQ(results[0], 4);
	EXPECT_EQ(results[1], 9);
	EXPECT_EQ(results[2], 16);
}
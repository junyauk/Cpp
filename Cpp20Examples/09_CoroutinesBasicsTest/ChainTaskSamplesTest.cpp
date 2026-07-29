#include "pch.h"
#include "gtest/gtest.h"
#include "..\09_CoroutinesBasics\ChainTaskSamples.h"

using namespace ChainTaskSamples;

TEST(CoroutineTest, ChainTaskSample1)
{
	auto t = chainSample();
	auto result = t.get();
	std::cout << "[Test] Final result: " << result << std::endl;
	EXPECT_EQ(result, "Result is 20");
}


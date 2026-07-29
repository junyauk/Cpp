#include "pch.h"
#include "gtest/gtest.h"
#include "..\10_LambdaImprovements\DynamicPriorityTaskDispatcher.h"

using namespace LambdaImprovements;

class DynamicPriorityTaskDispatcherTest : public testing::Test
{
protected:
	DynamicPriorityTaskDispatcher dispatcher{ 2, 6 };
};

TEST_F(DynamicPriorityTaskDispatcherTest, DynamicScalingBehavior)
{
	EZLog("Test start\n");
	dispatcher.start();

	std::atomic<int> counter = 0;

	EZLog("Before for loop\n");
	for (int i = 0; i < 50; ++i)
	{
		dispatcher.enqueue([&counter, i]()
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(50));
				++counter;
			}, i % 10);
	}

	EZLog("Before sleep_for()\n");
	std::this_thread::sleep_for(std::chrono::seconds(2));
	EZLog("Before getWorkerCount()\n");
	size_t workers = dispatcher.getWorkerCount();
	EXPECT_GE(workers, 3);

	EZLog("Before dispatcher.stop()\n");
	dispatcher.stop();
	EZLog("Test start\n");
}

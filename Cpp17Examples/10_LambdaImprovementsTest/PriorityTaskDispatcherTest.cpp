#include "pch.h"
#include "gtest/gtest.h"
#include "..\10_LambdaImprovements\PriorityTaskDispatcher.h"

using namespace LambdaImprovements;

TEST(PriorityTaskDispatcherTest, TasksRunInPriorityOrder)
{
	PriorityTaskDispatcher dispatcher(2);

	std::vector<std::string> results;
	std::mutex resultMutex;

	auto low = dispatcher.enqueue(TaskPriority::Low,
		[&]()
		{
			std::lock_guard<std::mutex> lock(resultMutex);
			results.push_back("low");
		});

	auto high = dispatcher.enqueue(TaskPriority::High,
		[&]()
		{
			std::lock_guard<std::mutex> lock(resultMutex);
			results.push_back("high");
		});

	auto normal = dispatcher.enqueue(TaskPriority::Normal,
		[&]()
		{
			std::lock_guard<std::mutex> lock(resultMutex);
			results.push_back("normal");
		});

	low.get();
	normal.get();
	high.get();

	EXPECT_EQ(results.size(), 3u);
	EXPECT_EQ(results[0], "high");
	EXPECT_EQ(results[1], "normal");
	EXPECT_EQ(results[2], "low");
}

#include "pch.h"
#include "gtest/gtest.h"
#include "..\10_LambdaImprovements\GatherDispatcher.h"

using namespace LambdaImprovements;

TEST(GatherDispatcherTests, AllTasksReturnValues)
{
	GatherDispatcher<int> dispatcher;
	dispatcher.submit([]() {return 1; });
	dispatcher.submit([]() {return 2; });
	dispatcher.submit([]() {return 3; });

	auto futures = dispatcher.runAll();
	auto results = GatherDispatcher<int>::gather(futures);

	ASSERT_EQ(results.size(), 3);
	for (size_t i = 0; i < results.size(); ++i)
	{
		EXPECT_TRUE(std::holds_alternative<int>(results[i]));
		EXPECT_EQ(std::get<int>(results[i]), static_cast<int>(i + 1));
	}
}

TEST(GatherDispatcherTests, TaskThrowsException)
{
	GatherDispatcher<int> dispatcher;
	dispatcher.submit([]() {return 1; });
	dispatcher.submit([]() -> int { throw std::runtime_error("boom"); });

	auto futures = dispatcher.runAll();
	auto results = GatherDispatcher<int>::gather(futures);
	ASSERT_EQ(results.size(), 2);
	EXPECT_TRUE(std::holds_alternative<int>(results[0]));
	EXPECT_TRUE(std::holds_alternative<std::exception_ptr>(results[1]));


}

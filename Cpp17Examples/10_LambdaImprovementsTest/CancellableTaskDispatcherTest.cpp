#include "pch.h"
#include "gtest/gtest.h"
#include "..\10_LambdaImprovements\CancellableTaskDispatcher.h"

using namespace LambdaImprovements;

TEST(CancellableTaskDispatcherTests, TaskRunsNormally)
{
	CancellableTaskDispatcher dispatcher(2);
	CancelToken::CancelToken token;
	auto future = dispatcher.enqueue([](int a, int b) { return a + b; }, token, 3, 4);
	EXPECT_EQ(future.get(), 7);
}

TEST(CancellableTaskDispatcherTests, TaskCanBeCancelled)
{
	CancellableTaskDispatcher dispatcher(2);
	CancelToken::CancelToken token;

	auto future = dispatcher.enqueue(
		[](int ms)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(ms));
			return 42;
		}, token, 200);

	token.cancel();
	EXPECT_THROW(
		{
			try
			{
				future.get();
			}
			catch (const std::exception& e)
			{
				EXPECT_STREQ(e.what(), "Task cancelled before start");
				throw;
			}
		}, std::exception
	);
}

TEST(CancellableTaskDispatcherTests, TaskExceptionPropagates)
{
	CancellableTaskDispatcher dispatcher(2);
	CancelToken::CancelToken token;

	auto future = dispatcher.enqueue(
		[](int value) -> int
		{
			if (value == 0)
			{
				throw std::runtime_error("Divide by zero");
			}
			return 100 / value;
		}, token, 0);
	EXPECT_THROW(
		{
			try
			{
				future.get();
			}
			catch (const std::runtime_error& e)
			{
				EXPECT_STREQ(e.what(), "Divide by zero");
				throw;
			}
		}, std::runtime_error
	);
}


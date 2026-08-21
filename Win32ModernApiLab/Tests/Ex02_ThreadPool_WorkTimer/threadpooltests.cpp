#include <thread>
#include "gtest/gtest.h"
#include "classicthreadpipeline.h"
#include "modernthreadpoolpipeline.h"

using namespace Ex02_ThreadPool_WorkTimer;

namespace Ex02_ThreadPool_WorkTimerTests
{
	template<typename T>
	class ThreadPoolTests : public ::testing::Test{};

	using ThreadImplementations = ::testing::Types<ClassicThreadPipeline, ModernThreadPoolPipeline>;

	TYPED_TEST_CASE(ThreadPoolTests, ThreadImplementations);

	TYPED_TEST(ThreadPoolTests, BasicTest)
	{
		TaskData data{ 0, "dummy", false };

		TypeParam pipeline;
		pipeline.StartPeriodicMetrics(500);
		pipeline.SubmitTask(data);
		pipeline.Stop();	// Need to stop to make sure all tasks have been completed
		auto numTasks = pipeline.GetProcessedCount();
		EXPECT_EQ(1, numTasks);
	}

	TYPED_TEST(ThreadPoolTests, MultiThreadingTest)
	{
		const static uint32_t NUM_THREADS = 10;

		TaskData data{ 0, "dummy", false };

		TypeParam pipeline;
		pipeline.StartPeriodicMetrics(500);

		std::vector<std::jthread> threads;
		
		for (int i = 0; i < NUM_THREADS; ++i)
		{
			threads.emplace_back([&](){pipeline.SubmitTask(data);});
		}

		for (auto& t : threads)
		{
			if (t.joinable())
			{
				t.join();
			}
		}
		pipeline.Stop();	// Need to stop to make sure all tasks have been completed
		auto numTasks = pipeline.GetProcessedCount();
		EXPECT_EQ(10, numTasks);
	}

	TYPED_TEST(ThreadPoolTests, ZeroTaskTest)
	{
		TaskData data{ 0, "dummy", false };

		TypeParam pipeline;
		pipeline.StartPeriodicMetrics(500);
		pipeline.Stop();
		auto numTasks = pipeline.GetProcessedCount();
		EXPECT_EQ(0, numTasks);
	}

	TYPED_TEST(ThreadPoolTests, RapidStartStopTest)
	{
		TypeParam pipeline;
		pipeline.StartPeriodicMetrics(100);

		std::vector<std::jthread> threads;

		TaskData data{ 0, "dummy", false };
		for (int i = 0; i < 100; ++i)
		{
			pipeline.SubmitTask(data);
		}
		pipeline.Stop();
		SUCCEED();
	}

	TYPED_TEST(ThreadPoolTests, DestructionWithoutExplicitStopTest)
	{
		{
			TypeParam pipeline;
			pipeline.StartPeriodicMetrics(100);

			std::vector<std::jthread> threads;

			TaskData data{ 0, "dummy", false };
			for (int i = 0; i < 100; ++i)
			{
				pipeline.SubmitTask(data);
			}
			// Intentionally NOT call .Stop()
			// pipeline.Stop();
		} // The pipeline's destructor should be called and everything's cleaned up without problems

		SUCCEED();
	}

	TYPED_TEST(ThreadPoolTests, HighLoadBurstTest)
	{
		const static uint32_t NUM_THREADS = 50;
		const static uint32_t NUM_TASKS = 100;
		TaskData data{ 0, "dummy", false };

		TypeParam pipeline;
		pipeline.StartPeriodicMetrics(500);

		std::vector<std::jthread> threads;

		for (int i = 0; i < NUM_THREADS; ++i)
		{
			threads.emplace_back([&]()
				{
					for (int i = 0; i < NUM_TASKS; ++i)
					{
						pipeline.SubmitTask(data);
					}
				});
		}

		for (auto& t : threads)
		{
			if (t.joinable())
			{
				t.join();
			}
		}
		pipeline.Stop();
		auto numTasks = pipeline.GetProcessedCount();
		EXPECT_EQ(NUM_THREADS * NUM_TASKS, numTasks);
	}

	TYPED_TEST(ThreadPoolTests, PeriodicMetricsDurabilityTest)
	{
		const static uint32_t NUM_THREADS = 50;
		const static uint32_t NUM_TASKS = 100;
		TaskData data{ 0, "dummy", false };

		TypeParam pipeline;
		pipeline.StartPeriodicMetrics(10); // High frequent interval

		std::vector<std::jthread> threads;

		for (int i = 0; i < NUM_THREADS; ++i)
		{
			threads.emplace_back([&]()
				{
					for (int i = 0; i < NUM_TASKS; ++i)
					{
						pipeline.SubmitTask(data);
					}
				});
		}

		for (auto& t : threads)
		{
			if (t.joinable())
			{
				t.join();
			}
		}
		pipeline.Stop();
		auto numTasks = pipeline.GetProcessedCount();
		EXPECT_EQ(NUM_THREADS * NUM_TASKS, numTasks);
	}
}

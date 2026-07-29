#include <array>
#include "gtest/gtest.h"
#include "job_scheduler.h"

using namespace Ex02_JobSystem;

namespace Ex02_JobSystemTests
{
	TEST(JobSystemTests, JobScheduler_NotNested)
	{
		JobScheduler scheduler(8);

		std::atomic<uint32_t> result = 0;
		auto lambda1 = [&result](uint32_t param1)
			{
				LOG(INFO) << "lambda1(" << param1 << ")";
				result.fetch_add(param1 * param1); 
			};
		auto lambda2 = [&result](uint32_t param1, uint32_t param2)
			{
				LOG(INFO) << "lambda2(" << param1 << "," << param2 << ")";
				result.fetch_add(param1 * param2);
			};
		auto lambda3 = [&result](uint32_t param1, uint32_t param2, uint32_t param3)
			{
				LOG(INFO) << "lambda2(" << param1 << "," << param2 << "," << param3 << ")";
				result.fetch_add(param1 * param2); result.fetch_add(param3);
			};


		scheduler.submit(lambda1, 10);		// 0 += 10 * 10 => 100
		scheduler.submit(lambda2, 2, 3);	// 100 += 2 * 3 => 106
		scheduler.submit(lambda3, 4, 5, 6);	// 106 += (4*5) + 6 => 132
		scheduler.submit(lambda3, 7, 8, 9);	// 132 += (7*8) + 9 => 197
		scheduler.submit(lambda2, 10, 11);	// 197 += (10*11) => 307
		scheduler.submit(lambda1, 4);		// 307 += (4*4) => 323
		scheduler.submit(lambda2, 8, 9);	// 323 += (8*9) => 395
		scheduler.submit(lambda2, 10, 5);	// 395 += (10*5) => 445
		scheduler.submit(lambda3, 1, 2, 3);	// 445 += (1*2) + 3 => 450
		scheduler.submit(lambda3, 3, 0, 0);	// 450 += (3*0) + 0 -> 450
		scheduler.submit(lambda1, 6);		// 450 += (6*6) => 486

		scheduler.stop();
		scheduler.join();

		ASSERT_EQ(486, result.load());
	}

	TEST(JobSystemTests, JobScheduler_Stress_NotNested)
	{
		constexpr size_t TASK_COUNT = 10'000;
		constexpr uint8_t NUM_THREADS = 8;
		std::array<size_t, NUM_THREADS> workers{};

		JobScheduler scheduler(NUM_THREADS);

		for (size_t i = 0; i < TASK_COUNT; ++i)
		{
			scheduler.submit([&workers]()
				{
					size_t m_id = Ex02_JobSystem::t_currentWorkerId;
					if (m_id != Ex02_JobSystem::INVALID_WORKER_ID)
					{
						workers[m_id]++;
					}
				});
		}

		scheduler.stop();
		scheduler.join();

		size_t sum = 0;
		for (size_t v : workers)
		{
			sum += v;
		}
		ASSERT_EQ(TASK_COUNT, sum);

		for (size_t v : workers)
		{
			ASSERT_TRUE(v != 0);
		}
	}
}

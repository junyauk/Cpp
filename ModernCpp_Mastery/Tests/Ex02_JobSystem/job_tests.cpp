#include "gtest/gtest.h"
#include <cstdio>
#include "job.h"
#include "work_stealing_queue.h"
#include "simple_logger.h"

using namespace SimpleLogger;
using namespace Ex02_JobSystem;

namespace Ex02_JobSystemTests
{
	TEST(JobSystemTests, Jobs)
	{
		uint32_t local1 = 10;
		uint32_t local2 = 20;

		{
			auto lambda = [local1, local2](uint32_t param1, uint32_t param2) -> void
				{
					uint32_t sum = local1 + local2 + param1 + param2;
					LOG(INFO) << "Sum: " << sum;
				};
			Job job(lambda, 3, 4);
			job();
		}

		{
			std::function<void(uint32_t, uint32_t)> func = [local1, local2](uint32_t param1, uint32_t param2)
				{
					uint32_t multiplied = local1 * local2 * param1 * param2;
					LOG(INFO) << "multiplied: " << multiplied;
				};
			Job job(func, 2, 6);
			job();
		}
	}

	TEST(JobSystemTests, WorkStealingQueue_Methods)
	{
		WorkStealingQueue<Job> q;
		uint32_t result;

		auto lambda = [&result](uint32_t param1, uint32_t param2) -> void
			{
				uint32_t sum = param1 + param2;
				result = sum;
			};
		Job job0(lambda, 1, 2);
		Job job1(lambda, 3, 4);
		Job job2(lambda, 5, 6);
		Job job3(lambda, 7, 8);

		q.push(std::move(job0));
		q.push(std::move(job1));
		q.push(std::move(job2));
		q.push(std::move(job3));
		auto poppedJob3 = q.pop();
		if (poppedJob3.has_value())
		{
			poppedJob3.value()();
			ASSERT_EQ(result, 7 + 8);
		}
		auto stealedJob0 = q.steal();
		if (stealedJob0.has_value())
		{
			stealedJob0.value()();
			ASSERT_EQ(result, 1 + 2);
		}
		ASSERT_FALSE(q.empty());
		auto poppedJob2 = q.pop();
		ASSERT_FALSE(q.empty());
		auto poppedJob1 = q.pop();
		ASSERT_TRUE(q.empty());
	}
}


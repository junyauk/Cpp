#include "gtest/gtest.h"
#include <cstdio>
#include <vector>
#include <memory>
#include <chrono>
#include "job.h"
#include "work_stealing_queue.h"
#include "worker_thread.h"
#include "job_scheduler.h"


using namespace Ex02_JobSystem;

namespace Ex02_JobSystemTests
{
	TEST(JobSystemTests, WorkerThreads)
	{
		constexpr size_t NUM_WORKERS = 3;
		std::vector<std::unique_ptr<WorkerThread<Job>>> workerThreads;
		workerThreads.reserve(NUM_WORKERS);

		workerThreads.push_back(std::make_unique<WorkerThread<Job>>());
		workerThreads.push_back(std::make_unique<WorkerThread<Job>>());
		workerThreads.push_back(std::make_unique<WorkerThread<Job>>());

		for (int i = 0; i < NUM_WORKERS; ++i)
		{
			workerThreads[i]->setSiblings(workerThreads);
		}
		for (int i = 0; i < NUM_WORKERS; ++i)
		{
			workerThreads[i]->start();
		}

		auto lambda = [&](uint32_t param1, uint32_t param2) -> void
			{
				uint32_t sum = param1 + param2;
			};
		Job job0(lambda, 1, 2);
		Job job1(lambda, 3, 4);
		Job job2(lambda, 5, 6);
		Job job3(lambda, 7, 8);



		std::this_thread::sleep_for(std::chrono::milliseconds(3000));

		for (int i = 0; i < NUM_WORKERS; ++i)
		{
			workerThreads[i]->stop();
		}
	}
}
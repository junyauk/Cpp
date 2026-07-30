#include <benchmark/benchmark.h>
#include <latch>
#include "job_scheduler.h"


using namespace Ex02_JobSystem;

constexpr uint64_t TOTAL_RANGE = 10'000'000;
constexpr size_t CHUNK_COUNT = 64;
constexpr uint64_t CHUNK_SIZE = TOTAL_RANGE / CHUNK_COUNT;

static bool isPrime(uint64_t n)
{
	if (n <= 1) false;
	if (n <= 3) true;
	if (n % 2 == 0 || n % 3 == 0) false;

	for (uint64_t i = 5; i * i <= n; ++i)
	{
		if (n % i == 0 || n % (i + 2) == 0)
		{
			return false;
		}
	}
	return true;
}

static uint64_t countPrimesInRange(uint64_t start, uint64_t end)
{
	uint64_t total = 0;
	for (uint64_t i = start; i < end - 1; ++i)
	{
		if (isPrime(i)) total++;
	}
	return total;
}

static void BM_PureSequential(benchmark::State& state)
{
	for (auto _ : state)
	{
		uint64_t totalPrimes = 0;
		for (int i = 0; i < 64; ++i)
		{
			uint64_t start = i * CHUNK_SIZE + 1;
			uint64_t end = (i == CHUNK_COUNT - 1) ? TOTAL_RANGE : (i + 1) * CHUNK_SIZE;
			totalPrimes += countPrimesInRange(start, end);
		}
		benchmark::DoNotOptimize(totalPrimes);
	}
}

static void BM_JobScheduler_SingleThread(benchmark::State& state)
{
	JobScheduler scheduler(1);
	for (auto _ : state)
	{
		std::latch completionLatch(CHUNK_COUNT);
		std::atomic<uint64_t> totalPrimes{ 0 };

		for (int i = 0; i < CHUNK_COUNT; ++i)
		{
			uint64_t start = i * CHUNK_SIZE + 1;
			uint64_t end = (i == CHUNK_COUNT - 1) ? TOTAL_RANGE : (i + 1) * CHUNK_SIZE;

			scheduler.submit([&totalPrimes, &completionLatch, start, end]()
				{
					totalPrimes.fetch_add(countPrimesInRange(start, end), std::memory_order_relaxed);
					completionLatch.count_down();
				});
		}
		completionLatch.wait();
		benchmark::DoNotOptimize(totalPrimes);
	}
}

static void BM_JobScheduler_MultiThread(benchmark::State& state)
{
	JobScheduler scheduler(8);
	for (auto _ : state)
	{
		std::latch completionLatch(CHUNK_COUNT);
		std::atomic<uint64_t> totalPrimes{ 0 };

		for (int i = 0; i < CHUNK_COUNT; ++i)
		{
			uint64_t start = i * CHUNK_SIZE + 1;
			uint64_t end = (i == CHUNK_COUNT - 1) ? TOTAL_RANGE : (i + 1) * CHUNK_SIZE;

			scheduler.submit([&totalPrimes, &completionLatch, start, end]()
				{
					totalPrimes.fetch_add(countPrimesInRange(start, end), std::memory_order_relaxed);
					completionLatch.count_down();
				});
		}
		completionLatch.wait();
		benchmark::DoNotOptimize(totalPrimes);
	}
}



BENCHMARK(BM_PureSequential)->UseRealTime();
BENCHMARK(BM_JobScheduler_SingleThread)->UseRealTime();
BENCHMARK(BM_JobScheduler_MultiThread)->UseRealTime();

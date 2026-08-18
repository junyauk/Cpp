#include <benchmark/benchmark.h>
#include <vector>
#include <memory>
#include "classicmutexcache.h"
#include "modernsrwcache.h"

using namespace Ex01_SRWLock_CondVar;

class CacheFixture : public benchmark::Fixture
{
public:
	const uint32_t NUM_KEYS = 100;
	inline static std::unique_ptr<ClassicMutexCache> classic;
	inline static std::unique_ptr<ModernSrwCache> modern;

	inline static std::vector<std::string> keys;
	inline static std::vector<std::string> values;

	void SetUp(benchmark::State& state) override
	{
		if (state.thread_index() == 0)
		{
			classic = std::make_unique<ClassicMutexCache>(NUM_KEYS);
			modern = std::make_unique<ModernSrwCache>(NUM_KEYS);

			// Pre-fill the caches with some data
			for (uint32_t i = 0; i < NUM_KEYS; ++i)
			{
				std::string key = "key" + std::to_string(i);
				std::string value = "value" + std::to_string(i);
				keys.push_back(key);
				values.push_back(value);

				classic->Put(key, value);
				modern->Put(key, value);
			}
		}
	}

	void TearDown(benchmark::State& state) override
	{
		if (state.thread_index() == 0)
		{
			// Clear the caches after each benchmark
			for (uint32_t i = 0; i < NUM_KEYS; ++i)
			{
				std::string key = "key" + std::to_string(i);
				classic->Remove(key);
				modern->Remove(key);
			}

			keys.clear();
			values.clear();
		}
	}
};

BENCHMARK_DEFINE_F(CacheFixture, ClassicMutexCacheGet)(benchmark::State& state)
{
	uint64_t itr = 0;
	for (auto _ : state)
	{
		std::string value;
		uint32_t index = itr++ % NUM_KEYS;
		if ((itr % 10) < 9)
		{
			classic->Get(keys[index], value);
		}
		else
		{
			classic->Put(keys[index], values[index]);
		}
	}
}

BENCHMARK_DEFINE_F(CacheFixture, ModernSrwCacheGet)(benchmark::State& state)
{
	uint64_t itr = 0;
	for (auto _ : state)
	{
		std::string value;
		uint32_t index = itr++ % NUM_KEYS;
		if ((itr % 10) < 9)
		{
			modern->Get(keys[index], value);
		}
		else
		{
			modern->Put(keys[index], values[index]);
		}
	}
}

BENCHMARK_REGISTER_F(CacheFixture, ClassicMutexCacheGet)->Threads(1)->Threads(2)->Threads(4)->Threads(8)->Threads(16)->UseRealTime();
BENCHMARK_REGISTER_F(CacheFixture, ModernSrwCacheGet)->Threads(1)->Threads(2)->Threads(4)->Threads(8)->Threads(16)->UseRealTime();

BENCHMARK_MAIN();


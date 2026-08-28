#include <benchmark/benchmark.h>
#include "classicdispatchermanager.h"
#include "moderndispatchernanager.h"

using namespace Ex04_AddressWait_OnceInit;

template<typename ManagerType>
static void BM_DispatcherManager(benchmark::State& state)
{
	static std::unique_ptr<ManagerType> manager; // Initialized once and it is kept for all threads
	// 1. Setup
	if (state.thread_index() == 0)
	{
		// Thread 0 creates the manager before timing starts
		manager = std::make_unique<ManagerType>();
	}
	TaskData data{ 1, 10 };

	// 2. Timed region: All threads execute Push concurrently
	for (auto _ : state)
	{
		for (uint32_t i = 0; i < state.range(0); ++i)
		{
			manager->Push(data);
		}
	}

	// 3. Teardown
	if (state.thread_index() == 0)
	{
		// Thread 0 cleans up AFTER all threads finish the loop
		manager->Stop();
		manager.reset();
	}
}
#if 0
BENCHMARK_TEMPLATE(BM_DispatcherManager, ClassicDispatcherManager)->Range(100, 10000)->Threads(1)->Threads(2)->Threads(4)->Threads(8)->Threads(16)->UseRealTime();
BENCHMARK_TEMPLATE(BM_DispatcherManager, ModernDispatcherManager)->Range(100, 10000)->Threads(1)->Threads(2)->Threads(4)->Threads(8)->Threads(16)->UseRealTime();
#endif

#include <memory>
#include "gtest/gtest.h"
#include "classicdispatchermanager.h"
#include "moderndispatchernanager.h"

using namespace Ex04_AddressWait_OnceInit;

namespace Ex04_AddressWait_OnceInitTests
{
	template<typename T>
	class DispatcherManagerTests : public ::testing::Test {};
	using DispatcherManagerImplementations = ::testing::Types<ClassicDispatcherManager, ModernDispatcherManager>;
	TYPED_TEST_CASE(DispatcherManagerTests, DispatcherManagerImplementations);

	TYPED_TEST(DispatcherManagerTests, Basic)
	{
		TypeParam manager;
		TaskData data{ 1, 10 };
		
		manager.Push(data);
		uint32_t results = manager.Stop();
		EXPECT_EQ(1, results);
	}

	TYPED_TEST(DispatcherManagerTests, MultiProducers)
	{
		const static uint32_t NUM_THREADS = 4;
		const static uint32_t NUM_DATA = 250;
		uint32_t numThreads = NUM_THREADS;
		TaskData data{ 1, 10 };
		std::vector<std::jthread> threads;

		TypeParam manager;

		for (uint32_t i = 0; i < numThreads; ++i)
		{
			threads.emplace_back([&](std::stop_token st)
				{
					for (int i = 0; i < NUM_DATA; ++i)
					{
						manager.Push(data);
					}
				}
			);
		}

		for (auto& t : threads)
		{
			t.request_stop();
		}
		for (auto& t : threads)
		{
			if (t.joinable()) t.join();
		}

		uint32_t results = manager.Stop();
		EXPECT_EQ(NUM_THREADS * NUM_DATA, results);
	}
}


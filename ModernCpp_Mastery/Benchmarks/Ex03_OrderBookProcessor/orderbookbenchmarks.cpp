#include <benchmark/benchmark.h>
#include "classicorderbook.h"
#include "modernorderbook.h"

using namespace Ex03_OrderBookProcessor;

constexpr uint64_t NUM_ORDERS = 10'000'000;

namespace Ex03_OrderBookProcessorBenchmarks
{
	class Ex03_OrderBookFixture : public ::benchmark::Fixture
	{
	public:
		inline static std::once_flag init_flag;
		inline static std::unique_ptr<ClassicOrderBook<Order>> classic;
		inline static std::unique_ptr<ModernOrderBook<Order>> modern;
		void SetUp(benchmark::State& state)
		{
			std::call_once(init_flag, []()
				{
					classic = std::make_unique<ClassicOrderBook<Order>>(1);
					modern = std::make_unique<ModernOrderBook<Order>>(1);

					Order buy{ 1, 1, 1, 10, 10, BUY, LIMIT, ADD };
					Order sell{ 2, 1, 1, 20, 10, SELL, LIMIT, ADD };
					classic->Add(buy);
					classic->Add(sell);
					modern->Add(buy);
					modern->Add(sell);
				});
		}
	};

	BENCHMARK_DEFINE_F(Ex03_OrderBookFixture, Classic)(benchmark::State& st)
	{
		for (auto _ : st)
		{
			thread_local static uint32_t times = 0;
			auto bid = classic->GetBestBid();
			auto ask = classic->GetBestAsk();
			if (times % 10 == 0)
			{
				if (bid.has_value())
				{
					bid.value().price++;
					classic->Add(bid.value());
				}
				if (ask.has_value())
				{
					ask.value().price++;
					classic->Add(ask.value());
				}
			}
			++times;
		}
	}

	BENCHMARK_DEFINE_F(Ex03_OrderBookFixture, Modern)(benchmark::State& st)
	{
		for (auto _ : st)
		{
			thread_local static uint32_t times = 0;
			auto bid = modern->GetBestBid();
			auto ask = modern->GetBestAsk();
			if (times % 10 == 0)
			{
				if (bid.has_value())
				{
					bid.value().price++;
					modern->Add(bid.value());
				}
				if (ask.has_value())
				{
					ask.value().price++;
					modern->Add(ask.value());
				}
			}
			++times;
		}
	}

	BENCHMARK_REGISTER_F(Ex03_OrderBookFixture, Classic)->Threads(1)->Threads(2)->Threads(4)->Threads(8)->UseRealTime();
	BENCHMARK_REGISTER_F(Ex03_OrderBookFixture, Modern)->Threads(1)->Threads(2)->Threads(4)->Threads(8)->UseRealTime();
}


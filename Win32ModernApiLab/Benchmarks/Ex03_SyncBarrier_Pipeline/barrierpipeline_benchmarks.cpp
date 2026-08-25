#include <benchmark/benchmark.h>
#include "classicbarrierpipeline.h"
#include "modernsyncbarrierpipeline.h"

using namespace Ex03_SyncBarrier_Pipeline;

template<typename PipelineType>
static void BM_Pipeline(benchmark::State& state)
{
	FrameBatch masterBatch;
	for (int i = 0; i < state.range(0); ++i)
	{
		masterBatch.pixelData.push_back(0.1f * (i % 11));
	}

	for (auto _ : state)
	{
		state.PauseTiming();
		PipelineType pipeline;
		FrameBatch fb = masterBatch;
		PipelineMetrics<std::chrono::nanoseconds> metrics;
		state.ResumeTiming();

		pipeline.Process(fb, &metrics);

		state.PauseTiming();
		metrics.Reset();
		state.ResumeTiming();
	}

	state.SetItemsProcessed(state.iterations() * state.range(0));
	state.SetBytesProcessed(state.iterations() * state.range(0) * sizeof(float));
}

BENCHMARK_TEMPLATE(BM_Pipeline, ClassicBarrierPipeline)->Range(10000, 1000000);
BENCHMARK_TEMPLATE(BM_Pipeline, ModernSyncBarrierPipeline)->Range(10000, 1000000);

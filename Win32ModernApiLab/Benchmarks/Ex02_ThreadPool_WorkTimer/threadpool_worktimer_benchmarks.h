#pragma once
#include <benchmark/benchmark.h>
#include <vector>
#include <memory>
#include "classicthreadpipeline.h"
#include "modernthreadpoolpipeline.h"

using namespace Ex02_ThreadPool_WorkTimer;

const static uint32_t NUM_TASKS = 10000;

// Note:
// This demonstrates how to run with multi threads without using Google test fixture.

template<typename PipelineType>
static void BM_Pipeline_Single(benchmark::State& state)
{
	for (auto _ : state)
	{
		state.PauseTiming();
		PipelineType pipeline;
		TaskData data{ 0, "dummy", false };
		pipeline.StartPeriodicMetrics(10);
		state.ResumeTiming();

		for (uint32_t i = 0; i < state.range(0); ++i)
		{
			pipeline.SubmitTask(data);
		}
		pipeline.Stop();
	}
	state.SetItemsProcessed(state.iterations() * state.range(0));
}

template<typename PipelineType>
static void BM_Pipeline_Multi(benchmark::State& state)
{
	static std::unique_ptr<PipelineType> pipeline;
	static std::atomic<bool> is_ready{ false };
	TaskData data{ 0, "dummy", false };

	// 1. Untimed setup
	if (state.thread_index() == 0)
	{
		pipeline = std::make_unique<PipelineType>();
		pipeline->StartPeriodicMetrics(10);
		is_ready.store(true, std::memory_order_release);
	}
	else
	{
		while (!is_ready.load(std::memory_order_acquire)) {}
	}

	// 2. Thread execution loop
	for (auto _ : state)
	{
		for (uint32_t i = 0; i < state.range(0); ++i)
		{
			pipeline->SubmitTask(data);
		}
	}

	// 3. Untimed teardown
	if (state.thread_index() == 0)
	{
		pipeline->Stop();
		is_ready.store(false, std::memory_order_relaxed);
	}
}

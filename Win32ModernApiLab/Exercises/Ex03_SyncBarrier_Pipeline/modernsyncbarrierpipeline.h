#pragma once
#include <algorithm>
#include <vector>
#include <thread>
#include <chrono>
#include <span>
#include <Windows.h>
#include "framebatch.h"
#include "pipelinemetrics.h"

namespace Ex03_SyncBarrier_Pipeline
{
	class ModernSyncBarrierPipeline
	{
	public:
		ModernSyncBarrierPipeline()
			: m_numThreads(std::thread::hardware_concurrency())
		{
			InitializeSynchronizationBarrier(&m_barrier, m_numThreads, -1);
		}
		~ModernSyncBarrierPipeline()
		{
			Stop();
			DeleteSynchronizationBarrier(&m_barrier);
		}

		ModernSyncBarrierPipeline(const ModernSyncBarrierPipeline&) = delete;
		ModernSyncBarrierPipeline(ModernSyncBarrierPipeline&&) = delete;
		ModernSyncBarrierPipeline& operator=(const ModernSyncBarrierPipeline&) = delete;
		ModernSyncBarrierPipeline& operator=(ModernSyncBarrierPipeline&&) = delete;

		void Stop()
		{
			for (auto& t : m_threads)
			{
				t.request_stop();
			}

			// Make sure all threads finished 
			for (auto& t : m_threads)
			{
				if (t.joinable())
				{
					t.join();
				}
			}
			m_threads.clear();
		}

		template<typename DurationT = std::chrono::nanoseconds>
		void Process(FrameBatch& batch, PipelineMetrics<DurationT>* metrics = nullptr)
		{
			if (batch.pixelData.empty()) return;
			size_t length = batch.pixelData.size() / m_numThreads;
			size_t rest = batch.pixelData.size() % m_numThreads;

			size_t index = 0;
			for (int i = 0; i < m_numThreads; ++i)
			{
				size_t chunkSize = length + ((rest-- > 0) ? 1 : 0);
				if (rest == -1) rest = 0;

				std::span<float> thread_span(
					&batch.pixelData[(chunkSize) ? index : 0],
					chunkSize);
				index += chunkSize;

				// Note:
				// i and thread_span are local variable, 
				// so they will be destroyed when a thread uses them, so they need to be copied, not reference.
				m_threads.emplace_back(
					[this, i, thread_span, metrics]
					(std::stop_token st) {WorkerThread(st, i, thread_span, metrics); });
			}

			Stop();
		}

	private:
		template<typename DurationT = std::chrono::nanoseconds>
		void WorkerThread(std::stop_token st, size_t id, std::span<float> data, PipelineMetrics<DurationT>* metrics = nullptr)
		{
			std::chrono::steady_clock::time_point s, e;
			DurationT duration;
			BOOL isLeader = false;

			isLeader = EnterSynchronizationBarrier(&m_barrier, 0);
			if (isLeader && (metrics != nullptr))
			{
				metrics->Reset();
				s = std::chrono::steady_clock::now();
			}
			Process_A(data);
			isLeader = EnterSynchronizationBarrier(&m_barrier, 0);
			if (isLeader && (metrics != nullptr))
			{
				e = std::chrono::steady_clock::now();
				duration = std::chrono::duration_cast<DurationT>(e - s);
				metrics->RecordPhaseDuration(duration);
				s = std::chrono::steady_clock::now();
			}
			Process_B(data);
			isLeader = EnterSynchronizationBarrier(&m_barrier, 0);
			if (isLeader && (metrics != nullptr))
			{
				e = std::chrono::steady_clock::now();
				duration = std::chrono::duration_cast<DurationT>(e - s);
				metrics->RecordPhaseDuration(duration);
				s = std::chrono::steady_clock::now();
			}

			Process_C(data);
			isLeader = EnterSynchronizationBarrier(&m_barrier, 0);
			if (isLeader && (metrics != nullptr))
			{
				e = std::chrono::steady_clock::now();
				duration = std::chrono::duration_cast<DurationT>(e - s);
				metrics->RecordPhaseDuration(duration);
			}
		}

		void Process_A(std::span<float> data)
		{
			for (float& f : data)
			{
				// Gain/Brightness adjustment
				f = std::clamp(f * 1.25f + 0.05f, 0.0f, 1.0f);
			}
		}
		void Process_B(std::span<float> data)
		{
			constexpr float gamma = 2.2f;
			for (float& f : data)
			{
				f = std::pow(f, 1.0f / gamma);
			}
		}

		void Process_C(std::span<float> data)
		{
			for (float& f : data)
			{
				f = std::sin(f * 3.14159f * 0.5f);
			}
		}

		const int m_numThreads;
		SYNCHRONIZATION_BARRIER m_barrier;
		std::vector<std::jthread> m_threads;
	};
}

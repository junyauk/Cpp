#pragma once
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <string>
#include <stop_token>
#include <iostream>
#include <atomic>
#include <functional>
#include <future>
#include <optional>

namespace ParallelSumWorkerSamples
{
	class ParallelSumWorker
	{
	private:
		void worker(std::stop_token st);
		std::vector<int> m_data;
		std::jthread m_thread;
		std::mutex m_mutex;
		std::optional<long long> m_result;
	public:
		ParallelSumWorker(std::vector<int> data);
		~ParallelSumWorker();

		void stop();

		std::optional<long long> latestResult();
	};

	class ParallelSumWorker2
	{
	private:
		std::vector<int> m_data;
		size_t m_begin;
		size_t m_end;
		std::stop_token m_st;
	public:
		ParallelSumWorker2(const std::vector<int>& data,
			size_t begin,
			size_t end,
			std::stop_token st)
			:m_data(data), m_begin(begin), m_end(end), m_st(st) {
		}
		long long operator()();
	};
	long long parallel_sum(const std::vector<int>& data, int num_workers, std::stop_source& ssrc);
}

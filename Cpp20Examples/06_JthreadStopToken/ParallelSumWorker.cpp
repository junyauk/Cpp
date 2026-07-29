#include "pch.h"
#include <numeric>
#include "ParallelSumWorker.h"

namespace ParallelSumWorkerSamples
{
	void ParallelSumWorker::worker(std::stop_token st)
	{
		while (!st.stop_requested())
		{
			long long sum = std::accumulate(m_data.begin(), m_data.end(), 0LL);
			{
				// Lock the mutex to safely update the result
				std::lock_guard<std::mutex> lock(m_mutex);
				m_result = sum; // Update the result
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
	}
	ParallelSumWorker::ParallelSumWorker(std::vector<int> data)
	{
		m_data = std::move(data);
		m_thread = std::jthread([this](std::stop_token st)
			{
				this->worker(st);
			});
	}
	ParallelSumWorker::~ParallelSumWorker()
	{
		stop();
		std::cout << "ParallelSumWorker destroyed." << std::endl;
	}

	void ParallelSumWorker::stop()
	{
		if (m_thread.joinable())
		{
			m_thread.request_stop();
			m_thread.join();
		}
	}

	std::optional<long long> ParallelSumWorker::latestResult()
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		return m_result;
	}

	long long ParallelSumWorker2::operator()()
	{
		long long sum = 0;
		for (size_t i = m_begin; i < m_end; ++i)
		{
			if (m_st.stop_requested())
			{
				std::cout << "Worker [" << m_begin << "-" << m_end << "] stopped.\n";
				return sum;
			}
			sum += m_data[i];
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
		std::cout << "Worker [" << m_begin << "-" << m_end << "] finished.\n";
		return sum;
	}

	long long parallel_sum(const std::vector<int>& data, int num_workers, std::stop_source& ssrc)
	{
		size_t block_size = data.size() / num_workers;
		std::vector<std::future<long long>> futures;

		for (int i = 0; i < num_workers; ++i)
		{
			size_t begin = i * block_size;
			size_t end = (i == num_workers - 1) ? data.size() : (i+1) + block_size;

			ParallelSumWorker2 worker(data, begin, end, ssrc.get_token());
//			futures.push_back(std::async(std::launch::async, std::ref(worker)));
			futures.push_back(std::async(std::launch::async, worker));
		}

		long long total_sum = 0;
		for (auto& fut : futures)
		{
			total_sum += fut.get();
		}
		return total_sum;
	}
}
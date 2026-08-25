#pragma once
#include <mutex>
#include <functional>
#include <condition_variable>

// Note:
// This class demonstrates how std::condition_variable and std::mutex work as barrier like std::barrier.

namespace Ex03_SyncBarrier_Pipeline
{
	class ClassicBarrier
	{
	public:
		ClassicBarrier(const size_t numThreads) : m_threadCount(numThreads)	{}
		~ClassicBarrier() {}

		ClassicBarrier(const ClassicBarrier&) = delete;
		ClassicBarrier(ClassicBarrier&&) = delete;
		ClassicBarrier& operator=(const ClassicBarrier&) = delete;
		ClassicBarrier& operator=(ClassicBarrier&&) = delete;

		void wait()
		{
			std::unique_lock<std::mutex> lock(m_mutex);
			// Capture the current generation
			const auto localGen = m_generation;
			// Update the waiting count
			++m_waitingCount;

			if (m_waitingCount == m_threadCount)
			{
				// All threads arrived, reset the count and step to the next generation
				m_waitingCount = 0;
				++m_generation;
				m_cv.notify_all();
			}
			else
			{
				// Wait for other threads
				m_cv.wait(lock, [&]() {return m_generation > localGen; });
			}
		}

	private:
		std::mutex m_mutex;
		std::condition_variable m_cv;
		const size_t m_threadCount;
		size_t m_waitingCount = 0;
		size_t m_generation = 0;
	};
}

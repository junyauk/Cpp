#pragma once
#include <Windows.h>
#include <atomic>


namespace Ex02_ThreadPool_WorkTimer
{
	// Note:
	// This ThreadPool class wraps ThreadPool related Win32APIs, and demonstrate how to use them.
	// And also demonstrate APIs are used in RAII design.

	class ThreadPool
	{
	public:
		ThreadPool();
		~ThreadPool();

		// Copy and move constructors and operators must be deleted
		ThreadPool(const ThreadPool&) = delete;
		ThreadPool(ThreadPool&&) = delete;
		ThreadPool& operator=(const ThreadPool&) = delete;
		ThreadPool& operator=(ThreadPool&&) = delete;

		void Initialize(uint32_t minThreads, uint32_t maxThreads);
		void Stop();
		void SetWork(PTP_WORK_CALLBACK callback, PVOID context);
		void SubmitWork();
		void StartTimer(PTP_TIMER_CALLBACK callback, PVOID context, uint32_t intervalMs);
		void StopTimer();

	private:
		TP_CALLBACK_ENVIRON m_environ;
		PTP_CLEANUP_GROUP m_cleanupGroup = nullptr;
		PTP_TIMER m_timer = nullptr;
		PTP_WORK m_worker = nullptr;
		PTP_POOL m_pool = nullptr;
		uint32_t m_intervalMs = 0;
	};
}

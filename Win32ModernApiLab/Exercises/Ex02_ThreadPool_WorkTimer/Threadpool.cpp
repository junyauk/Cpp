#include <Windows.h>
#include <thread>
#include <iostream>
#include "threadpool.h"

namespace Ex02_ThreadPool_WorkTimer
{
	ThreadPool::ThreadPool(){}

	ThreadPool::~ThreadPool()
	{
		Stop();
	}

	void ThreadPool::Initialize(uint32_t minThreads, uint32_t maxThreads)
	{
		// How to setup a thread pool with a cleanup group and a work object in Windows:
		// 1. Initialize the thread pool environment
		// 2. Create a thread pool, and associate it with the environment
		// 3. Create a cleanup group, and associate it with the environment

		// 1. Environment ---------------------------------------
		// Note:
		// Threadpool environment is not essentioal if you don't need to customize the thread pool behavior,
		// however it is recommended to use it for better control and management of the thread pool resources.
		// 1-1. Initialize the thread pool environment
		InitializeThreadpoolEnvironment(&m_environ);

		// 2. Thread Pool ---------------------------------------
		// 2-1. Create the thread pool
		m_pool = CreateThreadpool(nullptr);
		if (!m_pool)
		{
			throw std::runtime_error("Failed to create thread pool");
		}
		SetThreadpoolThreadMaximum(m_pool, maxThreads);
		SetThreadpoolThreadMinimum(m_pool, minThreads);

		// 2-2. Associate the thread pool with the callback environment
		SetThreadpoolCallbackPool(&m_environ, m_pool);

		// 3. Cleanup Group -------------------------------------
		// 3-1. Create a cleanup group for the thread pool
		m_cleanupGroup = CreateThreadpoolCleanupGroup();
		if (!m_cleanupGroup)
		{
			CloseThreadpool(m_pool);
			m_pool = nullptr;
			throw std::runtime_error("Failed to create thread pool cleanup group");
		}
		// 3-2. Associate the cleanup group with the callback environment
		SetThreadpoolCallbackCleanupGroup(&m_environ, m_cleanupGroup, nullptr);
	}

	void ThreadPool::Stop()
	{
		if (m_pool == nullptr)
		{
			return;
		}

		// Note:
		// Cleanup group members must be closed before the thread pool is closed, 
		// and the thread pool must be closed before the environment is destroyed.
		// Timers will be automatically canceled when the cleanup group is closed, 
		// so we don't need to explicitly cancel it.

		// 1. Close the cleanup group and wait for any pending callbacks to complete
		// Worker submitted by SubmitThreadpoolWork will be automatically waited and closed
		// Timers created by CreateThreadpoolTimer will be automatically canceled and closed
		CloseThreadpoolCleanupGroupMembers(m_cleanupGroup, FALSE, &m_environ);
		CloseThreadpoolCleanupGroup(m_cleanupGroup);
		m_worker = nullptr;
		m_timer = nullptr;
		m_cleanupGroup = nullptr;

		// 2. Close the thread pool and wait for any pending callbacks to complete
		CloseThreadpool(m_pool);
		m_pool = nullptr;

		// 3. Finally destroy the thread pool environment
		DestroyThreadpoolEnvironment(&m_environ);
	}

	void ThreadPool::SetWork(PTP_WORK_CALLBACK callback, PVOID context)
	{
		m_worker = CreateThreadpoolWork(callback, context, &m_environ);
		if (!m_worker)
		{
			throw std::runtime_error("Failed to create thread pool work");
		}
	}

	void ThreadPool::SubmitWork()
	{
		if (m_pool != nullptr && m_worker != nullptr)
		{
			SubmitThreadpoolWork(m_worker);
		}
	}

	void ThreadPool::StartTimer(PTP_TIMER_CALLBACK callback, PVOID context, uint32_t intervalMs)
	{
		if (m_pool == nullptr)
		{
			return;
		}

		if (m_timer == nullptr)
		{
			// Create a new timer
			m_timer = CreateThreadpoolTimer(callback, context, &m_environ);
			if (!m_timer)
			{
				throw std::runtime_error("Failed to create thread pool timer");
			}
		}

		// Note:
		// The due time for the timer is specified in 100-nanosecond intervals,
		// Negative values: indicate relative time
		// Positive values: indicate absolute time
		// Specified in nano seconds, so we need to convert milliseconds to 100-nanosecond intervals
		FILETIME dueTime;
		LARGE_INTEGER liDueTime;
		liDueTime.QuadPart = -static_cast<LONGLONG>(intervalMs) * 10000;
		dueTime.dwLowDateTime = liDueTime.LowPart;
		dueTime.dwHighDateTime = liDueTime.HighPart;
		SetThreadpoolTimer(m_timer, &dueTime, intervalMs, 0);
	}

	void ThreadPool::StopTimer()
	{
		if (m_pool != nullptr && m_timer != nullptr)
		{
			SetThreadpoolTimer(m_timer, nullptr, 0, 0);
		}
	}
}

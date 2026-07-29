#pragma once
#include <string>
#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <sstream>
#include <source_location>
#include <vector>
#include <atomic>

namespace AsyncLoggerSamples
{
	class AsyncLoggerBasic
	{
	private:
		AsyncLoggerBasic();
		~AsyncLoggerBasic();

		void process();
		std::queue<std::string> m_queue;
		std::mutex m_mtx;
		std::condition_variable m_cv;
		std::thread m_thread;
		std::atomic<bool> m_running{ false };

	public:
		static AsyncLoggerBasic& Instance();

		void Log(const std::string& message,
			const std::source_location location = std::source_location::current());

		void Start();
		void Stop();
	};

	// ------------------------------------------------------------
	class AsyncLogger
	{
	public:
		AsyncLogger();
		~AsyncLogger();
		void log(const std::string& message,
			const std::source_location& location = std::source_location::current());
		std::vector<std::string> drain();
	private:
		void worker();
		std::queue<std::string> m_queue;
		std::vector<std::string> m_logs;
		std::mutex m_mtx;
		std::condition_variable m_cv;
		std::thread m_thread;
		std::atomic<bool> m_stopRequested{ false };
	};
}

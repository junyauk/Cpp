#include "pch.h"
#include "AsyncLogger.h"

namespace AsyncLoggerSamples
{
	// ------------------------------------------------------------
	AsyncLoggerBasic::AsyncLoggerBasic(){}
	AsyncLoggerBasic::~AsyncLoggerBasic(){Stop();}

	void AsyncLoggerBasic::process()
	{
		while (m_running)
		{
			std::unique_lock lock(m_mtx);
			m_cv.wait(lock, [this]() { return !m_queue.empty() || !m_running; });
			while (!m_queue.empty())
			{
				auto message = m_queue.front();
				m_queue.pop();

				lock.unlock();
				std::cout << message << std::endl;
				lock.lock();
			}
		}
	}

	AsyncLoggerBasic& AsyncLoggerBasic::Instance()
	{
		static AsyncLoggerBasic instance;
		return instance;
	}

	void AsyncLoggerBasic::Log(const std::string& message,
		const std::source_location location)
	{
		std::ostringstream oss;
		oss << location.file_name()
			<< ":" << location.line()
			<< "[" << location.function_name()
			<< "] " << message;
		{
			std::lock_guard lock(m_mtx);
			m_queue.push(oss.str());
		}
		m_cv.notify_one();
	}

	void AsyncLoggerBasic::Start()
	{
		m_running = true;
		m_thread = std::thread(&AsyncLoggerBasic::process, this);
	}
	void AsyncLoggerBasic::Stop()
	{
		m_running = false;
		m_cv.notify_all();
		if (m_thread.joinable())
			m_thread.join();
	}

	// ------------------------------------------------------------
	AsyncLogger::AsyncLogger()
	{
		m_thread = std::thread(&AsyncLogger::worker, this);
	}
	AsyncLogger::~AsyncLogger()
	{
		m_stopRequested = true;
		m_cv.notify_all();
		if (m_thread.joinable())
		{
			m_thread.join();
		}
	}
	void AsyncLogger::log(const std::string& message,
		const std::source_location& location)
	{
		std::ostringstream oss;
		oss << location.file_name()
			<< ":" << location.line()
			<< "[" << location.function_name()
			<< "] " << message;
		{
			std::lock_guard lock(m_mtx);
			m_queue.push(oss.str());
		}
		m_cv.notify_one();
	}
	std::vector<std::string> AsyncLogger::drain()
	{
		std::lock_guard lock(m_mtx);
		return m_logs;
	}
	void AsyncLogger::worker()
	{
		while(!m_stopRequested)
		{
			std::unique_lock lock(m_mtx);
			m_cv.wait(lock, [this]() { return !m_queue.empty() || m_stopRequested; });
			while (!m_queue.empty())
			{
				auto message = m_queue.front();
				m_queue.pop();
				lock.unlock();
				std::cout << message << std::endl;
				m_logs.push_back(std::move(message));
				lock.lock();
			}
		}
	}
}

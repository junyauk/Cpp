#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <iostream>
#include <sstream>
#include <filesystem>
#include "simple_logger.h"

namespace SimpleLogger
{
	// ---------------------------------------------------------------------------
	// SimpleLogger class
	void SimpleLogger::stop()
	{
		m_thread.request_stop();
		m_cv.notify_one();	// Let m_cv.wait() know the conditions were changed

		if (m_thread.joinable())
		{
			m_thread.join();	// Make sure finishing the thread.
		}
	}

	void SimpleLogger::run(std::stop_token st)
	{
		std::unique_lock<std::mutex> lock(m_mutex);

		while (true)
		{
			m_cv.wait(lock, [&] {return !m_queue.empty() || st.stop_requested(); });
			if (st.stop_requested() && m_queue.empty())
			{
				break;
			}

			std::string msg = std::move(m_queue.front());
			m_queue.pop();
			lock.unlock();

			std::cout << msg << std::endl;

			lock.lock();
		}
	}

	SimpleLogger::SimpleLogger()
	{
		m_thread = std::jthread([this](std::stop_token st) {run(st);});
	}
	SimpleLogger::~SimpleLogger()
	{
		stop();
	}
	void SimpleLogger::push(const std::string msg)
	{
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			m_queue.push(msg);
		}
		m_cv.notify_one();
	}

	// ---------------------------------------------------------------------------
	// SimpleLoggerSingleton class
	SimpleLogger& SimpleLoggerSingleton::instance()
	{
		static SimpleLogger logger;
		return logger;
	}

	// ---------------------------------------------------------------------------
	// LogMessage class
	LogMessage::LogMessage(LogLevel level, const char* file, int line)
		: m_level(level)
		, m_file(std::filesystem::path(file).filename().string())
		, m_line(line) {}
	LogMessage::~LogMessage()
	{
		SimpleLoggerSingleton::instance().push(formatMessage());
	}

	std::string LogMessage::formatMessage() const
	{
		std::ostringstream oss;

		switch (m_level)
		{
		case LogLevel::INFO: oss << "[INF "; break;
		case LogLevel::WARNING: oss << "[WRN "; break;
		case LogLevel::ERROR: oss << "[ERR "; break;
		}

		oss << "TID:" << std::this_thread::get_id();
//		oss  << ", (" << m_file << ":" << m_line << ")";
		oss << "] ";
		oss << m_stream.str();
		return oss.str();
	}
}

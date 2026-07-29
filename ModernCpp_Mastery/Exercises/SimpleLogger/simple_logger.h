#pragma once
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <sstream>
#include <iostream>


namespace SimpleLogger
{
	enum class LogLevel
	{
		INFO,
		WARNING,
		ERROR
	};

	class SimpleLogger
	{
	private:
		std::mutex m_mutex;
		std::condition_variable m_cv;
		std::queue<std::string> m_queue;
		std::jthread m_thread;
		void stop();
		void run(std::stop_token st);

	public:
		SimpleLogger();
		~SimpleLogger();
		void push(const std::string msg);
	};

	class SimpleLoggerSingleton
	{
	public:
		static SimpleLogger& instance();
	};

	class LogMessage
	{
	private:
		LogLevel m_level;
		std::string m_file;
		int m_line;
		std::ostringstream m_stream;
		std::string formatMessage() const;

	public:
		LogMessage(LogLevel level, const char* file, int line);
		~LogMessage();

		template<class T>
		LogMessage& operator<<(const T& value)
		{
			m_stream << value;
			return *this;
		}
	};

#define LOG(level) LogMessage(LogLevel::level, __FILE__, __LINE__)
}

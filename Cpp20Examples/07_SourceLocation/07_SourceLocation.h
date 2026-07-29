#pragma once
#include <source_location>
#include <iostream>
#include <string>
#include <sstream>
#include <mutex>
#include <vector>

namespace SourceLocationSamples
{
	static void logMessage(const std::string& message,
		const std::source_location location = std::source_location::current())
	{
		std::cout << "[log] Message: " << message << "\n"
			<< "  file: " << location.file_name() << "\n"
			<< "  function: " << location.function_name() << "\n"
			<< "  line: " << location.line() << ", column: " << location.column() << "\n";
	}

	enum class LogLevel
	{
		Info, 
		Warning, 
		Error
	};

	class Logger
	{
	private:
		Logger() = default;

		mutable std::mutex logMutex;
		std::vector<std::string> logs;
	public:
		static std::string to_string(LogLevel level)
		{
			switch (level)
			{
			case LogLevel::Info: return "INFO";
			case LogLevel::Warning: return "WARNING";
			case LogLevel::Error: return "ERROR";
			default: return "UNKNOWN";
			}
		}
		static Logger& instance()
		{
			static Logger instance;
			return instance;
		}

		void log(LogLevel level,
			const std::string& message,
			const std::source_location location = std::source_location::current());
		const std::vector<std::string>& getLogs() const { return logs; }
		void clear();
	};


	// Multi-threaded test logger
	class SimpleLogger
	{
	public:
		void log(const std::string& message,
			const std::source_location& location = std::source_location::current());
	protected:
		std::mutex mtx;
	};

	class MTLogger
	{
	public:
		explicit MTLogger(std::ostream& out = std::cout)
			: m_out(out) {}
		void log(const std::string& message,
			const std::source_location& location = std::source_location::current())
		{
			std::lock_guard lock(m_mtx);
			m_out << location.file_name()
				<< "[" << location.file_name() << ":" << location.line() << "] "
				<< message << std::endl;
		}
	private:
		std::ostream& m_out;
		std::mutex m_mtx;
	};
}



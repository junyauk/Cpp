#include "pch.h"
#include "framework.h"

#include "07_SourceLocation.h"

namespace SourceLocationSamples
{
	void Logger::log(LogLevel level,
		const std::string& message,
		const std::source_location location)
	{
		std::stringstream ss;
		ss << "[" << to_string(level) << "] "
			<< location.file_name() << ":"
			<< location.line() << " ("
			<< location.function_name() << ") - "
			<< message;

		std::lock_guard lock(logMutex);
		logs.push_back(ss.str());
		std::cout << ss.str() << std::endl;
	}
	void Logger::clear()
	{
		std::lock_guard lock(logMutex);
		logs.clear();
	}

	void SimpleLogger::log(const std::string& message,
		const std::source_location& location)
	{
		std::scoped_lock lock(mtx);
		std::cout 
			<< location.file_name() 
			<< "(" << location.line() << ") "
			<< location.function_name() << ": "
			<< message << std::endl;
	}


}

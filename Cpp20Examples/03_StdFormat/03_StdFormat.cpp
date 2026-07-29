#include "pch.h"
#include "framework.h"
#include "03_StdFormat.h"
#include <numbers>
#include <format>

namespace SampleFormat
{
	std::string formatGreeting(const std::string& name)
	{
		return std::format("Hello, {}!", name);
	}
	std::string formatScore(const std::string& name, int score)
	{
		return std::format("{} scored {} points", name, score);
	}
	std::string formatPI(int precision)
	{
		return std::format("Pi = {:.{}f}", std::numbers::pi, precision);
	}
	std::string formatDateTime(std::chrono::sys_seconds tp)
	{
		return std::format("{:%F %T}", tp);
	}

	std::string formatDateYMD(std::chrono::sys_days date)
	{
		return std::format("{:%Y/%m/%d}", date);
	}

	std::string formatDateDMY(std::chrono::sys_days date)
	{
		return std::format("{:%d/%m/%Y}", date);
	}

	std::string formatTimeHMS(std::chrono::sys_seconds tp)
	{
		return std::format("{:%H:%M:%S}", tp);
	}

	std::string formatDateTimeISO(std::chrono::sys_seconds tp)
	{
		return std::format("{:%Y-%m-%d %H:%M:%S}", tp);
	}

	std::string formatDateWithWeekday(std::chrono::sys_days date)
	{
		return std::format("{:%Y-%m-%d %a}", date);
	}

	std::string formatDateTimeLong(std::chrono::sys_seconds tp)
	{
		return std::format("{:%A, %B %d, %Y %H:%M:%S}", tp);
	}

	std::string formatExam01()
	{
		// "   0XFF   "
		// Padding with spaces (default)
		// Centering (^)
		// 10 characters (10)
		// Prefix of 0X (#X)
		return std::format("{:^#10X}", 255);
	}

	std::string formatExam02()
	{
		// "**3.1416***"
		// Padding with * (*)
		// Centering (^)
		// 12 characters (12)
		// 4 columns under . (.4f)
		double pi = std::numbers::pi;
		return std::format("{:*^12.4f}", pi);
	}

	std::string formatExam03()
	{
		// "2025/08/13 14:05"
		std::chrono::sys_days date = std::chrono::year{ 2025 } / 8 / 13;
		auto tp = date + std::chrono::hours{ 14 } + std::chrono::minutes{ 5 };
		return std::format("{:%Y/%m/%d %H:%M}", tp);
	}

	std::string formatExam04()
	{
		// 10 characters (10)
		// Right shift (>)
		// Padding with '_' (_)
		// Prefix (#b)
		// value 42
		return std::format("{:_>#12b}", 42);
	}

}

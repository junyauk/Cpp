#pragma once
#pragma once

#include <string>
#include <chrono>

namespace SampleFormat
{
	std::string formatGreeting(const std::string& name);
	std::string formatScore(const std::string& name, int score);
	std::string formatPI(int precision);
	std::string formatDateTime(std::chrono::sys_seconds tp);
	std::string formatDateYMD(std::chrono::sys_days date);
	std::string formatDateDMY(std::chrono::sys_days date);
	std::string formatTimeHMS(std::chrono::sys_seconds tp);
	std::string formatDateTimeISO(std::chrono::sys_seconds tp);
	std::string formatDateWithWeekday(std::chrono::sys_days date);
	std::string formatDateTimeLong(std::chrono::sys_seconds tp);


	std::string formatExam01();
	std::string formatExam02();
	std::string formatExam03();
	std::string formatExam04();
}
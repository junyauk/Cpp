#include "pch.h"
#include "gtest/gtest.h"
#include "..\03_StdFormat\03_StdFormat.h"
#include <chrono>
#include <regex>

using namespace SampleFormat;

TEST(StdFormatTest, FormatGreeting)
{
	EXPECT_EQ(formatGreeting("Alice"), "Hello, Alice!");
}

TEST(StdFormatTest, FormatScore)
{
	EXPECT_EQ(formatScore("Bob", 42), "Bob scored 42 points");
}

TEST(StdFormatTest, FormatPi)
{
	EXPECT_EQ(formatPI(2), "Pi = 3.14");
	EXPECT_EQ(formatPI(4), "Pi = 3.1416");
}

TEST(StdFormatTest, FormatDateTime)
{
	std::chrono::sys_days day_point = std::chrono::year{ 2023 } / 5 / 15;
	auto tp = day_point + std::chrono::hours{ 12 } + std::chrono::minutes{ 34 } + std::chrono::seconds{ 56 };
	std::string result = formatDateTime(tp);
	EXPECT_EQ(result, "2023-05-15 12:34:56");
}

TEST(StdFormatTest, FormatDateTimePattern)
{
    std::chrono::sys_seconds sysSeconds = std::chrono::floor<std::chrono::seconds>(std::chrono::system_clock::now());
	
	auto output = formatDateTime(sysSeconds);

	std::regex pattern(R"(^\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2}$)");

	EXPECT_TRUE(std::regex_match(output, pattern));
}

TEST(StdFormatTest, FormatDateYMD)
{
	std::chrono::sys_days date = std::chrono::year{ 2023 } / 5 / 15;
	EXPECT_EQ(formatDateYMD(date), "2023/05/15");
}

TEST(StdFormatTest, FormatDateDMY)
{
	std::chrono::sys_days date = std::chrono::year{ 2023 } / 5 / 15;
	EXPECT_EQ(formatDateDMY(date), "15/05/2023");
}

TEST(StdFormatTest, FormatTimeHMS)
{
	std::chrono::sys_days date = std::chrono::year{ 2023 } / 5 / 15;
	auto tp = date
		    + std::chrono::hours{12}
		+ std::chrono::minutes{ 34 }
	+ std::chrono::seconds{ 56 };
	EXPECT_EQ(formatTimeHMS(tp), "12:34:56");

}

TEST(StdFormatTest, FormatDateTimeISO)
{
	std::chrono::sys_days date = std::chrono::year{ 2023 } / 5 / 15;
	auto tp = date + std::chrono::hours{ 12 } + std::chrono::minutes{ 34 } + std::chrono::seconds{ 56 };
	EXPECT_EQ(formatDateTimeISO(tp), "2023-05-15 12:34:56");
}

TEST(StdFormatTest, FormatDateWithWeekday)
{
	std::chrono::sys_days date = std::chrono::year{ 2023 } / 5 / 15;
	EXPECT_EQ(formatDateWithWeekday(date), "2023-05-15 Mon");
}

TEST(StdFormatTest, FormatDateTimeLong)
{
	std::chrono::sys_days date = std::chrono::year{ 2023 } / 5 / 15;
	auto tp = date
		+ std::chrono::hours{ 12 }
		+ std::chrono::minutes{ 34 }
	+ std::chrono::seconds{ 56 };
	EXPECT_EQ(formatDateTimeLong(tp), "Monday, May 15, 2023 12:34:56");
}

TEST(StdFormatTest, FormatExams)
{
	EXPECT_EQ(formatExam01(), "   0XFF   ");
	EXPECT_EQ(formatExam02(), "***3.1416***");
	EXPECT_EQ(formatExam03(), "2025/08/13 14:05");
	EXPECT_EQ(formatExam04(), "____0b101010");
}

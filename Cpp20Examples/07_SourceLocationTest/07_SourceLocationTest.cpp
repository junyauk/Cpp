#include "pch.h"
#include "gtest/gtest.h"
#include "..\07_SourceLocation\07_SourceLocation.h"

using namespace SourceLocationSamples;


TEST(SourceLocationSampleTest, LogMessageContainsMessage)
{
	testing::internal::CaptureStdout();
    SourceLocationSamples::logMessage("HelloTest");
	std::string result = testing::internal::GetCapturedStdout();
    EXPECT_NE(result.find("HelloTest"), std::string::npos);
}

TEST(SourceLocationSampleTest, LogMessageContainsFunctionName)
{
    testing::internal::CaptureStdout();
    SourceLocationSamples::logMessage("CheckFunction");
    std::string result = testing::internal::GetCapturedStdout();
    EXPECT_NE(result.find("LogMessageContainsFunctionName"), std::string::npos);
}

TEST(SourceLocationSampleTest, LogMessageContainsFileName)
{
    testing::internal::CaptureStdout();
    SourceLocationSamples::logMessage("CheckFile");
    std::string result = testing::internal::GetCapturedStdout();
    EXPECT_NE(result.find("07_SourceLocationTest.cpp"), std::string::npos);
}

TEST(LoggerTest, LogsContainMessageAndLocation)
{
    Logger::instance().clear();
    Logger::instance().log(LogLevel::Info, "Hello Log");

    auto logs = Logger::instance().getLogs();
    ASSERT_EQ(logs.size(), 1);

    EXPECT_NE(logs[0].find("Hello Log"), std::string::npos);

    EXPECT_NE(logs[0].find("INFO"), std::string::npos);

    EXPECT_NE(logs[0].find("LogsContainMessageAndLocation"), std::string::npos);
}

TEST(LoggerTest, MultipleLogsAreStored)
{
    Logger::instance().clear();
    Logger::instance().log(LogLevel::Warning, "First");
    Logger::instance().log(LogLevel::Error, "Second");

    auto logs = Logger::instance().getLogs();
    ASSERT_EQ(logs.size(), 2);

    EXPECT_NE(logs[0].find("First"), std::string::npos);
    EXPECT_NE(logs[1].find("Second"), std::string::npos);
}

class TestLogger : public SimpleLogger
{
public:
    std::ostringstream oss;
    void log(const std::string& message,
        const std::source_location& location = std::source_location::current())
    {
        std::scoped_lock lock(mtx);
        oss << location.file_name()
            << "(" << location.line() << ") "
            << location.function_name() << ": "
            << message << std::endl;
	}
    std::string str()
    {
        std::scoped_lock lock(mtx);
		return oss.str();
    }
private:
	using SimpleLogger::mtx;
};

TEST(LoggerTest, MultiThreaded)
{
    TestLogger logger;
    constexpr int N = 10;
    std::vector<std::thread> threads;

    for (int i = 0; i < N; ++i) {
        threads.emplace_back([&logger, i]() {
            logger.log("Message " + std::to_string(i));
            });
    }

    for (auto& t : threads) t.join();

    auto output = logger.str();

    for (int i = 0; i < N; ++i) {
        EXPECT_NE(output.find("Message " + std::to_string(i)), std::string::npos);
    }
}


TEST(LoggerTest, MultiThreadedLogging)
{
	std::ostringstream oss;
	MTLogger logger(oss);

    auto worker = [&](int id) {
        for (int i = 0; i < 3; ++i)
        {
            logger.log("Worker " + std::to_string(id) + " message " + std::to_string(i));
        }
	};

	std::vector<std::jthread> threads;
    for (int i = 0; i < 4; ++i)
    {
        threads.emplace_back(worker, i);
	}

	std::this_thread::sleep_for(std::chrono::seconds(5));

	std::string output = oss.str();

    for (int id = 0; id < 4; ++id)
    {
        for (int i = 0; i < 3; ++i)
        {
			std::string expected = "Worker " + std::to_string(id) + " message " + std::to_string(i);
            EXPECT_NE(output.find(expected), std::string::npos);
        }
	}
}
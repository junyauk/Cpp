#include "pch.h"
#include "..\07_SourceLocation\AsyncLogger.h"
#include <gtest/gtest.h>
#include <thread>
#include <vector>
#include <sstream>
#include <mutex>

using namespace AsyncLoggerSamples;

TEST(AsyncLoggerTest, MultiThreadedLogging)
{
    AsyncLoggerBasic& logger = AsyncLoggerBasic::Instance();
    logger.Start();

    constexpr int threadCount = 5;
    constexpr int messagesPerThread = 50;

    // 複数スレッドからログを出す
    std::vector<std::thread> threads;
    for (int t = 0; t < threadCount; ++t) {
        threads.emplace_back([t, &logger]() {
            for (int i = 0; i < messagesPerThread; ++i) {
                std::ostringstream oss;
                oss << "Thread " << t << " message " << i;
                logger.Log(oss.str());
            }
            });
    }

    for (auto& th : threads) th.join();

    // ここで Stop() → 全ログが処理されるまで待機
    logger.Stop();

    SUCCEED() << "All logs processed without crash.";
}

TEST(AsyncLoggerTest, SingleThreadAsyncLogging)
{
    AsyncLogger logger;
    logger.log("Hello World");

    auto logs = logger.drain();
    ASSERT_EQ(logs.size(), 1);
    EXPECT_NE(logs[0].find("Hello World"), std::string::npos);
}

TEST(AsyncLoggerTest, MultiThreadAsyncLogging)
{
    AsyncLogger logger;
    constexpr int threadCount = 5;
    constexpr int messagesPerThread = 10;

    std::vector<std::thread> threads;
    for (int t = 0; t < threadCount; ++t)
    {
        threads.emplace_back([&logger, t]()
            {
                for (int i = 0; i < messagesPerThread; ++i)
                {
                    logger.log("Message from thread " + std::to_string(t) +
                        " #" + std::to_string(i));
                }
            });
    }

    for (auto& th : threads)
    {
        th.join();
    }

    std::this_thread::sleep_for(std::chrono::seconds(5));
    auto logs = logger.drain();

    ASSERT_EQ(logs.size(), threadCount * messagesPerThread);
    for (auto& msg : logs)
    {
        EXPECT_NE(msg.find("Message"), std::string::npos);
    }
}

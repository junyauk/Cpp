#include "pch.h"
#include "..\06_JthreadStopToken\06_JthreadStopToken.h"
#include <future>
#include <numeric>

using namespace JThreadStopTokenSamples;

TEST(JThreadStopTokenTests, JThreadSampleBasic)
{
    {
        testing::internal::CaptureStdout();
        std::cout << "Starting worker in scope..." << std::endl;
        Worker w;
        std::this_thread::sleep_for(std::chrono::seconds(2));

        std::cout << "Stopping worker explicitly..." << std::endl;
        w.stop();

        std::cout << "Worker should be stopped now." << std::endl;
        auto result = testing::internal::GetCapturedStdout();
        EXPECT_NE(result.find("Worker stopped."), std::string::npos);
    }

    {
        testing::internal::CaptureStdout();
        {
            std::cout << "Starting worker in scope..." << std::endl;
            Worker w;
            std::this_thread::sleep_for(std::chrono::seconds(2));
            std::cout << "Worker should be stopped now." << std::endl;
        }
        std::cout << "Worker will also stop automatically at scope end." << std::endl;
        auto result = testing::internal::GetCapturedStdout();
        EXPECT_NE(result.find("Worker stopped."), std::string::npos);
    }
}

TEST(JThreadStopTokenTests, JThreadSampleBasic2)
{
    {
        testing::internal::CaptureStdout();
        { // Explicitly stop
            Worker2 w1("A");
            std::this_thread::sleep_for(std::chrono::seconds(2));

            std::cout << "Stopping worker2 explicitly...\n";
            w1.stop();
        }
        auto result = testing::internal::GetCapturedStdout();
        EXPECT_NE(result.find("Worker2: A stopped."), std::string::npos);
    }

    {
        testing::internal::CaptureStdout();
        { // Destroyed at destructor
            Worker2 w2("B");
            std::this_thread::sleep_for(std::chrono::seconds(2));
            std::cout << "Letting destructor handle stopping...\n";
        }
        auto result = testing::internal::GetCapturedStdout();
        EXPECT_NE(result.find("Worker2: B stopped."), std::string::npos);
    }

}

TEST(JThreadStopTokenTests, StartsAndStopsCorrectly)
{
    Worker3 w;

    w.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(350));
    EXPECT_TRUE(w.isRunning());
    EXPECT_GT(w.getCounter(), 0);

    w.stop();
    EXPECT_FALSE(w.isRunning());
}

TEST(JThreadStopTokenTests, MultipleWorkersStopTogether)
{
    std::stop_source ssrc;
	std::stop_token st = ssrc.get_token();

	std::vector<int> data1{ 1, 2, 3, 4, 5 };
	std::vector<int> data2{ 6, 7, 8, 9, 10 };
	Worker4 w1(st, data1);
	Worker4 w2(st, data2);

    w1.start();
	w2.start();

    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    ssrc.request_stop();

    w1.join();
    w2.join();
    EXPECT_LT(w1.result(), std::accumulate(data1.begin(), data1.end(), 0));
    EXPECT_LT(w2.result(), std::accumulate(data2.begin(), data2.end(), 0));
    SUCCEED();
}

TEST(JThreadStopTokenTests, MultipleWorkersStopTogether2)
{
    std::stop_source ssrc;
    std::stop_token st = ssrc.get_token();

    const int N = 3;
	std::vector<std::unique_ptr<Worker5>> workers;
    for(int i = 0; i < N; ++i)
    {
        workers.push_back(std::make_unique<Worker5>(st));
        workers.back()->start();
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(200));

    ssrc.request_stop();
    for (auto& w : workers)
    {
        w->join();
        EXPECT_FALSE(w->isRunning());
    }
	SUCCEED();
}

TEST(ThreadPoolTest, SingleTaskExecutes) {
    ThreadPool pool(2);
    std::atomic<int> counter = 0;

    pool.enqueue([&]() {
        counter++;
        });

    std::this_thread::sleep_for(std::chrono::seconds(3));

    EXPECT_EQ(counter.load(), 1);
}

TEST(ThreadPoolTest, MultipleTasksExecute) {
    ThreadPool pool(4);
    std::atomic<int> counter = 0;

    for (int i = 0; i < 10; ++i) {
        pool.enqueue([&]() {
            counter++;
            });
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    EXPECT_EQ(counter.load(), 10);
}

TEST(ThreadPoolTest, TasksRunInParallel) {
    ThreadPool pool(2);
    std::atomic<int> counter = 0;

    pool.enqueue([&]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        counter++;
        });
    pool.enqueue([&]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        counter++;
        });

    std::this_thread::sleep_for(std::chrono::seconds(5));

    EXPECT_EQ(counter.load(), 2);
}

TEST(ThreadPoolTest, DestructorStopsThreads) {
    std::atomic<int> counter = 0;

    {
        ThreadPool pool(2);
        for (int i = 0; i < 5; ++i) {
            pool.enqueue([&counter] {
                std::this_thread::sleep_for(std::chrono::milliseconds(20));
                counter++;
                });
        }
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
    EXPECT_GE(counter, 5);
}
TEST(JThreadStopTokenTests, DestructorStopsThread)
{
    testing::internal::CaptureStdout();
    {
        Worker3 w;

        w.start();
        std::this_thread::sleep_for(std::chrono::milliseconds(350));
    }
    auto result = testing::internal::GetCapturedStdout();
    EXPECT_NE(result.find("Thread is exiting."), std::string::npos);
    SUCCEED();
}

TEST(JThreadStopTokenTests, MultipleThreadsUsingThreadPool)
{
    ThreadPool pool(3);

    for (int i = 0; i < 10; ++i)
    {
        pool.enqueue([i]()
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                std::cout << "Task " << i << " executed.\n";
            });
    }

    std::this_thread::sleep_for(std::chrono::seconds(1));
    pool.stop();

    std::cout << "Pool stopped.\n";
    SUCCEED();
}


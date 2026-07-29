#include "pch.h"
#include "gtest/gtest.h"
#include "..\06_JthreadStopToken\ParallelSumWorker.h"
#include <random>
#include <numeric>
using namespace ParallelSumWorkerSamples;

TEST(ParallelSumWorkerTest, ComputesPartialSum)
{
    std::vector<int> data{ 1, 2, 3, 4, 5 };
    ParallelSumWorker worker(data);

    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    auto result = worker.latestResult();
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), 15);
}

TEST(ParallelSumWorkerTest, StopsGracefully)
{
    std::vector<int> data{ 10, 20, 30 };
    ParallelSumWorker worker(data);

    std::this_thread::sleep_for(std::chrono::milliseconds(150));
    worker.stop();

    worker.stop();

    SUCCEED();
}


TEST(ParallelSumWorkerTest, ParallelSumWorker2StopSourceStopToken)
{
    std::vector<int> data(1000);
	std::iota(data.begin(), data.end(), 1);

    std::stop_source ssrc;
	auto future = std::async(std::launch::async, [&]()
        {
			return parallel_sum(data, 4, ssrc);
        });

    std::this_thread::sleep_for(std::chrono::milliseconds(50));
	std::cout << "Requesting stop..." << std::endl;
    ssrc.request_stop();

    auto result = future.get();
    EXPECT_GT(result, 0);
	EXPECT_LT(result, 500000);
    std::cout << "Total result (may be partial due to stop): " << result << "\n";
}
#include "pch.h"
#include "..\09_CoroutinesBasics\AsyncTask.h"
#include <gtest/gtest.h>

using namespace CoroutineSamples;

TEST(CoroutineTest, AsyncTaskTest)
{
    {
        auto task = asyncFunction();
        task.start();
    }
    SUCCEED();
}

TEST(CoroutineTest, RandomAwaiterTest)
{
    testing::internal::CaptureStdout();
    std::cout << "RandomAwaiterTest started.\n";
    {
        auto task = randomCoroutine();
        while (!task.done())
        {
            std::cout << "Resuming...\n";
            task.resume();
        }
    }
    std::cout << "RandomAwaiterTest finished.\n";
    auto result = testing::internal::GetCapturedStdout();
    std::cout << result << std::endl;
}
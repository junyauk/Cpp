#include "pch.h"
#include "gtest/gtest.h"
#include "..\10_LambdaImprovements\DynamicPriorityTaskDispatcher_AutoShrink.h"

using namespace LambdaImprovements;

TEST(DynamicPriorityTaskDispatcher_AutoShrink, AdjustsThreadCountSafely)
{
    DynamicPriorityTaskDispatcher_AutoShrink dispatcher(2, 6);

    std::atomic<int> counter = 0;

    std::vector<std::future<void>> futures;
    for (int i = 0; i < 50; ++i)
    {
        futures.push_back(dispatcher.enqueue(i % 3, [&]()
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
                counter++;
            }));
    }

    for (auto& f : futures)
    {
        f.wait();
    }

    EXPECT_EQ(counter.load(), 50);
}

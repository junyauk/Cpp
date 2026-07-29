#include "pch.h"
#include "gtest/gtest.h"
#include "..\10_LambdaImprovements\DynamicPriorityTaskDispatcher_AutoShrink.h"
#include "..\10_lambdaImprovements\JobSystemExample.h"

using namespace LambdaImprovements;

TEST(JobSystemExampleTest, RunJobSystemExample)
{
	DynamicPriorityTaskDispatcher_AutoShrink dispatcher;

    std::vector<Job> jobs =
    {
        { JobType::AI, 800, "AI_Model_A" },
        { JobType::AI, 600, "AI_Model_B" },
        { JobType::IO, 400, "IO_LoadTexture" },
        { JobType::UI, 200, "UI_Refresh" },
        { JobType::AI, 700, "AI_Model_C" },
        { JobType::IO, 500, "IO_SaveResult" }
    };

    std::vector<std::future<double>> aiFutures;
    std::vector<std::future<void>> otherFutures;

    for (auto& j : jobs)
    {
        auto priority = getPriority(j);
        if (j.type == JobType::AI)
        {
            aiFutures.push_back(dispatcher.enqueue(priority, [j]()
                {
                    return processAIJob(j);
                }));
        }
        else
        {
            otherFutures.push_back(dispatcher.enqueue(priority, [j]()
                {
                    return processSimpleJob(j);
                }));
        }
    }

    std::this_thread::sleep_for(std::chrono::seconds(3));

    for (auto& f : otherFutures)
    {
        f.get();
    }

    double total = 0.0;
    for (auto& f : aiFutures)
    {
        total += f.get();
    }

    auto average = total / aiFutures.size();
    std::cout << "\n Average AI score = " << average << std::endl;

    SUCCEED();
}

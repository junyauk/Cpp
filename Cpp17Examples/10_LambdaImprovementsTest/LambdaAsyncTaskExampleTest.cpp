#include "pch.h"
#include "gtest/gtest.h"
#include "..\10_LambdaImprovements\LambdaAsyncTaskExample.h"

using namespace LambdaImprovements;

TEST(LambdaAsyncTaskExample, SingleTaskRunsSuccessfully)
{
    auto task = std::make_unique<Task>("One");
    auto future = LambdaAsyncTaskExample::dispatchTask(std::move(task));

    EXPECT_NO_THROW(future.get());
}

TEST(LambdaAsyncTaskExample, MultipleTasksRunConcurrently)
{
    std::vector<std::unique_ptr<Task>> tasks;
    tasks.push_back(std::make_unique<Task>("A"));
    tasks.push_back(std::make_unique<Task>("B"));
    tasks.push_back(std::make_unique<Task>("C"));

    auto futures = LambdaAsyncTaskExample::dispatchMultipleTasks(std::move(tasks));

    std::string name;
    EXPECT_NO_THROW(name = futures[0].get());
    EXPECT_EQ(name, "A");
    EXPECT_NO_THROW(name = futures[1].get());
    EXPECT_EQ(name, "B");
    EXPECT_NO_THROW(name = futures[2].get());
    EXPECT_EQ(name, "C");
}

TEST(LambdaAsyncTaskExample, CannotReuseMovedTask)
{
    auto task = std::make_unique<Task>("Once");
    auto future = LambdaAsyncTaskExample::dispatchTask(std::move(task));

    EXPECT_EQ(task, nullptr); // owner has been moved

    future.get(); // OK
}

#include "pch.h"
#include "..\09_CoroutinesBasics\SimpleTask.h"
#include <gtest/gtest.h>

using namespace CoroutineSamples;

TEST(CoroutineTest, SimpleTaskTest)
{
    auto task = simpleCoroutine();
    std::cout << "Resume after step 1..." << std::endl;
    task.handle.resume();
}


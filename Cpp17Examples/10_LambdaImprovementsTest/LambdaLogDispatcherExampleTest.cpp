#include "pch.h"
#include "gtest/gtest.h"
#include "..\10_LambdaImprovements\LambdaLogDispatcherExample.h"

using namespace LambdaImprovements;

TEST(LambdaLogDispatcherExample, LogsAreProcessedAsynchronously)
{
    LogDispatcher dispatcher;

    dispatcher.enqueueLog("Task started");
    dispatcher.enqueueLog("Processing data");
    dispatcher.enqueueLog("Task finished");

    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    dispatcher.stop();

    // should be safe calling stop twice
    dispatcher.stop();

    SUCCEED();
}

TEST(LambdaLogDispatcherExample, CanHandleMultipleThreadsEnqueueing)
{
    LogDispatcher dispatcher;

    std::thread t1([&] { dispatcher.enqueueLog("from thread 1"); });
    std::thread t2([&] { dispatcher.enqueueLog("from thread 2"); });
    std::thread t3([&] { dispatcher.enqueueLog("from thread 3"); });

    t1.join();
    t2.join();
    t3.join();

    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    dispatcher.stop();

    SUCCEED();
}

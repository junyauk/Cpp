#include "pch.h"
#include "gtest/gtest.h"
#include "..\10_LambdaImprovements\LambdaPerfectForwardingDispatcher.h"

using namespace LambdaImprovements;

class LambdaPerfectForwardingDispatcherTest : public testing::Test
{
protected:
	TaskDispatcher dispatcher;
};

TEST_F(LambdaPerfectForwardingDispatcherTest, DispatchSimpleLambda)
{
    auto fut = dispatcher.dispatch([](int a, int b)
        {
            return a + b;
        }, 3, 5);

    EXPECT_EQ(fut.get(), 8);
}

TEST_F(LambdaPerfectForwardingDispatcherTest, DispatchStringLambda)
{
    std::string base{ "Hello" };
    auto fut = dispatcher.dispatch([](std::string prefix, const std::string& suffix)
        {
            return prefix + " " + suffix;
        }, std::move(base), std::string("World"));

    EXPECT_EQ(fut.get(), "Hello World");
}

TEST_F(LambdaPerfectForwardingDispatcherTest, DispatchVoidLambda)
{
    bool called = false;
    auto fut = dispatcher.dispatch([&](int x)
        {
            called = (x == 42);
        }, 42);
    fut.get(); // it's void
    EXPECT_TRUE(called);
}

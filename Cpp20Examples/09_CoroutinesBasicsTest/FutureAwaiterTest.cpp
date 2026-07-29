#include "pch.h"
#include "..\09_CoroutinesBasics\FutureAwaiter.h"
#include <gtest/gtest.h>

using namespace FutureAwaiterSamples;

TEST(CoroutineTest, FutureAwaiterTest)
{
	testing::internal::CaptureStdout();
    {
        Task t = asyncFunction();
        t.start();
    }
	std::string output = testing::internal::GetCapturedStdout();
	std::cout << "---- Captured Output Start ----\n";
	std::cout << output;
}

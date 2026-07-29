#pragma once
#include <string>
#include <gtest/gtest.h>

template<typename Func>
std::string captureOutput(Func&& func)
{
    testing::internal::CaptureStdout();
    func();
    return testing::internal::GetCapturedStdout();
}

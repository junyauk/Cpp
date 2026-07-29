#include "pch.h"
#include "gtest/gtest.h"
#include "..\Caller\HelloCaller.h"
#include "..\Caller\CallerMathAPI.h"
#include "..\Caller\CallerStringAPI.h"

TEST(HelloCallerTests, CallHello_ShouldPrintMessage)
{
    testing::internal::CaptureStdout();
    CallHello();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find("Hello from MiniModules!"), std::string::npos);
}

TEST(CallerMathAPITest, Square) {
    EXPECT_DOUBLE_EQ(Caller::computeSquare(3.0), 9.0);
    EXPECT_DOUBLE_EQ(Caller::computeSquare(4.0), 16.0);
}

TEST(CallerMathAPITest, Hypotenuse) {
    EXPECT_DOUBLE_EQ(Caller::computeHypotenuse(3.0, 4.0), 5.0);
    EXPECT_DOUBLE_EQ(Caller::computeHypotenuse(5.0, 12.0), 13.0);
}

TEST(StringUtilsTest, ToUpper)
{
    EXPECT_EQ(caller_to_upper("Hello"), "HELLO");
}

TEST(StringUtilsTest, ToLower)
{
    EXPECT_EQ(caller_to_lower("World"), "world");
}

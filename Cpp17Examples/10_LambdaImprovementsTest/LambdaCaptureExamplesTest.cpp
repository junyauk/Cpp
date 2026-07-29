#include "pch.h"
#include "gtest/gtest.h"
#include "..\10_LambdaImprovements\LambdaCaptureExamples.h"

using namespace LambdaImprovements;

TEST(LambdaCaptureExamplesTest, CopyCapture)
{
    std::string result = LambdaCaptureExamples::copyCaptureExample();
    EXPECT_NE(result.find("42"), std::string::npos);
    EXPECT_EQ(result.find("100"), std::string::npos);
}

TEST(LambdaCaptureExamplesTest, ReferenceCapture)
{
    std::string result = LambdaCaptureExamples::referenceCaptureExample();
    EXPECT_NE(result.find("100"), std::string::npos);
}

TEST(LambdaCaptureExamplesTest, MoveCapture)
{
    std::string result = LambdaCaptureExamples::moveCaptureExample();
    EXPECT_NE(result.find("1 2 3"), std::string::npos);
    EXPECT_NE(result.find("Original size: 0"), std::string::npos);
}
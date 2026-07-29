#include "pch.h"
#include "gtest/gtest.h"
#include "..\10_LambdaImprovements\LambdaFunctionComparison.h"

using namespace LambdaImprovements;
TEST(LambdaFunctionComparisonTest, InspectClosure)
{
	EXPECT_EQ(LambdaFunctionComparison::inspectClosure(), "x=10(y by ref), result=35");
}

TEST(LambdaFunctionComparisonTest, UsingStdFunction)
{
    EXPECT_EQ(LambdaFunctionComparison::usingStdFunction(), 15);
}

TEST(LambdaFunctionComparisonTest, FunctionCopyBehavior)
{
    EXPECT_EQ(LambdaFunctionComparison::functionCopyBehavior(), 2);
}

TEST(LambdaFunctionComparisonTest, TypeDifference)
{
    auto s = LambdaFunctionComparison::typeDifference();
    EXPECT_NE(s.find("lambda type:"), std::string::npos);
    EXPECT_NE(s.find("std::function type:"), std::string::npos);
}

TEST(LambdaFunctionComparisonTest, FunctionCopyBehaviorDetailed) {
    auto s = LambdaFunctionComparison::functionCopyBehaviorDetailed();

    EXPECT_NE(s.find("after lambda creation"), std::string::npos);
    EXPECT_NE(s.find("after assigning to std::function"), std::string::npos);
    EXPECT_NE(s.find("result="), std::string::npos);

    LambdaFunctionComparison::Counter::copyCount = 0;
}

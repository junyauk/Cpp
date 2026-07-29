#include "pch.h"
#include <gtest/gtest.h>
#include "..\10_LambdaImprovements\LambdaImprovements.h"

using namespace LambdaImprovementsExamples;

TEST(LambdaImprovementsTest, BasicLambda)
{
	EXPECT_EQ(LambdaImprovements::basicLambda(2, 3), 5);
}

TEST(LambdaImprovementsTest, GenericLambda)
{
	EXPECT_EQ(LambdaImprovements::genericLambda(2, 3), 6);
}

TEST(LambdaImprovementsTest, InitCapture)
{
	EXPECT_EQ(LambdaImprovements::initCapture("Hello"), "Hello world");
}

TEST(LambdaImprovementsTest, ConstexprLambda)
{
	constexpr int result = LambdaImprovements::constexprLambda(5);
	EXPECT_EQ(result, 25);
}

TEST(LambdaImprovementsTest, CaptureThis)
{
	EXPECT_EQ(LambdaImprovements::captureThis(), 20);
}

TEST(LambdaImprovementsTest, RefQualifiedLambda)
{
	EXPECT_EQ(LambdaImprovements::refQualifiedLambda(), 25);
}


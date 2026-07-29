#include "pch.h"
#include "gtest/gtest.h"
#include "..\10_LambdaImprovements\LambdaVsBindExample.h"

using namespace LambdaImprovements;

TEST(LambdaVsBindExampleTest, Multiply_UsingBind)
{
	auto f = LambdaVsBindExample::createBindMultiplier(3);
	EXPECT_EQ(f(4), 12);
}

TEST(LambdaVsBindExampleTest, Multiply_usingLambda)
{
	auto f = LambdaVsBindExample::createLambdaMultiplier(5);
	EXPECT_EQ(f(2), 10);
}

TEST(LambdaVsBindExampleTest, StringAppender_UsingBind)
{
	auto f = LambdaVsBindExample::createBindStringAppender("Hello");
	EXPECT_EQ(f(), "Hello bound");
}

TEST(LambdaVsBindExampleTest, StringAppender_UsingLambda)
{
	auto f = LambdaVsBindExample::createLambdaStringAppender("Hello");
	EXPECT_EQ(f(), "Hello lambda");
}

TEST(LambdaVsBindExampleTest, CaptureBehavior_Difference)
{
	std::string text = "Hi";

	auto bindFunc = LambdaVsBindExample::createBindStringAppender(text);
	auto lambdaFunc = LambdaVsBindExample::createLambdaStringAppender(text);

	text = "changed";

	EXPECT_EQ(bindFunc(), "Hi bound");
	EXPECT_EQ(lambdaFunc(), "Hi lambda");
}

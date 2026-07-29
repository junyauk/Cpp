#include "pch.h"
#include "gtest/gtest.h"
#include "..\10_LambdaImprovements\LambdaGenericExample.h"

using namespace LambdaImprovements;

TEST(LambdaGenericExample, FixedLambdaWorks)
{
	auto result = LambdaGenericExample::fixedLambdaExample();
	EXPECT_NE(result.find("squareInt(5) = 25"), std::string::npos);
	EXPECT_NE(result.find("int (fixed)"), std::string::npos);
}

TEST(LambdaGenericExample, GenericLambdaWorks)
{
	auto result = LambdaGenericExample::genericLambdaExample();
	EXPECT_NE(result.find("square(4) = 16"), std::string::npos);
	EXPECT_NE(result.find("square(3.14) = 9.8596"), std::string::npos);
	EXPECT_NE(result.find("Return type for int: int"), std::string::npos);
	EXPECT_NE(result.find("Return type for double: double"), std::string::npos);
}

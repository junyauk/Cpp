#include "pch.h"
#include "gtest/gtest.h"
#include "..\10_LambdaImprovements\LambdaMoveUniquePtrExample.h"

using namespace LambdaImprovements;

// ----------------------------------------------------------------------------
// unique_ptr
class LambdaMoveUniquePtrExampleTest : public testing::Test
{
protected:
	void SetUp() override
	{
		// preparing 
	}

	void TearDown() override
	{
		// tidying up
	}
};

TEST_F(LambdaMoveUniquePtrExampleTest, MessageLambdaReturnsCorrectString)
{
    auto lambda = LambdaMoveUniquePtrExample::createMessageLambda("World");
    std::string result = lambda();
    EXPECT_EQ(result, "Hello, World!");
}

TEST_F(LambdaMoveUniquePtrExampleTest, IntProcessorDoublesValue)
{
    auto lambda = LambdaMoveUniquePtrExample::createIntProcessor(5);
    int result = lambda();
    EXPECT_EQ(result, 10);
}

TEST_F(LambdaMoveUniquePtrExampleTest, ExecuteMessageLambdaReturnsExpectedString)
{
    std::string result = LambdaMoveUniquePtrExample::executeMessageLambda();
    EXPECT_EQ(result, "Hello, Lambda!");
}

TEST_F(LambdaMoveUniquePtrExampleTest, ExecuteIntProcessorReturnsDoubledValue)
{
    int result = LambdaMoveUniquePtrExample::executeIntProcessor();
    EXPECT_EQ(result, 20);
}

// ----------------------------------------------------------------------------
// shared_ptr
class LambdaMoveSharedPtrExampleTest : public testing::Test
{
protected:
    void SetUp() override
    {

    }
    void TearDown() override
    {

    }
};

TEST_F(LambdaMoveSharedPtrExampleTest, MessageLambdaReturnsCorrectString)
{
    auto lambda = LambdaMoveSharedPtrExample::createMessageLambda("World");
    std::string result = lambda();
    EXPECT_EQ(result, "Hello, World!");
}

TEST_F(LambdaMoveSharedPtrExampleTest, IntProcessorDoublesValue)
{
    auto lambda = LambdaMoveSharedPtrExample::createIntProcessor(5);
    int result = lambda();
    EXPECT_EQ(result, 10);
}

TEST_F(LambdaMoveSharedPtrExampleTest, ExecuteMessageLambdaReturnsExpectedString)
{
    std::string result = LambdaMoveSharedPtrExample::executeMessageLambda();
    EXPECT_EQ(result, "Hello, Lambda!");
}

TEST_F(LambdaMoveSharedPtrExampleTest, ExecuteIntProcessorReturnsDoubledValue)
{
    int result = LambdaMoveSharedPtrExample::executeIntProcessor();
    EXPECT_EQ(result, 20);
}


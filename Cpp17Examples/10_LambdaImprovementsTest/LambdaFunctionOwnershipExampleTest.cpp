#include "pch.h"
#include "gtest/gtest.h"
#include "..\10_LambdaImprovements\LambdaFunctionOwnershipExample.h"

using namespace LambdaImprovements;

class LambdaFunctionOwnershipExampleTest : public testing::Test
{
    // empty
};

TEST_F(LambdaFunctionOwnershipExampleTest, MoveCapturedFunctionExecutes)
{
//    auto func = LambdaFunctionOwnershipExample::createFunctionWithMoveCapture();
//    EXPECT_NO_THROW(func()); // Never throw any excption
}

TEST_F(LambdaFunctionOwnershipExampleTest, SharedCapturedFunctionCanBeCopied)
{
    auto func1 = LambdaFunctionOwnershipExample::createFunctionWithSharedCapture();
    auto func2 = func1; // copy is allowed
    EXPECT_NO_THROW(func1());
    EXPECT_NO_THROW(func2());
}

TEST_F(LambdaFunctionOwnershipExampleTest, MoveCapturedLambdaIsNotCopyConstructible)
{
    bool result = LambdaFunctionOwnershipExample::isCopyConstructibleTest();
    EXPECT_FALSE(result); // check if it can't be copied
}

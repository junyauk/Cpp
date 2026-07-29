#include "pch.h"
#include "gtest/gtest.h"
#include "..\10_LambdaImprovements\LambdaMoveOwnershipExample.h"

using namespace LambdaImprovements;

class LambdaMoveOwnershipExampleTest : public testing::Test
{
protected:
	void SetUp() override {}
	void TearDown() override {}
};


TEST_F(LambdaMoveOwnershipExampleTest, ProcessWithAsync)
{
    auto result = LambdaMoveOwnershipExample::processWithAsync();
    EXPECT_EQ(result, "async_task_data_processed");
}

TEST_F(LambdaMoveOwnershipExampleTest, RunThreadPoolSimulation)
{
    EXPECT_NO_THROW(LambdaMoveOwnershipExample::runThreadPoolSimulation());
}

TEST_F(LambdaMoveOwnershipExampleTest, WriteToFileWithMove)
{
    EXPECT_TRUE(LambdaMoveOwnershipExample::writeToFileWithMove("test_output.txt"));
}

TEST_F(LambdaMoveOwnershipExampleTest, TransferOwnershipTwice)
{
    auto result = LambdaMoveOwnershipExample::transferOwnershipTwice();
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(*result, "first_owner_moved_twice");
}

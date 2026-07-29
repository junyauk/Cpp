#include "pch.h"
#include "gtest/gtest.h"
#include "..\10_LambdaImprovements\LambdaMoveThreadExample.h"

using namespace LambdaImprovements;

class LambdaMoveThreadExampleTest : public testing::Test
{
protected:
	void SetUp() override {}
	void TearDown() override {}
};

TEST_F(LambdaMoveThreadExampleTest, RunTaskWithMoveResource)
{
	EXPECT_NO_THROW(LambdaMoveThreadExample::runTaskWithMovedResource());
}

TEST_F(LambdaMoveThreadExampleTest, DistributeTasksRunsSafely)
{
	EXPECT_NO_THROW(LambdaMoveThreadExample::distributeTasks());
}

TEST_F(LambdaMoveThreadExampleTest, InvalidStdFunctionUsageCommentedOut)
{

	SUCCEED();
}
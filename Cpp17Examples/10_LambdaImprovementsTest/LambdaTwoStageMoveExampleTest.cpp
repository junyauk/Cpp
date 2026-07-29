#include "pch.h"
#include "gtest/gtest.h"
#include "..\10_LambdaImprovements\LambdaTwoStageMoveExample.h"

using namespace LambdaImprovements;

class LambdaTwoStageMoveExampleTest : public ::testing::Test
{
protected:
	void SetUp() override
	{

	}
	void TearDown() override
	{

	}
};

TEST_F(LambdaTwoStageMoveExampleTest, TwoStageMove)
{
	testing::internal::CaptureStdout();
	TwoStageMoveExample::run();
	std::string result = testing::internal::GetCapturedStdout();
}
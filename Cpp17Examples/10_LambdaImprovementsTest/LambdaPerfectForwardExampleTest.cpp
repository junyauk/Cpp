#include "pch.h"
#include "gtest/gtest.h"
#include "..\10_LambdaImprovements\LambdaPerfectForwardExample.h"

using namespace LambdaImprovements;

TEST(LambdaPerfectForwardExampleTest, Explanation)
{
	using namespace PerfectForwardingExplanation;
	std::string str = "Alice";

	// NG
	{
		testing::internal::CaptureStdout();
		Explanation::forwardToPrintNG(str);
		Explanation::forwardToPrintNG(std::string("Bob"));
		std::string result = testing::internal::GetCapturedStdout();
		EXPECT_EQ(result.find("rvalue reference (moved): Bob"), std::string::npos);
	}

	// Better but not enough
	{
		testing::internal::CaptureStdout();
		Explanation::forwardToPrintBetter(str);
		Explanation::forwardToPrintBetter(std::string("Bob"));
		std::string result = testing::internal::GetCapturedStdout();
		EXPECT_EQ(result.find("rvalue reference (moved): Bob"), std::string::npos);
	}

	// Perfect forwarding
	{
		testing::internal::CaptureStdout();
		Explanation::forwardToPrintOK(str);
		Explanation::forwardToPrintOK(std::string("Bob"));
		std::string result = testing::internal::GetCapturedStdout();
		EXPECT_NE(result.find("rvalue reference (moved): Bob"), std::string::npos);
	}

}

TEST(ForwardingMechanismTest, WithoutForward)
{
	using namespace PerfectForwardingExplanation;

	std::ostringstream os;

	int x = 10;
	analyzeForwarding(x, "x", os);
	EXPECT_EQ(os.str(), "x (lvalue)");

	os.str("");
	analyzeForwarding(20, "20", os);
	EXPECT_EQ(os.str(), "20 (rvalue)");
}

TEST(ForwardingMechanismTest, WithForward)
{
	using namespace PerfectForwardingExplanation;

	std::ostringstream os;

	int x = 10;

	analyzeStdForward(x, "x", os);
	EXPECT_EQ(os.str(), "x (lvalue)");

	os.str("");
	analyzeStdForward(20, "20", os);
	EXPECT_EQ(os.str(), "20 (rvalue)");
}


TEST(LambdaPerfectForwardExampleTest, CompareCopyAndPerfectForward)
{
	auto result = LambdaPerfectForwardExample::compareCopyAndPerfectForward();

	// check the output if both cases in it
	EXPECT_NE(result.find("CopyLambda"), std::string::npos);
	EXPECT_NE(result.find("ForwardLambda"), std::string::npos);

	// Perfect forward should use move
	EXPECT_NE(result.find("Moves: 1"), std::string::npos);
}

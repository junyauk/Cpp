#include "pch.h"
#include "gtest/gtest.h"
#include "..\10_LambdaImprovements\TrackableExample.h"

using namespace LambdaImprovements;

class TrackableExampleTest : public testing::Test
{
protected:
	void SetUp() override
	{
		Trackable::resetCounters();
	}
};

TEST_F(TrackableExampleTest, MakeTupleByCopy_ShouldInvokeCopyConstructor)
{
	Trackable t("apple");
	auto tuple = TrackableExample::makeTupleByCopy(t);
	EXPECT_EQ(Trackable::copyCount, 1);
	EXPECT_EQ(Trackable::moveCount, 0);
	EXPECT_EQ(std::get<0>(tuple).name, "apple");
}

TEST_F(TrackableExampleTest, MakeTupleByMove_ShouldInvokeMoveConstructor)
{
	Trackable t("banana");
	auto tuple = TrackableExample::makeTupleByMove(std::move(t));
	EXPECT_EQ(Trackable::copyCount, 0);
	EXPECT_EQ(Trackable::moveCount, 1);
	EXPECT_EQ(std::get<0>(tuple).name, "banana");
}
#include "pch.h"
#include "gtest/gtest.h"
#include "..\09_MapSet\UserManager.h"

using namespace MapSetExamples;

TEST(UserManagerTest, RegisterUser_Insert)
{
	UserManager um;

	EXPECT_TRUE(um.RegisterUser_Insert("Alice"));
	EXPECT_FALSE(um.RegisterUser_Insert("Alice"));
	EXPECT_EQ(um.Count(), 1);
}

TEST(UserManagerTest, RegisterUser_TryEmplace)
{
	UserManager um;

	EXPECT_TRUE(um.RegisterUser_TryEmplace("Alice"));
	EXPECT_FALSE(um.RegisterUser_TryEmplace("Alice"));
	EXPECT_EQ(um.Count(), 1);
}

TEST(UserManagerTest, RecordLogin)
{
	UserManager um;

	um.RecodeLogin("Charlie");
	auto c1 = um.GetLoginCount("Charlie");
	ASSERT_TRUE(c1.has_value());
	EXPECT_EQ(c1.value(), 1);

	um.RecodeLogin("Charlie");
	auto c2 = um.GetLoginCount("Charlie");
	ASSERT_TRUE(c2.has_value());
	EXPECT_EQ(c2.value(), 2);

	um.RecodeLogin("Dave");
	EXPECT_EQ(um.GetLoginCount("Dave"), 1);

	EXPECT_EQ(um.Count(), 2);
}
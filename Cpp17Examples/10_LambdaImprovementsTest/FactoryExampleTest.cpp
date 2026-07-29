#include "pch.h"
#include "gtest/gtest.h"
#include "..\10_LambdaImprovements\FactoryExample.h"

using namespace LambdaImprovements;

class FactoryExampleTest : public testing::Test {};

TEST_F(FactoryExampleTest, CreateSingleInstance)
{
	auto factory = makeFactory<Widget>("Test", 90);
	auto w = factory();

	ASSERT_NE(w, nullptr);
	EXPECT_EQ(w->name, "Test");
	EXPECT_EQ(w->value, 90);
}

TEST_F(FactoryExampleTest, CannotReuseAfterMove)
{
	auto factory = makeFactory<Widget>("Once", 1);
	auto first = factory();

	EXPECT_THROW(
		{
			auto second = factory();
			(void)second;
		}, std::exception);
}
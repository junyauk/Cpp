#include "pch.h"
#include "gtest/gtest.h"
#include "..\09_CoroutinesBasics\ValueReturningTask.h"

using namespace ValueReturningTaskSamples;

TEST(ValueReturningTaskSamples, SimpleValueTaskTest)
{
	runner();

	SUCCEED();
}
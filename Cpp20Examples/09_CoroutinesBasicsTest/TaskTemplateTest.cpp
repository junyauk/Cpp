#include "pch.h"
#include "gtest/gtest.h"
#include "..\09_CoroutinesBasics\TaskTemplate.h"

using namespace TaskTemplateExamples;

TEST(CoroutineTest, TaskTemplateExamples)
{
	run();
	SUCCEED();
}

TEST(CoroutineTest, TaskTemplateCoAwait)
{
	sample();
	SUCCEED();
}
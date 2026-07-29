#include "pch.h"
#include "gtest/gtest.h"
#include "..\10_LambdaImprovements\LambdaGenericForwardingExample.h"

using namespace LambdaImprovements;

// ----------------------------------------------------------------------------
class GenericLambdaExampleTest : public testing::Test{};
TEST_F(GenericLambdaExampleTest, HandleMultipleTypes)
{
	auto results = GenericLambdaExample::demonstrate();
	EXPECT_EQ(results.size(), 3);
	EXPECT_EQ(results[0], "42");
	EXPECT_EQ(results[1], "Hello");
	EXPECT_EQ(results[2], "3.14");
}

// ----------------------------------------------------------------------------
class ForwardingLambdaExampleTest : public testing::Test {};
TEST_F(ForwardingLambdaExampleTest, ForwardsLvalueAndRvalue)
{
	auto result = ForwardingLambdaExample::demonstrate();
	EXPECT_EQ(result, "HelloWorld");
}

// ----------------------------------------------------------------------------
class EventDispatcherTest : public testing::Test {};
TEST_F(EventDispatcherTest, CallsAllHandlers)
{
	EventDispatcher dispatcher;
	std::string output;

	dispatcher.addHandler([&output]() { output += "A"; });
	dispatcher.addHandler([&output](int v) { output += std::to_string(v); }, 2);
	dispatcher.addHandler([&output](const std::string& s) {output += s; }, "B");

	dispatcher.dispatchAll();

	EXPECT_EQ(output, "A2B");
}


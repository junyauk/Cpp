#include "pch.h"
#include "gtest/gtest.h"
#include <vector>
#include <functional>
#include "..\04_Variant\OverloadTechnique.h"


using namespace OverloadTechniqueExamples;

// 1. Define test data
struct TestData
{
	std::string name;
	InputType input;
	std::function<std::string(const InputType&)> func;
	// Note:
	// Using std::string_view, instead of std::string
	std::string_view expeted;
};

// 2. Define a test class inheriting TestWithParam<TestData>
class OverloadTechniqueTest : public ::testing::TestWithParam<TestData>
{
	/* if necessary...
	public:
		void SetUp() override{}
		void TearDown() override{}
	*/
};

// 3. Write a test func using TEST_P macro for one case
TEST_P(OverloadTechniqueTest, ExecuteFunctionAndCheckResults)
{
	// Get a set of test case
	const TestData& data = GetParam();

	// Run the specified function
	std::string result = data.func(data.input);

	// Check the result
	EXPECT_NE(std::string::npos, result.find(data.expeted));
}
#if 1
// Note:
//   They can be like this...
//        const static std::string VALUE_IS_INT = "Value is int";
//   But "constexpr static std::string_view..." is better.
constexpr static std::string_view VALUE_IS_INT = "Value is int";
constexpr static std::string_view VALUE_IS_DOUBLE = "Value is double";
constexpr static std::string_view VALUE_IS_STRING = "Value is std::string";
#else
const static std::string VALUE_IS_INT = "Value is int";
const static std::string VALUE_IS_DOUBLE = "Value is double";
const static std::string VALUE_IS_STRING = "Value is std::string";
#endif

// 4. Define TestData matrix
std::vector<TestData> function_test_data
{
	// Note:
	// The test name sould be consist of alphabet and '_' only that the test explorer can treat the name.
	{"UsingIndexAndGet_int", 42, UsingIndexAndGet, VALUE_IS_INT},
	{"UsingIndexAndGet_double", 3.14, UsingIndexAndGet, VALUE_IS_DOUBLE},
	{"UsingIndexAndGet_string", "Hello", UsingIndexAndGet, VALUE_IS_STRING},

	{"UsingGetIf_int", 42, UsingGetIf, VALUE_IS_INT},
	{"UsingGetIf_double", 3.14, UsingGetIf, VALUE_IS_DOUBLE},
	{"UsingGetIf_string", "Hello", UsingGetIf, VALUE_IS_STRING},

	{"UsingHoldsAlternative_int", 42, UsingHoldsAlternative, VALUE_IS_INT},
	{"UsingHoldsAlternative_double", 3.14, UsingHoldsAlternative, VALUE_IS_DOUBLE},
	{"UsingHoldsAlternative_string", "Hello", UsingHoldsAlternative, VALUE_IS_STRING},

	{"UsingVisitWithSingleLambdaAndConstexpr_int", 42, UsingVisitWithSingleLambdaAndConstexpr, VALUE_IS_INT},
	{"UsingVisitWithSingleLambdaAndConstexpr_double", 3.14, UsingVisitWithSingleLambdaAndConstexpr, VALUE_IS_DOUBLE},
	{"UsingVisitWithSingleLambdaAndConstexpr_string", "Hello", UsingVisitWithSingleLambdaAndConstexpr, VALUE_IS_STRING},

	{"UsingVisitWithFunctor_int", 42, UsingVisitWithFunctor, VALUE_IS_INT},
	{"UsingVisitWithFunctor_double", 3.14, UsingVisitWithFunctor, VALUE_IS_DOUBLE},
	{"UsingVisitWithFunctor_string", "Hello", UsingVisitWithFunctor, VALUE_IS_STRING}
};


// 5. Define INSTANTIATE_TEST_CASE_P
// 
// Note:
// The installed GoogleTest 1.8.1.7 supports "INSTANTIATE_TEST_CASE_P", NOT "INSTANTIATE_TEST_SUITE_P"
INSTANTIATE_TEST_CASE_P(
	04_Variant,				// This name is used for the Test Explorer
	OverloadTechniqueTest,	// Specify the test class inheriting testing::TestWithParam class
	::testing::ValuesIn(function_test_data),	// Specify test data matrix
	[](const testing::TestParamInfo<TestData>& info)
	{
		return info.param.name; // This name will be used by the Test Explorer
	}
);


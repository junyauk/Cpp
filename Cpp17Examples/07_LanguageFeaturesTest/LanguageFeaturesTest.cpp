#include "pch.h"
#include "..\07_LanguageFeatures\01_Nodiscard.h"
#include "..\07_LanguageFeatures\02_MaybeUnused.h"
#include "..\07_LanguageFeatures\03_IfConstExpr.h"
#include "..\07_LanguageFeatures\04_InlineVariable.h"
#include "..\07_LanguageFeatures\05_Noexcept.h"

using namespace LanguageFeatures;

TEST(LanguageFeaturesTest, NodiscardFunction)
{
	int val = ComputeValue(5);
	EXPECT_EQ(val, 10);

	Result r{ 42, "Answer" };
	EXPECT_EQ(r.value, 42);
	EXPECT_EQ(r.description, "Answer"); 

	auto f = []() -> Result { return { 7, "Seven" }; };
	// This call would cause a warning if uncommented
	// f();
}

TEST(LanguageFeaturesTest, MaybeUnused)
{
	UnusedFunction();
	MaybeUnusedExample();
	SUCCEED();
}

TEST(LanguageFeaturesTest, IfConstexpr)
{
	EXPECT_EQ(TypeName<int>(), "Integral");
	EXPECT_EQ(TypeName<double>(), "Floating point");
	EXPECT_EQ(TypeName<std::string>(), "Other");
}

TEST(LanguageFeaturesTest, InlineVariable)
{
	GlobalCounter = 5;
	EXPECT_EQ(GlobalCounter, 5);

	EXPECT_EQ(Config::MaxValue, 100);
}

TEST(LanguageFeaturesTest, NoexceptTrait)
{
	EXPECT_NO_THROW(MightThrow<int>());
	EXPECT_ANY_THROW(MightThrow<double>());
}

TEST(LanguageFeaturesTest, StaticVsInline)
{
	std::vector<int> resultsA;
	std::vector<int> resultsB;
	std::vector<int> resultsC;

	resultsA = getCountersA();
	resultsB = getCountersB();
	resultsC = getCountersC();

	// should be all zero
	EXPECT_EQ(resultsA[0], 0);
	EXPECT_EQ(resultsA[1], 0);
	EXPECT_EQ(resultsA[2], 0);
	EXPECT_EQ(resultsB[0], 0);
	EXPECT_EQ(resultsB[1], 0);
	EXPECT_EQ(resultsB[2], 0);
	EXPECT_EQ(resultsC[0], 0);
	EXPECT_EQ(resultsC[1], 0);
	EXPECT_EQ(resultsC[2], 0);

	incrementA();
	resultsA = getCountersA();
	resultsB = getCountersB();
	resultsC = getCountersC();
	EXPECT_EQ(resultsA[0], 1);
	EXPECT_EQ(resultsA[1], 1);
	EXPECT_EQ(resultsA[2], 1);
	EXPECT_EQ(resultsB[0], 0);
	EXPECT_EQ(resultsB[1], 1); // inline variable should be shared
	EXPECT_EQ(resultsB[2], 1); // inline static variable in class should be shared
	EXPECT_EQ(resultsC[0], 0);
	EXPECT_EQ(resultsC[1], 1); // inline variable should be shared
	EXPECT_EQ(resultsC[2], 1); // inline static variable in class should be shared

	incrementB();
	resultsA = getCountersA();
	resultsB = getCountersB();
	resultsC = getCountersC();
	EXPECT_EQ(resultsA[0], 1);
	EXPECT_EQ(resultsA[1], 2); // inline variable should be shared
	EXPECT_EQ(resultsA[2], 2); // inline static variable in class should be shared
	EXPECT_EQ(resultsB[0], 1);
	EXPECT_EQ(resultsB[1], 2);
	EXPECT_EQ(resultsB[2], 2);
	EXPECT_EQ(resultsC[0], 0);
	EXPECT_EQ(resultsC[1], 2); // inline variable should be shared
	EXPECT_EQ(resultsC[2], 2); // inline static variable in class should be shared

	incrementC();
	resultsA = getCountersA();
	resultsB = getCountersB();
	resultsC = getCountersC();
	EXPECT_EQ(resultsA[0], 1);
	EXPECT_EQ(resultsA[1], 3); // inline variable should be shared
	EXPECT_EQ(resultsA[2], 3); // inline static variable in class should be shared
	EXPECT_EQ(resultsB[0], 1);
	EXPECT_EQ(resultsB[1], 3); // inline variable should be shared
	EXPECT_EQ(resultsB[2], 3); // inline static variable in class should be shared
	EXPECT_EQ(resultsC[0], 1);
	EXPECT_EQ(resultsC[1], 3);
	EXPECT_EQ(resultsC[2], 3);

	// reportValues in ReportValues.cpp
	// staticCounter should be 0, because it's static in each cpp file
	// inlineCounter should be 3, because it's shared by all cpp files
	// Config::sharedValue should be 3, because it's inline static in class, shared by all cpp files
	EXPECT_EQ(reportValues(), "staticCounter=0, inlineCounter=3, Config::sharedValue=3");
}

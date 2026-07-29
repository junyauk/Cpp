#include "pch.h"
#include "..\04_SwitchInit\SwitchInitSample.h"

using namespace SwitchInitSample;

TEST(SwitchInitBasicTests, ModuloClassification)
{
	EXPECT_EQ(classifyByModulo(6), "divisible by 3");
	EXPECT_EQ(classifyByModulo(7), "remainder 1");
	EXPECT_EQ(classifyByModulo(8), "remainder 2");
}

TEST(SwitchInitBasicTests, VowelCheck)
{
	EXPECT_TRUE(isVowel('A'));
	EXPECT_TRUE(isVowel('e'));
	EXPECT_FALSE(isVowel('Z'));
}

TEST(SwitchInitBasicTests, EnumSwitch)
{
	EXPECT_EQ(toColor("red"), Color::Red);
	EXPECT_EQ(toColor("green"), Color::Green);
	EXPECT_EQ(toColor("blue"), Color::Blue);
	EXPECT_EQ(toColor("yellow"), Color::Unknown);
}

TEST(SwitchInitBasicTests, OptionalSwitch)
{
	EXPECT_EQ(toColorOrUnknown(std::optional<std::string>("red")), Color::Red);
	EXPECT_EQ(toColorOrUnknown(std::optional<std::string>("unknown")), Color::Unknown);
	EXPECT_EQ(toColorOrUnknown(std::nullopt), Color::Unknown);
}

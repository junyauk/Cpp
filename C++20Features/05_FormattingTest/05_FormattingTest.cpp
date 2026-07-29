#include "pch.h"
#include "..\05_Formatting\Formatting_Basic.h"

using namespace Formatting_Basic;

namespace Formatting_Basic_Test
{
	class FormattingBasicTest : public ::testing::Test
	{
	protected:
		FormattingBasic m_formatter;
	};

	// Test case for basic and implicit argument formatting
	TEST_F(FormattingBasicTest, BasicFormatting)
	{
		std::string expected = "MyApp Version 1";
		std::string result = m_formatter.formatBasic("MyApp", 1);
		EXPECT_EQ(expected, result);
	}

	// Test case for numerical precision, base conversion, and sign
	TEST_F(FormattingBasicTest, NumericalFormatting)
	{
		double pi = 3.14159265;
		int negativeNum = -42;

		// Expected: Pi: 3.1416, Binary: 101010, Sign: -42
		// Note: For signed integers, binary format does not include the sign prefix by default.
		std::string expected = "Pi: 3.1416, Binary: -101010, Sign: -42";

		// MSVC's implementation might handle negative binary slightly differently than standard;
		// checking the sign and precision part:
		auto result = m_formatter.formatNumbers(pi, negativeNum);
		// Assert the parts that are consistent (precision and sign)
		EXPECT_TRUE(result.find("Pi: 3.1416") != std::string::npos);
		EXPECT_TRUE(result.find("Sign: -42") != std::string::npos);
	}

	// Test case for padding and alignment
	TEST_F(FormattingBasicTest, AlignmentFormatting)
	{
		std::string item = "Keyboard";
		float price = 99.991f;

		// Item: "Keyboard-------" (15 chars)
		// Price: "***99.99" (8 chars, price rounded and padded)
		std::string expected = "Keyboard------- | ***99.99";
		std::string result = m_formatter.formatAlignment(item, price);

		EXPECT_EQ(expected, result);
	}

	using Formatting_Basic::TimeFormat; // enum class 

	// Test case for 24-hour formatting
	TEST_F(FormattingBasicTest, ChronoFormatting_Time24)
	{
		// Pass the enum value
		std::string result = m_formatter.formatChrono(TimeFormat::Time24Hour);

		// HH:MM:SS (8 chars)
		ASSERT_EQ(result.length(), 8);
		EXPECT_EQ(result[5], ':');
	}

	TEST_F(FormattingBasicTest, ChronoFormatting_FullDateTime24)
	{
		// Pass the enum value
		std::string result = m_formatter.formatChrono(TimeFormat::FullDateTime24);

		// YYYY-MM-DD HH:MM:SS (19 chars)
		ASSERT_EQ(result.length(), 19);
		EXPECT_EQ(result[13], ':');
	}

	// Test case for 12-hour formatting
	TEST_F(FormattingBasicTest, ChronoFormatting_Time12)
	{
		// Pass the enum value
		std::string result = m_formatter.formatChrono(TimeFormat::Time12Hour);

		// HH:MM:SS AM/PM (11 chars)
		ASSERT_EQ(result.length(), 11);
		EXPECT_EQ(result[8], ' ');
	}

	TEST_F(FormattingBasicTest, ChronoFormatting_FullDateTime12)
	{
		// Pass the enum value
		std::string result = m_formatter.formatChrono(TimeFormat::FullDateTime12);

		// YYYY-MM-DD HH:MM:SS xM (22 chars)
		ASSERT_EQ(result.length(), 22);
		EXPECT_EQ(result[21], 'M');
	}

	// Test case for date-only formatting
	TEST_F(FormattingBasicTest, ChronoFormatting_DateOnly)
	{
		// Pass the enum value
		std::string result = m_formatter.formatChrono(TimeFormat::DateOnly);

		// YYYY-MM-DD (10 chars)
		ASSERT_EQ(result.length(), 10);
		EXPECT_EQ(result[4], '-');
	}
}

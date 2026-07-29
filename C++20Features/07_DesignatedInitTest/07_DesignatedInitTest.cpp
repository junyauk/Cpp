#include "pch.h"
#include "../07_DesignatedInit/DesignatedInit_Basic.h"

using DesignatedInit_Basic::UserSettings;
using DesignatedInit_Basic::DesignatedInitBasic;

namespace DesignatedInit_Basic_Test
{
	class DesignatedInitTest : public ::testing::Test
	{
	protected:
		DesignatedInitBasic m_initBasic;
	};

	// Test case 1: Full initialization
	TEST_F(DesignatedInitTest, FullInitialization)
	{
		auto settings = m_initBasic.createFullSettings();

		// Assert that all members are initialized to the specified value.
		ASSERT_EQ(101, settings.m_id);
		EXPECT_TRUE(settings.m_darkMode);
		EXPECT_EQ("English", settings.m_language);
		EXPECT_EQ(12, settings.m_fontSize);
	}

	// Test case 2: Partial initialization and default values
	TEST_F(DesignatedInitTest, PartialInitialization)
	{
		auto settings = m_initBasic.createPartialSettings();

		// Assert explicitly initialized members.
		ASSERT_EQ(202, settings.m_id);
		EXPECT_FALSE(settings.m_darkMode);

		// Assert members that were default initialized (zero/empty).
		ASSERT_EQ("", settings.m_language);
		ASSERT_EQ(0, settings.m_fontSize);
	}

	TEST_F(DesignatedInitTest, PartialInitializationOK)
	{
		auto settings = m_initBasic.createPartialSettingsOK();

		// Assert explicitly initialized members.
		ASSERT_EQ(0, settings.m_id);
		EXPECT_TRUE(settings.m_darkMode);

		// Assert members that were default initialized (zero/empty).
		ASSERT_EQ("", settings.m_language);
		ASSERT_EQ(40, settings.m_fontSize);
	}

	// Test case 3: Check C++20 rule (order must be preserved)
	TEST_F(DesignatedInitTest, OrderPreserved)
	{
		// This test is conceptual, as reversing the order (e.g., .m_darkMode before .m_id)
		// would cause a COMPILER ERROR, preventing successful compilation.
		// C++20 ensures that: {.m_id=1, .m_fontSize=10} is valid,
		// but {.m_fontSize=10, .m_id=1} would be an error because m_fontSize is declared after m_id.
		SUCCEED() << "Order rule is enforced by the compiler, not at runtime.";
	}
}

